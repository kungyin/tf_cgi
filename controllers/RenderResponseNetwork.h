#ifndef RENDERRESPONSENETWORK_H
#define RENDERRESPONSENETWORK_H

#include "RenderResponseBase.h"

class T_CONTROLLER_EXPORT RenderResponseNetwork : public RenderResponseBase {
    Q_OBJECT
public:
    RenderResponseNetwork(QVariantMap &, CGI_COMMAND);
    RenderResponseNetwork(const RenderResponseNetwork &other) {}
    virtual ~RenderResponseNetwork();

    virtual RENDER_TYPE preRender();

private:

    void generateGetLLTD(QDomDocument &);
    void generateLanXml(QDomDocument &);
    void generateIPV6(QDomDocument &);
    void generateLanStatus(QDomDocument &);
    void generateLanXml2(QDomDocument &);
    void generateSetIPLock(QDomDocument &);
    void generateIP(QDomDocument &);
    void generateSpeed(QDomDocument &);
    void generateLLTD(QDomDocument &);
    void generateGetDdns(QDomDocument &);
    void generateGetDdnsStatus(QDomDocument &);
    void generateDdns(QDomDocument &);
    void generatePortForwardingGet(QDomDocument &);
    void generateUpnpTest(QString &);
    void generateUpnpTestResult(QString &);
    void generatePortForwardingTotal(QString &);
    void generateGetPortTable(QDomDocument &);
    void generatePortFrowardingAddScan(QString &);
    void generatePortFrowardingAdd(QString &);
    void generatePortFrowardingModify(QString &);
    void generatePortFrowardingDel(QString &);
};

#endif // RENDERRESPONSENETWORK_H
