cmake_minimum_required(VERSION 3.5)

project(345Application VERSION 0.1 LANGUAGES CXX)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#comment these out
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option for enabling building of tests
option(BUILD_TESTING "Builds test executable." OFF)

set(OpenCV_DIR "C:/opencv")
set(CMAKE_PREFIX_PATH "C:/opencv/build/x64/vc16/lib" "C:/Qt/6.5.2/msvc2019_64" "C:/Qt/6.5.2/msvc2019_64/include" "C:Qt/6.5.2/msvc2019_64/bin")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Qt/6.5.2/msvc2019_64/include" "C:Qt/6.5.2/msvc2019_64/bin")



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

set(PROJECT_SOURCES
        src/main.cpp
        src/camera.cpp
        src/camera.h
        src/camera.ui
        src/text_to_speech/ttsCall.h
        src/text_to_speech/ttsCall.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(345Application
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/inference_classifier.py

        resources.qrc



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
    Qt6::Core
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    Qt6::QuickControls2
    Qt6::Quick
    Qt6::Gui
    Python::Python
    ${OpenCV_LIBS}
    winmm
)


#add_executable(Tests
#    tests/camera_tests.cpp

#)



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

#include(GNUInstallDirs)
include_directories( ${OpenCV_INCLUDE_DIRS} )


install(TARGETS 345Application
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(345Application)
endif()

# Specify the file you want to move (the model)
set(source_file_path "${CMAKE_SOURCE_DIR}/src/img_recognition/ASL_model.p")
set(destination_folder "${CMAKE_BINARY_DIR}")

# Create a custom target to move the file after the build
add_custom_target(move_file
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${source_file_path} ${destination_folder}
    DEPENDS ${source_file_path}
    COMMENT "Moving file to build folder"
)
# Add a dependency on the custom target to ensure the file is moved after the build
add_dependencies(345Application move_file)

message("1 ${CMAKE_SOURCE_DIR} 2 ${CMAKE_BINARY_DIR}")


if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    if(DEFINED ENV{GITHUB_ACTIONS})

    else()

        add_custom_target(coverage_report_tests

            COMMAND powershell -ExecutionPolicy Bypass -File "${CMAKE_SOURCE_DIR}/coverage/generate_coverage_tests.ps1"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating code coverage report for tests"
        )
        add_dependencies(345Application coverage_report_tests)
    endif()

else()
    message(WARNING "Code coverage report generation is only supported in RelWithDebInfo build type.")
endif()




##################################################################################
# Build Testing below
##################################################################################

if(BUILD_TESTING)



    add_executable(Tests
        tests/test.cpp
        src/text_to_speech/ttscall.cpp
        src/camera.cpp


    )

    find_package(Qt6 REQUIRED COMPONENTS Test)
    find_package(Python REQUIRED Development)
    enable_testing(true)

    target_link_libraries(Tests PRIVATE
        Qt6::Test
        Qt6::Widgets
        Qt6::Core
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        Qt6::QuickControls2
        Qt6::Quick
        Qt6::Gui
        Python::Python
        winmm
    )



endif()
