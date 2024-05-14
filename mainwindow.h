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
#include <QThread>
#include <stack>
#include <unordered_set>
#include <cstdio>
#include <QMessageBox>
#include <QProgressDialog>
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
    void manyLoadImages(QStringList fileNames);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private slots:
    void on_loadButton_clicked();

    void on_noiseSlider_sliderReleased();

    void on_saturationSlider_sliderReleased();

    void on_thresholdSlider_sliderReleased();

    void onScaleChanged();

    void on_info_triggered();

    void on_swapRGBButton_clicked();

    void on_noiseSlider_valueChanged(int value);

    void on_saturationSlider_valueChanged(int value);

    void on_thresholdSlider_valueChanged(int value);

    void on_inversionButton_clicked();

    void on_saveButton_clicked();

    void onMouseClick(QPoint point);

    void on_removeBGButton_clicked();

    void on_manyLoadButton_clicked();
private:
    Ui::MainWindow *ui;
    Info* info;
    QGraphicsScene* scene;

    QPoint pointToFill;
    int currentThreshold = 30;


    // Определение типа указателя на функцию для эффектов
    using EffectFunction = QImage (MainWindow::*)(QImage &, double);

    QMap<std::string, std::pair<QImage, double>> layers;
    QMap<std::string, std::pair<EffectFunction, double>> effects;

    bool swapRGBFlag;
    bool inversionFlag;
    bool amountOfLightFlag = false;
    QString overexposureStatus;

    QImage noise;
    QImage originalImage;
    QImage viewImage;
    QString currentImagePath = "";

    QString getImageInfo();

    void updateInfo();

    QImage addSaturation(QImage &image, double k);

    QImage noiseGenerating();

    QImage applyLayers();

    QImage applyEffects();

    void setTimeToLastItem();

    void amountOfLight();

    QColor mediumColor(QColor colorRGB1, QColor colorRGB2, double k);

    QColor mediumColor2(QColor colorRGB1, QColor colorRGB2);

    QImage combiningImagesSameSize(const QImage &image1, const QImage &image2, double k = 0.5);

    QImage applyRgbSwap(QImage& image, double /*unused*/) {return image.rgbSwapped();}

    QImage inversionImage(QImage& image, double /*unused*/);

    QImage floodFill(QImage& image, QPoint point, QColor oldColor, QColor newColor, int threshold);

    bool colorDifference(QColor color1, QColor color2, int threshold);

    QImage applyFloodFill(QImage &image, double);
};
#endif // MAINWINDOW_H
