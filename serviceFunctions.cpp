#include "noisegenerator.h"
#include "ui_mainwindow.h"

// эта заполняла прозрачные пиксели
// QImage MainWindow::addSaturation(QImage& image, double k)
// {
//     int width = image.width();
//     int height = image.height();
//     QImage saturation = image.copy();

//     for (int y = 0; y < height; y++)
//     {
//         uchar* scanLine = saturation.scanLine(y);
//         for (int x = 0; x < width; x++)
//         {
//             QRgb* pixel = reinterpret_cast<QRgb*>(scanLine + x * 4); // 4 байта на пиксель (ARGB32)
//             QColor color(*pixel);
//             int h, s, l, a;
//             color.getHsl(&h, &s, &l, &a);
//             s *= k;
//             s = qBound(0, s, 255);
//             color.setHsl(h, s, l, a);
//             *pixel = color.rgba();
//         }
//     }
//     return saturation;
// }

QImage MainWindow::addSaturation(QImage& image, double k)
{
    int width = this->originalImage.width();
    int height = this->originalImage.height();
    QImage saturation = image.copy();
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
            if (invertImage.pixelColor(i,j).alpha() != 0)
            {
                int r = invertImage.pixelColor(i,j).red();
                int g = invertImage.pixelColor(i,j).green();
                int b = invertImage.pixelColor(i,j).blue();
                invertImage.setPixelColor(i,j,QColor(255-r,255-g,255-b));
            }
        }
    }
    return invertImage;
}

QImage MainWindow::floodFill(QImage& image, QPoint point, QColor oldColor, QColor newColor, int threshold)
{
    int width = image.width();
    int height = image.height();

    if (point.x() < 0 || point.x() >= width || point.y() < 0 || point.y() >= height)
    {
        return image;
    }

    if (!colorDifference(image.pixelColor(point), oldColor, threshold))
    {
        return image;
    }

    QImage filledImage = image;
    std::stack<QPoint> points;
    points.push(point);


    struct QPointHash
    {
        std::size_t operator()(const QPoint& p) const
        {
            return std::hash<int>()(p.x()) ^ std::hash<int>()(p.y());
        }
    };

    // использование std::set для отслеживания посещенных пикселей
    std::unordered_set<QPoint, QPointHash> visitedPixels;

    while (!points.empty())
    {
        QPoint p = points.top();
        points.pop();

        // пропуск уже посещенных пикселей
        if (visitedPixels.find(p) != visitedPixels.end())
        {
            continue;
        }
        visitedPixels.insert(p);

        filledImage.setPixelColor(p, newColor);

        // добавление соседних пикселей в стек
        if (p.x() > 0 && colorDifference(image.pixelColor(p), oldColor, threshold))
        {
            points.push(QPoint(p.x() - 1, p.y()));
        }
        if (p.x() < width - 1 && colorDifference(image.pixelColor(p), oldColor, threshold))
        {
            points.push(QPoint(p.x() + 1, p.y()));
        }
        if (p.y() > 0 && colorDifference(image.pixelColor(p), oldColor, threshold))
        {
            points.push(QPoint(p.x(), p.y() - 1));
        }
        if (p.y() < height - 1 && colorDifference(image.pixelColor(p), oldColor, threshold))
        {
            points.push(QPoint(p.x(), p.y() + 1));
        }
    }

    return filledImage;
}

bool MainWindow::colorDifference(QColor color1, QColor color2, int threshold) {
    bool rDiff = abs(color1.red() - color2.red()) <= threshold;
    bool gDiff = abs(color1.green() - color2.green()) <= threshold;
    bool bDiff = abs(color1.blue() - color2.blue()) <= threshold;
    return rDiff && gDiff && bDiff;
}

QImage MainWindow::applyFloodFill(QImage &image, double /*unused*/)
{
    return floodFill(image, pointToFill, image.pixelColor(pointToFill), QColor(255, 255, 255, 0), currentThreshold);
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

            if (color.alpha() != 0)
            {
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
    }
    if (countOverLightPixels == 0)
    {
        this->overexposureStatus = QString("...There are no overexposures in the image...");
        return;
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
