#include "noisegenerator.h"
#include "ui_mainwindow.h"


QImage MainWindow::addSaturation(QImage& image, double k)
{
    int width = image.width();
    int height = image.height();
    QImage saturation = image.copy();

    for (int y = 0; y < height; y++)
    {
        uchar* scanLine = saturation.scanLine(y);
        for (int x = 0; x < width; x++)
        {
            QRgb* pixel = reinterpret_cast<QRgb*>(scanLine + x * 4); // 4 байта на пиксель (ARGB32)
            QColor color(*pixel);
            int h, s, l, a;
            color.getHsl(&h, &s, &l, &a);
            s *= k;
            s = qBound(0, s, 255);
            color.setHsl(h, s, l, a);
            *pixel = color.rgba();
        }
    }
    return saturation;
}

QImage MainWindow::noiseGenerating()
{
    int width = originalImage.width();
    int height = originalImage.height();
    QImage noise(width, height, QImage::Format_ARGB32);
    QByteArray noiseData(width * height * 4, 0);

    // Количество потоков (можно экспериментировать с этим значением)
    int numThreads = QThread::idealThreadCount();

    // Создание и запуск потоков
    QList<QSharedPointer<NoiseGenerator>> threads;
    int chunkSize = height / numThreads;
    for (int i = 0; i < numThreads; ++i)
    {
        int startY = i * chunkSize;
        int endY = (i == numThreads - 1) ? height : startY + chunkSize;
        QSharedPointer<NoiseGenerator> thread(new NoiseGenerator(startY, endY, width, noiseData));
        threads.append(thread);
        thread->start();
    }

    // Ожидание завершения всех потоков
    for (auto thread : threads)
    {
        thread->wait();
    }

    // Заполнение изображения
    for (int y = 0; y < height; y++)
    {
        memcpy(noise.scanLine(y), noiseData.constData() + y * width * 4, width * 4);
    }

    return noise;
}


// QImage MainWindow::noiseGenerating() {
//     int width = originalImage.width();
//     int height = originalImage.height();
//     QImage noise(width, height, QImage::Format_ARGB32);

//     // Генерация массива шума
//     QByteArray noiseData(width * height * 4, 0);
//     QRandomGenerator generator;
//     for (int i = 0; i < noiseData.size(); i += 4) {
//         uint rgb = generator.bounded(256);
//         noiseData[i] = noiseData[i+1] = noiseData[i+2] = rgb;
//         noiseData[i+3] = 255;
//     }

//     // Заполнение изображения
//     for (int y = 0; y < height; y++) {
//         memcpy(noise.scanLine(y), noiseData.constData() + y * width * 4, width * 4);
//     }

//     return noise;
// }

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

    const QRgb* data1 = reinterpret_cast<const QRgb*>(image1.constBits());
    const QRgb* data2 = reinterpret_cast<const QRgb*>(image2.constBits());
    for (int i = 0; i < width * height; i++)
    {
        QRgb* pixel = reinterpret_cast<QRgb*>(finallyImage.bits() + i * 4);
        QRgb pixel1 = data1[i];
        QRgb pixel2 = data2[i];
        if (qAlpha(pixel1) != 0)
        {
            *pixel = mediumColor(QColor::fromRgba(pixel1), QColor::fromRgba(pixel2), k).rgba();
        }
        else
        {
            *pixel = QColor(0, 0, 0, 0).rgba();
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

QImage MainWindow::inversionImage(QImage& image, double /*unused*/)
{
    int width = image.width();
    int height = image.height();
    QImage invertImage = image.copy();

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int r = invertImage.pixelColor(i,j).red();
            int g = invertImage.pixelColor(i,j).green();
            int b = invertImage.pixelColor(i,j).blue();
            invertImage.setPixelColor(i,j,QColor(255-r,255-g,255-b));
        }
    }
    return invertImage;
}

QImage MainWindow::floodFill(QImage& image, QPoint point, QColor oldColor, QColor newColor)
{
    int width = image.width();
    int height = image.height();
    QImage filledImage = image.copy();
    int x = point.x();
    int y = point.y();

    if (x < 0 || x >= width || y < 0 || y >= height || filledImage.pixelColor(x, y) != oldColor)
    {
        return filledImage;
    }

    std::queue<QPoint> q;
    q.push(point);

    while (!q.empty())
    {
        QPoint p = q.front();
        q.pop();

        filledImage.setPixelColor(p, newColor);

        if (p.x() > 0 && filledImage.pixelColor(p.x() - 1, p.y()) == oldColor)
        {
            q.push(QPoint(p.x() - 1, p.y()));
        }
        if (p.x() < width - 1 && filledImage.pixelColor(p.x() + 1, p.y()) == oldColor)
        {
            q.push(QPoint(p.x() + 1, p.y()));
        }
        if (p.y() > 0 && filledImage.pixelColor(p.x(), p.y() - 1) == oldColor)
        {
            q.push(QPoint(p.x(), p.y() - 1));
        }
        if (p.y() < height - 1 && filledImage.pixelColor(p.x(), p.y() + 1) == oldColor)
        {
            q.push(QPoint(p.x(), p.y() + 1));
        }
    }

    return filledImage;
}

QImage MainWindow::applyFloodFill(QImage &image, double /*unused*/)
{
    return floodFill(image, pointToFill, image.pixelColor(pointToFill), QColor(255, 255, 255, 0));
}

void MainWindow::amountOfLight()
{
    QImage image = viewImage.copy();
    int countOverLightPixels = 0;
    int countEXTRAOverLightPixels = 0;
    int width = image.width();
    int height = image.height();
    int countPixels = (width * height);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor color = image.pixelColor(i, j);

            int deltaR = 255 - color.red();
            int deltaG = 255 - color.green();
            int deltaB = 255 - color.blue();

            if ((deltaR + deltaG + deltaB) < 90)
            {
                countOverLightPixels++;
            }
            if ((deltaR + deltaG + deltaB) < 20)
            {
                countEXTRAOverLightPixels++;
            }
        }
    }
    double k = (static_cast<double>(countOverLightPixels) / static_cast<double>(countPixels));
    double lpixK = (static_cast<double>(countEXTRAOverLightPixels) / static_cast<double>(countOverLightPixels));

    if ((k * 100 > 7) || (lpixK >= 0.4))
    {
        this->overexposureStatus = QString("!!!There is an overexposure in the image!!!");
    }
    else
    {
        this->overexposureStatus = QString("...There are no overexposures in the image...");
    }
}
