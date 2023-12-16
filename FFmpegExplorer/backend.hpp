#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <QObject>
#include <QQmlEngine>

class Backend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Backend(QObject *parent = nullptr);

    Q_INVOKABLE void runProcess(QString exe, QStringList args, QJSValue callback);

signals:
};

#endif // BACKEND_HPP
