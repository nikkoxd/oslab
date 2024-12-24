#include "carryworker.h"

CarryWorker::CarryWorker(QString firstNum, QString secondNum, int index)
    : firstNum(firstNum), secondNum(secondNum), i(index) {}

void CarryWorker::run() 
{
  if (firstNum[0] == '0' && secondNum[0] == '0')
  {
    carry = 0;
  }
  else if (firstNum[0] == '1' && secondNum[0] == '1')
  {
    carry = 1;
  }
  else
  {
    carry = 0;
  }

  emit carryUpdated(carry);
}
