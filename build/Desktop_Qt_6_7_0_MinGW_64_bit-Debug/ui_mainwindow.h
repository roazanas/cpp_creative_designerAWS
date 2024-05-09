/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *infoPlain;
    QLabel *image;
    QGridLayout *gridLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *loadButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QMenu *menuSettings;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 800);
        MainWindow->setMinimumSize(QSize(800, 800));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("applications-graphics");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("res/icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        infoPlain = new QPlainTextEdit(centralwidget);
        infoPlain->setObjectName("infoPlain");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(infoPlain->sizePolicy().hasHeightForWidth());
        infoPlain->setSizePolicy(sizePolicy);
        infoPlain->setMinimumSize(QSize(0, 0));
        infoPlain->setReadOnly(true);
        infoPlain->setTextInteractionFlags(Qt::NoTextInteraction);
        infoPlain->setBackgroundVisible(false);

        horizontalLayout->addWidget(infoPlain);

        image = new QLabel(centralwidget);
        image->setObjectName("image");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(image->sizePolicy().hasHeightForWidth());
        image->setSizePolicy(sizePolicy1);
        image->setCursor(QCursor(Qt::CrossCursor));
        image->setLayoutDirection(Qt::LeftToRight);
        image->setFrameShape(QFrame::NoFrame);
        image->setFrameShadow(QFrame::Plain);
        image->setMidLineWidth(5);
        image->setTextFormat(Qt::AutoText);
        image->setScaledContents(false);
        image->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        image->setWordWrap(false);

        horizontalLayout->addWidget(image);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy2);
        pushButton_3->setMinimumSize(QSize(120, 120));
        pushButton_3->setCheckable(false);

        gridLayout->addWidget(pushButton_3, 2, 0, 1, 1);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        sizePolicy2.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy2);
        pushButton_5->setMinimumSize(QSize(120, 120));
        pushButton_5->setCheckable(false);

        gridLayout->addWidget(pushButton_5, 4, 0, 1, 1);

        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName("loadButton");
        sizePolicy2.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy2);
        loadButton->setMinimumSize(QSize(120, 120));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("res/icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        loadButton->setIcon(icon1);
        loadButton->setIconSize(QSize(100, 100));
        loadButton->setCheckable(true);
        loadButton->setAutoDefault(false);
        loadButton->setFlat(false);

        gridLayout->addWidget(loadButton, 0, 0, 1, 1);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        sizePolicy2.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy2);
        pushButton_4->setMinimumSize(QSize(120, 120));
        pushButton_4->setCheckable(false);

        gridLayout->addWidget(pushButton_4, 3, 0, 1, 1);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy2.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy2);
        pushButton_2->setMinimumSize(QSize(120, 120));
        pushButton_2->setCheckable(false);

        gridLayout->addWidget(pushButton_2, 1, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 800, 25));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName("menuSettings");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuSettings->menuAction());

        retranslateUi(MainWindow);

        loadButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Designer tool", nullptr));
        infoPlain->setPlainText(QString());
        infoPlain->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265, \320\275\320\260\320\266\320\260\320\262 \320\275\320\260 \320\261\320\276\320\273\321\214\321\210\321\203\321\216 \320\272\320\275\320\276\320\277\320\272\321\203 \320\262 \320\262\320\270\320\264\320\265 \320\270\320\272\320\276\320\275\320\272\320\270 \321\215\321\202\320\276\320\263\320\276 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217", nullptr));
        image->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Tool", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Tool", nullptr));
        loadButton->setText(QString());
#if QT_CONFIG(shortcut)
        loadButton->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Tool", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Tool", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
