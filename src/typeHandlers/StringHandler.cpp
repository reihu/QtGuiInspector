#include "StringHandler.h"

#include <QLineEdit>

QWidget* StringHandler::createEditor(PropertyEditor::ValueItem *item) {
	return new QLineEdit(item->getValue().toString());
}

void StringHandler::setModelData(QWidget *editor, PropertyEditor::ValueItem *item) {
	QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
	item->setText(lineEdit->text());
}
