// This code controls a Roomba 620 using the Arduino Roomba library
// See pinout diagram to connect Arduino Mega to Roomba via mini DIN connection
// If Serial1 doesn't work, try Serial3
// Note: if you disconnect the Arduino while the Roomba is running, it will keep running the last command!
// Note: the Roomba can be woken from sleep by using a pin but this sketch does not

#include <Roomba.h>
// Note: in line 394ish of Roomba.h, I manually changed the baudrate to 19200
// but I think you can also pass it in as a second parameter

Roomba roomba(&Serial3);

void setup() {
  Serial.begin(9600);

  roomba.start();
  Serial.println("Roomba started");
  roomba.fullMode();
  Serial.println("Be careful, I am in 'full' mode");

  delay(1000);

  // check LEDs
  Serial.println("Checking LEDs");
  blinkLed(3);
  roomba.leds(ROOMBA_MASK_LED_PLAY, 0, 255);

  roomba.drive(200, Roomba::DriveStraight);
  delay(3000);
  roomba.drive(0, 0);  // stop
  delay(1000);

  // play tune
  uint8_t song[] = { 60, 24, 64, 24, 67, 24, 72, 24, 67, 24, 64, 24, 60, 48 };
  roomba.song(0, song, sizeof(song));
  roomba.playSong(0);
  delay(4000);

  roomba.drive(-100, Roomba::DriveStraight);
  delay(5000);
  roomba.drive(0, 0);  // stop
  delay(1000);

  driveAround(100); // slow
  delay(1000);
  driveAround(200); // medium
  delay(1000);
  driveAround(500); // fast

  roomba.power();  // go to sleep, Roomba
}

void loop() {}

void blinkLed(int times) {
  for (int i = 0; i < times; i++) {
    roomba.leds(ROOMBA_MASK_LED_PLAY, 255, 255);
    delay(250);
    roomba.leds(ROOMBA_MASK_LED_NONE, 0, 0);
    delay(250);
  }
}

void driveAround(int speed) {
  roomba.drive(speed, Roomba::DriveStraight);
  delay(2000);
  roomba.drive(0, 0);  // stop
  delay(1000);
  roomba.drive(speed, Roomba::DriveInPlaceClockwise);
  delay(2000);
  roomba.drive(0, 0);  // stop
  delay(1000);
  roomba.drive(speed, Roomba::DriveInPlaceCounterClockwise);
  delay(2000);
  roomba.drive(0, 0);  // stop
  delay(1000);
  roomba.drive(-1 * speed, Roomba::DriveStraight);
  delay(2000);
  roomba.drive(0, 0);  // stop
}