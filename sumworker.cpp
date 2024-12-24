#include "sumworker.h"

SumWorker::SumWorker(QString firstNum, QString secondNum, int index)
    : firstNum(firstNum), secondNum(secondNum), i(index) {}

void SumWorker::run() 
{
  if (firstNum[0] == '0' && secondNum[0] == '0')
  {
    sum = 0;
  }
  else if (firstNum[0] == '1' && secondNum[0] == '1')
  {
    sum = 0;
  }
  else
  {
    sum = 1;
  }

  emit sumUpdated(sum);
}
