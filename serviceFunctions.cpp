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
