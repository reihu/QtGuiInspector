#include "PropertyDelegate.h"
#include "PropertyEditor.h"
#include "typeHandlers/EnumHandler.h"
#include "typeHandlers/PropertyTypeHandler.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QStandardItemModel>

Q_DECLARE_METATYPE(QMetaProperty)

PropertyDelegate::PropertyDelegate(QObject *parent):
		QItemDelegate(parent) {
	PropertyTypeHandler::initBasicHandlers();
}

QWidget* PropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	const QStandardItemModel *model = static_cast<const QStandardItemModel*>(index.model());
	PropertyEditor::ValueItem *item = static_cast<PropertyEditor::ValueItem*>(model->itemFromIndex(index));
	QMetaProperty metaProperty = item->getMetaProperty();
	QVariant::Type type = metaProperty.type();
	QVariant data = index.data();
	QWidget *rc = 0;

	if (metaProperty.isEnumType()) {
		EnumHandler handler;
		rc = handler.createEditor(item);
	}
	else if (PropertyTypeHandler::hasHandler(type)) {
		PropertyTypeHandler *handler = PropertyTypeHandler::getHandler(type);
		rc = handler->createEditor(item);
	}
	else if (type == QVariant::Int) {
		QSpinBox *spinBox = new QSpinBox();
		spinBox->setValue(data.toInt());
		rc = spinBox;
	}
	else {
		qWarning("Unexpected data type: %s", metaProperty.typeName());
		rc = new QLineEdit(data.toString());
	}

	rc->setParent(parent);
	return rc;
}

void PropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *standardModel, const QModelIndex &index) const {
	QStandardItemModel *model = static_cast<QStandardItemModel*>(standardModel);
	PropertyEditor::ValueItem *item = static_cast<PropertyEditor::ValueItem*>(model->itemFromIndex(index));
	QMetaProperty metaProperty = item->getMetaProperty();
	QVariant::Type type = metaProperty.type();
	QObject *object = item->getObject();

	if (metaProperty.isEnumType()) {
		EnumHandler handler;
		handler.setModelData(editor, item);
	}
	else if (PropertyTypeHandler::hasHandler(type)) {
		PropertyTypeHandler *handler = PropertyTypeHandler::getHandler(type);
		handler->setModelData(editor, item);
	}

	QString propertyName = model->index(index.row(), 1).data().toString();

	object->setProperty(propertyName.toLocal8Bit().constData(), index.data());
}
