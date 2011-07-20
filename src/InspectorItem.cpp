#include "InspectorItem.h"

InspectorItem::InspectorItem(QObject *object) : QTreeWidgetItem() {
	m_object = object;

	setText(0, object->metaObject()->className());
	setText(1, object->objectName());

	connect(object, SIGNAL(destroyed()), this, SLOT(_objectDestroyed()));
}

void InspectorItem::_objectDestroyed() {
	// delete this InspectorItem
	delete this;
}

QObject* InspectorItem::getObject() {
	return m_object;
}

QWidget* InspectorItem::getWidget() {
	return dynamic_cast<QWidget*>(m_object);
}
