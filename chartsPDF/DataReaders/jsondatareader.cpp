#include "jsondatareader.h"

shared_ptr<QList<Record>> JSONDataReader::readData(const QFileInfo &fileInfo) const
{
    shared_ptr<QList<Record>> data = make_shared<QList<Record>>();

    QFile file(fileInfo.absoluteFilePath());

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw QString("Error opening file");
    }

    QByteArray rawData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(rawData, &parseError);

    if(parseError.error != QJsonParseError::NoError)
    {
        throw QString("JSON parse error:" + parseError.errorString());
    }

    QJsonArray jsonArray = jsonDocument.array();

    QJsonObject firstItem = jsonArray.first().toObject();
    QStringList keys = firstItem.keys();


    for(const QJsonValue &value : jsonArray)
    {
        if(!value.isObject())
            continue;

        QJsonObject pair = value.toObject();

        QString dateString = pair.value(keys[0]).toString();

        qreal pairValue = pair.value(keys[1]).toDouble();
        QDateTime date = QDateTime::fromString(dateString, Qt::ISODate);

        if(!date.isValid() || !pairValue){
            throw QString("Not valid data");
        }

        data->append(qMakePair(date, pairValue));
    }

    return data;

}
