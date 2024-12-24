#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QString>

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(QString firstNumString, QString secondNumString, int startingPoint, QObject *parent = nullptr);

public slots:
    void processNextStep();

signals:
    void updateText(const QString &carryText, const QString &sumText);

private:
    void set_sum();
    void set_carry();
    void check_for_prev_carry();

    QString firstNumString;
    QString secondNumString;
    QString carryText = QString("%1").arg("", 7, ' ');
    QString sumText = QString("%1").arg("", 7, ' ');
    int i;
    int sum = 0;
    int carry = 0;
    int prev_carry = 0;
};

#endif

