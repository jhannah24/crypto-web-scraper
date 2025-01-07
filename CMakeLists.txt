cmake_minimum_required(VERSION 3.16)

project(cryptoScraper VERSION 0.1 LANGUAGES CXX)

# Enable automatic processing of Qt features
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(CURL REQUIRED)

# Source files
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    worker.cpp
    worker.h
    curlobj.cpp
    curlobj.h
    data.cpp
    data.h
)

# Define executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(cryptoScraper
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(cryptoScraper
        ${PROJECT_SOURCES}

    )
endif()

# Link libraries
target_link_libraries(cryptoScraper PRIVATE Qt${QT_VERSION_MAJOR}::Widgets CURL::libcurl)

# Bundle configuration
set_target_properties(cryptoScraper PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install configuration
include(GNUInstallDirs)
install(TARGETS cryptoScraper
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the executable for Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(cryptoScraper)
endif()
