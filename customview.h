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
protected:
    virtual void wheelEvent(QWheelEvent *event);
    using QGraphicsView::QGraphicsView;
private:
    double currentScale = 1.0; // переменная только для отображения процентов в тексте
signals:
    void scaleChanged();
};

#endif // CUSTOMVIEW_H
