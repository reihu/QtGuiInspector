#include "PropertyDelegate.h"
#include "PropertyEditor.h"
#include "typeHandlers/EnumHandler.h"
#include "HandlerRegistry.h"

#include <QLabel>
#include <QStandardItemModel>

Q_DECLARE_METATYPE(QMetaProperty)

PropertyDelegate::PropertyDelegate(QObject *parent):
		QItemDelegate(parent) {
	HandlerRegistry::initBasicHandlers();
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
	else if (HandlerRegistry::hasHandler(type)) {
		PropertyTypeHandler *handler = HandlerRegistry::getHandler(type);
		rc = handler->createEditor(item);
	}
	else {
		qWarning("Unexpected data type: %s", metaProperty.typeName());
		rc = new QLabel("Editing not yet implemented...");
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
	else if (HandlerRegistry::hasHandler(type)) {
		PropertyTypeHandler *handler = HandlerRegistry::getHandler(type);
		handler->setModelData(editor, item);
	}

	QString propertyName = model->index(index.row(), 1).data().toString();

	object->setProperty(propertyName.toLocal8Bit().constData(), index.data());
}
