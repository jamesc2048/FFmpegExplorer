cmake_minimum_required(VERSION 3.16)

project(FFmpegExplorer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appFFmpegExplorer
    main.cpp
)

qt_add_qml_module(appFFmpegExplorer
    URI FFmpegExplorer
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES backend.hpp backend.cpp
    RESOURCES resources.qrc
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appFFmpegExplorer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFFmpegExplorer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Keep file and line number info in logs
target_compile_definitions(appFFmpegExplorer PUBLIC QT_MESSAGELOGCONTEXT)
target_compile_definitions(appFFmpegExplorer PUBLIC APP_VERSION="${CMAKE_PROJECT_VERSION}")

if (MSVC)
  target_compile_options(appFFmpegExplorer PRIVATE /W4 /WX)
else()
  target_compile_options(appFFmpegExplorer PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(appFFmpegExplorer
    PRIVATE Qt6::Quick Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appFFmpegExplorer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
