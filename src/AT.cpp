#include "main.h"
#include "AT.h"

uint8_t SendATMult(char **argv, int argc)
{
    uint8_t res;

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
}

uint8_t SendAT(char *at)
{
    int8_t res;

    Xbee.write("+++", 3);
    if (Wait_AT_Command() != AT_OK)
        return res;

    Xbee.write(at, strlen(at));
    res = Wait_AT_Command();
    if (res != AT_OK)
        return res;

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
}

uint8_t Wait_AT_Command()
{
    long start = millis();
    while (!Xbee.available() && millis() - start < 10000)
        ;
    if (millis() - start >= 10000)
        return AT_TIMEOUT;
    if (Xbee.readString() != "OK\r")
        return AT_ERROR;
    return AT_OK;
}