#ifndef OBJECTTREE_H
#define OBJECTTREE_H

#include <QTreeWidget>

class ObjectTree : public QTreeWidget {
Q_OBJECT
private:
	void _buildTree(QTreeWidgetItem *item, QObject *wgt);

public:
    explicit ObjectTree(QWidget *parent = 0);

	void displayTree(QObject *object);
signals:
	void objectSelected(QObject *object);
	void widgetSelected(QWidget *widget);
private slots:
	void _selectionChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
public slots:

};

#endif // OBJECTTREE_H
