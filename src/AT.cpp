#include "main.h"
#include "AT.h"

int current_dl = 2;
long last_time_send = -11000;

uint8_t SendATMult(char **argv, int argc)
{
    uint8_t res;
    long del = (1100 - ((millis() - last_time_send)));
    if (del > 0)
        delay(del);

    delay(1100);
    Xbee.write("+++", 3);
    if (Wait_AT_Command() != AT_OK)
        return res;

    for (int i = 0; i < argc; i++)
    {
        Xbee.write(argv[i], strlen(argv[i]));
        res = Wait_AT_Command();
        if (res != AT_OK)
            return res;
    }
    // Save configuration
    Xbee.write("ATWR\r", 5);
    res = Wait_AT_Command();
    if (res != AT_OK)
        return res;
    // Exit AT mode
    Xbee.write("ATCN\r", 5);
    res = Wait_AT_Command();
    if (res != AT_OK)
        return res;

    return res;
    last_time_send = millis();
}

uint8_t SendAT(char *at)
{
    int8_t res;
    long del = (1200 - ((millis() - last_time_send)));
    if (del > 0)
        delay(del);

    Xbee.write("+++", 3);
    if (Wait_AT_Command() != AT_OK)
        return res;
    Xbee.write(at, strlen(at));
    res = Wait_AT_Command();
    if (res != AT_OK)
        return res;
    // Save configuration
    Xbee.write("ATAC\r", 5);
    res = Wait_AT_Command();
    if (res != AT_OK)
        return res;
    // Exit AT mode
    Xbee.write("ATCN\r", 5);
    res = Wait_AT_Command();
    if (res != AT_OK)
        return res;
    return res;
    last_time_send = millis();
}

uint8_t SendMsg(char *msg, int dl)
{
    char conf[5];

    if (dl != current_dl)
    {
        sprintf(conf, "ATDL %d\r", dl);
        if (SendAT(conf) != AT_OK)
            return AT_ERROR;
        current_dl = dl;
    }

    Xbee.println(msg);
    last_time_send = millis();
    return AT_OK;
}

uint8_t Wait_AT_Command()
{
    long start = millis();
    while (!Xbee.available() && millis() - start < TIMEOUT_AT)
        ;
    if (millis() - start >= 10000)
        return AT_TIMEOUT;
    if (Xbee.readString() != "OK\r")
        return AT_ERROR;
    return AT_OK;
}
