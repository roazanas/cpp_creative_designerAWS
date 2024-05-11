#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_noiseSlider_actionTriggered(int action)
{
    switch (action)
    {
    case 3: case 4:
        on_noiseSlider_sliderReleased();
    }
}

void MainWindow::on_saturationSlider_actionTriggered(int action)
{
    switch (action)
    {
    case 3: case 4:
        on_saturationSlider_sliderReleased();
    }
}

void MainWindow::on_noiseSlider_sliderReleased()
{
    int value = ui->noiseSlider->value();
    double transperancy = static_cast<double>(value) / 100.0;

    if (this->noise.isNull())
    {
        this->noise = noiseGenerating();
    }

    this->layers["noise"] = {this->noise, transperancy};

    // затирает картинку на изначальную чтобы эффекты не стакались
    viewImage = originalImage.copy();

    // сначала применяет все существующие эффекты, потом уже применяет и сохраняет этот
    viewImage = applyLayers();

    QImage temp = combiningImagesSameSize(viewImage, noise, transperancy);

    temp = applyEffects();

    QPixmap pixmap = QPixmap::fromImage(temp);
    scene->clear();
    scene->addPixmap(pixmap);

    ui->noiseSlider->setToolTip(QString("%1%").arg(value));

    ui->activityLog->addItem("Noise level - "+QString("%1%").arg(value));
}

void MainWindow::on_saturationSlider_sliderReleased()
{
    int value = ui->saturationSlider->value();
    double transperancy = (static_cast<double>(value) / 100.0);

    QImage temp;

    viewImage = originalImage.copy();

    viewImage = applyLayers();

    this->effects["saturation"] = {transperancy};

    temp = applyEffects();

    QPixmap pixmap = QPixmap::fromImage(temp);
    scene->clear();
    scene->addPixmap(pixmap);

    ui->saturationSlider->setToolTip(QString("%1%").arg(value));

    ui->activityLog->addItem("Saturation level - "+QString("%1%").arg(value));
}
