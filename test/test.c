#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>

void get_eth0_ip_netmask_broadip(void)
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct ifreq ifr = {0};
	struct sockaddr_in *sock_ip = NULL;
	char ip[18] = {0};
	char netmask[18] = {0};
	char broadcast_ip[18] = {0};
	
	strncpy(ifr.ifr_name, "eth0", strlen("eth0"));
	//get interface info
	if(ioctl(sock, SIOCGIFADDR, &ifr) < 0){
		perror("hehe1");
		return;
	}
	
	sock_ip = (struct sockaddr_in *)&(ifr.ifr_addr);
	inet_ntop(AF_INET, &sock_ip->sin_addr, ip, 18);

	if(ioctl(sock, SIOCGIFNETMASK, &ifr) < 0)
	{
		perror("hehe2");
		return;
	}
	sock_ip = (struct sockaddr_in *)&(ifr.ifr_addr);
	inet_ntop(AF_INET, &sock_ip->sin_addr, netmask, 18);

	if(ioctl(sock, SIOCGIFBRDADDR, &ifr) < 0)
	{
		perror("hehe3");
		return;
	}

	sock_ip = (struct sockaddr_in *)&(ifr.ifr_broadaddr);
	inet_ntop(AF_INET, &sock_ip->sin_addr, broadcast_ip, 18);
	printf("ifname:%s ip:%s network:%s broadcast ip:%s\n", 
		ifr.ifr_name, ip, netmask, broadcast_ip);
}

int main(void)
{
	get_eth0_ip_netmask_broadip();
	return 0;
}
