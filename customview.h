#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>

class CustomView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CustomView(QWidget *parent = nullptr);
    QString getScaleInfo() const;

signals:
    void scaleChanged();
    void mouseClick(QPoint point);

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

    using QGraphicsView::QGraphicsView;
private:
    double currentScale = 1.0;
};

#endif // CUSTOMVIEW_H
