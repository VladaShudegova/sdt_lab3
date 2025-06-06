#include "sqllitedatareader.h"

shared_ptr<QList<Record>> SQLLiteDataReader::readData(const QFileInfo &fileInfo) const
{
    shared_ptr<QList<Record>> data = make_shared<QList<Record>>();

    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(fileInfo.absoluteFilePath());
    dbase.setConnectOptions("QSQLITE_OPEN_READONLY");

    if(!dbase.open()) {
        throw QString("Cannot open SQLITE file: " + dbase.lastError().text());
    }

    QStringList tables = dbase.tables();
    if(tables.isEmpty()) {
        throw QString ("Warning: no tables in sqlite dbase");
    }
    QString tableName = tables.first();

    QSqlRecord record = dbase.record(tableName);

    if(record.count() < 2) {
        throw QString("SQLITE Not enough columns to build a graph");
    }

    QString col1 = record.fieldName(0), col2 = record.fieldName(1);
    QString queryString = QString("SELECT %1, %2 FROM %3")
                              .arg(col1, col2, tableName);
    QSqlQuery queryAllRecords(queryString);

    while(queryAllRecords.next())
    {
        QDateTime dataTime = QDateTime::fromString(queryAllRecords.value(col1).toString(), "dd.MM.yyyy HH:mm");
        qreal value = queryAllRecords.value(col2).toReal();
        if(!dataTime.isValid() ){
            throw QString("Not valid date");
        }

        data->append(qMakePair(dataTime, value));
    }

    return data;
}
