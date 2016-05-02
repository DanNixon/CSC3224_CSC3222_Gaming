/**
 * @file
 * @author Tom Archer, Rick Leinecker, Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 */

#include "SerialPort.h"

#include <Engine_Logging/Logger.h>

namespace
{
Engine::Logging::Logger g_log(__FILE__);
}

namespace GameDev
{
namespace FlightSim
{
  SerialPort::SerialPort()
      : m_device(nullptr)
      , m_open(false)
  {
    memset(&m_read, 0, sizeof(OVERLAPPED));
    memset(&m_write, 0, sizeof(OVERLAPPED));
  }

  SerialPort::~SerialPort()
  {
    close();
  }

  bool SerialPort::open(const std::string &portName, int baud)
  {
    if (m_open)
      return true;

    g_log.debug("Opening serial port " + portName);

    char szComParams[50];
    DCB dcb;

    m_device = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, nullptr);
    if (m_device == nullptr)
    {
      g_log.warn("Failed to create serial port");
      return false;
    }

    memset(&m_read, 0, sizeof(OVERLAPPED));
    memset(&m_write, 0, sizeof(OVERLAPPED));

    COMMTIMEOUTS CommTimeOuts;
    CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
    CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
    CommTimeOuts.ReadTotalTimeoutConstant = 0;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
    CommTimeOuts.WriteTotalTimeoutConstant = 5000;
    SetCommTimeouts(m_device, &CommTimeOuts);

    wsprintf(szComParams, "%s:%d,n,8,1", portName.c_str(), baud);

    m_read.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    m_write.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

    dcb.DCBlength = sizeof(DCB);
    GetCommState(m_device, &dcb);
    dcb.BaudRate = baud;
    dcb.ByteSize = 8;
    unsigned char ucSet;
    ucSet = (unsigned char)((FC_RTSCTS & FC_DTRDSR) != 0);
    ucSet = (unsigned char)((FC_RTSCTS & FC_RTSCTS) != 0);
    ucSet = (unsigned char)((FC_RTSCTS & FC_XONXOFF) != 0);

    if (!SetCommState(m_device, &dcb) || !SetupComm(m_device, 10000, 10000) || m_read.hEvent == nullptr ||
        m_write.hEvent == nullptr)
    {
      DWORD dwError = GetLastError();

      if (m_read.hEvent != nullptr)
        CloseHandle(m_read.hEvent);

      if (m_write.hEvent != nullptr)
        CloseHandle(m_write.hEvent);

      CloseHandle(m_device);

      g_log.warn("Failed to configure serial port IO");
      return false;
    }

    m_open = true;
    return m_open;
  }

  bool SerialPort::close()
  {
    if (!m_open || m_device == nullptr)
      return true;

    g_log.debug("Closing serial port");

    if (m_read.hEvent != nullptr)
      CloseHandle(m_read.hEvent);

    if (m_write.hEvent != nullptr)
      CloseHandle(m_write.hEvent);

    CloseHandle(m_device);

    m_open = false;
    m_device = nullptr;

    return true;
  }

  int SerialPort::sendData(const char *buffer, size_t len)
  {
    if (!m_open || m_device == nullptr)
      return 0;

    g_log.debug("Sending serial data");

    DWORD dwBytesWritten = 0;
    int i;
    for (i = 0; i < len; i++)
    {
      writeCommByte(buffer[i]);
      dwBytesWritten++;
    }

    g_log.debug("Sent bytes: " + std::to_string((int)dwBytesWritten));
    return (int)dwBytesWritten;
  }

  int SerialPort::readDataWaiting()
  {
    if (!m_open || m_device == nullptr)
      return 0;

    DWORD dwErrorFlags;
    COMSTAT ComStat;

    ClearCommError(m_device, &dwErrorFlags, &ComStat);

    return (int)ComStat.cbInQue;
  }

  int SerialPort::readData(void *buffer, size_t len)
  {
    if (!m_open || m_device == nullptr)
      return 0;

    g_log.debug("Reading serial data");

    BOOL bReadStatus;
    DWORD dwBytesRead, dwErrorFlags;
    COMSTAT ComStat;

    ClearCommError(m_device, &dwErrorFlags, &ComStat);
    if (!ComStat.cbInQue)
    {
      g_log.debug("No data to be read");
      return 0;
    }

    dwBytesRead = (DWORD)ComStat.cbInQue;
    if (len < (int)dwBytesRead)
      dwBytesRead = (DWORD)len;

    bReadStatus = ReadFile(m_device, buffer, dwBytesRead, &dwBytesRead, &m_read);
    if (!bReadStatus)
    {
      if (GetLastError() == ERROR_IO_PENDING)
      {
        WaitForSingleObject(m_read.hEvent, 2000);
        g_log.debug("Read bytes: " + std::to_string((int)dwBytesRead));
        return ((int)dwBytesRead);
      }

      g_log.debug("No data to be read");
      return 0;
    }

    g_log.debug("Read bytes: " + std::to_string((int)dwBytesRead));
    return (int)dwBytesRead;
  }

  bool SerialPort::writeCommByte(unsigned char ucByte)
  {
    BOOL bWriteStat;
    DWORD dwBytesWritten;

    bWriteStat = WriteFile(m_device, (LPSTR)&ucByte, 1, &dwBytesWritten, &m_write);
    if (!bWriteStat && (GetLastError() == ERROR_IO_PENDING))
    {
      if (WaitForSingleObject(m_write.hEvent, 1000))
        dwBytesWritten = 0;
      else
      {
        GetOverlappedResult(m_device, &m_write, &dwBytesWritten, FALSE);
        m_write.Offset += dwBytesWritten;
      }
    }

    return true;
  }
}
}
