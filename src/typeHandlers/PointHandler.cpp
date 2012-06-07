#include "PointHandler.h"

#include <QLabel>

QWidget* PointHandler::createEditor(PropertyEditor::ValueItem *item) {
	return NULL; // Editing isn't possible atm
}

void PointHandler::setModelData(QWidget *editor, PropertyEditor::ValueItem *item) {
}

QString PointHandler::toString(const QVariant &variant) {
	QString rc;
	if (variant.type() == QVariant::Point) {
		QPoint point = variant.toPoint();
		rc = QString("%1 x %2").arg(point.x()).arg(point.y());
	}
	else if (variant.type() == QVariant::PointF) {
		QPointF point = variant.toPointF();
		rc = QString("(%1, %2)").arg(point.x()).arg(point.y());
	}
	else rc = "[not a QPoint!]";
	return rc;
}
