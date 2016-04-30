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

uint32_t lastBadFrames;

#define SBUS_HIGH 83
#define SBUS_LOW -SBUS_HIGH

#define STATUS_LED 13

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

  // Detect bad frames
  uint32_t badFrames = sbus.getLostFrames();
  bool haveBadFrames = badFrames > lastBadFrames;
  if (haveBadFrames)
    lastBadFrames = badFrames;

  // Light LED on bad frames
  digitalWrite(STATUS_LED, haveBadFrames);

  // Update telemetry values
  fcs.setData(25.3, 12.6);    // Current, Voltage
  sp2uart.setData(1.5, 3.3);  // A3, A4
  vario.setData(250.5, -1.5); // Altitude (m), vertical speed (ms-1)

  // Send telemetry data to polled sensors
  telemetry.send();
}

void up()
{
  sbus.process();
}
