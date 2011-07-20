#ifndef INSPECTORITEM_H
#define INSPECTORITEM_H

#include <QTreeWidgetItem>
#include <QWidget>

class InspectorItem : public QTreeWidgetItem {
private:
	QObject *m_object;

public:
	explicit InspectorItem(QObject *object = 0);

	QObject *getObject();
	QWidget *getWidget();
signals:

public slots:

};

#endif // INSPECTORITEM_H
