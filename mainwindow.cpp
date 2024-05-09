#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->noiseSlider, &QSlider::valueChanged, this, &MainWindow::on_noiseSlider_move);
    connect(ui->saturationSlider, &QSlider::valueChanged, this, &MainWindow::on_saturationSlider_move);
}

QPixmap MainWindow::rescaleImageByHeight(const QImage originalImage, int newHeight)
{
    // коэф. который и изменяет размер
    double k = static_cast<double>(originalImage.height()) / originalImage.width();
    int newWidth = static_cast<int>(newHeight / k);

    QPixmap newPixmap = QPixmap::fromImage(originalImage).scaled(newWidth, newHeight);
    return newPixmap;
}

void MainWindow::on_loadButton_clicked()
{
    // даёт юзеру выбрать картинку и возвращает её полный путь
    QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите картинку"),
                                                    "/",
                                                    tr("Картинки (*.png *.jpg *.jpeg)"));
    ui->loadButton->setChecked(false);
    if (fileName.isEmpty())
    {
        return;
    }
    currentImagePath = fileName;
    originalImage.load(fileName);
    originalImage = originalImage.convertToFormat(QImage::Format_ARGB32);

    this->viewImage = originalImage;
    this->layers.clear();
    this->noise = QImage();

    // корипуем основную картинку
    // this->viewImage = QImage(originalImage)

    double a = ui->centralwidget->height();
    double b = originalImage.height();

    scaleFactor = a / b; // сброс коэф. масштабирования
    // новая пиксель-мапа исходной картинки с высотой окна программы
    QPixmap scaledPixmap = rescaleImageByHeight(viewImage,
                                                 ui->centralwidget->height());
    ui->image->setPixmap(scaledPixmap);
    ui->image->setAlignment(Qt::AlignCenter);


    // отображаем информацию о картинке
    updateInfo();
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if (currentImagePath.isEmpty())
    {
        return;
    }
    // определение направления прокрутки
    int delta = event->angleDelta().y();

    // изменение scaleFactor
    if (delta > 0) {
        scaleFactor *= 1.05 ; // Увеличить
    } else if (delta < 0) {
        scaleFactor /= 1.05; // Уменьшить
    }

    // применение масштабирования
    viewImage = applyEffects();
    QPixmap scaledPixmap = rescaleImageByHeight(viewImage,
                                                 originalImage.height() * scaleFactor);
    viewImage = originalImage;
    // обновление QLabel
    ui->image->setPixmap(scaledPixmap);

    updateInfo();
}

QImage MainWindow::applyEffects()
{
    for (auto it = this->layers.begin(); it != this->layers.end(); it++)
    {
        QImage layer = it.value().first;
        float transparency = it.value().second;
        this->viewImage = combiningImagesSameSize(viewImage, layer, transparency);
    }
    return this->viewImage;
}

void MainWindow::on_noiseSlider_move(int value)
{
    //if (this->layers.contains("noise"))
    //{
        this->layers.remove("noise");
    //}

    if (this->noise.isNull())
    {
        this->noise = noiseGenerating();
    }

    float fvalue = static_cast<float>(value) / 100.0;

    // затирает картинку на изначальную чтобы эффекты не стакались
    viewImage = originalImage;

    // сначала применяет все существующие эффекты, потом уже применяет и сохраняет этот
    viewImage = applyEffects();

    QImage temp = combiningImagesSameSize(viewImage, noise, fvalue);

    this->layers["noise"] = {this->noise, fvalue};

    QPixmap scaledPixmap = rescaleImageByHeight(temp,
                                                originalImage.height() * scaleFactor);
    ui->image->setPixmap(scaledPixmap);
}

void MainWindow::on_saturationSlider_move(int value)
{
    if (this->layers.contains("saturation"))
    {
        this->layers.remove("saturation");
    }

    float fvalue = (static_cast<double>(value) / 100.0);

    viewImage = originalImage;

    viewImage = applyEffects();

    // 4 - это значит что можно сделать в 4 раза менее насыщенно либо в 4 раза более насыщенно
    QImage temp = combiningImagesSameSize(viewImage, addSaturation(4), fvalue);

    this->layers["saturation"] = {addSaturation(4), fvalue};

    viewImage = applyEffects();

    QPixmap scaledPixmap = rescaleImageByHeight(temp,
                                                originalImage.height() * scaleFactor);
    ui->image->setPixmap(scaledPixmap);
}

QImage MainWindow::addSaturation(float k)
{
    int width = this->originalImage.width();
    int height = this->originalImage.height();
    QImage saturation = this->viewImage;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor color = saturation.pixelColor(i, j);
            int h, s, l;
            color.getHsl(&h, &s, &l);
            s *= k;
            if (s < 0)
                s = 0;
            if (s > 255)
                s = 255;
            color.setHsl(h, s, l);
            saturation.setPixelColor(i, j, color);
        }
    }
    return saturation;
}

QString MainWindow::getImageInfo()
{
    QString result;
    QStringList filePathArray = currentImagePath.split("/");
    QString sizeString = QString("(%1 x %2)").arg(originalImage.width()).arg(originalImage.height());
    result += "• Имя файла: \n\t" + filePathArray.last() + "\n\n";
    result += "• Размеры изображения: \n\t" + sizeString + "\n\n";
    result += "• Коэф. масштабирования: \n\t" + std::to_string(scaleFactor) + "\n\n";
    return result;
}

void MainWindow::updateInfo()
{
    ui->infoPlain->setPlainText(getImageInfo());
}

QImage MainWindow::noiseGenerating()
{
    int width = this->originalImage.width();
    int height = this->originalImage.height();
    QImage noise(width, height, QImage::Format_RGB32);

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

MainWindow::~MainWindow()
{
    delete ui;
}

