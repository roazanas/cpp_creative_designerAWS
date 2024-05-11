#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_invertButton_clicked()
{
    if (this->effects.contains("invertation"))
    {
        this->invertationFlag = false;
        this->effects.remove("invertation");
    }
    else
    {
        this->invertationFlag = true;
    }
    double transperancy = 1.0;

    QImage temp;

    viewImage = originalImage.copy();

    viewImage = applyLayers();

    if (this->invertationFlag)
    {
        this->effects["invertation"].first = &MainWindow::applyRgbSwap;
        this->effects["invertation"].second = transperancy;
    }

    temp = applyEffects();

    QPixmap pixmap = QPixmap::fromImage(temp);
    scene->clear();
    scene->addPixmap(pixmap);

    ui->activityLog->addItem("RGB swapped");
    setTimeToLastItem();
}

void MainWindow::on_loadButton_clicked()
{
    // даёт юзеру выбрать изображение и возвращает его полный путь
    QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите изображение"),
                                                    "/",
                                                    tr("Изображения (*.png *.jpg *.jpeg)"));
    ui->loadButton->setChecked(false);
    if (fileName.isEmpty())
    {
        return;
    }

    loadImage(fileName);
}
