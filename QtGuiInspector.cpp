#include "QtGuiInspector.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "InspectorItem.h"
#include "ui_QtGuiInspector.h"

QtGuiInspector::QtGuiInspector(QWidget *widget) {
	m_selectedWidget = 0;
	m_widget = widget;

	ui = new Ui::QtGuiInspector();
	ui->setupUi(this);

	connect(ui->objectTree, SIGNAL(objectSelected(QObject*)), this, SLOT(_objectSelected(QObject*)));
	connect(ui->objectTree, SIGNAL(widgetSelected(QWidget*)), this, SLOT(_widgetSelected(QWidget*)));
	connect(ui->findWidgetBtn, SIGNAL(pressed()), this, SLOT(_startFindWidget()));
	connect(ui->styleEdit, SIGNAL(textChanged()), this, SLOT(_updateStyle()));

	ui->objectTree->displayTree(widget);
	_widgetSelected(widget);
}

void QtGuiInspector::_objectSelected(QObject *object) {
	m_selectedWidget = 0;
	ui->propertyList->setObject(object);
	ui->styleEdit->setEnabled(false);
	ui->styleEdit->clear();
	ui->methodList->setObject(object);
}

void QtGuiInspector::_startFindWidget() {
	qDebug (":: mousePress");
	ui->findWidgetBtn->installEventFilter(this);
	ui->findWidgetBtn->setCursor(Qt::CrossCursor);
}

void QtGuiInspector::_updateStyle() {
	if (m_selectedWidget) {
		QString newStyle = ui->styleEdit->document()->toPlainText();
		if (m_selectedWidget->styleSheet() != newStyle) {
			m_selectedWidget->setStyleSheet(newStyle);
		}
	}
}

void QtGuiInspector::_widgetSelected(QWidget *widget) {
	m_selectedWidget = widget;
	ui->styleEdit->setEnabled(true);
	ui->styleEdit->document()->setPlainText(widget->styleSheet());
}

bool QtGuiInspector::eventFilter(QObject *object, QEvent *event) {

	if (event->type() == QEvent::MouseButtonRelease) {
		QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
		QWidget *wgt = static_cast<QWidget*>(object);
		QPoint pos = m_widget->mapFromGlobal(wgt->mapToGlobal(mouseEvent->pos()));

		QWidget *child = m_widget->childAt(pos);
		if (child) {
			ui->objectTree->selectObject(child);
		}

		wgt->setCursor(Qt::ArrowCursor);
		object->removeEventFilter(this);
	}

	return false;
}
