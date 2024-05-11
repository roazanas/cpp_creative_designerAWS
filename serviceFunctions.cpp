#include "mainwindow.h"
#include "ui_mainwindow.h"


QImage MainWindow::addSaturation(double k)
{
    int width = this->originalImage.width();
    int height = this->originalImage.height();
    QImage saturation = this->viewImage;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor pixel = saturation.pixelColor(i, j);
            int h, s, l, a;
            pixel.getHsl(&h, &s, &l, &a);
            s *= k;
            if (s < 0)
                s = 0;
            if (s > 255)
                s = 255;
            pixel.setHsl(h, s, l, a);
            saturation.setPixel(i, j, pixel.rgba());
        }
    }
    return saturation;
}

QImage MainWindow::noiseGenerating()
{
    int width = this->originalImage.width();
    int height = this->originalImage.height();
    QImage noise(width, height, QImage::Format_ARGB32);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int RBG = QRandomGenerator::global()->bounded(256);
            noise.setPixelColor(i, j, QColor::fromRgb(RBG, RBG, RBG));
        }
    }

    return noise;
}

QColor MainWindow::mediumColor(QColor colorRGB1, QColor colorRGB2, double k)
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

QImage MainWindow::combiningImagesSameSize(const QImage& image1, const QImage& image2, double k)
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

void MainWindow::setTimeToLastItem()
{
    static int counter = 0;
    QString currentDateTime = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    ui->activityLog->item(counter)->setToolTip(currentDateTime);
    counter++;
}
