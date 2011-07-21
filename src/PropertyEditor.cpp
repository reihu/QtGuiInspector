#include "PropertyEditor.h"

#include <QHeaderView>
#include <QMetaProperty>

PropertyEditor::ValueItem::ValueItem(const QVariant &value, QObject *object, QMetaProperty metaProperty):
		QStandardItem(value.toString()) {
	m_object = object;
	m_metaProperty = metaProperty;
	m_value = value;

	if (!metaProperty.isWritable()) {
		setFlags(flags() & ~Qt::ItemIsEditable);
	}

	if (metaProperty.isEnumType()) {
		QMetaEnum metaEnum = metaProperty.enumerator();
		setText(metaEnum.key(value.toInt()));
	}
}

PropertyEditor::PropertyEditor(QWidget *parent) : QTreeView(parent) {
	m_object = 0;

	setModel(&m_model);
	setItemDelegate(&m_delegate);

	setRootIsDecorated(false);
}

void PropertyEditor::setObject(QObject *object) {
	m_object = object;
	m_model.clear();

	m_model.setColumnCount(3);
	m_model.setHorizontalHeaderLabels(QStringList() << tr("Class") << tr("Name") << tr("Value"));

	m_model.setRowCount(object->metaObject()->propertyCount());
	for (int i = 0; i < object->metaObject()->propertyCount(); i++) {
		QMetaProperty property = object->metaObject()->property(i);
		const char *propertyName = property.name();
		QVariant value = object->property(propertyName);

#if 0
		qDebug(":: Property '%s'='%s' (type: '%s', variantType: '%s', class: '%s')", propertyName,
			   value.toString().toLocal8Bit().constData(),
			   property.typeName(), value.typeName(),
			   property.enclosingMetaObject()->className());
#endif

		QStandardItem *item = new QStandardItem(property.enclosingMetaObject()->className());
		item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		m_model.setItem(i, 0, item);

		item = new QStandardItem(propertyName);
		item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		m_model.setItem(i, 1, item);

		item = new ValueItem(value, object, property);
		m_model.setItem(i, 2, item);
	}

	/// @todo Add dynamic property support
}
