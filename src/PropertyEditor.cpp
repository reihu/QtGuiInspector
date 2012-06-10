#include "HandlerRegistry.h"
#include "PropertyEditor.h"

#include <QHeaderView>
#include <QMetaProperty>

PropertyEditor::ValueItem::ValueItem(const QVariant &value, QObject *object, const QMetaProperty &metaProperty) {
	QString valueString;
	if (HandlerRegistry::hasHandler(value.type())) {
		valueString = HandlerRegistry::getHandler(value.type())->toString(value);
	}
	else valueString = value.toString();
	setText(valueString);

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

void PropertyEditor::ValueItem::setValue(const QVariant &value, const QString &displayText) {
	m_value = value;
	setText(displayText);
}

PropertyEditor::PropertyEditor(QWidget *parent): QTreeView(parent) {
	m_object = 0;

	setModel(&m_model);
	setItemDelegate(&m_delegate);

	setRootIsDecorated(false);
}

void PropertyEditor::_addProperty(const char *className, const char *typeName, const char *key, ValueItem *valueItem) {

#if 0
		qDebug(":: Property '%s'='%s' (type: '%s', variantType: '%s', class: '%s')", propertyName,
			   value.toString().toLocal8Bit().constData(),
			   property.typeName(), value.typeName(),
			   property.enclosingMetaObject()->className());
#endif

		QList<QStandardItem*> rowItems;
		// defining class
		QStandardItem *item = new QStandardItem(className);
		item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		rowItems << item;

		// property type
		item = new QStandardItem(typeName);
		item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		rowItems << item;

		// property name
		item = new QStandardItem(key);
		item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		rowItems << item;

		// property value
		rowItems << valueItem;

		m_model.appendRow(rowItems);
}

void PropertyEditor::setObject(QObject *object) {
	m_object = object;
	m_model.clear();

	m_model.setColumnCount(4);
	m_model.setHorizontalHeaderLabels(QStringList() << tr("Class") << tr("Type") << tr("Name") << tr("Value"));

	for (int i = 0; i < object->metaObject()->propertyCount(); i++) {
		QMetaProperty property = object->metaObject()->property(i);
		const char *propertyName = property.name();
		QVariant value = object->property(propertyName);
		const char *className = property.enclosingMetaObject()->className();

		_addProperty(className, property.typeName(), propertyName, new ValueItem(value, object, property));
	}

	QMetaProperty dynamicMetaProperty;
	foreach (QByteArray dynPropName, object->dynamicPropertyNames()) {
		QVariant value = object->property(dynPropName.constData());
		_addProperty("_dynamic", value.typeName(), dynPropName, new ValueItem(value, object, dynamicMetaProperty));
	}

	/// @todo Add dynamic property support
}
