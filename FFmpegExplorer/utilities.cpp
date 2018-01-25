#include "utilities.hpp"


QString Utilities::getCommandOutputSync(const QString &exePath, const QStringList &args)
{
    QProcess p;

    p.start(exePath, args);
    p.waitForFinished();

    if (p.exitStatus() == QProcess::ExitStatus::NormalExit)
    {
        return p.readAllStandardOutput();
    }

    return {};
}

void Utilities::downloadFile(const QUrl url, std::function<void(QNetworkReply *)> callback)
{
    std::unique_ptr<QNetworkAccessManager> nam = std::make_unique<QNetworkAccessManager>();

    QNetworkRequest req(url);
    QNetworkReply *reply = nam->get(req);

    QObject::connect(nam.get(), &QNetworkAccessManager::finished, [nam {std::move(nam)}, callback](QNetworkReply *reply)
    {
        callback(reply);
    });
}
