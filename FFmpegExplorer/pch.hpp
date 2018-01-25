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
#include <QtWinExtras/QtWinExtras>

// Needs to be declared after QtWinExtras, for some reason?
#ifdef _WIN32
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#endif

// Application headers
#include "utilities.hpp"

#endif // PCH_H
