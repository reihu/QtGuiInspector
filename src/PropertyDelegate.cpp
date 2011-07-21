#include "PropertyDelegate.h"
#include "PropertyEditor.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QStandardItemModel>

Q_DECLARE_METATYPE(QMetaProperty)

PropertyDelegate::PropertyDelegate(QObject *parent):
		QItemDelegate(parent) {
}

QWidget* PropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	const QStandardItemModel *model = static_cast<const QStandardItemModel*>(index.model());
	PropertyEditor::ValueItem *item = static_cast<PropertyEditor::ValueItem*>(model->itemFromIndex(index));
	QMetaProperty metaProperty = item->getMetaProperty();
	QVariant::Type type = metaProperty.type();
	QVariant data = index.data();
	QWidget *rc = 0;

	qDebug(":: Requested Editor for variant of type '%s'", data.typeName());

	if (metaProperty.isEnumType()) {
		QMetaEnum metaEnum = metaProperty.enumerator();
		QComboBox *cbo = new QComboBox();
		int currentIndex = -1, currentValue = data.toInt();
		for (int i = 0; i < metaEnum.keyCount(); i++) {
			cbo->addItem(metaEnum.key(i), metaEnum.value(i));
			if (currentIndex < 0 && currentValue == metaEnum.value(i)) currentIndex = i;
		}
		if (currentIndex >= 0) cbo->setCurrentIndex(currentIndex);

		rc = cbo;
	}
	else if (type == QVariant::Bool) {
		QCheckBox *checkBox = new QCheckBox();
		checkBox->setChecked(data.toBool());
		rc = checkBox;
	}
	else if (type == QVariant::String) {
		rc = new QLineEdit(data.toString());
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
	QObject *object = item->getObject();

	if (QComboBox *cbo = dynamic_cast<QComboBox*>(editor)) {
		QMetaEnum metaEnum = item->getMetaProperty().enumerator();
		int value = cbo->itemData(cbo->currentIndex()).toInt();

		item->setValue(value);
		model->setData(index, metaEnum.key(value));
	}
	else if (QCheckBox *checkBox = dynamic_cast<QCheckBox*>(editor)) {
		model->setData(index, checkBox->isChecked());
	}
	else if (QLineEdit *lineEdit = dynamic_cast<QLineEdit*>(editor)) {
		model->setData(index, lineEdit->text());
	}

	QString propertyName = model->index(index.row(), 1).data().toString();

	object->setProperty(propertyName.toLocal8Bit().constData(), index.data());
}
