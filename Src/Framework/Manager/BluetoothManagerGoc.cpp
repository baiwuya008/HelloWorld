#include "BluetoothManagerGoc.h"
#include <QDebug>

class BluetoothManagerGocPrivate{
public:
    explicit BluetoothManagerGocPrivate(BluetoothManagerGoc *parent);
    ~BluetoothManagerGocPrivate();

private:
    Q_DECLARE_PUBLIC(BluetoothManagerGoc)
    BluetoothManagerGoc* const q_ptr;

};

BluetoothManagerGocPrivate::BluetoothManagerGocPrivate(BluetoothManagerGoc *parent)
    :q_ptr(parent)
{

}

BluetoothManagerGocPrivate::~BluetoothManagerGocPrivate()
{

}

//--------------
BluetoothManagerGoc * BluetoothManagerGoc::self = NULL;

BluetoothManagerGoc * BluetoothManagerGoc::instance() {
    if(self == NULL){self = new BluetoothManagerGoc();}
    return self;
}


BluetoothManagerGoc::BluetoothManagerGoc(QObject *parent) :
    BluetoothManager(parent),d_ptr(new BluetoothManagerGocPrivate(this))
{
   initBluetoothModleAndService();
}

void BluetoothManagerGoc::initBluetoothModleAndService()
{
  openDevice(0,SerialPortService::BT_GOC_VIRTUAR_SERIALPORT); //port 3
  setupDevice(115200,8,'N',1);
  initService();
}

//注释后面带--》的为操作后相应的回调回复
//打开蓝牙---->onBluetoothOpen()
void BluetoothManagerGoc::openBluetooth(){
    unsigned char cmd[]={'P','1'};
    sendMsg(2,cmd,sizeof(cmd));
}

//关闭蓝牙---->onBluetoothClose()
void BluetoothManagerGoc::closeBluetooth(){
    unsigned char cmd[]={'P','0'};
    sendMsg(2,cmd,sizeof(cmd));
}

//蓝牙协议软复位--->onInitSucceed()
void BluetoothManagerGoc::resetBluetooth(){
    unsigned char cmd[]={'C','Z'};
    sendMsg(2,cmd,sizeof(cmd));
}

//获取本地蓝牙名称--->onLocalName()
void BluetoothManagerGoc::getLocalName(){
    unsigned char cmd[]={'M','M'};
    sendMsg(2,cmd,sizeof(cmd));
}

//获取连接设备蓝牙名称--->onCurrentDeviceName()
void BluetoothManagerGoc::getCurrentDeviceName(){
    unsigned char cmd[]={'M','M'};
    sendMsg(2,cmd,sizeof(cmd));
}

//设置本地蓝牙名称--->Succeed/Fail
void BluetoothManagerGoc::setLocalName(QString name){
    unsigned char cmd[32]={'M','M',0};
    std::string str = name.toStdString();
    const char* ch = str.c_str();
    int name_size = sizeof(ch)-1;
    if(name_size>30) name_size =30;
    memcpy(cmd+2,ch,name_size);
    sendMsg(2,cmd,name_size+2);
}

//获取蓝牙pin码--->onCurrentPinCode()
void BluetoothManagerGoc::getPinCode(){
    unsigned char cmd[]={'M','N'};
    sendMsg(2,cmd,sizeof(cmd));
}

//设置蓝牙pin码 4bit--->Succeed/Fail
void BluetoothManagerGoc::setPinCode(QString pincode){
    unsigned char cmd[10]={'M','N',0};
    std::string str = pincode.toStdString();
    const char* ch = str.c_str();
    int name_size = sizeof(ch)-1;
    if(name_size>8) name_size =8;
    memcpy(cmd+2,ch,name_size);
    sendMsg(2,cmd,name_size+2);
}

//获取本地蓝牙地址--->onLocalAddress()
void BluetoothManagerGoc::getLocalAddress(){
    unsigned char cmd[]={'V','E'};
    sendMsg(2,cmd,sizeof(cmd));
}

//获取当前连接设备蓝牙地址--->onCurrentDevicesAddr()
void BluetoothManagerGoc::getCurrentDeviceAddr(){
    unsigned char cmd[]={'Q','A'};
    sendMsg(2,cmd,sizeof(cmd));
}

//获取自动连接及自动接听状态--->onAutoConnectAnswer()
void BluetoothManagerGoc::getAutoConnectAnswer(){
    unsigned char cmd[]={'M','F'};
    sendMsg(2,cmd,sizeof(cmd));
}

//设置自动连接--->Succeed/Fail
void BluetoothManagerGoc::setAutoConnect(){
    unsigned char cmd[]={'M','G'};
    sendMsg(2,cmd,sizeof(cmd));
}

//取消自动连接--->Succeed/Fail
void BluetoothManagerGoc::cancelAutoConnect(){
    unsigned char cmd[]={'M','H'};
    sendMsg(2,cmd,sizeof(cmd));
}

//设置自动接听--->Succeed/Fail
void BluetoothManagerGoc::setAutoAnswer(){
    unsigned char cmd[]={'M','P'};
    sendMsg(2,cmd,sizeof(cmd));
}

//取消自动接听--->Succeed/Fail
void BluetoothManagerGoc::cancelAutoAnswer(){
    unsigned char cmd[]={'M','Q'};
    sendMsg(2,cmd,sizeof(cmd));
}

//获取蓝牙版本信息--->onVersionDate()
void BluetoothManagerGoc::getVersion(){
    unsigned char cmd[]={'M','Y'};
    sendMsg(2,cmd,sizeof(cmd));
}

//进入配对模式（蓝牙可见）--->Succeed/Fail
void BluetoothManagerGoc::setPairMode(){
    unsigned char cmd[]={'C','A'};
    sendMsg(2,cmd,sizeof(cmd));
}

//退出配对模式（蓝牙不可见）--->Succeed/Fail
void BluetoothManagerGoc::cancelPairMode(){
    unsigned char cmd[]={'C','B'};
    sendMsg(2,cmd,sizeof(cmd));
}

//连接上次连接过的设备--->onHfpConnected() onA2dpConnected()
void BluetoothManagerGoc::connectLast(){
    unsigned char cmd[]={'C','C'};
    sendMsg(2,cmd,sizeof(cmd));
}

//配对蓝牙--->Succeed/Fail
void BluetoothManagerGoc::pairedDevice(QString addr){
    unsigned char cmd[32]={'D','B',0};
    std::string str = addr.toStdString();
    const char* ch = str.c_str();
    int name_size = sizeof(ch)-1;
    if(name_size>30) name_size =30;
    memcpy(cmd+2,ch,name_size);
    sendMsg(2,cmd,name_size+2);
}

//连接指定地址设备 地址可以从搜索或配对列表中获取--->Succeed/Fail
void BluetoothManagerGoc::connectDevice(QString addr){
    unsigned char cmd[32]={'C','C',0};
    std::string str = addr.toStdString();
    const char* ch = str.c_str();
    int name_size = sizeof(ch)-1;
    if(name_size>30) name_size =30;
    memcpy(cmd+2,ch,name_size);
    sendMsg(2,cmd,name_size+2);
}

//连接指定地址A2dp服务--->onA2dpConnected()
void BluetoothManagerGoc::connectA2dp(QString addr){
    unsigned char cmd[32]={'D','C',0};
    std::string str = addr.toStdString();
    const char* ch = str.c_str();
    int name_size = sizeof(ch)-1;
    if(name_size>30) name_size =30;
    memcpy(cmd+2,ch,name_size);
    sendMsg(2,cmd,name_size+2);
}
void BluetoothManagerGoc::connectA2dpp(){
    unsigned char cmd[]={'D','C'};
    sendMsg(2,cmd,sizeof(cmd));
}

//连接指定地址HFP服务--->onHfpConnected()
void BluetoothManagerGoc::connectHFP(QString addr){
    unsigned char cmd[32]={'S','C',0};
    std::string str = addr.toStdString();
    const char* ch = str.c_str();
    int name_size = sizeof(ch)-1;
    if(name_size>30) name_size =30;
    memcpy(cmd+2,ch,name_size);
    sendMsg(2,cmd,name_size+2);
}

//连接指定地址Hid服务--->onHidConnected()
void BluetoothManagerGoc::connectHid(QString addr){
    unsigned char cmd[32]={'H','C',0};
    std::string str = addr.toStdString();
    const char* ch = str.c_str();
    int name_size = sizeof(ch)-1;
    if(name_size>30) name_size =30;
    memcpy(cmd+2,ch,name_size);
    sendMsg(2,cmd,name_size+2);
}

//连接指定地址Spp服务--->onSppConnected()
void BluetoothManagerGoc::connectSpp(QString addr){
    unsigned char cmd[32]={'S','P',0};
    std::string str = addr.toStdString();
    const char* ch = str.c_str();
    int name_size = sizeof(ch)-1;
    if(name_size>30) name_size =30;
    memcpy(cmd+2,ch,name_size);
    sendMsg(2,cmd,name_size+2);
}

//断开当前连接设备的所有服务--->onSppDisconnected() onHfpDisconnected() onA2dpDisconnected() onHidDisconnected()
void BluetoothManagerGoc::disconnectAll(){
    unsigned char cmd[]={'C','D'};
    sendMsg(2,cmd,sizeof(cmd));
}

//断开当前连接设备的A2DP服务--->onA2dpDisconnected()
void BluetoothManagerGoc::disconnectA2DP(){
    unsigned char cmd[]={'D','A'};
    sendMsg(2,cmd,sizeof(cmd));
}

//断开当前连接设备的HFP服务--->onHfpDisconnected()
void BluetoothManagerGoc::disconnectHFP(){
    unsigned char cmd[]={'S','E'};
    sendMsg(2,cmd,sizeof(cmd));
}

//断开当前连接设备的Hid服务--->onHidDisconnected()
void BluetoothManagerGoc::disconnectHid(){
    unsigned char cmd[]={'H','D'};
    sendMsg(2,cmd,sizeof(cmd));
}

//断开当前连接设备的Spp服务--->onSppDisconnected()
void BluetoothManagerGoc::disconnectSpp(){
    unsigned char cmd[]={'S','H'};
    sendMsg(2,cmd,sizeof(cmd));
}

//删除指定地址的配对列表--->Succeed/Fail
void BluetoothManagerGoc::deletePair(QString addr){
    unsigned char cmd[32]={'C','V',0};
    std::string str = addr.toStdString();
    const char* ch = str.c_str();
    int name_size = sizeof(ch)-1;
    if(name_size>30) name_size =30;
    memcpy(cmd+2,ch,name_size);
    sendMsg(2,cmd,name_size+2);
}

//开始搜索周边蓝牙设备--->onDiscovery()
void BluetoothManagerGoc::startDiscovery(){
    unsigned char cmd[]={'S','D'};
    sendMsg(2,cmd,sizeof(cmd));
}

//停止蓝牙搜索--->onDiscoveryDone()
void BluetoothManagerGoc::stopDiscovery(){
    unsigned char cmd[]={'S','T'};
    sendMsg(2,cmd,sizeof(cmd));
}

//获取当前配对列表--->onCurrentPairList()
void BluetoothManagerGoc::getPairList(){
    unsigned char cmd[]={'M','X'};
    sendMsg(2,cmd,sizeof(cmd));
}

//hfp
//来电接听--->onTalking()
void BluetoothManagerGoc::phoneAnswer(){
    unsigned char cmd[]={'C','E'};
    sendMsg(2,cmd,sizeof(cmd));
}

//挂断电话--->onHangUp()
void BluetoothManagerGoc::phoneHangUp(){
    unsigned char cmd[]={'C','F'};
    sendMsg(2,cmd,sizeof(cmd));
}

//拨打电话--->onCallSucceed()
void BluetoothManagerGoc::phoneDail(QString num){
    unsigned char cmd[32]={'C','W',0};
    std::string str = num.toStdString();
    const char* ch = str.c_str();
    int name_size = sizeof(ch)-1;
    if(name_size>30) name_size =30;
    memcpy(cmd+2,ch,name_size);
    sendMsg(2,cmd,name_size+2);
}

//拨打分机号--->onInitSucceed()
void BluetoothManagerGoc::phoneTransmitDTMFCode(QString code){
    unsigned char cmd[32]={'C','X',0};
    std::string str = code.toStdString();
    const char* ch = str.c_str();
    int name_size = sizeof(ch)-1;
    if(name_size>30) name_size =30;
    memcpy(cmd+2,ch,name_size);
    sendMsg(2,cmd,name_size+2);
}

//切换声道到手机端--->onHfpRemote() onVoiceDisconnected()
void BluetoothManagerGoc::phoneTransfer(){
    unsigned char cmd[]={'C','O'};
    sendMsg(2,cmd,sizeof(cmd));
}

//切换声道到车机端--->onHfpLocal() onVoiceConnected()
void BluetoothManagerGoc::phoneTransferBack(){
    unsigned char cmd[]={'C','P'};
    sendMsg(2,cmd,sizeof(cmd));
}

//语音拨号--->onTalking()
void BluetoothManagerGoc::phoneVoiceDail(){
    unsigned char cmd[]={'C','I'};
    sendMsg(2,cmd,sizeof(cmd));
}

//取消语音拨号--->onHangUp()
void BluetoothManagerGoc::cancelPhoneVoiceDail(){
    unsigned char cmd[]={'C','J'};
    sendMsg(2,cmd,sizeof(cmd));
}

//contacts
//电话本下载--->onPhoneBook() onPhoneBookDone()
void BluetoothManagerGoc::phoneBookStartUpdate(){
    unsigned char cmd[]={'P','B'};
    sendMsg(2,cmd,sizeof(cmd));
}

//暂停电话本下载---> onPhoneBookDone()
void BluetoothManagerGoc::pauseDownLoadContact(){
    unsigned char cmd[]={'P','O'};
    sendMsg(2,cmd,sizeof(cmd));
}


//继续电话本下载---> Succeed/Fail
void BluetoothManagerGoc::restartDownLoadContact(){
    unsigned char cmd[]={'P','Q'};
    sendMsg(2,cmd,sizeof(cmd));
}

//停止电话本下载---> Succeed/Fail
void BluetoothManagerGoc::stopDownLoadContact(){
    unsigned char cmd[]={'P','S'};
    sendMsg(2,cmd,sizeof(cmd));
}

//通话记录下载--->onCallLogs() onCallLogsDone()
//type: 1 outgoing ; 2 missed ; 3 incoming
void BluetoothManagerGoc::callLogsStartUpdate(int type){

    switch (type) {
    case 1:
       {
        unsigned char cmd[]={'P','H'};
        sendMsg(2,cmd,sizeof(cmd));
       }
        break;
    case 2:
       {
         unsigned char cmd[]={'P','J'};
         sendMsg(2,cmd,sizeof(cmd));
       }
        break;
    case 3:
       {
         unsigned char cmd[]={'P','I'};
         sendMsg(2,cmd,sizeof(cmd));
       }
        break;
    default:
        break;
    }
}

//music
//音乐播放或暂停--->onMusicPlaying() onMusicStopped() onMusicInfo()
void BluetoothManagerGoc::musicPlayOrPause(){
    unsigned char cmd[]={'M','A'};
    sendMsg(2,cmd,sizeof(cmd));
}

//音乐播放
void BluetoothManagerGoc::musicPlay(){
    unsigned char cmd[]={'M','S'};
    sendMsg(2,cmd,sizeof(cmd));
}

//音乐暂停
void BluetoothManagerGoc::musicPause(){
    unsigned char cmd[]={'M','J'};
    sendMsg(2,cmd,sizeof(cmd));
}

//音乐停止--->onMusicStopped()
void BluetoothManagerGoc::musicStop(){
    unsigned char cmd[]={'M','C'};
    sendMsg(2,cmd,sizeof(cmd));
}

//上一曲
void BluetoothManagerGoc::musicPrevious(){
    unsigned char cmd[]={'M','E'};
    sendMsg(2,cmd,sizeof(cmd));
}

//下一曲
void BluetoothManagerGoc::musicNext(){
    unsigned char cmd[]={'M','D'};
    sendMsg(2,cmd,sizeof(cmd));
}

//音乐静音 用于混音处理
void BluetoothManagerGoc::musicMute(){
    unsigned char cmd[]={'V','A'};
    sendMsg(2,cmd,sizeof(cmd));
}

//音乐解除静音
void BluetoothManagerGoc::musicUnmute(){
    unsigned char cmd[]={'V','B'};
    sendMsg(2,cmd,sizeof(cmd));
}

//音乐半音 用于GPS出声时混音处理
void BluetoothManagerGoc::musicBackground(){
    unsigned char cmd[]={'V','C'};
    sendMsg(2,cmd,sizeof(cmd));
}

//音乐恢复正常 配合半音处理GPS出声时混音处理
void BluetoothManagerGoc::musicNormal(){
    unsigned char cmd[]={'V','D'};
    sendMsg(2,cmd,sizeof(cmd));
}

//获取蓝牙音乐信息---->onMusicInfo()
void BluetoothManagerGoc::getMusicInfo(){
    unsigned char cmd[]={'M','K'};
    sendMsg(2,cmd,sizeof(cmd));
}

//status
//查询Hfp服务状态---->onHfpStatus()
void BluetoothManagerGoc::inqueryHfpStatus(){
    unsigned char cmd[]={'C','Y'};
    sendMsg(2,cmd,sizeof(cmd));
}

//查询A2dp服务状态---->onA2dpStatus()
void BluetoothManagerGoc::inqueryA2dpStatus(){
    unsigned char cmd[]={'M','V'};
    sendMsg(2,cmd,sizeof(cmd));
}

//打开mic头
void BluetoothManagerGoc::micOn(){
    unsigned char cmd[]={'I','O'};
    sendMsg(2,cmd,sizeof(cmd));
}

//关闭mic头
void BluetoothManagerGoc::micOff(){
    unsigned char cmd[]={'I','C'};
    sendMsg(2,cmd,sizeof(cmd));
}



//the manager will call back this function while get some data from the bt modle
void BluetoothManagerGoc::callBackRspMsg(unsigned char cmd_id,unsigned char *data,unsigned char len)
{
  qDebug()<<"BluetoothManagerGoc::callBackRspMsg"<<" len:"<<len<<endl;
//  for (int var = 0; var < len; ++var) {
//      qDebug()<<"data["<<var<<"]="<<data[var]<<endl;
//  }
  //Command Parser
   if(data[0]=='I'&& data[1]=='B'){
     onHfpConnected();
     return;
   }
   if(data[0]=='I'&& data[1]=='A'){
     onHfpDisconnected();
     return;
   }
   if(data[0]=='I'&& data[1]=='C'){
     if(len<4){
        onCallSucceed("");
     }else{
        QByteArray bytes = QByteArray((char*)data);
        QString cmdString = QString(bytes);
        onCallSucceed(cmdString.right(cmdString.size()-2));
     }

     return;
   }
   if(data[0]=='I'&& data[1]=='D'){
       if(len<4){
          onIncoming("");
       }else{
          QByteArray bytes = QByteArray((char*)data);
          QString cmdString = QString(bytes);
          onIncoming(cmdString.right(cmdString.size()-2));
       }
     return;
   }
   if(data[0]=='I'&& data[1]=='F'){
     onHangUp();
     return;
   }
   if(data[0]=='I'&& data[1]=='G'){
       if(len<4){
          onTalking("");
       }else{
          QByteArray bytes = QByteArray((char*)data);
          QString cmdString = QString(bytes);
          onTalking(cmdString.right(cmdString.size()-2));
       }
     return;
   }
   if(data[0]=='V'&& data[1]=='R'){
     if(len<3){
        qDebug()<<"VR error here!!"<<endl;
     }else{
         if(data[2]=='1'){
            onRingStart();
         }else if(data[2]=='0'){
            onRingStop();
         }
     }
     return;
   }
   if(data[0]=='T'&& data[1]=='0'){
     onHfpLocal();
     return;
   }
   if(data[0]=='T'&& data[1]=='1'){
     onHfpRemote();
     return;
   }

   if(data[0]=='I'&& data[1]=='I'){
     onInPairMode();
     return;
   }
   if(data[0]=='I'&& data[1]=='J'){
     onExitPairMode();
     return;
   }
   if(data[0]=='I'&& data[1]=='S'){
     onInitSucceed();
     return;
   }
   if(data[0]=='M'&& data[1]=='B'){
     onMusicPlaying();
     return;
   }
   if(data[0]=='M'&& data[1]=='A'){
     onMusicStopped();
     return;
   }
   if(data[0]=='M'&& data[1]=='C'){
     onVoiceConnected();
     return;
   }
   if(data[0]=='M'&& data[1]=='D'){
     onVoiceDisconnected();
     return;
   }
   if(data[0]=='M'&& data[1]=='F'){
       if(len<4){
          qDebug()<<"MF error here!!"<<endl;
       }else{
          QByteArray bytes = QByteArray((char*)data);
          QString cmdString = QString(bytes);
          onAutoConnectAnswer(cmdString.right(cmdString.size()-2));
       }
     return;
   }
   if(data[0]=='J'&& data[1]=='H'){
       if(len<3){
          qDebug()<<"JH error here!!"<<endl;
       }else{
          QByteArray bytes = QByteArray((char*)data);
          QString cmdString = QString(bytes);
          onCurrentAddr(cmdString.right(cmdString.size()-2));
       }
     return;
   }
   if(data[0]=='S'&& data[1]=='A'){
       if(len<3){
          qDebug()<<"SA error here!!"<<endl;
       }else{
          QByteArray bytes = QByteArray((char*)data);
          QString cmdString = QString(bytes);
          onCurrentName(cmdString.right(cmdString.size()-2));
       }
     return;
   }
   if(data[0]=='M'&& data[1]=='U'){
       if(len<3){
          qDebug()<<"MU error here!!"<<endl;
       }else{
          onAvStatus(data[2]-'0');
       }
     return;
   }
   if(data[0]=='M'&& data[1]=='G'){
       if(len<3){
          qDebug()<<"MG error here!!"<<endl;
       }else{
          onHfpStatus(data[2]-'0');
       }
     return;
   }
   if(data[0]=='I'&& data[1]=='O'){
       if(len<3){
          qDebug()<<"IO error here!!"<<endl;
       }else{
          onMicState(data[2]-'0');
       }
     return;
   }
   if((data[0]=='M'&& data[1]=='W')
       ||(data[0]=='S'&& data[1]=='Y')){
       if(len<3){
          qDebug()<<"MW,SY error here!!"<<endl;
       }else{
          QByteArray bytes = QByteArray((char*)data);
          QString cmdString = QString(bytes);
          onVersionDate(cmdString.right(cmdString.size()-2));
       }
     return;
   }
   if(data[0]=='M'&& data[1]=='M'){
       if(len<3){
          qDebug()<<"MM error here!!"<<endl;
       }else{
          QByteArray bytes = QByteArray((char*)data);
          QString cmdString = QString(bytes);
          onCurrentDeviceName(cmdString.right(cmdString.size()-2));
       }
     return;
   }
   if(data[0]=='M'&& data[1]=='N'){
       if(len<3){
          qDebug()<<"MN error here!!"<<endl;
       }else{
          QByteArray bytes = QByteArray((char*)data);
          QString cmdString = QString(bytes);
          onCurrentPinCode(cmdString.right(cmdString.size()-2));
       }
     return;
   }
   if(data[0]=='M'&& data[1]=='H'){
     onA2dpConnected();
     return;
   }
   if(data[0]=='M'&& data[1]=='Y'){
     onA2dpDisconnected();
     return;
   }
   if(data[0]=='M'&& data[1]=='X'){
       if(len<15){
          qDebug()<<"MX error here!!"<<endl;
       }else if(len==15){
           QByteArray bytes = QByteArray((char*)data);
           QString cmdString = QString(bytes);
           onCurrentPairList((data[2]-'0'),"",cmdString.right(cmdString.size()-3));
       }
       else{
           QByteArray bytes = QByteArray((char*)data);
           QString cmdString = QString(bytes);
           onCurrentPairList((data[2]-'0'),cmdString.right(cmdString.size()-15),cmdString.mid(3,12));
       }
     return;
   }
   if(data[0]=='P'&& data[1]=='B'){
       if(len<6){
          qDebug()<<"PB error here!!"<<endl;
       }
       else{
           QByteArray bytes = QByteArray((char*)data);
           QString cmdString = QString(bytes);

           QString name = NULL;
           QString number = NULL;
           if(cmdString.contains("[FF]")){
               QStringList myList= cmdString.right(cmdString.size()-2).split(QString("[FF]"));
               if(myList.size()==2){
                  name =myList.at(0);
                  number =myList.at(1);
               }
           }else{
              QString namels = cmdString.mid(2,2);
              QString numbls = cmdString.mid(4,2);
              int nameLen = cmdString.mid(2,2).toInt();
              int numLen = cmdString.mid(4,2).toInt();
              if(nameLen>0){
                  name = cmdString.mid(6,nameLen);
              }else{
                  name = "";
              }

              if(numLen>0){
                 number = cmdString.mid(6+nameLen,numLen);

              }else{
                  number = "";
              }

           }

           if(name !=NULL && number != NULL){
              onPhoneBook(name,number);
           }

       }
     return;
   }
   if(data[0]=='P'&& data[1]=='C'){
     onPhoneBookDone();
     return;
   }
   if(data[0]=='P'&& data[1]=='E'){
     onCalllogDone();
     return;
   }
   if(data[0]=='P'&& data[1]=='D'){
       if(len<4){
          qDebug()<<"PD error here!!"<<endl;
       }
       else{
           QByteArray bytes = QByteArray((char*)data);
           QString cmdString = QString(bytes);
           QStringList myList= cmdString.right(cmdString.size()-3).split(QString("[FF]"));
           onCalllog((data[2]-'0'),myList.at(0),myList.at(1));
       }
     return;
   }
   if(data[0]=='S'&& data[1]=='F'){
       if(len<14){
          qDebug()<<"SF error here!!"<<endl;
       }else if(len==14){
           QByteArray bytes = QByteArray((char*)data);
           QString cmdString = QString(bytes);
           onDiscovery("","",cmdString.right(cmdString.size()-2));
       }
       else{
           QByteArray bytes = QByteArray((char*)data);
           QString cmdString = QString(bytes);
           onDiscovery("",cmdString.right(cmdString.size()-14),cmdString.mid(2,12));
       }
     return;
   }
   if(data[0]=='S'&& data[1]=='H'){
     onDiscoveryDone();
     return;
   }
   if(data[0]=='D'&& data[1]=='B'){
       if(len<14){
          qDebug()<<"DB error here!!"<<endl;
       }else{
          QByteArray bytes = QByteArray((char*)data);
          QString cmdString = QString(bytes);
          onLocalAddress(cmdString.right(cmdString.size()-2));
       }
     return;
   }
   if(data[0]=='I'&& data[1]=='R'){
       if(len<=2){
          onOutGoingOrTalkingNumber("");
       }else{
          QByteArray bytes = QByteArray((char*)data);
          QString cmdString = QString(bytes);
          onOutGoingOrTalkingNumber(cmdString.right(cmdString.size()-2));
       }
     return;
   }
   if(data[0]=='M'&& data[1]=='I'){
       if(len<3){
          qDebug()<<"MI error here!!"<<endl;
       }
       else{
           QByteArray bytes = QByteArray((char*)data);
           QString cmdString = QString(bytes);
           QStringList myList= cmdString.right(cmdString.size()-2).split(QString("[FF]"));
           if(myList.size() == 5){
             onMusicInfo(myList.at(0), myList.at(1),"none",myList.at(2).toInt(),myList.at(3).toInt(),myList.at(4).toInt());
           }else if(myList.size() == 6){
             onMusicInfo(myList.at(0), myList.at(1),myList.at(2),myList.at(3).toInt(),myList.at(4).toInt(),myList.at(5).toInt());
           }else{
              qDebug()<<"MI error here 22 !!"<<endl;
           }
       }
     return;
   }
   if(data[0]=='M'&& data[1]=='P'){
       if(len<10){
          qDebug()<<"MP error here!!"<<endl;
       }else{
          int cur_id = (data[2]-'0')*16*16*16+(data[3]-'0')*16*16+(data[4]-'0')*16+(data[5]-'0');
          int total_num = (data[6]-'0')*16*16*16+(data[7]-'0')*16*16+(data[8]-'0')*16+(data[9]-'0');
          onMusicPos(cur_id,total_num);
       }
     return;
   }
}


//-------------------
//----------the next is the callback function
void BluetoothManagerGoc::onHfpDisconnected(){
  emit callOnHfpDisconnected();
}
void BluetoothManagerGoc::onHfpConnected(){
  emit callOnHfpConnected();
}
void BluetoothManagerGoc::onCallSucceed(QString number){
  emit callOnCallSucceed(number);
}
void BluetoothManagerGoc::onIncoming(QString number){
  emit callOnIncoming(number);
}
void BluetoothManagerGoc::onHangUp(){
  emit callOnHangUp();
}
void BluetoothManagerGoc::onTalking(QString number){
  emit callOnTalking(number);
}
void BluetoothManagerGoc::onRingStart(){
  emit callOnRingStart();
}
void BluetoothManagerGoc::onRingStop(){
  emit callOnRingStop();
}
void BluetoothManagerGoc::onHfpLocal(){
  emit callOnHfpLocal();
}
void BluetoothManagerGoc::onHfpRemote(){
  emit callOnHfpRemote();
}
void BluetoothManagerGoc::onInPairMode(){
  emit callOnInPairMode();
}
void BluetoothManagerGoc::onExitPairMode(){
  emit callOnExitPairMode();
}
void BluetoothManagerGoc::onInitSucceed(){
  emit callOnInitSucceed();
}
void BluetoothManagerGoc::onMusicPlaying(){
  emit callOnMusicPlaying();
}
void BluetoothManagerGoc::onMusicStopped(){
  emit callOnMusicStopped();
}
void BluetoothManagerGoc::onVoiceConnected(){
  emit callOnVoiceConnected();
}
void BluetoothManagerGoc::onVoiceDisconnected(){
  emit callOnVoiceDisconnected();
}
void BluetoothManagerGoc::onAutoConnectAnswer(QString autoStatus){
  emit callOnAutoConnectAnswer(autoStatus);
}
void BluetoothManagerGoc::onCurrentAddr(QString addr){
  emit callOnCurrentAddr(addr);
}
void BluetoothManagerGoc::onCurrentName(QString name){
  emit callOnCurrentName(name);
}

void BluetoothManagerGoc::onHfpStatus(int status){
  emit callOnHfpStatus(status);
}
void BluetoothManagerGoc::onAvStatus(int status){
  emit callOnAvStatus(status);
}
void BluetoothManagerGoc::onVersionDate(QString version){
  emit callOnVersionDate(version);
}
void BluetoothManagerGoc::onCurrentDeviceName(QString name){
  emit callOnCurrentDeviceName(name);
}
void BluetoothManagerGoc::onCurrentPinCode(QString code){
  emit callOnCurrentPinCode(code);
}
void BluetoothManagerGoc::onA2dpConnected(){
  emit callOnA2dpConnected();
}
void BluetoothManagerGoc::onCurrentPairList(int index,QString name,QString addr){
  emit callOnCurrentPairList(index,name,addr);
}
void BluetoothManagerGoc::onA2dpDisconnected(){
  emit callOnA2dpDisconnected();
}
void BluetoothManagerGoc::onPhoneBook(QString name,QString number){
  emit callOnPhoneBook(name,number);
}

void BluetoothManagerGoc::onPhoneBookDone(){
  emit callOnPhoneBookDone();
}

void BluetoothManagerGoc::onCalllogDone(){
  emit callOnCalllogDone();
}
void BluetoothManagerGoc::onCalllog(int type,QString name,QString number){
  emit callOnCalllog(type,name,number);
}
void BluetoothManagerGoc::onDiscovery(QString type,QString name,QString addr){
  emit callOnDiscovery(type,name,addr);
}
void BluetoothManagerGoc::onDiscoveryDone(){
  emit callOnDiscoveryDone();
}
void BluetoothManagerGoc::onLocalAddress(QString addr){
  emit callOnLocalAddress(addr);
}
void BluetoothManagerGoc::onMusicInfo(QString music, QString artist,QString album,int duration,int pos,int total){
  emit callOnMusicInfo(music, artist,album,duration,pos,total);
}
void BluetoothManagerGoc::onMusicPos(int current,int total){
  emit callOnMusicPos(current,total);
}
void BluetoothManagerGoc::onOutGoingOrTalkingNumber(QString number){
  emit callOnOutGoingOrTalkingNumber(number);
}
void BluetoothManagerGoc::onConnecting(){
  emit callOnConnecting();
}

void BluetoothManagerGoc::onPairedState(int state){
  emit callOnPairedState(state);
}

void BluetoothManagerGoc::onMicState(int state){
    emit callOnMicState(state);
}

//---------------------
