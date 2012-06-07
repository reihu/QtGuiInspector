DEPENDPATH += $$PWD
SOURCES += src/QtGuiInspector.cpp \
	src/HandlerRegistry.cpp \
	src/InspectorItem.cpp \
    src/MethodViewer.cpp \
    src/ObjectTree.cpp \
	src/PropertyEditor.cpp \
	src/PropertyDelegate.cpp \
    src/typeHandlers/PropertyTypeHandler.cpp \
    src/typeHandlers/EnumHandler.cpp \
    src/typeHandlers/StringHandler.cpp \
    src/typeHandlers/BoolHandler.cpp \
    src/typeHandlers/IntHandler.cpp \
	src/typeHandlers/SizePolicyHandler.cpp \
	src/typeHandlers/SizeHandler.cpp

HEADERS += src/QtGuiInspector.h \
	src/QtGuiInspector_global.h \
	src/HandlerRegistry.h \
	src/InspectorItem.h \
    src/MethodViewer.h \
    src/ObjectTree.h \
	src/PropertyEditor.h \
	src/PropertyDelegate.h \
    src/typeHandlers/PropertyTypeHandler.h \
    src/typeHandlers/EnumHandler.h \
    src/typeHandlers/StringHandler.h \
    src/typeHandlers/BoolHandler.h \
    src/typeHandlers/IntHandler.h \
	src/typeHandlers/SizePolicyHandler.h \
	src/typeHandlers/SizeHandler.h

OTHER_FILES += ../eartunes/etplayer/src/test.qml
DEFINES += USE_QTGUIINSPECTOR

FORMS += \
    src/QtGuiInspector.ui
