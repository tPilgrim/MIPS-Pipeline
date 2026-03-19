/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include <VerticalLabel.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *stepButton;
    QLabel *cycleLabel;
    QListWidget *instrList;
    QTableWidget *regTable;
    QTableWidget *memTable;
    QLabel *pipelineLabel;
    QLabel *IF_ID_PC;
    VerticalLabel *Instruction;
    QLabel *ID_EX_PC;
    QLabel *RD1;
    QLabel *RD2;
    QLabel *Imm;
    QLabel *dest;
    QLabel *ID_EX_OP;
    QLabel *Address;
    QLabel *Zero;
    QLabel *ALURes;
    QLabel *EX_MEM_RD2;
    QLabel *EX_MEM_OP;
    QLabel *WriteReg;
    QLabel *MEM_WB_ALU;
    QLabel *MemData;
    QLabel *MEM_WB_WriteReg;
    QLabel *MEM_WB_OP;
    QPushButton *autoButton;
    QPushButton *resetButton;
    QComboBox *programSelector;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1239, 672);
        MainWindow->setMaximumSize(QSize(1239, 672));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stepButton = new QPushButton(centralwidget);
        stepButton->setObjectName("stepButton");
        stepButton->setGeometry(QRect(860, 480, 171, 41));
        cycleLabel = new QLabel(centralwidget);
        cycleLabel->setObjectName("cycleLabel");
        cycleLabel->setGeometry(QRect(1000, 440, 101, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        cycleLabel->setFont(font);
        instrList = new QListWidget(centralwidget);
        instrList->setObjectName("instrList");
        instrList->setGeometry(QRect(10, 10, 256, 611));
        regTable = new QTableWidget(centralwidget);
        regTable->setObjectName("regTable");
        regTable->setGeometry(QRect(280, 430, 281, 192));
        memTable = new QTableWidget(centralwidget);
        memTable->setObjectName("memTable");
        memTable->setGeometry(QRect(570, 430, 281, 192));
        pipelineLabel = new QLabel(centralwidget);
        pipelineLabel->setObjectName("pipelineLabel");
        pipelineLabel->setGeometry(QRect(282, 19, 941, 401));
        pipelineLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/pipeline.png")));
        pipelineLabel->setScaledContents(true);
        IF_ID_PC = new QLabel(centralwidget);
        IF_ID_PC->setObjectName("IF_ID_PC");
        IF_ID_PC->setGeometry(QRect(439, 78, 37, 41));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        IF_ID_PC->setFont(font1);
        IF_ID_PC->setAutoFillBackground(false);
        IF_ID_PC->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        IF_ID_PC->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Instruction = new VerticalLabel(centralwidget);
        Instruction->setObjectName("Instruction");
        Instruction->setGeometry(QRect(439, 135, 37, 180));
        QFont font2;
        font2.setPointSize(7);
        font2.setBold(true);
        Instruction->setFont(font2);
        Instruction->setAutoFillBackground(false);
        Instruction->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        Instruction->setFrameShape(QFrame::Shape::NoFrame);
        Instruction->setAlignment(Qt::AlignmentFlag::AlignCenter);
        ID_EX_PC = new QLabel(centralwidget);
        ID_EX_PC->setObjectName("ID_EX_PC");
        ID_EX_PC->setGeometry(QRect(674, 80, 37, 41));
        ID_EX_PC->setFont(font1);
        ID_EX_PC->setAutoFillBackground(false);
        ID_EX_PC->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        ID_EX_PC->setAlignment(Qt::AlignmentFlag::AlignCenter);
        RD1 = new QLabel(centralwidget);
        RD1->setObjectName("RD1");
        RD1->setGeometry(QRect(674, 170, 37, 41));
        RD1->setFont(font2);
        RD1->setAutoFillBackground(false);
        RD1->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        RD1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        RD2 = new QLabel(centralwidget);
        RD2->setObjectName("RD2");
        RD2->setGeometry(QRect(674, 220, 37, 41));
        RD2->setFont(font2);
        RD2->setAutoFillBackground(false);
        RD2->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        RD2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Imm = new QLabel(centralwidget);
        Imm->setObjectName("Imm");
        Imm->setGeometry(QRect(674, 276, 37, 32));
        Imm->setFont(font2);
        Imm->setAutoFillBackground(false);
        Imm->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        Imm->setAlignment(Qt::AlignmentFlag::AlignCenter);
        dest = new QLabel(centralwidget);
        dest->setObjectName("dest");
        dest->setGeometry(QRect(674, 325, 37, 32));
        dest->setFont(font1);
        dest->setAutoFillBackground(false);
        dest->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        dest->setAlignment(Qt::AlignmentFlag::AlignCenter);
        ID_EX_OP = new QLabel(centralwidget);
        ID_EX_OP->setObjectName("ID_EX_OP");
        ID_EX_OP->setGeometry(QRect(674, 364, 37, 30));
        ID_EX_OP->setFont(font1);
        ID_EX_OP->setAutoFillBackground(false);
        ID_EX_OP->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        ID_EX_OP->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Address = new QLabel(centralwidget);
        Address->setObjectName("Address");
        Address->setGeometry(QRect(885, 58, 37, 41));
        Address->setFont(font1);
        Address->setAutoFillBackground(false);
        Address->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        Address->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Zero = new QLabel(centralwidget);
        Zero->setObjectName("Zero");
        Zero->setGeometry(QRect(885, 142, 37, 41));
        Zero->setFont(font1);
        Zero->setAutoFillBackground(false);
        Zero->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        Zero->setAlignment(Qt::AlignmentFlag::AlignCenter);
        ALURes = new QLabel(centralwidget);
        ALURes->setObjectName("ALURes");
        ALURes->setGeometry(QRect(885, 202, 37, 41));
        ALURes->setFont(font2);
        ALURes->setAutoFillBackground(false);
        ALURes->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        ALURes->setAlignment(Qt::AlignmentFlag::AlignCenter);
        EX_MEM_RD2 = new QLabel(centralwidget);
        EX_MEM_RD2->setObjectName("EX_MEM_RD2");
        EX_MEM_RD2->setGeometry(QRect(885, 288, 37, 32));
        EX_MEM_RD2->setFont(font2);
        EX_MEM_RD2->setAutoFillBackground(false);
        EX_MEM_RD2->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        EX_MEM_RD2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        EX_MEM_OP = new QLabel(centralwidget);
        EX_MEM_OP->setObjectName("EX_MEM_OP");
        EX_MEM_OP->setGeometry(QRect(885, 364, 37, 30));
        EX_MEM_OP->setFont(font1);
        EX_MEM_OP->setAutoFillBackground(false);
        EX_MEM_OP->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        EX_MEM_OP->setAlignment(Qt::AlignmentFlag::AlignCenter);
        WriteReg = new QLabel(centralwidget);
        WriteReg->setObjectName("WriteReg");
        WriteReg->setGeometry(QRect(885, 325, 37, 32));
        WriteReg->setFont(font1);
        WriteReg->setAutoFillBackground(false);
        WriteReg->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        WriteReg->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MEM_WB_ALU = new QLabel(centralwidget);
        MEM_WB_ALU->setObjectName("MEM_WB_ALU");
        MEM_WB_ALU->setGeometry(QRect(1089, 165, 37, 30));
        MEM_WB_ALU->setFont(font2);
        MEM_WB_ALU->setAutoFillBackground(false);
        MEM_WB_ALU->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        MEM_WB_ALU->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MemData = new QLabel(centralwidget);
        MemData->setObjectName("MemData");
        MemData->setGeometry(QRect(1089, 202, 37, 41));
        MemData->setFont(font2);
        MemData->setAutoFillBackground(false);
        MemData->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        MemData->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MEM_WB_WriteReg = new QLabel(centralwidget);
        MEM_WB_WriteReg->setObjectName("MEM_WB_WriteReg");
        MEM_WB_WriteReg->setGeometry(QRect(1089, 327, 37, 30));
        MEM_WB_WriteReg->setFont(font1);
        MEM_WB_WriteReg->setAutoFillBackground(false);
        MEM_WB_WriteReg->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        MEM_WB_WriteReg->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MEM_WB_OP = new QLabel(centralwidget);
        MEM_WB_OP->setObjectName("MEM_WB_OP");
        MEM_WB_OP->setGeometry(QRect(1089, 364, 37, 30));
        MEM_WB_OP->setFont(font1);
        MEM_WB_OP->setAutoFillBackground(false);
        MEM_WB_OP->setStyleSheet(QString::fromUtf8("color: black;  \n"
"background-color: rgb(240, 240, 240);"));
        MEM_WB_OP->setAlignment(Qt::AlignmentFlag::AlignCenter);
        autoButton = new QPushButton(centralwidget);
        autoButton->setObjectName("autoButton");
        autoButton->setGeometry(QRect(860, 530, 171, 41));
        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(860, 580, 171, 41));
        programSelector = new QComboBox(centralwidget);
        programSelector->addItem(QString());
        programSelector->addItem(QString());
        programSelector->setObjectName("programSelector");
        programSelector->setGeometry(QRect(1050, 480, 171, 41));
        programSelector->setInsertPolicy(QComboBox::InsertPolicy::InsertAtCurrent);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1239, 25));
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
        stepButton->setText(QCoreApplication::translate("MainWindow", "Step", nullptr));
        cycleLabel->setText(QCoreApplication::translate("MainWindow", "Cycle: 0", nullptr));
        pipelineLabel->setText(QString());
        IF_ID_PC->setText(QString());
        Instruction->setText(QString());
        ID_EX_PC->setText(QString());
        RD1->setText(QString());
        RD2->setText(QString());
        Imm->setText(QString());
        dest->setText(QString());
        ID_EX_OP->setText(QString());
        Address->setText(QString());
        Zero->setText(QString());
        ALURes->setText(QString());
        EX_MEM_RD2->setText(QString());
        EX_MEM_OP->setText(QString());
        WriteReg->setText(QString());
        MEM_WB_ALU->setText(QString());
        MemData->setText(QString());
        MEM_WB_WriteReg->setText(QString());
        MEM_WB_OP->setText(QString());
        autoButton->setText(QCoreApplication::translate("MainWindow", "Auto", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        programSelector->setItemText(0, QCoreApplication::translate("MainWindow", "Instructions 1", nullptr));
        programSelector->setItemText(1, QCoreApplication::translate("MainWindow", "Instructions 2", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
