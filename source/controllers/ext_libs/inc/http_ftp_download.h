#ifndef __HTTP_FTP_DOWNLOAD_H__
#define __HTTP_FTP_DOWNLOAD_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    RET_SUCCESS = 0,
    RET_READ_ERR,
    RET_MOUNT_PATH_ERR,
    RET_GEN_TASK_ID_ERR,
    RET_ALLOCATE_MEMORY_ERR,
    RET_DELETE_TASK_ERR,
    RET_XML_READ_DOC_ERR,
    RET_TEST_TASK_ERR,
    RET_START_TASK_ERR,
    RET_TEST_LOCAL_ERR,
    RET_GET_RSYNC_INFO_ERR,
    RET_SET_RSYNC_INFO_ERR,
    RET_GEN_REMOTE_TASK_ERR,
    RET_TEST_REMOTE_ERR,
} RESULT_STATUS;

typedef enum
{
    TAG_ALL = 0,
    TAG_IDX,
    TAG_STATUS,
    TAG_PERIOD,
    TAG_RECUR_DATE,
    TAG_FILE_TYPE,
    TAG_SRC,
    TAG_DEST,
    TAG_SRC_USER,
    TAG_SRC_PWD,
    TAG_DST_USER,
    TAG_DST_PWD,
    TAG_EXECAT,
    TAG_RENAME,
    TAG_OPTION,
    TAG_NUM
} DOWNLOAD_TASK_TAG;

typedef struct
{
    int is_download; // 1=ftp/http 0=backup 2=remote backup
    char *idx; // task id
    char *status; // 0 | 2 | 3 | 4 | 6 (int) //0=status_queue, 2=status_queue or status_download, 3=status_ok, 4=status_fail, 6=icon_stop
    char *period; // 0=none 1=day 2=week 3=month
    char *recur_date; // 0~6 | 1~31 (int) //period=2 -> 0~6=Sun、Mon、Tue、Wed、Thu、Fri、Sat . period=3 -> 1~31
    int is_file; // 0=folder 1=file
    char *src;
    char *dest;
    char *src_user; // this value matters if is_src_login=1
    char *src_pwd; // this value matters if is_src_login=1
    char *dst_user; // this value matters if is_dst_login=1
    char *dst_pwd; // this value matters if is_dst_login=1
    char *execat; // execute time
    char *rename; // for file name only
    union
    {
        char *lang;
        char *inc;
    } option; // lang for download, and inc from backup
} DOWNLOAD_TASK; //for task read back

typedef struct
{
    int year;
    int month;
    int day;
    int hour;
    int min;
} DATE_S;

typedef struct
  {
    int is_download; // 1=ftp/http 0=backup 2=remote backup
    int is_src_login;
    int is_dst_login;
    int is_file; // 0=folder 1=file
    DATE_S task_id_date; // generate 20 digital linux timestamp, this first char=is_download (1=ftp/http 0=backup)
    char *execat; // execute time
    char *login_id; // system login id from cookie
    char *src;
    char *src_user; // this value matters if is_src_login=1
    char *src_pwd; // this value matters if is_src_login=1
    char *dest;
    char *dst_user; // this value matters if is_dst_login=1
    char *dst_pwd; // this value matters if is_dst_login=1
    int recur_type; // 0=none 1=day 2=week 3=month 4=once
    int recur_date; // 0~6 | 1~31 (int) //period=2 -> 0~6=Sun、Mon、Tue、Wed、Thu、Fri、Sat . period=3 -> 1~31
    int is_inc; // this value matters if is_download=0|2
    char *rename; // this value matters if is_download=1 && is_file=1
    char *charset; // this value matter if is_download=1
    char *comment; // task result status
    char *task_name; // null if is_download=0|1
  } DOWNLOAD_TASK_INFO; // for write task

typedef struct
{
    int result;
    unsigned long long size;
} DOWNLOAD_TEST_RESULT;

typedef struct
{
    char *task_id;
    char *src;
    char *dest;
    char *percent;
    char *status;
    char *speed;
    char *execat;
    char *comment;
} DOWNLOAD_LIST;

typedef struct
{
    int is_enable;
    char *pwd;
    char *local_ip;
} RSYNC_INFO;

typedef enum
{
    TAG_R_ALL = 0,
    TAG_R_TASK_NAME,
    TAG_R_ENABLE,
    TAG_R_STATE,
    TAG_R_SERVER_TYPE,
    TAG_R_BACKUP_TYPE,
    TAG_R_SCHED_MODE,
    TAG_R_USE_SSH,
    TAG_R_KEEP_EXIST,
    TAG_R_INC_ENABLE,
    TAG_R_INC_NUM,
    TAG_R_RSYNC_USER,
    TAG_R_RSYNC_PWD,
    TAG_R_SSH_USER,
    TAG_R_SSH_PWD,
    TAG_R_IP,
    TAG_R_PATH,
    TAG_R_LOCAL_PATH,
    TAG_R_EXECAT,
    TAG_R_RECUR_TYPE,
    TAG_R_RECUR_DATE,
    TAG_R_PERCENT,
    TAG_R_COMMENT,
    TAG_R_NUM
} REMOTE_BACKUP_TAG;

typedef struct
{
    char *task_name; // uniqle id. auto add 2 in front of file name.
    int is_enable; // 1=enable, 0=disable
    int state;
    int server_type; //1=nas to nas, 2=nas to linux
    int backup_type; //1=local to remote, 2=remote to local
    int schedule_mode; // 1~3 (int) schedule mode, 1-> manual(default), 2-> once, 3-> schedule
    int is_use_ssh;
    int is_keep_exist_file;
    int is_inc_enable;
    int inc_number; // this value matters if is_inc=1
    char *rsync_user;
    char *rsync_pwd;
    char *ssh_user; // this value matters if is_use_ssh=1
    char *ssh_pwd; // this value matters if is_use_ssh=1
    char *remote_ip;
    char *remote_path;
    char *local_path;
    char *execat;
    int recur_type;
    int recur_date;
    char *percent;
    char *comment;
} REMOTE_BACKUP_INFO; // if modify, int variables=-1 and string variables=NULL means not to modify.

typedef struct
{
    char *task_name;
    char *schedule_mode;
    char *state;
    char *enable;
} REMOTE_LIST;

typedef struct
{
    int ssh_test_result; //ssh_test_status= 1 | 2 | 3 | 4 | 5 (int) //0=no used; 1=SSH Test Result: Successfully, 2=SSH Test Failed, 3=Unknown SSH Host, 4=Unknown Reason Failed, 5=SSH Deny Access, 6=SSH Key Change Failed
    int rsync_test_result; //101 | 102 | 103 | 104 | 105 | 106 | 107 | 108 (int) //101=RSYNC Test Result: Successfully, 102=RSYNC Test Failed, 103=RSYNC Server Refused, 104=SSH Refused, 105=Remote Path Not Exist, 106=Remote Share Read Only, 107=RSYNC Module Not Exist, 108=Password Failed
} REMOTE_TEST_RESULT;

RESULT_STATUS GetTaskXmlValue(char *task_id, DOWNLOAD_TASK_TAG tag, DOWNLOAD_TASK *task); // return value need free
void FreeTask(DOWNLOAD_TASK *task);

RESULT_STATUS SaveTaskXml(DOWNLOAD_TASK_INFO task_info, char **task_id);
RESULT_STATUS DeleteTaskXml(char *task_id);
RESULT_STATUS TestDownloadTask(int f_type, char *f_suser, char *f_passwd, char *lang, char *src, DOWNLOAD_TEST_RESULT *result);

RESULT_STATUS GetListXmlValue(int type, int page, int rp, int *total, int *page_cnt, DOWNLOAD_LIST **list); // return value need free
void FreeList(DOWNLOAD_LIST *list);

RESULT_STATUS StartTask(char *task_id);
void StopTask(char *task_id);
RESULT_STATUS UpdateXmlStatus(char *task_id, char *status, char *comment);
void UpdateTaskPercent(char *task_id);

int GetCodepageList(int idx, char **name, char **desc); // return values need free

RESULT_STATUS TestBackupTask(int f_type, char *f_suser, char *f_passwd, char *src, DOWNLOAD_TEST_RESULT *result);

RESULT_STATUS GetRsyncInfo(RSYNC_INFO *rsync_info); // return values need free
void FreeRsyncInfo(RSYNC_INFO *rsync_info);
RESULT_STATUS SetRsyncInfo(int is_enable, char *pwd); // it will start rsync server. read RSYNC_SHARE_NODE

RESULT_STATUS SaveRemoteXml(REMOTE_BACKUP_INFO r_info, int is_add);
RESULT_STATUS GetRemoteTaskXmlValue(char *task_name, REMOTE_BACKUP_TAG tag, REMOTE_BACKUP_INFO *r_info); // return value need free
void FreeRemoteTask(REMOTE_BACKUP_INFO *r_info);
RESULT_STATUS TestRemoteBackupTask(char *ip, int s_type, int direction, char *task, char *local_path, int encryption, int keep_exist_file, char *rsync_user, char *rsync_pw, char *ssh_user, char *ssh_pw, REMOTE_TEST_RESULT *result);
void StopRemoteTask(char *task_name);
RESULT_STATUS DeleteRemoteTaskXml(char *task_name);
RESULT_STATUS UpdateRemoteXmlStatus(char *task_name, char *state, char *comment, char *enable);

void GetRsyncSharePath(char *name, char **path); // return values(*path) need free
void GetLocalDeviceSizeString(char *path, char *exclude_file_path, char **size_string); // return values need free
int TestSSHConnect(char *ip, char *ssh_user, char *ssh_pwd); // nas to nas use ssh direct, remote share node and size need another api(use root default ssh login to get).
int TestRsyncConnect(char *ip, int s_type, int direction, char *task, char *local_path, int encryption, int keep_exist_file, char *rsync_user, char *rsync_pw, char *ssh_user, char *ssh_pwd);
void StartStopRemoteTask(char *task_name, char *enable);
void StartRemoteTask(char *task_name);
void UpdateRemoteTaskPercent(char *task_name);
RESULT_STATUS GetRemoteListXmlValue(int page, int rp, int *total, int *page_cnt, REMOTE_LIST **list); // return value need free
void FreeRemoteList(REMOTE_LIST *list);

int GetAllRemoteTaskName(char ***name_list);
void FreeRemoteTaskName(int count, char ***name_list);

#ifdef __cplusplus
}
#endif

#endif
