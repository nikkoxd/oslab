#include "visualizationwindow.h"
#include "carryworker.h"
#include "sumworker.h"
#include "ui_visualizationwindow.h"
#include <QtConcurrent/QtConcurrent>

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
  connect(sumWorker, &SumWorker::sumUpdated, this, [this](int sum) {
      this->sum = sum;
  });

  CarryWorker *carryWorker = new CarryWorker(firstNumString, secondNumString, i);
  connect(carryWorker, &CarryWorker::carryUpdated, this, [this](int carry) {
      this->carry = carry;
  });

  sumWorker->start();
  carryWorker->start();

  sumWorker->wait();
  carryWorker->wait();

  check_for_prev_carry();
  set_text();

  i--;
}
