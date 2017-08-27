// SPI Master Example
// Adapted from Nick Gammon
// http://www.gammon.com.au/spi

#include <SPI.h>

void setup() {
  Serial.begin(115200);
  Serial.println();

  digitalWrite(SS, HIGH); // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin();
}

void loop() {
  byte a, b, c, d;

  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0)); // 2 MHz clock

  // add some numbers
  digitalWrite(SS, LOW);
  spiTransfer('a');
  spiTransfer(10);
  a = spiTransfer(32);
  b = spiTransfer(54);
  c = spiTransfer(76);
  d = spiTransfer(0); // ignored
  digitalWrite(SS, HIGH);

  Serial.println("Running sum:");
  Serial.println(a, DEC);
  Serial.println(b, DEC);
  Serial.println(c, DEC);
  Serial.println(d, DEC);

  // multiply some numbers
  digitalWrite(SS, LOW);
  spiTransfer('m');
  spiTransfer(5);
  a = spiTransfer(4);
  b = spiTransfer(3);
  c = spiTransfer(2);
  d = spiTransfer(1); // ignored
  digitalWrite(SS, HIGH);

  Serial.println("Running product:");
  Serial.println(a, DEC);
  Serial.println(b, DEC);
  Serial.println(c, DEC);
  Serial.println(d, DEC);

  SPI.endTransaction();
  delay(1000);
}

byte spiTransfer(const byte b) {
  byte result = SPI.transfer(b);
  delayMicroseconds(20);
  return result;
}

