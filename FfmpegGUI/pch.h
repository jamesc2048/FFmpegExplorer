#ifndef PCH_H
#define PCH_H

#ifdef _WIN32
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#endif

// STD headers
#include <iostream>
#include <vector>
#include <chrono>
#include <tuple>
#include <memory>

// QT headers
#include <QtCore>
#include <QtGui>
#include <QtQml>
#include <QtQuick>
#include <QtNetwork>
#include <QtSql>
#include <QtConcurrent>
//#include <QtWinExtras>

// Application headers
#include "utilities.h"

#endif // PCH_H
