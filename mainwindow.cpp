#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    info = new Info;
    scene = new QGraphicsScene(this);
    connect(ui->image, &CustomView::scaleChanged, this, &MainWindow::onScaleChanged);

    setAcceptDrops(true);
}

void MainWindow::loadImage(QString fileName)
{
    ui->groupBox->setEnabled(1);
    ui->groupBox_2->setEnabled(1);

    // радикальные методы очистки, т.к. scene.clear() работает не полностью корректно
    delete scene;
    scene = new QGraphicsScene(this);
    ui->image->setScene(scene);

    // перемещаем слайдеры в первоначальное положение
    ui->noiseSlider->setValue(0);
    ui->saturationSlider->setValue(ui->saturationSlider->maximum()/2);
    ui->noiseSlider->setToolTip(QString("%1%").arg(0));
    ui->saturationSlider->setToolTip(QString("%1%").arg(ui->saturationSlider->maximum()/2));

    currentImagePath = fileName;
    originalImage.load(fileName);
    originalImage = originalImage.convertToFormat(QImage::Format_ARGB32);

    this->viewImage = originalImage.copy();
    this->viewImage = viewImage.convertToFormat(QImage::Format_ARGB32);
    this->layers.clear();
    this->noise = QImage();

    QPixmap pixmap = QPixmap::fromImage(viewImage);
    QGraphicsPixmapItem* pixmapItem = scene->addPixmap(pixmap);
    ui->image->fitInView(pixmapItem, Qt::KeepAspectRatio);

    // отображаем информацию об изображении
    updateInfo();
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
        double transparency = it.value();
        if (effect == "saturation") {this->viewImage = addSaturation(transparency);}
        if (effect == "invertation") {this->viewImage = viewImage.rgbSwapped();}
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
}

void MainWindow::on_saturationSlider_actionTriggered(int action)
{
    switch (action)
    {
    case 3: case 4:
        on_saturationSlider_sliderReleased();
    }
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
}

QImage MainWindow::addSaturation(double k)
{
    int width = this->originalImage.width();
    int height = this->originalImage.height();
    QImage saturation = this->viewImage;
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
    int width = this->originalImage.width();
    int height = this->originalImage.height();
    QImage noise(width, height, QImage::Format_ARGB32);

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
    if (this->currentImagePath != "")
        updateInfo();
}

void MainWindow::on_invertButton_clicked()
{

    // пока не работает корректно
    if (this->effects.contains("invertation"))
    {
        this->effects.remove("invertation");
        QPixmap pixmap = QPixmap::fromImage(viewImage);
        scene->clear();
        scene->addPixmap(pixmap);
        return;
    }


    double transperancy = 1.0;

    QImage temp;

    viewImage = originalImage.copy();

    viewImage = applyLayers();

    this->effects["invertation"] = {transperancy};

    temp = applyEffects();

    QPixmap pixmap = QPixmap::fromImage(temp);
    scene->clear();
    scene->addPixmap(pixmap);
}

void MainWindow::on_info_triggered()
{
    info->move(100,100);
    info->show();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    // Получаем URL из события
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }

    // Получаем путь к файлу
    QString fileName = urls.first().toLocalFile();

    loadImage(fileName);
}

MainWindow::~MainWindow()
{
    delete ui;
}

