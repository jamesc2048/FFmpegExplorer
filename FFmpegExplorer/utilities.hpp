#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "pch.hpp"

class Utilities : public QObject
{
    Q_OBJECT
public:
    explicit Utilities(QObject *parent = nullptr);

    Q_INVOKABLE void httpGet(QString urlStr, QJSValue callback);

signals:

public slots:
};

#endif // UTILITIES_HPP
