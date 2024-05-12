#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_loadButton_clicked()
{
    // даёт юзеру выбрать изображение и возвращает его полный путь
    QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите изображение"),
                                                    QString(),
                                                    tr("Изображения (*.png *.jpg *.jpeg)"));
    ui->loadButton->setChecked(false);
    if (!fileName.isEmpty())
    {
        loadImage(fileName);
    }
}


void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить изображение"),
                                                    QString(),
                                                    tr("Изображения (*.png *.jpg *.jpeg)"));
    ui->saveButton->setChecked(false);
    if (!fileName.isEmpty())
    {
        viewImage.save(fileName);
    }
}


void MainWindow::on_swapRGBButton_clicked()
{
    if (this->effects.contains("swapRGB"))
    {
        this->swapRGBFlag = false;
        this->effects.remove("swapRGB");
    }
    else
    {
        this->swapRGBFlag = true;
    }
    double transperancy = 1.0;

    QImage temp;

    viewImage = originalImage.copy();

    viewImage = applyLayers();

    if (this->swapRGBFlag)
    {
        this->effects["swapRGB"].first = &MainWindow::applyRgbSwap;
        this->effects["swapRGB"].second = transperancy;
    }

    temp = applyEffects();

    this->amountOfLightFlag = false;
    updateInfo();

    QPixmap pixmap = QPixmap::fromImage(temp);
    scene->clear();
    scene->addPixmap(pixmap);

    ui->activityLog->addItem("RGB swapped");
    setTimeToLastItem();
}

void MainWindow::on_inversionButton_clicked()
{
    if (this->effects.contains("inversion"))
    {
        this->inversionFlag = false;
        this->effects.remove("inversion");
    }
    else
    {
        this->inversionFlag = true;
    }
    double transperancy = 1.0;

    QImage temp;

    viewImage = originalImage.copy();

    viewImage = applyLayers();

    if (this->inversionFlag)
    {
        this->effects["inversion"].first = &MainWindow::inversionImage;
        this->effects["inversion"].second = transperancy;
    }

    temp = applyEffects();

    this->amountOfLightFlag = false;
    updateInfo();

    QPixmap pixmap = QPixmap::fromImage(temp);
    scene->clear();
    scene->addPixmap(pixmap);

    ui->activityLog->addItem("Inversion image");
    setTimeToLastItem();
}

void MainWindow::on_removeBGButton_clicked()
{
    if (ui->removeBGButton->isChecked()) {
        QMessageBox::information(
            this,
            tr("Designer AWS"),
            tr("Click on the desired pixel to delete same-colored area") );
        ui->image->setCursor(Qt::CursorShape::CrossCursor); // Более подходящий курсор
    } else {
        ui->image->setCursor(Qt::CursorShape::ArrowCursor); // Возвращение стандартного курсора
    }
}
