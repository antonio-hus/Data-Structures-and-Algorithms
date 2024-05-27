/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *allBox;
    QCheckBox *unpaidBox;
    QCheckBox *paidBox;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *companySearch;
    QPushButton *getTotalButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *totalSumLabel;

    void setupUi(QWidget *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName("GUI");
        GUI->resize(577, 477);
        verticalLayout = new QVBoxLayout(GUI);
        verticalLayout->setObjectName("verticalLayout");
        listWidget = new QListWidget(GUI);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        allBox = new QCheckBox(GUI);
        allBox->setObjectName("allBox");

        horizontalLayout->addWidget(allBox);

        unpaidBox = new QCheckBox(GUI);
        unpaidBox->setObjectName("unpaidBox");

        horizontalLayout->addWidget(unpaidBox);

        paidBox = new QCheckBox(GUI);
        paidBox->setObjectName("paidBox");

        horizontalLayout->addWidget(paidBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        companySearch = new QLineEdit(GUI);
        companySearch->setObjectName("companySearch");

        horizontalLayout_2->addWidget(companySearch);

        getTotalButton = new QPushButton(GUI);
        getTotalButton->setObjectName("getTotalButton");

        horizontalLayout_2->addWidget(getTotalButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(GUI);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        totalSumLabel = new QLabel(GUI);
        totalSumLabel->setObjectName("totalSumLabel");

        horizontalLayout_3->addWidget(totalSumLabel);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(GUI);

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QWidget *GUI)
    {
        GUI->setWindowTitle(QCoreApplication::translate("GUI", "GUI", nullptr));
        allBox->setText(QCoreApplication::translate("GUI", "Show All", nullptr));
        unpaidBox->setText(QCoreApplication::translate("GUI", "Show UnPaid", nullptr));
        paidBox->setText(QCoreApplication::translate("GUI", "Show Paid", nullptr));
        getTotalButton->setText(QCoreApplication::translate("GUI", "Compute Bills", nullptr));
        label->setText(QCoreApplication::translate("GUI", "Total Unpaid Bills Sum:", nullptr));
        totalSumLabel->setText(QCoreApplication::translate("GUI", "N/A", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
