#include "main.h"
#include "AT.h"

const char *config[] = {"ATMY 1\r", "ATID 1234\r"};
SoftwareSerial Xbee(RX, TX);

void setup()
{
  Serial.begin(9600);
  Xbee.begin(9600);
  if (SendATMult((char **)config, 2) != AT_OK)
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
