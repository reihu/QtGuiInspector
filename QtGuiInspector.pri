DEPENDPATH += $$PWD
SOURCES += src/QtGuiInspector.cpp \
    src/InspectorItem.cpp \
    src/MethodViewer.cpp \
    src/ObjectTree.cpp \
	src/PropertyEditor.cpp \
	src/PropertyDelegate.cpp \
    src/typeHandlers/PropertyTypeHandler.cpp \
    src/typeHandlers/EnumHandler.cpp

HEADERS += src/QtGuiInspector.h \
    src/QtGuiInspector_global.h \
	src/InspectorItem.h \
    src/MethodViewer.h \
    src/ObjectTree.h \
	src/PropertyEditor.h \
	src/PropertyDelegate.h \
    src/typeHandlers/PropertyTypeHandler.h \
    src/typeHandlers/EnumHandler.h

OTHER_FILES += ../eartunes/etplayer/src/test.qml
DEFINES += USE_QTGUIINSPECTOR

FORMS += \
    src/QtGuiInspector.ui
