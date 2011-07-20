#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QStandardItemModel>
#include <QTreeView>

class PropertyEditor : public QTreeView {
Q_OBJECT
private:
	QObject *m_object;
	QStandardItemModel m_model;
public:
    explicit PropertyEditor(QWidget *parent = 0);

signals:

public slots:
	void setObject(QObject *object);
};

#endif // PROPERTYEDITOR_H
