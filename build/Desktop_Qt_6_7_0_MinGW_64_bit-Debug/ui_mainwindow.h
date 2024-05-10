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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <customview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPlainTextEdit *infoPlain;
    QSpacerItem *horizontalSpacer_2;
    CustomView *image;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *loadButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QFormLayout *formLayout;
    QSlider *noiseSlider;
    QSlider *saturationSlider;
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
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_3 = new QSpacerItem(15, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

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

        horizontalLayout_2->addWidget(infoPlain);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        image = new CustomView(centralwidget);
        image->setObjectName("image");
        image->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));

        horizontalLayout_2->addWidget(image);


        horizontalLayout->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(25);
        verticalLayout->setObjectName("verticalLayout");
        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName("loadButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy1);
        loadButton->setMinimumSize(QSize(155, 45));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("res/icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        loadButton->setIcon(icon1);
        loadButton->setIconSize(QSize(50, 40));
        loadButton->setCheckable(true);
        loadButton->setAutoDefault(false);
        loadButton->setFlat(false);

        verticalLayout->addWidget(loadButton);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        sizePolicy1.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy1);
        pushButton_4->setMinimumSize(QSize(155, 45));
        pushButton_4->setCheckable(false);

        verticalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        sizePolicy1.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy1);
        pushButton_5->setMinimumSize(QSize(155, 45));
        pushButton_5->setCheckable(false);

        verticalLayout->addWidget(pushButton_5);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setMinimumSize(QSize(155, 45));
        pushButton_3->setCheckable(false);

        verticalLayout->addWidget(pushButton_3);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        formLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(25);
        noiseSlider = new QSlider(centralwidget);
        noiseSlider->setObjectName("noiseSlider");
        sizePolicy1.setHeightForWidth(noiseSlider->sizePolicy().hasHeightForWidth());
        noiseSlider->setSizePolicy(sizePolicy1);
        noiseSlider->setMinimumSize(QSize(120, 0));
        noiseSlider->setMaximum(100);
        noiseSlider->setPageStep(5);
        noiseSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::LabelRole, noiseSlider);

        saturationSlider = new QSlider(centralwidget);
        saturationSlider->setObjectName("saturationSlider");
        sizePolicy1.setHeightForWidth(saturationSlider->sizePolicy().hasHeightForWidth());
        saturationSlider->setSizePolicy(sizePolicy1);
        saturationSlider->setMinimumSize(QSize(120, 0));
        saturationSlider->setLayoutDirection(Qt::LeftToRight);
        saturationSlider->setAutoFillBackground(false);
        saturationSlider->setMaximum(100);
        saturationSlider->setValue(50);
        saturationSlider->setTracking(true);
        saturationSlider->setOrientation(Qt::Horizontal);
        saturationSlider->setInvertedAppearance(false);

        formLayout->setWidget(1, QFormLayout::LabelRole, saturationSlider);


        verticalLayout->addLayout(formLayout);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName("menuSettings");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuSettings->menuAction());
        menuSettings->addSeparator();

        retranslateUi(MainWindow);

        loadButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Designer tool", nullptr));
        infoPlain->setPlainText(QString());
        infoPlain->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265, \320\275\320\260\320\266\320\260\320\262 \320\275\320\260 \320\261\320\276\320\273\321\214\321\210\321\203\321\216 \320\272\320\275\320\276\320\277\320\272\321\203 \320\262 \320\262\320\270\320\264\320\265 \320\270\320\272\320\276\320\275\320\272\320\270 \321\215\321\202\320\276\320\263\320\276 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217", nullptr));
        loadButton->setText(QString());
#if QT_CONFIG(shortcut)
        loadButton->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Tool", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Tool", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Tool", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
