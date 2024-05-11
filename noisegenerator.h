#include "mainwindow.h"
#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

class NoiseGenerator : public QThread
{
    Q_OBJECT
public:
    NoiseGenerator(int startY, int endY, int width, QByteArray& noiseData)
        : startY(startY), endY(endY), width(width), noiseData(noiseData) {}

    void run();

private:
    int startY, endY, width;
    QByteArray& noiseData;
};

#endif // NOISEGENERATOR_H
