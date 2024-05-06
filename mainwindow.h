#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QColor>
#include <QImage>
#include <iostream>

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

private:
    Ui::MainWindow *ui;

    // основное изобраение которое мы загружаем
    QImage originalImage;

    // копия основного, над которой будут проводиться
    // изменения, чтобы не менять исходник
    QImage viewImage;

    // функция для подгона размера изображения под размер экрана
    // в том числе учитывает и ширину
    QPixmap newSize(const QImage originalImage, int w, int h, int newWidth);
};
#endif // MAINWINDOW_H
