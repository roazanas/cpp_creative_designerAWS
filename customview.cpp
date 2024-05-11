#include "customview.h"

CustomView::CustomView(QWidget *parent) : QGraphicsView(parent) {}

QString CustomView::getScaleInfo() const
{
    return QString("• Масштаб: \n\t%1%").arg(currentScale * 100);
}

void CustomView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
    double scaleFactor = 1.10; // задаёт скорость зума (1.10 - 1.20 лучше всего)
    if (event->angleDelta().y() > 0)
    {
        scale(scaleFactor, scaleFactor);
        currentScale *= scaleFactor;
    }
    else
    {
        scale(1/scaleFactor, 1/scaleFactor);
        currentScale /= scaleFactor;
    }
    emit scaleChanged();
}
