#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include "PropertyDelegate.h"

#include <QMetaProperty>
#include <QStandardItemModel>
#include <QTreeView>

class PropertyEditor : public QTreeView {
Q_OBJECT
private:
	QObject *m_object;
	QStandardItemModel m_model;
	PropertyDelegate m_delegate;
public:
	class ValueItem: public QStandardItem {
	private:
		QObject *m_object;
		QMetaProperty m_metaProperty;
		QVariant m_value;
	public:
		ValueItem(const QVariant &value, QObject *object, QMetaProperty metaProperty);

		QObject* getObject() const {return m_object;}
		QMetaProperty getMetaProperty() const {return m_metaProperty;}
		QVariant getValue() const {return m_value;}

		void setValue(const QVariant &value) {m_value = value;}
	};

    explicit PropertyEditor(QWidget *parent = 0);

signals:

public slots:
	void setObject(QObject *object);
};

#endif // PROPERTYEDITOR_H
