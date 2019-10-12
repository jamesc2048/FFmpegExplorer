#include "utilities.hpp"

Utilities::Utilities(QObject *parent) : QObject(parent)
{

}

void Utilities::httpGet(QString urlStr, QJSValue callback)
{
    QUrl url = QUrl(urlStr);

    QNetworkAccessManager *nam = new QNetworkAccessManager();

    connect(nam, &QNetworkAccessManager::finished, [=](QNetworkReply *r) {
        const QString replyStr = r->readAll();
        qDebug() << replyStr;

        r->deleteLater();
        nam->deleteLater();

        static_cast<QJSValue>(callback).call({ QJSValue(replyStr) });
    });

    nam->get(QNetworkRequest(url));
}
