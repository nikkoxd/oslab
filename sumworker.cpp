#include "sumworker.h"

SumWorker::SumWorker(QString firstNum, QString secondNum, int index)
    : firstNum(firstNum), secondNum(secondNum), i(index) {}

void SumWorker::run() 
{
  if (firstNum[i] == '0' && secondNum[i] == '0')
  {
    sum = 0;
  }
  else if (firstNum[i] == '1' && secondNum[i] == '1')
  {
    sum = 0;
  }
  else
  {
    sum = 1;
  }

  emit sumUpdated(sum);
}
