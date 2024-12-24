#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "visualizationwindow.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QRegularExpressionValidator *binaryValidator =
      new QRegularExpressionValidator(QRegularExpression("[01]+"));

  ui->firstNumBox->setValidator(binaryValidator);
  ui->secondNumBox->setValidator(binaryValidator);
}

MainWindow::~MainWindow() { delete ui; }

QString firstNum, secondNum;

void MainWindow::on_submitButton_clicked()
{
  firstNum = ui->firstNumBox->text();
  secondNum = ui->secondNumBox->text();

  VisualizationWindow *v = new VisualizationWindow(this, firstNum, secondNum);
  v->show();
}
