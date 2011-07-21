#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H

#include "PropertyTypeHandler.h"

class StringHandler : public PropertyTypeHandler {
public:
	virtual QWidget *createEditor(PropertyEditor::ValueItem *item);
	virtual void setModelData(QWidget *editor, PropertyEditor::ValueItem *item);
};

#endif // STRINGHANDLER_H
