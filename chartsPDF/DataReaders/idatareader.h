#ifndef IDATAREADER_H
#define IDATAREADER_H

#include <QFileInfo>
#include <memory>

using std::shared_ptr;
using std::make_shared;

#include "ChartData/chartdata.h"


class IDataReader
{
public:
    virtual shared_ptr<QList<Record>> readData(const QFileInfo& file) const = 0;
};

#endif // IDATAREADER_H
