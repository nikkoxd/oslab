#include "visualizationwindow.h"
#include "ui_visualizationwindow.h"
#include "worker.h"
#include <QThread>

VisualizationWindow::VisualizationWindow(QWidget *parent, QString firstNum,
                                         QString secondNum)
    : QMainWindow(parent), ui(new Ui::VisualizationWindow)
{
  ui->setupUi(this);

  ui->firstNum->setText(firstNum);
  ui->secondNum->setText(secondNum);

  worker = new Worker(firstNum, secondNum);
  workerThread = new QThread;
  worker->moveToThread(workerThread);

  connect(workerThread, &QThread::started, worker, &Worker::processNextStep);
  connect(worker, &Worker::updateText, this, &VisualizationWindow::set_text);
  connect(this, &VisualizationWindow::nextButtonClicked, worker,
          &Worker::processNextStep);
  connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
  connect(workerThread, &QThread::finished, workerThread,
          &QObject::deleteLater);

  workerThread->start();
}

VisualizationWindow::~VisualizationWindow() { delete ui; }

void VisualizationWindow::set_text(const QString &carryText,
                                   const QString &sumText)
{
  ui->carry->setText(carryText);
  ui->result->setText(sumText);
}

void VisualizationWindow::on_nextButton_clicked() { emit nextButtonClicked(); }
