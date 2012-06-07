#ifndef SIZEHANDLER_H
#define SIZEHANDLER_H

#include "PropertyTypeHandler.h"

class SizeHandler : public PropertyTypeHandler {
public:
	virtual QWidget *createEditor(PropertyEditor::ValueItem *item);
	virtual void setModelData(QWidget *editor, PropertyEditor::ValueItem *item);

	virtual QString toString(const QVariant &variant);
};

#endif // SIZEHANDLER_H
