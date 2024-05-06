#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Сюда вставлять ПОЛНЫЙ путь до картинки которую нужно отобразить
    originalImage.load("C:\\Users\\echo1\\Desktop\\designerAWS\\build\\Desktop_Qt_6_7_0_MinGW_64_bit-Debug\\res\\520efb741b4f940e59e165debcddc3ed.jpeg");

    // копипуем основную картинку
    this->viewImage = QImage(originalImage);

    // новая пиксель-мапа исходной картинки с высотой "1000"
    // высота 1000 - оптималная вычисленная для экрана 1920x1080
    QPixmap scaledPixmap = newSize(originalImage,
                                   originalImage.width(),
                                   originalImage.height(),
                                   1000);
    ui->image->setPixmap(scaledPixmap);
    //ui->image->setFixedSize(scaledPixmap.size());
    ui->image->setAlignment(Qt::AlignCenter);
}

QPixmap MainWindow::newSize(const QImage originalImage, int w, int h, int newHeight)
{
    // коэф. который и изменяет размер
    double k = static_cast<double>(h) / w;
    int newWidth = static_cast<int>(newHeight / k);

    // если ширина больше допустимого, 1600 - макс доп. ширина
    if (newWidth > 1600)
    {
        newWidth = 1600;
        newHeight = static_cast<int>(newWidth * k);
    }
    QPixmap newPixmap = QPixmap::fromImage(originalImage).scaled(newWidth, newHeight);
    return newPixmap;
}

MainWindow::~MainWindow()
{
    delete ui;
}
