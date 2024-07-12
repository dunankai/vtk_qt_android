cmake_minimum_required(VERSION 3.16)

project(qtquick VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Widgets OpenGL Gui)

find_package(VTK)

qt_standard_project_setup()

qt_add_executable(appqtquick
    main.cpp
    qtquick.qrc
)

qt_add_qml_module(appqtquick
    URI qtquick
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES MyVtkItem.h MyVtkItem.cpp
    SOURCES MyConeItem.h MyConeItem.cpp
    SOURCES MyWidgetItem.h MyWidgetItem.cpp
    SOURCES MyGeomItem.h MyGeomItem.cpp
    SOURCES MyVolumeItem.h MyVolumeItem.cpp
    SOURCES MyGlyphItem.h MyGlyphItem.cpp
    SOURCES QQuickVTKItem.h QQuickVTKItem.cxx
    SOURCES QVTKInteractor.h QVTKInteractor.cxx
    SOURCES QVTKInteractorAdapter.h QVTKInteractorAdapter.cxx
    #SOURCES QVTKRenderWindowAdapter.h QVTKRenderWindowAdapter.cxx
    SOURCES QVTKInteractorInternal.h
    #SOURCES QQuickVTKRenderItem.h QQuickVTKRenderItem.cxx
    #SOURCES QQuickVTKRenderWindow.h QQuickVTKRenderWindow.cxx
    #SOURCES QQuickVTKInteractiveWidget.h QQuickVTKInteractiveWidget.cxx
    #SOURCES QQuickVTKInteractorAdapter.h QQuickVTKInteractorAdapter.cxx
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqtquick PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqtquick
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

message(${VTK_LIBRARIES})

target_link_libraries(appqtquick
    PRIVATE Qt6::Quick
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::Gui
    ${VTK_LIBRARIES}
)

vtk_module_autoinit(TARGETS appqtquick MODULES ${VTK_LIBRARIES})

#qt_import_qml_plugins(appqtquick)

include(GNUInstallDirs)
install(TARGETS appqtquick
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
