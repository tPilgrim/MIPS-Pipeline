cmake_minimum_required(VERSION 3.19)
project(PipelineSimulator LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(PipelineSimulator
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    cpu.cpp
    cpu.h
    resources.qrc
    VerticalLabel.h

)

target_link_libraries(PipelineSimulator
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS PipelineSimulator
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET PipelineSimulator
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

target_sources(PipelineSimulator PRIVATE
    cpu.cpp
    cpu.h
)

target_include_directories(PipelineSimulator
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
