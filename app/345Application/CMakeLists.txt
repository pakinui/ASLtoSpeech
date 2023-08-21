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
        python_files/include/cpython/abstract.h python_files/include/cpython/bytearrayobject.h python_files/include/cpython/bytesobject.h python_files/include/cpython/cellobject.h python_files/include/cpython/ceval.h python_files/include/cpython/classobject.h python_files/include/cpython/code.h python_files/include/cpython/compile.h python_files/include/cpython/complexobject.h python_files/include/cpython/context.h python_files/include/cpython/descrobject.h python_files/include/cpython/dictobject.h python_files/include/cpython/fileobject.h python_files/include/cpython/fileutils.h python_files/include/cpython/floatobject.h python_files/include/cpython/frameobject.h python_files/include/cpython/funcobject.h python_files/include/cpython/genobject.h python_files/include/cpython/import.h python_files/include/cpython/initconfig.h python_files/include/cpython/listobject.h python_files/include/cpython/longintrepr.h python_files/include/cpython/longobject.h python_files/include/cpython/methodobject.h python_files/include/cpython/modsupport.h python_files/include/cpython/object.h python_files/include/cpython/objimpl.h python_files/include/cpython/odictobject.h python_files/include/cpython/picklebufobject.h python_files/include/cpython/pthread_stubs.h python_files/include/cpython/pyctype.h python_files/include/cpython/pydebug.h python_files/include/cpython/pyerrors.h python_files/include/cpython/pyfpe.h python_files/include/cpython/pyframe.h python_files/include/cpython/pylifecycle.h python_files/include/cpython/pymem.h python_files/include/cpython/pystate.h python_files/include/cpython/pythonrun.h python_files/include/cpython/pythread.h python_files/include/cpython/pytime.h python_files/include/cpython/setobject.h python_files/include/cpython/sysmodule.h python_files/include/cpython/traceback.h python_files/include/cpython/tupleobject.h python_files/include/cpython/unicodeobject.h python_files/include/cpython/warnings.h python_files/include/cpython/weakrefobject.h python_files/include/internal/pycore_abstract.h python_files/include/internal/pycore_accu.h python_files/include/internal/pycore_asdl.h python_files/include/internal/pycore_ast.h python_files/include/internal/pycore_ast_state.h python_files/include/internal/pycore_atomic.h python_files/include/internal/pycore_atomic_funcs.h python_files/include/internal/pycore_bitutils.h python_files/include/internal/pycore_blocks_output_buffer.h python_files/include/internal/pycore_bytes_methods.h python_files/include/internal/pycore_bytesobject.h python_files/include/internal/pycore_call.h python_files/include/internal/pycore_ceval.h python_files/include/internal/pycore_code.h python_files/include/internal/pycore_compile.h python_files/include/internal/pycore_condvar.h python_files/include/internal/pycore_context.h python_files/include/internal/pycore_dict.h python_files/include/internal/pycore_dtoa.h python_files/include/internal/pycore_emscripten_signal.h python_files/include/internal/pycore_exceptions.h python_files/include/internal/pycore_fileutils.h python_files/include/internal/pycore_floatobject.h python_files/include/internal/pycore_format.h python_files/include/internal/pycore_frame.h python_files/include/internal/pycore_function.h python_files/include/internal/pycore_gc.h python_files/include/internal/pycore_genobject.h python_files/include/internal/pycore_getopt.h python_files/include/internal/pycore_gil.h python_files/include/internal/pycore_global_objects.h python_files/include/internal/pycore_global_strings.h python_files/include/internal/pycore_hamt.h python_files/include/internal/pycore_hashtable.h python_files/include/internal/pycore_import.h python_files/include/internal/pycore_initconfig.h python_files/include/internal/pycore_interp.h python_files/include/internal/pycore_interpreteridobject.h python_files/include/internal/pycore_list.h python_files/include/internal/pycore_long.h python_files/include/internal/pycore_moduleobject.h python_files/include/internal/pycore_namespace.h python_files/include/internal/pycore_object.h python_files/include/internal/pycore_opcode.h python_files/include/internal/pycore_parser.h python_files/include/internal/pycore_pathconfig.h python_files/include/internal/pycore_pyarena.h python_files/include/internal/pycore_pyerrors.h python_files/include/internal/pycore_pyhash.h python_files/include/internal/pycore_pylifecycle.h python_files/include/internal/pycore_pymath.h python_files/include/internal/pycore_pymem.h python_files/include/internal/pycore_pystate.h python_files/include/internal/pycore_runtime.h python_files/include/internal/pycore_runtime_init.h python_files/include/internal/pycore_signal.h python_files/include/internal/pycore_sliceobject.h python_files/include/internal/pycore_strhex.h python_files/include/internal/pycore_structseq.h python_files/include/internal/pycore_symtable.h python_files/include/internal/pycore_sysmodule.h python_files/include/internal/pycore_traceback.h python_files/include/internal/pycore_tuple.h python_files/include/internal/pycore_typeobject.h python_files/include/internal/pycore_ucnhash.h python_files/include/internal/pycore_unicodeobject.h python_files/include/internal/pycore_unionobject.h python_files/include/internal/pycore_warnings.h python_files/include/abstract.h python_files/include/bltinmodule.h python_files/include/boolobject.h python_files/include/bytearrayobject.h python_files/include/bytesobject.h python_files/include/ceval.h python_files/include/codecs.h python_files/include/compile.h python_files/include/complexobject.h python_files/include/datetime.h python_files/include/descrobject.h python_files/include/dictobject.h python_files/include/dynamic_annotations.h python_files/include/enumobject.h python_files/include/errcode.h python_files/include/exports.h python_files/include/fileobject.h python_files/include/fileutils.h python_files/include/floatobject.h python_files/include/frameobject.h python_files/include/genericaliasobject.h python_files/include/import.h python_files/include/intrcheck.h python_files/include/iterobject.h python_files/include/listobject.h python_files/include/longobject.h python_files/include/marshal.h python_files/include/memoryobject.h python_files/include/methodobject.h python_files/include/modsupport.h python_files/include/moduleobject.h python_files/include/object.h python_files/include/objimpl.h python_files/include/opcode.h python_files/include/osdefs.h python_files/include/osmodule.h python_files/include/patchlevel.h python_files/include/py_curses.h python_files/include/pybuffer.h python_files/include/pycapsule.h python_files/include/pyconfig.h python_files/include/pydtrace.h python_files/include/pyerrors.h python_files/include/pyexpat.h python_files/include/pyframe.h python_files/include/pyhash.h python_files/include/pylifecycle.h python_files/include/pymacconfig.h python_files/include/pymacro.h python_files/include/pymath.h python_files/include/pymem.h python_files/include/pyport.h python_files/include/pystate.h python_files/include/pystrcmp.h python_files/include/pystrtod.h python_files/include/Python.h python_files/include/pythonrun.h python_files/include/pythread.h python_files/include/pytypedefs.h python_files/include/rangeobject.h python_files/include/setobject.h python_files/include/sliceobject.h python_files/include/structmember.h python_files/include/structseq.h python_files/include/sysmodule.h python_files/include/token.h python_files/include/traceback.h python_files/include/tracemalloc.h python_files/include/tupleobject.h python_files/include/typeslots.h python_files/include/unicodeobject.h python_files/include/warnings.h python_files/include/weakrefobject.h python_files/libs/_tkinter.lib python_files/libs/python3.lib python_files/libs/python311.lib
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
