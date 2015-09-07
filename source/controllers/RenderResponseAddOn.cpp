#include <QProcess>

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

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_enable_disable", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAddOn::generateModuleUninstall() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_uninstall", true, ";");

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

