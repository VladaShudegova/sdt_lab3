#include "datareaderfactory.h"

DataReaderFactory::DataReaderFactory() {
    registerReader<JSONDataReader>("json");
    registerReader<SQLLiteDataReader>("sqlite");
}

std::shared_ptr<IDataReader> DataReaderFactory::getReader(const QString& type) const {
    auto it = DataReaderFactory::creators.find(type);
    if (it != DataReaderFactory::creators.end()) {
        return it->second();
    }
    return nullptr;
}
