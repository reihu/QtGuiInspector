#ifndef SIZEPOLICYHANDLER_H
#define SIZEPOLICYHANDLER_H

#include "PropertyTypeHandler.h"

class SizePolicyHandler : public PropertyTypeHandler {
public:
	virtual QWidget *createEditor(PropertyEditor::ValueItem *item);
	virtual void setModelData(QWidget *editor, PropertyEditor::ValueItem *item);

	virtual QString toString(const QVariant &variant);
	QString toString(QSizePolicy::Policy policy);
};

#endif // SIZEPOLICYHANDLER_H
