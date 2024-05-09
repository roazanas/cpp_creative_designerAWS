#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    // корипуем основную картинку
    // this->viewImage = QImage(originalImage)

    double a = ui->centralwidget->height();
    double b = originalImage.height();

    scaleFactor = a / b; // сброс коэф. масштабирования
    // новая пиксель-мапа исходной картинки с высотой окна программы
    QPixmap scaledPixmap = rescaleImageByHeight(originalImage,
                                                 ui->centralwidget->height());

    ui->image->setPixmap(scaledPixmap);
    //ui->image->setFixedSize(scaledPixmap.size());
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
    QPixmap scaledPixmap = rescaleImageByHeight(originalImage,
                                                 originalImage.height() * scaleFactor);

    // обновление QLabel
    ui->image->setPixmap(scaledPixmap);

    updateInfo();
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

void MainWindow::updateInfo() {
    ui->infoPlain->setPlainText(getImageInfo());
}

MainWindow::~MainWindow()
{
    delete ui;
}

