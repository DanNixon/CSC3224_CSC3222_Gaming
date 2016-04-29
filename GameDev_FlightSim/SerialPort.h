/**
 * @file
 * @author Tom Archer, Rick Leinecker, Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 *
 * Adapted from:
 * http://www.codeguru.com/cpp/i-n/network/serialcommunications/article.php/c2503/CSerial--A-C-Class-for-Serial-Communications.htm
 */

#ifndef _GAMEDEV_FLIGHTSIM_SERIALPORT_H_
#define _GAMEDEV_FLIGHTSIM_SERIALPORT_H_

#define FC_DTRDSR 0x01
#define FC_RTSCTS 0x02
#define FC_XONXOFF 0x04
#define ASCII_BEL 0x07
#define ASCII_BS 0x08
#define ASCII_LF 0x0A
#define ASCII_CR 0x0D
#define ASCII_XON 0x11
#define ASCII_XOFF 0x13

#include "Windows.h"

namespace GameDev
{
namespace FlightSim
{
  class SerialPort
  {
  public:
    SerialPort();
    ~SerialPort();

    bool open(int nPort = 2, int nBaud = 9600);
    bool close();

    bool isOpen()
    {
      return m_open;
    }

    int readData(void *, int);
    int sendData(const char *, int);
    int readDataWaiting();

  protected:
    bool writeCommByte(unsigned char);

    HANDLE m_device;
    OVERLAPPED m_read;
    OVERLAPPED m_write;
    bool m_open;
  };
}
}

#endif
