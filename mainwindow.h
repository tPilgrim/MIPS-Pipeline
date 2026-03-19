#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cpu.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PipelineCPU cpu;

    void updateInstructionHighlight();
    void updateRegistersAndMemory();

    QTimer *autoTimer;
    bool autoRunning = false;

    void runOneCycle();
    void loadProgram(const QString& filename);

};
#endif // MAINWINDOW_H
