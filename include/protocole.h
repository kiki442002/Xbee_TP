#define HUB_ACK 'h'
#define MOT_ACK 'a'
#define SERV_ACK 'b'
#define LCD_ACK 'c'
#define RELAY_ACK 'r'

#define TEMP_CMD 'T'
#define ERROR_CMD 'E'
#define POT_CMD 'P'
#define ALERTE_CMD 'M'

#define MY_HUB 1
#define MY_REL 2
#define MY_LCP 3
#define MY_TMP 4
#define MY_MOT 5

extern int pot_device[1];
extern int temp_device[2];
extern int error_device[1];
extern int alerte_device[1];
