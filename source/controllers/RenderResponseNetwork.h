#ifndef RENDERRESPONSENETWORK_H
#define RENDERRESPONSENETWORK_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseNetwork : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseNetwork(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseNetwork();

    virtual void preRender();

private:

    void generateGetLLTD(QDomDocument &);
    void generateLanXml(QDomDocument &);
    void generateIPV6(QDomDocument &);
    void generateLanStatus(QDomDocument &);
    void generateLanXml2(QDomDocument &);
    void generateSetIPLock();
    void generateIP();
    void generateDefaultGw();
    void generateSetIPv6();
    void generateChkIPv6Addr();
    void generateChkGwAddr();
    void generateSpeed();
    void generateLLTD(QDomDocument &);
    void generateGetDdns(QDomDocument &);
    void generateGetDdnsStatus(QDomDocument &);
    void generateDdns(QDomDocument &);
    void generatePortForwardingGet(QDomDocument &);
    void generateUpnpTest();
    void generateUpnpTestResult(QString &);
    void generatePortForwardingTotal(QString &);
    void generateGetPortTable(QDomDocument &);
    void generatePortFrowardingAddScan(QString &);
    void generatePortFrowardingAdd(QString &);
    void generatePortFrowardingModify(QString &);
    void generatePortFrowardingDel(QString &);
    void generatePortFrowardingGetPort(QDomDocument &);

    void generateGetSshPort(QDomDocument &);
    void generateSetSshPort(QDomDocument &);
};

#endif // RENDERRESPONSENETWORK_H
