#ifndef QT_GUI_INSPECTOR_H
#define QT_GUI_INSPECTOR_H

#include "QtGuiInspector_global.h"
#include <QDialog>
#include <QPlainTextEdit>
#include "ObjectTree.h"
#include "PropertyEditor.h"
#include "MethodViewer.h"

class QTGUIINSPECTORSHARED_EXPORT QtGuiInspector: public QDialog {
	Q_OBJECT
private:

	/// inspected widget
	QWidget *m_widget;
	QWidget *m_selectedWidget;
	ObjectTree *m_tree;
	PropertyEditor *m_properties;
	MethodViewer *m_methodViewer;
	QPlainTextEdit *m_style;
	QPushButton *m_findWidgetBtn;

protected:
	bool eventFilter(QObject *object, QEvent *event);

public:
	/**
	 * \brief Creates a QtGuiInspector dialog
	 * \param widget Widget to inspect
	 */
	QtGuiInspector(QWidget *widget);

private slots:
	void _objectSelected(QObject *object);
	void _startFindWidget();
	void _updateStyle();
	void _widgetSelected(QWidget *widget);
};

#endif // QT_GUI_INSPECTOR_H
