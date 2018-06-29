#include "BluetoothManager.h"



class BluetoothManagerPrivate {

public:
    explicit BluetoothManagerPrivate(BluetoothManager *parent);
    ~BluetoothManagerPrivate();

private:
    Q_DECLARE_PUBLIC(BluetoothManager)
    BluetoothManager* const q_ptr;
    SerialPortService * mSerialPort;

};

BluetoothManagerPrivate::BluetoothManagerPrivate(BluetoothManager *parent)
    :q_ptr(parent)
{
   mSerialPort = NULL;

}

BluetoothManagerPrivate::~BluetoothManagerPrivate()
{

}

//--------------

BluetoothManager::BluetoothManager(QObject *parent) :
    QObject(parent),d_ptr(new BluetoothManagerPrivate(this))
{
}

//data lenth must less then 128 bytes
void BluetoothManager::sendMsg(unsigned char cmd_id,unsigned char *data,unsigned char len)
{
  Q_D(BluetoothManager);
  d->mSerialPort->sendMsg(cmd_id,data,len);
}

void BluetoothManager::openDevice(int port,SerialPortService::TYPE type)
{
  Q_D(BluetoothManager);
  d->mSerialPort = new SerialPortService(port,type);
}

void BluetoothManager::setupDevice(int baudrate,int nbits,char parary,int stopbits)
{
  Q_D(BluetoothManager);
  d->mSerialPort->setupDevice(baudrate,nbits,parary,stopbits);
}


void BluetoothManager::initService()
{
  Q_D(BluetoothManager);
  d->mSerialPort->startAllThread();
  connect(d->mSerialPort,SIGNAL(rspMsg(unsigned char,unsigned char*,unsigned char)),this,SLOT(rspMsg(unsigned char,unsigned char*,unsigned char)));
}

void BluetoothManager::rspMsg(unsigned char cmd_id,unsigned char *data,unsigned char len)
{
  callBackRspMsg(cmd_id,data,len);
}


