#include <QUrlQuery>
#include <QEventLoop>

#include "AssKicking.h"

AssKicking::AssKicking(QObject *parent)
    : QObject(parent)
    , m_pAssKicgingManager(new QNetworkAccessManager(this))
{
    qRegisterMetaType<QNetworkReply::NetworkError>("QNetworkReply::NetworkError");
}

AssKicking::~AssKicking() {
}

void AssKicking::startKickAss(QUrl url, THttpRequest *pReq) {

    if(pReq == NULL)
        return;

    QUrlQuery query;

    for(QString key : pReq->allParameters().keys()) {
        QString value = pReq->parameter(key);
//        if(key == "cmd")
//            value = "1";
        query.addQueryItem(key, value);
    }

    QNetworkRequest assRequest(url);
    assRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply *assReply = m_pAssKicgingManager->post(assRequest, query.toString(QUrl::FullyEncoded).toUtf8());
    connect(assReply, SIGNAL(finished()), this, SLOT(onGoodAssArrived()), Qt::AutoConnection);
    connect(assReply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(onBadAssArrived(QNetworkReply::NetworkError)), Qt::AutoConnection);

    QEventLoop loop;
    connect(this, SIGNAL(sigAssWithBullShit()), &loop, SLOT(quit()));
    loop.exec();
}

void AssKicking::onGoodAssArrived() {

    QNetworkReply *assData = qobject_cast<QNetworkReply *>(sender());

    if (assData->error() == QNetworkReply::NoError) {

        m_assData = assData->readAll();
        tDebug("AssKicking::onGoodAssArrived noerror, assData: %s ", m_assData.data());

    }
    else

        tDebug("AssKicking::onGoodAssArrived error, assData: %s ", m_assData.data());


    assData->deleteLater();

    emit sigAssWithBullShit();
}

void AssKicking::onBadAssArrived(QNetworkReply::NetworkError badAss) {

    QNetworkReply *assData = qobject_cast<QNetworkReply *>(sender());
    tDebug("AssKicking::onBadAssArrived: %d %s", badAss, assData->errorString().toLocal8Bit().data());
    tDebug("AssKicking::onBadAssArrived: %s", assData->readAll().data());

    assData->deleteLater();
    emit sigAssWithBullShit();
}

QByteArray AssKicking::buildRequestBody(const QVariantMap &parameters) {
    QByteArray body;
    bool first = true;
    foreach (QString key, parameters.keys()) {
        if (first) {
            first = false;
        } else {
            body.append("&");
        }
        QString value = parameters.value(key).toString();
        body.append(QUrl::toPercentEncoding(key) + QString("=").toUtf8() + QUrl::toPercentEncoding(value));
    }
    tDebug("body: %s", body.data());
    return body;
}
