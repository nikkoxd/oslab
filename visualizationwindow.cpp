#include "visualizationwindow.h"
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

void VisualizationWindow::set_sum()
{
  if (firstNumString[i] == '0' && secondNumString[i] == '0')
  {
    sum = 0;
  }
  else if (firstNumString[i] == '1' && secondNumString[i] == '1')
  {
    sum = 0;
  }
  else
  {
    sum = 1;
  }
}

void VisualizationWindow::set_carry()
{
  if (firstNumString[i] == '0' && secondNumString[i] == '0')
  {
    carry = 0;
  }
  else if (firstNumString[i] == '1' && secondNumString[i] == '1')
  {
    carry = 1;
  }
  else
  {
    carry = 0;
  }
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

  QThread *sumWorker = QThread::create([this]() { set_sum(); });
  QThread *carryWorker = QThread::create([this]() { set_carry(); });

  sumWorker->start();
  carryWorker->start();

  sumWorker->wait();
  carryWorker->wait();

  check_for_prev_carry();
  set_text();

  delete sumWorker;
  delete carryWorker;

  i--;
}
