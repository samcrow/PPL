
# Include this file from a .pro file to incorporate PPL into your project.
# The variable PRIVATENAMESPACE must be defined before this file is included

DEFINES += PRIVATENAMESPACE=$$PRIVATENAMESPACE

INCLUDEPATH += PPL/src
INCLUDEPATH += PPL/include

withfreetype {
    INCLUDEPATH += PPL/include/freetype2
    LIBS += -L/opt/local/lib -lfreetype-static

    # It may be the case that freetype requires libpng
    CONFIG += withpng
}
withpng {
    LIBS += -L/opt/local/lib -lpng
}

# Add the library. Assumes that PPL was compiled in the PPL-build directory
LIBS += -L$$PWD/../PPL-build/lib$$PRIVATENAMESPACE -lppl
PRE_TARGETDEPS += $$PWD/../PPL-build/lib$$PRIVATENAMESPACE/libppl.a
