#include "SizePolicyHandler.h"

#include <QLabel>

QWidget* SizePolicyHandler::createEditor(PropertyEditor::ValueItem *item) {
	return NULL; // Editing isn't possible atm
}

void SizePolicyHandler::setModelData(QWidget *editor, PropertyEditor::ValueItem *item) {
}

QString SizePolicyHandler::toString(const QVariant &variant) {
	QString rc;
	if (variant.type() == QVariant::SizePolicy) {
		QSizePolicy policy = variant.value<QSizePolicy>();
		rc = QString("[%1, %2]").arg(toString(policy.horizontalPolicy())).arg(toString(policy.verticalPolicy()));
	}
	else rc = "[not a QSizePolicy!]";
	return rc;
}

QString SizePolicyHandler::toString(QSizePolicy::Policy policy) {
	const QMetaObject &metaObject = QSizePolicy::staticMetaObject;
	int index = metaObject.indexOfEnumerator("Policy");
	QMetaEnum enumerator = metaObject.enumerator(index);

	return enumerator.valueToKey(policy);
}
