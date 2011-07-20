#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QTreeWidget>

class PropertyEditor : public QTreeWidget {
Q_OBJECT
private:
	QObject *m_object;
public:
    explicit PropertyEditor(QWidget *parent = 0);

signals:

public slots:
	void setObject(QObject *object);
};

#endif // PROPERTYEDITOR_H
