#ifndef MULTIMEDIAUTILS_H
#define MULTIMEDIAUTILS_H

#include <QString>
#include <QStringList>
#include <QDebug>

class MultimediaUtils
{
public:
    MultimediaUtils();

    typedef enum {
        ALL_MEDIA = 0, //所有类型
        MUSIC = 1, //播放音乐
        VIDEO = 2, //播放视频
        BT_MUSIC = 3, //播放蓝牙音乐
        MUSIC_LIST = 4, //音乐文件列表
        VIDEO_LIST = 5,  //视频文件列表
        IMAGE = 6,       //图片
        DIR_LIST         //文件夹列表
    } MultimediaType;
#define MultimediaType int

    enum DeviceWatcherType {
        DWT_Undefined  = 0,
        DWT_SDDisk = 1,
        DWT_USBDisk = 2,
    };
#define DeviceWatcherType int


    typedef enum {
        ORDER = 1, //顺序播放模式
        RANDOM = 2, //随机播放模式
        LOOP = 3, //循环播放模式
        SINGLE_LOOP = 4 //单曲循环播放模式
    } PLAY_MODE;
#define PLAY_MODE int

    typedef enum {
        SCAN_Undefined = -1,
        SCAN_Busy = 1,
        SCAN_Finish = 2,
    } SCAN_STATUS;
#define SCAN_STATUS int

    typedef enum {
        QUERY_All_Files = 1, //查询所有文件
        QUERY_Main_Dir = 2, //查询主文件夹
        QUERY_Current_Dir = 3,//查询当前文件夹
    } QUERY_MODE;
#define QUERY_MODE int

public:
    static QString getLastToName(QString path);
    static QString changeWindowsPath(QString filePath);
};

#endif // MULTIMEDIAUTILS_H
