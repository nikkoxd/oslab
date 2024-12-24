#ifndef SUMWORKER_H
#define SUMWORKER_H

#include <QThread>

class SumWorker : public QThread
{
  Q_OBJECT

private:
  QString firstNum;
  QString secondNum;
  int sum;
  int i;

public:
  SumWorker(QString firstNum, QString secondNum, int index);

protected:
  void run() override;

signals:
  void sumUpdated(int);
};

#endif
