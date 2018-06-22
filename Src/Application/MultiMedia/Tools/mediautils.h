#ifndef MEDIAUTILS_H
#define MEDIAUTILS_H

#include <QString>

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
        IMAGE = 6       //图片
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

public:
    static QString getLastToName(QString path);
};

#endif // MEDIAUTILS_H
