cmake_minimum_required(VERSION 3.5)

project(345Application VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(OpenCV_DIR "C:/opencv")
set(CMAKE_PREFIX_PATH "C:/opencv/build/x64/vc16/lib")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Core Widgets Multimedia MultimediaWidgets Gui Quick QuickControls2 REQUIRED)
find_package(OpenCV REQUIRED)

#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
#find_package(QT NAMES Qt6 REQUIRED COMPONENTS TextToSpeech)
#find_package(OpenCV REQUIRED)
#find_package(Qt6 REQUIRED COMPONENTS Gui)


set(PROJECT_SOURCES
        main.cpp
        camera.cpp
        camera.h
        camera.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(345Application
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resouces.qrc
    )


# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 345Application APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(345Application SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(345Application
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(345Application PRIVATE
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    Qt6::QuickControls2
    Qt6::Quick
    Qt6::Gui
)
target_link_libraries(345Application PRIVATE ${OpenCV_LIBS})

#target_link_libraries(345Application PRIVATE Qt6::Gui)
#target_link_libraries(345Application PRIVATE Qt6::TextToSpeech)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.345Application)
endif()
set_target_properties(345Application PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
include_directories( ${OpenCV_INCLUDE_DIRS} )

install(TARGETS 345Application
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(345Application)
endif()
