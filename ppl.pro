TEMPLATE = lib

# Static library without any Qt functionality
QT -= gui core

CONFIG += static exceptions stl console static c++11
CONFIG -= thread qt rtti warn_on

VERSION = 1.0.0

INCLUDEPATH += include
INCLUDEPATH += include/freetype2
INCLUDEPATH += include/simpleini
INCLUDEPATH += ../SDK/CHeaders/XPLM
INCLUDEPATH += ../SDK/CHeaders/Widgets

# Defined to use X-Plane SDK 2.1 capabilities - no backward compatibility before 10.0
DEFINES += XPLM200 XPLM210

OBJECTS_DIR  = objects
TARGET = ppl

DEFINES += PRIVATENAMESPACE=$$PRIVATENAMESPACE
DESTDIR = lib$$PRIVATENAMESPACE

standalone {
    DEFINES += BUILD_FOR_STANDALONE
    TARGET = pplstandalone
}

macx {
    DEFINES += APL=1 IBM=0 LIN=0
    QMAKE_CXXFLAGS += -Wall -Wextra -Wfloat-equal -pedantic

    # Build for multiple architectures.
    # The following line is only needed to build universal on PPC architectures.
    # QMAKE_MAC_SDK=/Developer/SDKs/MacOSX10.4u.sdk
    # This line defines for which architectures we build.
    CONFIG += x86 x86_64
}

win32 {
    DEFINES += APL=0 IBM=1 LIN=0
    !win32-msvc2008:!win32-msvc2010 {
        QMAKE_CXXFLAGS += -Werror -Wall -Wextra -pedantic
    } else {
        CONFIG += warn_on
        #disable the deprecated warnings that make writing standards-compliant code impossible
        QMAKE_CXXFLAGS += -wd4996
        DEFINES += NOMINMAX
    }
    INCLUDEPATH += include C:\\Boost\\include\\boost-1_52 openALsoft/include
}

unix:!macx {
    DEFINES += APL=0 IBM=0 LIN=1 HAVE_TR1
    QMAKE_CXXFLAGS += -Wall -Wextra -Wfloat-equal -pedantic
    QMAKE_CXXFLAGS += -fvisibility=hidden -fno-stack-protector
}

CONFIG( debug, debug|release ) {
    # debug settings go here
} else {
    DEFINES += NDEBUG
}

HEADERS += \
    src/dataref.h \
    src/messagewindow.h \
    src/onscreendisplay.h \
    src/pluginpath.h \
    src/owneddata.h \
    src/logichandler.h \
    src/settings.h \
    src/texture.h \
    src/overlaygauge.h \
    src/xposd.h \
    src/log.h \
    src/logwriter.h \
    src/basics.h \
    src/menuitem.h \
    src/action.h \
    src/smoothed.h \
    src/processor.h \
    src/namespaces.h \
    src/vertexbuffer.hpp \
    src/command.h \
    src/externalcommand.h \
    src/signalcommand.h \
    src/imageio/bitmapio.h \
    src/imageio/imagedata.h \
    src/imageio/targaio.h \
    src/mvc/controller.h \
    src/mvc/view.h \
    src/mvc/view/clickregion/clickregion.h \
    src/mvc/view/advancedoverlaygauge.h \
    src/mvc/view/basicgraphicscontext.h \
    src/mvc/view/drawable.h \
    src/mvc/view/fontcache.h \
    src/mvc/view/glgraphicscontext.h \
    src/mvc/view/graphicscontext.h \
    src/mvc/view/overlaygaugeview.h \
    src/mvc/view/viewcomponent.h \
    src/plugin_namespace/pathcomponent.h \
    src/plugin_namespace/pluginnamespace.h \
    src/util/hash_specialization.h \
    src/util/varadiccompiler.h \
    src/delayedaction.h \
    src/ui/cursormanager.h \
    src/ui/cursor.h \
    src/ui/cursortype.h \
    src/scenery/probe.h \
    src/scenery/proberesult.h \
    src/periodicaction.h

SOURCES += \
    src/pluginpath.cpp \
    src/settings.cpp \
    src/dataref.cpp \
    src/messagewindow.cpp \
    src/onscreendisplay.cpp \
    src/owneddata.cpp \
    src/logichandler.cpp \
    src/texture.cpp \
    src/overlaygauge.cpp \
    src/log.cpp \
    src/logwriter.cpp \
    src/menuitem.cpp \
    src/smoothed.cpp \
    src/processor.cpp \
    src/vertexbuffer.cpp \
    src/command.cpp \
    src/signalcommand.cpp \
    src/imageio/bitmapio.cpp \
    src/imageio/targaio.cpp \
    src/mvc/view/clickregion/clickregion.cpp \
    src/mvc/view/advancedoverlaygauge.cpp \
    src/mvc/view/basicgraphicscontext.cpp \
    src/mvc/view/fontcache.cpp \
    src/mvc/view/glgraphicscontext.cpp \
    src/mvc/view/overlaygaugeview.cpp \
    src/plugin_namespace/pathcomponent.cpp \
    src/plugin_namespace/pluginnamespace.cpp \
    src/delayedaction.cpp \
    src/externalcommand.cpp \
    src/ui/cursormanager.cpp \
    src/ui/cursor.cpp \
    src/scenery/probe.cpp \
    src/scenery/proberesult.cpp \
    src/periodicaction.cpp


withsound {
    HEADERS += \
        src/alsoundbuffer.h \
        src/alcontextmanager.h \
        src/alcontextchanger.h
    SOURCES += \
        src/alsoundbuffer.cpp \
        src/alcontextmanager.cpp \
        src/alcontextchanger.cpp
}

withfreetype {
    win32 {
        INCLUDEPATH += include ../../Downloads/freetype-2.3.5/include
    }
    unix:!macx {
        INCLUDEPATH += /usr/local/include/freetype2
    }
    macx {
        INCLUDEPATH += /usr/local/include/freetype2
    }

    HEADERS += src/fontmgr.h
    SOURCES += src/fontmgr.cpp
}

withserialization {
    win32 {
        INCLUDEPATH += C:\\Boost\\include\\boost-1_52
    }
    unix:!macx {
        INCLUDEPATH += /usr/local/include/
    }
    macx {
        INCLUDEPATH += /usr/local/include/
    }

    HEADERS += src/sharedobject.h
    SOURCES += src/sharedobject.cpp

}

# Configuration option adds support for PNG files
withpng {
    DEFINES += PPL_ENABLE_PNG
    HEADERS += src/imageio/pngio.h
    SOURCES += src/imageio/pngio.cpp

    # libpng
    macx {
        INCLUDEPATH += /opt/local/include
        LIBS += -L/opt/local/lib/libpng-static -lpng
    }
}

# Boost Signals2
win32 {
    # TODO
}
unix:!macx {
    # TODO
}
macx {
    INCLUDEPATH += /opt/local/include
}

