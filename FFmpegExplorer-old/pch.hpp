#ifndef PCH_H
#define PCH_H

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
#include <QtMultimedia>

// Needs to be declared after QtWinExtras, for some reason?
#ifdef _WIN32
    #include <QtWinExtras/QtWinExtras>

    #ifndef NOMINMAX
        #define NOMINMAX 1
    #endif
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif

// Application headers
#include "utilities.hpp"

#endif // PCH_H
