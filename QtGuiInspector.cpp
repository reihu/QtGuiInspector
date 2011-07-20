#include "QtGuiInspector.h"
#include <QVBoxLayout>
#include "InspectorItem.h"

QtGuiInspector::QtGuiInspector(QWidget *widget) {
	QHBoxLayout *layout = new QHBoxLayout();
	QVBoxLayout *vbox = new QVBoxLayout();
	m_properties = new PropertyEditor();
	m_style = new QPlainTextEdit();
	m_tree = new ObjectTree(widget);
	m_sigSlotViewer = new SignalSlotViewer();
	m_selectedWidget = 0;

	setWindowTitle(tr("WidgetInspector"));

	vbox->addWidget(m_properties);
	vbox->addWidget(m_style);
	vbox->addWidget(m_sigSlotViewer);

	layout->addWidget(m_tree);
	layout->addItem(vbox);
	setLayout(layout);

	m_tree->setHeaderLabels(QStringList() << tr("Class") << tr("Name"));

	connect(m_tree, SIGNAL(objectSelected(QObject*)), this, SLOT(_objectSelected(QObject*)));
	connect(m_tree, SIGNAL(widgetSelected(QWidget*)), this, SLOT(_widgetSelected(QWidget*)));
	connect(m_style, SIGNAL(textChanged()), this, SLOT(_updateStyle()));

	m_tree->displayTree(widget);
	_widgetSelected(widget);
}

void QtGuiInspector::_objectSelected(QObject *object) {
	m_selectedWidget = 0;
	m_properties->setObject(object);
	m_style->setEnabled(false);
	m_style->clear();
	m_sigSlotViewer->setObject(object);
}

void QtGuiInspector::_updateStyle() {
	if (m_selectedWidget) {
		QString newStyle = m_style->document()->toPlainText();
		if (m_selectedWidget->styleSheet() != newStyle) {
			m_selectedWidget->setStyleSheet(newStyle);
		}
	}
}

void QtGuiInspector::_widgetSelected(QWidget *widget) {
	m_selectedWidget = widget;
	m_style->setEnabled(true);
	m_style->document()->setPlainText(widget->styleSheet());
}
