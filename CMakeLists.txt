cmake_minimum_required(VERSION 3.26)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

project(taskman 
    VERSION 0.1
    DESCRIPTION "Qt Clone of Windows Task Manager"
    LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

qt_add_executable(taskman
    main.cpp
    addresswidget.hpp
    mainwindow.hpp
    tablemodel.hpp
)

set_target_properties(taskman PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(taskman PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

install(TARGETS taskman
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
