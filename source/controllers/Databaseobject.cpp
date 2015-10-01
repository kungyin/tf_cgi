#include <QProcess>
#include "Databaseobject.h"

DbDataProvider::DbDataProvider(DB_TYPE db_type)
{
    m_DbType = db_type;
    if (QSqlDatabase::database("mysql_connection_1").isValid())
        m_Db = QSqlDatabase::database("mysql_connection_1");
    else
        m_Db = QSqlDatabase::addDatabase("QMYSQL", "mysql_connection_1");
    if (m_Db.isOpen()) m_Db.close();
    m_Db.setHostName("127.0.0.1");
    m_Db.setUserName("root");
#ifdef SIMULATOR_MODE
    m_Db.setPassword("00000000");
#else
    m_Db.setConnectOptions("UNIX_SOCKET=/tmp/mysqld.sock");
#endif
    m_Query = NULL;
    SetDatabase();
}

DbDataProvider::~DbDataProvider()
{
    DeleteSqlQuery();
    if (m_Db.isOpen())
        m_Db.close();
    QSqlDatabase::removeDatabase("mysql_connection_1");
}

void DbDataProvider::SetDatabase()
{
    if (m_DbType == DB_TYPE_SYSLOG)
        m_Db.setDatabaseName("Syslog");
    else
        m_Db.setDatabaseName("dlink_nas");
}

void DbDataProvider::SetDatabase(QString database)
{
    if (m_Db.isOpen()) m_Db.close();
    m_Db.setDatabaseName(database);
}

void DbDataProvider::DeleteSqlQuery()
{
    if (m_Query != NULL)
    {
        if (m_Query->isSelect()) m_Query->clear();
        delete m_Query;
        m_Query = NULL;
    }
}

QSqlError DbDataProvider::SelectData(QString selected, QString condition, QString order_name, QString order, QString limit, QString table)
{
    if (!m_Db.isOpen()) m_Db.open();
    DeleteSqlQuery();
    m_Query = new QSqlQuery(m_Db);
    QString sql = QString("select %1 from %2 %3 %4 %5 %6").arg(selected, (m_DbType == DB_TYPE_SYSLOG)?"SystemEvents":table, ((condition.length() > 0)?condition:""), ((order_name.length() > 0)?"order by " + order_name:""), order, limit);
    m_Query->prepare(sql);
    if (!m_Query->exec()) return m_Query->lastError();
    return m_Db.lastError();
}

int DbDataProvider::GetTotalSize(QString condition, QString table)
{
    int ret = 0;
    if (!m_Db.isOpen()) m_Db.open();
    QSqlQuery q(m_Db);
    QString sql = QString("select count(*) as a from %1 %2").arg((m_DbType == DB_TYPE_SYSLOG)?"SystemEvents":table, ((condition.length() > 0)?condition:""));
    q.prepare(sql);
    if (q.exec() && q.next())
        ret = q.value("a").toInt();
    m_Db.close();
    return ret;
}

QString DbDataProvider::DumpData(QString database, QString selected, QString condition, QString limit)
{
    QProcess process, processZip;
    process.start("date +\"%Y%m%d_%H%M%S\"");
    process.waitForFinished();
    QString out = QString(process.readAllStandardOutput());
    QString fileName = QString("%1%2").arg(database, out.split("\n").at(0));
    QString filePath = QString("%1.csv").arg(fileName);
    QString zipPath = QString("%1.zip").arg(fileName);
    QString args = QString("mysql -hlocalhost -uroot -e\"select %1 from %2.%3%4 %5\" --batch --silent").arg(selected, database, (m_DbType == DB_TYPE_SYSLOG)?"SystemEvents":"tbl_files", ((condition.length() > 0)?" " + condition:""), limit);
#ifdef SIMULATOR_MODE
    args.append(" -p00000000");
#endif
    process.setStandardOutputFile(filePath);
    process.start(args);
    process.waitForFinished();
    QString zipArgs = QString("zip %1 %2").arg(fileName, filePath);
    processZip.start(zipArgs);
    processZip.waitForFinished();
    QString rmArgs = QString("rm %1").arg(filePath);
    processZip.start(rmArgs);
    processZip.waitForFinished();
    return zipPath;
}

QSqlError DbDataProvider::UpdateData(int id, QString condition)
{
    return m_Query->lastError();
}

QSqlError DbDataProvider::InsertData(QString condition)
{
    return m_Query->lastError();
}

QSqlError DbDataProvider::DeleteData(int id)
{
    return m_Query->lastError();
}

QSqlError DbDataProvider::ShowDatabases()
{
    if (!m_Db.isOpen()) m_Db.open();
    DeleteSqlQuery();
    m_Query = new QSqlQuery(m_Db);
    QString sql = "show databases";
    m_Query->prepare(sql);
    if (!m_Query->exec()) return m_Query->lastError();
    return m_Db.lastError();
}

SyslogDbDataProvider::SyslogDbDataProvider()
    : DbDataProvider(DB_TYPE_SYSLOG)
{

}

QSqlError SyslogDbDataProvider::SelectDataFromPara(QString paraPage, QString paraRp, QString paraSortname, QString paraSortorder, QString paraQuery, QString paraQType,
                     QString paraField, QString paraUser, QString paraLogFile, QString paraDateFrom, QString paraDateTo, QString paraViewSeverity,
                     QString paraLogHost, QString paraLogFacility, QString paraLogApplication, QString paraKeyword, int *totalCnt)
{
    QString condition = "where ", limit = "";
    if (!paraLogFile.isNull() && !paraLogFile.isEmpty()) DbDataProvider::SetDatabase(paraLogFile);
    condition += ((!paraDateFrom.isEmpty())?"(DeviceReportedTime >='" + paraDateFrom + "'":"");
    if (!paraDateTo.isEmpty())
    {
        if (!paraDateFrom.isEmpty()) condition += " and";
        condition += (" DeviceReportedTime < '" + paraDateTo + "'");
    }
    if (!paraDateFrom.isEmpty()) condition += ")";
    if (!paraViewSeverity.isEmpty() && paraViewSeverity.compare("any", Qt::CaseInsensitive) != 0)
    {
        if (!condition.isEmpty() && condition.length() > 7) condition += " and";
        condition += (" Priority=" + paraViewSeverity);
    }
    if (!paraLogFacility.isEmpty() && paraLogFacility.compare("any", Qt::CaseInsensitive) != 0)
    {
        if (!condition.isEmpty() && condition.length() > 7) condition += " and";
        condition += (" Facility=" + paraLogFacility);
    }
    if (!paraLogHost.isEmpty() && paraLogHost.compare("any", Qt::CaseInsensitive) != 0)
    {
        if (!condition.isEmpty() && condition.length() > 7) condition += " and";
        condition += (" FromHost='" + paraLogHost + "'");
    }
    if (!paraLogApplication.isEmpty() && paraLogApplication.compare("any", Qt::CaseInsensitive) != 0)
    {
        if (!condition.isEmpty() && condition.length() > 7) condition += " and";
        condition += (" SysLogTag='" + paraLogApplication + "'");
    }
    if (!paraKeyword.isEmpty())
    {
        if (!condition.isEmpty() && condition.length() > 7) condition += " and";
        condition += (" Message like '%" + paraKeyword + "%'");
    }
    if (!paraPage.isEmpty() && paraRp.length() > 0)
    {
        int offset = (paraPage.toInt() - 1) * paraRp.toInt();
        limit = QString("limit %1,%2 ").arg(QString::number(offset), paraRp);
    }
    *totalCnt = DbDataProvider::GetTotalSize((condition.length() > 7)?condition:"");
    return DbDataProvider::SelectData("*", (condition.length() > 7)?condition:"", paraSortname, paraSortorder, limit);
}

QString SyslogDbDataProvider::DumpDataFromPara(QString paraLogFile, QString paraDateFrom, QString paraDateTo, QString paraViewSeverity, QString paraLogHost, QString paraLogFacility,
                     QString paraLogApplication, QString paraKeyword, QString paraRp)
{
    QString condition = "where ", limit = "";
    condition += ((!paraDateFrom.isEmpty())?"(DeviceReportedTime >='" + paraDateFrom + "'":"");
    if (!paraDateTo.isEmpty())
    {
        if (!paraDateFrom.isEmpty()) condition += " and";
        condition += (" DeviceReportedTime < '" + paraDateTo + "'");
    }
    if (!paraDateFrom.isEmpty()) condition += ")";
    if (!paraViewSeverity.isEmpty() && paraViewSeverity.compare("any", Qt::CaseInsensitive) != 0)
    {
        if (!condition.isEmpty() && condition.length() > 7) condition += " and";
        condition += (" Priority=" + paraViewSeverity);
    }
    if (!paraLogFacility.isEmpty() && paraLogFacility.compare("any", Qt::CaseInsensitive) != 0)
    {
        if (!condition.isEmpty() && condition.length() > 7) condition += " and";
        condition += (" Facility=" + paraLogFacility);
    }
    if (!paraLogHost.isEmpty() && paraLogHost.compare("any", Qt::CaseInsensitive) != 0)
    {
        if (!condition.isEmpty() && condition.length() > 7) condition += " and";
        condition += (" FromHost='" + paraLogHost + "'");
    }
    if (!paraLogApplication.isEmpty() && paraLogApplication.compare("any", Qt::CaseInsensitive) != 0)
    {
        if (!condition.isEmpty() && condition.length() > 7) condition += " and";
        condition += (" SysLogTag='" + paraLogApplication + "'");
    }
    if (!paraKeyword.isEmpty())
    {
        if (!condition.isEmpty() && condition.length() > 7) condition += " and";
        condition += (" Message like '%" + paraKeyword + "%'");
    }
    if (!paraRp.isEmpty() && paraRp.length() > 0)
    {
        limit = QString("limit %1").arg(paraRp);
    }
    return DbDataProvider::DumpData(paraLogFile, "*", (condition.length() > 7)?condition:"", limit);
}

QSqlError SyslogDbDataProvider::SelectAllServerity(QString database)
{
    if (!database.isNull() && !database.isEmpty()) DbDataProvider::SetDatabase(database);
    return DbDataProvider::SelectData("priority", "group by priority", "priority", "", "");
}

QSqlError SyslogDbDataProvider::SelectAllHost(QString database)
{
    if (!database.isNull() && !database.isEmpty()) DbDataProvider::SetDatabase(database);
    return DbDataProvider::SelectData("FromHost", "group by FromHost", "FromHost", "", "");
}

QSqlError SyslogDbDataProvider::SelectAllFacility(QString database)
{
    if (!database.isNull() && !database.isEmpty()) DbDataProvider::SetDatabase(database);
    return DbDataProvider::SelectData("facility", "group by facility", "facility", "", "");
}

QSqlError SyslogDbDataProvider::SelectAllApplication(QString database)
{
    if (!database.isNull() && !database.isEmpty()) DbDataProvider::SetDatabase(database);
    return DbDataProvider::SelectData("SysLogTag", "group by SysLogTag", "SysLogTag", "", "");
}

QSqlError SyslogDbDataProvider::GetAllDatabase()
{
    return DbDataProvider::ShowDatabases();
}

MediaDbDataProvider::MediaDbDataProvider()
    : DbDataProvider(DB_TYPE_MULTI_MEDIA)
{

}

QSqlError MediaDbDataProvider::SelectFolderList(QString paraPage, QString paraRp, int *totalCnt)
{
    QString limit = "";
    if (!paraPage.isEmpty() && paraRp.length() > 0)
    {
        int offset = (paraPage.toInt() - 1) * paraRp.toInt();
        limit = QString("limit %1,%2 ").arg(QString::number(offset), paraRp);
    }
    *totalCnt = DbDataProvider::GetTotalSize("", "tbl_multimedia_folder");
    return DbDataProvider::SelectData("*", "", "", "", limit, "tbl_multimedia_folder");
}

QSqlError MediaDbDataProvider::GetServerStatus(int *status)
{
    *status = 0;
    if (!m_Db.isOpen()) m_Db.open();
    QString sql = "select * from tbl_multimedia_folder where scan_status='pause'";
    QSqlQuery q(m_Db);
    q.prepare(sql);
    if (q.exec() && q.size() > 0) *status = 3;
    if (*status == 0)
    {
        sql = "select * from tbl_multimedia_folder where scan_status='stop'";
        q.clear();
        q.prepare(sql);
        if (q.exec() && q.size() > 0) *status = 2;
    }
    if (*status == 0)
    {
        sql = "select * from tbl_multimedia_folder where scan_status='scan'";
        q.clear();
        q.prepare(sql);
        if (q.exec() && q.size() > 0) *status = 1;
    }
    m_Db.close();
    return m_Db.lastError();
}

QSqlError MediaDbDataProvider::GetPercentAndFile(int *percent, QString *filePath)
{
    if (!m_Db.isOpen()) m_Db.open();
    QString sql = "select * from tbl_multimedia_folder where scan_status='scan' or scan_status='finish'";
    QSqlQuery q(m_Db);
    q.prepare(sql);
    if (q.exec() && q.size() <= 0)
    {
        *percent = 100;
        q.clear();
        if (m_Db.isOpen()) m_Db.close();
        *filePath = "finish";
        return m_Db.lastError();
    }
    sql = "select floor(sum(current_file_count)*100/sum(pre_file_count)) as a from tbl_multimedia_folder where scan_status='scan' or scan_status='finish'";
    q.prepare(sql);
    if (q.exec() && q.size() > 0 && q.next()) *percent = q.value("a").toInt();
    sql = "select current_scan_file from tbl_multimedia_folder where scan_status='scan' limit 1";
    q.clear();
    q.prepare(sql);
    if (q.exec() && q.size() > 0 && q.next()) *filePath = q.value("current_scan_file").toString();
    m_Db.close();
    return m_Db.lastError();
}

QStringList MediaDbDataProvider::GetFolderAll()
{
    QStringList list;
    if (!m_Db.isOpen()) m_Db.open();
    QSqlQuery q(m_Db);
    QString sql = "select folder_path from tbl_multimedia_folder";
    q.prepare(sql);
    if (!q.exec())
        qDebug() << q.lastError();
    if (q.size() > 0)
    {
        list.clear();
        while (q.next())
        {
            list.append(q.value("folder_path").toString());
        }
    }
    m_Db.close();
    return list;
}
