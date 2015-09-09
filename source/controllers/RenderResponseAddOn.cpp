#include <QProcess>

#include "RenderResponseAddOn.h"

#include <QDir>
#include <QXmlStreamWriter>

RenderResponseAddOn::RenderResponseAddOn(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseAddOn::~RenderResponseAddOn() {
}

void RenderResponseAddOn::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_MODULE_SHOW_INSTALL_STATUS:
        generateModuleShowInstallStatus();
        break;
    case CMD_GET_ALLAPPS:
        generateGetAllApps();
        break;
    case CMD_GET_APKG_DETAIL:
        generateGetApkgDetail();
        break;
    case CMD_MYFAV_CHECK_IMG:
        generateMyFavCheckImg();
        break;
    case CMD_CHK_HDD_FREE_SIZE:
        generateChkHddFreeSize();
        break;
    case CMD_DOWNLOAD_INSTALL_ADDON:
        generateDownloadInstallAddOn();
        break;
    case CMD_CLEAR_ADDON_FILES:
        generateClearAddOnFiles();
        break;
    case CMD_MODULE_RE_INSTALL:
        generateModuleReInstall();
        break;
    case CMD_INSTALL_3_PARTY_APKG:
        generateInstall3PartyApkg();
        break;
    case CMD_UNINSTALL_ADDON:
        generateUninstallAddOn();
        break;
    case CMD_MODULE_ENABLE_DISABLE:
        generateModuleEnableDisable();
        break;
    case CMD_MODULE_UNINSTALL:
        generateModuleUninstall();
        break;
    case CMD_APP:
        generateApp();
        break;
    case CMD_APPLICATION_1ST:
        generateApplication1st();
        break;
    case CMD_MODULE_GET_ONE_INFO:
        generateModuleGetOneInfo();
        break;
	case CMD_MYFAV_SET:
        generateMyFavSet();
        break;
    case CMD_MYFAV_GET_SORT_INFO:
        generateMyFavGetSortInfo();

    default:
        break;
    }

}

void RenderResponseAddOn::generateModuleShowInstallStatus() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_show_install_status", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QStringList configContentElement(QStringList()
        << "install_type" << "install_status" << "install_error_mesg" << "install_filename");

    if( configContentElement.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {
            QDomElement element = doc.createElement(configContentElement.value(i));
            root.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseSysStatus::generateModuleShowInstallStatus(): "
               "configContentElement size is not equal to apiOut size.");
    }

    m_var = doc.toString();

}

void RenderResponseAddOn::generateGetAllApps() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " cgi_get_allapps", true, ";");

    QDomElement root = doc.createElement("allapps");
    doc.appendChild(root);

    QStringList allappsContentElement(QStringList()
        << "status" << "path" << "model");

    if( allappsContentElement.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {
            QDomElement element = doc.createElement(allappsContentElement.value(i));
            root.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseSysStatus::generateGetAllApps(): "
               "allappsContentElement size is not equal to apiOut size.");
    }
    m_var = doc.toString();

}

void RenderResponseAddOn::generateGetApkgDetail() {

    QDomDocument doc;

    QString xmlFile = QUrl::fromPercentEncoding(m_pReq->parameter("xml_path").toLocal8Bit());

    QFile file(xmlFile);
    if (file.open(QIODevice::ReadOnly)) {
        if (!doc.setContent(&file)) {
            tError("RenderResponseAddOn::generateGetApkgDetail(): file %s is not XML.",
                   xmlFile.toLocal8Bit().data());
        }
        file.close();
    }
    else
        tError("RenderResponseAddOn::generateGetApkgDetail(): file %s does not exist.",
               xmlFile.toLocal8Bit().data());

    m_var = doc.toString();

}

void RenderResponseAddOn::generateMyFavCheckImg() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " cgi_myfavorite_check_img " +
                                      allParametersToString(), true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAddOn::generateChkHddFreeSize() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " cgi_chk_hdd_free_size", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement hddFreeSizeElement = doc.createElement("hdd_free_size");
    root.appendChild(hddFreeSizeElement);
    hddFreeSizeElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement installPathElement = doc.createElement("install_path");
    root.appendChild(installPathElement);
    installPathElement.appendChild(doc.createTextNode(apiOut.value(1)));
    m_var = doc.toString();

}

void RenderResponseAddOn::generateDownloadInstallAddOn() {

    if(startDetached(API_PATH + SCRIPT_MANAGER_API, QStringList()
                                << "download_install_addon" << allParametersToString(false)))
        ;

}

void RenderResponseAddOn::generateClearAddOnFiles() {

    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " clear_addon_files " +
                                      allParametersToString(), true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement installStatusElement = doc.createElement("install_status");
    root.appendChild(installStatusElement);
    installStatusElement.appendChild(doc.createTextNode(apiOut.value(0)));
    if(apiOut.value(1) != "N/A") {
        QDomElement urlElement = doc.createElement("sc_url");
        root.appendChild(urlElement);
        urlElement.appendChild(doc.createTextNode(apiOut.value(1)));
    }

    m_var = doc.toString();

}

void RenderResponseAddOn::generateModuleReInstall() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_re_install " +
                                      allParametersToString(), true);

    m_var = "<script>location.href='/web/addon_center/installed.html'</script>";
}

void RenderResponseAddOn::generateInstall3PartyApkg() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " install_3_party_apkg " +
                                      allParametersToString(), true);

    m_var = "<script>location.href='/web/addon_center/installed.html?id=8401878'</script>";
}

void RenderResponseAddOn::generateUninstallAddOn() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " uninstall_addon " +
                                      allParametersToString(), true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement retElement = doc.createElement("ret");
    root.appendChild(retElement);
    retElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAddOn::generateModuleEnableDisable() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_enable_disable " +
                                      allParametersToString(), true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAddOn::generateModuleUninstall() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_uninstall " +
                                      allParametersToString(), true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement moduleNameElement = doc.createElement("module_name");
    root.appendChild(moduleNameElement);
    moduleNameElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(1)));

    m_var = doc.toString();

}

void RenderResponseAddOn::generateApp() {
    if(!m_pReq->multipartFormData().isEmpty()) {
        if(m_pReq->multipartFormData().renameUploadedFile("file", PACKAGE_FILE, true)) {
            m_var = "<script>location.href='/web/addon_center/installed.html?id=8401878'</script>";
        }
    }
}

void RenderResponseAddOn::generateApplication1st() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " cgi_application_lst");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QStringList itemTags(QStringList()
        << "status" << "ShowName" << "Enable" << "URL" << "User" << "Center"
                         << "Icon_Disable" << "Icon_MouseOver" << "Icon_MouseOut");

    for(int i = 0; i < apiOut.size(); i++) {
        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);
        if( itemTags.size() == apiOut.value(i).split(";").size() ) {

            for(int j = 0; j < apiOut.value(i).split(";").size(); j++) {
                QDomElement element = doc.createElement(itemTags.value(j));
                itemElement.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(j)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseSysStatus::generateApplication1st(): "
                   "itemTags size is not equal to apiOut size.");
        }
    }

    m_var = doc.toString();

}

void RenderResponseAddOn::generateModuleGetOneInfo() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_Get_One_Info " +
                                      allParametersToString(), true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QStringList itemTags(QStringList()
        << "path" << "version" << "date" << "apkg_status");

    QDomElement itemElement = doc.createElement("Item");
    root.appendChild(itemElement);

    if( itemTags.size() == apiOut.size()-1 ) {
        for(int i = 0; i < apiOut.size()-1; i++) {
            QDomElement element = doc.createElement(itemTags.value(i));
            itemElement.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseSysStatus::generateModuleGetOneInfo(): "
               "itemTags size is not equal to apiOut size.");
    }

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(4)));

    m_var = doc.toString();

}

void RenderResponseAddOn::generateMyFavSet()
{
    int res = 0, i = 0;
    QDomDocument doc;
    QString paraUser = m_pReq->parameter("f_user");
    int paraNum = m_pReq->parameter("f_num").toInt();
    QString paraSort = m_pReq->parameter("f_sort");
    QStringList paraLists;
    for (i = 0; i < paraNum; i++)
        paraLists.append(QUrl::fromPercentEncoding(m_pReq->parameter("f_lst" + QString::number(i)).toLocal8Bit()));
    if (paraNum > 0 && !paraLists.isEmpty() && paraLists.length() > 0)
    {
        QDir dir(MY_FAVORITE_FOLDER);
        if (!dir.exists()) dir.mkpath(MY_FAVORITE_FOLDER);
        QDir dirXml(MY_FAVORITE_WEB_FOLDER);
        if (!dirXml.exists()) dirXml.mkpath(MY_FAVORITE_WEB_FOLDER);
        QString userPath = QString("%1gui_%2.xml").arg(MY_FAVORITE_FOLDER, paraUser);
        QFile file(userPath);
        if (file.open(QIODevice::WriteOnly))
        {
            QXmlStreamWriter writer(&file);
            writer.setAutoFormatting(true);
            writer.writeStartDocument();
            writer.writeStartElement("config");
            writer.writeTextElement("sort", paraSort);
            writer.writeStartElement("my_favorite");
            for (i = 0; i < paraNum; i++)
            {
                writer.writeStartElement("item");
                QStringList addonLists = paraLists.value(i).split(",");
                if (!addonLists.isEmpty() && addonLists.length() == 6)
                {
                    writer.writeTextElement("name", addonLists.value(1));
                    writer.writeTextElement("show_name", addonLists.value(5));
                    writer.writeTextElement("flag", addonLists.value(0));
                    QString path = QString("%1?id=%2").arg(addonLists.value(4), addonLists.value(1));
                    writer.writeTextElement("path", path);
                }
                writer.writeEndElement();
            }
            writer.writeEndElement();
            writer.writeEndElement();
            writer.writeEndDocument();
            file.close();
            QString newPath = QString("%1gui_%2.xml").arg(MY_FAVORITE_WEB_FOLDER, paraUser);
            QFile::copy(userPath, newPath);
            res = 1;
        }
    }

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(QString::number(res)));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateMyFavGetSortInfo()
{
    int res = 2;
    QDomDocument doc;
    QString paraUser = m_pReq->parameter("f_user");
    QString path = QString("%1gui_%2.xml").arg(MY_FAVORITE_WEB_FOLDER, paraUser);
    QFile file(path);
    if (file.exists()) res = 0;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(QString::number(res)));

    m_var = doc.toString();
}

