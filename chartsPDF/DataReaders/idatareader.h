#ifndef IDATAREADER_H
#define IDATAREADER_H

#include <QFileInfo>
#include <memory>

#include "ChartData/chartdata.h"

class IDataReader
{
public:
    virtual QList<Record> readData(const QFileInfo& file) const = 0;
};

#endif // IDATAREADER_H
