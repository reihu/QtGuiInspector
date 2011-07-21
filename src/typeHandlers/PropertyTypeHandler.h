#ifndef PROPERTYTYPEHANDLER_H
#define PROPERTYTYPEHANDLER_H

#include "../PropertyEditor.h"

#include <QMap>

class PropertyTypeHandler {
private:
	static QMap<QVariant::Type, PropertyTypeHandler*> m_registeredHandlers;
public:
	PropertyTypeHandler();

	virtual QWidget *createEditor(PropertyEditor::ValueItem *item) = 0;
	virtual void setModelData(QWidget *editor, QStandardItemModel *model, PropertyEditor::ValueItem *item) = 0;

	static void registerHandler(QVariant::Type type, PropertyTypeHandler *handler);
	static void deleteHandler(QVariant::Type type);

	static bool hasHandler(QVariant::Type type) {
		return m_registeredHandlers.contains(type);
	}

	static PropertyTypeHandler* getHandler(QVariant::Type type) {
		return m_registeredHandlers[type];
	}
};

#endif // PROPERTYTYPEHANDLER_H
