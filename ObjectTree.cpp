#include "ObjectTree.h"
#include "InspectorItem.h"

ObjectTree::ObjectTree(QWidget *parent) : QTreeWidget(parent) {
	connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(_selectionChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
}

void ObjectTree::_buildTree(QTreeWidgetItem *parentItem, QObject *object) {
	QTreeWidgetItem *item = new InspectorItem(object);
	parentItem->addChild(item);

	foreach (QObject *childWidget, object->children()) {
		_buildTree(item, childWidget);
	}
}

void ObjectTree::_selectionChanged(QTreeWidgetItem *current, QTreeWidgetItem* /*previous*/) {
	InspectorItem *item = static_cast<InspectorItem*>(current);
	if (item) {
		emit objectSelected(item->getObject());
		QWidget *wgt = item->getWidget();
		if (wgt) {
			emit widgetSelected(wgt);
		}
	}
}

void ObjectTree::displayTree(QObject *object) {
	clear();
	_buildTree(invisibleRootItem(), object);
}
