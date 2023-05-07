#include "list.h"
#include "packet.h"
#include "private_packet_define.h"

#define PACK_INFO(fmt, arg...) printf("[PACK-INFO]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)
#define PACK_ERR(fmt, arg...) printf("[PACK-ERR]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)

#define    		SOH             0x01
#define    		STX             0xfefe
#define    		EOT             0x04
#define    		ACK             0x06
#define    		NAK             0x15
#define    		CAN             0x18
#define    		CTRLZ           0x1A
#define    		PACK_TAIL            0xefef

#ifdef     USE_ACK
#define    RETRY_TIMES				(1)
#else
#define    RETRY_TIMES				(0)
#endif
#define  isPacketHead(phead)	(*phead==STX)
#define  set_packet_Head(phead) (*(phead))=STX
#define  isPacketTail(ptail)	(*ptail==PACK_TAIL)

#ifdef  USE_SCOKET_MANAGE
#define       MAX_ONLINE_DOWNLOAD			10
#else
#define		  MAX_ONLINE_DOWNLOAD			1
#endif

extern int zpc_sockfd;

void debug_print_packet(T_Packet *packet)
{
	printf( "head %d %d %d %d %d ",packet->packet_head,packet->packet_id,\
		packet->packet_num,packet->packet_type,packet->packet_data_len);
	printf("   checksum =%d \r\n", packet->check_sum);
}

//return ret: ret==1���ݿɶ�; ret=0������; ret<0�������
int sock_can_read(int fd)
{
	int rc;
	fd_set fds;
	static struct timeval out;
	
	FD_ZERO(&fds);
	FD_SET(fd,&fds);

	out.tv_sec  = 2;	//2
	out.tv_usec = 80000;//80000
	
	rc = select(fd+1, &fds, NULL, NULL, &out);
	if (rc < 0)   //error
	{
		PACK_INFO("network error, exit!!!");
		return -1;
	}

	return FD_ISSET(fd,&fds) ? 1 : 0;
}

/**********************************************
*timeout: max 1000ms
*�ɹ�����1
*ʧ��:-1=some errors,-2=net error,-3=timeout
**********************************************/
int sock_can_write(int fd)
{
	int ret = 0;
	fd_set write_fdset;
	struct timeval timeout;
	
	FD_ZERO(&write_fdset);
	FD_SET(fd, &write_fdset);
	
	timeout.tv_sec = 2;
	timeout.tv_usec = 80000;
	
	ret = select(fd + 1, NULL, &write_fdset, NULL, &timeout);
	if(ret<0)
	{
		perror("select");
		ret = -2;
	}
	else if(ret == 0)
	{			
		//retry_cnt--;
		//if(retry_cnt==0)
		//{
			PACK_INFO("select timeout");
			ret = -3;
		//}
	}
	else
		ret = FD_ISSET(fd,&write_fdset) ? 1 : 0;

	return ret;
}
int client_tcp_send(char *buf , int size)
{
	int len;
	int ret = 0,  retry =0;
	do{
		if(zpc_sockfd <= 0)
		{
			PACK_INFO("zpc_sockfd is NULL");
			ret = -1;
			return ret;
		}
		if(sock_can_write(zpc_sockfd) != 1)
		{
			PACK_INFO("sock write pipe busy");
			ret =0;
			return ret;
		}
		len = send(zpc_sockfd, buf, size, 0);
		if(len < 0)
		{
			PACK_INFO("send failed, errno=%d",errno);
			if(errno == EAGAIN)//�����ݶ�
			{
				ret = 0;
				break ;
			}
			else if(errno == EINTR)//�����ź��ж�û�ж�������
			{
				ret = 0;
				break ;
			}
			else
			{
				ret = -1;
				return ret;
			}
		}
		else if(len == 0)
		{
			PACK_INFO("write err");
			ret = -1;
			return ret;
		}
		buf += len;
		size -= len;
		ret += len;
	}while(size > 0);

	return ret;
}
//return ret: ret>0��������; ret=0������; ret<0�������
int client_tcp_recv(char *buf, int size)
{    
	int len;
	int ret = 0;
	int val = -1;
	
	do{
		if(zpc_sockfd <= 0)
		{
			PACK_INFO("zpc_sockfd is NULL");
			ret = -1;
			return ret;
		}
		val = sock_can_read(zpc_sockfd);
		if(val != 1)
		{
			//PACK_INFO("socket no data for read");
			ret = val;
			break;
		}
		len = recv(zpc_sockfd, buf, size, 0);
		if(len < 0)
		{
			PACK_INFO("recv failed, errno=%d",errno);
			if(errno == EAGAIN)//�����ݶ�
			{
				ret = 0;
				break ;
			}
			else if(errno == EINTR)//�����ź��ж�û�ж�������
			{
				ret = 0;
				break;
			}
			else
			{
				ret = -1;
				PACK_INFO("network error.");
				return ret;
			}
		}
		else if(len == 0)        
		{    
			return ret;
		}  
		
		buf += len;
		size -= len;
		ret += len;
	}while(size > 0);

	return ret;
}

T_Service_List* service_malloc()
{
	T_Service_List* plist = NULL;
	plist = (T_Service_List*)malloc( sizeof(T_Service_List));
	if(plist)
		plist->next = NULL;
	return plist;
}

void service_free(T_Service_List* list)
{
	if(list)
	{
		list->next =NULL;
		free((void*)list);
	}
}

//ֻ���������б���ȥ
int insert_packet(T_Service_List **head, T_Service_List* packet)
{
	T_Service_List* phead;
	
	if(packet == NULL && head == NULL)
			return 0;
	phead = *head;
	
	if(phead == NULL)
	{
			*head = packet;//�޸���
			packet->next =NULL;
			return 1;
	}
		
	while(phead->next)
	{
		//printf("next\r\n");
		phead = phead->next;
	}

	packet->next =NULL;
	phead->next = packet;
	return 1;
}

static unsigned char _calculate_check_sum(T_Packet *packet)
{
	unsigned char *ppacket = (unsigned char *)packet;
	
	unsigned short i =0;
	unsigned check_sum = 0;
	for(i=0; i<7; i++)
	{
		check_sum ^= ppacket[i];
	}
	for(i=0; i<packet->packet_data_len; i++)
	{
		check_sum ^= packet->data[i];
	}
	return check_sum;
}	

void delete_packet_list(T_Service_List* *manage)
{
	T_Service_List* phead = NULL;
	T_Service_List* pnext;
	
	packet_debug("enter delete_packet_list\r\n");
	if(manage == NULL || *manage == NULL)
		return;

	phead = *manage;
	while(phead)
	{
		pnext = phead->next;
		if(phead->packet.data!=NULL)
		{
			free(phead->packet.data);
			phead->packet.data = NULL;
		}
		service_free(phead);
		phead = pnext;
	}

	packet_debug("exit delete_packet_list\r\n");
	*manage = NULL;
}

//成功返回1，失败返回0，   网络错误返回 -1
static T_Service_List* _prepare_send_packet(unsigned char type, char *data, unsigned int len)
{
	unsigned int left_size = 0;
	int index=0;
	T_Service_List* head =NULL;
	T_Service_List* service_list =NULL;

	if(data == NULL)
		return 0;
	//PACK_INFO("send packet size=%d",len);
	left_size = len;
	while(left_size>0)
	{
		service_list = service_malloc();
		set_packet_Head(&service_list->packet.packet_head);
		service_list->packet.packet_id = index;
		service_list->packet.packet_num  = index+1;
		service_list->packet.packet_type = type;
		if(!(left_size/PACKET_DATA_LEN))
		{
			service_list->packet.data = (char*)malloc(left_size);
			memset(service_list->packet.data, 0, left_size);
			service_list->packet.packet_data_len = left_size;
			//service_list->packet.packet_data_len = htons(service_list->packet.packet_data_len);
			memcpy(service_list->packet.data , data+index*PACKET_DATA_LEN, service_list->packet.packet_data_len);
			left_size = 0;
		}
		else
		{
			service_list->packet.data = (char*)malloc(PACKET_DATA_LEN);
			service_list->packet.packet_data_len = PACKET_DATA_LEN;
			memcpy(service_list->packet.data , data+index*PACKET_DATA_LEN,PACKET_DATA_LEN);
			left_size -= PACKET_DATA_LEN;
		}

		//PACK_INFO("id=%d num=%d data_len=%d",service_list->packet.packet_id,service_list->packet.packet_num,service_list->packet.packet_data_len);
		service_list->packet.check_sum = _calculate_check_sum(&service_list->packet);
		service_list->packet.packet_tail = PACK_TAIL;
		service_list->next = NULL;
		insert_packet(&head, service_list);

		index++;
	}

	return head;
}

int _send_packet(T_Packet *packet)
{
	int ret,retry = RETRY_TIMES;
	char *buf=NULL;
	int buf_size=0;
	int size_have_send=0;
	int size_need_send=0;
	int i=0;

	buf_size = packet->packet_data_len + 10;
	buf = (char*)malloc(buf_size);
	if(buf==NULL)
	{
		PACK_ERR("malloc failed for send buf, size=%d",buf_size);
		return -1;
	}
	buf[0] = packet->packet_head>>8 & 0xff;
	buf[1] = packet->packet_head & 0xff;
	buf[2] = packet->packet_type;
	buf[3] = packet->packet_num;
	buf[4] = packet->packet_id;
	buf[5] = packet->packet_data_len>>8 & 0xff;
	buf[6] = packet->packet_data_len&0xff;
	memcpy(buf+7, packet->data, packet->packet_data_len);
	buf[7+packet->packet_data_len] = packet->check_sum;
	buf[7+packet->packet_data_len+1] = (packet->packet_tail>>8)&0xff;
	buf[7+packet->packet_data_len+2] = packet->packet_tail&0xff;
#if 0//test
	printf("send %d[", buf_size);
	for(i=0; i<buf_size; i++)
	{
		if(i!=0 && i%16==0)
			printf("\n");
		printf("%02x ", buf[i]);
	}
	printf("]\n");
#endif//end test
	size_need_send = buf_size;
send_again:
	ret = client_tcp_send(buf+size_have_send, size_need_send);
	if(ret <= 0)
	{
		PACK_INFO("send failed, ret=%d", ret);
		free(buf);
		return ret;
	}
	else
	{
		if(ret == size_need_send)
		{
			free(buf);
			return 1;
		}
		else
		{
			PACK_INFO("only send %d bytes", ret);
			size_have_send += ret;
			size_need_send -= ret;
			if(retry > 0)
			{
				retry--;
				goto send_again;
			}
			else
			{
				PACK_INFO("send failed");
				free(buf);
				return 0;
			}
		}
	}

	return 1;
}


static int _send_service_list(T_Service_List* list)
{
	int ret =1;

	while(list)
	{
		ret = _send_packet(&list->packet);
		if(ret <= 0)
			break;
		list = list->next;
	}

	return ret;
}


//进行数据包的校验，校验成功返回1 否则返回0
//异或校验
static int _checkSum(T_Packet *packet)
{
	unsigned char i =0;
	unsigned check_sum = 0;

	if(packet==0 || !isPacketHead(&packet->packet_head) || !isPacketTail(&packet->packet_tail)){

		PACK_ERR("packet=0x%x packet_head =0X%X packet_tail=0X%X",packet,packet->packet_head,packet->packet_tail);
		return 0;
	}

	check_sum = _calculate_check_sum( packet);

	if(check_sum == packet->check_sum)
		return 1;
	else
	{
		PACK_ERR("check_sum=%d , packet->check_sum=%d",check_sum,packet->check_sum);
		return 0;
	}
}


//return:
//1=收到了一个数据包
//0=没有收到一个包或数据出错
//-1=网络异常
//-2=checksum error
int _receive_Onepacket(T_Packet *packet)
{
	int ret =0,retry = RETRY_TIMES;
	char  buf[32];
	unsigned short head;

read_head:
	ret = client_tcp_recv(buf, sizeof(head));
	if(ret <= 0)
	{
		//PACK_INFO("recv ret=%d", ret);
		return ret;
	}
	//PACK_INFO("Head=0x%02x 0x%02x", buf[0], buf[1]);
	if(ret != sizeof(head))
	{
		PACK_ERR("ret=%d sizeof(head)=%d", ret, sizeof(head));
		return 0;
	}
	head = (buf[0]<<8)|buf[1];
	if(!isPacketHead(&head))
	{
		PACK_ERR("Head not found, head=0x%02x",head);
		goto read_head;
	}
	packet->packet_head = head;
//read 2
	ret = client_tcp_recv(buf, 5);//type+num+id+len
	//PACK_INFO("read type+num+id+len ret=%d",ret);
	if(ret <= 0)
	{
		return ret;
	}
	//printf("[%02x] [%02x] [%02x] [%02x %02x]\n", buf[0], buf[1], buf[2], buf[3], buf[4]);
	packet->packet_type = buf[0];
	packet->packet_num = buf[1];
	packet->packet_id = buf[2];
	packet->packet_data_len = (buf[3]<<8)|buf[4];

	if(packet->packet_data_len>0)
	{
		packet->data = (char*)malloc(packet->packet_data_len);
		if(packet->data==NULL)
		{
			PACK_ERR("malloc failed for (%d) data", packet->packet_data_len);
			return -1;
		}
		memset(packet->data, 0, packet->packet_data_len);
		ret = client_tcp_recv(packet->data, packet->packet_data_len);
		//PACK_INFO("ret=%d packet_data_len=%d", ret, packet->packet_data_len);
		if(ret <= 0)
		{
			PACK_ERR("read data failed");
			free(packet->data);
			packet->data = NULL;
			return ret;
		}
	}

again:
	ret = client_tcp_recv(buf, 3);//checksum+tail
	//PACK_INFO("ret =%d sizeof(T_Packet) =%d",ret,sizeof(T_Packet));
	if(ret <= 0)
	{
		PACK_ERR("read checksum+tail failed");
		return ret;
	}
	packet->check_sum = buf[0];
	packet->packet_tail = (buf[1]<<8)|buf[2];
	//PACK_INFO("checksum=0x%x tail=0x%x", packet->check_sum, packet->packet_tail);

	if(_checkSum(packet) != 1)
	{
		return -2;
	}

	return 1;
}


int write_data(unsigned char type, char *data, unsigned int len)
{
	int ret ;
	T_Service_List* head = _prepare_send_packet(type,data,len);
	
	ret = _send_service_list(head);
	delete_packet_list(&head);
	
	packet_debug("send_data ret =%d\r\n",ret);
	return ret;
}

enum{
	PACKET_MODE_WRITE=0,
	PACKET_MODE_READ,
};

enum{
	PACKET_STATUS_TIMEOUT =0,
	PACKET_STATUS_IN_USE,
	PACKET_STATUS_NO_USE,
	PACKET_STATUS_COMPLETE,
};

static T_Service_List* packet_manage[MAX_ONLINE_DOWNLOAD]={0};
//
void init_packet_manage()
{
	int i=0;
	
	for(i=0;i<MAX_ONLINE_DOWNLOAD;i++)
	{
		packet_manage[i] = NULL;
	}
}

int isSamePacket(T_Service_List* list1,T_Service_List* list2)
{
	if(list1->packet.packet_type == list2->packet.packet_type)
		return 1;
	else
		return 0;
}

//判断既是第一个也是最后一个包
//也就是说这个包只有一个包组成
int packet_start_end(T_Service_List* packet)
{
	if(packet == NULL)
		return 0;

	if(packet->packet.packet_num == 1)
		return 1;
	else
		return 0;
}

int is_first_packet(T_Service_List* packet)
{
	if(packet->packet.packet_num == 1)
		return 1;
	else
		return 0;
}


int poll_packet(T_Service_List* list)
{
	int i,first_packet = 0;
	
	if(is_first_packet( list ) == 1)
	{
		first_packet =1;
	}

	for(i=0;i < MAX_ONLINE_DOWNLOAD;i++)
	{
		if(first_packet)
		{
			if(packet_manage[i] == NULL)
				return i;
		}
		else
		{
			if(packet_manage[i] && packet_manage[i]->packet.packet_type == list->packet.packet_type)
			{
				return i;
			}
		}			
	}

	return -1;
}

void debug_print_receive_packet(T_Packet *packet)
{
	int i=0;

	printf("\n");
	PACK_INFO("head=0x%04x type=0x%02x num=0x%02x id=0x%02x size=0x%04x",\
			packet->packet_head, packet->packet_type, packet->packet_num, packet->packet_id, packet->packet_data_len);
	printf("data{");
	for(i=0;i<packet->packet_data_len;i++)
	{
		if(i/16&&i!=0)
			printf("\n");
		printf("%02x ", packet->data[i]);
	}
	printf("}\n");
	PACK_INFO("checksum=0x%02x tail=0x%04x",packet->check_sum, packet->packet_tail);
	printf("\n");
}

//return ret:
//>0读到数据
//0=无数据
//-1=网络异常
//-2=checksum error
int	read_data(int *type, unsigned char *packet_num, unsigned char *packet_id, char *data, unsigned int *len)
{	
	static T_Service_List static_packet;
	T_Service_List* list = NULL;
	int i=0,size =0,insert_postion=-1;
	
	static_packet.next = NULL;

	i = _receive_Onepacket(&static_packet.packet);
	if(i <= 0)
	{
		return i;
	}

	*type = -1;
	*len  = 0;

	//debug_print_receive_packet(&static_packet.packet);

	if(packet_start_end( &static_packet) == 1)
	{
		goto read_data_one;
	}

copy:
	list = service_malloc();
	if(list)
		memcpy(list,&static_packet,sizeof(T_Service_List));
	else
		return 0;
	list->next = NULL;

	//printf("packet num =%d,len=%d \r\n",list->packet.packet_num,list->packet.packet_data_len);

	insert_postion = poll_packet( list);
	if(insert_postion >= 0)
	{
		insert_packet(&packet_manage[insert_postion], list);//packet_manage[i]    OR     packet_manage[insert_postion]--zyf
		if(list->packet.packet_id == list->packet.packet_num-1)
		{
			goto read_data;
		}
		return 0;
	}

	service_free(list);
	return 0;
	
read_data_one:
	//PACK_INFO("Only one packet.");
	*type  = static_packet.packet.packet_type;
	*packet_num = static_packet.packet.packet_num;
	*packet_id = static_packet.packet.packet_id;
	size = static_packet.packet.packet_data_len;
	memcpy(data,static_packet.packet.data,size);
	*len = size;
	return size;
	
read_data:
	//PACK_INFO("Have several packets.");
	list = packet_manage[insert_postion];
	
	*type = list->packet.packet_type;
	*packet_num = static_packet.packet.packet_num;
	*packet_id = static_packet.packet.packet_id;
	while(list)
	{
		memcpy( data+size ,list->packet.data , list->packet.packet_data_len);
		size += list->packet.packet_data_len;
		//printf("packet_id =%d,len=%d packet_len =%d\r\n",head->packet.packet_id,size,head->packet.packet_data_len);
		list = list->next;
	}
	
	//delete_packet_list(&packet_manage[i]);
	delete_packet_list(&packet_manage[insert_postion]);
	*len = size;
	return size;
}

