#ifndef JSONDATAREADER_H
#define JSONDATAREADER_H

#include "idatareader.h"
#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

class JSONDataReader : public IDataReader
{
public:
    virtual shared_ptr<QList<Record>> readData(const QFileInfo& fileInfo) const override;
};

#endif // JSONDATAREADER_H
