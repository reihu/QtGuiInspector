#include "SignalSlotViewer.h"

#include <QContextMenuEvent>
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
	setSortingEnabled(true);
	sortByColumn(0, Qt::AscendingOrder);
}

void SignalSlotViewer::_invokeMethod() {
	QAction *sender = static_cast<QAction*>(this->sender());
	SSVItem *item = sender->property("treeItem").value<SignalSlotViewer::SSVItem*>();
	item->getMethod().invoke(item->getObject());
}

void SignalSlotViewer::contextMenuEvent(QContextMenuEvent *event) {
	SSVItem *item = static_cast<SSVItem*>(itemAt(event->pos()));
	if (item->isSlot() && item->getMethod().parameterNames().count() == 0) {
		QMenu menu(this);
		QAction *action = menu.addAction("invoke", this, SLOT(_invokeMethod()));
		action->setProperty("treeItem", QVariant::fromValue<SignalSlotViewer::SSVItem*>(item));
		menu.exec(mapToGlobal(event->pos()));
	}
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

	clear();
	for (int i = 0; i < metaObject->methodCount(); i++) {
		QMetaMethod method = metaObject->method(i);
		addTopLevelItem(new SSVItem(object, method));
	}
}
