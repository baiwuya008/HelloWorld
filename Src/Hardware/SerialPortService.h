#ifndef SERIALPORTSERVICE_H
#define SERIALPORTSERVICE_H

#include <QObject>
#include <QThread>
#include <QList>
#include "SerialPort.h"


struct O_MSG {
    unsigned char cmd_id;
    unsigned char *params;
    unsigned char lens;
    unsigned char check_sum;
};



class SerialPortServicePrivate;
class SerialPortService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SerialPortService)
public:
    enum TYPE{
        NONE=0,
        MCU_NORMAL_SERIALPORT,
        BT_GOC_VIRTUAR_SERIALPORT,

    };

    explicit SerialPortService(int port,SerialPortService::TYPE type,QObject *parent = 0);
    ~SerialPortService();




    void sendMsg(unsigned char cmd_id,unsigned char *data,unsigned char len); //data lenth must less then 128 bytes

    void setupDevice(int baudrate,int nbits,char parary,int stopbits);

    SerialPortService::TYPE getSerialPortType();

    void setCmdSyncHeader(unsigned char syncHeader[],unsigned char len);
    int getCmdSyncHeader(unsigned char syncHeader[]);

    int getDeviceFd();
    QList<O_MSG> & getRspMsgs();

    void startAllThread();
    void stopAllThread();

signals:
    void rspMsg(unsigned char cmd_id,unsigned char *data,unsigned char len);
public slots:

private:
    Q_DECLARE_PRIVATE(SerialPortService)
    SerialPortServicePrivate* const d_ptr;
    int const PORT;




};


//----------------发送数据线程
class ReqDispatchingThreadPrivate;
class ReqDispatchingThread : public QThread
{
    Q_OBJECT
    Q_DISABLE_COPY(ReqDispatchingThread)
public:
    explicit ReqDispatchingThread(QObject *parent = 0);
    void safeExit();
    void sendMsg(struct O_MSG msg);
protected:
    void run();

signals:

public slots:

private:
    Q_DECLARE_PRIVATE(ReqDispatchingThread)
    ReqDispatchingThreadPrivate * const d_ptr;
    QObject * const mParent;

};

//----------------读取数据线程
class RspPackagingThreadPrivate;
class RspPackagingThread : public QThread
{
    Q_OBJECT
    Q_DISABLE_COPY(RspPackagingThread)
public:
    explicit RspPackagingThread(QObject *parent = 0);
    void safeExit();
    QList<O_MSG> & getMsgs();
protected:
    void run();

signals:

public slots:

private:
    Q_DECLARE_PRIVATE(RspPackagingThread)
    RspPackagingThreadPrivate * const d_ptr;
    QObject * const mParent;

};

//----------------分发读取数据线程
class RspDispatchingThreadPrivate;
class RspDispatchingThread : public QThread
{
    Q_OBJECT
    Q_DISABLE_COPY(RspDispatchingThread)
public:
    explicit RspDispatchingThread(QObject *parent = 0);
    void safeExit();
protected:
    void run();

signals:

public slots:

private:
    Q_DECLARE_PRIVATE(RspDispatchingThread)
    RspDispatchingThreadPrivate * const d_ptr;
    QObject * const mParent;


};





#endif // SERIALPORTSERVICE_H
