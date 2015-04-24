#ifndef APPDEFINE_H
#define APPDEFINE_H

//#define SIMULATOR_MODE

#ifndef SIMULATOR_MODE
const QString API_PATH = "/usr/local/modules/api/";
const QString SYS_CONFIG_FILE = "/etc/sysconfig/config/sys_config";
const QString NETWORK_SCRIPT = "network";
const QString LLTD_SCRIPT = "lltdctl";
const QString DDNS_SCRIPT = "ddnsctl";
#else
const QString API_PATH = "./";
const QString SYS_CONFIG_FILE = "./sys_config";

#endif

#endif // APPDEFINE_H
