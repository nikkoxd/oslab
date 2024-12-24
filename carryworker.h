#ifndef CARRYWORKER_H
#define CARRYWORKER_H

#include <QThread>

class CarryWorker : public QThread
{
  Q_OBJECT

private:
  QString firstNum;
  QString secondNum;
  int carry;
  int i;

public:
  CarryWorker(QString firstNum, QString secondNum, int index);

protected:
  void run() override;

signals:
  void carryUpdated(int);
};

#endif
