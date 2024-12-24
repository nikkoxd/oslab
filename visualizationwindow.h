#ifndef VISUALIZATIONWINDOW_H
#define VISUALIZATIONWINDOW_H

#include "worker.h"
#include <QMainWindow>
#include <QThread>

namespace Ui
{
class VisualizationWindow;
}

class VisualizationWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit VisualizationWindow(QWidget *parent = nullptr, QString firstNum = "",
                               QString secondNum = "");
  ~VisualizationWindow();

signals:
  void nextButtonClicked();

private slots:
  void set_text(const QString &carryText, const QString &sumText);
  void on_nextButton_clicked();

private:
  Ui::VisualizationWindow *ui;
  Worker *worker;
  QThread *workerThread;
};

#endif
