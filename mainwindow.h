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

    void on_noiseSlider_actionTriggered(int action);

    void on_saturationSlider_actionTriggered(int action);

    void onScaleChanged();

    void on_info_triggered();

    void on_invertButton_clicked();

private:
    Ui::MainWindow *ui;
    Info* info;
    QGraphicsScene* scene;

    QMap<std::string, std::pair<QImage, double>> layers;
    QMap<std::string, double> effects;

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


    QColor mediumColor(QColor colorRGB1, QColor colorRGB2, double k)
    {
        if (k == 0)
        {
            return colorRGB1;
        }

        if (k == 1)
        {
            return colorRGB2;
        }

        int red = colorRGB1.red() * (1 - k) + colorRGB2.red() * k;
        int green = colorRGB1.green() * (1 - k) + colorRGB2.green() * k;
        int blue = colorRGB1.blue() * (1 - k) + colorRGB2.blue() * k;
        return QColor::fromRgb(red, green, blue);
    }

    QImage combiningImagesSameSize(const QImage& image1, const QImage& image2, double k = 0.5)
    {
        QImage finallyImage = image1.copy();
        int width = image1.width();
        int height = image1.height();

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (finallyImage.pixelColor(i, j).alpha() != 0)
                finallyImage.setPixelColor(i, j,
                                     mediumColor(finallyImage.pixelColor(i,j) ,
                                                image2.pixelColor(i,j), k)
                                     );
                else
                {
                    finallyImage.setPixelColor(i, j, QColor::fromHsl(0,0,0,0));
                }
            }
        }
        return finallyImage;
    }
};
#endif // MAINWINDOW_H
