#include "RectHandler.h"

#include <QLabel>

QWidget* RectHandler::createEditor(PropertyEditor::ValueItem *item) {
	return NULL; // Editing isn't possible atm
}

void RectHandler::setModelData(QWidget *editor, PropertyEditor::ValueItem *item) {
}

QString RectHandler::toString(const QVariant &variant) {
	QString rc;
	if (variant.type() == QVariant::Rect) {
		QRect rect = variant.toRect();
		rc = QString("[(%1, %2) %3 x %4]").arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height());
	}
	else if (variant.type() == QVariant::RectF) {
		QRectF rect = variant.toRectF();
		rc = QString("[(%1, %2) %3 x %4]").arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height());
	}
	else rc = "[not a QRect!]";
	return rc;
}
