#ifndef DATABASEOBJECT
#define DATABASEOBJECT

#include <TActionController>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

enum DB_TYPE
{
    DB_TYPE_SYSLOG,
    DB_TYPE_MULTI_MEDIA
};

class T_CONTROLLER_EXPORT DbDataProvider
{
public:
    DbDataProvider(DB_TYPE db_type = DB_TYPE_SYSLOG);
    ~DbDataProvider();

    void SetDatabase();
    void SetDatabase(QString database);
    virtual QSqlError SelectData(QString selected, QString condition, QString order_name, QString order, QString limit);
    virtual QString DumpData(QString database, QString selected, QString condition, QString limit);
    virtual QSqlError UpdateData(int id, QString condition);
    virtual QSqlError InsertData(QString condition);
    virtual QSqlError DeleteData(int id);

    virtual int GetSize() = 0;
    virtual int GetIdAt(int i) = 0;
    virtual QString GetTitleAt(int i) = 0;
    virtual QString GetDataAt(int i) = 0;

    QSqlQuery *GetSelectedData() { return m_Query; }
    QSqlError ShowDatabases();
private:
    void DeleteSqlQuery();
    DB_TYPE m_DbType;
    QSqlDatabase m_Db;
    QSqlQuery *m_Query;
};

class T_CONTROLLER_EXPORT SyslogDbDataProvider : public DbDataProvider
{
public:
    SyslogDbDataProvider();
    ~SyslogDbDataProvider();

    QSqlError SelectDataFromPara(QString paraPage, QString paraRp, QString paraSortname, QString paraSortorder, QString paraQuery, QString paraQType,
                         QString paraField, QString paraUser, QString paraLogFile, QString paraDateFrom, QString paraDateTo, QString paraViewSeverity,
                         QString paraLogHost, QString paraLogFacility, QString paraLogApplication, QString paraKeyword);
    QSqlError SelectAllServerity(QString database);
    QSqlError SelectAllHost(QString database);
    QSqlError SelectAllFacility(QString database);
    QSqlError SelectAllApplication(QString database);
    QSqlError GetAllDatabase();
    QString DumpDataFromPara(QString paraLogFile, QString paraDateFrom, QString paraDateTo, QString paraViewSeverity, QString paraLogHost, QString paraLogFacility,
                         QString paraLogApplication, QString paraKeyword, QString paraRp);

    int GetSize() { if (GetSelectedData() != NULL && GetSelectedData()->isSelect()) return GetSelectedData()->size(); else return -1; }
    int GetIdAt(int i);
    QString GetTitleAt(int i);
    QString GetDataAt(int i);
};

#endif // DATABASEOBJECT

