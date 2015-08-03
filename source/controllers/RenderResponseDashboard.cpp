#include "RenderResponseDashboard.h"

RenderResponseDashboard::RenderResponseDashboard(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseDashboard::~RenderResponseDashboard() {
}

void RenderResponseDashboard::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_GET_DEVICE_DETAIL_INFO:
        generateGetDeviceDetailInfo();
        break;

    case CMD_NONE:
    default:
        break;
    }

}

/* todo */
void RenderResponseDashboard::generateGetDeviceDetailInfo() {
    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_status", true, ";");

    QDomElement root = doc.createElement("device_info");
    doc.appendChild(root);

    QStringList deviceInfoContentElement(QStringList()
            << "hostname" << "modelname" << "fanspeed" << "high_speed_temp"
            << "low_speed_temp" << "onlineuser" << "bonding_enable"
            << "lan_r_speed" << "lan_t_speed" << "lan2_r_speed" << "lan2_t_speed"
            << "mem_total" << "mem_free" << "buffers" << "cached" << "cpu");

//    if( deviceInfoContentElement.size() == apiOut.value(i).split(";").size() ) {

//        for(int i = 0; i < apiOut.value(i).split(";").size(); i++) {

//            QDomElement element = doc.createElement(deviceInfoContentElement.value(j));
//            printerElement.appendChild(element);
//            element.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(j)));
//        }
//    }
//    else {
//        //assert(0);
//        tError("RenderResponseSysStatus::generateGetDeviceDetailInfo() :"
//               "deviceInfoContentElement size is not equal to apiOut size.");
//    }

    m_var = doc.toString();
}

