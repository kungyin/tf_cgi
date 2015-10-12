#include "RenderResponseDropbox.h"

RenderResponseDropbox::RenderResponseDropbox(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseDropbox::~RenderResponseDropbox() {
}

void RenderResponseDropbox::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_DROPBOX_REFRESH_STATUS:
        generateDropboxRefreshStatus();
        break;
    case CMD_DROPBOX_GET_INFO:
        generateDropboxGetInfo();
        break;
    case CMD_DROPBOX_API_CHANGE_PATH:
        generateDropboxAPIChangePath();
        break;
    case CMD_DROPBOX_GET_ACCESS_URL:
        generateDropboxGetAccessUrl();
        break;
    case CMD_DROPBOX_ENABLE:
        generateDropboxEnable();
        break;
    case CMD_OPEN_NEW_FOLDER_ENCODE:
        generateDropboxNewFolderEncode();
        break;
    case CMD_DROPBOX_CHECK_FOLDER_EXIST:
        generateDropboxCheckFolderExist();
        break;
    case CMD_DROPBOX_SET_INTERVAL:
        generateDropboxSetInterval();
        break;
    case CMD_DROPBOX_SYNC_NOW:
        generateDropboxSyncNow();
        break;
    case CMD_DROPBOX_UNLINK:
        generateDropboxUnlink();
        break;

    default:
        break;
    }

}

void RenderResponseDropbox::generateDropboxRefreshStatus() {

    QDomDocument doc;
    QStringList arg = QStringList() << "cgi_Dropbox_refresh_status";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("result");
    root.appendChild(element);
    element.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseDropbox::generateDropboxGetInfo() {

    QDomDocument doc;
    QStringList arg = QStringList() << "cgi_Dropbox_get_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QStringList configContentElement(QStringList()
        << "enable" << "local_folder" << "download_period" << "busy" << "last_job_time" << "user_display_name"
        << "user_email" << "total_size" << "used_size" << "is_auth_valid" << "file_downloads" << "file_uploads"
        << "rm_local_files" << "rm_dbox_files" << "create_local_dirs" << "create_dbox_dirs" << "rm_local_dirs"
        << "rm_dbox_dirs" << "mv_dbox_files" << "mv_dbox_dirs" << "downloads_bytes" << "uploads_bytes"
        << "sync_errors" << "running_state" << "need_space");

    tDebug("%d %d", configContentElement.size(), apiOut.size());
    if( configContentElement.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {
            QDomElement element = doc.createElement(configContentElement.value(i));
            root.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseDropbox::generateDropboxGetInfo(): "
               "configContentElement size is not equal to apiOut size.");
    }

    m_var = doc.toString();

}

void RenderResponseDropbox::generateDropboxAPIChangePath() {

    QDomDocument doc;
    QStringList arg = QStringList() << "cgi_Dropbox_api_change_path" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("path");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseDropbox::generateDropboxGetAccessUrl() {

    QDomDocument doc;
    QStringList arg = QStringList() << "cgi_Dropbox_get_access_url" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("URL");
    root.appendChild(element);
    element.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseDropbox::generateDropboxEnable() {

    QDomDocument doc;
    QStringList arg = QStringList() << "cgi_Dropbox_enable";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("result");
    root.appendChild(element);
    element.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseDropbox::generateDropboxNewFolderEncode() {

    QDomDocument doc;
    QStringList arg = QStringList() << "cgi_open_new_folder_encode" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("mkdir");
    doc.appendChild(root);
    QDomElement element = doc.createElement("status");
    root.appendChild(element);
    element.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseDropbox::generateDropboxCheckFolderExist() {

    QDomDocument doc;
    QStringList arg = QStringList() << "cgi_Dropbox_check_folder_exist" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("exist");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseDropbox::generateDropboxSetInterval() {

    QDomDocument doc;
    QStringList arg = QStringList() << "cgi_Dropbox_set_interval" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("result");
    root.appendChild(element);
    element.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseDropbox::generateDropboxSyncNow() {

    QDomDocument doc;
    QStringList arg = QStringList() << "cgi_Dropbox_sync_now";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("result");
    root.appendChild(element);
    element.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseDropbox::generateDropboxUnlink() {

    QDomDocument doc;
    QStringList arg = QStringList() << "cgi_Dropbox_unlink";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("result");
    root.appendChild(element);
    element.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}
