#ifndef ENUMHANDLER_H
#define ENUMHANDLER_H

#include "PropertyTypeHandler.h"

class EnumHandler : public PropertyTypeHandler {
public:
	virtual QWidget *createEditor(PropertyEditor::ValueItem *item);
	virtual void setModelData(QWidget *editor, QStandardItemModel *model, PropertyEditor::ValueItem *item);
};

#endif // ENUMHANDLER_H
