#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "configuration.h"


class SerialPort
{
public:
    SerialPort();
    static int Open(int port,char* prefix=NULL);
    static int Setup(int fd,int baudrate,int nbits,char parary,int stopbits);
    static int ReadData(int fd,unsigned char *data_buff,int len,int rcv_wait);
    static int WriteData(int fd,unsigned char *data_buff,int s_num);
    static int Close(int fd);
private:
    const static int speed_arr[];
    const static int name_arr[];

};

#endif // SERIALPORT_H
