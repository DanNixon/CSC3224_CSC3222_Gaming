/** @file */

#include <SBUS.h>

#include <FrSkySportSensor.h>
#include <FrSkySportSensorFcs.h>
#include <FrSkySportSensorSp2uart.h>
#include <FrSkySportSensorVario.h>
#include <FrSkySportSingleWireSerial.h>
#include <FrSkySportTelemetry.h>

#include <TimerThree.h>

SBUS sbus(Serial3);

FrSkySportSensorFcs fcs;
FrSkySportSensorSp2uart sp2uart;
FrSkySportSensorVario vario;
FrSkySportTelemetry telemetry;

#define SBUS_HIGH 83
#define SBUS_LOW -SBUS_HIGH

#define STATUS_LED 13

#define SERIAL_BUFFER_LEN 32
#define SERIAL_COMMAND_END ';'

uint32_t lastBadFrames;
int serialBufferPos;
char serialBuffer[SERIAL_BUFFER_LEN];

enum Channel
{
  CH_ZERO,

  CH_THROT,
  CH_ROLL,
  CH_PITCH,
  CH_YAW
};

/**
 * @brief Setup routine.
 */
void setup()
{
  Serial.begin(9600);

  lastBadFrames = 0;
  serialBufferPos = 0;
  memset(serialBuffer, '\0', SERIAL_BUFFER_LEN);

  Joystick.useManualSend(true);

  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, HIGH);

  Timer3.initialize(1000);
  Timer3.attachInterrupt(up);
  sbus.begin();

  telemetry.begin(FrSkySportSingleWireSerial::SERIAL_2, &fcs, &sp2uart, &vario);
}

/**
 * @brief Main routine.
 */
void loop()
{
  // If RX failsafe is active
  if (sbus.getFailsafeStatus() == SBUS_FAILSAFE_ACTIVE)
  {
    // Set failsafe
    Joystick.Y(512);
    Joystick.X(512);
    Joystick.Z(512);
    Joystick.Zrotate(512);
    Joystick.sliderLeft(512);
    Joystick.sliderRight(512);

    for (int i = 0; i < 4; i++)
      Joystick.button(i, false);
  }
  else
  {
    // Joystick axes
    Joystick.Y(map(sbus.getNormalizedChannel(CH_PITCH), SBUS_LOW, SBUS_HIGH, 0, 1023));
    Joystick.X(map(sbus.getNormalizedChannel(CH_ROLL), SBUS_LOW, SBUS_HIGH, 0, 1023));
    Joystick.Z(map(sbus.getNormalizedChannel(CH_THROT), SBUS_LOW, SBUS_HIGH, 0, 1023));
    Joystick.Zrotate(map(sbus.getNormalizedChannel(CH_YAW), SBUS_LOW, SBUS_HIGH, 0, 1023));

    // Sliders / aux channels
    Joystick.sliderLeft(map(sbus.getNormalizedChannel(5), SBUS_LOW, SBUS_HIGH, 0, 1023));
    Joystick.sliderRight(map(sbus.getNormalizedChannel(6), SBUS_LOW, SBUS_HIGH, 0, 1023));

    // Aux channel switches as buttons
    Joystick.button(1, sbus.getNormalizedChannel(7) >= 60);
    Joystick.button(2, sbus.getNormalizedChannel(8) >= 60);
    Joystick.button(3, sbus.getNormalizedChannel(9) >= 60);
    Joystick.button(4, sbus.getNormalizedChannel(10) >= 60);
  }

  // Send joystick values
  Joystick.send_now();

  // Detect bad frames
  uint32_t badFrames = sbus.getLostFrames();
  bool haveBadFrames = badFrames > lastBadFrames;
  if (haveBadFrames)
    lastBadFrames = badFrames;

  // Light LED on bad frames
  digitalWrite(STATUS_LED, haveBadFrames);

  // Read serial port
  while (Serial.available())
  {
    char c = Serial.read();

    if (c == SERIAL_COMMAND_END)
    {
      float current, voltage, a3, a4, altitude, vSpeed;

      // Parse serial data
      sscanf(serialBuffer, "%f,%f,%f,%f,%f,%f", &a3, &a4, &current, &voltage, &altitude, &vSpeed);

      // Empty buffer
      memset(serialBuffer, '\0', SERIAL_BUFFER_LEN);
      serialBufferPos = 0;

      // Update telemetry values
      fcs.setData(current, voltage);
      sp2uart.setData(a3, a4);
      vario.setData(altitude, vSpeed);
    }
    else if (serialBufferPos == SERIAL_BUFFER_LEN - 1)
    {
      // Empty buffer
      memset(serialBuffer, '\0', SERIAL_BUFFER_LEN);
      serialBufferPos = 0;
    }
    else
      serialBuffer[serialBufferPos++] = c;
  }

  // Send telemetry data to polled sensors
  telemetry.send();
}

void up()
{
  sbus.process();
}
