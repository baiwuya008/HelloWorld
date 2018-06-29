#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <QObject>
#include "Src/Hardware/SerialPortService.h"

class BluetoothManagerPrivate;
class BluetoothManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(BluetoothManager)
public:
    explicit BluetoothManager(QObject *parent = 0);

    //data lenth must less then 128 bytes
    void sendMsg(unsigned char cmd_id,unsigned char *data,unsigned char len);

    void openDevice(int port,SerialPortService::TYPE type=SerialPortService::MCU_NORMAL_SERIALPORT);

    void setupDevice(int baudrate,int nbits,char parary,int stopbits);

    void initService();

    virtual void callBackRspMsg(unsigned char cmd_id,unsigned char *data,unsigned char len){};

    //---------------some normal bt ctrl functions
    //注释后面带--》的为操作后相应的回调回复
    //打开蓝牙---->onBluetoothOpen()
    virtual void openBluetooth(){};

    //关闭蓝牙---->onBluetoothClose()
    virtual void closeBluetooth(){};

    //蓝牙协议软复位--->onInitSucceed()
    virtual void resetBluetooth(){};

    //获取本地蓝牙名称--->onLocalName()
    virtual void getLocalName(){};

    //获取连接设备蓝牙名称--->onCurrentDeviceName()
    virtual void getCurrentDeviceName(){};

    //设置本地蓝牙名称--->Succeed/Fail
    virtual void setLocalName(QString name){};

    //获取蓝牙pin码--->onCurrentPinCode()
    virtual void getPinCode(){};

    //设置蓝牙pin码 4bit--->Succeed/Fail
    virtual void setPinCode(QString pincode){};

    //获取本地蓝牙地址--->onLocalAddress()
    virtual void getLocalAddress(){};

    //获取当前连接设备蓝牙地址--->onCurrentDevicesAddr()
    virtual void getCurrentDeviceAddr(){};

    //获取自动连接及自动接听状态--->onAutoConnectAnswer()
    virtual void getAutoConnectAnswer(){};

    //设置自动连接--->Succeed/Fail
    virtual void setAutoConnect(){};

    //取消自动连接--->Succeed/Fail
    virtual void cancelAutoConnect(){};

    //设置自动接听--->Succeed/Fail
    virtual void setAutoAnswer(){};

    //取消自动接听--->Succeed/Fail
    virtual void cancelAutoAnswer(){};

    //获取蓝牙版本信息--->onVersionDate()
    virtual void getVersion(){};

    //进入配对模式（蓝牙可见）--->Succeed/Fail
    virtual void setPairMode(){};

    //退出配对模式（蓝牙不可见）--->Succeed/Fail
    virtual void cancelPairMode(){};

    //连接上次连接过的设备--->onHfpConnected() onA2dpConnected()
    virtual void connectLast(){};

    //配对蓝牙--->Succeed/Fail
    virtual void pairedDevice(QString addr){};

    //连接指定地址设备 地址可以从搜索或配对列表中获取--->Succeed/Fail
    virtual void connectDevice(QString addr){};

    //连接指定地址A2dp服务--->onA2dpConnected()
    virtual void connectA2dp(QString addr){};
    virtual void connectA2dpp(){};

    //连接指定地址HFP服务--->onHfpConnected()
    virtual void connectHFP(QString addr){};

    //连接指定地址Hid服务--->onHidConnected()
    virtual void connectHid(QString addr){};

    //连接指定地址Spp服务--->onSppConnected()
    virtual void connectSpp(QString addr){};

    //断开当前连接设备的所有服务--->onSppDisconnected() onHfpDisconnected() onA2dpDisconnected() onHidDisconnected()
    virtual void disconnectAll(){};

    //断开当前连接设备的A2DP服务--->onA2dpDisconnected()
    virtual void disconnectA2DP(){};

    //断开当前连接设备的HFP服务--->onHfpDisconnected()
    virtual void disconnectHFP(){};

    //断开当前连接设备的Hid服务--->onHidDisconnected()
    virtual void disconnectHid(){};

    //断开当前连接设备的Spp服务--->onSppDisconnected()
    virtual void disconnectSpp(){};

    //删除指定地址的配对列表--->Succeed/Fail
    virtual void deletePair(QString addr){};

    //开始搜索周边蓝牙设备--->onDiscovery()
    virtual void startDiscovery(){};

    //停止蓝牙搜索--->onDiscoveryDone()
    virtual void stopDiscovery(){};

    //获取当前配对列表--->onCurrentPairList()
    virtual void getPairList(){};

 //hfp
    //来电接听--->onTalking()
    virtual void phoneAnswer(){};

    //挂断电话--->onHangUp()
    virtual void phoneHangUp(){};

    //拨打电话--->onCallSucceed()
    virtual void phoneDail(QString num){};

    //拨打分机号--->onInitSucceed()
    virtual void phoneTransmitDTMFCode(QString code){};

    //切换声道到手机端--->onHfpRemote() onVoiceDisconnected()
    virtual void phoneTransfer(){};

    //切换声道到车机端--->onHfpLocal() onVoiceConnected()
    virtual void phoneTransferBack(){};

    //语音拨号--->onTalking()
    virtual void phoneVoiceDail(){};

    //取消语音拨号--->onHangUp()
    virtual void cancelPhoneVoiceDail(){};

//contacts
    //电话本下载--->onPhoneBook() onPhoneBookDone()
    virtual void phoneBookStartUpdate(){};

    //暂停电话本下载---> onPhoneBookDone()
    virtual void pauseDownLoadContact(){};

    //继续电话本下载---> Succeed/Fail
    virtual void restartDownLoadContact(){};

    //停止电话本下载---> Succeed/Fail
    virtual void stopDownLoadContact(){};

    //通话记录下载--->onCallLogs() onCallLogsDone()
    //type: 1 outgoing ; 2 missed ; 3 incoming
    virtual void callLogsStartUpdate(int type){};

//music
    //音乐播放或暂停--->onMusicPlaying() onMusicStopped() onMusicInfo()
    virtual void musicPlayOrPause(){};

    //音乐播放
    virtual void musicPlay(){};

    //音乐暂停
    virtual void musicPause(){};

    //音乐停止--->onMusicStopped()
    virtual void musicStop(){};

    //上一曲
    virtual void musicPrevious(){};

    //下一曲
    virtual void musicNext(){};

    //音乐静音 用于混音处理
    virtual void musicMute(){};

    //音乐解除静音
    virtual void musicUnmute(){};

    //音乐半音 用于GPS出声时混音处理
    virtual void musicBackground(){};

    //音乐恢复正常 配合半音处理GPS出声时混音处理
    virtual void musicNormal(){};

    //获取蓝牙音乐信息---->onMusicInfo()
    virtual void getMusicInfo(){};

//status
    //查询Hfp服务状态---->onHfpStatus()
    virtual void inqueryHfpStatus(){};

    //查询A2dp服务状态---->onA2dpStatus()
    virtual void inqueryA2dpStatus(){};

    //打开mic头
    virtual void micOn(){};

    //关闭mic头
    virtual void micOff(){};

 //----------hid

    //鼠标移动
    //point 8byte x 4byte , y 4byte
    virtual void hidMouseMove(QString point){};

    //鼠标移动
    //point 8byte x 4byte , y 4byte
    virtual void hidMouseDown(QString point){};

    //鼠标移动
    //point 8byte x 4byte , y 4byte
    virtual void hidMouseUp(QString point){};

    //Home按键按下
    virtual void hidHomeClick(){};

    //Back按键按下
    virtual void hidBackClick(){};

    //Menu按键按下
    virtual void hidMenuClick(){};


//----------spp

    //spp发送数据--->onSppData()
    virtual void sspSendData(QString addr,QString data){};

//-----other
    virtual void setProfileEnable(bool enable[]){};
    virtual void getProfileEnable(){};
//------------------------------------



//----------the next is the callback function
   virtual  void onHfpDisconnected(){};
   virtual  void onHfpConnected(){};
   virtual  void onCallSucceed(QString number){};
   virtual  void onIncoming(QString number){};
   virtual  void onHangUp(){};
   virtual  void onTalking(QString number){};
   virtual  void onRingStart(){};
   virtual  void onRingStop(){};
   virtual  void onHfpLocal(){};
   virtual  void onHfpRemote(){};
   virtual  void onInPairMode(){};
   virtual  void onExitPairMode(){};
   virtual  void onInitSucceed(){};
   virtual  void onMusicPlaying(){};
   virtual  void onMusicStopped(){};
   virtual  void onVoiceConnected(){};
   virtual  void onVoiceDisconnected(){};
   virtual  void onAutoConnectAnswer(QString autoStatus){};
   virtual  void onCurrentAddr(QString addr){};
   virtual  void onCurrentName(QString name){};

   virtual  void onHfpStatus(int status){};
   virtual  void onAvStatus(int status){};
   virtual  void onVersionDate(QString version){};
   virtual  void onCurrentDeviceName(QString name){};
   virtual  void onCurrentPinCode(QString code){};
   virtual  void onA2dpConnected(){};
   virtual  void onCurrentPairList(int index,QString name,QString addr){};
   virtual  void onA2dpDisconnected(){};
   virtual  void onPhoneBook(QString name,QString number){};
   virtual  void onPhoneBookDone(){};
   virtual  void onCalllogDone(){};
   virtual  void onCalllog(int type,QString name,QString number){};
   virtual  void onDiscovery(QString type,QString name,QString addr){};
   virtual  void onDiscoveryDone(){};
   virtual  void onLocalAddress(QString addr){};
   virtual  void onHidConnected(){};
   virtual  void onHidDisconnected(){};
   virtual  void onMusicInfo(QString music, QString artist,QString album,int duration,int pos,int total){};
   virtual  void onMusicPos(int current,int total){};
   virtual  void onOutGoingOrTalkingNumber(QString number){};
   virtual  void onConnecting(){};
   virtual  void onSppData(int index, QString data){};
   virtual  void onSppConnect(int index){};
   virtual  void onSppDisconnect(int index){};
   virtual  void onSppStatus(int status){};
   virtual  void onOppReceivedFile(QString path){};
   virtual  void onOppPushSuccess(){};
   virtual  void onOppPushFailed(){};
   virtual  void onHidStatus(int status){};
   virtual  void onPanConnect(){};
   virtual  void onPanDisconnect(){};
   virtual  void onPanStatus(int status){};
   virtual  void onProfileEnbled(bool enabled[]){};
   virtual  void onPairedState(int state){};
   virtual  void onMicState(int state){};
//-------------------------------------------

signals:

public slots:
    void rspMsg(unsigned char cmd_id,unsigned char *data,unsigned char len);
private:
    Q_DECLARE_PRIVATE(BluetoothManager)
    BluetoothManagerPrivate* const d_ptr;
};

#endif // BLUETOOTHMANAGER_H
