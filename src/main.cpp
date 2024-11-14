#include "main.h"
#include "AT.h"
#include "queue.h"

#define N_CONFIG 4
#define TIMEOUT_SEND 5000

char *config[N_CONFIG] = {"ATMY 1\r", "ATID 1234\r", "ATCH C\r", "ATDL 2\r"};

long time_last_send = 0;
bool send_msg = true;

String cmd_to_relay = " ";

SoftwareSerial Xbee(RX, TX);
PriorityQueue msgQueue;
QueueElement msgSent;

void setup()
{
  Serial.begin(9600);
  Xbee.begin(9600);

  if (SendATMult((char **)config, N_CONFIG) != AT_OK)
    Serial.println("Error");
  else
    Serial.println("Conf OK");

  Xbee.println("Test");
}

void loop()
{
  if (Xbee.available())
  {
    cmd_to_relay = Xbee.readString();
    Serial.print("Received: ");
    Serial.println(cmd_to_relay);
  }

  if ((cmd_to_relay[0] & 0x20))
  {
    switch (cmd_to_relay[0])
    {
    case MOT_ACK:
      if (msgSent.ack_to_receive == MOT_ACK)
        send_msg = true;
      break;
    case SERV_ACK:
      if (msgSent.ack_to_receive == SERV_ACK)
        send_msg = true;
      break;
    case LCD_ACK:
      if (msgSent.ack_to_receive == LCD_ACK)
        send_msg = true;
      break;
    case RELAY_ACK:
      if (msgSent.ack_to_receive == RELAY_ACK)
        send_msg = true;
      break;

    case ' ':
      break;

    default:
      Serial.println("ACK not recognized");
      break;
    }
  }
  else
  {
    char ack[3] = {HUB_ACK, '\r', '\0'};
    switch (cmd_to_relay[0])
    {

    case TEMP_CMD:
      SendMsg(ack, MY_TMP);
      msgQueue.enqueue(cmd_to_relay, MY_REL, RELAY_ACK, 1);
      msgQueue.enqueue(cmd_to_relay, MY_LCP, LCD_ACK, 1);
      break;
    case ERROR_CMD:
      SendMsg(ack, MY_REL);
      msgQueue.enqueue(cmd_to_relay, MY_LCP, LCD_ACK, 2);
      break;
    case POT_CMD:
      SendMsg(ack, MY_LCP);
      msgQueue.enqueue(cmd_to_relay, MY_REL, RELAY_ACK, 1);
      break;
    case ALERTE_CMD:
      SendMsg(ack, MY_LCP);
      msgQueue.enqueue(cmd_to_relay, MY_LCP, LCD_ACK, 3);
      break;

    default:
      Serial.println("CMD not recognized");
      break;
    }
  }

  if ((millis() - time_last_send > TIMEOUT_SEND) && !send_msg)
  {
    send_msg = true;
    msgQueue.enqueue(msgSent.msg, msgSent.dl, msgSent.ack_to_receive, 1);
  }

  if (!msgQueue.isEmpty() && send_msg)
  {
    msgQueue.dequeue(msgSent);
    time_last_send = millis();
    SendMsg((char *)msgSent.msg.c_str(), msgSent.dl);
  }
}
