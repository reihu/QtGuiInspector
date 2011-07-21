#include "BoolHandler.h"

QWidget* BoolHandler::createEditor(PropertyEditor::ValueItem *item) {
	QCheckBox *checkBox = new QCheckBox();
	checkBox->setChecked(data.toBool());
	return checkBox;
}

void BoolHandler::setModelData(QWidget *editor, PropertyEditor::ValueItem *item) {
	QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
	item->setText(checkBox->isChecked());
}
