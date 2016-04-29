/**
 * @file
 * @author Tom Archer, Rick Leinecker, Dan Nixon (120263697)
 *
 * For CSC3224 Project 2.
 *
 * Adapted from:
 * http://www.codeguru.com/cpp/i-n/network/serialcommunications/article.php/c2503/CSerial--A-C-Class-for-Serial-Communications.htm
 */

#include "SerialPort.h"

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

  bool SerialPort::open(int nPort, int nBaud)
  {
    if (m_open)
      return true;

    char szPort[15];
    char szComParams[50];
    DCB dcb;

    wsprintf(szPort, "COM%d", nPort);
    m_device = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, nullptr);
    if (m_device == nullptr)
      return false;

    memset(&m_read, 0, sizeof(OVERLAPPED));
    memset(&m_write, 0, sizeof(OVERLAPPED));

    COMMTIMEOUTS CommTimeOuts;
    CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
    CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
    CommTimeOuts.ReadTotalTimeoutConstant = 0;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
    CommTimeOuts.WriteTotalTimeoutConstant = 5000;
    SetCommTimeouts(m_device, &CommTimeOuts);

    wsprintf(szComParams, "COM%d:%d,n,8,1", nPort, nBaud);

    m_read.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    m_write.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

    dcb.DCBlength = sizeof(DCB);
    GetCommState(m_device, &dcb);
    dcb.BaudRate = nBaud;
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

      return false;
    }

    m_open = true;
    return m_open;
  }

  bool SerialPort::close(void)
  {
    if (!m_open || m_device == nullptr)
      return true;

    if (m_read.hEvent != nullptr)
      CloseHandle(m_read.hEvent);

    if (m_write.hEvent != nullptr)
      CloseHandle(m_write.hEvent);

    CloseHandle(m_device);

    m_open = false;
    m_device = nullptr;

    return true;
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

  int SerialPort::sendData(const char *buffer, int size)
  {

    if (!m_open || m_device == nullptr)
      return 0;

    DWORD dwBytesWritten = 0;
    int i;
    for (i = 0; i < size; i++)
    {
      writeCommByte(buffer[i]);
      dwBytesWritten++;
    }

    return (int)dwBytesWritten;
  }

  int SerialPort::readDataWaiting(void)
  {

    if (!m_open || m_device == nullptr)
      return 0;

    DWORD dwErrorFlags;
    COMSTAT ComStat;

    ClearCommError(m_device, &dwErrorFlags, &ComStat);

    return (int)ComStat.cbInQue;
  }

  int SerialPort::readData(void *buffer, int limit)
  {

    if (!m_open || m_device == nullptr)
      return 0;

    BOOL bReadStatus;
    DWORD dwBytesRead, dwErrorFlags;
    COMSTAT ComStat;

    ClearCommError(m_device, &dwErrorFlags, &ComStat);
    if (!ComStat.cbInQue)
      return 0;

    dwBytesRead = (DWORD)ComStat.cbInQue;
    if (limit < (int)dwBytesRead)
      dwBytesRead = (DWORD)limit;

    bReadStatus = ReadFile(m_device, buffer, dwBytesRead, &dwBytesRead, &m_read);
    if (!bReadStatus)
    {
      if (GetLastError() == ERROR_IO_PENDING)
      {
        WaitForSingleObject(m_read.hEvent, 2000);
        return ((int)dwBytesRead);
      }
      return 0;
    }

    return (int)dwBytesRead;
  }
}
}