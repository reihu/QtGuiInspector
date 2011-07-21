#ifndef BOOLHANDLER_H
#define BOOLHANDLER_H

#include "PropertyTypeHandler.h"

class BoolHandler : public PropertyTypeHandler {
public:
	virtual QWidget *createEditor(PropertyEditor::ValueItem *item);
	virtual void setModelData(QWidget *editor, PropertyEditor::ValueItem *item);
};

#endif // BOOLHANDLER_H
