cmake_minimum_required (VERSION 3.0)

project (kdewizard)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

find_package(KDE1 REQUIRED)
find_package(X11 REQUIRED)

include_directories (
    ${KDE1_INCLUDE_DIR}
)


include(CMakePackageConfigHelpers)
include(Qt1Macros)
include(KDE1Macros)
include(KDE1InstallDirs)

option(ENABLE_SANITIZERS "Enable runtime sanitizing (for development)")
if (ENABLE_SANITIZERS)
    message("Enabling asan and ubsan")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-write-strings")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -std=c++98 -Wno-write-strings")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
endif()

qt1_wrap_moc(MOC_FILES
    drivepage.h
    intropage.h
    linkpage.h
    printerpage.h
    theme.h
    themepage.h
    toplevel.h
)

add_executable(kdewizard
    drivepage.cpp
    intropage.cpp
    linkpage.cpp
    main.cpp
    printerpage.cpp
    theme.cpp
    themepage.cpp
    toplevel.cpp

    ${MOC_FILES}
)
target_link_libraries(kdewizard
    ${KDE1_KDECORE}
    ${KDE1_KDEUI}
    ${KDE1_KFILE}
    ${KDE1_KFM}
    ${KDE1_KHTMLW}
    Qt::Qt1
    X11::X11
)

install(TARGETS kdewizard RUNTIME DESTINATION ${KDE1_BINDIR})
install(FILES krunonce
    PERMISSIONS WORLD_EXECUTE WORLD_READ
    DESTINATION ${KDE1_BINDIR}
)

install_icon(html/kconfwizard.xpm)
install(FILES kdewizard.kdelnk DESTINATION ${KDE1_APPSDIR})

install(FILES
    html/intro.html
    html/kdelogo.gif
    html/wizard.gif
    html/wizard_small.gif

    DESTINATION ${KDE1_DATADIR}/kdewizard/html
)

install(FILES
    pics/kdetheme.xpm
    pics/mactheme.xpm
    pics/beostheme.xpm
    pics/wintheme.xpm
    pics/kdehome.xpm
    pics/kdedevel.xpm
    pics/kdeftp.xpm
    pics/printer.xpm

    DESTINATION ${KDE1_DATADIR}/kdewizard/pics
)

install(FILES
    data/kdewww.kdelnk
    data/kdeftp.kdelnk
    data/kdedevel.kdelnk
    data/printer.kdelnk

    theme.mappings

    DESTINATION ${KDE1_DATADIR}/kdewizard
)


##############
### Themes ###
##############


install(FILES
    themes/Default/Default.themerc
    DESTINATION ${KDE1_DATADIR}/kdewizard/Themes/Default
)

install(FILES
    themes/BeOS/BeOS.themerc
    DESTINATION ${KDE1_DATADIR}/kdewizard/Themes/BeOS
)

install(FILES
    themes/MacOS/activetitlebar.xpm
    themes/MacOS/cdrom.xpm
    themes/MacOS/clap.wav
    themes/MacOS/close.xpm
    themes/MacOS/desktop2.jpg
    themes/MacOS/desktop.jpg
    themes/MacOS/extensions-folder.xpm
    themes/MacOS/folder.xpm
    themes/MacOS/harddrive.xpm
    themes/MacOS/iconify.xpm
    themes/MacOS/inactivetitlebar.xpm
    themes/MacOS/MacOS.htm
    themes/MacOS/MacOS.themerc
    themes/MacOS/marbles.wav
    themes/MacOS/maximizedown.xpm
    themes/MacOS/maximize.xpm
    themes/MacOS/menu.xpm
    themes/MacOS/mini-folder.xpm
    themes/MacOS/mini-trashempty.xpm
    themes/MacOS/mini-trashfull.xpm
    themes/MacOS/panel.xpm
    themes/MacOS/pindown.xpm
    themes/MacOS/pinup.xpm
    themes/MacOS/startup-folder.xpm
    themes/MacOS/trashempty.xpm
    themes/MacOS/trashfull.xpm
    themes/MacOS/wm_bottomleft.xpm
    themes/MacOS/wm_bottomright.xpm
    themes/MacOS/wm_bottom.xpm
    themes/MacOS/wm_left.xpm
    themes/MacOS/wm_right.xpm
    themes/MacOS/wm_topleft.xpm
    themes/MacOS/wm_topright.xpm
    themes/MacOS/wm_top.xpm
    DESTINATION ${KDE1_DATADIR}/kdewizard/Themes/MacOS
)

install(FILES
    themes/Windows/close.xpm
    themes/Windows/iconify.xpm
    themes/Windows/maximizedown.xpm
    themes/Windows/maximize.xpm
    themes/Windows/Windows.themerc

    DESTINATION ${KDE1_DATADIR}/kdewizard/Themes/Windows
)

