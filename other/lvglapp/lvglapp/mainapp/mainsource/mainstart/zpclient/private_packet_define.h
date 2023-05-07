#ifndef _PRIVATE_PACKET_DEFINE_H_
#define _PRIVATE_PACKET_DEFINE_H_



#ifdef USE_BIG_PACKET
#define    PACKET_DATA_LEN			512
#else
#define    PACKET_DATA_LEN			0xffff	//128
#endif

#pragma pack(1)


typedef struct packet_t{
	unsigned short packet_head;
	unsigned char packet_type;
	unsigned char packet_num;
	unsigned char packet_id;
	unsigned short packet_data_len;
	//unsigned char data[PACKET_DATA_LEN];
	char *data;
	unsigned char check_sum;
	unsigned short packet_tail;
}T_Packet;

typedef struct service_list_t{
	T_Packet packet;
	struct service_list_t *next;
}T_Service_List;

#endif//_PRIVATE_PACKET_DEFINE_H_
