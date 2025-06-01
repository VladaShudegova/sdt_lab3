#include "jsondatareader.h"

QList<Record> JSONDataReader::readData(const QFileInfo &fileInfo) const
{
    QList<Record> data;
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
        //throw QString("JSON parse error:" << parseError.errorString());
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

        data.append(qMakePair(date, pairValue));
    }

    for (const auto& pair : data) {
        qDebug() << pair.first.toString(Qt::ISODate) << "->" << pair.second;
    }

    return data;

}
