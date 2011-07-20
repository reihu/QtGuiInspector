#include "PropertyEditor.h"

#include <QHeaderView>
#include <QMetaProperty>

PropertyEditor::PropertyEditor(QWidget *parent) : QTreeView(parent) {
	m_object = 0;

	setModel(&m_model);

	setRootIsDecorated(false);
}

void PropertyEditor::setObject(QObject *object) {
	m_object = object;
	m_model.clear();

	m_model.setColumnCount(2);
	m_model.setHorizontalHeaderLabels(QStringList() << tr("Name") << tr("Value"));
	m_model.setRowCount(object->metaObject()->propertyCount());
	for (int i = 0; i < object->metaObject()->propertyCount(); i++) {
		QMetaProperty property = object->metaObject()->property(i);
		const char *propertyName = property.name();
		QVariant value = object->property(propertyName);
		QStandardItem *item = new QStandardItem(propertyName);
		item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		m_model.setItem(i, 0, item);

		item = new QStandardItem(value.toString());
		m_model.setItem(i, 1, item);
	}
}
