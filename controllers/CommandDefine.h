#ifndef COMMANDDEFINE_H
#define COMMANDDEFINE_H

enum CGI_COMMAND {
    CMD_NONE = 0,

    /**** Disk ****/
    CMD_VOLUME_STATUS,              /* cgi_Volume_Status" */
    CMD_FMT_GET_SYNC_SATTE,         /* cgi_FMT_Get_Sync_State */
    CMD_FMT_GET_AUTO_REBUILD_INFO,  /* cgi_FMT_Get_Auto_Rebuild_Info */
    CMD_AJAXPLORER_STOP,            /* cgi_AJAXPlorer_Stop */
    CMD_FMT_CREATE_DISKMGR,         /* cgi_FMT_Create_DiskMGR */
    CMD_SMART_HD_LIST,              /* cgi_SMART_HD_List */
    CMD_SMART_XML_CREATE_TEST_LIST, /* SMART_XML_Create_Test_List */
    CMD_SMART_SCHEDULE_LIST,        /* SMART_Schedule_List */
    CMD_SMART_GET_TEST_STATUS,      /* SMART_Get_Test_Status */
    CMD_SMART_SET_SCHEDULE,         /* SMART_Set_Schedule */
    CMD_SMART_TEST_START,           /* SMART_Test_Start */
    CMD_SCANDISK_INFO,              /* ScanDisk_info */
    CMD_CHECK_DISK_REMOUNT_STATUS,  /* cgi_Check_Disk_Remount_State */
    CMD_SCANDISK_RUN_E2FSCK,        /* ScanDisk_run_e2fsck */
    CMD_SCANDISK_FINISH,            /* ScanDisk_Finish */
    CMD_DISK_END,

    /**** Home Page ****/
    CMD_CGI_IS_BUILD_IN_LANGUAGE,   /* cgi_is_build_in_language */
    CMD_CGI_GET_USER_LANGUAGE,      /* cgi_get_user_language */
    CMD_CGI_GET_SSL_INFO,           /* cgi_get_ssl_info */
    CMD_UI_CHECK_WTO,               /* ui_check_wto */
    CMD_FW_STATUS,                  /* cgi_get_fw_status */
    CMD_LOGIN,                      /* login */
    CMD_LOGOUT,                     /* logout */
    CMD_LONGIN_END,

    /**** Network ****/
    CMD_GET_LLTD,                   /* cgi_get_lltd */
    CMD_LAN_XML,                    /* cgi_get_lan_xml */
    CMD_IPV6,                       /* cgi_get_ipv6 */
    CMD_LAN_STATUS,                 /* cgi_get_lan_status */
    CMD_LAN_XML2,                   /* cgi_get_lan_xml2 */
    CMD_SETIP_LOCK,                 /* cgi_setip_lock */
    CMD_IP,                         /* cgi_ip */
    CMD_SPEED,                      /* cgi_speed */
    CMD_LLTD,                       /* cgi_lltd */
    CMD_GET_DDNS,                   /* cgi_get_ddns */
    CMD_GET_DDNS_STATUS,            /* cgi_get_ddns_status */
    CMD_DDNS,                       /* cgi_ddns */
    CMD_PORTFORWARDING_GET,         /* cgi_portforwarding_get */
    CMD_UPNP_TEST,                  /* upnp_test */
    CMD_UPNP_TEST_RESULT,           /* upnp_test_result */
    CMD_PORTFORWARDING_TOTAL,       /* cgi_portforwarding_total */
    CMD_GET_PORT_TABLE,             /* get_port_table */
    CMD_PORTFORWARDING_ADD_SCAN,    /* cgi_portforwarding_add_scan */
    CMD_PORTFORWARDING_ADD,         /* cgi_portforwarding_add */
    CMD_PORTFORWARDING_MODIFY,      /* cgi_portforwarding_modify */
    CMD_PORTFORWARDING_DEL,         /* cgi_portforwarding_del */
    CMD_NETWORK_END,

    /**** Account ****/
    CMD_CHANGE_ADMIN_PWD,               /* cgi_chg_admin_pw */
    CMD_GET_USER_LIST,                  /* cgi_get_user_list */
    CMD_GET_USER_INFO,                  /* cgi_get_user_info */
    CMD_GET_SMB_LIST,                   /* cgi_get_smb_list */
    CMD_USER_ADD,                       /* cgi_user_add */
    CMD_RESTART_SERVICE,                /* cgi_restart_service */
    CMD_USER_SET_QUOTA,                 /* cgi_user_set_quota */
    CMD_ADDUSER_TO_SESSION,             /* cgi_adduser_to_session */
    CMD_CREATE_FTP_LINK,                /* cgi_create_ftp_link */
    CMD_FTP_SERVICE,                    /* cgi_ftp_service */
    CMD_WEBDAV_ACCOUNT_MERGE,           /* Webdav_Account_merge */
    CMD_USER_BATCH_CREATE,              /* cgi_user_batch_create */
    CMD_GET_MODIFY_USER_INFO,           /* cgi_get_modify_user_info */
    CMD_USER_MODIFY,                    /* cgi_user_modify */
    CMD_USER_DEL,                       /* cgi_user_del */
    CMD_MYFAVORITE_DEL_USER,            /* cgi_myfavorite_del_user */
    CMD_DWONLOAD_IMPORT_SAMPLE,         /* cgi_download_import_sample */
    CMD_GET_ALL_SESSION,                /* cgi_get_all_session */
    CMD_GET_IMPORT_USERS,               /* cgi_get_import_uesrs */
    CMD_ADDUSER_GET_USER_QUOTA_MAXSIZE, /* cgi_adduser_get_user_quota_maxsize */
    CMD_CREATE_IMPORT_USERS,            /* cgi_create_import_users */
    CMD_GET_CREATE_STATUS,              /* cgi_get_create_status */

    /**** Group ****/
    CMD_GET_GROUP_LIST,                     /* cgi_get_group_list */
    CMD_GET_GROUP_INFO,                     /* cgi_get_group_info */
    CMD_GROUP_ADD,                          /* cgi_group_add */
    CMD_ADDGROUP_GET_GROUP_QUOTA_MINSIZE,   /* cgi_addgroup_get_group_quota_minsize */
    CMD_GROUP_SET_QUOTA,                    /* cgi_group_set_quota */
    CMD_GET_MODIFY_GROUP_INFO,              /* cgi_get_modify_group_info */
    //CMD_WEBDAV_ACCOUNT_MERGE,               /* Webdav_Account_merge */
    CMD_GROUP_MODIFY,                       /* cgi_group_modify */
    CMD_GROUP_DEL,                          /* cgi_group_del */

    /**** Quota ****/
    CMD_GET_QUOTA_INFO,                     /* cgi_get_quota_info */
    CMD_GET_HD_MAPPING_INFO,                /* cgi_get_HD_Mapping_Info */
    CMD_GET_USER_QUOTA_LIST,                /* cgi_get_user_quota_list */
    CMD_GET_GROUP_QUOTA_LIST,               /* cgi_get_group_quota_list */
    CMD_GET_USER_QUOTA_MAXSIZE,             /* cgi_get_user_quota_maxsize */
    CMD_GET_GROUP_QUOTA_MINSIZE,            /* cgi_get_group_quota_minsize */
    CMD_SET_QUOTA_ONOFF,                    /* cgi_set_quota_onoff */

    /**** Network Share ****/
    CMD_MODULE_GET_INFO,                    /* Module_Get_Info */
    CMD_GET_ADS_INFO,                       /* cgi_get_ads_info */
    CMD_GET_SESSION,                        /* cgi_get_session */
    CMD_GET_ISO_SHARE,                      /* cgi_get_iso_share */
    //CMD_GET_HD_MAPPING_INFO,                /* cgi_get_HD_Mapping_Info */
    CMD_GET_AFP_INFO,                       /* cgi_get_afp_info */
    CMD_GET_NFS_INFO,                       /* cgi_get_nfs_info */
    CMD_ISO_PERCENTAGE,                     /* cgi_iso_percentage */
    CMD_CLEAR_ISO_CREATE,                   /* cgi_clear_iso_create */
    CMD_USER_LIST,                          /* cgi_user_list */
    CMD_GROUP_LIST,                         /* cgi_group_list */
    //CMD_GET_ALL_SESSION,                    /* cgi_get_all_session */
    CMD_GET_ALL_ISO_SHARE,                  /* cgi_get_all_iso_share */
    CMD_OPEN_TREE,                          /* cgi_open_tree */
    CMD_OPEN_NEW_FOLDER,                    /* cgi_open_new_folder */
    //CMD_FTP_SERVICE,                        /* cgi_ftp_service */
    CMD_ADD_SESSION,                        /* cgi_add_session */
    CMD_SET_NFS_SHARE,                      /* cgi_set_nfs_share */
    //CMD_RESTART_SERVICE,                    /* cgi_restart_service */
    CMD_GET_MODIFY_SESSION,                 /* cgi_get_modify_session */
    CMD_MODIFY_SESSION,                     /* cgi_modify_session */
    CMD_MODIFY_NFS_SHARE,                   /* cgi_modify_nfs_share */
    CMD_WEBDAV_ACCOUNT_ADD,                 /* Webdav_Account_add */
    CMD_DEL_SESSION,                        /* cgi_del_session */
    CMD_ACCOUNT_DEL,                        /* Webdav_Account_Del */
    CMD_RESET_SESSION,                      /* cgi_reset_session */
    CMD_ACCOUNT_END,

    /**** Application Management ****/
    CMD_SET_AFP,                            /* cgi_set_afp */
    CMD_NFS_ENABLE,                         /* cgi_nfs_enable */
    CMD_APP_MNGM_END,

    CMD_SIZE

};

const char CGI_PARA_COMMANDS[][255] = {

    /**** Disk ****/
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
    "cgi_get_lan_xml",
    "cgi_get_ipv6",
    "cgi_get_lan_status",
    "cgi_get_lan_xml2",
    "cgi_setip_lock",
    "cgi_ip",
    "cgi_speed",
    "cgi_lltd",
    "cgi_get_ddns",
    "cgi_get_ddns_status",
    "cgi_ddns",
    "cgi_portforwarding_get",
    "upnp_test",
    "upnp_test_result",
    "cgi_portforwarding_total",
    "get_port_table",
    "cgi_portforwarding_add_scan",
    "cgi_portforwarding_add",
    "cgi_portforwarding_modify",
    "cgi_portforwarding_del",
    "",

    /**** Account ****/
    "cgi_chg_admin_pw",
    "cgi_get_user_list",
    "cgi_get_user_info",
    "cgi_get_smb_list",
    "cgi_user_add",
    "cgi_restart_service",
    "cgi_user_set_quota",
    "cgi_adduser_to_session",
    "cgi_create_ftp_link",
    "cgi_ftp_service",
    "Webdav_Account_merge",
    "cgi_user_batch_create",
    "cgi_get_modify_user_info",
    "cgi_user_modify",
    "cgi_user_del",
    "cgi_myfavorite_del_user",
    "cgi_download_import_sample",
    "cgi_get_all_session",
    "cgi_get_import_uesrs",
    "cgi_adduser_get_user_quota_maxsize",
    "cgi_create_import_users",
    "cgi_get_create_status",

    /**** Group ****/
    "cgi_get_group_list",
    "cgi_get_group_info",
    "cgi_group_add",
    "cgi_addgroup_get_group_quota_minsize",
    "cgi_group_set_quota",
    "cgi_get_modify_group_info",
    //"Webdav_Account_merge",
    "cgi_group_modify",
    "cgi_group_del",

    /**** Quota ****/
    "cgi_get_quota_info",
    "cgi_get_HD_Mapping_Info",
    "cgi_get_user_quota_list",
    "cgi_get_group_quota_list",
    "cgi_get_user_quota_maxsize",
    "cgi_get_group_quota_minsize",
    "cgi_set_quota_onoff",

    /**** Network Share ****/
    "Module_Get_Info",
    "cgi_get_ads_info",
    "cgi_get_session",
    "cgi_get_iso_share",
    //"cgi_get_HD_Mapping_Info",
    "cgi_get_afp_info",
    "cgi_get_nfs_info",
    "cgi_iso_percentage",
    "cgi_clear_iso_create",
    "cgi_user_list",
    "cgi_group_list",
    //"cgi_get_all_session",
    "cgi_get_all_iso_share",
    "cgi_open_tree",
    "cgi_open_new_folder",
    //"cgi_ftp_service",
    "cgi_add_session",
    "cgi_set_nfs_share",
    //"cgi_restart_service",
    "cgi_get_modify_session",
    "cgi_modify_session",
    "cgi_modify_nfs_share",
    "Webdav_Account_add",
    "cgi_del_session",
    "Webdav_Account_Del",
    "cgi_reset_session",
    "",

    /**** Application Management ****/
    "cgi_set_afp",
    "cgi_nfs_enable",
    ""

};

#endif // COMMANDDEFINE_H
