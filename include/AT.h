#define AT_OK 0
#define AT_ERROR 1
#define AT_TIMEOUT 2

#define TIMOUT_AT 10000 // 10s

uint8_t SendATMult(char **argv, int argc);
uint8_t SendA(char *at);
uint8_t Wait_AT_Command();