
#include "main.h"
#include <SoftwareSerial.h>
#include "TimerInterrupt_Generic.h"

#define RX 2
#define TX 3

bool Time_delay = NO_TIMEOUT;
TimerInterrupt Timer1(1);

SoftwareSerial Xbee(RX, TX);
void setup()
{
  Serial.begin(9600);
  Xbee.begin(9600);
  Timer1.init();
  Timer1.attachInterruptInterval(10, Timer1_ISR);
  Timer1.pauseTimer();

  Xbee.write("+++", 3);
  AT_delay();
  while (!Xbee.available() && Time_delay)
    ;

  if (Xbee.readString() != "OK\r")
    return;
  Serial.println("OK1");
  char cmd[] = "ATMY 1\r";
  Xbee.write(cmd, strlen(cmd));
  while (!Xbee.available() && Time_delay)
    ;
  if (Xbee.readString() != "OK\r")
    Serial.println("Error");

  Serial.println("OK4");

  Serial.print("Hello");
}

void loop()
{

  if (Xbee.available())
  {
    Serial.println(Xbee.readString());
  }
}

void SendAT(char **argv, int argc)
{
  // Xbee.write("+++", 3);
  // while (Xbee.available() <= 0)
  //   ;
  // if (Xbee.readString() != "OK")
  //   return;
  // Xbee.write(cmd, 7);
  // while (Xbee.available() <= 0)
  //   ;
  // if (Xbee.readString() != "OK")
  //   return;
  // Xbee.write("ATWR\r", 5);
  // while (Xbee.available() <= 0)
  //   ;
  // if (Xbee.readString() != "OK")
  //   return;
  // Xbee.write("ATCN\r", 5);
  // while (Xbee.available() <= 0)
  //   ;
}

void Timer1_ISR()
{
  Timer1.pauseTimer();
  Time_delay = ERROR_TIMEOUT;
  Serial.println("Time OUT");
}

void AT_delay()
{
  Time_delay = NO_TIMEOUT;
  Timer1.restartTimer();
  Serial.println("Timer start");
}

// void Xbee_delay()
// {
//   Time_delay = NO_TIMEOUT;
//   Timer1.initialize(5000000);
//   Timer1.start();
// }

// void Stop_delay()
// {
//   Timer1.stop();
// }