#ifndef APPDEFINE_H
#define APPDEFINE_H

#include <QString>

const QString SCRIPT_DISK_API       =   "sysapi_dsk";
const QString SCRIPT_SCANDISK_API   =   "scandisk";
const QString SCRIPT_HOME_API       =   "sysapi_home";
const QString SCRIPT_USER_API       =   "sysapi_user";
const QString SCRIPT_DDNS_CTL       =   "ddnsctl";
const QString SCRIPT_LLTD_CTL       =   "lltdctl";
const QString SCRIPT_UPNP_CTL       =   "upnpctl";
const QString SCRIPT_USER_MGR       =   "ccUsermgr";
const QString SCRIPT_GET_IP         =   "GetIP";
const QString SCRIPT_QUOTA_MGR      =   "quotamgr";
const QString SCRIPT_AFP_API        =   "sysapi_afp";
const QString SCRIPT_NFS_API        =   "sysapi_nfs";
const QString SCRIPT_FTP_API        =   "appapi_ftp";
const QString SCRIPT_FTP_API2       =   "sysapi_ftp";
const QString SCRIPT_SERVICE_API    =   "sysapi_service";
const QString SCRIPT_SMB_API        =   "sysapi_smb";
const QString SCRIPT_IMPORTUSER_API =   "importuser";
const QString SCRIPT_DATE_API       =   "sysapi_date";
const QString SCRIPT_TIMEZONE_API   =   "sysapi_timezone";
const QString SCRIPT_NTP_API        =   "sysapi_ntp";
const QString SCRIPT_DEVICE_API     =   "sysapi_device";
const QString SCRIPT_DISK_MANAGER   =   "diskmgr";
const QString SCRIPT_MANAGER_API    =   "ccManager";
const QString SCRIPT_POWER_API      =   "sysapi_power";
const QString SCRIPT_IDLE_API       =   "sysapi_idle";
const QString SCRIPT_RESTORE_API    =   "sysapi_restore";
const QString SCRIPT_CONFIG_API     =   "sysapi_config";
const QString SCRIPT_LED_API        =   "cled";
const QString SCRIPT_APPAPI_FTP     =   "appapi_ftp2";
const QString SCRIPT_APPAPI_TMM     =   "appapi_tmm";
const QString SCRIPT_SYSLOG_GET     =   "syslog_get";
const QString SCRIPT_SYSLOG_API     =   "sysapi_syslog";
const QString SCRIPT_FW_UPGRADE_MGR =   "ccFwupgrade";
const QString SCRIPT_AFP_CTL        =   "afpctl";

#ifndef SIMULATOR_MODE

const QString API_PATH = "";
const QString ENV_PATH = "";
const QString SYS_CONFIG_FILE = "/etc/sysconfig/config/sys_config";
const QString USER_IMPORT_FILE = "/tmp/backupconfig.tar";
const QString FIRMWARE_FILE = "/mnt/HD_a4/genius_fw.bin";
const QString FIRMWARE_PERCENTAGE_FILE = "/tmp/.fw_percentage";
const QString FIRMWARE_VERIFY_STATUS_FILE = "/tmp/.verify_status";
const QString FIRMWARE_RESULT_FILE = "/tmp/.fw_result";
const QString SENDOUT_LOGFILE = "/tmp/log.txt";

const QString NETWORK_SCRIPT = API_PATH + "network";

#else

const QString API_PATH = "./faked_api/";
const QString ENV_PATH = API_PATH;
const QString SYS_CONFIG_FILE = API_PATH + "sys_config";
const QString USER_IMPORT_FILE = API_PATH + "backupconfig.tar";
const QString FIRMWARE_FILE = API_PATH + "genius_fw.bin";
const QString FIRMWARE_PERCENTAGE_FILE = "./faked_api/.fw_percentage";
const QString FIRMWARE_VERIFY_STATUS_FILE = API_PATH + ".verify_status";
const QString FIRMWARE_RESULT_FILE = API_PATH + ".fw_result";
const QString SENDOUT_LOGFILE = API_PATH + "log.txt";

#endif

#endif // APPDEFINE_H
