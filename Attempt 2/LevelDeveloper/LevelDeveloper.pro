QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src\commands.cpp \
    src\main.cpp \
    src\mainwindow.cpp \
    src\map_board.cpp \
    src\maplayoutscreen.cpp \
    src\mygraphicsview.cpp \
    src\newtilewindow.cpp \
    src\startingscreen.cpp \
    src\tileitem.cpp \
    src\xmlwriter.cpp

HEADERS += \
    include\commands.h \
    include\mainwindow.h \
    include\map_board.h \
    include\maplayoutscreen.h \
    include\mygraphicsview.h \
    include\newtilewindow.h \
    include\startingscreen.h \
    include\tileitem.h \
    include\xmlwriter.h

FORMS += \
    mainwindow.ui \
    maplayoutscreen.ui \
    newtilewindow.ui \
    startingscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



RESOURCES += \
    LevelDeveloper.qrc

RC_ICONS = Images/Icon.ico

OTHER_FILES += \
    Images/floor.png
    Images/floor1.png
    Images/floor2.png
    Images/floor3.png
    Images/empty.png
    Images/Icon.png
</


