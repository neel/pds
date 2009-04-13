/********************************************************************************
** Form generated from reading ui file 'dialog.ui'
**
** Created: Sat Apr 11 21:17:14 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogClass
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *DialogClass)
    {
    if (DialogClass->objectName().isEmpty())
        DialogClass->setObjectName(QString::fromUtf8("DialogClass"));
    DialogClass->resize(156, 35);
    horizontalLayout = new QHBoxLayout(DialogClass);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setMargin(11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    pushButton = new QPushButton(DialogClass);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    horizontalLayout->addWidget(pushButton);

    pushButton_2 = new QPushButton(DialogClass);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

    horizontalLayout->addWidget(pushButton_2);


    retranslateUi(DialogClass);
    QObject::connect(pushButton, SIGNAL(released()), DialogClass, SLOT(startSlot()));
    QObject::connect(pushButton_2, SIGNAL(released()), DialogClass, SLOT(reportSlot()));

    QMetaObject::connectSlotsByName(DialogClass);
    } // setupUi

    void retranslateUi(QDialog *DialogClass)
    {
    DialogClass->setWindowTitle(QApplication::translate("DialogClass", "Dialog", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("DialogClass", "&Start", 0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("DialogClass", "&Report", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(DialogClass);
    } // retranslateUi

};

namespace Ui {
    class DialogClass: public Ui_DialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
