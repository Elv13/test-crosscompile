project (foo)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

IF(POLICY CMP0063)
   CMAKE_POLICY(SET CMP0063 NEW)
ENDIF(POLICY CMP0063)

set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")

set(CMAKE_BUILD_TYPE DEBUG)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Widgets
    RemoteObjects
)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons
    WidgetsAddons
    ItemModels
)

add_subdirectory(qt5-node-editor)
add_subdirectory(Qt-Color-Widgets)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(foo_SRCS
    main.cpp
)


QT5_WRAP_UI(foo_SRCS mainwindow.ui)

add_executable(foo ${foo_SRCS})

TARGET_LINK_LIBRARIES( foo
    qnodeeditor
    ColorWidgets-qt5
    Qt5::Widgets
    Qt5::Core
    KF5::ItemModels
)

install(TARGETS foo  ${INSTALL_TARGETS_DEFAULT_ARGS})
INSTALL( FILES data/fooui.rc DESTINATION  ${KXMLGUI_INSTALL_DIR}/foo )
