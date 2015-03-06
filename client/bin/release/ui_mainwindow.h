/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "textedit.h"
#include "userlist.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    UserList *userList;
    QTextBrowser *browserMsg;
    QPushButton *choiceSmile;
    QLabel *labelPrivate;
    QPushButton *connectDisconnectButton;
    QSpacerItem *horizontalSpacer;
    TextEdit *msgEdit;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(674, 505);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 492, 345));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 2);

        userList = new UserList(layoutWidget);
        userList->setObjectName(QStringLiteral("userList"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(userList->sizePolicy().hasHeightForWidth());
        userList->setSizePolicy(sizePolicy);
        userList->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(userList, 1, 4, 1, 2);

        browserMsg = new QTextBrowser(layoutWidget);
        browserMsg->setObjectName(QStringLiteral("browserMsg"));
        browserMsg->setMinimumSize(QSize(350, 190));

        gridLayout->addWidget(browserMsg, 1, 1, 1, 3);

        choiceSmile = new QPushButton(layoutWidget);
        choiceSmile->setObjectName(QStringLiteral("choiceSmile"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(choiceSmile->sizePolicy().hasHeightForWidth());
        choiceSmile->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(choiceSmile, 2, 1, 1, 1);

        labelPrivate = new QLabel(layoutWidget);
        labelPrivate->setObjectName(QStringLiteral("labelPrivate"));

        gridLayout->addWidget(labelPrivate, 2, 2, 1, 1);

        connectDisconnectButton = new QPushButton(layoutWidget);
        connectDisconnectButton->setObjectName(QStringLiteral("connectDisconnectButton"));
        sizePolicy1.setHeightForWidth(connectDisconnectButton->sizePolicy().hasHeightForWidth());
        connectDisconnectButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(connectDisconnectButton, 4, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(27, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 5, 1, 1);

        msgEdit = new TextEdit(layoutWidget);
        msgEdit->setObjectName(QStringLiteral("msgEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(msgEdit->sizePolicy().hasHeightForWidth());
        msgEdit->setSizePolicy(sizePolicy2);
        msgEdit->setMinimumSize(QSize(0, 80));
        msgEdit->setMaximumSize(QSize(16777215, 80));
        msgEdit->setFocusPolicy(Qt::StrongFocus);

        gridLayout->addWidget(msgEdit, 3, 1, 2, 3);

        horizontalSpacer_2 = new QSpacerItem(188, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 68, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 2, 4, 2, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 674, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        choiceSmile->setText(QApplication::translate("MainWindow", "\320\241\320\274\320\260\320\271\320\273\321\213", 0));
        labelPrivate->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\270\320\262\320\260\321\202\320\275\320\276\320\265", 0));
        connectDisconnectButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\320\265", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
