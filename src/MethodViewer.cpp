#include "MethodViewer.h"

#include <QContextMenuEvent>
#include <QInputDialog>
#include <QMenu>

Q_DECLARE_METATYPE(MethodViewer::Item*)

MethodViewer::Item::Item(QObject *object, const QMetaMethod &method) {
	QMetaMethod::MethodType methodType = method.methodType();

	setText(0, getMethodTypeName(methodType));
	setText(1, method.signature());

	m_method = method;
	m_object = object;
}

MethodViewer::MethodViewer(QWidget *parent):
	QTreeWidget(parent) {
	setColumnCount(2);
	setHeaderLabels(QStringList() << tr("Type") << tr("Signature"));

	connect(&m_invokeTimer, SIGNAL(timeout()), this, SLOT(_invokeTimerTick()));
}

void MethodViewer::_invokeMethod() {
	QAction *sender = static_cast<QAction*>(this->sender());
	Item *item = sender->property("treeItem").value<MethodViewer::Item*>();
	item->getMethod().invoke(item->getObject());
}

void MethodViewer::_invokeMethodEvery() {
	QAction *sender = static_cast<QAction*>(this->sender());
	Item *item = sender->property("treeItem").value<MethodViewer::Item*>();
	QMetaMethod method = item->getMethod();

	bool bOk;
	int interval = QInputDialog::getInt(this, tr("Invoke method %1 every...").arg(method.signature()),
										tr("Interval in seconds"), 5, 1, 30, 1, &bOk);

	if (!bOk) return;

	m_invokedMethod = method;
	m_invokedObject = item->getObject();
	m_invokeTimer.start(interval*1000);
}

void MethodViewer::_invokeTimerTick() {
	m_invokedMethod.invoke(m_invokedObject);
}

void MethodViewer::contextMenuEvent(QContextMenuEvent *event) {
	Item *item = static_cast<Item*>(itemAt(event->pos()));
	QMenu menu(this);

	if ((item->isSignal() || item->isSlot()) && item->getMethod().parameterNames().count() == 0) {
		QAction *action = menu.addAction("invoke", this, SLOT(_invokeMethod()));
		action->setProperty("treeItem", QVariant::fromValue<MethodViewer::Item*>(item));
		action = menu.addAction(tr("Invoke every n seconds..."), this, SLOT(_invokeMethodEvery()));
		action->setProperty("treeItem", QVariant::fromValue<MethodViewer::Item*>(item));

	}

	if (m_invokeTimer.isActive()) {
		menu.addAction(tr("Stop Invoking %1()").arg(m_invokedMethod.tag()), &m_invokeTimer, SLOT(stop()));
	}

	if (!menu.isEmpty()) menu.exec(mapToGlobal(event->pos()));
}

const char* MethodViewer::getMethodTypeName(QMetaMethod::MethodType methodType) {
	const char *rc = 0;

	switch (methodType) {
	case QMetaMethod::Constructor:
		rc = "constructor";
		break;
	case QMetaMethod::Method:
		rc = "method";
		break;
	case QMetaMethod::Signal:
		rc = "signal";
		break;
	case QMetaMethod::Slot:
		rc = "slot";
		break;
	}

	return rc;
}

void MethodViewer::setObject(QObject *object) {
	const QMetaObject *metaObject = object->metaObject();

	setSortingEnabled(false);
	clear();
	for (int i = 0; i < metaObject->methodCount(); i++) {
		QMetaMethod method = metaObject->method(i);
		addTopLevelItem(new Item(object, method));
	}

	setSortingEnabled(true);
	sortByColumn(1, Qt::AscendingOrder);
	sortByColumn(0, Qt::AscendingOrder);
}
