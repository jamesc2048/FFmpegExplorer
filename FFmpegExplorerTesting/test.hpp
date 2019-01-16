#ifndef TEST_HPP
#define TEST_HPP

#include <QObject>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);



Q_INVOKABLE QString test()
{
    return "wowowow";
}
};

#endif // TEST_HPP
