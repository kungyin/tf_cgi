#ifndef APPDEFINE_H
#define APPDEFINE_H

#include <QString>

#define LOGIN_TIMOUT 1800

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
const QString SCRIPT_NFS_API        =   "nfsctl";
const QString SCRIPT_FTP_API        =   "ftpctl";
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
const QString SCRIPT_SSH_CTL        =   "sshctl";
const QString SCRIPT_TUXERA_API     =   "tuxera";
const QString SCRIPT_GROUP_MANAGER  =   "groupmgr";
const QString SCRIPT_START_REMOTE_BACKUP = "StartRemoteBackup";
const QString SCRIPT_P2P_API        =   "cp2p";
const QString SCRIPT_REMOTE_HD_SIZE =   "get_remote_hd_free_size";

const QString RSYNC_SHARE_NODE      =   "/etc/sysconfig/config/NetworkShareRsync";
const QString SYSTEM_PT_FILE        =   "/etc/systempt";
const QString MY_FAVORITE_FOLDER    =   "/etc/sysconfig/config/myfavorite/";
const QString MY_FAVORITE_WEB_FOLDER=   "/var/www/xml/";

#ifndef SIMULATOR_MODE

const QString API_PATH = "";
const QString ENV_PATH = "";
const QString SYS_CONFIG_FILE = "/etc/sysconfig/config/sys_config";
const QString USER_IMPORT_FILE = "/tmp/backupconfig.tar";
const QString FIRMWARE_FILE = "/mnt/HD_a4/genius_fw.bin";
const QString FIRMWARE_PERCENTAGE_FILE = "/tmp/.fw_percentage";
const QString FIRMWARE_VERIFY_STATUS_FILE = "/tmp/.verify_status";
const QString FIRMWARE_RESULT_FILE = "/tmp/.fw_result";
const QString DWONLOAD_USER_IMPORT_FILE = "/var/www/web/account_mgr/import_file.txt";
const QString VE_EXPORT_KEY_FILE = "/tmp/Encrypted-Volume_1.Key";
const QString SENDOUT_LOGFILE = "/tmp/log.txt";
const QString P2P_STATE_FILE = "/tmp/p2p_status";
const QString TORRENT_UPLOAD_FILE = "/tmp/upload/torrent_file";
const QString USB_SHARE_INFO_FILE = "/etc/usbshare_info";
const QString SHARE_INFO_FILE = "/etc/share_info";

const QString NETWORK_SCRIPT = API_PATH + "network";

#else

const QString API_PATH = "./faked_api/";
const QString ENV_PATH = API_PATH;
const QString SYS_CONFIG_FILE = API_PATH + "sys_config";
const QString USER_IMPORT_FILE = API_PATH + "backupconfig.tar";
const QString FIRMWARE_FILE = API_PATH + "genius_fw.bin";
const QString FIRMWARE_PERCENTAGE_FILE = API_PATH + ".fw_percentage";
const QString FIRMWARE_VERIFY_STATUS_FILE = API_PATH + ".verify_status";
const QString FIRMWARE_RESULT_FILE = API_PATH + ".fw_result";
const QString DWONLOAD_USER_IMPORT_FILE = API_PATH + "import_file.txt";
const QString VE_EXPORT_KEY_FILE = API_PATH + "Encrypted-Volume_1.Key";
const QString SENDOUT_LOGFILE = API_PATH + "log.txt";
const QString P2P_STATE_FILE = API_PATH + "p2p_status";
const QString TORRENT_UPLOAD_FILE = API_PATH + "torrent_file";
const QString USB_SHARE_INFO_FILE = API_PATH + "usbshare_info";
const QString SHARE_INFO_FILE = API_PATH + "share_info";

#endif

#endif // APPDEFINE_H
