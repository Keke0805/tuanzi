#ifndef PACKET_H
#define PACKET_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define UART_DEV		"/dev/ttyS1"

#define PACKRT_HEAD		0xFA
#define PACKRT_TAIL		0xF5

//CMD
#define PACKRT_CMD_DISP_INIT        0x01
#define PACKRT_CMD_BULETOOTH        0x02
#define PACKRT_CMD_VOLUME           0x03
#define PACKRT_CMD_MICROPHONE       0x04
#define PACKRT_CMD_RGB_LIGHT        0x05
#define PACKRT_CMD_PLAY_CTRL        0x06
#define PACKRT_CMD_SONG_INFO        0x07


typedef struct packet_t{
    unsigned char packet_head;
    unsigned char packet_type;
    unsigned short packet_data_len;
    unsigned char *data;
    unsigned short packet_tail;
}T_Packet;

#endif // PACKET_H
