#ifndef MEDIAUTILS_H
#define MEDIAUTILS_H

#include <QString>
#include <QLabel>
#include <QWidget>
#include <QFileInfo>

class MediaUtils
{
public:
    MediaUtils();

    enum MEDIA_TYPE {
        ALL_MEDIA = 0, //所有类型
        MUSIC = 1, //播放音乐
        VIDEO = 2, //播放视频
        BT_MUSIC = 3, //播放蓝牙音乐
        MUSIC_LIST = 4, //音乐文件列表
        VIDEO_LIST = 5,  //视频文件列表
        IMAGE = 6,       //图片
        DIR_LIST         //文件夹列表
    };

    enum DeviceWatcherType {
        DWT_Undefined  = 0,
        DWT_SDDisk = 1,
        DWT_USBDisk = 2,
    };

    enum PLAY_MODE {
        ORDER = 1, //顺序播放模式
        RANDOM = 2, //随机播放模式
        LOOP = 3, //循环播放模式
        SINGLE_LOOP = 4 //单曲循环播放模式
    };

    enum QUERY_MODE {
        QUERY_All_Files = 1, //查询所有文件
        QUERY_Main_Dir = 2, //查询主文件夹
        QUERY_Current_Dir = 3,//查询当前文件夹
    };

public:
    static inline QString getLastToName(QString path) {
         return path.mid(path.lastIndexOf('/')+1);
    }
    static inline QString getUpperPath(QString path) {
         return path.left(path.lastIndexOf('/'));
    }

    static bool isDirPath(QString path);
    static void setLabText(QWidget *text, int size);
    static void setWidgetBackground(QWidget *widget, QString path);

    static inline QPixmap getPixmap(QString path) {
        QImage image;
        image.load(path);
        return QPixmap::fromImage(image);
    }
    static inline QPixmap getPixmap(QString path, int width, int height) {
        QImage image;
        image.load(path);
        return QPixmap::fromImage(image.scaled(QSize(width, height),
                                               Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
    static inline QPixmap getPixmap(QString path, QSize size) {
        QImage image;
        image.load(path);
        return  QPixmap::fromImage(image.scaled(size));
    }
};

#endif // MEDIAUTILS_H
