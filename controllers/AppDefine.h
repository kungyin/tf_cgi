#ifndef APPDEFINE_H
#define APPDEFINE_H

#include <QString>

//#define SIMULATOR_MODE

const QString SCRIPT_DISK_API = "sysapi_dsk";
const QString SCRIPT_HOME_API = "sysapi_home";
const QString SCRIPT_USER_API = "sysapi_user";
const QString SCRIPT_DDNS_CTL = "ddnsctl";
const QString SCRIPT_LLTD_CTL = "lltdctl";
const QString SCRIPT_UPNP_CTL = "upnpctl";
const QString SCRIPT_USER_MGR = "ccUsermgr";
const QString SCRIPT_GET_IP = "GetIP";
const QString SCRIPT_QUOTA_MGR = "quotamgr";
const QString SCRIPT_AFP_API = "sysapi_afp";
const QString SCRIPT_NFS_API = "sysapi_nfs";
const QString SCRIPT_FTP_API = "appapi_ftp";

#ifndef SIMULATOR_MODE

const QString API_PATH = "/usr/local/modules/api/";
const QString SCRIPT_DISK_MANAGER = "diskmgr";

const QString SYS_CONFIG_FILE = "/etc/sysconfig/config/sys_config";
const QString NETWORK_SCRIPT = API_PATH + "network";

#else

const QString API_PATH = "./faked_api/";
const QString SYS_CONFIG_FILE = "./faked_api/sys_config";

#endif

#endif // APPDEFINE_H
