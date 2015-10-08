#include "RenderResponseS3.h"

RenderResponseS3::RenderResponseS3(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseS3::~RenderResponseS3() {
}

void RenderResponseS3::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_GET_S3:
        generateGetS3();
        break;
    case CMD_S3:
        generateS3();
        break;
    case CMD_S3_MODIFY:
        generateS3Modify();
        break;
    case CMD_S3_GET_MODIFY:
        generateS3GetModify();
        break;
    case CMD_S3_DEL:
        generateS3Del();
        break;
    case CMD_S3_START:
        generateS3Start();
        break;
    case CMD_S3_STOP:
        generateS3Stop();
        break;
    case CMD_S3_BACKUP:
        generateS3Backup();
        break;
    case CMD_GET_RECOVERY:
        generateGetRecovery();
        break;
    case CMD_GET_PERCENT:
        generateGetPercent();
        break;
    case CMD_CLEAR_PERCENT:
        generateClearPercent();
        break;

    default:
        break;
    }

}

void RenderResponseS3::generateGetS3() {
    QDomDocument doc;
    QString paraPage = m_pReq->parameter("page");
    QString paraRp = m_pReq->parameter("rp");
    QString paraQuery = m_pReq->parameter("query");
    QString paraQType = m_pReq->parameter("qtype");
    QString paraField = m_pReq->parameter("f_field");
    QString paraUser = m_pReq->parameter("user");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_s3_info");

    QString cellContent0 = "<span style='display:none'>%1</span><span>%2</span>";
    QString cellContent3 = "<img border='0' src='/web/images/%1.png' width='27' height='17' onclick='parent.action_stop(\"%2\")'>";
    QString cellContent4 = "<img border='0' src='/web/images/%1.png' width='16' height='16' onclick='parent.backup_now(\"%2\")'>";
    QString cellContent5 = "<img border='0' src='/web/images/%1.png' width='16' height='16' onclick='parent.s3_reload(\"%2\")'>";
    QString cellContent6 = "<img border='0' src='/web/images/%1.png' width='16' height='16' onclick='parent.s3_open(\"%2\")'>";

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QStringList userInfoList(apiOut);
    int rp = paraRp.toInt();
    if(userInfoList.size() > rp)
        userInfoList = apiOut.mid((paraPage.toInt()-1) * rp, rp);

    for(QString e : userInfoList) {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        for(int i = 0; i < e.split(";").size(); i++) {
            if(i == 0) {
                QDomElement element = doc.createElement("cell");
                rowElement.appendChild(element);
                element.appendChild(doc.createCDATASection(cellContent0.arg(QString::number(i+1), e.split(";").value(i))));
            }
            else if(i == 3) {
                QString image = e.split(";").value(i) == "1" ? "stop" : "start";
                QDomElement element = doc.createElement("cell");
                rowElement.appendChild(element);
                element.appendChild(doc.createCDATASection(cellContent3.arg(image, e.split(";").value(0))));
            }
            else if(i == 4) {
                QString image = "backup";
                QString content = "--";
                if(e.split(";").value(i) == "1")
                    content = cellContent4.arg(image, e.split(";").value(0));
                QDomElement element = doc.createElement("cell");
                rowElement.appendChild(element);
                element.appendChild(doc.createCDATASection(content));
            }
            else if(i == 5) {
                QString image = "restore";
                QString content = "--";
                if(e.split(";").value(i) == "1")
                    content = cellContent5.arg(image, e.split(";").value(0));
                QDomElement element = doc.createElement("cell");
                rowElement.appendChild(element);
                element.appendChild(doc.createCDATASection(content));
            }
            else if(i == 6) {
                QString image = "detail";
                QString content = "--";
                if(e.split(";").value(i) == "1")
                    content = cellContent6.arg(image, e.split(";").value(0));
                QDomElement element = doc.createElement("cell");
                rowElement.appendChild(element);
                element.appendChild(doc.createCDATASection(content));
            }
            else {
                QDomElement element = doc.createElement("cell");
                rowElement.appendChild(element);
                element.appendChild(doc.createTextNode(e.split(";").value(i)));
            }
        }
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

    m_var = doc.toString();
}

void RenderResponseS3::generateS3() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_add_s3_account "
                                      + allParametersToString(), true);
    m_var = apiOut.value(0);
}

void RenderResponseS3::generateS3Modify() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_mod_s3_account "
                                      + allParametersToString(), true);
    m_var = apiOut.value(0);
}

void RenderResponseS3::generateS3GetModify() {

    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_s3_modify "
                                      + allParametersToString(), true, ";");

    QDomElement root = doc.createElement("s3");
    doc.appendChild(root);

    QStringList s3Tags(QStringList()
        << "dir" << "backuptype" << "a_key" << "p_key" << "b_path" << "location" << "n_path" << "schedule"
                       << "mday" << "hour" << "min");

    if( s3Tags.size() == apiOut.size() ) {
        for(int i=0; i < apiOut.size(); i++) {
            QString tagName = s3Tags.value(i);
            if(i == 8 && apiOut.value(7) == "0")
                tagName = "date";
            QDomElement element = doc.createElement(tagName);
            root.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseS3::generateS3GetModify() :"
            "s3Tags size is not equal to apiOut size.");

    }

    m_var = doc.toString();
}

void RenderResponseS3::generateS3Del() {

    QString paraJobName = m_pReq->parameter("f_job_name");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_del_s3_account "
                                      + paraJobName, true);
}

void RenderResponseS3::generateS3Start() {

    QString paraJobName = m_pReq->parameter("f_job_name");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_start_s3_account "
                                      + paraJobName, true);
    m_var = apiOut.value(0);
}

void RenderResponseS3::generateS3Stop() {

    QString paraJobName = m_pReq->parameter("f_job_name");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_stop_s3_account "
                                      + allParametersToString(), true);

}

void RenderResponseS3::generateS3Backup() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_s3_backup "
                                      + allParametersToString(), true);
    m_var = apiOut.value(0);

}

void RenderResponseS3::generateGetRecovery() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_restore_s3_account " + allParametersToString());

    QDomElement root = doc.createElement("s3");
    doc.appendChild(root);

    for(QString e : apiOut) {
        QDomElement backupElement = doc.createElement("backup");
        root.appendChild(backupElement);

        QDomElement jobnameElement = doc.createElement("jobname");
        backupElement.appendChild(jobnameElement);
        jobnameElement.appendChild(doc.createTextNode(e.split(";").value(0)));

        QDomElement timeElement = doc.createElement("time");
        backupElement.appendChild(timeElement);
        timeElement.appendChild(doc.createTextNode(e.split(";").value(1)));
    }

    m_var = doc.toString();
}

void RenderResponseS3::generateGetPercent() {
    QDomDocument doc;

    QString paraName = m_pReq->parameter("name");
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_s3_progress "
                                      + allParametersToString(), true, ";");

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);

    if(!apiOut.value(0).isEmpty() || !apiOut.value(1).isEmpty() || !apiOut.value(2).isEmpty()) {
        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);

        QStringList itemContentElement(QStringList()
            << "fileName" << "time" << "percent");

        for(int i=0; i < itemContentElement.size(); i++) {
            QDomElement element = doc.createElement(itemContentElement.value(i));
            itemElement.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }

    QStringList infoContentElement(QStringList()
        << "state" << "time" << "total" << "tpercent");

    for(int i=3; i < apiOut.size(); i++) {
        QDomElement element = doc.createElement(infoContentElement.value(i-3));
        root.appendChild(element);
        element.appendChild(doc.createTextNode(apiOut.value(i)));
    }

    m_var = doc.toString();
}


void RenderResponseS3::generateClearPercent() {

    QString paraJobName = m_pReq->parameter("name");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_clear_s3_account "
                                      + allParametersToString(), true);

}
