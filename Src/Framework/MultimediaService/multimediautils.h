#ifndef MULTIMEDIAUTILS_H
#define MULTIMEDIAUTILS_H


class MultimediaUtils
{
public:
    MultimediaUtils();

    typedef enum {
        MUSIC = 1, //播放音乐
        VIDEO = 2, //播放视频
        BT_MUSIC = 3, //播放蓝牙音乐
        MUSIC_LIST = 4, //音乐文件列表
        VIDEO_LIST = 5,  //视频文件列表
        IMAGE = 6       //图片
    } MultimediaType;
    #define MultimediaType int

    enum DeviceWatcherType {
        DWT_Undefined  = -1,
        DWT_SDDisk = 0,
        DWT_USBDisk = 1,
    };
    #define DeviceWatcherType int

public:

};

#endif // MULTIMEDIAUTILS_H
