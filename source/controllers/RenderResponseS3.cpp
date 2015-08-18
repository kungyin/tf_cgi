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

/* todo */
void RenderResponseS3::generateGetS3() {
    QDomDocument doc;
    QString paraPage = m_pReq->parameter("page");
    QString paraRp = m_pReq->parameter("rp");
    QString paraQuery = m_pReq->parameter("query");
    QString paraQType = m_pReq->parameter("qtype");
    QString paraField = m_pReq->parameter("f_field");
    QString paraUser = m_pReq->parameter("user");

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " media_get_share_folder_list");

    QString cellContent0 = "<span style='display:none'>%1</span><span>%2</span>";
    QString cellContent3 = "<img border='0' src='/web/images/stop.png' width='27' height='17' onclick='parent.action_stop(\"%1\")'>";
    QString cellContent4 = "<img border='0' src='/web/images/backup.png' width='16' height='16' onclick='parent.backup_now(\"%1\")'>";


    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);
//    for(int i=0; i < apiOut.size(); i++) {

//        QDomElement rowElement = doc.createElement("row");
//        root.appendChild(rowElement);

//        QDomElement cellElement1 = doc.createElement("cell");
//        rowElement.appendChild(cellElement1);
//        cellElement1.appendChild(doc.createTextNode(QString::number(i+1)));

//        QDomElement cellElement2 = doc.createElement("cell");
//        rowElement.appendChild(cellElement2);
//        cellElement2.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(0)));

//        QDomElement cellElement3 = doc.createElement("cell");
//        rowElement.appendChild(cellElement3);
//        cellElement3.appendChild(doc.createCDATASection(cellContent1.arg(apiOut.value(i).split(";").value(1))));

//        QDomElement cellElement4 = doc.createElement("cell");
//        rowElement.appendChild(cellElement4);
//        cellElement4.appendChild(doc.createCDATASection(cellContent2));

//        QDomElement cellElement5 = doc.createElement("cell");
//        rowElement.appendChild(cellElement5);
//        cellElement5.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(2)));

//        rowElement.setAttribute("id", i+1);
//    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(6/*apiOut.size()*/)));

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

void RenderResponseS3::generateS3Del() {

    QString paraJobName = m_pReq->parameter("f_job_name");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_stop_s3_account "
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

    QDomElement root = doc.createElement("s3");
    doc.appendChild(root);
    QDomElement itemElement = doc.createElement("item");
    root.appendChild(itemElement);

    QList<QString> itemContentElement(QList<QString>()
        << "fileName" << "time" << "percent");

    if( itemContentElement.size() == apiOut.size() ) {

        for(int i=0; i < apiOut.size(); i++) {
            QDomElement element = doc.createElement(itemContentElement.value(i));
            itemElement.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseS3::generateGetPercent() :"
            "itemContentElement size is not equal to apiOut size.");

        tDebug(" %d", apiOut.size());
        tDebug(" %d", itemContentElement.size());

    }

    m_var = doc.toString();
}


void RenderResponseS3::generateClearPercent() {

    QString paraJobName = m_pReq->parameter("name");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_clear_s3_account "
                                      + allParametersToString(), true);

}
