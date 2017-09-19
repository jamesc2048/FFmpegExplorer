#ifndef PCH_H
#define PCH_H

#ifdef _WIN32
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#endif

#include <iostream>
#include <vector>
#include <chrono>
#include <tuple>

#include <QtCore>
#include <QtGui>
#include <QtQml>
#include <QtQuick>
#include <QtNetwork>
#include <QtSql>
#include <QtConcurrent>
//#include <QtWinExtras>

#include "QSimpleUpdater.h"

#endif // PCH_H
