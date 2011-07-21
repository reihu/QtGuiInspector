#include "EnumHandler.h"

#include <QComboBox>

QWidget* EnumHandler::createEditor(PropertyEditor::ValueItem *item) {
	QMetaEnum metaEnum = item->getMetaProperty().enumerator();
	QComboBox *cbo = new QComboBox();
	int currentIndex = -1, currentValue = item->getValue().toInt();
	for (int i = 0; i < metaEnum.keyCount(); i++) {
		cbo->addItem(metaEnum.key(i), metaEnum.value(i));
		if (currentIndex < 0 && currentValue == metaEnum.value(i)) currentIndex = i;
	}
	if (currentIndex >= 0) cbo->setCurrentIndex(currentIndex);

	return cbo;
}

void EnumHandler::setModelData(QWidget *editor, QStandardItemModel *model, PropertyEditor::ValueItem *item) {
	QComboBox *cbo = static_cast<QComboBox*>(editor);
	QMetaEnum metaEnum = item->getMetaProperty().enumerator();
	int value = cbo->itemData(cbo->currentIndex()).toInt();

	item->setValue(value);
	item->setText(metaEnum.key(value));
}
