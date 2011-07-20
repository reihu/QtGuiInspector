#ifndef SIGNALSLOTVIEWER_H
#define SIGNALSLOTVIEWER_H

#include <QMetaMethod>
#include <QTreeWidget>

class SignalSlotViewer: public QTreeWidget {
    Q_OBJECT
public:
	class SSVItem: public QTreeWidgetItem {
	private:
		QMetaMethod m_method;
		QObject *m_object;
	public:
		SSVItem(QObject *object, const QMetaMethod &method);

		QMetaMethod getMethod() const {return m_method;}
		QObject* getObject() const {return m_object;}

		bool isSlot() {return m_method.methodType() == QMetaMethod::Slot;}
	};

    explicit SignalSlotViewer(QWidget *parent = 0);

	void setObject(QObject *object);

	static const char* getMethodTypeName(QMetaMethod::MethodType methodType);

protected:
	void contextMenuEvent(QContextMenuEvent *event);

private slots:
	void _invokeMethod();
};

#endif // SIGNALSLOTVIEWER_H
