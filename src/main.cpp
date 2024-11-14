#include "main.h"
#include "AT.h"
#include "queue.h"

#define N_CONFIG 4

char *config[N_CONFIG] = {"ATMY 1\r", "ATID 1234\r", "ATCH C\r", "ATDL 2\r"};

int pot_device[1] = {MY_REL};
int temp_device[2] = {MY_LCP, MY_REL};
int error_device[1] = {MY_LCP};
int alerte_device[1] = {MY_LCP};

String cmd_to_relay = "";

SoftwareSerial Xbee(RX, TX);
PriorityQueue msgQueue;

void setup()
{
  Serial.begin(9600);
  Xbee.begin(9600);

  if (SendATMult((char **)config, N_CONFIG) != AT_OK)
    Serial.println("Error");
  else
    Serial.println("Conf OK");
}

void loop()
{
  if (Xbee.available())
  {
    // cmd_to_relay = Xbee.readString();
    Serial.println(Xbee.readString());
  }

  if ((cmd_to_relay[0] & 0x20))
  {
    switch (cmd_to_relay[0])
    {
    case MOT_ACK:
      /* code */
      break;
    case SERV_ACK:
      /* code */
      break;
    case LCD_ACK:
      /* code */
      break;
    case RELAY_ACK:
      /* code */
      break;

    default:
      // Serial.println("ACK not recognized");
      break;
    }
  }
  else
  {
    switch (cmd_to_relay[0])
    {
    case TEMP_CMD:
      msgQueue.enqueue(cmd_to_relay, MY_REL, 1);
      msgQueue.enqueue(cmd_to_relay, MY_LCP, 1);
      break;
    case ERROR_CMD:
      msgQueue.enqueue(cmd_to_relay, MY_LCP, 2);
      break;
    case POT_CMD:
      msgQueue.enqueue(cmd_to_relay, MY_REL, 1);
      break;
    case ALERTE_CMD:
      msgQueue.enqueue(cmd_to_relay, MY_LCP, 3);
      break;

    default:
      // Serial.println("CMD not recognized");
      break;
    }
  }

  String msg_to_send;
  int dl_to_send;
  if (msgQueue.dequeue(msg_to_send, dl_to_send) != 0)
  {
    SendMsg((char *)msg_to_send.c_str(), dl_to_send);
  }
}
