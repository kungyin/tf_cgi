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

#ifndef SIMULATOR_MODE

const QString API_PATH = "/usr/local/modules/api/";
const QString SCRIPT_DISK_MANAGER = "diskmgr";

const QString SYS_CONFIG_FILE = "/etc/sysconfig/config/sys_config";
const QString NETWORK_SCRIPT = "network";

#else

const QString API_PATH = "./faked_api/";
const QString SYS_CONFIG_FILE = "./faked_api/sys_config";

#endif

#endif // APPDEFINE_H
