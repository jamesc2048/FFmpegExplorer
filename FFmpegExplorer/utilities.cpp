#include "utilities.hpp"

Utilities::Utilities(QObject *parent) : QObject(parent)
{

}

void Utilities::httpGet(QString urlStr)
{
    QUrl url = QUrl(urlStr);

    QNetworkAccessManager *nam = new QNetworkAccessManager();

    connect(nam, &QNetworkAccessManager::finished, [=](QNetworkReply *r) {
        qDebug() << r->readAll();

        r->deleteLater();
        nam->deleteLater();
    });

    nam->get(QNetworkRequest(url));
}
