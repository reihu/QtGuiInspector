#include "PropertyDelegate.h"

#include <QCheckBox>
#include <QLineEdit>

PropertyDelegate::PropertyDelegate(QObject *parent):
		QItemDelegate(parent) {

}

QWidget* PropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	QWidget *rc = 0;

	index.column();
	index.row();
	QVariant data = index.data();

	qDebug(":: Requested Editor for variant of type '%s'", data.typeName());

	if (data.type() == QVariant::Bool) {
		QCheckBox *checkBox = new QCheckBox();
		checkBox->setChecked(data.toBool());
		rc = checkBox;
	}
	else if (data.type() == QVariant::String) {
		rc = new QLineEdit(data.toString());
	}
	else {
		qWarning("Unexpected data type: %s", data.typeName());
		rc = new QLineEdit(data.toString());
	}

	rc->setParent(parent);
	return rc;
}

void PropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
	if (QCheckBox *checkBox = dynamic_cast<QCheckBox*>(editor)) {
		model->setData(index, checkBox->isChecked());
	}
	else if (QLineEdit *lineEdit = dynamic_cast<QLineEdit*>(editor)) {
		model->setData(index, lineEdit->text());
	}

	QString propertyName = model->index(index.row(), 1).data().toString();

	QObject *obj = index.data(Qt::UserRole).value<QObject*>();
	obj->setProperty(propertyName.toLocal8Bit().constData(), index.data());
}
