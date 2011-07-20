#include "SignalSlotViewer.h"

#include <QContextMenuEvent>
#include <QInputDialog>
#include <QMenu>

Q_DECLARE_METATYPE(SignalSlotViewer::SSVItem*)

SignalSlotViewer::SSVItem::SSVItem(QObject *object, const QMetaMethod &method) {
	QMetaMethod::MethodType methodType = method.methodType();

	setText(0, getMethodTypeName(methodType));
	setText(1, method.signature());

	m_method = method;
	m_object = object;
}

SignalSlotViewer::SignalSlotViewer(QWidget *parent):
	QTreeWidget(parent) {
	setColumnCount(2);
	setHeaderLabels(QStringList() << tr("Type") << tr("Signature"));

	connect(&m_invokeTimer, SIGNAL(timeout()), this, SLOT(_invokeTimerTick()));
}

void SignalSlotViewer::_invokeMethod() {
	QAction *sender = static_cast<QAction*>(this->sender());
	SSVItem *item = sender->property("treeItem").value<SignalSlotViewer::SSVItem*>();
	item->getMethod().invoke(item->getObject());
}

void SignalSlotViewer::_invokeMethodEvery() {
	QAction *sender = static_cast<QAction*>(this->sender());
	SSVItem *item = sender->property("treeItem").value<SignalSlotViewer::SSVItem*>();
	QMetaMethod method = item->getMethod();

	bool bOk;
	int interval = QInputDialog::getInt(this, tr("Invoke method %1 every...").arg(method.signature()),
										tr("Interval in seconds"), 5, 1, 30, 1, &bOk);

	if (!bOk) return;

	m_invokedMethod = method;
	m_invokedObject = item->getObject();
	m_invokeTimer.start(interval*1000);
}

void SignalSlotViewer::_invokeTimerTick() {
	m_invokedMethod.invoke(m_invokedObject);
}

void SignalSlotViewer::contextMenuEvent(QContextMenuEvent *event) {
	SSVItem *item = static_cast<SSVItem*>(itemAt(event->pos()));
	QMenu menu(this);

	if ((item->isSignal() || item->isSlot()) && item->getMethod().parameterNames().count() == 0) {
		QAction *action = menu.addAction("invoke", this, SLOT(_invokeMethod()));
		action->setProperty("treeItem", QVariant::fromValue<SignalSlotViewer::SSVItem*>(item));
		action = menu.addAction(tr("Invoke every n seconds..."), this, SLOT(_invokeMethodEvery()));
		action->setProperty("treeItem", QVariant::fromValue<SignalSlotViewer::SSVItem*>(item));

	}

	if (m_invokeTimer.isActive()) {
		menu.addAction(tr("Stop Invoking %1()").arg(m_invokedMethod.tag()), &m_invokeTimer, SLOT(stop()));
	}

	if (!menu.isEmpty()) menu.exec(mapToGlobal(event->pos()));
}

const char* SignalSlotViewer::getMethodTypeName(QMetaMethod::MethodType methodType) {
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

void SignalSlotViewer::setObject(QObject *object) {
	const QMetaObject *metaObject = object->metaObject();

	setSortingEnabled(false);
	clear();
	for (int i = 0; i < metaObject->methodCount(); i++) {
		QMetaMethod method = metaObject->method(i);
		addTopLevelItem(new SSVItem(object, method));
	}

	setSortingEnabled(true);
	sortByColumn(1, Qt::AscendingOrder);
	sortByColumn(0, Qt::AscendingOrder);
}
