#ifndef HANDLERREGISTRY_H
#define HANDLERREGISTRY_H

#include "typeHandlers/PropertyTypeHandler.h"

class HandlerRegistry {
private:
	static QMap<QVariant::Type, PropertyTypeHandler*> m_registeredHandlers;

public:
	static void registerHandler(QVariant::Type type, PropertyTypeHandler *handler);
	static void deleteHandler(QVariant::Type type);

	static bool hasHandler(QVariant::Type type) {
		return m_registeredHandlers.contains(type);
	}

	static PropertyTypeHandler* getHandler(QVariant::Type type) {
		return m_registeredHandlers[type];
	}

	static void initBasicHandlers();
};

#endif // HANDLERREGISTRY_H
