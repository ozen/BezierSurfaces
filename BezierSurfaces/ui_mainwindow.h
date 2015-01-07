/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "bezierwidget.h"
#include "cpwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionWireframe;
    QAction *actionGouraud;
    QAction *actionPhong;
    QAction *actionAdd;
    QAction *actionDelete;
    QWidget *centralWidget;
    CPWidget *topViewWidget;
    CPWidget *sideViewWidget;
    CPWidget *frontViewWidget;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_6;
    BezierWidget *bezierWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(830, 860);
        actionWireframe = new QAction(MainWindow);
        actionWireframe->setObjectName(QStringLiteral("actionWireframe"));
        actionGouraud = new QAction(MainWindow);
        actionGouraud->setObjectName(QStringLiteral("actionGouraud"));
        actionPhong = new QAction(MainWindow);
        actionPhong->setObjectName(QStringLiteral("actionPhong"));
        actionAdd = new QAction(MainWindow);
        actionAdd->setObjectName(QStringLiteral("actionAdd"));
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        topViewWidget = new CPWidget(centralWidget);
        topViewWidget->setObjectName(QStringLiteral("topViewWidget"));
        topViewWidget->setGeometry(QRect(10, 10, 400, 400));
        sideViewWidget = new CPWidget(centralWidget);
        sideViewWidget->setObjectName(QStringLiteral("sideViewWidget"));
        sideViewWidget->setGeometry(QRect(420, 10, 400, 400));
        frontViewWidget = new CPWidget(centralWidget);
        frontViewWidget->setObjectName(QStringLiteral("frontViewWidget"));
        frontViewWidget->setGeometry(QRect(10, 420, 400, 400));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(190, 420, 20, 20));
        label_4->setAutoFillBackground(true);
        label_4->setFrameShape(QFrame::Box);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(390, 600, 20, 20));
        label_5->setAutoFillBackground(true);
        label_5->setFrameShape(QFrame::Box);
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(190, 390, 20, 20));
        label_6->setAutoFillBackground(true);
        label_6->setFrameShape(QFrame::Box);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(390, 190, 20, 20));
        label_7->setAutoFillBackground(true);
        label_7->setFrameShape(QFrame::Box);
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(800, 190, 20, 20));
        label_8->setAutoFillBackground(true);
        label_8->setFrameShape(QFrame::Box);
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(600, 10, 20, 20));
        label_9->setAutoFillBackground(true);
        label_9->setFrameShape(QFrame::Box);
        label_9->setAlignment(Qt::AlignCenter);
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 210, 400, 1));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(420, 210, 400, 1));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(10, 620, 400, 1));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(210, 10, 1, 400));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(620, 10, 1, 400));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(210, 420, 1, 400));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        bezierWidget = new BezierWidget(centralWidget);
        bezierWidget->setObjectName(QStringLiteral("bezierWidget"));
        bezierWidget->setGeometry(QRect(420, 420, 400, 400));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 830, 101, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(120, 830, 121, 23));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(580, 830, 75, 23));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(660, 830, 75, 23));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(740, 830, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 47, 13));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label->setPalette(palette);
        label->setAutoFillBackground(false);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(430, 10, 47, 13));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_2->setPalette(palette1);
        label_2->setAutoFillBackground(false);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 420, 47, 13));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_3->setPalette(palette2);
        label_3->setAutoFillBackground(false);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(topViewWidget, SIGNAL(ctrlPointMoved(QVector3D)), sideViewWidget, SLOT(moveCtrlPoint(QVector3D)));
        QObject::connect(topViewWidget, SIGNAL(ctrlPointMoved(QVector3D)), frontViewWidget, SLOT(moveCtrlPoint(QVector3D)));
        QObject::connect(topViewWidget, SIGNAL(ctrlPointSelected(int)), frontViewWidget, SLOT(selectCtrlPoint(int)));
        QObject::connect(topViewWidget, SIGNAL(ctrlPointSelected(int)), sideViewWidget, SLOT(selectCtrlPoint(int)));
        QObject::connect(frontViewWidget, SIGNAL(ctrlPointSelected(int)), topViewWidget, SLOT(selectCtrlPoint(int)));
        QObject::connect(frontViewWidget, SIGNAL(ctrlPointMoved(QVector3D)), topViewWidget, SLOT(moveCtrlPoint(QVector3D)));
        QObject::connect(sideViewWidget, SIGNAL(ctrlPointMoved(QVector3D)), topViewWidget, SLOT(moveCtrlPoint(QVector3D)));
        QObject::connect(sideViewWidget, SIGNAL(ctrlPointSelected(int)), topViewWidget, SLOT(selectCtrlPoint(int)));
        QObject::connect(frontViewWidget, SIGNAL(ctrlPointMoved(QVector3D)), sideViewWidget, SLOT(moveCtrlPoint(QVector3D)));
        QObject::connect(frontViewWidget, SIGNAL(ctrlPointSelected(int)), sideViewWidget, SLOT(selectCtrlPoint(int)));
        QObject::connect(sideViewWidget, SIGNAL(ctrlPointMoved(QVector3D)), frontViewWidget, SLOT(moveCtrlPoint(QVector3D)));
        QObject::connect(sideViewWidget, SIGNAL(ctrlPointSelected(int)), frontViewWidget, SLOT(selectCtrlPoint(int)));
        QObject::connect(topViewWidget, SIGNAL(ctrlPointMoved(QVector3D)), bezierWidget, SLOT(moveCtrlPoint(QVector3D)));
        QObject::connect(topViewWidget, SIGNAL(ctrlPointSelected(int)), bezierWidget, SLOT(selectCtrlPoint(int)));
        QObject::connect(sideViewWidget, SIGNAL(ctrlPointMoved(QVector3D)), bezierWidget, SLOT(moveCtrlPoint(QVector3D)));
        QObject::connect(sideViewWidget, SIGNAL(ctrlPointSelected(int)), bezierWidget, SLOT(selectCtrlPoint(int)));
        QObject::connect(frontViewWidget, SIGNAL(ctrlPointMoved(QVector3D)), bezierWidget, SLOT(moveCtrlPoint(QVector3D)));
        QObject::connect(frontViewWidget, SIGNAL(ctrlPointSelected(int)), bezierWidget, SLOT(selectCtrlPoint(int)));
        QObject::connect(pushButton, SIGNAL(clicked()), frontViewWidget, SLOT(addCtrlPoint()));
        QObject::connect(pushButton, SIGNAL(clicked()), bezierWidget, SLOT(addCtrlPoint()));
        QObject::connect(pushButton, SIGNAL(clicked()), sideViewWidget, SLOT(addCtrlPoint()));
        QObject::connect(pushButton, SIGNAL(clicked()), topViewWidget, SLOT(addCtrlPoint()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), bezierWidget, SLOT(deleteCtrlPoint()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), frontViewWidget, SLOT(deleteCtrlPoint()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), sideViewWidget, SLOT(deleteCtrlPoint()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), topViewWidget, SLOT(deleteCtrlPoint()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), bezierWidget, SLOT(setWireframe()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), bezierWidget, SLOT(setGouraud()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), bezierWidget, SLOT(setPhong()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "B\303\251zier Surfaces", 0));
        actionWireframe->setText(QApplication::translate("MainWindow", "Wireframe", 0));
        actionGouraud->setText(QApplication::translate("MainWindow", "Gouraud", 0));
        actionPhong->setText(QApplication::translate("MainWindow", "Phong", 0));
        actionAdd->setText(QApplication::translate("MainWindow", "Add", 0));
        actionDelete->setText(QApplication::translate("MainWindow", "Delete", 0));
        label_4->setText(QApplication::translate("MainWindow", "Y", 0));
        label_5->setText(QApplication::translate("MainWindow", "X", 0));
        label_6->setText(QApplication::translate("MainWindow", "Z", 0));
        label_7->setText(QApplication::translate("MainWindow", "X", 0));
        label_8->setText(QApplication::translate("MainWindow", "Z", 0));
        label_9->setText(QApplication::translate("MainWindow", "Y", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Add Control Point", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Remove Control Point", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Wireframe", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Gouraud", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "Phong", 0));
        label->setText(QApplication::translate("MainWindow", "TOP", 0));
        label_2->setText(QApplication::translate("MainWindow", "LEFT SIDE", 0));
        label_3->setText(QApplication::translate("MainWindow", "FRONT", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
