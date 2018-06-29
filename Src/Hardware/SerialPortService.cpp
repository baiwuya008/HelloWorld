#include "SerialPortService.h"
#include <QDebug>

//-----------
#define READ_DATA_BUFFER_SIZE  4096
#define SEND_DATA_BUFFER_SIZE  128
//-------------------

class SerialPortServicePrivate
{
    Q_DISABLE_COPY(SerialPortServicePrivate)
public:
    explicit SerialPortServicePrivate(SerialPortService *parent);
    ~SerialPortServicePrivate();
    //---------
    int mSerialDevice;

private:
    void initDevice();
    void deInitDevice();
private:
    Q_DECLARE_PUBLIC(SerialPortService)
    SerialPortService * const q_ptr;

    //---------
    ReqDispatchingThread *mReqDispatchingThread;
    RspPackagingThread   *mRspPackagingThread;
    RspDispatchingThread *mRspDispatchingThread;
    //---------
    unsigned char syncHeader[5];
    int syncHeaderLen;
    SerialPortService::TYPE mSerialType;

};

SerialPortServicePrivate::SerialPortServicePrivate(SerialPortService *parent)
    :q_ptr(parent)
{
    mReqDispatchingThread = NULL;
    mRspPackagingThread = NULL;
    mRspDispatchingThread = NULL;
    mSerialDevice = -1;
    memset(syncHeader,0,sizeof(syncHeader));
    syncHeaderLen = 0;
    mSerialType = SerialPortService::NONE;


}

SerialPortServicePrivate::~SerialPortServicePrivate()
{
   deInitDevice();
}

void SerialPortServicePrivate::initDevice()
{
    qDebug()<<"SerialPortServicePrivate::initDevice"<<endl;
    Q_Q(SerialPortService);
    if(mSerialType = SerialPortService::BT_GOC_VIRTUAR_SERIALPORT){
        //mSerialDevice = SerialPort::Open(q->PORT,"/dev/goc_serial");
        mSerialDevice = SerialPort::Open(q->PORT,"/dev/ttyUSB");
    }else{
        mSerialDevice = SerialPort::Open(q->PORT);
    }

    qDebug()<<"SerialPortServicePrivate::initDevice mSerialDevice:"<<mSerialDevice<<endl;
}

void SerialPortServicePrivate::deInitDevice()
{
    qDebug()<<"SerialPortServicePrivate::deInitDevice"<<endl;
    SerialPort::Close(mSerialDevice);
    mSerialDevice = -1;
}

//----------------------
SerialPortService::SerialPortService(int port,SerialPortService::TYPE type,QObject *parent) :
    QObject(parent),
    PORT(port),
    d_ptr(new SerialPortServicePrivate(this))
{
   d_ptr->mSerialType =type;
   d_ptr->initDevice();
}

SerialPortService::~SerialPortService()
{
stopAllThread();
}

void SerialPortService::startAllThread()
{
 qDebug()<<"SerialPortService::startAllThread"<<endl;
 Q_D(SerialPortService);
 if(d->mReqDispatchingThread == NULL){
    d->mReqDispatchingThread = new ReqDispatchingThread(this);
 }
 if(d->mRspPackagingThread == NULL){
    d->mRspPackagingThread = new RspPackagingThread(this);
 }
 if(d->mRspDispatchingThread == NULL){
    d->mRspDispatchingThread = new RspDispatchingThread(this);
 }
   d->mReqDispatchingThread->start();
   d->mRspPackagingThread->start();
   d->mRspDispatchingThread->start();
}

void SerialPortService::stopAllThread()
{
qDebug()<<"SerialPortService::stopAllThread"<<endl;
Q_D(SerialPortService);
  if(d->mReqDispatchingThread == NULL){
    d->mReqDispatchingThread->safeExit();
    d->mReqDispatchingThread->wait(100);
  }
  if(d->mRspPackagingThread == NULL){
    d->mRspPackagingThread->safeExit();
    d->mRspPackagingThread->wait(100);
  }
  if(d->mRspDispatchingThread == NULL){
    d->mRspDispatchingThread->safeExit();
    d->mRspDispatchingThread->wait(100);
  }
}

void SerialPortService::setupDevice(int baudrate,int nbits,char parary,int stopbits)
{
    qDebug()<<"SerialPortService::setupDevice"<<endl;
    Q_D(SerialPortService);
    if(d->mSerialDevice == -1)
    {
      qDebug()<<"mSerialDevice == -1 , serial port open fail or have not open"<<endl;
    }else{
      SerialPort::Setup(d->mSerialDevice,baudrate,nbits,parary,stopbits);
    }
}


void SerialPortService::sendMsg(unsigned char cmd_id,unsigned char *data,unsigned char len)
{
    qDebug()<<"SerialPortService::sendMsg"<<endl;
    Q_D(SerialPortService);
    struct O_MSG my_msg;
    my_msg.cmd_id = cmd_id;
    my_msg.params = (unsigned char *)(new char[len]);
    my_msg.lens = len;
    memcpy(my_msg.params,data,len);
    unsigned char check_sum_tmp=0;
    for (int i = 0; i < len; ++i) {
        check_sum_tmp = check_sum_tmp+data[i];
    }
    check_sum_tmp = check_sum_tmp+len;
    my_msg.check_sum = 0xFF-check_sum_tmp;
    d->mReqDispatchingThread->sendMsg(my_msg);
}

int SerialPortService::getDeviceFd()
{
    Q_D(SerialPortService);
    return d->mSerialDevice;
}

QList<O_MSG> & SerialPortService::getRspMsgs()
{
    Q_D(SerialPortService);
    if(d->mRspPackagingThread != NULL){
        return d->mRspPackagingThread->getMsgs();
    }else{
        QList<O_MSG> null_msgs;
        return null_msgs;
    }
}

void SerialPortService::setCmdSyncHeader(unsigned char syncHeader[],unsigned char len)
{
  Q_D(SerialPortService);
  memcpy(d->syncHeader,syncHeader,len);
  d->syncHeaderLen = len;
}

int SerialPortService::getCmdSyncHeader(unsigned char syncHeader[])
{
  Q_D(SerialPortService);
  memcpy(syncHeader,d->syncHeader,d->syncHeaderLen);
  return d->syncHeaderLen;
}

SerialPortService::TYPE SerialPortService::getSerialPortType()
{
    Q_D(SerialPortService);
    return d->mSerialType;
}

//----------------------

//-------------------发送数据线程
class ReqDispatchingThreadPrivate
{
    Q_DISABLE_COPY(ReqDispatchingThreadPrivate)
public:
    explicit ReqDispatchingThreadPrivate(ReqDispatchingThread *parent);
private:
    Q_DECLARE_PUBLIC(ReqDispatchingThread)
    void sendCmdUnitLoop();
    //-------
    bool mExit;
    ReqDispatchingThread * const q_ptr;
    QList<O_MSG> mSendCmds;


};

ReqDispatchingThreadPrivate::ReqDispatchingThreadPrivate(ReqDispatchingThread *parent)
    :q_ptr(parent)
{
 mSendCmds.clear();
}

void ReqDispatchingThreadPrivate::sendCmdUnitLoop()
{
   if(mSendCmds.size()>0){
      Q_Q(ReqDispatchingThread);
      int deviceFd = (static_cast<SerialPortService *>(q->mParent))->getDeviceFd();
      SerialPortService::TYPE serialType = (static_cast<SerialPortService *>(q->mParent))->getSerialPortType();
      unsigned char syncHeader[5]={0};
      int syncHeaderLen = (static_cast<SerialPortService *>(q->mParent))->getCmdSyncHeader(syncHeader);
      if(deviceFd > 0){
          O_MSG msg = mSendCmds.takeFirst();
          unsigned char send_data[SEND_DATA_BUFFER_SIZE]={0};
          switch (serialType) {
          case SerialPortService::MCU_NORMAL_SERIALPORT:
              {
              if(syncHeaderLen>0){
                  memcpy(send_data,syncHeader,syncHeaderLen);
              }
              send_data[syncHeaderLen]=msg.lens;
              memcpy(send_data+syncHeaderLen+1,msg.params,msg.lens);
              send_data[syncHeaderLen+msg.lens+1] = msg.check_sum;
              SerialPort::WriteData(deviceFd,send_data,syncHeaderLen+msg.lens+2);
              }
              break;
          case SerialPortService::BT_GOC_VIRTUAR_SERIALPORT:
              {
              //add AT# prefix
              send_data[0]='A';
              send_data[1]='T';
              send_data[2]='#';

              memcpy(send_data+3,msg.params,msg.lens);
              //add \r \n in the tail
              send_data[msg.lens+3] = '\r';
              send_data[msg.lens+3+1] = '\n';

              SerialPort::WriteData(deviceFd,send_data,msg.lens+5);
              }
              break;
          default:
              break;
          }

      }
   }
}

//----------------------
ReqDispatchingThread::ReqDispatchingThread(QObject *parent) :
    QThread(parent),
    mParent(parent),
    d_ptr(new ReqDispatchingThreadPrivate(this))
{

}

void ReqDispatchingThread::run()
{
    qDebug()<<"ReqDispatchingThread::run"<<endl;
    Q_D(ReqDispatchingThread);
    //setPriority(QThread::HighestPriority);
    d->mExit = false;
    while (true) {
        if(d->mExit) break;
        //----------Do something here
        d->sendCmdUnitLoop();
        //----------
        msleep(10);
    }
    qDebug()<<"ReqDispatchingThread::run->exit"<<endl;
}

void ReqDispatchingThread::safeExit()
{
    qDebug()<<"ReqDispatchingThread::safeExit"<<endl;
    Q_D(ReqDispatchingThread);
    d->mExit = true;
}

void ReqDispatchingThread::sendMsg(struct O_MSG msg)
{
  Q_D(ReqDispatchingThread);
  d->mSendCmds.append(msg);
}

//----------------------

//-------------------读取数据线程
class RspPackagingThreadPrivate
{
    Q_DISABLE_COPY(RspPackagingThreadPrivate)
public:
    explicit RspPackagingThreadPrivate(RspPackagingThread *parent);
private:
    Q_DECLARE_PUBLIC(RspPackagingThread)
    RspPackagingThread * const q_ptr;
    //------
    bool mExit;
    QList<O_MSG> mReadCmds;

    unsigned char mReadDataBuf[READ_DATA_BUFFER_SIZE];
    unsigned char mMsgUnHandledData[READ_DATA_BUFFER_SIZE*2];
    int mUnHandledDataLen;

    //--------
    //functions
    O_MSG getResponseMsg();
    int readData();
    O_MSG readData2Msg();
    O_MSG readDataFromBtGoc2Msg();

};

RspPackagingThreadPrivate::RspPackagingThreadPrivate(RspPackagingThread *parent)
    :q_ptr(parent)
{
   memset(&mReadDataBuf,0,sizeof(mReadDataBuf));
   memset(&mMsgUnHandledData,0,sizeof(mMsgUnHandledData));
   mUnHandledDataLen = 0;
}

O_MSG RspPackagingThreadPrivate::getResponseMsg()
{
   O_MSG msg;
   memset(&msg,0,sizeof(msg));
   Q_Q(RspPackagingThread);
   int deviceFd =static_cast<SerialPortService *>(q->mParent)->getDeviceFd();
   SerialPortService::TYPE serialType = (static_cast<SerialPortService *>(q->mParent))->getSerialPortType();

   if(deviceFd>0){
       //parse the rev data here !!
       while (true) {
           switch (serialType) {
           case SerialPortService::MCU_NORMAL_SERIALPORT:
              {
               msg = readData2Msg();
              }
               break;
           case SerialPortService::BT_GOC_VIRTUAR_SERIALPORT:
              {
               msg = readDataFromBtGoc2Msg();
              }
               break;
           default:
               break;
           }

           if(msg.cmd_id == 0){
               continue;
           }else{
               break;
           }
       }
       //--------------------------
   }

   return msg;
}

int RspPackagingThreadPrivate::readData()
{
    int read_n = 0;
    Q_Q(RspPackagingThread);
    int deviceFd = (static_cast<SerialPortService *>(q->mParent))->getDeviceFd();
    while (true) {
        read_n = SerialPort::ReadData(deviceFd,mReadDataBuf,READ_DATA_BUFFER_SIZE-2,100);
        if(read_n >0){
           break;
        }else{
            continue;
        }
    }
    return read_n;
}

O_MSG RspPackagingThreadPrivate::readData2Msg()
{
    Q_Q(RspPackagingThread);
    int msgLen = 0;
    int dataReadLen;
    O_MSG msg,null_msg;
    memset(&msg,0,sizeof(msg));
    memset(&null_msg,0,sizeof(null_msg));

    unsigned char syncHeader[5]={0};
    int syncHeaderLen = (static_cast<SerialPortService *>(q->mParent))->getCmdSyncHeader(syncHeader);

    if (mUnHandledDataLen == 0) {
           //qDebug()<<"[readData2Msg] mUnHandledDataLen == 0."<<endl;
           dataReadLen = readData();
           if (dataReadLen <= 0) {
                  return null_msg;
            }

            if ((dataReadLen < syncHeaderLen+1)) {
                        //qDebug()<<QString("[readData2Msg] syncHeaderLen+1 > dataRead.length.  dataRead.length: %1").arg(dataReadLen)<<endl;
                        mUnHandledDataLen = dataReadLen;
                        memcpy(mMsgUnHandledData, mReadDataBuf, mUnHandledDataLen);
                        //return null_msg;
                        return readData2Msg();
                    }

            if(syncHeaderLen ==2){
                  if (mReadDataBuf[0] == syncHeader[0] && mReadDataBuf[1] == syncHeader[1]) {
                            msgLen = (mReadDataBuf[2]>=0?mReadDataBuf[2]:(mReadDataBuf[2]+256)) + syncHeaderLen+1; //add sync and len size
                        } else {
                            //qDebug()<<"[readData2Msg] read  data  format error"<<endl;
                            //System.arraycopy(mReadDataBuf,1,mMsgUnHandledData,0, dataReadLen-1);
                            memcpy(mMsgUnHandledData, mReadDataBuf+1, dataReadLen-1);
                            mUnHandledDataLen = dataReadLen-1;
                            return null_msg;
                        }
                        if(msgLen == (syncHeaderLen+1)){
                            qDebug()<<"[readData2Msg] mMsgUnHandledData  data  error:msgLen == (syncHeaderLen+1)"<<endl;
                            mUnHandledDataLen = 0;
                            return null_msg;
                        }
                  }else if(syncHeaderLen ==3){
                        if (mReadDataBuf[0] == syncHeader[0]&& mReadDataBuf[1] == syncHeader[1]&& mReadDataBuf[2] == syncHeader[2]) {
                            msgLen = (mReadDataBuf[3]>=0?mReadDataBuf[3]:(mReadDataBuf[3]+256)) + syncHeaderLen+1; //add sync and len size
                        } else {
                            //qDebug()<<"[readData2Msg] read  data  format error"<<endl;
                            //System.arraycopy(mReadDataBuf,1,mMsgUnHandledData,0, dataReadLen-1);
                            memcpy(mMsgUnHandledData, mReadDataBuf+1, dataReadLen-1);
                            mUnHandledDataLen = dataReadLen-1;
                            return null_msg;
                        }
                        if(msgLen == (syncHeaderLen+1)){
                            qDebug()<<"[readData2Msg] mMsgUnHandledData  data  error:msgLen == (syncHeaderLen+1)"<<endl;
                            mUnHandledDataLen = 0;
                            return null_msg;
                        }
             }


             if (msgLen == dataReadLen) {
                        //qDebug()<<"[readData2Msg] (msgLen + 3) == dataRead.length."<<endl;
                        mUnHandledDataLen = 0;
                        //byte[] msgData = new byte[msgLen];
                        //System.arraycopy(mReadDataBuf, 0, msgData, 0,msgLen);
                        //return msgData;
                        msg.cmd_id = 1;
                        unsigned char *params= (unsigned char *)(new char[msgLen-syncHeaderLen-2+1]);
                        memset(params,0,msgLen-syncHeaderLen-2+1);
                        msg.params =params;
                        memcpy(msg.params,mReadDataBuf+syncHeaderLen+1,msgLen-syncHeaderLen-2);
                        msg.lens = msgLen-syncHeaderLen-2;
                        msg.check_sum = mReadDataBuf[msgLen-1];
                        return msg;
              } else if ((msgLen > dataReadLen)) {
                        //qDebug()<<"[readData2Msg] msgLen > dataRead.length."<<endl;
                        mUnHandledDataLen = dataReadLen;
                        //System.arraycopy(mReadDataBuf, 0, mMsgUnHandledData, 0, mUnHandledDataLen);
                        memcpy(mMsgUnHandledData,mReadDataBuf,mUnHandledDataLen);
                        return null_msg;
              } else if ((msgLen < dataReadLen)) {
                        //qDebug()<<QString("[readData2Msg] msgLen < dataRead.length: %1").arg(dataReadLen)<<endl;
                        mUnHandledDataLen = dataReadLen - msgLen;
                        //System.arraycopy(mReadDataBuf, msgLen, mMsgUnHandledData,0, mUnHandledDataLen);
                        memcpy(mMsgUnHandledData,mReadDataBuf+msgLen,mUnHandledDataLen);

                        //byte[] msgData = new byte[msgLen];
                        //System.arraycopy(mReadDataBuf, 0, msgData, 0,msgLen);
                        //return msgData;
                        msg.cmd_id = 1;
                        unsigned char *params= (unsigned char *)(new char[msgLen-syncHeaderLen-2+1]);
                        memset(params,0,msgLen-syncHeaderLen-2+1);
                        msg.params =params;
                        memcpy(msg.params,mReadDataBuf+syncHeaderLen+1,msgLen-syncHeaderLen-2);
                        msg.lens = msgLen-syncHeaderLen-2;
                        msg.check_sum = mReadDataBuf[msgLen-1];
                        return msg;
              }

    } else {
              //qDebug()<<"mUnHandledDataLen != 0."<<endl;
             if(mUnHandledDataLen < syncHeaderLen+1 ){
                  //qDebug()<<QString("[readData2Msg] mUnHandledDataLen < 3,mUnHandledDataLen: %1").arg(mUnHandledDataLen)<<endl;
                        dataReadLen = readData();
                        if (dataReadLen <=0) {
                            return null_msg;
                        }
                        //System.arraycopy(mReadDataBuf, 0, mMsgUnHandledData,mUnHandledDataLen, dataReadLen);
                        memcpy(mMsgUnHandledData+mUnHandledDataLen, mReadDataBuf, dataReadLen);
                        mUnHandledDataLen += dataReadLen;
              }

             if(syncHeaderLen ==2){
                        if (mMsgUnHandledData[0] == syncHeader[0] && mMsgUnHandledData[1] == syncHeader[1]) {
                            msgLen = (mMsgUnHandledData[2]>=0?mMsgUnHandledData[2]:(mMsgUnHandledData[2]+256)) + syncHeaderLen+1; //add sync and len size
                        } else {
                            //qDebug()<<"[readData2Msg] read  data  format error"<<endl;
                            memcpy(mMsgUnHandledData, mMsgUnHandledData+1, mUnHandledDataLen-1);
                            mUnHandledDataLen --;
                            return null_msg;
                        }

             }else if(syncHeaderLen ==3){
                        if (mMsgUnHandledData[0] == syncHeader[0]&& mMsgUnHandledData[1] == syncHeader[1]&& mMsgUnHandledData[2] == syncHeader[2]) {
                            msgLen = (mMsgUnHandledData[3]>=0?mMsgUnHandledData[3]:(mMsgUnHandledData[3]+256)) + syncHeaderLen+1; //add sync and len size
                        } else {
                            //qDebug()<<"[readData2Msg] read  data  format error"<<endl;
                            memcpy(mMsgUnHandledData, mMsgUnHandledData+1, mUnHandledDataLen-1);
                            mUnHandledDataLen --;
                            return null_msg;
                        }

             }


             if(msgLen == (syncHeaderLen+1)){
                        qDebug()<<"[readData2Msg] mMsgUnHandledData  data  error:msgLen == (syncHeaderLen+1)"<<endl;
                        mUnHandledDataLen = 0;
                        return null_msg;
             }

             if (msgLen == mUnHandledDataLen) {
                        //qDebug()<<"[readData2Msg] msgLen == mUnHandledDataLen."<<endl;
                        mUnHandledDataLen = 0;
                        //byte[] msgData = new byte[msgLen];
                        //System.arraycopy(mMsgUnHandledData, 0, msgData, 0,msgLen);
                        //return msgData;
                        msg.cmd_id = 1;
                        unsigned char *params= (unsigned char *)(new char[msgLen-syncHeaderLen-2+1]);
                        memset(params,0,msgLen-syncHeaderLen-2+1);

                        msg.params =params;
                        memcpy(msg.params,mMsgUnHandledData+syncHeaderLen+1,msgLen-syncHeaderLen-2);
                        msg.lens = msgLen-syncHeaderLen-2;
                        msg.check_sum = mMsgUnHandledData[msgLen-1];
                        return msg;

            } else if ((msgLen > mUnHandledDataLen)) {
                        //qDebug()<<QString("[readData2Msg] msgLen > mUnHandledDataLen. msgLen: %1").arg(msgLen)<<endl;
                        dataReadLen = readData();
                        if (dataReadLen <=0) {
                            return null_msg;
                        }
                        //System.arraycopy(mReadDataBuf, 0, mMsgUnHandledData,mUnHandledDataLen, dataReadLen);
                        memcpy(mMsgUnHandledData+mUnHandledDataLen,mReadDataBuf,dataReadLen);
                        mUnHandledDataLen += dataReadLen;
                        return null_msg;
            } else if ((msgLen < mUnHandledDataLen)) {
                        //qDebug()<<QString("[readData2Msg] msgLen < mUnHandledDataLen. msgLen: %1").arg(msgLen)<<endl;
                        mUnHandledDataLen -= msgLen;
                        msg.cmd_id = 1;
                        unsigned char *params= (unsigned char *)(new char[msgLen-syncHeaderLen-2+1]);
                        memset(params,0,msgLen-syncHeaderLen-2+1);
                        msg.params =params;
                        memcpy(msg.params,mMsgUnHandledData+syncHeaderLen+1,msgLen-syncHeaderLen-2);
                        msg.lens = msgLen-syncHeaderLen-2;
                        msg.check_sum = mMsgUnHandledData[msgLen-1];

                        memcpy(mMsgUnHandledData, mMsgUnHandledData+msgLen, mUnHandledDataLen);

                        return msg;

            }
      }
}


O_MSG RspPackagingThreadPrivate::readDataFromBtGoc2Msg()
{
    Q_Q(RspPackagingThread);
    int msgLen = 0;
    int dataReadLen;
    O_MSG msg,null_msg;
    memset(&msg,0,sizeof(msg));
    memset(&null_msg,0,sizeof(null_msg));

    if (mUnHandledDataLen == 0) {
           //qDebug()<<"[readDataFromBtGoc2Msg] mUnHandledDataLen == 0."<<endl;
           dataReadLen = readData();
           if (dataReadLen <= 0) {
                  return null_msg;
            }

            if ((dataReadLen < 3)) {
                        //qDebug()<<QString("[readDataFromBtGoc2Msg] syncHeaderLen+1 > dataRead.length.  dataRead.length: %1").arg(dataReadLen)<<endl;
                        mUnHandledDataLen = dataReadLen;
                        memcpy(mMsgUnHandledData, mReadDataBuf, mUnHandledDataLen);
                        return null_msg;
                        //return readDataFromBtGoc2Msg();
                    }

              //find \r,\n code in the readData
              int suffix_idx = -1;
              for (int i = 0; i < dataReadLen; ++i) {
                  if(mReadDataBuf[i]=='\r' && mReadDataBuf[i+1] == '\n'){
                     suffix_idx = i;
                     break;
                  }
              }

              if(suffix_idx == -1){
                  mUnHandledDataLen = dataReadLen;
                  memcpy(mMsgUnHandledData, mReadDataBuf, mUnHandledDataLen);
                  return null_msg;
              }

             msgLen = suffix_idx+2; //add \r \n code

             if (msgLen == dataReadLen) {
                        //qDebug()<<"[readDataFromBtGoc2Msg] (msgLen + 3) == dataRead.length."<<endl;
                        mUnHandledDataLen = 0;
                        msg.cmd_id = 1;
                        unsigned char *params= (unsigned char *)(new char[msgLen-2+1]);
                        memset(params,0,msgLen-2+1);
                        memcpy(params,mReadDataBuf,msgLen-2);
                        msg.params =params;
                        msg.lens = msgLen-2;
                        params = NULL;
//                        qDebug()<<"copy 1"<<endl;
//                        for (int var = 0; var < msg.lens; ++var) {
//                            qDebug()<<"data["<<var<<"]="<<msg.params[var]<<endl;
//                        }
                        return msg;
              } else if ((msgLen < dataReadLen)) {
                        //qDebug()<<QString("[readDataFromBtGoc2Msg] msgLen < dataRead.length: %1").arg(dataReadLen)<<endl;
                        mUnHandledDataLen = dataReadLen - msgLen;
                        memcpy(mMsgUnHandledData,mReadDataBuf+msgLen,mUnHandledDataLen);
                        msg.cmd_id = 1;
                        unsigned char *params= (unsigned char *)(new char[msgLen-2+1]);
                        memset(params,0,msgLen-2+1);
                        memcpy(params,mReadDataBuf,msgLen-2);
                        msg.params =params;
                        msg.lens = msgLen-2;
                        params = NULL;
//                        qDebug()<<"copy 2"<<endl;
//                        for (int var = 0; var < msg.lens; ++var) {
//                            qDebug()<<"data["<<var<<"]="<<msg.params[var]<<endl;
//                        }
                        return msg;
              }

    } else {
              //qDebug()<<"mUnHandledDataLen != 0."<<endl;
             if(mUnHandledDataLen < 3 ){
                  //qDebug()<<QString("[readDataFromBtGoc2Msg] mUnHandledDataLen < 3,mUnHandledDataLen: %1").arg(mUnHandledDataLen)<<endl;
                        dataReadLen = readData();
                        if (dataReadLen <=0) {
                            return null_msg;
                        }
                        memcpy(mMsgUnHandledData+mUnHandledDataLen, mReadDataBuf, dataReadLen);
                        mUnHandledDataLen += dataReadLen;
              }

             //find \r,\n code in the readData
             int suffix_idx = -1;
             for (int i = 0; i < mUnHandledDataLen; ++i) {
                 if(mMsgUnHandledData[i]=='\r' && mMsgUnHandledData[i+1] == '\n'){
                    suffix_idx = i;
                    break;
                 }
             }

             if(suffix_idx == -1){
                 dataReadLen = readData();
                 if (dataReadLen <=0) {
                     return null_msg;
                 }
                 memcpy(mMsgUnHandledData+mUnHandledDataLen, mReadDataBuf, dataReadLen);
                 mUnHandledDataLen += dataReadLen;
                 //check again here!!
                 for (int i = 0; i < mUnHandledDataLen; ++i) {
                     if(mMsgUnHandledData[i]=='\r' && mMsgUnHandledData[i+1] == '\n'){
                        suffix_idx = i;
                        break;
                     }
                 }
                 //------------------
             }

             if(suffix_idx == -1)
             {
                 return null_msg;
             }

             msgLen = suffix_idx+2; //add \r \n code

             if (msgLen == mUnHandledDataLen) {
                        //qDebug()<<"[readDataFromBtGoc2Msg] msgLen == mUnHandledDataLen."<<endl;
                        mUnHandledDataLen = 0;
                        msg.cmd_id = 1;
                        unsigned char *params= (unsigned char *)(new char[msgLen-2+1]);
                        memset(params,0,msgLen-2+1);
                        memcpy(params,mMsgUnHandledData,msgLen-2);
                        msg.params =params;
                        msg.lens = msgLen-2;
                        params = NULL;

                        memset(mMsgUnHandledData,0,READ_DATA_BUFFER_SIZE*2);
//                        qDebug()<<"copy 3"<<endl;
//                        for (int var = 0; var < msg.lens; ++var) {
//                            qDebug()<<"data["<<var<<"]="<<msg.params[var]<<endl;
//                        }
                        return msg;

            }else if ((msgLen < mUnHandledDataLen)) {
                        //qDebug()<<QString("[readDataFromBtGoc2Msg] msgLen < mUnHandledDataLen. msgLen: %1").arg(msgLen)<<endl;
                        mUnHandledDataLen -= msgLen;

                        msg.cmd_id = 1;
                        unsigned char *params= (unsigned char *)(new char[msgLen-2+1]);
                        memset(params,0,msgLen-2+1);
                        memcpy(params,mMsgUnHandledData,msgLen-2);
                        msg.params =params;
                        msg.lens = msgLen-2;
                        params = NULL;
//                        qDebug()<<"copy 4"<<endl;
//                        for (int var = 0; var < msg.lens; ++var) {
//                            qDebug()<<"data["<<var<<"]="<<msg.params[var]<<endl;
//                        }

                        unsigned char *temp_data= (unsigned char *)(new char[mUnHandledDataLen]);
                        memset(temp_data,0,mUnHandledDataLen);
                        memcpy(temp_data, mMsgUnHandledData+msgLen, mUnHandledDataLen);
                        memset(mMsgUnHandledData,0,READ_DATA_BUFFER_SIZE*2);
                        memcpy(mMsgUnHandledData, temp_data, mUnHandledDataLen);
                        delete temp_data;

                        return msg;

            }
      }

}


//----------------------
RspPackagingThread::RspPackagingThread(QObject *parent) :
    QThread(parent),
    mParent(parent),
    d_ptr(new RspPackagingThreadPrivate(this))
{

}

void RspPackagingThread::run()
{
    qDebug()<<"RspPackagingThread::run"<<endl;
    Q_D(RspPackagingThread);
    //setPriority(QThread::HighestPriority);
    d->mExit = false;
    while (true) {
        if(d->mExit) break;
        //----------Do something here
        O_MSG my_msg = d->getResponseMsg();
        if(my_msg.cmd_id>0)
        {
          d->mReadCmds.append(my_msg);
        }
        //----------
        //msleep(10);
    }
    qDebug()<<"RspPackagingThread::run->exit"<<endl;
}

void RspPackagingThread::safeExit()
{
    qDebug()<<"RspPackagingThread::safeExit"<<endl;
    Q_D(RspPackagingThread);
    d->mExit = true;
}

QList<O_MSG> & RspPackagingThread::getMsgs()
{
    Q_D(RspPackagingThread);
    return d->mReadCmds;
}

//----------------------

//-------------------分发读取数据线程
class RspDispatchingThreadPrivate
{
    Q_DISABLE_COPY(RspDispatchingThreadPrivate)
public:
    explicit RspDispatchingThreadPrivate(RspDispatchingThread *parent);
private:
    Q_DECLARE_PUBLIC(RspDispatchingThread)
    RspDispatchingThread * const q_ptr;
    //----------
    bool mExit;

};
RspDispatchingThreadPrivate::RspDispatchingThreadPrivate(RspDispatchingThread *parent)
    :q_ptr(parent)
{

}

//----------------------
RspDispatchingThread::RspDispatchingThread(QObject *parent) :
    QThread(parent),
    mParent(parent),
    d_ptr(new RspDispatchingThreadPrivate(this))
{

}

void RspDispatchingThread::run()
{
    qDebug()<<"RspDispatchingThread::run"<<endl;
    Q_D(RspDispatchingThread);
    //setPriority(QThread::HighestPriority);
    d->mExit = false;

    QList<O_MSG> & readMsgs = static_cast<SerialPortService *>(mParent)->getRspMsgs();
    while (true) {
        if(d->mExit) break;
        //----------Do something here
        if(readMsgs.size()>0){
           O_MSG msg =readMsgs.takeFirst();
           if(msg.cmd_id>0){
               //valid msg
               emit static_cast<SerialPortService *>(mParent)->rspMsg(msg.cmd_id,msg.params,msg.lens);
           }
        }
        //----------
        msleep(20);
    }
    qDebug()<<"RspDispatchingThread::run->exit"<<endl;
}

void RspDispatchingThread::safeExit()
{
    qDebug()<<"RspDispatchingThread::safeExit"<<endl;
    Q_D(RspDispatchingThread);
    d->mExit = true;
}
//----------------------
