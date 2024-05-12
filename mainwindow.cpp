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
    connect(ui->image, &CustomView::mouseClick, this, &MainWindow::onMouseClick);

    setAcceptDrops(true);
}

void MainWindow::loadImage(QString fileName)
{
    ui->groupBox->setEnabled(1);
    ui->groupBox_2->setEnabled(1);
    ui->saveButton->setEnabled(1);

    // радикальные методы очистки, т.к. scene.clear() работает не полностью корректно
    delete scene;
    scene = new QGraphicsScene(this);
    ui->image->setScene(scene);
    this->amountOfLightFlag = false;
    this->inversionFlag = false;
    this->swapRGBFlag = false;

    this->layers.clear();
    this->effects.clear();

    // перемещаем слайдеры в первоначальное положение
    ui->noiseSlider->setValue(0);
    ui->saturationSlider->setValue(ui->saturationSlider->maximum()/2);
    ui->thresholdSlider->setValue(30);
    ui->noiseLabel->setText("Noise (0%)");
    ui->saturationLabel->setText("Saturation ("+QString("%1%").arg(ui->saturationSlider->maximum()/2)+")");
    ui->thresholdLabel->setText("Threshold (30)");

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

    ui->activityLog->addItem("Opened: "+fileName);
    setTimeToLastItem();
}

QString MainWindow::getImageInfo()
{
    QString result;
    QStringList filePathArray = currentImagePath.split("/");
    QString sizeString = QString("(%1 x %2)").arg(originalImage.width()).arg(originalImage.height());
    result += "• File name: \n\t" + filePathArray.last() + "\n\n";
    result += "• Image size: \n\t" + sizeString + "\n\n";
    result += ui->image->getScaleInfo() + "\n\n";
    if (!amountOfLightFlag)
    {
        amountOfLight();
        this->amountOfLightFlag = true;
    }

    result += this->overexposureStatus;
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
    // получаем URL из события
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }

    // получаем путь к файлу
    QString fileName = urls.first().toLocalFile();

    loadImage(fileName);
}

void MainWindow::onMouseClick(QPoint point)
{
    if (ui->removeBGButton->isChecked()) {
        pointToFill = point;
        QImage temp;
        viewImage = originalImage.copy();
        viewImage = applyLayers();
        this->effects["filled"].first = &MainWindow::applyFloodFill;
        this->effects["filled"].second = 1.0;
        temp = applyEffects();

        QPixmap pixmap = QPixmap::fromImage(temp);
        scene->clear();
        scene->addPixmap(pixmap);

        ui->activityLog->addItem("Filled image");
        setTimeToLastItem();

        ui->removeBGButton->setChecked(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
