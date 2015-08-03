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

    void generateGetLLTD();
    void generateLanXml();
    void generateIPV6();
    void generateLanStatus();
    void generateLanXml2();
    void generateSetIPLock();
    void generateIP();
    void generateDefaultGw();
    void generateSetIPv6();
    void generateChkIPv6Addr();
    void generateChkGwAddr();
    void generateSpeed();
    void generateLLTD();
    void generateGetDdns();
    void generateGetDdnsStatus();
    void generateDdns();
    void generatePortForwardingGet();
    void generateUpnpTest();
    void generateUpnpTestResult();
    void generatePortForwardingTotal();
    void generateGetPortTable();
    void generatePortFrowardingAddScan();
    void generatePortFrowardingAdd();
    void generatePortFrowardingModify();
    void generatePortFrowardingDel();
    void generatePortFrowardingGetPort();

    void generateGetSshPort();
    void generateSetSshPort();
};

#endif // RENDERRESPONSENETWORK_H
