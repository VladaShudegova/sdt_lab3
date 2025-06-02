#ifndef DATAREADERFACTORY_H
#define DATAREADERFACTORY_H

#include <memory>
#include "idatareader.h"
#include "jsondatareader.h"
#include "sqllitedatareader.h"

using std::shared_ptr;
using std::make_shared;

class DataReaderFactory
{
public:
    DataReaderFactory();
    shared_ptr<IDataReader> getReader(const QString type) const;
};

#endif // DATAREADERFACTORY_H
