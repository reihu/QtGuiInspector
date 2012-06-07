#ifndef RECTHANDLER_H
#define RECTHANDLER_H

#include "PropertyTypeHandler.h"

class RectHandler : public PropertyTypeHandler {
public:
	virtual QWidget *createEditor(PropertyEditor::ValueItem *item);
	virtual void setModelData(QWidget *editor, PropertyEditor::ValueItem *item);

	virtual QString toString(const QVariant &variant);
};

#endif // RECTHANDLER_H
