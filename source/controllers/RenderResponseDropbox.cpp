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

/* todo */
void RenderResponseDropbox::generateDropboxRefreshStatus() {

    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_show_install_status", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("result");
    root.appendChild(element);
    element.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseDropbox::generateDropboxGetInfo() {

    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " Module_Get_Info");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QStringList configContentElement(QStringList()
        << "enable" << "local_folder" << "download_period" << "busy" << "last_job_time" << "user_display_name"
        << "user_email" << "total_size" << "used_size" << "is_auth_valid" << "file_downloads" << "file_uploads"
        << "rm_local_files" << "rm_dbox_files" << "create_local_dirs" << "create_dbox_dirs" << "rm_local_dirs"
        << "rm_dbox_dirs" << "mv_dbox_files" << "mv_dbox_dirs" << "downloads_bytes" << "uploads_bytes"
        << "sync_errors" << "running_state" << "need_space");

//    if( configContentElement.size() == apiOut.size() ) {
//        for(int i = 0; i < apiOut.size(); i++) {
//            QDomElement element = doc.createElement(configContentElement.value(i));
//            root.appendChild(element);
//            element.appendChild(doc.createTextNode(apiOut.value(i)));
//        }
//    }
//    else {
//        //assert(0);
//        tError("RenderResponseDropbox::generateDropboxGetInfo(): "
//               "configContentElement size is not equal to apiOut size.");
//    }

    m_var = doc.toString();

}

/* todo */
void RenderResponseDropbox::generateDropboxAPIChangePath() {

    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_show_install_status", true, ";");

    QDomElement root = doc.createElement("path");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode("Volume_1/dropbox"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseDropbox::generateDropboxGetAccessUrl() {

    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_show_install_status", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("URL");
    root.appendChild(element);
    element.appendChild(doc.createTextNode("https://www.dropbox.com/1/oauth/authorize?oauth_token"
          "=223fTLwDvmqVkPTU&amp;oauth_callback=http://192.168.100.85/web/backup_mgr/dropbox.php"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseDropbox::generateDropboxEnable() {

    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_show_install_status", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("result");
    root.appendChild(element);
    element.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseDropbox::generateDropboxNewFolderEncode() {

    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_show_install_status", true, ";");

    QDomElement root = doc.createElement("mkdir");
    doc.appendChild(root);
    QDomElement element = doc.createElement("status");
    root.appendChild(element);
    element.appendChild(doc.createTextNode("ok"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseDropbox::generateDropboxCheckFolderExist() {

    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_show_install_status", true, ";");

    QDomElement root = doc.createElement("exist");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseDropbox::generateDropboxSetInterval() {

    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_show_install_status", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("result");
    root.appendChild(element);
    element.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseDropbox::generateDropboxSyncNow() {

    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_show_install_status", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("result");
    root.appendChild(element);
    element.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseDropbox::generateDropboxUnlink() {

    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " module_show_install_status", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement element = doc.createElement("result");
    root.appendChild(element);
    element.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}
