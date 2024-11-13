
#include "main.h"
#include "AT.h"

#define RX 2
#define TX 3

SoftwareSerial Xbee(RX, TX);
void setup()
{
  Serial.begin(9600);
  Xbee.begin(9600);
  char *argv[] = {"ATMY 1\r", "ATID 1234\r"};
  if (SendATMult(argv, 2) != AT_OK)
    Serial.println("Error");
  else
    Serial.println("Conf OK");
}

void loop()
{

  if (Xbee.available())
  {
    Serial.println(Xbee.readString());
  }
}
