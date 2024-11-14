#define AT_OK 0
#define AT_ERROR 1
#define AT_TIMEOUT 2

#define TIMEOUT_AT 10000 // 10s

#define DEFAULT_DL 2

uint8_t SendATMult(char **argv, int argc);
uint8_t SendAT(char *at);
uint8_t SendMsg(char *msg, int dl);
uint8_t Wait_AT_Command();
