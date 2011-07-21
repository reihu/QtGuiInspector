#include "BoolHandler.h"

#include <QCheckBox>

QWidget* BoolHandler::createEditor(PropertyEditor::ValueItem *item) {
	QCheckBox *checkBox = new QCheckBox();
	checkBox->setChecked(item->getValue().toBool());
	return checkBox;
}

void BoolHandler::setModelData(QWidget *editor, PropertyEditor::ValueItem *item) {
	QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
	item->setValue(checkBox->isChecked());
}
