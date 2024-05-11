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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
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
    QAction *actioninfo;
    QAction *help;
    QAction *info;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QPlainTextEdit *infoPlain;
    QListWidget *activityLog;
    QSpacerItem *horizontalSpacer_2;
    CustomView *image;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *noiseLabel;
    QSlider *noiseSlider;
    QLabel *saturationLabel;
    QSlider *saturationSlider;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_5;
    QPushButton *invertButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QMenuBar *menuBar;
    QMenu *menuSettings;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1043, 800);
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
        actioninfo = new QAction(MainWindow);
        actioninfo->setObjectName("actioninfo");
        help = new QAction(MainWindow);
        help->setObjectName("help");
        info = new QAction(MainWindow);
        info->setObjectName("info");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_3 = new QSpacerItem(15, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        infoPlain = new QPlainTextEdit(centralwidget);
        infoPlain->setObjectName("infoPlain");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(infoPlain->sizePolicy().hasHeightForWidth());
        infoPlain->setSizePolicy(sizePolicy);
        infoPlain->setMinimumSize(QSize(0, 0));
        infoPlain->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        infoPlain->setReadOnly(true);
        infoPlain->setTextInteractionFlags(Qt::NoTextInteraction);
        infoPlain->setMaximumBlockCount(0);
        infoPlain->setBackgroundVisible(false);
        infoPlain->setCenterOnScroll(false);

        verticalLayout_3->addWidget(infoPlain);

        activityLog = new QListWidget(centralwidget);
        activityLog->setObjectName("activityLog");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(activityLog->sizePolicy().hasHeightForWidth());
        activityLog->setSizePolicy(sizePolicy1);
        activityLog->setEditTriggers(QAbstractItemView::NoEditTriggers);
        activityLog->setTabKeyNavigation(true);
        activityLog->setAlternatingRowColors(true);

        verticalLayout_3->addWidget(activityLog);


        horizontalLayout_2->addLayout(verticalLayout_3);

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
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName("loadButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy2);
        loadButton->setMinimumSize(QSize(50, 50));
        loadButton->setAcceptDrops(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("res/icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        loadButton->setIcon(icon1);
        loadButton->setIconSize(QSize(40, 40));
        loadButton->setCheckable(true);
        loadButton->setAutoDefault(false);
        loadButton->setFlat(false);

        horizontalLayout_3->addWidget(loadButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");
        saveButton->setEnabled(false);
        sizePolicy2.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        saveButton->setSizePolicy(sizePolicy2);
        saveButton->setMinimumSize(QSize(50, 50));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("res/file.svg"), QSize(), QIcon::Normal, QIcon::Off);
        saveButton->setIcon(icon2);
        saveButton->setIconSize(QSize(40, 40));
        saveButton->setFlat(false);

        horizontalLayout_3->addWidget(saveButton);


        verticalLayout->addLayout(horizontalLayout_3);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        QFont font;
        font.setFamilies({QString::fromUtf8("Yu Gothic")});
        font.setPointSize(12);
        groupBox->setFont(font);
        groupBox->setCursor(QCursor(Qt::PointingHandCursor));
        groupBox->setContextMenuPolicy(Qt::NoContextMenu);
        groupBox->setAcceptDrops(false);
        groupBox->setLayoutDirection(Qt::LeftToRight);
        groupBox->setAutoFillBackground(false);
        groupBox->setAlignment(Qt::AlignCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        noiseLabel = new QLabel(groupBox);
        noiseLabel->setObjectName("noiseLabel");
        noiseLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        noiseLabel->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_4->addWidget(noiseLabel);

        noiseSlider = new QSlider(groupBox);
        noiseSlider->setObjectName("noiseSlider");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(noiseSlider->sizePolicy().hasHeightForWidth());
        noiseSlider->setSizePolicy(sizePolicy4);
        noiseSlider->setMinimumSize(QSize(120, 0));
        noiseSlider->setContextMenuPolicy(Qt::DefaultContextMenu);
        noiseSlider->setToolTipDuration(-1);
        noiseSlider->setMaximum(100);
        noiseSlider->setSingleStep(0);
        noiseSlider->setPageStep(0);
        noiseSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(noiseSlider);

        saturationLabel = new QLabel(groupBox);
        saturationLabel->setObjectName("saturationLabel");
        saturationLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        saturationLabel->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_4->addWidget(saturationLabel);

        saturationSlider = new QSlider(groupBox);
        saturationSlider->setObjectName("saturationSlider");
        sizePolicy4.setHeightForWidth(saturationSlider->sizePolicy().hasHeightForWidth());
        saturationSlider->setSizePolicy(sizePolicy4);
        saturationSlider->setMinimumSize(QSize(120, 0));
        saturationSlider->setToolTipDuration(-1);
        saturationSlider->setLayoutDirection(Qt::LeftToRight);
        saturationSlider->setAutoFillBackground(false);
        saturationSlider->setMaximum(200);
        saturationSlider->setSingleStep(0);
        saturationSlider->setPageStep(0);
        saturationSlider->setValue(100);
        saturationSlider->setSliderPosition(100);
        saturationSlider->setTracking(true);
        saturationSlider->setOrientation(Qt::Horizontal);
        saturationSlider->setInvertedAppearance(false);

        verticalLayout_4->addWidget(saturationSlider);

        noiseLabel->raise();
        saturationLabel->raise();
        noiseSlider->raise();
        saturationSlider->raise();

        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setEnabled(false);
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        groupBox_2->setFont(font);
        groupBox_2->setCursor(QCursor(Qt::PointingHandCursor));
        groupBox_2->setAcceptDrops(false);
        groupBox_2->setAlignment(Qt::AlignCenter);
        verticalLayout_5 = new QVBoxLayout(groupBox_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        invertButton = new QPushButton(groupBox_2);
        invertButton->setObjectName("invertButton");
        sizePolicy3.setHeightForWidth(invertButton->sizePolicy().hasHeightForWidth());
        invertButton->setSizePolicy(sizePolicy3);
        invertButton->setMinimumSize(QSize(155, 45));
        invertButton->setCheckable(false);

        verticalLayout_5->addWidget(invertButton);

        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName("pushButton_5");
        sizePolicy3.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy3);
        pushButton_5->setMinimumSize(QSize(155, 45));
        pushButton_5->setCheckable(false);

        verticalLayout_5->addWidget(pushButton_5);

        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy3.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy3);
        pushButton_3->setMinimumSize(QSize(155, 45));
        pushButton_3->setCheckable(false);

        verticalLayout_5->addWidget(pushButton_3);

        pushButton_5->raise();
        pushButton_3->raise();
        invertButton->raise();

        verticalLayout->addWidget(groupBox_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1043, 25));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName("menuSettings");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuSettings->menuAction());
        menuSettings->addSeparator();
        menuSettings->addAction(info);
        menuSettings->addAction(help);

        retranslateUi(MainWindow);

        loadButton->setDefault(false);
        saveButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Designer tool", nullptr));
        actioninfo->setText(QCoreApplication::translate("MainWindow", "help", nullptr));
        help->setText(QCoreApplication::translate("MainWindow", "help", nullptr));
        info->setText(QCoreApplication::translate("MainWindow", "info", nullptr));
        infoPlain->setDocumentTitle(QString());
        infoPlain->setPlainText(QString());
        infoPlain->setPlaceholderText(QCoreApplication::translate("MainWindow", "Upload image by pressing icon button", nullptr));
#if QT_CONFIG(tooltip)
        loadButton->setToolTip(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217", nullptr));
#endif // QT_CONFIG(tooltip)
        loadButton->setText(QString());
#if QT_CONFIG(shortcut)
        loadButton->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        saveButton->setToolTip(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
#endif // QT_CONFIG(tooltip)
        saveButton->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Sliders", nullptr));
        noiseLabel->setText(QCoreApplication::translate("MainWindow", "Noise", nullptr));
#if QT_CONFIG(tooltip)
        noiseSlider->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        noiseSlider->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        saturationLabel->setText(QCoreApplication::translate("MainWindow", "Saturation", nullptr));
#if QT_CONFIG(tooltip)
        saturationSlider->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        saturationSlider->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        saturationSlider->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
#if QT_CONFIG(accessibility)
        saturationSlider->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        saturationSlider->setAccessibleDescription(QString());
#endif // QT_CONFIG(accessibility)
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
#if QT_CONFIG(tooltip)
        invertButton->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        invertButton->setText(QCoreApplication::translate("MainWindow", "Swap RGB", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_5->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Tool", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_3->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Tool", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
