#ifndef RENDERRESPONSEAPPDOWNLOADS_H
#define RENDERRESPONSEAPPDOWNLOADS_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseAppDownloads : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseAppDownloads(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseAppDownloads();

    virtual void preRender();

private:

//    void generateDownloadsScheduleNow(QDomDocument &);
//    void generateDownloadsScheduleList(QDomDocument &);
//    void generateDownloadsScheduleAdd(QString &);
//    void generateDownloadsScheduleInfo(QDomDocument &);
//    void generateDownloadsScheduleRenew(QString &);
//    void generateDownloadsScheduleDel(QDomDocument &);
//    void generateDownloadsScheduleTest(QDomDocument &);

};

#endif // RENDERRESPONSEAPPDOWNLOADS_H
