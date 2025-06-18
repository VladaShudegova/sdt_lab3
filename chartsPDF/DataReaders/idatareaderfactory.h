#ifndef IDATAREADERFACTORY_H
#define IDATAREADERFACTORY_H

class IDataReaderFactory
{
public:
    virtual ~IDataReaderFactory() = default;

    virtual std::shared_ptr<IDataReader> getReader(const QString& type) const = 0;
};

#endif // IDATAREADERFACTORY_H
