#ifndef UTILITIES_H
#define UTILITIES_H

#include <QProcess>
#include <QFuture>
#include <QtNetwork>
#include <QJSValue>
#include <QtConcurrent>

namespace Utilities
{
    QString getCommandOutputSync(const QString&, const QStringList&);
    void downloadFile(const QUrl, std::function<void(QNetworkReply *)>);
}

class QMLUtilities : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void getWebResponse(QString url, QJSValue jsCallback)
    {
        //QtConcurrent::run([=]() {
            qDebug() << "getWebResponse";
            QNetworkAccessManager *nam = new QNetworkAccessManager();

            connect(nam, &QNetworkAccessManager::finished, [callback = std::move(jsCallback), nam](QNetworkReply *reply)
            {
                qDebug() << "getWebResponse finished";
                auto r = reply->readAll();

                reply->deleteLater();
                nam->deleteLater();

                qDebug() << "getWebResponse callback";
                ((QJSValue)(callback)).call({ QJSValue(QString(r)) });
            });

            qDebug() << "getWebResponse get";
            nam->get(QNetworkRequest(QUrl(url)));
            qDebug() << "getWebResponse after get";

//            connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), [=](QNetworkReply::NetworkError code)
//            {
//                qDebug() << "error " << code;
//            });

//            ((QJSValue)(jsCallback)).call({ QJSValue("omg") });
       // });
    }

    Q_INVOKABLE int getSystemOS()
    {
#ifdef Q_OS_WIN
        return 0;
#endif

#ifdef Q_OS_LINUX
        return 1;
#endif

#ifdef Q_OS_MACOS
        return 2;
#endif
        return -1;
    }
};

#endif // UTILITIES_H
