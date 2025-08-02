cmake_minimum_required(VERSION 3.16)

project(TexasRed_Desktop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/core/main.cpp
        src/core/mainwindow.cpp
        src/core/mainwindow.h
        src/core/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Core)

    qt_add_executable(TexasRed_Desktop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/pages/regexsandboxpage.h src/pages/regexsandboxpage.cpp src/pages/regexsandboxpage.ui
        src/pages/portscannerpage.h src/pages/portscannerpage.cpp src/pages/portscannerpage.ui
        src/utils/regexhighlighter.h src/utils/regexhighlighter.cpp
        src/utils/Settings.h
        src/pages/logfileanalyzerpage.h src/pages/logfileanalyzerpage.cpp src/pages/logfileanalyzerpage.ui
        src/pages/emato3dconverterpage.h src/pages/emato3dconverterpage.cpp src/pages/emato3dconverterpage.ui
        src/utils/emato3dparser.h src/utils/emato3dparser.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TexasRed_Desktop APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TexasRed_Desktop SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TexasRed_Desktop
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TexasRed_Desktop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(TexasRed_Desktop PRIVATE Qt6::Core)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TexasRed_Desktop)
endif()
set_target_properties(TexasRed_Desktop PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TexasRed_Desktop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TexasRed_Desktop)
endif()
