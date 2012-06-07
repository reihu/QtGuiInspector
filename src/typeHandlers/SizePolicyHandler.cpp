#include "../HandlerRegistry.h"
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
#if 0
	QString rc = "UNKNOWN";
	switch (policy) {
	case QSizePolicy::Fixed:
		rc = "Fixed";
		break;
	case QSizePolicy::Minimum:
		rc = "Minimum";
		break;
	case QSizePolicy::Maximum:
		rc = "Maximum";
		break;
	case QSizePolicy::Preferred:
		rc = "Preferred";
		break;
	case QSizePolicy::MinimumExpanding:
		rc = "MinimumExpanding";
		break;
	case QSizePolicy::Expanding:
		rc = "Expanding";
		break;
	case QSizePolicy::Ignored:
		rc = "Ignored";
		break;
	}
	return rc;
#else
	const QMetaObject &metaObject = QSizePolicy::staticMetaObject;
	int index = metaObject.indexOfEnumerator("Policy");
	QMetaEnum enumerator = metaObject.enumerator(index);

	return enumerator.valueToKey(policy);
#endif
}
