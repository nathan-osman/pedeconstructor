set(SRC
    generalwidget.h
    generalwidget.cpp
    importswidget.h
    importswidget.cpp
    main.cpp
    mainwindow.h
    mainwindow.cpp
    sectionswidget.h
    sectionswidget.cpp
)

add_executable(pedeconstructor WIN32 ${SRC})

set_target_properties(pedeconstructor PROPERTIES
    CXX_STANDARD          11
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(pedeconstructor Qt5::Widgets win32pe)

install(TARGETS pedeconstructor RUNTIME DESTINATION bin)
