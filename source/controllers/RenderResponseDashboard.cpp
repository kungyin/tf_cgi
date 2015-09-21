#include <TAppSettings>
#include <TWebApplication>
#include <QDir>

#include "RenderResponseDashboard.h"

RenderResponseDashboard::RenderResponseDashboard(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseDashboard::~RenderResponseDashboard() {
}

void RenderResponseDashboard::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_GET_DEVICE_DETAIL_INFO:
        generateGetDeviceDetailInfo();
        break;

    default:
        break;
    }

}

void RenderResponseDashboard::generateGetDeviceDetailInfo() {
    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_device_detail_info", true, ";");

    QDomElement root = doc.createElement("device_info");
    doc.appendChild(root);

    QDir dir(sessionDirPath());
    QDir::Filters filters = QDir::Files;
    QFileInfoList fileList = dir.entryInfoList(filters);

    QSet<QString> usersSet;
    QListIterator<QFileInfo> iter(fileList);
    while (iter.hasNext()) {
        QFileInfo entry = iter.next();
        if(entry.fileName().length() == 40) {
            usersSet.insert(find(entry.fileName().toLocal8Bit()).value("user").toString());
        }
    }

    QString users;
    for(QString e : usersSet) {
        QString split;
        if(!users.isEmpty())
            split = ",";
        users += split + e;
    }

    QStringList deviceInfoContentElement(QStringList()
            << "hostname" << "modelname" << "fanspeed" << "high_speed_temp"
            << "low_speed_temp" << "onlineuser" << "bonding_enable"
            << "lan_r_speed" << "lan_t_speed" << "lan2_r_speed" << "lan2_t_speed"
            << "mem_total" << "mem_free" << "buffers" << "cached" << "cpu");

    if( deviceInfoContentElement.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {
            QDomElement element = doc.createElement(deviceInfoContentElement.value(i));
            root.appendChild(element);
            if(i == 5)
                element.appendChild(doc.createTextNode(users));
            else
                element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseSysStatus::generateGetDeviceDetailInfo() :"
               "deviceInfoContentElement size is not equal to apiOut size.");
    }

    m_var = doc.toString();
}

TSession RenderResponseDashboard::find(const QByteArray &id)
{
    QFileInfo fi(sessionDirPath() + id);

    if (fi.exists()) {
        QFile file(fi.filePath());

        if (file.open(QIODevice::ReadOnly)) {
            QDataStream ds(&file);
            TSession result(id);
            ds >> *static_cast<QVariantMap *>(&result);
            if (ds.status() == QDataStream::Ok)
                return result;
        }
    }
    return TSession();
}

QString RenderResponseDashboard::sessionDirPath()
{
    return Tf::app()->tmpPath() + QLatin1String("session") + QDir::separator();
}
