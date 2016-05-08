/**
 * @file
 * @author Tom Archer, Rick Leinecker, Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#ifndef _GAMEDEV_FLIGHTSIM_SERIALPORT_H_
#define _GAMEDEV_FLIGHTSIM_SERIALPORT_H_

#ifndef DOXYGEN_SKIP
#define FC_DTRDSR 0x01
#define FC_RTSCTS 0x02
#define FC_XONXOFF 0x04
#define ASCII_BEL 0x07
#define ASCII_BS 0x08
#define ASCII_LF 0x0A
#define ASCII_CR 0x0D
#define ASCII_XON 0x11
#define ASCII_XOFF 0x13
#endif /* DOXYGEN_SKIP */

#include <string>

#include <Windows.h>

#include <Engine_ResourceManagment\IMemoryManaged.h>

namespace GameDev
{
namespace FlightSim
{
  /**
   * @class SerialPort
   * @brief Serial port driver.
   * @author Tom Archer, Rick Leinecker, Dan Nixon (120263697)
   *
   * Adapted from:
   * http://www.codeguru.com/cpp/i-n/network/serialcommunications/article.php/c2503/CSerial--A-C-Class-for-Serial-Communications.htm
   */
  class SerialPort : public Engine::ResourceManagment::IMemoryManaged
  {
  public:
    SerialPort();
    ~SerialPort();

    bool open(const std::string &portName, int baud = 9600);
    bool close();

    /**
     * @brief Check if the port is open.
     * @return True if port is open
     */
    bool isOpen()
    {
      return m_open;
    }

    int readData(void *buffer, size_t len);
    int sendData(const char *buffer, size_t len);
    int readDataWaiting();

  protected:
    bool writeCommByte(unsigned char ucByte);

    HANDLE m_device;    //!< Device handle
    OVERLAPPED m_read;  //!< Read IO
    OVERLAPPED m_write; //!< Write IO
    bool m_open;        //!< Flag indicating the port is open
  };
}
}

#endif
