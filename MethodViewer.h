#ifndef METHODVIEWER_H
#define METHODVIEWER_H

#include <QMetaMethod>
#include <QTimer>
#include <QTreeWidget>

class MethodViewer: public QTreeWidget {
    Q_OBJECT
private:
	QTimer m_invokeTimer;
	QMetaMethod m_invokedMethod;
	QObject *m_invokedObject;

public:
	class Item: public QTreeWidgetItem {
	private:
		QMetaMethod m_method;
		QObject *m_object;

	public:
		Item(QObject *object, const QMetaMethod &method);

		QMetaMethod getMethod() const {return m_method;}
		QObject* getObject() const {return m_object;}

		bool isSignal() {return m_method.methodType() == QMetaMethod::Signal;}
		bool isSlot() {return m_method.methodType() == QMetaMethod::Slot;}
	};

	explicit MethodViewer(QWidget *parent = 0);

	void setObject(QObject *object);

	static const char* getMethodTypeName(QMetaMethod::MethodType methodType);

protected:
	void contextMenuEvent(QContextMenuEvent *event);

private slots:
	void _invokeMethod();
	void _invokeMethodEvery();
	void _invokeTimerTick();
};

#endif // METHODVIEWER_H
