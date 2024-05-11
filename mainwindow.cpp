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
