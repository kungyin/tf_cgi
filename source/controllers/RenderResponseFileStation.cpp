#include "RenderResponseFileStation.h"

#include <QDir>

RenderResponseFileStation::RenderResponseFileStation(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseFileStation::~RenderResponseFileStation() {
}

void RenderResponseFileStation::preRender() {

    if(!m_pReq)
        return;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_FOLDER_CONTENT:
        generateFolderContent(doc);
        break;

    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

}

/* todo */
void RenderResponseFileStation::generateFolderContent(QDomDocument &doc) {

    QString paraPage = m_pReq->parameter("page");
    QString paraRp = m_pReq->parameter("rp");
    QString paraQuery = m_pReq->parameter("query");
    QString paraType = m_pReq->parameter("qtype");
    QString paraField = m_pReq->parameter("f_field");
    QString paraUsedDir = QUrl::fromPercentEncoding(m_pReq->parameter("used_dir").toLocal8Bit());

    /* todo */
//    QString uiContent = /*THttpUtility::htmlEscape(*/"&lt;a href=javascript:onclick=GetSmartInfo(&apos;sda&apos;,&apos;0&apos;)"
//            ";&gt;&lt;IMG border=&apos;0&apos; src=&apos;/web/images/normal.png&apos; alt=&apos;"
//            "Normal&apos;&gt;&lt;/a&gt;"/*)*/;


    QDir dir(paraUsedDir);
    QDir::Filters filters = QDir::NoDotAndDotDot | QDir::AllEntries;
    QFileInfoList fileList= dir.entryInfoList(filters);

    tDebug("yyyyyy: %d", fileList.size());

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    int start = (paraPage.toInt()-1) * paraRp.toInt();
    int end = start + paraRp.toInt();
    if(end > fileList.size())
        end = fileList.size();

    for(int i = start; i < end; i++) {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QStringList cellContent(QStringList()
            << fileList.value(i).fileName() << "" << "" << "");

        for(QString e : cellContent) {
            QDomElement cellElement = doc.createElement("cell");
            rowElement.appendChild(cellElement);
            cellElement.appendChild(doc.createTextNode(e));
        }

        rowElement.setAttribute("id", QString::number( i - start + 1 ));
    }

    int total = 1;
    if(paraRp.toInt() != 0)
        total = fileList.size() / paraRp.toInt() + (fileList.size() % paraRp.toInt() != 0);

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(total)));

}


