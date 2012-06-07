#include "HandlerRegistry.h"
#include "typeHandlers/BoolHandler.h"
#include "typeHandlers/IntHandler.h"
#include "typeHandlers/SizePolicyHandler.h"
#include "typeHandlers/StringHandler.h"

QMap<QVariant::Type, PropertyTypeHandler*> HandlerRegistry::m_registeredHandlers;

void HandlerRegistry::cleanup() {
	foreach (QVariant::Type type, m_registeredHandlers.keys()) {
		deleteHandler(type);
	}
}

void HandlerRegistry::initBasicHandlers() {
	// register some basic types
	registerHandler(QVariant::Bool, new BoolHandler());
	registerHandler(QVariant::Int, new IntHandler());
	registerHandler(QVariant::SizePolicy, new SizePolicyHandler());
	registerHandler(QVariant::String, new StringHandler());
}

void HandlerRegistry::deleteHandler(QVariant::Type type) {
	if (m_registeredHandlers.contains(type)) {
		delete m_registeredHandlers[type];
		m_registeredHandlers.remove(type);
	}
}

void HandlerRegistry::registerHandler(QVariant::Type type, PropertyTypeHandler *handler) {
	m_registeredHandlers.insert(type, handler);
}
