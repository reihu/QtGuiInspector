DEPENDPATH += $$PWD
SOURCES += QtGuiInspector.cpp \
    InspectorItem.cpp \
    MethodViewer.cpp \
    ObjectTree.cpp \
    PropertyEditor.cpp \

HEADERS += QtGuiInspector.h \
    QtGuiInspector_global.h \
    InspectorItem.h \
    MethodViewer.h \
    ObjectTree.h \
    PropertyEditor.h

OTHER_FILES += ../eartunes/etplayer/src/test.qml
DEFINES += USE_QTGUIINSPECTOR
