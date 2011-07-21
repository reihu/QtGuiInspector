#include "EnumHandler.h"
#include "PropertyTypeHandler.h"
#include "StringHandler.h"

QMap<QVariant::Type, PropertyTypeHandler*> PropertyTypeHandler::m_registeredHandlers;

void PropertyTypeHandler::initBasicHandlers() {
	// register some basic types
	registerHandler(QVariant::String, new StringHandler());
}

void PropertyTypeHandler::deleteHandler(QVariant::Type type) {
	if (m_registeredHandlers.contains(type)) {
		delete m_registeredHandlers[type];
		m_registeredHandlers.remove(type);
	}
}

void PropertyTypeHandler::registerHandler(QVariant::Type type, PropertyTypeHandler *handler) {
	m_registeredHandlers.insert(type, handler);
}
