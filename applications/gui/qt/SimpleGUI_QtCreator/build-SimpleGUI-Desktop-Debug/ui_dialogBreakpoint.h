/********************************************************************************
** Form generated from reading UI file 'dialogBreakpoint.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGBREAKPOINT_H
#define UI_DIALOGBREAKPOINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dialogBreakpoint
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_Type;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label_Type;
    QComboBox *comboBox_On;
    QDoubleSpinBox *doubleSpinBox_OnTme;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *dialogBreakpoint)
    {
        if (dialogBreakpoint->objectName().isEmpty())
            dialogBreakpoint->setObjectName(QString::fromUtf8("dialogBreakpoint"));
        dialogBreakpoint->setWindowModality(Qt::ApplicationModal);
        dialogBreakpoint->resize(383, 118);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dialogBreakpoint->sizePolicy().hasHeightForWidth());
        dialogBreakpoint->setSizePolicy(sizePolicy);
        dialogBreakpoint->setModal(true);
        verticalLayout = new QVBoxLayout(dialogBreakpoint);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(dialogBreakpoint);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox_Type = new QComboBox(dialogBreakpoint);
        comboBox_Type->setObjectName(QString::fromUtf8("comboBox_Type"));

        horizontalLayout->addWidget(comboBox_Type);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(dialogBreakpoint);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        label_Type = new QLabel(dialogBreakpoint);
        label_Type->setObjectName(QString::fromUtf8("label_Type"));

        horizontalLayout_2->addWidget(label_Type);

        comboBox_On = new QComboBox(dialogBreakpoint);
        comboBox_On->setObjectName(QString::fromUtf8("comboBox_On"));
        comboBox_On->setEnabled(false);

        horizontalLayout_2->addWidget(comboBox_On);

        doubleSpinBox_OnTme = new QDoubleSpinBox(dialogBreakpoint);
        doubleSpinBox_OnTme->setObjectName(QString::fromUtf8("doubleSpinBox_OnTme"));
        doubleSpinBox_OnTme->setDecimals(6);

        horizontalLayout_2->addWidget(doubleSpinBox_OnTme);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(dialogBreakpoint);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(dialogBreakpoint);
        QObject::connect(buttonBox, SIGNAL(accepted()), dialogBreakpoint, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dialogBreakpoint, SLOT(reject()));

        QMetaObject::connectSlotsByName(dialogBreakpoint);
    } // setupUi

    void retranslateUi(QDialog *dialogBreakpoint)
    {
        dialogBreakpoint->setWindowTitle(QCoreApplication::translate("dialogBreakpoint", "Insert Breakpoint", nullptr));
        label->setText(QCoreApplication::translate("dialogBreakpoint", "Breakpoint Type: ", nullptr));
        label_2->setText(QCoreApplication::translate("dialogBreakpoint", "Breakpoint On  ", nullptr));
        label_Type->setText(QCoreApplication::translate("dialogBreakpoint", ".:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialogBreakpoint: public Ui_dialogBreakpoint {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGBREAKPOINT_H
