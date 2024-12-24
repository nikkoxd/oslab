#include "visualizationwindow.h"
#include "ui_visualizationwindow.h"
#include <QtConcurrent/QtConcurrent>
#include "carryworker.h"
#include "sumworker.h"

VisualizationWindow::VisualizationWindow(QWidget *parent, QString firstNum,
                                         QString secondNum)
    : QMainWindow(parent), ui(new Ui::VisualizationWindow)
{
  ui->setupUi(this);

  ui->firstNum->setText(firstNum);
  ui->secondNum->setText(secondNum);
  firstNumString = ui->firstNum->text();
  secondNumString = ui->secondNum->text();
  i = firstNum.size() - 1;
}

VisualizationWindow::~VisualizationWindow() 
{
  delete ui;
}

void VisualizationWindow::set_text()
{
  ui->carry->setText(carryText);
  ui->result->setText(sumText);
}

void VisualizationWindow::check_for_prev_carry()
{
  if (prev_carry)
  {
    sum = !sum;
    if (!sum)
    {
      carry = 1;
    }

    carryText[i + 1] = char('0' + prev_carry);
  }
  sumText[i + 1] = char('0' + sum);
}

void VisualizationWindow::set_sum(int sum)
{
  this->sum = sum;
}

void VisualizationWindow::set_carry(int carry)
{
  this->carry = carry;
}

void VisualizationWindow::on_nextButton_clicked()
{
  if (i == -1 && carry)
  {
    carryText[i + 1] = char('0' + carry);
    sumText[i + 1] = char('0' + 1);

    set_text();

    i--;
    return;
  }
  else if (i < 0)
  {
    return;
  }

  prev_carry = carry;

  SumWorker *sumWorker = new SumWorker(firstNumString, secondNumString, i);
  connect(sumWorker, &SumWorker::sumUpdated, this, &VisualizationWindow::set_sum);
  sumWorker->start();

  CarryWorker *carryWorker = new CarryWorker(firstNumString, secondNumString, i);
  connect(carryWorker, &CarryWorker::carryUpdated, this, &VisualizationWindow::set_carry);
  carryWorker->start();

  sumWorker->wait();
  carryWorker->wait();

  check_for_prev_carry();
  set_text();

  i--;
}
