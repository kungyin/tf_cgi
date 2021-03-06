#ifndef COMMANDDEFINE_H
#define COMMANDDEFINE_H

enum RENDER_TYPE {
    RENDER_TYPE_UNKNOWN,
    RENDER_TYPE_NULL,
    RENDER_TYPE_STRING,
    RENDER_TYPE_XML,
    RENDER_TYPE_JOSEN,
    RENDER_TYPE_FILE,
    RENDER_TYPE_HTML,
    RENDER_TYPE_REDIRECT,
    RENDER_TYPE_USER_LOGIN,
    RENDER_TYPE_USER_LOGOUT,
    RENDER_TYPE_FILE_REMOVE,
};

enum COMMAND_ALLOW {
    LOGIN_CMDS      =   1,
    OPENED_CMDS     =   1 << 1,
    COOKIE_REQ_CMDS =   1 << 2,  // login with cookie required.
};

enum CGI_COMMAND {
    CMD_NONE = 0,

    /**** Disk ****/
    CMD_VOLUME_STATUS,              /* cgi_Volume_Status" */
    CMD_FMT_GET_SYNC_SATTE,         /* cgi_FMT_Get_Sync_State */
    CMD_FMT_GET_AUTO_REBUILD_INFO,  /* cgi_FMT_Get_Auto_Rebuild_Info */
    CMD_AJAXPLORER_STOP,            /* cgi_AJAXPlorer_Stop */
    CMD_FMT_CREATE_DISKMGR,         /* cgi_FMT_Create_DiskMGR */
    CMD_FMT_REMAIN_DISKMGR,         /* cgi_FMT_Remain_DiskMGR */
    CMD_DISK_REMOUNT,               /* cgi_Disk_Remount */
    CMD_FMT_GUI_LOG,                /* cgi_FMT_GUI_Log */
    CMD_FMT_REMOUNT_STATE,          /* cgi_Check_Disk_Format_Remount_State */
    CMD_FMT_DISK_FINISH,            /* cgi_FMT_Disk_Finish */
    CMD_SMART_HD_LIST,              /* cgi_SMART_HD_List */
    CMD_SMART_XML_CREATE_TEST_LIST, /* SMART_XML_Create_Test_List */
    CMD_SMART_SCHEDULE_LIST,        /* SMART_Schedule_List */
    CMD_SMART_GET_TEST_STATUS,      /* SMART_Get_Test_Status */
    CMD_SMART_SET_SCHEDULE,         /* SMART_Set_Schedule */
    CMD_SMART_TEST_START,           /* cgi_SMART_Test_Start */
    CMD_SCANDISK_INFO,              /* ScanDisk_info */
    CMD_CHECK_DISK_REMOUNT_STATUS,  /* cgi_Check_Disk_Remount_State */
    CMD_SCANDISK_RUN_E2FSCK,        /* ScanDisk_run_e2fsck */
    CMD_SCANDISK_FINISH,            /* ScanDisk_Finish */
    CMD_VE_LIST,                    /* cgi_VE_List */
    CMD_VE_PWD_CHECK,               /* cgi_VE_PWD_Check */
    CMD_VE_VERIFY_KEYFILE,          /* cgi_VE_Verify_KeyFile */
    CMD_VE_MODIFY,                  /* cgi_VE_Mofify */
    CMD_VE_SAVE_FILE,               /* cgi_VE_Save_File */
    CMD_DISK_END,

    /**** Home Page ****/
    CMD_CGI_IS_BUILD_IN_LANGUAGE,   /* cgi_is_build_in_language */
    CMD_GET_USER_LANGUAGE,          /* cgi_get_user_language */
    CMD_CGI_GET_SSL_INFO,           /* cgi_get_ssl_info */
    CMD_UI_CHECK_WTO,               /* ui_check_wto */
    CMD_FW_STATUS,                  /* cgi_get_fw_status */
    CMD_LOGIN,                      /* login */
    CMD_LOGOUT,                     /* logout */
    CMD_SET_USER_LANGUAGE,          /* cgi_set_user_language */
    CMD_GET_LOG_ITEM,               /* cgi_get_log_item */
    CMD_LONGIN_END,

    /**** Network ****/
    CMD_GET_LLTD,                   /* cgi_get_lltd */
    CMD_LAN_XML,                    /* cgi_get_lan_xml */
    CMD_IPV6,                       /* cgi_get_ipv6 */
    CMD_LAN_STATUS,                 /* cgi_get_lan_status */
    CMD_LAN_XML2,                   /* cgi_get_lan_xml2 */
    CMD_SETIP_LOCK,                 /* cgi_setip_lock */
    CMD_IP,                         /* cgi_ip */
    CMD_DEFAULT_GW,                 /* cgi_default_gw */
    CMD_SET_IPV6,                   /* cgi_set_ipv6 */
    CMD_CHK_IPV6_ADDR,              /* cgi_chk_ipv6_addr */
    CMD_CHK_GW_ADDR,                /* cgi_chk_gw_addr */
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
    CMD_PORTFORWARDING_GET_PORT,    /* cgi_portforwarding_get_port */

    CMD_GET_SSH_PORT,               /* cgi_get_ssh_port */
    CMD_SET_SSH_PORT,               /* cgi_set_ssh_port */
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
    CMD_ACCOUNT_END,

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
    CMD_WEBDAV_ACCOUNT_DEL,                 /* Webdav_Account_Del */
    CMD_RESET_SESSION,                      /* cgi_reset_session */
    CMD_GET_SHARE_INFO,                     /* cgi_get_share_info */
    CMD_GET_FTP,                            /* cgi_get_ftp */
    CMD_WEBDAV_ACCOUNT_INFO,                /* Webdav_Account_Info */

    /**** ISO mount share ****/
    CMD_SET_ISO_SHARE,                      /* cgi_set_iso_share */
    CMD_GET_ISO_SHARE_DETAIL,               /* cgi_get_iso_share_detail */
    CMD_GET_NFS_SHARE_INFO,                 /* cgi_get_nfs_share_info */
    CMD_GET_MODIFY_ISO_INFO,                /* cgi_get_modify_iso_info */
    CMD_MODIFY_ISO_SHARE,                   /* cgi_modify_iso_share */
    CMD_DEL_ISO_SHARE,                      /* cgi_del_iso_share */
    CMD_CHK_IMG_NAME,                       /* cgi_chk_img_name */
    CMD_CHK_HD_SIZE,                        /* cgi_chk_hd_size */
    CMD_ISO_CONFIG,                         /* cgi_iso_config */
    CMD_ISO_CREATE_PATH,                    /* cgi_iso_create_path */
    CMD_ISO_SIZE,                           /* cgi_iso_size */
    //CMD_DEL,                                /* cgi_del */
    CMD_ISO_CREATE_IMAGE,                   /* cgi_iso_create_image */
    CMD_NETSHARE_END,

    /**** Application Management ****/
    CMD_SET_AFP,                            /* cgi_set_afp */
    CMD_NFS_ENABLE,                         /* cgi_nfs_enable */

    /**** Multimedia Services ****/
    CMD_CHK_DB,                             /* cgi_chk_db */
    CMD_UPNP_AV_SERVER_PATH_LIST,           /* UPnP_AV_Server_Path_List */
    CMD_UPNP_AV_SERVER_GET_CONFIG,          /* UPnP_AV_Server_Get_Config */
    CMD_UPNP_AV_SERVER,                     /* UPnP_AV_Server */
    CMD_UPNP_AV_SERVER_GET_SQLDB_STATE,     /* UPnP_AV_Server_Get_SQLDB_State */
    CMD_GUI_CODEPAGE_GET_LIST,              /* GUI_codepage_get_list */
    CMD_ITUNES_SERVER_GET_XML,              /* iTunes_Server_Get_XML */
    CMD_ITUNES_SERVER_READY,                /* iTunes_Server_Ready */
    CMD_AV_SERVER_CHECK_PATH,               /* UPnP_AV_Server_Check_Path */
    CMD_AV_SERVER_PATH_SETTING,             /* UPnP_AV_Server_Path_Setting */
    CMD_SQLDB_STOP_FINISH,                  /* CGI_SQLDB_Stop_Finish */
    CMD_UPNP_AV_SERVER_PRESCAN,             /* UPnP_AV_Server_Prescan */
    CMD_UPNP_AV_SERVER_PATH_DEL,            /* UPnP_AV_Server_Path_Del */
    CMD_UPNP_AV_SERVER_SETTING,             /* UPnP_AV_Server_Setting */
    CMD_GUI_CODEPAGE_ADD,                   /* GUI_codepage_add */
    CMD_ITUNES_SERVER_SETTING,              /* iTunes_Server_Setting */
    CMD_ITUNES_SERVER_CHECK_PS,             /* iTunes_Server_Check_PS */
    CMD_ITUNES_SERVER_REFRESH,              /* iTunes_Server_Refresh */
    CMD_ITUNES_SERVER_REFRESH_STATE,        /* iTunes_Server_Refresh_State */

    /**** Syslog Server ****/
    CMD_SYSLOG_SEARCH,                      /* Syslog_Search */
    CMD_GET_VOLUME_INFO,                    /* Get_Volume_Info */
    CMD_SYSLOG_GET_LOG_FILE_OPTION,         /* Syslog_Get_Log_File_Option */
    CMD_SYSLOG_GET_CONFIG,                  /* Syslog_Get_Config */
    CMD_SYSLOG_GET_SELECT_OPTION,           /* Syslog_Get_Select_Option */
    CMD_SYSLOG_SET_CONFIG,                  /* Syslog_Set_Config */
    CMD_SYSLOG_EXPORT,                      /* Syslog_Export */
    CMD_SYSLOG_GET_EXPORT_STATUS,           /* Syslog_Get_Export_Status */
    CMD_SYSLOG_CLEAR,                       /* Syslog_Clear */

    /**** Local Backup ****/
    CMD_LOCAL_BACKUP_NOW,                   /* Local_Backup_Now */
    CMD_LOCAL_BACKUP_LIST,                  /* Local_Backup_List */
    CMD_READ_OPEN_TREE,                     /* cgi_read_open_tree */
    CMD_GENERIC_OPEN_TREE,                  /* cgi_generic_open_tree */
    CMD_LOCAL_BACKUP_SAMBA_FORMAT,          /* Local_Backup_Samba_Format */
    CMD_LOCAL_BACKUP_ADD,                   /* Local_Backup_Add */
    CMD_LOCAL_BACKUP_INFO,                  /* Local_Backup_Info */
    CMD_LOCAL_BACKUP_RENEW,                 /* Local_Backup_Renew */
    CMD_LOCAL_BACKUP_DEL,                   /* Local_Backup_Del */
    CMD_LOCAL_BACKUP_TEST,                  /* Localbackup_Test */
    CMD_LOCAL_BACKUP_START,                 /* Localbackup_Start */
    CMD_LOCAL_BACKUP_STOP,                  /* Localbackup_Stop */

    CMD_GET_RSYNC_INFO,                     /* cgi_get_rsync_info */
    CMD_SET_RSYNC_SERVER,                   /* cgi_set_rsync_server */

    CMD_GET_BACKUP_LIST,                    /* cgi_get_backup_list */
    CMD_GET_ALL_TASK_NAME,                  /* cgi_get_all_task_name */
    CMD_SERVER_TEST,                        /* cgi_server_test */
    CMD_CHECK_RSYNC_RW,                     /* cgi_check_rsync_rw */
    CMD_SET_SCHEDULE,                       /* cgi_set_schedule */
    CMD_GET_MODIFY_INFO,                    /* cgi_get_modify_info */
    CMD_DEL_SCHEDULE,                       /* cgi_del_schedule */
    CMD_ENABLE_DISABLE_SCHEDULE,            /* cgi_enable_disable_schedule */
    CMD_BACKUP_NOW,                         /* cgi_backup_now */
    CMD_MTP_INFO_GET,                       /* cgi_mtp_info_get */
    CMD_USB_BACKUP_INFO_GET,                /* cgi_usb_backup_info_get */
    CMD_MTP_INFO_SET,                       /* cgi_mtp_info_set */
    CMD_USB_BACKUP_INFO_SET,                /* cgi_usb_backup_info_set */
    CMD_GET_USB_MAPPING_INFO,               /* cgi_get_USB_Mapping_Info */
    CMD_OPEN_USB_TREE,                      /* cgi_open_usb_tree */
    CMD_APP_MNGM_END,

    /**** System Management ****/
    CMD_GET_TIME,                           /* cgi_get_time */
    CMD_MANUAL_TIME,                        /* cgi_manual_time */
    CMD_TIMEZONE,                           /* cgi_timezone */
    CMD_NTP_TIME,                           /* cgi_ntp_time */
    CMD_GET_TIME_STATUS,                    /* cgi_get_time_status */

    CMD_GET_DEVICE_INFO,                    /* cgi_get_device_info */
    CMD_DEVICE,                             /* cgi_device */

    CMD_DETECT_DANGEROUS,                   /* cgi_Detect_Dangerous */
    CMD_GET_IDEL,                           /* cgi_get_idle */
    CMD_GET_TEMPERATURE,                    /* cgi_get_temperature */
    CMD_GET_RESTORE_STATUS,                 /* cgi_get_restore_status */
    CMD_RESTART,                            /* cgi_restart */
    CMD_RESTORE,                            /* cgi_restore */
    CMD_SHUTDOWN,                           /* cgi_shutdown */
    CMD_IDLE,                               /* cgi_idle */
    CMD_TEMPERATURE,                        /* cgi_temperature */
    CMD_BACKUP_CONF,                        /* cgi_backup_conf */
    CMD_RESTORE_CONF,                       /* cgi_restore_conf */

    CMD_GET_POWER_MGR,                      /* cgi_get_power_mgr_xml */
    CMD_POWER_MANAGEMENT,                   /* cgi_power_management */
    CMD_POWER_RECV,                         /* cgi_power_recovery */
    CMD_FAN,                                /* cgi_fan */
    CMD_POWER_OFF_SCH,                      /* cgi_power_off_sch */

    CMD_GET_EMAIL_XML,                      /* cgi_get_email_xml */
    CMD_GET_EVENT_XML,                      /* cgi_get_event_xml */
    CMD_EMAIL_EVENT,                        /* cgi_email_event */
    CMD_EMAIL,                              /* cgi_email */
    CMD_EMAIL_TEST,                         /* cgi_email_test */
    CMD_EMAIL_TEST_RESULT,                  /* cgi_email_test_result */
    CMD_EMAIL_CLEAR,                        /* cgi_email_clear */

    CMD_SMS_ADD,                            /* cgi_sms_add */
    CMD_SMS_MODIFY,                         /* cgi_sms_modify */
    CMD_SMS_TEST,                           /* cgi_sms_test */
    CMD_SMS_TEST_RESULT,                    /* cgi_sms_test_result */
    CMD_SMS_DEL,                            /* cgi_sms_del */

    CMD_LOG_SYSTEM,                         /* cgi_log_system */
    CMD_GET_LOG_INFO,                       /* cgi_get_log_info */
    CMD_LOG_SERVER,                         /* cgi_log_server */
    CMD_SEND_LOG_TEST,                      /* cgi_send_log_test */
    CMD_LOG_BACKUP,                         /* cgi_log_backup */
    CMD_LOG_CLEAR,                          /* cgi_log_clear */

    CMD_GUI_UPS_INFO,                       /* GUI_ups_info */
    CMD_GUI_UPS_MATER_LIST,                 /* GUI_ups_mater_list */
    CMD_GUI_UPS_SLAVE_SETTING,              /* GUI_ups_slave_setting */
    CMD_GUI_UPS_PS,                         /* GUI_ups_ps */
    CMD_USB_STORAGE_UMOUNT,                 /* cgi_usb_Storage_umount */
    CMD_USB_PRINTER_CLEAR,                  /* cgi_usb_printer_clear */

    CMD_FIRM_V_XML,                         /* get_firm_v_xml */
    CMD_CHECK_POWER_SCH,                    /* check_power_sch */
    CMD_FIRMWARE_INIT_UPLOAD,               /* cgi_firmware_init_upload */
    CMD_FIRMWARE_UPLOAD,                    /* cgi_firmware_upload */
    CMD_GET_PERCENTAGE,                     /* cgi_get_percentage */
    CMD_GET_FIRMWARE_VERIFY,                /* cgi_get_firmware_verify */
    CMD_GET_UP_FW,                          /* cgi_get_uP_fw */
    CMD_REBOOT,                             /* cgi_reboot */

    CMD_SYS_MNGM_END,

    /**** System Status ****/
    CMD_GET_STATUS,                         /* cgi_get_status */
    //CMD_GET_TEMPERATURE,                    /* cgi_get_temperature */
    CMD_STATUS_VOLUME_INFO,                 /* cgi_Status_Volume_Info */
    CMD_USB_STORAGE_INFO,                   /* cgi_usb_Storage_info */
    CMD_MTP_INFO,                           /* cgi_mtp_info */
    CMD_USB_PRINTER_INFO,                   /* cgi_usb_printer_info */
    CMD_UPS_INFO2,                          /* cgi_ups_info2 */

    CMD_SMART_XML_CREATE_DEVICE_LIST,       /* SMART_XML_Create_Device_List */
    CMD_SMART_XML_CREATE_SMART_INFO,        /* SMART_XML_Create_Smart_Info */

    CMD_RESOURCE,                           /* resource */

    CMD_GET_SERVICE,                        /* cgi_get_service */
    CMD_MODULE_LIST,                        /* module_list */

    CMD_SYS_STATUS_END,

    /**** FTP Server ****/
    CMD_FTP_SERVER_GET_CONFIG,              /* FTP_Server_Get_Config */
    CMD_FTP_SERVER_EXIP_RENEW,              /* FTP_Server_EXIP_Renew */
    CMD_P2P_GET_PORT,                       /* p2p_get_port */
    CMD_FTP_SERVER_BLOCKIP_LIST,            /* FTP_Server_BlockIP_List */
    CMD_FTP_SERVER_BLOCKIP_ADD,             /* FTP_Server_BlockIP_Add */
    CMD_FTP_SERVER_ENABLE,                  /* FTP_Server_Enable */
    CMD_FTP_SERVER_SET_CONFIG,              /* FTP_Server_Set_Config */
    CMD_FTP_SERVER_END,

    /**** Time Machine ****/

    CMD_TM_GET_INFO,                        /* cgi_tm_get_info */
    CMD_TM_GET_LIST,                        /* cgi_tm_get_list */
    CMD_TM_GET_SMB_LIST,                    /* cgi_tm_get_smb_list */
    CMD_TM_SET,                             /* cgi_tm_set */
    CMD_TM_GET_SHARENAME,                   /* cgi_tm_get_sharename */
    CMD_TM_SET_SHARE,                       /* cgi_tm_set_share */
    CMD_TM_DEL_SHARE,                       /* cgi_tm_del_share */
    CMD_TM_DEL_ALL_SHARE,                   /* cgi_tm_del_all_share */
    CMD_TIME_MACHINE_END,
	
	/**** Setup Wizard ****/
    CMD_CHK_ADMIN_PW,                       /* cgi_chk_admin_pw */
    CMD_SET_LED,                            /* cgi_set_led */
    CMD_GET_WIZARD,                         /* cgi_get_wizard */
    CMD_SETUP_WIZARD_END,

    /**** Application FTP/HTTP download ****/
    CMD_DOWNLOADS_SCHEDULE_NOW,              /* Downloads_Schedule_Now */
    CMD_DOWNLOADS_SCHEDULE_LIST,             /* Downloads_Schedule_List */
    CMD_DOWNLOADS_SCHEDULE_ADD,              /* Downloads_Schedule_Add */
    CMD_DOWNLOADS_SCHEDULE_INFO,             /* Downloads_Schedule_Info */
    CMD_DOWNLOADS_SCHEDULE_RENEW,            /* Downloads_Schedule_Renew */
    CMD_DOWNLOADS_SCHEDULE_DEL,              /* Downloads_Schedule_Del */
    CMD_DOWNLOADS_SCHEDULE_TEST,             /* Downloads_Schedule_Test */
    CMD_DOWNLOADS_SCHEDULE_START,            /* Downloads_Schedule_Start */
    CMD_DOWNLOADS_SCHEDULE_STOP,             /* Downloads_Schedule_Stop */
    CMD_APP_DOWNLOAD_END,

    /**** Add-on ****/
    CMD_MODULE_SHOW_INSTALL_STATUS,          /* module_show_install_status */
    CMD_GET_ALLAPPS,                         /* cgi_get_allapps */
    CMD_GET_APKG_DETAIL,                     /* cgi_get_apkg_detail */
    CMD_MYFAV_CHECK_IMG,                     /* cgi_myfavorite_check_img */
    CMD_CHK_HDD_FREE_SIZE,                   /* cgi_chk_hdd_free_size */
    CMD_DOWNLOAD_INSTALL_ADDON,              /* download_install_addon */
    CMD_CLEAR_ADDON_FILES,                   /* clear_addon_files */
    CMD_MODULE_RE_INSTALL,                   /* module_re_install */
    CMD_INSTALL_3_PARTY_APKG,                /* install_3_party_apkg */
    CMD_UNINSTALL_ADDON,                     /* uninstall_addon */
    CMD_MODULE_ENABLE_DISABLE,               /* module_enable_disable */
    CMD_MODULE_UNINSTALL,                    /* module_uninstall */
    CMD_ADD_ON_END,

    /**** Dashboard ****/
    CMD_GET_DEVICE_DETAIL_INFO,              /* cgi_get_device_detail_info */
    CMD_DASHBOARD_END,

    /**** Photo ****/
//    CMD_GET_MEDIA_FOLDER,                    /* cgi_get_media_folder */
//    CMD_GET_ALBUMS,                          /* cgi_get_albums */
//    CMD_GET_CURRENT_PATH,                    /* cgi_get_current_path */
//    CMD_CREATE_ALBUM,                        /* cgi_create_album */
//    CMD_GET_CURRENT_ALBUM_PATH,              /* cgi_get_current_album_path */
//    CMD_RELOAD_ALBUM_DB,                     /* cgi_reload_album_db */
//    CMD_GET_PERCENT,                         /* cgi_get_percent */
//    CMD_DEL_ALBUM,                           /* cgi_del_album */
//    CMD_MOVE_ALBUM,                          /* cgi_move_album */
//    CMD_GET_PHOTOS,                          /* cgi_get_photos */
//    CMD_GET_FULLSCREEN_PHOTOS,               /* cgi_get_fullscreen_photos */
//    CMD_GET_AIRPLAY_DEVICE,                  /* cgi_get_airplay_device */
//    CMD_ROTATE_IMAGE,                        /* cgi_rotate_image */
//    CMD_GET_COOLIRIS,                        /* cgi_get_cooliris */
//    CMD_CHK_REFRESH_STATUS,                  /* cgi_chk_refresh_status */
//    CMD_PHOTO_END,

    /**** File ****/
    CMD_FOLDER_CONTENT,                      /* cgi_folder_content */
    CMD_EMPTY_FOLDER,                        /* cgi_empty_folder */
    CMD_GET_USER_QUOTA,                      /* cgi_get_user_quota */
    CMD_CHK_FILE,                            /* chk_file */
    CMD_COMPRESS,                            /* cgi_compress */
    CMD_DOWNLOAD,                            /* cgi_download */
    CMD_CP,                                  /* cgi_cp */
    CMD_MOVE,                                /* cgi_move */
    CMD_DEL,                                 /* cgi_del */
    CMD_RENAME,                              /* cgi_rename */
    CMD_GET_PROPERTIES,                      /* cgi_get_properties */
    CMD_CHANGE_PERMISSIONS,                  /* cgi_change_permision */
    CMD_ADD_ZIP,                             /* cgi_add_zip */
    CMD_UNZIP,                               /* cgi_unzip */
    CMD_UNTAR,                               /* cgi_untar */
    CMD_GET_SECDOWNLOAD_URL,                 /* cgi_get_secdownload_url */
    CMD_GET_COOLIRIS_RSS,                    /* get_cooliris_rss*/
    CMD_FILE_END,

    CMD_P2P_STATE,                           /* p2p_state */
    CMD_P2P_GET_LIST_BY_PRIORITY,            /* p2p_get_list_by_priority */
    CMD_P2P_ADD_TORRENT_URL,                 /* p2p_add_torrent_url */
    CMD_P2P_GET_URL_STATE,                   /* p2p_get_url_state */
    CMD_P2P_CURRENT_SES_STATE,               /* p2p_current_ses_state */
    CMD_P2P_ADD_TORRENT_FILE_NEW,            /* p2p_add_torrent_file_new */
    CMD_P2P_DEL_ALL_COMPLETED,               /* p2p_del_all_completed */
    CMD_P2P_GET_TORRENT_SCHEDULING,          /* p2p_get_torrent_scheduling */
    CMD_P2P_TORRENT_SCHEDULING_SET,          /* p2p_torrent_scheduling_set */
    CMD_P2P_DETAIL_TORRENT,                  /* p2p_detail_torrent */
    CMD_P2P_PRIORITY_SET,                    /* p2p_priority_set */
    CMD_P2P_DEL_TORRENT,                     /* p2p_del_torrent */
    CMD_P2P_GET_SETTING_INFO,                /* p2p_get_setting_info */
    CMD_P2P_GET_HD,                          /* p2p_get_hd */
    CMD_P2P_SET_CONFIG,                      /* p2p_set_config */
    CMD_P2P_END,

    CMD_GET_S3,                              /* cgi_get_s3 */
    CMD_S3,                                  /* cgi_s3 */
    CMD_S3_MODIFY,                           /* cgi_s3_modify */
    CMD_S3_DEL,                              /* cgi_s3_del */
    CMD_S3_START,                            /* cgi_s3_start */
    CMD_S3_STOP,                             /* cgi_s3_stop */
    CMD_S3_BACKUP,                           /* cgi_s3_backup */
    CMD_GET_RECOVERY,                        /* get_recovery */
    CMD_GET_PERCENT,                         /* get_precent */
    CMD_CLEAR_PERCENT,                       /* clear_percent */
    CMD_S3_END,

    CMD_GD_1,                                /* 1 */
    CMD_GD_2,                                /* 2 */
    CMD_GD_3,                                /* 3 */
    CMD_GD_4,                                /* 4 */
    CMD_GD_END,

    CMD_1,                                   /* 1 */
    CMD_2,                                   /* 2 */
    CMD_3,                                   /* 3 */
    CMD_4,                                   /* 4 */
    CMD_5,                                   /* 5 */
    CMD_6,                                   /* 6 */
    CMD_7,                                   /* 7 */
    CMD_8,                                   /* 8 */
    CMD_9,                                   /* 9 */
    CMD_10,                                   /* 10 */
    CMD_11,                                   /* 11 */
    CMD_12,                                   /* 12 */
    CMD_13,                                   /* 13 */
    CMD_14,                                   /* 14 */
    CMD_15,                                   /* 15 */
    CMD_16,                                   /* 16 */
    CMD_17,                                   /* 17 */
    CMD_18,                                   /* 18 */
    CMD_19,                                   /* 19 */
    CMD_20,                                   /* 20 */
    CMD_21,                                   /* 21 */
    CMD_22,                                   /* 22 */
    CMD_MYDLINK_END,

    CMD_SIZE

};

enum SPECIAL_CMD_GROUP {
    CMD_GRP_NONE = 0,
    CMD_GRP_GOOGLE_DRIVE,
};

const int CMD_GROUP_SPACE[][3] {
    /* group_name,                  start,                  end */
    { CMD_GRP_NONE,                 0,                      CMD_SIZE - 1   },
    { CMD_GRP_GOOGLE_DRIVE,         CMD_GD_1,               CMD_GD_END     },
};

const char CGI_PARA_COMMANDS[][255] = {

    /**** Disk ****/
    "cgi_Volume_Status",
    "cgi_FMT_Get_Sync_State",
    "cgi_FMT_Get_Auto_Rebuild_Info",
    "cgi_AJAXPlorer_Stop",
    "cgi_FMT_Create_DiskMGR",
    "cgi_FMT_Remain_DiskMGR",
    "cgi_Disk_Remount",
    "cgi_FMT_GUI_Log",
    "cgi_Check_Disk_Format_Remount_State",
    "cgi_FMT_Disk_Finish",
    "cgi_SMART_HD_List",
    "SMART_XML_Create_Test_List",
    "SMART_Schedule_List",
    "SMART_Get_Test_Status",
    "SMART_Set_Schedule",
    "cgi_SMART_Test_Start",
    "ScanDisk_info",
    "cgi_Check_Disk_Remount_State",
    "ScanDisk_run_e2fsck",
    "ScanDisk_Finish",
    "cgi_VE_List",
    "cgi_VE_PWD_Check",
    "cgi_VE_Verify_KeyFile",
    "cgi_VE_Mofify",
    "cgi_VE_Save_File",
    "",

    /**** Home Page ****/
    "cgi_is_build_in_language",
    "cgi_get_user_language",
    "cgi_get_ssl_info",
    "ui_check_wto",
    "cgi_get_fw_status",
    "login",
    "logout",
    "cgi_set_user_language",
    "cgi_get_log_item",
    "",

    /**** Network ****/
    "cgi_get_lltd",
    "cgi_get_lan_xml",
    "cgi_get_ipv6",
    "cgi_get_lan_status",
    "cgi_get_lan_xml2",
    "cgi_setip_lock",
    "cgi_ip",
    "cgi_default_gw",
    "cgi_set_ipv6",
    "cgi_chk_ipv6_addr",
    "cgi_chk_gw_addr",
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
    "cgi_portforwarding_get_port",

    "cgi_get_ssh_port",
    "cgi_set_ssh_port",
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
    "",

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
    "cgi_get_share_info",
    "cgi_get_ftp",
    "Webdav_Account_Info",

    /**** ISO mount share ****/
    "cgi_set_iso_share",
    "cgi_get_iso_share_detail",
    "cgi_get_nfs_share_info",
    "cgi_get_modify_iso_info",
    "cgi_modify_iso_share",
    "cgi_del_iso_share",
    "cgi_chk_img_name",
    "cgi_chk_hd_size",
    "cgi_iso_config",
    "cgi_iso_create_path",
    "cgi_iso_size",
    //"cgi_del",
    "cgi_iso_create_image",
    "",

    /**** Application Management ****/
    "cgi_set_afp",
    "cgi_nfs_enable",

    /**** Multimedia Services ****/
    "cgi_chk_db",
    "UPnP_AV_Server_Path_List",
    "UPnP_AV_Server_Get_Config",
    "UPnP_AV_Server",
    "UPnP_AV_Server_Get_SQLDB_State",
    "GUI_codepage_get_list",
    "iTunes_Server_Get_XML",
    "iTunes_Server_Ready",
    "UPnP_AV_Server_Check_Path",
    "UPnP_AV_Server_Path_Setting",
    "CGI_SQLDB_Stop_Finish",
    "UPnP_AV_Server_Prescan",
    "UPnP_AV_Server_Path_Del",
    "UPnP_AV_Server_Setting",
    "GUI_codepage_add",
    "iTunes_Server_Setting",
    "iTunes_Server_Check_PS",
    "iTunes_Server_Refresh",
    "iTunes_Server_Refresh_State",


    /**** Syslog Server ****/
    "Syslog_Search",
    "Get_Volume_Info",
    "Syslog_Get_Log_File_Option",
    "Syslog_Get_Config",
    "Syslog_Get_Select_Option",
    "Syslog_Set_Config",
    "Syslog_Export",
    "Syslog_Get_Export_Status",
    "Syslog_Clear",

    /**** Local Backup ****/
    "Local_Backup_Now",
    "Local_Backup_List",
    "cgi_read_open_tree",
    "cgi_generic_open_tree",
	"Local_Backup_Samba_Format",
    "Local_Backup_Add",
    "Local_Backup_Info",
    "Local_Backup_Renew",
    "Local_Backup_Del",
    "Localbackup_Test",
    "Local_Backup_Start",
    "Local_Backup_Stop",

    "cgi_get_rsync_info",
    "cgi_set_rsync_server",

    "cgi_get_backup_list",
    "cgi_get_all_task_name",
    "cgi_server_test",
    "cgi_check_rsync_rw",
    "cgi_set_schedule",
    "cgi_get_modify_info",
    "cgi_del_schedule",
    "cgi_enable_disable_schedule",
    "cgi_backup_now",

    /**** Usb Backup ****/
    "cgi_mtp_info_get",
    "cgi_usb_backup_info_get",
    "cgi_mtp_info_set",
    "cgi_usb_backup_info_set",
    "cgi_get_USB_Mapping_Info",
	"cgi_open_usb_tree",
    "",

    /**** System Management ****/
    "cgi_get_time",
    "cgi_manual_time",
    "cgi_timezone",
    "cgi_ntp_time",
    "cgi_get_time_status",

    "cgi_get_device_info",
    "cgi_device",

    "cgi_Detect_Dangerous",
    "cgi_get_idle",
    "cgi_get_temperature",
    "cgi_get_restore_status",
    "cgi_restart",
    "cgi_restore",
    "cgi_shutdown",
    "cgi_idle",
    "cgi_temperature",
    "cgi_backup_conf",
    "cgi_restore_conf",

    "cgi_get_power_mgr_xml",
    "cgi_power_management",
    "cgi_power_recovery",
    "cgi_fan",
    "cgi_power_off_sch",

    "cgi_get_email_xml",
    "cgi_get_event_xml",
    "cgi_email_event",
    "cgi_email",
    "cgi_email_test",
    "cgi_email_test_result",
    "cgi_email_clear",

    "cgi_sms_add",
    "cgi_sms_modify",
    "cgi_sms_test",
    "cgi_sms_test_result",
    "cgi_sms_del",

    "cgi_log_system",
    "cgi_get_log_info",
    "cgi_log_server",
    "cgi_send_log_test",
    "cgi_log_backup",
    "cgi_log_clear",

    "GUI_ups_info",
    "GUI_ups_mater_list",
    "GUI_ups_slave_setting",
    "GUI_ups_ps",
    "cgi_usb_Storage_umount",
    "cgi_usb_printer_clear",

    "get_firm_v_xml",
    "check_power_sch",
    "cgi_firmware_init_upload",
    "cgi_firmware_upload",
    "cgi_get_percentage",
    "cgi_get_firmware_verify",
    "cgi_get_uP_fw",
    "cgi_reboot",
    "",

    /**** System Status ****/
    "cgi_get_status",
    //"cgi_get_temperature",
    "cgi_Status_Volume_Info",
    "cgi_usb_Storage_info",
    "cgi_mtp_info",
    "cgi_usb_printer_info",
    "cgi_ups_info2",

    "SMART_XML_Create_Device_List",
    "SMART_XML_Create_Smart_Info",

    "resource",

    "cgi_get_service",
    "module_list",
    "",
    
    /**** FTP Server ****/    
    "FTP_Server_Get_Config",
    "FTP_Server_EXIP_Renew",
    "p2p_get_port",
    "FTP_Server_BlockIP_List",
    "FTP_Server_BlockIP_Add",
    "FTP_Server_Enable",
    "FTP_Server_Set_Config",
    "",

    /**** Time Machine ****/
    "cgi_tm_get_info",
    "cgi_tm_get_list",
    "cgi_tm_get_smb_list",
    "cgi_tm_set",
    "cgi_tm_get_sharename",
    "cgi_tm_set_share",
    "cgi_tm_del_share",
    "cgi_tm_del_all_share",
	"",
	
    /**** Setup Wizard ****/
    "cgi_chk_admin_pw",
    "cgi_set_led",
    "cgi_get_wizard",
    "",

    /**** Application FTP/HTTP download ****/
    "Downloads_Schedule_Now",
    "Downloads_Schedule_List",
    "Downloads_Schedule_Add",
    "Downloads_Schedule_Info",
    "Downloads_Schedule_Renew",
    "Downloads_Schedule_Del",
    "Downloads_Schedule_Test",
    "Downloads_Schedule_Start",
    "Downloads_Schedule_Stop",
    "",

    /**** Add-on ****/
    "module_show_install_status",
    "cgi_get_allapps",
    "cgi_get_apkg_detail",
    "cgi_myfavorite_check_img",
    "cgi_chk_hdd_free_size",
    "download_install_addon",
    "clear_addon_files",
    "module_re_install",
    "install_3_party_apkg",
    "uninstall_addon",
    "module_enable_disable",
    "module_uninstall",
    "",

    /**** Dashboard ****/
    "cgi_get_device_detail_info",
    "",

//    /**** Photo ****/
//    "cgi_get_media_folder",
//    "cgi_get_albums",
//    "cgi_get_current_path",
//    "cgi_create_album",
//    "cgi_get_current_album_path",
//    "cgi_reload_album_db",
//    "cgi_get_percent",
//    "cgi_del_album",
//    "cgi_move_album",
//    "cgi_get_photos",
//    "cgi_get_fullscreen_photos",
//    "cgi_get_airplay_device",
//    "cgi_rotate_image",
//    "cgi_get_cooliris",
//    "cgi_chk_refresh_status",
//    ""

    /**** File ****/
    "cgi_folder_content",
    "cgi_empty_folder",
    "cgi_get_user_quota",
    "chk_file",
    "cgi_compress",
    "cgi_download",
    "cgi_cp",
    "cgi_move",
    "cgi_del",
    "cgi_rename",
    "cgi_get_properties",
    "cgi_change_permision",
    "cgi_add_zip",
    "cgi_unzip",
    "cgi_untar",
    "cgi_get_secdownload_url",
    "get_cooliris_rss",
    "",

    /**** P2P download ****/
    "p2p_state",
    "p2p_get_list_by_priority",
    "p2p_add_torrent_url",
    "p2p_get_url_state",
    "p2p_current_ses_state",
    "p2p_add_torrent_file_new",
    "p2p_del_all_completed",
    "p2p_get_torrent_scheduling",
    "p2p_torrent_scheduling_set",
    "p2p_detail_torrent",
    "p2p_priority_set",
    "p2p_del_torrent",
    "p2p_get_setting_info",
    "p2p_get_hd",
    "p2p_set_config",
    "",

    /**** Amazon S3 ****/
    "cgi_get_s3",
    "cgi_s3",
    "cgi_s3_modify",
    "cgi_s3_del",
    "cgi_s3_start",
    "cgi_s3_stop",
    "cgi_s3_backup",
    "get_recovery",
    "get_precent",
    "clear_percent",
    "",

    /**** Google Drive ****/
    "1",
    "2",
    "3",
    "4",
    "",

    /**** Mydlink Account ****/
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12",
    "13",
    "14",
    "15",
    "16",
    "17",
    "18",
    "19",
    "20",
    "21",
    "22",
    ""

};

const int EQUAL_COMMANDS[][2] {
    { CMD_READ_OPEN_TREE,           CMD_OPEN_TREE           },
    { CMD_GENERIC_OPEN_TREE,        CMD_OPEN_TREE           },
    { CMD_OPEN_USB_TREE,            CMD_OPEN_TREE           },
    { CMD_DOWNLOADS_SCHEDULE_NOW,   CMD_LOCAL_BACKUP_NOW    },
    { CMD_DOWNLOADS_SCHEDULE_LIST,  CMD_LOCAL_BACKUP_LIST   },
    { CMD_DOWNLOADS_SCHEDULE_ADD,   CMD_LOCAL_BACKUP_ADD    },
    { CMD_DOWNLOADS_SCHEDULE_INFO,  CMD_LOCAL_BACKUP_INFO   },
    { CMD_DOWNLOADS_SCHEDULE_RENEW, CMD_LOCAL_BACKUP_RENEW  },
    { CMD_DOWNLOADS_SCHEDULE_DEL,   CMD_LOCAL_BACKUP_DEL    },
    { CMD_DOWNLOADS_SCHEDULE_TEST,  CMD_LOCAL_BACKUP_TEST   },
    { CMD_DOWNLOADS_SCHEDULE_START, CMD_LOCAL_BACKUP_START },
    { CMD_DOWNLOADS_SCHEDULE_STOP,  CMD_LOCAL_BACKUP_STOP   },
};

const int CGI_COMMAND_TYPE_FILTER[][3] {
    { CMD_NONE,                         RENDER_TYPE_STRING,         OPENED_CMDS          },

    /**** Disk ****/
    { CMD_VOLUME_STATUS,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_Volume_Status" */
    { CMD_FMT_GET_SYNC_SATTE,           RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_FMT_Get_Sync_State */
    { CMD_FMT_GET_AUTO_REBUILD_INFO,    RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_FMT_Get_Auto_Rebuild_Info */
    { CMD_AJAXPLORER_STOP,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_AJAXPlorer_Stop */
    { CMD_FMT_CREATE_DISKMGR,           RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_FMT_Create_DiskMGR */
    { CMD_FMT_REMAIN_DISKMGR,           RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_FMT_Remain_DiskMGR */
    { CMD_DISK_REMOUNT,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_Disk_Remount */
    { CMD_FMT_GUI_LOG,                  RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_FMT_GUI_Log */
    { CMD_FMT_REMOUNT_STATE,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_Check_Disk_Format_Remount_State */
    { CMD_FMT_DISK_FINISH,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_FMT_Disk_Finish */
    { CMD_SMART_HD_LIST,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_SMART_HD_List */
    { CMD_SMART_XML_CREATE_TEST_LIST,   RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* SMART_XML_Create_Test_List */
    { CMD_SMART_SCHEDULE_LIST,          RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* SMART_Schedule_List */
    { CMD_SMART_GET_TEST_STATUS,        RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* SMART_Get_Test_Status */
    { CMD_SMART_SET_SCHEDULE,           RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* SMART_Set_Schedule */
    { CMD_SMART_TEST_START,             RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_SMART_Test_Start */
    { CMD_SCANDISK_INFO,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* ScanDisk_info */
    { CMD_CHECK_DISK_REMOUNT_STATUS,    RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_Check_Disk_Remount_State */
    { CMD_SCANDISK_RUN_E2FSCK,          RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* ScanDisk_run_e2fsck */
    { CMD_SCANDISK_FINISH,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* ScanDisk_Finish */
    { CMD_VE_LIST,                      RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_VE_List */
    { CMD_VE_PWD_CHECK,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_VE_PWD_Check */
    { CMD_VE_VERIFY_KEYFILE,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_VE_Verify_KeyFile */
    { CMD_VE_MODIFY,                    RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_VE_Mofify */
    { CMD_VE_SAVE_FILE,                 RENDER_TYPE_FILE,           COOKIE_REQ_CMDS      },          /* cgi_VE_Save_File */

    //{ CMD_DISK_END,                     RENDER_TYPE_UNKNOWN,        COOKIE_REQ_CMDS      },

    /**** Home Page ****/
    { CMD_CGI_IS_BUILD_IN_LANGUAGE,     RENDER_TYPE_XML,            LOGIN_CMDS          },          /* cgi_is_build_in_language */
    { CMD_GET_USER_LANGUAGE,            RENDER_TYPE_XML,            LOGIN_CMDS          },          /* cgi_get_user_language */
    { CMD_CGI_GET_SSL_INFO,             RENDER_TYPE_XML,            LOGIN_CMDS          },          /* cgi_get_ssl_info */
    { CMD_UI_CHECK_WTO,                 RENDER_TYPE_STRING,         LOGIN_CMDS          },          /* ui_check_wto */
    { CMD_FW_STATUS,                    RENDER_TYPE_STRING,         LOGIN_CMDS          },          /* cgi_get_fw_status */
    { CMD_LOGIN,                        RENDER_TYPE_USER_LOGIN,     LOGIN_CMDS          },          /* login */
    { CMD_LOGOUT,                       RENDER_TYPE_USER_LOGOUT,    LOGIN_CMDS          },          /* logout */
    { CMD_SET_USER_LANGUAGE,            RENDER_TYPE_XML,            LOGIN_CMDS          },          /* cgi_set_user_language */
    { CMD_GET_LOG_ITEM,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS     },          /* cgi_get_log_item */

//    CMD_LONGIN_END,

    /**** Network ****/
    { CMD_GET_LLTD,                     RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_lltd */
    { CMD_LAN_XML,                      RENDER_TYPE_XML,            OPENED_CMDS          },          /* cgi_get_lan_xml */
    { CMD_IPV6,                         RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_ipv6 */
    { CMD_LAN_STATUS,                   RENDER_TYPE_XML,            OPENED_CMDS          },          /* cgi_get_lan_status */
    { CMD_LAN_XML2,                     RENDER_TYPE_XML,            OPENED_CMDS          },          /* cgi_get_lan_xml2 */
    { CMD_SETIP_LOCK,                   RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_setip_lock */
    { CMD_IP,                           RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_ip */
    { CMD_DEFAULT_GW,                   RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_default_gw */
    { CMD_SET_IPV6,                     RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_set_ipv6 */
    { CMD_CHK_IPV6_ADDR,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_chk_ipv6_addr */
    { CMD_CHK_GW_ADDR,                  RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_chk_gw_addr */
    { CMD_SPEED,                        RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_speed */
    { CMD_LLTD,                         RENDER_TYPE_REDIRECT,       COOKIE_REQ_CMDS      },          /* cgi_lltd */
    { CMD_GET_DDNS,                     RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_ddns */
    { CMD_GET_DDNS_STATUS,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_ddns_status */
    { CMD_DDNS,                         RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_ddns */
    { CMD_PORTFORWARDING_GET,           RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_portforwarding_get */
    { CMD_UPNP_TEST,                    RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* upnp_test */
    { CMD_UPNP_TEST_RESULT,             RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },          /* upnp_test_result */
    { CMD_PORTFORWARDING_TOTAL,         RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },          /* cgi_portforwarding_total */
    { CMD_GET_PORT_TABLE,               RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* get_port_table */
    { CMD_PORTFORWARDING_ADD_SCAN,      RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },          /* cgi_portforwarding_add_scan */
    { CMD_PORTFORWARDING_ADD,           RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },          /* cgi_portforwarding_add */
    { CMD_PORTFORWARDING_MODIFY,        RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },          /* cgi_portforwarding_modify */
    { CMD_PORTFORWARDING_DEL,           RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },          /* cgi_portforwarding_del */
    { CMD_PORTFORWARDING_GET_PORT,      RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_portforwarding_get_port */

    { CMD_GET_SSH_PORT,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_ssh_port */
    { CMD_SET_SSH_PORT,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_set_ssh_port */
//    CMD_NETWORK_END,

    /**** Account ****/
    { CMD_CHANGE_ADMIN_PWD,             RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_chg_admin_pw */
    { CMD_GET_USER_LIST,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_user_list */
    { CMD_GET_USER_INFO,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_user_info */
    { CMD_GET_SMB_LIST,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_smb_list */
    { CMD_USER_ADD,                     RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_user_add */
    { CMD_RESTART_SERVICE,              RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_restart_service */
    { CMD_USER_SET_QUOTA,               RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_user_set_quota */
    { CMD_ADDUSER_TO_SESSION,           RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_adduser_to_session */
    { CMD_CREATE_FTP_LINK,              RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_create_ftp_link */
    { CMD_FTP_SERVICE,                  RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_ftp_service */
    { CMD_WEBDAV_ACCOUNT_MERGE,         RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* Webdav_Account_merge */
    { CMD_USER_BATCH_CREATE,            RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_user_batch_create */
    { CMD_GET_MODIFY_USER_INFO,         RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_modify_user_info */
    { CMD_USER_MODIFY,                  RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_user_modify */
    { CMD_USER_DEL,                     RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_user_del */
    { CMD_MYFAVORITE_DEL_USER,          RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_myfavorite_del_user */
    { CMD_DWONLOAD_IMPORT_SAMPLE,       RENDER_TYPE_FILE,           COOKIE_REQ_CMDS      },          /* cgi_download_import_sample */
    { CMD_GET_ALL_SESSION,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_all_session */
    { CMD_GET_IMPORT_USERS,             RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_import_uesrs */
    { CMD_ADDUSER_GET_USER_QUOTA_MAXSIZE, RENDER_TYPE_XML,          COOKIE_REQ_CMDS      },          /* cgi_adduser_get_user_quota_maxsize */
    { CMD_CREATE_IMPORT_USERS,          RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_create_import_users */
    { CMD_GET_CREATE_STATUS,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_create_status */

    /**** Group ****/
    { CMD_GET_GROUP_LIST,               RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_group_list */
    { CMD_GET_GROUP_INFO,               RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_group_info */
    { CMD_GROUP_ADD,                    RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_group_add */
    { CMD_ADDGROUP_GET_GROUP_QUOTA_MINSIZE, RENDER_TYPE_XML,        COOKIE_REQ_CMDS      },          /* cgi_addgroup_get_group_quota_minsize */
    { CMD_GROUP_SET_QUOTA,              RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_group_set_quota */
    { CMD_GET_MODIFY_GROUP_INFO,        RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },          /* cgi_get_modify_group_info */
    //CMD_WEBDAV_ACCOUNT_MERGE,               /* Webdav_Account_merge */
    { CMD_GROUP_MODIFY,                 RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_group_modify */
    { CMD_GROUP_DEL,                    RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },          /* cgi_group_del */

    /**** Quota ****/
    { CMD_GET_QUOTA_INFO,               RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_quota_info */
    { CMD_GET_HD_MAPPING_INFO,          RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_HD_Mapping_Info */
    { CMD_GET_USER_QUOTA_LIST,          RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_user_quota_list */
    { CMD_GET_GROUP_QUOTA_LIST,         RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_group_quota_list */
    { CMD_GET_USER_QUOTA_MAXSIZE,       RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_user_quota_maxsize */
    { CMD_GET_GROUP_QUOTA_MINSIZE,      RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_group_quota_minsize */
    { CMD_SET_QUOTA_ONOFF,              RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_set_quota_onoff */
//    CMD_ACCOUNT_END,

    /**** Network Share ****/
    { CMD_MODULE_GET_INFO,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Module_Get_Info */
    { CMD_GET_ADS_INFO,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_ads_info */
    { CMD_GET_SESSION,                  RENDER_TYPE_XML,            OPENED_CMDS          },         /* cgi_get_session */
    { CMD_GET_ISO_SHARE,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_iso_share */
    //CMD_GET_HD_MAPPING_INFO,                /* cgi_get_HD_Mapping_Info */
    { CMD_GET_AFP_INFO,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_afp_info */
    { CMD_GET_NFS_INFO,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_nfs_info */
    { CMD_ISO_PERCENTAGE,               RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_iso_percentage */
    { CMD_CLEAR_ISO_CREATE,             RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_clear_iso_create */
    { CMD_USER_LIST,                    RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_user_list */
    { CMD_GROUP_LIST,                   RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_group_list */
    //CMD_GET_ALL_SESSION,                    /* cgi_get_all_session */
    { CMD_GET_ALL_ISO_SHARE,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_all_iso_share */
    { CMD_OPEN_TREE,                    RENDER_TYPE_HTML,           COOKIE_REQ_CMDS      },         /* cgi_open_tree */
    { CMD_OPEN_NEW_FOLDER,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_open_new_folder */
    //CMD_FTP_SERVICE,                        /* cgi_ftp_service */
    { CMD_ADD_SESSION,                  RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_add_session */
    { CMD_SET_NFS_SHARE,                RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_set_nfs_share */
    //CMD_RESTART_SERVICE,                    /* cgi_restart_service */
    { CMD_GET_MODIFY_SESSION,           RENDER_TYPE_XML,            OPENED_CMDS          },         /* cgi_get_modify_session */
    { CMD_MODIFY_SESSION,               RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_modify_session */
    { CMD_MODIFY_NFS_SHARE,             RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_modify_nfs_share */
    { CMD_WEBDAV_ACCOUNT_ADD,           RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Webdav_Account_add */
    { CMD_DEL_SESSION,                  RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_del_session */
    { CMD_WEBDAV_ACCOUNT_DEL,           RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Webdav_Account_Del */
    { CMD_RESET_SESSION,                RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_reset_session */
    { CMD_GET_SHARE_INFO,               RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_share_info */
    { CMD_GET_FTP,                      RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_ftp */
    { CMD_WEBDAV_ACCOUNT_INFO,          RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Webdav_Account_Info */

    /**** ISO mount share ****/
    { CMD_SET_ISO_SHARE,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_set_iso_share */
    { CMD_GET_ISO_SHARE_DETAIL,         RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_iso_share_detail */
    { CMD_GET_NFS_SHARE_INFO,           RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_nfs_share_info */
    { CMD_GET_MODIFY_ISO_INFO,          RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_modify_iso_info */
    { CMD_MODIFY_ISO_SHARE,             RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_modify_iso_share */
    { CMD_DEL_ISO_SHARE,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_del_iso_share */
    { CMD_CHK_IMG_NAME,                 RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_chk_img_name */
    { CMD_CHK_HD_SIZE,                  RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_chk_hd_size */
    { CMD_ISO_CONFIG,                   RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_iso_config */
    { CMD_ISO_CREATE_PATH,              RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_iso_create_path */
    { CMD_ISO_SIZE,                     RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_iso_size */
    //{ CMD_DEL,                          RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_del */
    { CMD_ISO_CREATE_IMAGE,             RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_iso_create_image */
//    CMD_NETSHARE_END,

    /**** Application Management ****/
    { CMD_SET_AFP,                      RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_set_afp */
    { CMD_NFS_ENABLE,                   RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_nfs_enable */

    /**** Multimedia Services ****/
    { CMD_CHK_DB,                       RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_chk_db */
    { CMD_UPNP_AV_SERVER_PATH_LIST,     RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* UPnP_AV_Server_Path_List */
    { CMD_UPNP_AV_SERVER_GET_CONFIG,    RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* UPnP_AV_Server_Get_Config */
    { CMD_UPNP_AV_SERVER,               RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* UPnP_AV_Server */
    { CMD_UPNP_AV_SERVER_GET_SQLDB_STATE, RENDER_TYPE_XML,          COOKIE_REQ_CMDS      },         /* UPnP_AV_Server_Get_SQLDB_State */
    { CMD_GUI_CODEPAGE_GET_LIST,        RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* GUI_codepage_get_list */
    { CMD_ITUNES_SERVER_GET_XML,        RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* iTunes_Server_Get_XML */
    { CMD_ITUNES_SERVER_READY,          RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* iTunes_Server_Ready */
    { CMD_AV_SERVER_CHECK_PATH,         RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* UPnP_AV_Server_Check_Path */
    { CMD_AV_SERVER_PATH_SETTING,       RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* UPnP_AV_Server_Path_Setting */
    { CMD_SQLDB_STOP_FINISH,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* CGI_SQLDB_Stop_Finish */
    { CMD_UPNP_AV_SERVER_PRESCAN,       RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* UPnP_AV_Server_Prescan */
    { CMD_UPNP_AV_SERVER_PATH_DEL,      RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* UPnP_AV_Server_Path_Del */
    { CMD_UPNP_AV_SERVER_SETTING,       RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* UPnP_AV_Server_Setting */
    { CMD_GUI_CODEPAGE_ADD,             RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* GUI_codepage_add */
    { CMD_ITUNES_SERVER_SETTING,        RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* iTunes_Server_Setting */
    { CMD_ITUNES_SERVER_CHECK_PS,       RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* iTunes_Server_Check_PS */
    { CMD_ITUNES_SERVER_REFRESH,        RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* iTunes_Server_Refresh */
    { CMD_ITUNES_SERVER_REFRESH_STATE,  RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* iTunes_Server_Refresh_State */

    /**** Syslog Server ****/
    { CMD_SYSLOG_SEARCH,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Syslog_Search */
    { CMD_GET_VOLUME_INFO,              RENDER_TYPE_XML,            OPENED_CMDS          },         /* Get_Volume_Info */
    { CMD_SYSLOG_GET_LOG_FILE_OPTION,   RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Syslog_Get_Log_File_Option */
    { CMD_SYSLOG_GET_CONFIG,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Syslog_Get_Config */
    { CMD_SYSLOG_GET_SELECT_OPTION,     RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Syslog_Get_Select_Option */
    { CMD_SYSLOG_SET_CONFIG,            RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* Syslog_Set_Config */
    { CMD_SYSLOG_EXPORT,                RENDER_TYPE_FILE_REMOVE,           COOKIE_REQ_CMDS      },         /* Syslog_Export */
    { CMD_SYSLOG_GET_EXPORT_STATUS,     RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Syslog_Get_Export_Status */
    { CMD_SYSLOG_CLEAR,                 RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* Syslog_Clear */

    /**** Local Backup ****/
    { CMD_LOCAL_BACKUP_NOW,             RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Local_Backup_Now */
    { CMD_LOCAL_BACKUP_LIST,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Local_Backup_List */
    { CMD_READ_OPEN_TREE,               RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_read_open_tree */
    { CMD_GENERIC_OPEN_TREE,            RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_generic_open_tree */
    { CMD_LOCAL_BACKUP_SAMBA_FORMAT,    RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Local_Backup_Samba_Format */
    { CMD_LOCAL_BACKUP_ADD,             RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* Local_Backup_Add */
    { CMD_LOCAL_BACKUP_INFO,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Local_Backup_Info */
    { CMD_LOCAL_BACKUP_RENEW,           RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* Local_Backup_Renew */
    { CMD_LOCAL_BACKUP_DEL,             RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Local_Backup_Del */
    { CMD_LOCAL_BACKUP_TEST,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Localbackup_Test */
    { CMD_LOCAL_BACKUP_START,           RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* Localbackup_Start */
    { CMD_LOCAL_BACKUP_STOP,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* Localbackup_Stop */

    { CMD_GET_RSYNC_INFO,               RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_rsync_info */
    { CMD_SET_RSYNC_SERVER,             RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_set_rsync_server */
    { CMD_GET_BACKUP_LIST,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_backup_list */
    { CMD_GET_ALL_TASK_NAME,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_all_task_name */
    { CMD_SERVER_TEST,                  RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_server_test */
    { CMD_CHECK_RSYNC_RW,               RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_check_rsync_rw */
    { CMD_SET_SCHEDULE,                 RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_set_schedule */
    { CMD_GET_MODIFY_INFO,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_modify_info */
    { CMD_DEL_SCHEDULE,                 RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_del_schedule */
    { CMD_ENABLE_DISABLE_SCHEDULE,      RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_enable_disable_schedule */
    { CMD_BACKUP_NOW,                   RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_backup_now */

    { CMD_MTP_INFO_GET,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_mtp_info_get */
    { CMD_USB_BACKUP_INFO_GET,          RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_usb_backup_info_get */
    { CMD_MTP_INFO_SET,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_mtp_info_set */
    { CMD_USB_BACKUP_INFO_SET,          RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_usb_backup_info_set */
    { CMD_GET_USB_MAPPING_INFO,         RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_USB_Mapping_Info */
    { CMD_OPEN_USB_TREE,                RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_open_usb_tree */

//    CMD_APP_MNGM_END,

    /**** System Management ****/
    { CMD_GET_TIME,                     RENDER_TYPE_XML,            OPENED_CMDS          },         /* cgi_get_time */
    { CMD_MANUAL_TIME,                  RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_manual_time */
    { CMD_TIMEZONE,                     RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_timezone */
    { CMD_NTP_TIME,                     RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_ntp_time */
    { CMD_GET_TIME_STATUS,              RENDER_TYPE_XML,            OPENED_CMDS          },         /* cgi_get_time_status */

    { CMD_GET_DEVICE_INFO,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_device_info */
    { CMD_DEVICE,                       RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_device */

    { CMD_DETECT_DANGEROUS,             RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_Detect_Dangerous */
    { CMD_GET_IDEL,                     RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_get_idle */
    { CMD_GET_TEMPERATURE,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_temperature */
    { CMD_GET_RESTORE_STATUS,           RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_get_restore_status */
    { CMD_RESTART,                      RENDER_TYPE_REDIRECT,       COOKIE_REQ_CMDS      },         /* cgi_restart */
    { CMD_RESTORE,                      RENDER_TYPE_REDIRECT,       COOKIE_REQ_CMDS      },         /* cgi_restore */
    { CMD_SHUTDOWN,                     RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_shutdown */
    { CMD_IDLE,                         RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_idle */
    { CMD_TEMPERATURE,                  RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_temperature */
    { CMD_BACKUP_CONF,                  RENDER_TYPE_FILE,           COOKIE_REQ_CMDS      },         /* cgi_backup_conf */
    { CMD_RESTORE_CONF,                 RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_restore_conf */

    { CMD_GET_POWER_MGR,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_power_mgr_xml */
    { CMD_POWER_MANAGEMENT,             RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_power_management */
    { CMD_POWER_RECV,                   RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_power_recovery */
    { CMD_FAN,                          RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_fan */
    { CMD_POWER_OFF_SCH,                RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_power_off_sch */

    { CMD_GET_EMAIL_XML,                RENDER_TYPE_XML,            OPENED_CMDS          },         /* cgi_get_email_xml */
    { CMD_GET_EVENT_XML,                RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_event_xml */
    { CMD_EMAIL_EVENT,                  RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_email_event */
    { CMD_EMAIL,                        RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_email */
    { CMD_EMAIL_TEST,                   RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_email_test */
    { CMD_EMAIL_TEST_RESULT,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_email_test_result */
    { CMD_EMAIL_CLEAR,                  RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_email_clear */

    { CMD_SMS_ADD,                      RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_sms_add */
    { CMD_SMS_MODIFY,                   RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_sms_modify */
    { CMD_SMS_TEST,                     RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_sms_test */
    { CMD_SMS_TEST_RESULT,              RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_sms_test_result */
    { CMD_SMS_DEL,                      RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_sms_del */

    { CMD_LOG_SYSTEM,                   RENDER_TYPE_JOSEN,          COOKIE_REQ_CMDS      },         /* cgi_log_system */
    { CMD_GET_LOG_INFO,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_log_info */
    { CMD_LOG_SERVER,                   RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_log_server */
    { CMD_SEND_LOG_TEST,                RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_send_log_test */
    { CMD_LOG_BACKUP,                   RENDER_TYPE_FILE,           COOKIE_REQ_CMDS      },         /* cgi_log_backup */
    { CMD_LOG_CLEAR,                    RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_log_clear */

    { CMD_GUI_UPS_INFO,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* GUI_ups_info */
    { CMD_GUI_UPS_MATER_LIST,           RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* GUI_ups_mater_list */
    { CMD_GUI_UPS_SLAVE_SETTING,        RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* GUI_ups_slave_setting */
    { CMD_GUI_UPS_PS,                   RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* GUI_ups_ps */
    { CMD_USB_STORAGE_UMOUNT,           RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_usb_Storage_umount */
    { CMD_USB_PRINTER_CLEAR,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_usb_printer_clear */

    { CMD_FIRM_V_XML,                   RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* get_firm_v_xml */
    { CMD_CHECK_POWER_SCH,              RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* check_power_sch */
    { CMD_FIRMWARE_INIT_UPLOAD,         RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_firmware_init_upload */
    { CMD_FIRMWARE_UPLOAD,              RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_firmware_upload */
    { CMD_GET_PERCENTAGE,               RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_get_percentage */
    { CMD_GET_FIRMWARE_VERIFY,          RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_get_firmware_verify */
    { CMD_GET_UP_FW,                    RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_get_uP_fw */
    { CMD_REBOOT,                       RENDER_TYPE_REDIRECT,       COOKIE_REQ_CMDS      },         /* cgi_reboot */

//    CMD_SYS_MNGM_END,

    /**** System Status ****/
    { CMD_GET_STATUS,                   RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_status */
    //CMD_GET_TEMPERATURE,                    /* cgi_get_temperature */
    { CMD_STATUS_VOLUME_INFO,           RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_Status_Volume_Info */
    { CMD_USB_STORAGE_INFO,             RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_usb_Storage_info */
    { CMD_MTP_INFO,                     RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_mtp_info */
    { CMD_USB_PRINTER_INFO,             RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_usb_printer_info */
    { CMD_UPS_INFO2,                    RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_ups_info2 */

    { CMD_SMART_XML_CREATE_DEVICE_LIST, RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* SMART_XML_Create_Device_List */
    { CMD_SMART_XML_CREATE_SMART_INFO,  RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* SMART_XML_Create_Smart_Info */

    { CMD_RESOURCE,                     RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* resource */

    { CMD_GET_SERVICE,                  RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_get_service */
    { CMD_MODULE_LIST,                  RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* module_list */

//    CMD_SYS_STATUS_END,

    /**** FTP Server ****/
    { CMD_FTP_SERVER_GET_CONFIG,        RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* FTP_Server_Get_Config */
    { CMD_FTP_SERVER_EXIP_RENEW,        RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* FTP_Server_EXIP_Renew */
    { CMD_P2P_GET_PORT,                 RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* p2p_get_port */
    { CMD_FTP_SERVER_BLOCKIP_LIST,      RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* FTP_Server_BlockIP_List */
    { CMD_FTP_SERVER_BLOCKIP_ADD,       RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* FTP_Server_BlockIP_Add */
    { CMD_FTP_SERVER_ENABLE,            RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* FTP_Server_Enable */
    { CMD_FTP_SERVER_SET_CONFIG,        RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* FTP_Server_Set_Config */

//    CMD_FTP_SERVER_END,

//    /**** Time Machine ****/
    { CMD_TM_GET_INFO,                  RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_tm_get_info */
    { CMD_TM_GET_LIST,                  RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_tm_get_list */
    { CMD_TM_GET_SMB_LIST,              RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_tm_get_smb_list */
    { CMD_TM_SET,                       RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_tm_set */
    { CMD_TM_GET_SHARENAME,             RENDER_TYPE_XML,            COOKIE_REQ_CMDS      },         /* cgi_tm_get_sharename */
    { CMD_TM_SET_SHARE,                 RENDER_TYPE_STRING,         COOKIE_REQ_CMDS      },         /* cgi_tm_set_share */
    { CMD_TM_DEL_SHARE,                 RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_tm_del_share */
    { CMD_TM_DEL_ALL_SHARE,             RENDER_TYPE_NULL,           COOKIE_REQ_CMDS      },         /* cgi_tm_del_all_share */
//  CMD_TIME_MACHINE_END

    /**** Setup Wizard ****/
    { CMD_CHK_ADMIN_PW,                 RENDER_TYPE_XML,            OPENED_CMDS          },         /* cgi_chk_admin_pw */
    { CMD_SET_LED,                      RENDER_TYPE_NULL,           OPENED_CMDS          },         /* cgi_set_led */
    { CMD_GET_WIZARD,                   RENDER_TYPE_XML,            OPENED_CMDS          },         /* cgi_get_wizard */
    //CMD_SETUP_WIZARD_END,

    /**** Application FTP/HTTP download ****/
    { CMD_DOWNLOADS_SCHEDULE_NOW,        RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* Downloads_Schedule_Now */
    { CMD_DOWNLOADS_SCHEDULE_LIST,       RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* Downloads_Schedule_List */
    { CMD_DOWNLOADS_SCHEDULE_ADD,        RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* Downloads_Schedule_Add */
    { CMD_DOWNLOADS_SCHEDULE_INFO,       RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* Downloads_Schedule_Info */
    { CMD_DOWNLOADS_SCHEDULE_RENEW,      RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* Downloads_Schedule_Renew */
    { CMD_DOWNLOADS_SCHEDULE_DEL,        RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* Downloads_Schedule_Del */
    { CMD_DOWNLOADS_SCHEDULE_TEST,       RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* Downloads_Schedule_Test */
    { CMD_DOWNLOADS_SCHEDULE_START,      RENDER_TYPE_NULL,           COOKIE_REQ_CMDS          },        /* Downloads_Schedule_Start */
    { CMD_DOWNLOADS_SCHEDULE_STOP,       RENDER_TYPE_NULL,           COOKIE_REQ_CMDS          },         /* Downloads_Schedule_Stop */

    //CMD_APP_DOWNLOAD_END,

    { CMD_MODULE_SHOW_INSTALL_STATUS,    RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* module_show_install_status */
    { CMD_GET_ALLAPPS,                   RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_allapps */
    { CMD_GET_APKG_DETAIL,               RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_apkg_detail */
    { CMD_MYFAV_CHECK_IMG,               RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_myfavorite_check_img */
    { CMD_CHK_HDD_FREE_SIZE,             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_chk_hdd_free_size */
    { CMD_DOWNLOAD_INSTALL_ADDON,        RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* download_install_addon */
    { CMD_CLEAR_ADDON_FILES,             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* clear_addon_files */
    { CMD_MODULE_RE_INSTALL,             RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* module_re_install */
    { CMD_INSTALL_3_PARTY_APKG,          RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* install_3_party_apkg */
    { CMD_UNINSTALL_ADDON,               RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* uninstall_addon */
    { CMD_MODULE_ENABLE_DISABLE,         RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* module_enable_disable */
    { CMD_MODULE_UNINSTALL,              RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* module_uninstall */

    //CMD_ADD_ON_END,


    { CMD_GET_DEVICE_DETAIL_INFO,        RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_device_detail_info */

    //CMD_DASHBOARD_END,

//    { CMD_GET_MEDIA_FOLDER,              RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_media_folder */
//    { CMD_GET_ALBUMS,                    RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_albums */
//    { CMD_GET_CURRENT_PATH,              RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_current_path */
//    { CMD_CREATE_ALBUM,                  RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_create_album */
//    { CMD_GET_CURRENT_ALBUM_PATH,        RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_current_album_path */
//    { CMD_RELOAD_ALBUM_DB,               RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* cgi_reload_album_db */
//    { CMD_GET_PERCENT,                   RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_percent */
//    { CMD_DEL_ALBUM,                     RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* cgi_del_album */
//    { CMD_MOVE_ALBUM,                    RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_move_album */
//    { CMD_GET_PHOTOS,                    RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_photos */
//    { CMD_GET_FULLSCREEN_PHOTOS,         RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_fullscreen_photos */
//    { CMD_GET_AIRPLAY_DEVICE,            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_airplay_device */
//    { CMD_ROTATE_IMAGE,                  RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_rotate_image */
//    { CMD_GET_COOLIRIS,                  RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* cgi_get_cooliris */
//    { CMD_CHK_REFRESH_STATUS,            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_chk_refresh_status */
    //CMD_PHOTO_END,

    { CMD_FOLDER_CONTENT,                RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_folder_content */
    { CMD_EMPTY_FOLDER,                  RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_empty_folder */
    { CMD_GET_USER_QUOTA,                RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_user_quota */
    { CMD_CHK_FILE,                      RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* chk_file */
    { CMD_COMPRESS,                      RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_compress */
    { CMD_DOWNLOAD,                      RENDER_TYPE_FILE,          COOKIE_REQ_CMDS          },         /* cgi_download */
    { CMD_CP,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_cp */
    { CMD_MOVE,                          RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_move */
    { CMD_DEL,                           RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_del */
    { CMD_RENAME,                        RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_rename */
    { CMD_GET_PROPERTIES,                RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_properties */
    { CMD_CHANGE_PERMISSIONS,            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_change_permision */
    { CMD_ADD_ZIP,                       RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_add_zip */
    { CMD_UNZIP,                         RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_unzip */
    { CMD_UNTAR,                         RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_untar */
    { CMD_GET_SECDOWNLOAD_URL,           RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_secdownload_url */
    { CMD_GET_COOLIRIS_RSS,              RENDER_TYPE_FILE,          COOKIE_REQ_CMDS          },         /* get_cooliris_rss */

    //CMD_FILE_END,

    { CMD_P2P_STATE,                     RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* p2p_state */
    { CMD_P2P_GET_LIST_BY_PRIORITY,      RENDER_TYPE_JOSEN,         COOKIE_REQ_CMDS          },         /* p2p_get_list_by_priority */
    { CMD_P2P_ADD_TORRENT_URL,           RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* p2p_add_torrent_url */
    { CMD_P2P_GET_URL_STATE,             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* p2p_get_url_state */
    { CMD_P2P_CURRENT_SES_STATE,         RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* p2p_current_ses_state */
    { CMD_P2P_ADD_TORRENT_FILE_NEW,      RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* p2p_add_torrent_file_new */
    { CMD_P2P_DEL_ALL_COMPLETED,         RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* p2p_del_all_completed */
    { CMD_P2P_GET_TORRENT_SCHEDULING,    RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* p2p_get_torrent_scheduling */
    { CMD_P2P_TORRENT_SCHEDULING_SET,    RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* p2p_torrent_scheduling_set */
    { CMD_P2P_DETAIL_TORRENT,            RENDER_TYPE_JOSEN,         COOKIE_REQ_CMDS          },         /* p2p_detail_torrent */
    { CMD_P2P_PRIORITY_SET,              RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* p2p_priority_set */
    { CMD_P2P_DEL_TORRENT,               RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* p2p_del_torrent */
    { CMD_P2P_GET_SETTING_INFO,          RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* p2p_get_setting_info */
    { CMD_P2P_GET_HD,                    RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* p2p_get_hd */
    { CMD_P2P_SET_CONFIG,                RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* p2p_set_config */

    //CMD_P2P_END,

    { CMD_GET_S3,                        RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* cgi_get_s3 */
    { CMD_S3,                            RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* cgi_s3 */
    { CMD_S3_MODIFY,                     RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* cgi_s3_modify */
    { CMD_S3_DEL,                        RENDER_TYPE_NULL,          COOKIE_REQ_CMDS          },         /* cgi_s3_del */
    { CMD_S3_START,                      RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* cgi_s3_start */
    { CMD_S3_STOP,                       RENDER_TYPE_NULL,          COOKIE_REQ_CMDS          },         /* cgi_s3_stop */
    { CMD_S3_BACKUP,                     RENDER_TYPE_STRING,        COOKIE_REQ_CMDS          },         /* cgi_s3_backup */
    { CMD_GET_RECOVERY,                  RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* get_recovery */
    { CMD_GET_PERCENT,                   RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* get_precent */
    { CMD_CLEAR_PERCENT,                 RENDER_TYPE_NULL,          COOKIE_REQ_CMDS          },         /* clear_percent */
    //CMD_S3_END,

    { CMD_GD_1,                          RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 1 */
    { CMD_GD_2,                          RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 2 */
    { CMD_GD_3,                          RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 3 */
    { CMD_GD_4,                          RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 4 */
    // CMD_GD_END,

    { CMD_1,                             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 1 */
    { CMD_2,                             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 2 */
    { CMD_3,                             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 3 */
    { CMD_4,                             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 4 */
    { CMD_5,                             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 5 */
    { CMD_6,                             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 6 */
    { CMD_7,                             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 7 */
    { CMD_8,                             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 8 */
    { CMD_9,                             RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 9 */
    { CMD_10,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 10 */
    { CMD_11,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 11 */
    { CMD_12,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 12 */
    { CMD_13,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 13 */
    { CMD_14,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 14 */
    { CMD_15,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 15 */
    { CMD_16,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 16 */
    { CMD_17,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 17 */
    { CMD_18,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 18 */
    { CMD_19,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 19 */
    { CMD_20,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 20 */
    { CMD_21,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 21 */
    { CMD_22,                            RENDER_TYPE_XML,           COOKIE_REQ_CMDS          },         /* 22 */

    //CMD_MYDLINK_END,

//    CMD_SIZE

};

#endif // COMMANDDEFINE_H

