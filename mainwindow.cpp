#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionECO_2d_Solver_triggered()
{
    Eco2dSolverUI *eco_solver_window = new Eco2dSolverUI;
    eco_solver_window->show();
}
