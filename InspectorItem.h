#ifndef INSPECTORITEM_H
#define INSPECTORITEM_H

#include <QTreeWidgetItem>
#include <QWidget>

class InspectorItem : public QObject, public QTreeWidgetItem {
	Q_OBJECT
private:
	QObject *m_object;

public:
	explicit InspectorItem(QObject *object = 0);

	QObject *getObject();
	QWidget *getWidget();
signals:

private slots:
	void _objectDestroyed();
};

#endif // INSPECTORITEM_H
