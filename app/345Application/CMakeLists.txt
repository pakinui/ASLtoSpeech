cmake_minimum_required(VERSION 3.5)

project(345Application VERSION 0.1 LANGUAGES CXX)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#comment these out
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Core Widgets Multimedia MultimediaWidgets Gui Quick QuickControls2 Test REQUIRED)

# Set OpenCV paths based on environment
if(DEFINED ENV{GITHUB_ACTIONS})
    message(STATUS "Running in GitHub Actions environment")
    set(OpenCV_DIR "C:/tools/opencv")  # Adjust to your GitHub Actions path
    set(CMAKE_PREFIX_PATH "C:/tools/opencv/build/x64/vc16/lib")  # Adjust to your GitHub Actions path
else()
    message(STATUS "Running in standard user environment")
    set(OpenCV_DIR "C:/opencv")  # Adjust to your standard user path
    set(CMAKE_PREFIX_PATH "C:/opencv/build/x64/vc16/lib")  # Adjust to your standard user path
endif()

#comment these out
find_package(OpenCV REQUIRED)
find_package(Python REQUIRED Development)
#find_package(PySide6 REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        camera.cpp
        camera.h
        camera.ui
        text_to_speech/ttsCall.h
        text_to_speech/ttsCall.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(345Application
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resouces.qrc
        inference_classifier.py
        webcam_pattern_detection.py
        shared_lib.cpp


#*****************************************important*************************************************#
#**********once you finished building, put ASL_model(located in img_recognition) in your build folder and uncomment this.*****/
#        ../build-345Application-Desktop_Qt_6_5_2_MinGW_64_bit-Debug/ASL_model.p
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

add_library(shared SHARED shared_lib.cpp)

target_link_libraries(345Application PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    Qt6::QuickControls2
    Qt6::Quick
    Qt6::Gui
    shared_lib

)

target_link_libraries(345Application PRIVATE winmm)

target_link_libraries(345Application PRIVATE Python::Python)
target_link_libraries(345Application PRIVATE ${OpenCV_LIBS})
#target_link_directories(345Application PRIVATE "C:/Users/yhkyh/Desktop/experiment/build/lib/Release")
target_link_libraries(shared PRIVATE  Qt6::Multimedia)

add_executable(Tests
    tests/camera_tests.cpp
)

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
