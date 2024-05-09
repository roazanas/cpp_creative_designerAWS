#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QColor>
#include <QImage>
#include <QFileDialog>
#include <string>
// #include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;

    // основное изобраение которое мы загружаем
    QImage originalImage;
    QString currentImagePath = "";


    // // копия основного, над которой будут проводиться
    // // изменения, чтобы не менять исходник
    // QImage viewImage;

    // функция для подгона размера изображения под размер экрана
    // в том числе учитывает и ширину
    QPixmap rescaleImageByHeight(const QImage originalImage, int newWidth);
    double scaleFactor;

    void wheelEvent(QWheelEvent *event);

    QString getImageInfo();

    void updateInfo();
};
#endif // MAINWINDOW_H
