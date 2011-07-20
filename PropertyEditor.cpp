#include "PropertyEditor.h"
#include <QMetaProperty>

PropertyEditor::PropertyEditor(QWidget *parent) : QTreeWidget(parent) {
	m_object = 0;
	setHeaderLabels(QStringList() << tr("Name") << tr("Value"));
}

void PropertyEditor::setObject(QObject *object) {
	m_object = object;
	clear();
	for (int i = 0; i < object->metaObject()->propertyCount(); i++) {
		QMetaProperty property = object->metaObject()->property(i);
		const char *propertyName = property.name();
		QVariant value = object->property(propertyName);
		QTreeWidgetItem *item = new QTreeWidgetItem();
		item->setText(0, propertyName);
		item->setText(1, value.toString());
		addTopLevelItem(item);
	}
}
