#include "EnumHandler.h"
#include "PropertyTypeHandler.h"

QMap<QVariant::Type, PropertyTypeHandler*> PropertyTypeHandler::m_registeredHandlers;

PropertyTypeHandler::PropertyTypeHandler() {
	// register some basic types
}

void PropertyTypeHandler::registerHandler(QVariant::Type type, PropertyTypeHandler *handler) {
	m_registeredHandlers.insert(type, handler);
}

void PropertyTypeHandler::deleteHandler(QVariant::Type type) {
	if (m_registeredHandlers.contains(type)) {
		delete m_registeredHandlers[type];
		m_registeredHandlers.remove(type);
	}
}
