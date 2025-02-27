/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *ColorInput;
    QLineEdit *colorInputEdit;
    QComboBox *formatComboBox;
    QPushButton *previewButton;
    QGroupBox *groupBox;
    QFrame *colorPreviewFrame;
    QGroupBox *groupBox_2;
    QFrame *prediction1Frame;
    QLabel *label;
    QComboBox *monitorTypeComboBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        ColorInput = new QGroupBox(centralwidget);
        ColorInput->setObjectName("ColorInput");
        ColorInput->setGeometry(QRect(10, 10, 361, 171));
        colorInputEdit = new QLineEdit(ColorInput);
        colorInputEdit->setObjectName("colorInputEdit");
        colorInputEdit->setGeometry(QRect(60, 70, 201, 22));
        formatComboBox = new QComboBox(ColorInput);
        formatComboBox->setObjectName("formatComboBox");
        formatComboBox->setGeometry(QRect(60, 30, 201, 22));
        previewButton = new QPushButton(ColorInput);
        previewButton->setObjectName("previewButton");
        previewButton->setGeometry(QRect(130, 110, 75, 24));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(380, 20, 401, 161));
        colorPreviewFrame = new QFrame(groupBox);
        colorPreviewFrame->setObjectName("colorPreviewFrame");
        colorPreviewFrame->setGeometry(QRect(70, 40, 251, 80));
        colorPreviewFrame->setFrameShape(QFrame::Shape::Box);
        colorPreviewFrame->setFrameShadow(QFrame::Shadow::Raised);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 190, 771, 351));
        prediction1Frame = new QFrame(groupBox_2);
        prediction1Frame->setObjectName("prediction1Frame");
        prediction1Frame->setGeometry(QRect(10, 40, 171, 16));
        prediction1Frame->setMinimumSize(QSize(100, 10));
        prediction1Frame->setFrameShape(QFrame::Shape::Box);
        prediction1Frame->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 49, 16));
        monitorTypeComboBox = new QComboBox(groupBox_2);
        monitorTypeComboBox->setObjectName("monitorTypeComboBox");
        monitorTypeComboBox->setGeometry(QRect(200, 10, 101, 22));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ColorInput->setTitle(QCoreApplication::translate("MainWindow", "Color Input", nullptr));
        previewButton->setText(QCoreApplication::translate("MainWindow", "Preview", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Your Monitor Preview", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Predictions", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Pre1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
