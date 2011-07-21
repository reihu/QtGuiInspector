#include "IntHandler.h"

#include <QIntValidator>
#include <QSpinBox>

QWidget* IntHandler::createEditor(PropertyEditor::ValueItem *item) {
	QIntValidator validator;
	QSpinBox *spinBox = new QSpinBox();
	spinBox->setRange(validator.bottom(), validator.top());
	spinBox->setValue(item->getValue().toInt());
	return spinBox;
}

void IntHandler::setModelData(QWidget *editor, PropertyEditor::ValueItem *item) {
	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	item->setValue(spinBox->value());
}
