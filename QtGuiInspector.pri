DEPENDPATH += $$PWD
SOURCES += QtGuiInspector.cpp \
    InspectorItem.cpp \
    ObjectTree.cpp \
    PropertyEditor.cpp \
    SignalSlotViewer.cpp

HEADERS += QtGuiInspector.h \
    QtGuiInspector_global.h \
    InspectorItem.h \
    ObjectTree.h \
    PropertyEditor.h \
    SignalSlotViewer.h

OTHER_FILES += ../eartunes/etplayer/src/test.qml
DEFINES += USE_QTGUIINSPECTOR
