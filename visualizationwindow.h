#ifndef VISUALIZATIONWINDOW_H
#define VISUALIZATIONWINDOW_H

#include <QMainWindow>

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

private slots:
  void on_nextButton_clicked();

private:
  QString firstNumString;
  QString secondNumString;
  QString carryText = QString("%1").arg("", 7, ' ');
  QString sumText = QString("%1").arg("", 7, ' ');
  int i;
  int sum = 0, carry = 0, prev_carry = 0;

  void set_text();
  void set_sum();
  void set_carry();
  void check_for_prev_carry();
  Ui::VisualizationWindow *ui;
};

#endif // VISUALIZATIONWINDOW_H
