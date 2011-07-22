#ifndef PROPERTYTYPEHANDLER_H
#define PROPERTYTYPEHANDLER_H

#include "../PropertyEditor.h"

#include <QMap>

class PropertyTypeHandler {
public:
	virtual QWidget *createEditor(PropertyEditor::ValueItem *item) = 0;
	virtual void setModelData(QWidget *editor, PropertyEditor::ValueItem *item) = 0;
};

#endif // PROPERTYTYPEHANDLER_H
