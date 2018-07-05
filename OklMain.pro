
#-------------------------------------------------
#
# Project created by QtCreator 2018-05-18T18:39:52
#
#-------------------------------------------------

QT       += core gui
QT       += xml

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets sql axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets sql xml

TARGET = OklMain
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Src/CommonUserWidget/BmpButton.cpp \
    Src/CommonUserWidget/BmpWidget.cpp \
    Src/CommonUserWidget/CustomItemDelegate.cpp \
    Src/CommonUserWidget/CustomScrollBar.cpp \
    Src/CommonUserWidget/MessageBox.cpp \
    Src/CommonUserWidget/Slider.cpp \
    Src/CommonUserWidget/TextWidget.cpp \
    Src/CommonUserWidget/UserInterfaceUtility.cpp \
    Src/CommonUserWidget/CustomListView.cpp \
    Src/Framework/Base/Core/application.cpp \
    Src/Framework/Base/Audio/audiomanager.cpp \
    Src/Framework/Base/Video/videomanager.cpp \
    Src/Framework/View/toast.cpp \
    Src/Framework/Base/Core/context.cpp \
    Src/Framework/Base/Core/activity.cpp \
    Src/Framework/Base/Core/service.cpp \
    Src/Application/Launcher/launcher.cpp \
    Src/Framework/Base/Core/message.cpp \
    Src/Application/Radio/radio.cpp \
    Src/Application/Settings/settings.cpp \
    Src/Application/BlueTooth/Music/btmusic.cpp \
    Src/Application/BlueTooth/Phone/btphone.cpp \
    Src/Application/Ipod/ipod.cpp \
    Src/Application/MultiMedia/Image/image.cpp \
    Src/Application/MultiMedia/Music/music.cpp \
    Src/Application/MultiMedia/Video/video.cpp \
    Src/Application/SystemUi/systemui.cpp \
    Src/Application/Avin/avin.cpp \
    Src/Framework/Base/Core/simulation.cpp \
    Src/Simulation/simulationda.cpp \
    Src/Application/Radio/radio_am.cpp \
    Src/Hardware/SerialPort.cpp \
    Src/Hardware/SerialPortService.cpp \
    Src/Framework/Manager/BluetoothManager.cpp \
    Src/Framework/Manager/BluetoothManagerGoc.cpp \
    Src/Application/MultiMedia/Music/musicplaywidget.cpp \
    Src/Application/MultiMedia/Music/musiclistwidget.cpp \
    Src/Application/MultiMedia/Music/musiclistitem.cpp \
    Src/Application/MultiMedia/Music/musicprogresswidget.cpp \
    Src/Application/MultiMedia/Music/musicclickwidget.cpp \
    Src/Application/MultiMedia/Image/flowadapter.cpp \
    Src/Application/MultiMedia/Image/flowview.cpp \
    Src/Application/MultiMedia/Music/rotatewidget.cpp \
    Src/Application/MultiMedia/BtMusic/btmusicwidget.cpp \
    Src/Application/MultiMedia/Video/videoplaywidget.cpp \
    Src/Application/MultiMedia/Tools/mediatoolswidget.cpp \
    Src/Application/MultiMedia/Tools/mediautils.cpp \
    Src/Application/MultiMedia/multimedia.cpp \
    Src/Framework/MultimediaService/multimediaservice.cpp \
    Src/Framework/MultimediaService/multimediautils.cpp \
    Src/Framework/MultimediaService/player.cpp \
    Src/Framework/MultimediaService/DeviceWatcher/devicewatcher.cpp \
    Src/Framework/MultimediaService/DeviceWatcher/DiskScanner/diskscanner.cpp \
    Src/Framework/MultimediaService/CustomThread/customthread.cpp \
    Src/Framework/MultimediaService/MusicPlayer/musicplayer.cpp \
    Src/Framework/MultimediaService/MediaDb/mediadb.cpp \
    Src/Framework/MultimediaService/MediaDb/mediadbentity.cpp \
    Src/Framework/MultimediaService/VideoPlayer/videoplayer.cpp \
    Src/Framework/MultimediaService/ImagePlayer/imageplayer.cpp \
    Src/Application/MultiMedia/Music/musicid3.cpp \
    Src/Framework/MultimediaService/BtMusicPlayer/btmusicplayer.cpp \
    Src/Application/Launcher/viewpagerwidget.cpp \
    Src/Application/Radio/radio_unit.cpp \
    Src/Application/Radio/radio_data.cpp \
    Src/Application/Radio/radio_process.cpp \
    Src/Application/Settings/wheelview.cpp \
    Src/Application/Settings/tumbler.cpp \
    Src/Application/BlueTooth/Phone/phonelistwidgetitem.cpp \
    Src/Application/BlueTooth/Phone/phonerecordwidget.cpp \
    Src/Application/BlueTooth/Phone/listitembean.cpp \
    Src/Application/BlueTooth/Phone/customwidget.cpp \
    Src/Application/BlueTooth/Phone/phonedialwidget.cpp \
    Src/Application/BlueTooth/Phone/btphonewidget.cpp \
    Src/Application/BlueTooth/Phone/phonedeviceswidget.cpp \
    Src/Application/BlueTooth/Phone/phoneoptionswidget.cpp \
    Src/Application/BlueTooth/Phone/phoneoptionwidgetitem.cpp \
    Src/Hardware/RadioService.cpp \
    Src/Framework/Manager/RadioManager.cpp


HEADERS  += mainwindow.h \
    configuration.h \
    Src/CommonUserWidget/BmpButton.h \
    Src/CommonUserWidget/BmpWidget.h \
    Src/CommonUserWidget/CustomItemDelegate.h \
    Src/CommonUserWidget/CustomScrollBar.h \
    Src/CommonUserWidget/MessageBox.h \
    Src/CommonUserWidget/Slider.h \
    Src/CommonUserWidget/TextWidget.h \
    Src/CommonUserWidget/UserInterfaceUtility.h \
    Src/CommonUserWidget/CustomListView.h \
    Src/Framework/Base/Core/application.h \
    Src/Framework/Base/Audio/audiomanager.h \
    Src/Framework/Base/Video/videomanager.h \
    Src/Framework/View/toast.h \
    Src/Framework/Base/Core/context.h \
    Src/Framework/Base/Core/activity.h \
    Src/Framework/Base/Core/service.h \
    Src/Framework/Base/Core/message.h \
    Src/Framework/Base/Core/apptype.h \
    Src/Application/AllApplication.h \
    Src/Application/Launcher/launcher.h \
    Src/Application/Radio/radio.h \
    Src/Application/Settings/settings.h \
    Src/Application/BlueTooth/Phone/btphone.h \
    Src/Application/Ipod/ipod.h \
    Src/Application/MultiMedia/Image/image.h \
    Src/Application/MultiMedia/Music/music.h \
    Src/Application/MultiMedia/Video/video.h \
    Src/Application/SystemUi/systemui.h \
    Src/Application/BlueTooth/Music/btmusic.h \
    Src/Application/Avin/avin.h \
    Src/Framework/Base/Core/simulation.h \
    Src/Simulation/simulationda.h \
    Src/Application/Radio/radio_am.h \
    Src/Hardware/SerialPort.h \
    Src/Hardware/okl_errorno.h \
    Src/Hardware/SerialPortService.h \
    Src/Framework/Manager/BluetoothManager.h \
    Src/Framework/Manager/BluetoothManagerGoc.h \
    Src/Application/MultiMedia/Music/musicplaywidget.h \
    Src/Application/MultiMedia/Music/musiclistwidget.h \
    Src/Application/MultiMedia/Music/musiclistitem.h \
    Src/Application/MultiMedia/Music/musicprogresswidget.h \
    Src/Application/MultiMedia/Music/musicclickwidget.h \
    Src/Application/MultiMedia/Image/flowadapter.h \
    Src/Application/MultiMedia/Image/flowview.h \
    Src/Application/MultiMedia/Music/rotatewidget.h \
    Src/Application/MultiMedia/BtMusic/btmusicwidget.h \
    Src/Application/MultiMedia/Video/videoplaywidget.h \
    Src/Application/MultiMedia/Tools/mediatoolswidget.h \
    Src/Application/MultiMedia/Tools/mediautils.h \
     Src/Application/MultiMedia/multimedia.h \
    Src/Framework/MultimediaService/multimediaservice.h \
    Src/Framework/MultimediaService/multimediautils.h \
    Src/Framework/MultimediaService/player.h \
    Src/Framework/MultimediaService/DeviceWatcher/devicewatcher.h \
    Src/Framework/MultimediaService/DeviceWatcher/DiskScanner/diskscanner.h \
    Src/Framework/MultimediaService/CustomThread/customthread.h \
    Src/Framework/MultimediaService/MusicPlayer/musicplayer.h \
    Src/Framework/MultimediaService/MediaDb/mediadb.h \
    Src/Framework/MultimediaService/MediaDb/mediadbentity.h \
    Src/Framework/MultimediaService/VideoPlayer/videoplayer.h \
    Src/Framework/MultimediaService/ImagePlayer/imageplayer.h \
    Src/Application/MultiMedia/Music/musicid3.h \
    Src/Framework/MultimediaService/BtMusicPlayer/btmusicplayer.h \
    Src/Application/Launcher/viewpagerwidget.h \
    Src/Application/Radio/radio_unit.h \
    Src/Application/Radio/radio_data.h \
    Src/Application/Radio/radio_process.h \
    Src/Application/Settings/wheelview.h \
    Src/Application/Settings/tumbler.h \
    Src/Application/BlueTooth/Phone/phonelistwidgetitem.h \
    Src/Application/BlueTooth/Phone/phonerecordwidget.h \
    Src/Application/BlueTooth/Phone/listitembean.h \
    Src/Application/BlueTooth/Phone/customwidget.h \
    Src/Application/BlueTooth/Phone/phonedialwidget.h \
    Src/Application/BlueTooth/Phone/btphonewidget.h \
    Src/Application/BlueTooth/Phone/phonedeviceswidget.h \
    Src/Application/BlueTooth/Phone/phoneoptionswidget.h \
    Src/Application/BlueTooth/Phone/phoneoptionwidgetitem.h \
    Libs/Etal/etal_api.h \
    Libs/Etal/etaltml_api.h \
    Libs/Etal/etaltml_types.h \
    Libs/Etal/etal_types.h \
    Libs/Etal/etalversion.h \
    Src/Hardware/RadioService.h \
    Src/Framework/Manager/RadioManager.h \
    Src/Framework/Manager/RadioUnit.h



RESOURCES += \
    Res/test.qrc \
    Res/simulation.qrc \
    Res/multimedia.qrc \
    Res/settingsrc.qrc \
    Res/commonsrc.qrc \
    Res/blu.qrc \
    Res/systemuisrc.qrc \
    Res/launchersrc.qrc \
    Res/rediosrc.qrc \
	Res/resource.qrc
	


#DISTFILES += \

#INCLUDEPATH += $$PWD/Libs/Etal
#DEPENDPATH += $$PWD/Libs/Etal
#unix:!macx: LIBS += -L$$PWD/Libs/Etal/etal.a
#unix:!macx: PRE_TARGETDEPS += $$PWD/Libs/Etal/etal.a





unix:!macx: LIBS += $$PWD/Libs/Etal/etal.a

INCLUDEPATH += $$PWD/Libs/Etal
DEPENDPATH += $$PWD/Libs/Etal

##unix:!macx: PRE_TARGETDEPS += $$PWD/Libs/Etal/libetal.a
