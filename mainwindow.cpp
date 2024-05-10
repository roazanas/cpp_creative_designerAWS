#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    connect(ui->image, &CustomView::scaleChanged, this, &MainWindow::onScaleChanged);
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

    // радикальные методы очистки, т.к. scene.clear() работает не полностью корректно
    delete scene;
    scene = new QGraphicsScene(this);
    ui->image->setScene(scene);

    currentImagePath = fileName;
    originalImage.load(fileName);
    originalImage = originalImage.convertToFormat(QImage::Format_ARGB32);

    this->viewImage = originalImage;
    this->layers.clear();
    this->noise = QImage();

    QPixmap pixmap = QPixmap::fromImage(viewImage);
    QGraphicsPixmapItem* pixmapItem = scene->addPixmap(pixmap);
    ui->image->fitInView(pixmapItem, Qt::KeepAspectRatio);

    // отображаем информацию о картинке
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

void MainWindow::on_noiseSlider_actionTriggered(int action)
{
    switch (action)
    {
    case 3: case 4:
        on_noiseSlider_sliderReleased();
    }
}

void MainWindow::on_noiseSlider_sliderReleased()
{
    int value = ui->noiseSlider->value();
    if (this->layers.contains("noise"))
    {
        this->layers.remove("noise");
    }

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

    QPixmap pixmap = QPixmap::fromImage(temp);
    scene->addPixmap(pixmap);
}

void MainWindow::on_saturationSlider_actionTriggered(int action)
{
    switch (action)
    {
    case 3: case 4:
        on_noiseSlider_sliderReleased();
    }
}

void MainWindow::on_saturationSlider_sliderReleased()
{
    int value = ui->noiseSlider->value();
    if (this->layers.contains("saturation"))
    {
        this->layers.remove("saturation");
    }

    float fvalue = (static_cast<double>(value) / 100.0);

    viewImage = originalImage;

    viewImage = applyEffects();

    // 4 - это значит что можно сделать в 4 раза менее насыщенно либо в 4 раза более насыщенно
    combiningImagesSameSize(viewImage, addSaturation(4), fvalue);

    this->layers["saturation"] = {addSaturation(4), fvalue};

    viewImage = applyEffects();

    QPixmap pixmap = QPixmap::fromImage(viewImage);
    scene->addPixmap(pixmap);
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

QString MainWindow::getImageInfo()
{
    QString result;
    QStringList filePathArray = currentImagePath.split("/");
    QString sizeString = QString("(%1 x %2)").arg(originalImage.width()).arg(originalImage.height());
    result += "• Имя файла: \n\t" + filePathArray.last() + "\n\n";
    result += "• Размеры изображения: \n\t" + sizeString + "\n\n";
    result += ui->image->getScaleInfo() + "\n\n";
    return result;
}

void MainWindow::updateInfo()
{
    ui->infoPlain->setPlainText(getImageInfo());
}

void MainWindow::onScaleChanged()
{
    updateInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}
