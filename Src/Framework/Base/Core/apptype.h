#ifndef APPTYPE_H
#define APPTYPE_H

enum AppType {
    T_None = -1,
    //this section for Activity type
    T_SystemUi = 0,
    T_Home = 1,
    T_ViewPaper0,
    T_ViewPaper1,
    T_Radio,
    T_RadioAm,
    T_Bluetooth,
    T_BluetoothDial,
    T_BluetoothContact,
    T_BluetoothRecord,
    T_BluetoothMusic,
    T_BluetoothSetting,
    T_SDDisk,
    T_SDDiskMusic,
    T_SDDiskImage,
    T_SDDiskVideo,
    T_SDMusic,
    T_SDImage,
    T_SDImageFullScreen,
    T_SDVideo,
    T_SDVideoFullScreen,
    T_USBDisk,
    T_USBDiskMusic,
    T_USBDiskImage,
    T_USBDiskVideo,
    T_USBMusic,
    T_USBImage,
    T_USBImageFullScreen,
    T_USBVideo,
    T_USBVideoFullScreen,
    T_Ipod,
    T_Link,
    T_Carlife,
    T_Auto,
    T_Carplay,
    T_AVIN,
    T_AVINFullScreen,
    T_Camera,
    T_CameraFullScreen,
    T_Steering,
    T_Setting,
    T_SettingGeneral,
    T_SettingStyle,
    T_SettingSound,
    T_SettingFactory,
    //************************


    //this section for Service type
    T_ServiceSectionStart= 0x1000,

    //************************

    //*************this section for All
    T_All = 0x8000,
    //************************
};

#endif // APPTYPE_H
