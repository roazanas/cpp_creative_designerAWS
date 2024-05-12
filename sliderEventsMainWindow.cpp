#include "mainwindow.h"
#include "ui_mainwindow.h"


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

    this->amountOfLightFlag = false;
    updateInfo();

    QPixmap pixmap = QPixmap::fromImage(temp);
    scene->clear();
    scene->addPixmap(pixmap);

    ui->activityLog->addItem("Noise level - "+QString("%1%").arg(value));
    setTimeToLastItem();
}

void MainWindow::on_saturationSlider_sliderReleased()
{
    int value = ui->saturationSlider->value();
    double transperancy = (static_cast<double>(value) / 100.0);

    QImage temp;

    viewImage = originalImage.copy();

    viewImage = applyLayers();

    this->effects["saturation"] = {&MainWindow::addSaturation, transperancy};

    temp = applyEffects();

    this->amountOfLightFlag = false;
    updateInfo();

    QPixmap pixmap = QPixmap::fromImage(temp);
    scene->clear();
    scene->addPixmap(pixmap);

    ui->activityLog->addItem("Saturation level - "+QString("%1%").arg(value));
    setTimeToLastItem();
}

void MainWindow::on_noiseSlider_valueChanged(int value)
{
    ui->noiseLabel->setText("Noise ("+QString("%1%").arg(value)+")");
}

void MainWindow::on_saturationSlider_valueChanged(int value)
{
    ui->saturationLabel->setText("Saturation ("+QString("%1%").arg(value)+")");
}

