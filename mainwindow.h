#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QColor>
#include <QImage>
#include <QFileDialog>
// #include <iostream>

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

private slots:
    void on_loadButton_clicked();
    void on_noiseSlider_move(int value);
    void on_saturationSlider_move(int value);

private:
    Ui::MainWindow *ui;


    QMap<std::string, std::pair<QImage, float>> layers;
    QImage noise;
    QImage originalImage;
    QImage viewImage;
    QString currentImagePath = "";
    double scaleFactor;

    QPixmap rescaleImageByHeight(const QImage originalImage, int newWidth);

    void wheelEvent(QWheelEvent *event);

    QString getImageInfo();

    void updateInfo();

    QImage addSaturation(float k);

    QImage noiseGenerating();

    QImage applyEffects();


    QColor mediumColor(QColor colorRGB1, QColor colorRGB2, float k)
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

    QImage combiningImagesSameSize(QImage image1, QImage image2, float k = 0.5)
    {
        QImage finallyImage = image1;
        int width = image1.width();
        int height = image1.height();

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                finallyImage.setPixelColor(i, j,
                                     mediumColor(finallyImage.pixelColor(i,j) ,
                                                image2.pixelColor(i,j), k)
                                     );
            }
        }
        return finallyImage;
    }
};
#endif // MAINWINDOW_H
