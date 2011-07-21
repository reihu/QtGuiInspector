#ifndef INTHANDLER_H
#define INTHANDLER_H

#include "PropertyTypeHandler.h"

class IntHandler : public PropertyTypeHandler {
public:
	virtual QWidget *createEditor(PropertyEditor::ValueItem *item);
	virtual void setModelData(QWidget *editor, PropertyEditor::ValueItem *item);
};

#endif // INTHANDLER_H
