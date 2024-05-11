#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage MainWindow::applyLayers()
{
    for (auto it = this->layers.begin(); it != this->layers.end(); it++)
    {
        QImage layer = it.value().first;
        double transparency = it.value().second;
        this->viewImage = combiningImagesSameSize(viewImage, layer, transparency);
    }
    return this->viewImage;
}

QImage MainWindow::applyEffects()
{
    for (auto it = this->effects.begin(); it != this->effects.end(); it++)
    {
        std::string effect = it.key();
        EffectFunction func = it.value().first;
        double transparency = it.value().second;
        this->viewImage = (this->*func)(this->viewImage, transparency);
    }
    return this->viewImage;
}
