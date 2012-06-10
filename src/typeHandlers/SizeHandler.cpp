#include "SizeHandler.h"

#include <QLabel>

QWidget* SizeHandler::createEditor(PropertyEditor::ValueItem *item) {
	Q_UNUSED(item);
	return NULL; // Editing isn't possible atm
}

void SizeHandler::setModelData(QWidget *editor, PropertyEditor::ValueItem *item) {
	Q_UNUSED(editor);
	Q_UNUSED(item);
}

QString SizeHandler::toString(const QVariant &variant) {
	QString rc;
	if (variant.type() == QVariant::Size) {
		QSize size = variant.toSize();
		rc = QString("%1 x %2").arg(size.width()).arg(size.height());
	}
	else if (variant.type() == QVariant::SizeF) {
		QSizeF size = variant.toSizeF();
		rc = QString("%1 x %2").arg(size.width()).arg(size.height());
	}
	else rc = "[not a QSize!]";
	return rc;
}
