#ifndef __HTTP_FTP_DOWNLOAD_H__
#define __HTTP_FTP_DOWNLOAD_H__

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
    int is_download; // 1=ftp/http 0=backup
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
  } DOWNLOAD_TASK;

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
    int is_download; // 1=ftp/http 0=backup
    int is_src_login;
    int is_dst_login;
    int is_file; // 0=folder 1=file
    DATE_S task_id_date; // generate 20 digital linux timestamp
    char *execat; // execute time
    char *login_id; // system login id from cookie
    char *src;
    char *src_user; // this value matters if is_src_login=1
    char *src_pwd; // this value matters if is_src_login=1
    char *dest;
    char *dst_user; // this value matters if is_dst_login=1
    char *dst_pwd; // this value matters if is_dst_login=1
    int recur_type; // 0=none 1=day 2=week 3=month
    int recur_date; // 0~6 | 1~31 (int) //period=2 -> 0~6=Sun、Mon、Tue、Wed、Thu、Fri、Sat . period=3 -> 1~31
    int is_inc; // this value matters if is_download=0
    char *rename; // this value matters if is_download=1 && is_file=1
    char *charset; // this value matter if is_download=1
    char *comment; // task result status
    char *task_name; // empty now.
  } DOWNLOAD_TASK_INFO;

typedef struct
{
    int result;
    unsigned long long size;
} DOWNLOAD_TEST_RESULT;

typedef struct
{
    char *src;
    char *dest;
    char *percent;
    char *status;
    char *speed;
    char *execat;
    char *comment;
} DOWNLOAD_LIST;

RESULT_STATUS GetTaskXmlValue(char *mnt_path, char *task_id, DOWNLOAD_TASK_TAG tag, DOWNLOAD_TASK *task); // return value need free
RESULT_STATUS GetTaskXmlValueTimer(char *task_path, DOWNLOAD_TASK_TAG tag, DOWNLOAD_TASK *task); // return value need free
void FreeTask(DOWNLOAD_TASK *task);

RESULT_STATUS SaveTaskXml(char *mnt_path, DOWNLOAD_TASK_INFO task_info, char **task_id);
RESULT_STATUS DeleteTaskXml(char *mnt_path, char *task_id);
RESULT_STATUS TestDownloadTask(int f_type, char *f_suser, char *f_passwd, char *lang, char *src, DOWNLOAD_TEST_RESULT *result);

RESULT_STATUS GetListXmlValue(char *mnt_path, char *task_id, DOWNLOAD_LIST *task); // return value need free
void FreeList(DOWNLOAD_LIST *task);

void StartTimerDownload(char *task_path);
RESULT_STATUS StartTask(char *mnt_path, char *task_id);
void StopTask(char *mnt_path, char *task_id);
RESULT_STATUS UpdateXmlStatus(char *mnt_path, char *task_id, char *status, char *comment);
void UpdateTaskPercent(char *mnt_path, char *task_id);

int GetCodepageList(int idx, char **name, char **desc); // return values need free

RESULT_STATUS TestBackupTask(int f_type, char *f_suser, char *f_passwd, char *src, DOWNLOAD_TEST_RESULT *result);

#endif
