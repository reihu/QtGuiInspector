#ifndef POINTHANDLER_H
#define POINTHANDLER_H

#include "PropertyTypeHandler.h"

class PointHandler : public PropertyTypeHandler {
public:
	virtual QWidget *createEditor(PropertyEditor::ValueItem *item);
	virtual void setModelData(QWidget *editor, PropertyEditor::ValueItem *item);

	virtual QString toString(const QVariant &variant);
};

#endif // POINTHANDLER_H
