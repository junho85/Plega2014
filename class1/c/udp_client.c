#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv) {
	int sockfd;
	int i;

	char buf[255];

	struct sockaddr_in serveraddr;

	memset(buf, 0, sizeof(buf));
	
	// join args
	for (i=1; i<argc; i++) {
		if (i != 1) {
			strcat(buf, " ");
		}
		strcat(buf, argv[i]);
	}
 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	int is_broadcast = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &is_broadcast, sizeof(is_broadcast));

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9999);
	serveraddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	sendto(sockfd, (void*)buf, sizeof(buf), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	close(sockfd);
	
	return 0;
}
