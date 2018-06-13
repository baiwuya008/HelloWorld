#ifndef MEDIAUTILS_H
#define MEDIAUTILS_H


class MediaUtils
{
public:
    MediaUtils();

    enum MEDIA_TYPE {
        MUSIC = 1, //播放音乐
        VIDEO = 2, //播放视频
        BT_MUSIC = 3, //播放蓝牙音乐
        MUSIC_LIST = 4, //音乐文件列表
        VIDEO_LIST = 5,  //视频文件列表
        IMAGE = 6       //图片
    };
};

#endif // MEDIAUTILS_H
