#ifndef SQLLITEDATAREADER_H
#define SQLLITEDATAREADER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QtSql>

#include "idatareader.h"

class SQLLiteDataReader : public IDataReader
{
public:
    virtual shared_ptr<QList<Record>> readData(const QFileInfo& fileInfo) const override;
};

#endif // SQLLITEDATAREADER_H
