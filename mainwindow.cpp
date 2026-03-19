#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VerticalLabel.h"
#include <string>
#include <sstream>

std::string getOperation(const std::string& line) {
    std::istringstream iss(line);
    std::string label, op;

    if (std::getline(iss, label, ':')) {
        iss >> op;
    }

    return op;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    autoTimer = new QTimer(this);
    autoTimer->setInterval(1000);

    QPixmap pipelinePix("pipeline.png");
    ui->pipelineLabel->setPixmap(pipelinePix);
    ui->pipelineLabel->setAlignment(Qt::AlignCenter);

    ui->instrList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->instrList->setSelectionMode(QAbstractItemView::NoSelection);

    ui->programSelector->clear();

    ui->programSelector->addItem("Instructions 1", "instr1.txt");
    ui->programSelector->addItem("Instructions 2", "instr2.txt");

    updateRegistersAndMemory();

    for (const auto& line : cpu.asmLines) {
        ui->instrList->addItem(QString::fromStdString(line));
    }

    connect(ui->stepButton, &QPushButton::clicked, this, [&]() {
        runOneCycle();
    });

    connect(ui->autoButton, &QPushButton::clicked, this, [&]() {
        if (!autoRunning)
        {
            autoTimer->start();
            ui->autoButton->setText("Stop");
            ui->autoButton->setStyleSheet(
                "background-color: rgb(200, 50, 50);"
                "color: white;"
                "font-weight: bold;"
                );
            autoRunning = true;
        }
        else
        {
            autoTimer->stop();
            ui->autoButton->setText("Auto");
            ui->autoButton->setStyleSheet("");
            autoRunning = false;
        }
    });

    connect(autoTimer, &QTimer::timeout, this, [&]() {
        runOneCycle();
    });

    connect(ui->resetButton, &QPushButton::clicked, this, [&]() {
        autoTimer->stop();
        autoRunning = false;

        ui->autoButton->setText("Auto Run");
        ui->autoButton->setStyleSheet("");

        cpu.load("instr1.txt");

        ui->stepButton->setEnabled(true);
        ui->autoButton->setEnabled(true);

        ui->cycleLabel->setText("Cycle: 0");
        ui->IF_ID_PC->setText("");
        ui->Instruction->setText("");

        updateInstructionHighlight();
        updateRegistersAndMemory();
    });

    loadProgram(ui->programSelector->currentText());

    connect(ui->programSelector, &QComboBox::currentIndexChanged,
            this, [=](int index) {
                QString filename = ui->programSelector->itemData(index).toString();
                loadProgram(filename);
            });

    int index = ui->programSelector->currentIndex();
    QString filename = ui->programSelector->itemData(index).toString();
    loadProgram(filename);
}

void MainWindow::runOneCycle()
{
    bool stillRunning = cpu.step();

    if (!stillRunning)
    {
        autoTimer->stop();
        autoRunning = false;

        ui->stepButton->setEnabled(false);
        ui->autoButton->setEnabled(false);

        ui->autoButton->setText("Auto Run");
        ui->autoButton->setStyleSheet("");

        return;
    }

    ui->cycleLabel->setText("Cycle: " + QString::number(cpu.cycle));
    updateInstructionHighlight();
    updateRegistersAndMemory();

    if (cpu.IF_ID_Reg.valid)
    {
        ui->IF_ID_PC->setText(QString::number(cpu.IF_ID_Reg.PC));
        ui->Instruction->setText(QString::fromStdString(cpu.IF_ID_Reg.instr.to_string()));
    }
    else
    {
        ui->IF_ID_PC->clear();
        ui->Instruction->clear();
    }

    if (cpu.ID_EX_Reg.valid)
    {
        ui->ID_EX_PC->setText(QString::number(cpu.ID_EX_Reg.PC));
        ui->RD1->setText(QString::number(cpu.ID_EX_Reg.RD1.to_ulong()));
        ui->RD2->setText(QString::number(cpu.ID_EX_Reg.RD2.to_ulong()));
        ui->Imm->setText(QString::number(cpu.ID_EX_Reg.imm.to_ulong()));
        ui->dest->setText(QString::number(cpu.ID_EX_Reg.rd.to_ulong()));
        ui->ID_EX_OP->setText(
            QString::fromStdString(getOperation(cpu.asmLines[cpu.ID_EX_Reg.PC]))
            );
    }
    else
    {
        ui->ID_EX_PC->clear();
        ui->RD1->clear();
        ui->RD2->clear();
        ui->Imm->clear();
        ui->dest->clear();
        ui->ID_EX_OP->clear();
    }

    if (cpu.EX_MEM_Reg.valid)
    {
        if (cpu.EX_MEM_Reg.control.Branch && cpu.EX_MEM_Reg.Zero)
            ui->Address->setText(QString::number(cpu.EX_MEM_Reg.BranchAddress));
        else if (cpu.EX_MEM_Reg.control.Jump)
            ui->Address->setText(QString::number(cpu.EX_MEM_Reg.JumpAddress));
        else
            ui->Address->clear();

        ui->Zero->setText(QString::number(cpu.EX_MEM_Reg.Zero));
        ui->ALURes->setText(QString::number(cpu.EX_MEM_Reg.ALURes.to_ulong()));
        ui->EX_MEM_RD2->setText(QString::number(cpu.EX_MEM_Reg.RD2.to_ulong()));
        ui->WriteReg->setText(QString::number(cpu.EX_MEM_Reg.WriteReg.to_ulong()));
        ui->EX_MEM_OP->setText(
            QString::fromStdString(getOperation(cpu.asmLines[cpu.EX_MEM_Reg.PC]))
            );
    }
    else
    {
        ui->Address->clear();
        ui->Zero->clear();
        ui->ALURes->clear();
        ui->EX_MEM_RD2->clear();
        ui->WriteReg->clear();
        ui->EX_MEM_OP->clear();
    }

    if (cpu.MEM_WB_Reg.valid)
    {
        ui->MEM_WB_ALU->setText(QString::number(cpu.MEM_WB_Reg.ALURes.to_ulong()));
        ui->MemData->setText(QString::number(cpu.MEM_WB_Reg.MemData.to_ulong()));
        ui->MEM_WB_WriteReg->setText(QString::number(cpu.MEM_WB_Reg.WriteReg.to_ulong()));
        ui->MEM_WB_OP->setText(
            QString::fromStdString(getOperation(cpu.asmLines[cpu.MEM_WB_Reg.PC]))
            );
    }
    else
    {
        ui->MEM_WB_ALU->clear();
        ui->MemData->clear();
        ui->MEM_WB_WriteReg->clear();
        ui->MEM_WB_OP->clear();
    }
}

void MainWindow::updateInstructionHighlight()
{
    for (int i = 0; i < ui->instrList->count(); i++)
        ui->instrList->item(i)->setBackground(QBrush(Qt::NoBrush));

    auto color = [&](int idx, QColor c) {
        if (idx >= 0 && idx < ui->instrList->count())
            ui->instrList->item(idx)->setBackground(QBrush(c));
    };

    color(cpu.IF_PC, QColor(110, 207, 189));
    color(cpu.ID_PC, QColor(150, 186, 151));
    color(cpu.EX_PC, QColor(237, 208, 129));
    color(cpu.MEM_PC, QColor(120, 119, 145));
    color(cpu.WB_PC, QColor(243, 137, 182));
}

void MainWindow::updateRegistersAndMemory()
{
    int numRegs = 32;
    int numCols = 2;
    int numRows = (numRegs + numCols - 1) / numCols;

    ui->regTable->clear();
    ui->regTable->setRowCount(numRows);
    ui->regTable->setColumnCount(numCols * 2);
    ui->regTable->horizontalHeader()->setVisible(false);
    ui->regTable->verticalHeader()->setVisible(false);
    ui->regTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->regTable->setSelectionMode(QAbstractItemView::NoSelection);

    for (int i = 0; i < numRegs; ++i) {
        int col = i % numCols * 2;
        int row = i / numCols;
        ui->regTable->setItem(row, col, new QTableWidgetItem(QString("Reg[%1]").arg(i)));
        ui->regTable->setItem(row, col + 1, new QTableWidgetItem(QString::number(cpu.Regs[i].to_ulong())));
    }

    int numMem = 32;
    numRows = (numMem + numCols - 1) / numCols;

    ui->memTable->clear();
    ui->memTable->setRowCount(numRows);
    ui->memTable->setColumnCount(numCols * 2);
    ui->memTable->horizontalHeader()->setVisible(false);
    ui->memTable->verticalHeader()->setVisible(false);
    ui->memTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->memTable->setSelectionMode(QAbstractItemView::NoSelection);

    for (int i = 0; i < numMem; ++i) {
        int col = i % numCols * 2;
        int row = i / numCols;
        ui->memTable->setItem(row, col, new QTableWidgetItem(QString("Mem[%1]").arg(i)));
        ui->memTable->setItem(row, col + 1, new QTableWidgetItem(QString::number(cpu.Mem[i].to_ulong())));
    }

    for (int c = 0; c < ui->regTable->columnCount(); ++c)
        ui->regTable->setColumnWidth(c, 66);
    for (int r = 0; r < ui->regTable->rowCount(); ++r)
        ui->regTable->setRowHeight(r, 40);

    for (int c = 0; c < ui->memTable->columnCount(); ++c)
        ui->memTable->setColumnWidth(c, 66);
    for (int r = 0; r < ui->memTable->rowCount(); ++r)
        ui->memTable->setRowHeight(r, 40);
}

void MainWindow::loadProgram(const QString& filename)
{
    cpu.load(filename.toStdString());

    ui->cycleLabel->setText("Cycle: 0");

    ui->instrList->clear();
    for (const auto& line : cpu.asmLines)
        ui->instrList->addItem(QString::fromStdString(line));

    updateInstructionHighlight();
    updateRegistersAndMemory();

    ui->IF_ID_PC->clear();
    ui->Instruction->clear();

    ui->ID_EX_PC->clear();
    ui->RD1->clear();
    ui->RD2->clear();
    ui->Imm->clear();
    ui->dest->clear();
    ui->ID_EX_OP->clear();

    ui->Address->clear();
    ui->Zero->clear();
    ui->ALURes->clear();
    ui->EX_MEM_RD2->clear();
    ui->WriteReg->clear();
    ui->EX_MEM_OP->clear();

    ui->MEM_WB_ALU->clear();
    ui->MemData->clear();
    ui->MEM_WB_WriteReg->clear();
    ui->MEM_WB_OP->clear();

    ui->stepButton->setEnabled(true);
    ui->autoButton->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
