#include "RenderResponseAddOn.h"

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

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_MODULE_SHOW_INSTALL_STATUS:
        generateModuleShowInstallStatus(doc);
        break;
    case CMD_GET_ALLAPPS:
        generateGetAllApps(doc);
        break;
    case CMD_GET_APKG_DETAIL:
        generateGetApkgDetail(doc);
        break;
    case CMD_MYFAV_CHECK_IMG:
        generateMyFavCheckImg(doc);
        break;
    case CMD_CHK_HDD_FREE_SIZE:
        generateChkHddFreeSize(doc);
        break;
    case CMD_DOWNLOAD_INSTALL_ADDON:
        generateDownloadInstallAddOn(str);
        break;
    case CMD_CLEAR_ADDON_FILES:
        generateClearAddOnFiles(doc);
        break;
    case CMD_MODULE_RE_INSTALL:
        generateModuleReInstall(str);
        break;
    case CMD_INSTALL_3_PARTY_APKG:
        generateInstall3PartyApkg(str);
        break;
    case CMD_UNINSTALL_ADDON:
        generateUninstallAddOn(doc);
        break;
    case CMD_MODULE_ENABLE_DISABLE:
        generateModuleEnableDisable(doc);
        break;
    case CMD_MODULE_UNINSTALL:
        generateModuleUninstall(doc);
        break;

    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

}

/* todo */
void RenderResponseAddOn::generateModuleShowInstallStatus(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    QDomElement root = doc.createElement("service");
    doc.appendChild(root);

    QStringList configContentElement(QStringList()
        << "install_type" << "install_status" << "install_error_mesg" << "install_filename");

//    if( configContentElement.size() != apiOut.size() ) {
//        for(int i = 0; i < apiOut.size(); i++) {
//            QDomElement element = doc.createElement(configContentElement.value(i));
//            root.appendChild(element);
//            element.appendChild(doc.createTextNode(apiOut.value(i)));
//        }
//    }
//    else {
//        //assert(0);
//        tError("RenderResponseSysStatus::generateModuleShowInstallStatus(): "
//               "configContentElement size is not equal to apiOut size.");
//    }

}

/* todo */
void RenderResponseAddOn::generateGetAllApps(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    QDomElement root = doc.createElement("service");
    doc.appendChild(root);

    QStringList allappsContentElement(QStringList()
        << "status" << "path" << "model");

//    if( configContentElement.size() != apiOut.size() ) {
//        for(int i = 0; i < apiOut.size(); i++) {
//            QDomElement element = doc.createElement(allappsContentElement.value(i));
//            root.appendChild(element);
//            element.appendChild(doc.createTextNode(apiOut.value(i)));
//        }
//    }
//    else {
//        //assert(0);
//        tError("RenderResponseSysStatus::generateGetAllApps(): "
//               "allappsContentElement size is not equal to apiOut size.");
//    }

}

/* todo */
void RenderResponseAddOn::generateGetApkgDetail(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement apkgElement = doc.createElement("apkg");
    root.appendChild(apkgElement);
    QDomElement itemElement = doc.createElement("item");
    apkgElement.appendChild(itemElement);


    QStringList itemContentElement(QStringList()
        << "show_name" << "name" << "category" << "description" << "version" << "update" << "show"
        << "show" << "size" << "developer" << "website" << "forum" << "platform" << "screenshot");

//    if( itemContentElement.size() != apiOut.size() ) {
//        for(int i = 0; i < apiOut.size(); i++) {
//            QDomElement element = doc.createElement(itemContentElement.value(i));
//            apkgElement.appendChild(element);
//            element.appendChild(doc.createTextNode(apiOut.value(i)));
//        }
//    }
//    else {
//        //assert(0);
//        tError("RenderResponseSysStatus::generateGetApkgDetail(): "
//               "itemContentElement size is not equal to apiOut size.");
//    }

}

/* todo */
void RenderResponseAddOn::generateMyFavCheckImg(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseAddOn::generateChkHddFreeSize(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement hddFreeSizeElement = doc.createElement("hdd_free_size");
    root.appendChild(hddFreeSizeElement);
    hddFreeSizeElement.appendChild(doc.createTextNode("2881387472"));
    QDomElement installPathElement = doc.createElement("install_path");
    root.appendChild(installPathElement);
    installPathElement.appendChild(doc.createTextNode("/mnt/HD/HD_a2"));
}

/* todo */
void RenderResponseAddOn::generateDownloadInstallAddOn(QString &str) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    str = "N/A";
}

/* todo */
void RenderResponseAddOn::generateClearAddOnFiles(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement installStatusElement = doc.createElement("install_status");
    root.appendChild(installStatusElement);
    installStatusElement.appendChild(doc.createTextNode("6"));
}

/* todo */
void RenderResponseAddOn::generateModuleReInstall(QString &str) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    str = "<script>location.href='/web/addon_center/installed.html'</script>";
}

/* todo */
void RenderResponseAddOn::generateInstall3PartyApkg(QString &str) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    str = "<script>location.href='/web/addon_center/installed.html'</script>";
}

/* todo */
void RenderResponseAddOn::generateUninstallAddOn(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement retElement = doc.createElement("ret");
    root.appendChild(retElement);
    retElement.appendChild(doc.createTextNode("1"));
}

/* todo */
void RenderResponseAddOn::generateModuleEnableDisable(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode("1"));
}

/* todo */
void RenderResponseAddOn::generateModuleUninstall(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement moduleNameElement = doc.createElement("module_name");
    root.appendChild(moduleNameElement);
    moduleNameElement.appendChild(doc.createTextNode("wordpress"));
    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode("1"));
}

