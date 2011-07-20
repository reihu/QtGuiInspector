#ifndef QT_GUI_INSPECTOR_H
#define QT_GUI_INSPECTOR_H

#include "QtGuiInspector_global.h"

#include "ui_QtGuiInspector.h"

class QTGUIINSPECTORSHARED_EXPORT QtGuiInspector: public QMainWindow {
	Q_OBJECT
private:
	Ui::QtGuiInspector *ui;

	/// inspected widget
	QWidget *m_widget;
	QWidget *m_selectedWidget;

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
