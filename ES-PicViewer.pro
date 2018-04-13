#-------------------------------------------------
#
# Project created by QtCreator 2018-04-08T04:28:01
#
#-------------------------------------------------

QT       += core gui
QT	 += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ES-PicViewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#  comment this to disable qDebug outputs
# DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += \
    CustomClasses/album.cpp \
    CustomClasses/foto.cpp \
    CustomClasses/gestorbd.cpp \
    CustomClasses/listaalbuns.cpp \
    CustomClasses/listapessoas.cpp \
    CustomClasses/pagina.cpp \
    CustomClasses/pessoa.cpp \
    UI/addalbumdialog.cpp \
    UI/addassociationdialog.cpp \
    UI/addpagedialog.cpp \
    UI/addpersondialog.cpp \
    UI/albuminfodisplay.cpp \
    UI/albumlistitem.cpp \
    UI/albumlistpage.cpp \
    UI/loadwindow.cpp \
    UI/main.cpp \
    UI/mainwindow.cpp \
    UI/managepeople.cpp \
    UI/pageinfodisplay.cpp \
    UI/photodisplay.cpp \
    UI/photominiature.cpp \
    CustomClasses/subpagina.cpp

HEADERS += \
    CustomClasses/album.h \
    CustomClasses/foto.h \
    CustomClasses/gestorbd.h \
    CustomClasses/listaalbuns.h \
    CustomClasses/listapessoas.h \
    CustomClasses/pagina.h \
    CustomClasses/pessoa.h \
    UI/addalbumdialog.h \
    UI/addassociationdialog.h \
    UI/addpagedialog.h \
    UI/addpersondialog.h \
    UI/albuminfodisplay.h \
    UI/albumlistitem.h \
    UI/albumlistpage.h \
    UI/loadwindow.h \
    UI/mainwindow.h \
    UI/managepeople.h \
    UI/pageinfodisplay.h \
    UI/photodisplay.h \
    UI/photominiature.h \
    CustomClasses/flags.h \
    CustomClasses/paramstructs.h

FORMS += \
    UI/addalbumdialog.ui \
    UI/addassociationdialog.ui \
    UI/addpagedialog.ui \
    UI/addpersondialog.ui \
    UI/albuminfodisplay.ui \
    UI/albumlistitem.ui \
    UI/albumlistpage.ui \
    UI/loadwindow.ui \
    UI/mainwindow.ui \
    UI/managepeople.ui \
    UI/pageinfodisplay.ui \
    UI/photodisplay.ui \
    UI/photominiature.ui

RESOURCES += \
    UI/resources.qrc

SUBDIRS += \
    ES-PicViewer.pro

DISTFILES +=
