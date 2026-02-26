cmake_minimum_required(VERSION 3.16)

project(HospitalManagementSystem
    VERSION 1.0
    DESCRIPTION "Hospital Management System — DSA Mini Project using Qt GUI"
    LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp

    mainwindow.h
    mainwindow.cpp
    mainwindow.ui

    queue.h
    queue.cpp

    patientrecord.h
    patientrecord.cpp

    doctor.h
    doctor.cpp

    patient.h

    hospital.h
    hospital.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HospitalManagementSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(HospitalManagementSystem ${PROJECT_SOURCES})
endif()

target_link_libraries(HospitalManagementSystem
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
)

set_target_properties(HospitalManagementSystem PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER  com.student.HospitalMS
    MACOSX_BUNDLE_BUNDLE_VERSION  ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE

    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS HospitalManagementSystem
    BUNDLE  DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(HospitalManagementSystem)
endif()
