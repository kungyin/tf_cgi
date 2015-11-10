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
        break;
    case CMD_MYFAV_COMPARE_APKG:
        generateMyFavCompareApkg();
        break;

    case CMD_ICE_PLAYLIST:
        generateIcePlaylist();
        break;
    case CMD_ICE_IS_PLAYLIST_FULL:
        generateIceIsPlaylistFull();
        break;
    case CMD_ICE_PLAYLIST_NAME:
        generateIcePlaylistName();
        break;
    case CMD_ICE_HAS_PLAYLIST_NAME:
        generateIceHasPlaylistName();
        break;
    case CMD_ICE_PLAYLIST_NEW:
        generateIcePlaylistNew();
        break;
    case CMD_ICE_PLAYLIST_DEL:
        generateIcePlaylistDel();
        break;
    case CMD_ICE_MOD_INFO:
        generateIceModInfo();
        break;
    case CMD_ICE_PLAYLIST_RENEW:
        generateIcePlaylistRenew();
        break;
    case CMD_ICE_IS_ACTIVE_FULL:
        generateIceIsActiveFull();
        break;
    case CMD_ICE_PLAYLIST_ENABLE:
        generateIcePlaylistEnable();
        break;
    case CMD_ICE_PLAYLIST_DISABLE:
        generateIcePlaylistDisable();
        break;
    case CMD_ICE_GET:
        generateIceGet();
        break;
    case CMD_ICE_SET:
        generateIceSet();
        break;

    default:
        break;
    }

}

void RenderResponseAddOn::generateModuleShowInstallStatus() {

    QDomDocument doc;
    QStringList arg = QStringList() << "module_show_install_status";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

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
    QStringList arg = QStringList() << "cgi_get_allapps";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

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

    QStringList arg = QStringList() << "cgi_myfavorite_check_img" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAddOn::generateChkHddFreeSize() {

    QDomDocument doc;
    QStringList arg = QStringList() << "cgi_chk_hdd_free_size";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

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

    QStringList arg = QStringList() << "clear_addon_files" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

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

    QStringList arg = QStringList() << "module_re_install" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    m_var = "<script>location.href='/web/addon_center/installed.html'</script>";
}

void RenderResponseAddOn::generateInstall3PartyApkg() {

    QStringList arg = QStringList() << "install_3_party_apkg" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    m_var = "<script>location.href='/web/addon_center/installed.html?id=8401878'</script>";
}

void RenderResponseAddOn::generateUninstallAddOn() {
    QDomDocument doc;

    QStringList arg = QStringList() << "uninstall_addon" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement retElement = doc.createElement("ret");
    root.appendChild(retElement);
    retElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAddOn::generateModuleEnableDisable() {
    QDomDocument doc;

    QStringList arg = QStringList() << "module_enable_disable" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAddOn::generateModuleUninstall() {
    QDomDocument doc;

    QStringList arg = QStringList() << "module_uninstall" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

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
    QStringList arg = QStringList() << "cgi_application_lst";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QStringList itemTags(QStringList()
        << "Name" << "ShowName" << "Enable" << "URL" << "User" << "Center"
                         << "Icon_Disable" << "Icon_MouseOver" << "Icon_MouseOut");

    for(int i = 0; i < apiOut.size(); i++) {
        QDomElement itemElement = doc.createElement("Item");
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
    QStringList arg = QStringList() << "module_Get_One_Info" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

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
    QString userPath = QString("%1gui_%2.xml").arg(MY_FAVORITE_FOLDER, paraUser);
    QString newPath = QString("%1gui_%2.xml").arg(MY_FAVORITE_WEB_FOLDER, paraUser);
    if (paraNum <= 0)
    {
        QFile::remove(userPath);
        QFile::remove(newPath);
        res = 1;
    }
    QStringList paraLists;
    for (i = 0; i < paraNum; i++)
        paraLists.append(QUrl::fromPercentEncoding(m_pReq->parameter("f_lst" + QString::number(i)).toLocal8Bit()));
    if (paraNum > 0 && !paraLists.isEmpty() && paraLists.length() > 0)
    {
        QDir dir(MY_FAVORITE_FOLDER);
        if (!dir.exists()) dir.mkpath(MY_FAVORITE_FOLDER);
        QDir dirXml(MY_FAVORITE_WEB_FOLDER);
        if (!dirXml.exists()) dirXml.mkpath(MY_FAVORITE_WEB_FOLDER);
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
                    writer.writeTextElement("flag", (addonLists.value(0) == "0")?"1":addonLists.value(0));
                    writer.writeTextElement("path", addonLists.value(4));
                }
                writer.writeEndElement();
            }
            writer.writeEndElement();
            writer.writeEndElement();
            writer.writeEndDocument();
            file.close();
            QFile::remove(newPath);
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

void RenderResponseAddOn::generateMyFavCompareApkg()
{
    QDomDocument doc;
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIcePlaylist() {

    QDomDocument doc;
    QString paraPage = m_pReq->parameter("page");
    QString paraRp = m_pReq->parameter("rp");

    QStringList arg = QStringList() << "GUI_ice_playlist";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QString uiContent1 = "<a href=javascript:ices_playlist('%1')><IMG border='0' width='20' "
            "src='/audiostreamer/tunein.png'></a>";
    QString uiContent2 = "<a href=javascript:isplaylist_%1('%2')>"
            "<IMG border='0' src='/web/images/%3.png'></a>";

    QStringList playList(apiOut);
    int rp = paraRp.toInt();
    if(playList.size() > rp)
        playList = apiOut.mid((paraPage.toInt()-1) * rp, rp);

    int i = 0;
    for(QString e : playList) {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);

        QStringList rowContents;
        QString playListEnable = "disable";
        if(e.split(";").value(5) == "start")
            playListEnable = "enable";

        rowContents << (e.split(";").value(0) == "-" ? "-" : uiContent1.arg(e.split(";").value(0)))
                    << e.split(";").value(1) << e.split(";").value(2) << e.split(";").value(3)
                    << e.split(";").value(4)
                    << uiContent2.arg(playListEnable, e.split(";").value(1), e.split(";").value(5));

        for(int j = 0; j < rowContents.size(); j++ ) {
            QDomElement cellElement = doc.createElement("cell");
            rowElement.appendChild(cellElement);
            if(j == 0 || j == rowContents.size() - 1)
                cellElement.appendChild(doc.createCDATASection(rowContents.value(j)));
            else
                cellElement.appendChild(doc.createTextNode(rowContents.value(j)));
        }

        rowElement.setAttribute("id", QString::number(++i));
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

    m_var = doc.toString();

}

void RenderResponseAddOn::generateIceIsPlaylistFull()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_is_playlist_full";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIcePlaylistName()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_playlist_name";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement playlistNameElement = doc.createElement("playlist_name");
    root.appendChild(playlistNameElement);
    playlistNameElement.appendChild(doc.createTextNode(apiOut.value(1)));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIceHasPlaylistName()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_has_playlist_name"  << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIcePlaylistNew()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_playlist_new"  << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIcePlaylistDel()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_playlist_del"  << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIceModInfo()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_modify_info" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QStringList configTagNames(QStringList() << "res" << "genre" << "desc" << "rand");

    for(int i = 0; i < configTagNames.size(); i++) {
        QDomElement element = doc.createElement(configTagNames.value(i));
        root.appendChild(element);
        element.appendChild(doc.createTextNode(apiOut.value(i)));
    }

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIcePlaylistRenew()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_playlist_renew"  << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIceIsActiveFull()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_is_active_full";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIcePlaylistEnable()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_playlist_enable"  << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIcePlaylistDisable()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_playlist_disable"  << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIceGet()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_get";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement portElement = doc.createElement("port");
    root.appendChild(portElement);
    portElement.appendChild(doc.createTextNode(apiOut.value(1)));

    m_var = doc.toString();
}

void RenderResponseAddOn::generateIceSet()
{
    QDomDocument doc;

    QStringList arg = QStringList() << "GUI_ice_set"  << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();
}
