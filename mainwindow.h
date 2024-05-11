#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QColor>
#include <QImage>
#include <QFileDialog>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include <QToolTip>
#include <QMimeData>
#include <QListWidget>
#include <QDateTime>
#include "info.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadImage(QString fileName);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private slots:
    void on_loadButton_clicked();

    void on_noiseSlider_sliderReleased();

    void on_saturationSlider_sliderReleased();

    void onScaleChanged();

    void on_info_triggered();

    void on_invertButton_clicked();
private:
    Ui::MainWindow *ui;
    Info* info;
    QGraphicsScene* scene;

    QMap<std::string, std::pair<QImage, double>> layers;
    QMap<std::string, double> effects;

    bool invertationFlag;
    QImage noise;
    QImage originalImage;
    QImage viewImage;
    QString currentImagePath = "";

    QString getImageInfo();

    void updateInfo();

    QImage addSaturation(double k);

    QImage noiseGenerating();

    QImage applyLayers();

    QImage applyEffects();

    void setTimeToLastItem();

    QColor mediumColor(QColor colorRGB1, QColor colorRGB2, double k);

    QImage combiningImagesSameSize(const QImage &image1, const QImage &image2, double k = 0.5);
};
#endif // MAINWINDOW_H
