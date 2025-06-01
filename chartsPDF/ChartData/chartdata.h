#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <QPair>
#include <QDateTime>
#include <QList>
#include <QString>

typedef QPair<QDateTime, qreal> Record;

class ChartData
{
public:
    ChartData();

private:
    QList<Record>* data;
};

#endif // CHARTDATA_H
