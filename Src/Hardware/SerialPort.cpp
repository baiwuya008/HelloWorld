#include "SerialPort.h"
#include "okl_errorno.h"
#include <cstring>
#include <unistd.h>
#include <QThread>

#if(QT_IN_WINDOWS == 0)
  #include <termios.h>
  #include <sys/ioctl.h>

const static int speed_arr[] = {B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1200, B300};
const static int name_arr[]  = {115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300};
#endif

#define    DEBUG_SERIAL_MSG        1
#define    SERIAL_DEVICE_PREFIX    "/dev/ttymxc"

SerialPort::SerialPort()
{
}

int SerialPort::Open(int port,char* prefix){
    char  device_name[512];
    int   slen = 0x00;
    int   serial_fd = 0x00;

    //改变设备文件属性，使其可以有权限进行写入操作
    slen = sizeof(device_name);
//    memset(device_name, 0x00, slen);
//    if(prefix != NULL){
//        if(port == -1){
//           sprintf(device_name, "%s%s", "chmod -R 660 ", prefix);
//        }else{
//           sprintf(device_name, "%s%s%d", "chmod -R 660 ", prefix, port);
//        }

//    }else{
//           sprintf(device_name, "%s%s%d", "chmod -R 660 ", SERIAL_DEVICE_PREFIX, port);

//    }
//    if (system(device_name) == -1)
//        {
//         #if DEBUG_SERIAL_MSG
//             printf("file = %s, function = %s  SerialPort::Open system error1\n", __FILE__, __func__);
//         #endif
//        }
     //构造设备路径字符串，打开设备文件
     memset(device_name, 0x00, slen);
     if(prefix != NULL){
         if(port == -1){
            snprintf(device_name, slen-1, "%s", prefix);
         }else{
            snprintf(device_name, slen-1, "%s%d", prefix, port);
         }

     }else{
        snprintf(device_name, slen-1, "%s%d", SERIAL_DEVICE_PREFIX, port);
     }
#if(QT_IN_WINDOWS == 0)
     serial_fd = open(device_name, O_RDWR | O_NOCTTY | O_NDELAY,  660);
#else
     serial_fd = open(device_name, O_RDWR,  660);
#endif

     if (serial_fd < 0x00)
         {
          #if DEBUG_SERIAL_MSG
             printf("file = %s, function = %s  open uart port error\n", __FILE__, __func__);
          #endif

             serial_fd = OPEN_PORT_ERROR;
             goto RETURN_LABEL;
         }

RETURN_LABEL:
     printf("open serial port success: %s.\n", device_name);
   return serial_fd;
}

int SerialPort::Setup(int fd,int baudrate,int nbits,char parary,int stopbits){

    int  iret = 0x00;
#if(QT_IN_WINDOWS == 0)
    struct termios newtio, oldtio;
    int  speed = 0x00; 
    int  status;

    memset(&newtio, 0x00, sizeof(newtio));
    memset(&oldtio, 0x00, sizeof(oldtio));

    //获取串口的参数属性配置
    if (tcgetattr(fd, &oldtio) != 0x00)
       {
         #if DEBUG_SERIAL_MSG
            printf("file = %s, function = %s  get serial attributiong failed!\n", __FILE__, __func__);
         #endif

         iret = GET_UART_ATTR_ERROR;
         goto RETURN_LABEL;
       }

     //获取串口的Modem 的通信属性参数
     if (ioctl(fd, TIOCMGET, &status) < 0x00)
        {
          #if DEBUG_SERIAL_MSG
             printf("file = %s, function = %s  get serial attributiong failed!\n", __FILE__, __func__);
          #endif

            iret = GET_UART_MATTR_ERROR;
            goto RETURN_LABEL;
         }

     //关闭串口通信Modem流控制
         status &= ~(TIOCM_DTR | TIOCM_RTS);
      if (ioctl(fd, TIOCMSET, &status) < 0x00)
        {
           #if DEBUG_SERIAL_MSG
              printf("file = %s, function = %s  set serial attributiong failed!\n", __FILE__, __func__);
           #endif

           iret = SET_UART_MATTR_ERROR;
           goto RETURN_LABEL;
         }

         newtio.c_cflag |= CLOCAL|CREAD;
         newtio.c_cflag &= ~CSIZE;

        //设置数据位宽
         switch (nbits)
            {
                case 7:
                    newtio.c_cflag |= CS7;
                    break;

                case 8:
                    newtio.c_cflag |= CS8;
                    break;

                default:
                    newtio.c_cflag |= CS8;
                    break;
            }

         //设置数据校验属性
         switch (parary)
            {
                case 'O':
                case 'o':
                    newtio.c_cflag |=  PARENB;
                    newtio.c_cflag |= PARODD;
                    newtio.c_iflag |= (INPCK | ISTRIP);
                    break;

                case 'E':
                case 'e':
                    newtio.c_iflag |= (INPCK | ISTRIP);
                    newtio.c_cflag |= PARENB;
                    newtio.c_cflag &= ~PARODD;
                    break;

                case 'N':
                case 'n':
                    newtio.c_cflag &= ~PARENB;
                    break;

                default:
                    newtio.c_cflag &= ~PARENB;
                    break;
            }

            //设置数据通信速度
            switch (baudrate)
            {

                case 9600:
                    cfsetispeed(&newtio, B9600);
                    cfsetospeed(&newtio, B9600);
                    break;


                case 19200:
                    cfsetispeed(&newtio, B19200);
                    cfsetospeed(&newtio, B19200);
                    break;

                case 38400:
                    cfsetispeed(&newtio, B38400);
                    cfsetospeed(&newtio, B38400);
                    break;

                case 57600:
                    cfsetispeed(&newtio, B57600);
                    cfsetospeed(&newtio, B57600);
                    break;

                case 115200:
                    cfsetispeed(&newtio, B115200);
                    cfsetospeed(&newtio, B115200);
                    break;

                case 230400:
                    cfsetispeed(&newtio, B230400);
                    cfsetospeed(&newtio, B230400);
                    break;

                default:
                    cfsetispeed(&newtio, B115200);
                    cfsetospeed(&newtio, B115200);
                    break;
            }

            //设置通信双方数据停止位
            switch (stopbits)
            {
                case 1:
                    newtio.c_cflag &=  ~CSTOPB;
                    break;

                case 2:
                    newtio.c_cflag |=  CSTOPB;
                    break;

                default:
                    newtio.c_cflag |=  CSTOPB;
                    break;
            }

            newtio.c_iflag &= ~(IXON | IXOFF | IXANY);
            newtio.c_cflag &= ~CRTSCTS;

            newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
            newtio.c_oflag &= ~OPOST;
            newtio.c_cc[VTIME]  = 0;
            newtio.c_cc[VMIN] = 1;
            tcflush(fd,TCIFLUSH);

            //设置串口的数据通信参数
            if((tcsetattr(fd,TCSANOW,&newtio)) != 0x00)
            {
                #if DEBUG_SERIAL_MSG
                printf("file = %s, function = %s  set uart port failed!\n", __FILE__, __func__);
                #endif

                iret = SET_UART_ATTR_ERROR;
                goto RETURN_LABEL;
            }

            #if DEBUG_SERIAL_MSG
                printf("file = %s, function = %s  set uart successed!\n", __FILE__, __func__);
            #endif

  RETURN_LABEL:
#endif
  return iret;
}

int SerialPort::ReadData(int fd,unsigned char *data_buff,int len,int rcv_wait){

#if(QT_IN_WINDOWS == 0)
    int ret = 0x00;
    int retval = 0x00;
    int ret_more = 0x00;
    int pos = 0x00;

    unsigned char data_temp[200]={0};
    memset(data_buff,0,len);
    fd_set rfds;
    struct timeval tv;

    tv.tv_sec = rcv_wait;
    tv.tv_usec = 0x00;

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);


    while (true)
      {
         if (rcv_wait == 0x00)
            {
               retval = select(fd+1 , &rfds, NULL, NULL, NULL);
            }else{
               retval = select(fd+1 , &rfds, NULL, NULL, &tv);
            }

         if (retval > 0)
            {
                if (FD_ISSET(fd, &rfds))
                    {
                        //ret =  read(fd,data_buff,len);
                        ret =  read(fd,data_temp,200);
                        if(ret <2){
                            QThread::msleep(30);
                            ret_more =  read(fd,data_temp+ret,200-ret);
                            ret = ret+ret_more;
                        }

                        memcpy(data_buff,data_temp,ret);
                        return ret;
                    }
             }
             else{

                 #if DEBUG_SERIAL_MSG
                    //printf("fle = %s function = %s TimeOut, read data size null\n", __FILE__, __func__);
                 #endif

                 return -1;
            }
     }
#else
    return -1;
#endif
}

int SerialPort::WriteData(int fd,unsigned char *data_buff,int s_num){
    int slen = 0x00;
    int iret = 0x00;
    unsigned char *p_sendbuf = NULL;

     //分配临时缓冲区，保存传入的待发送数据
     p_sendbuf = (unsigned char *)malloc(s_num + 1);
            if (p_sendbuf != NULL)
            {
                memset(p_sendbuf, 0x00, s_num + 1);

                //拷贝待发送数据到临时缓冲区
                memcpy(p_sendbuf,data_buff,s_num);

                iret = write(fd, p_sendbuf, s_num);
                if (iret < 0x00)
                {
                    #if DEBUG_SERIAL_MSG
                    printf("file = %s function = %s  android_serial_write_data write uart error!\n", __FILE__, __func__);
                    #endif

                    free(p_sendbuf);
                    p_sendbuf = NULL;
                    iret = WRITE_UART_ERROR;
                    goto RETURN_LABEL;
                }

                #if DEBUG_SERIAL_MSG
                //printf("file = %s function = %s send data successed\n", __FILE__, __func__);
                #endif

                free(p_sendbuf);
                p_sendbuf = NULL;
                iret = 0x00;
                goto RETURN_LABEL;
            }
            else
            {
                #if DEBUG_SERIAL_MSG
                printf("file= %s  function = %s  WriteData malloc memory failed!\n", __FILE__, __func__);
                #endif

                iret = WRITE_UART_MEM_ERROR;
                goto RETURN_LABEL;
            }

RETURN_LABEL:
   return iret;
}

int SerialPort::Close(int fd){
  close(fd);
}
