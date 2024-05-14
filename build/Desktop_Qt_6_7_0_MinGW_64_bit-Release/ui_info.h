/********************************************************************************
** Form generated from reading UI file 'info.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFO_H
#define UI_INFO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Info
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *Info)
    {
        if (Info->objectName().isEmpty())
            Info->setObjectName("Info");
        Info->resize(318, 354);
        QIcon icon;
        icon.addFile(QString::fromUtf8("res/icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Info->setWindowIcon(icon);
        label = new QLabel(Info);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 70, 241, 181));
        QFont font;
        font.setFamilies({QString::fromUtf8("Yu Gothic")});
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);
        label_2 = new QLabel(Info);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(-20, 220, 241, 181));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Yu Gothic")});
        font1.setPointSize(9);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        label_2->setWordWrap(true);

        retranslateUi(Info);

        QMetaObject::connectSlotsByName(Info);
    } // setupUi

    void retranslateUi(QWidget *Info)
    {
        Info->setWindowTitle(QCoreApplication::translate("Info", "Info", nullptr));
        label->setText(QCoreApplication::translate("Info", "The project was created for the purpose of practice, as a group project in computer science", nullptr));
        label_2->setText(QCoreApplication::translate("Info", "Prod. by: echo1, roazanas.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Info: public Ui_Info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_H
