#ifndef COMMANDDEFINE_H
#define COMMANDDEFINE_H

enum CGI_COMMAND {
    CMD_NONE = 0,
    CMD_VOLUME_STATUS,
    CMD_FMT_GET_SYNC_SATTE,
    CMD_FMT_GET_AUTO_REBUILD_INFO,
    CMD_AJAXPLORER_STOP,
    CMD_FMT_CREATE_DISKMGR,
    CMD_SMART_HD_LIST,
    CMD_SMART_XML_CREATE_TEST_LIST,
    CMD_SMART_SCHEDULE_LIST,
    CMD_SMART_GET_TEST_STATUS,
    CMD_SMART_SET_SCHEDULE,
    CMD_SMART_TEST_START,
    CMD_SCANDISK_INFO,
    CMD_CHECK_DISK_REMOUNT_STATUS,
    CMD_SCANDISK_RUN_E2FSCK,
    CMD_SCANDISK_FINISH,
    CMD_DISK_END,

    CMD_CGI_IS_BUILD_IN_LANGUAGE,
    CMD_CGI_GET_USER_LANGUAGE,
    CMD_CGI_GET_SSL_INFO,
    CMD_UI_CHECK_WTO,
    CMD_FW_STATUS,
    CMD_LOGIN,
    CMD_LOGOUT,
    CMD_LONGIN_END,

    CMD_LLTD,
    CMD_NETWORK_END,

};

const char CGI_PARA_COMMANDS[][255] = {
    "cgi_Volume_Status",
    "cgi_FMT_Get_Sync_State",
    "cgi_FMT_Get_Auto_Rebuild_Info",
    "cgi_AJAXPlorer_Stop",
    "cgi_FMT_Create_DiskMGR",
    "cgi_SMART_HD_List",
    "SMART_XML_Create_Test_List",
    "SMART_Schedule_List",
    "SMART_Get_Test_Status",
    "SMART_Set_Schedule",
    "SMART_Test_Start",
    "ScanDisk_info",
    "cgi_Check_Disk_Remount_State",
    "ScanDisk_run_e2fsck",
    "ScanDisk_Finish",
    "",

    /**** Home Page ****/
    "cgi_is_build_in_language",
    "cgi_get_user_language",
    "cgi_get_ssl_info",
    "ui_check_wto",
    "cgi_get_fw_status",
    "login",
    "logout",
    "",

    /**** Network ****/
    "cgi_get_lltd",
    "",

};


#endif // COMMANDDEFINE_H
