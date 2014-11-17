
# Include this file from a .pro file to incorporate PPL into your project.
# The variable PRIVATENAMESPACE must be defined before this file is included

DEFINES += PRIVATENAMESPACE=$$PRIVATENAMESPACE

INCLUDEPATH += PPL/src

# Add the library. Assumes that PPL was compiled in the PPL-build directory
LIBS += -L$$PWD/../PPL-build/lib$$PRIVATENAMESPACE -lppl
