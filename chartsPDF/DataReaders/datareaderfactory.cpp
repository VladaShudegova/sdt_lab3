#include "datareaderfactory.h"

DataReaderFactory::DataReaderFactory() {}

shared_ptr<IDataReader> DataReaderFactory::getReader(const QString type) const
{
    if(type == "json")
    {
        return make_shared<JSONDataReader>();
    }
    else if(type == "sqlite")
    {
        return make_shared<SQLLiteDataReader>();
    }
}
