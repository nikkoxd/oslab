#include "worker.h"

Worker::Worker(QString firstNumString, QString secondNumString, int startingPoint, QObject *parent) : firstNumString(firstNumString), secondNumString(secondNumString), i(startingPoint), QObject(parent) {}

void Worker::processNextStep()
{
  if (i == -1 && carry)
  {
    carryText[i + 1] = char('0' + carry);
    sumText[i + 1] = char('0' + 1);

    emit updateText(carryText, sumText);

    i--;
    return;
  }
  else if (i < 0)
  {
    return;
  }

  prev_carry = carry;

  set_sum();
  set_carry();
  check_for_prev_carry();

  emit updateText(carryText, sumText);

  i--;
}

void Worker::set_sum()
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

void Worker::set_carry()
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

void Worker::check_for_prev_carry()
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
