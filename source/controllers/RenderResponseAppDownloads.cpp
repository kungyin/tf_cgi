#include "RenderResponseAppDownloads.h"

RenderResponseAppDownloads::RenderResponseAppDownloads(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseAppDownloads::~RenderResponseAppDownloads() {
}

void RenderResponseAppDownloads::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
//    case CMD_DOWNLOADS_SCHEDULE_NOW:
//        generateDownloadsScheduleNow(doc);
//        break;
//    case CMD_DOWNLOADS_SCHEDULE_LIST:
//        generateDownloadsScheduleList(doc);
//        break;
//    case CMD_DOWNLOADS_SCHEDULE_ADD:
//        generateDownloadsScheduleAdd(str);
//        break;
//    case CMD_DOWNLOADS_SCHEDULE_INFO:
//        generateDownloadsScheduleInfo(doc);
//        break;
//    case CMD_DOWNLOADS_SCHEDULE_RENEW:
//        generateDownloadsScheduleRenew(str);
//        break;
//    case CMD_DOWNLOADS_SCHEDULE_DEL:
//        generateDownloadsScheduleDel(doc);
//        break;
//    case CMD_DOWNLOADS_SCHEDULE_TEST:
//        generateDownloadsScheduleTest(doc);
//        break;
    case CMD_NONE:
    default:
        break;
    }


}




