#ifndef DATAREADERFACTORY_H
#define DATAREADERFACTORY_H

#include <memory>
#include "idatareader.h"
#include "jsondatareader.h"
#include "sqllitedatareader.h"

using std::shared_ptr;
using std::make_shared;


class DataReaderFactory {
private:
    using CreatorFunc = std::function<std::shared_ptr<IDataReader>()>;
    std::unordered_map<QString, CreatorFunc> creators;

public:
    template<typename T>
    void registerReader(const QString& type) {
        creators[type] = []() { return std::make_shared<T>(); };
    }

    DataReaderFactory();

    std::shared_ptr<IDataReader> getReader(const QString& type) const;
};

#endif // DATAREADERFACTORY_H
