#ifndef ASSKICKING_H
#define ASSKICKING_H

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT AssKicking: public QObject {
    Q_OBJECT

public:
    /// Constructor.
    /// @param  parent  Parent object.
    explicit AssKicking(QObject *parent = 0);

    /// Destructor.
    virtual ~AssKicking();

    QByteArray &getAssData() { return m_assData; }

public slots:
    Q_INVOKABLE virtual void startKickAss(QUrl, THttpRequest *);

signals:
    void sigAssWithBullShit();

protected slots:
    /// Handle completion of an ass arrived.
    virtual void onGoodAssArrived();

    /// Handle failure of an ass arrived.
    virtual void onBadAssArrived(QNetworkReply::NetworkError badAss);

protected:
    /// Build HTTP request body.
    QByteArray buildRequestBody(const QVariantMap &parameters);

protected:
    QNetworkAccessManager *m_pAssKicgingManager;

private:
    QByteArray m_assData;

};

#endif // ASSKICKING_H
