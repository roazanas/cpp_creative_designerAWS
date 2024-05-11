#include "noisegenerator.h"
#include "ui_mainwindow.h"


QImage MainWindow::addSaturation(QImage& image, double k) {
    int width = image.width();
    int height = image.height();
    QImage saturation = image.copy();

    for (int y = 0; y < height; y++) {
        uchar* scanLine = saturation.scanLine(y);
        for (int x = 0; x < width; x++) {
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

QImage MainWindow::noiseGenerating() {
    int width = originalImage.width();
    int height = originalImage.height();
    QImage noise(width, height, QImage::Format_ARGB32);
    QByteArray noiseData(width * height * 4, 0);

    // Количество потоков (можно экспериментировать с этим значением)
    int numThreads = QThread::idealThreadCount();

    // Создание и запуск потоков
    QList<NoiseGenerator*> threads;
    int chunkSize = height / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int startY = i * chunkSize;
        int endY = (i == numThreads - 1) ? height : startY + chunkSize;
        NoiseGenerator* thread = new NoiseGenerator(startY, endY, width, noiseData);
        threads.append(thread);
        thread->start();
    }

    // Ожидание завершения всех потоков
    for (auto thread : threads) {
        thread->wait();
        delete thread;
    }

    // Заполнение изображения
    for (int y = 0; y < height; y++) {
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

QImage MainWindow::combiningImagesSameSize(const QImage& image1, const QImage& image2, double k) {
    QImage finallyImage = image1.copy();
    int width = image1.width();
    int height = image1.height();

    const QRgb* data1 = reinterpret_cast<const QRgb*>(image1.constBits());
    const QRgb* data2 = reinterpret_cast<const QRgb*>(image2.constBits());
    for (int i = 0; i < width * height; i++) {
        QRgb* pixel = reinterpret_cast<QRgb*>(finallyImage.bits() + i * 4);
        QRgb pixel1 = data1[i];
        QRgb pixel2 = data2[i];
        if (qAlpha(pixel1) != 0) {
            *pixel = mediumColor(QColor::fromRgba(pixel1), QColor::fromRgba(pixel2), k).rgba();
        } else {
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
