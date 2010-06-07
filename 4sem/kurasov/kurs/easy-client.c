#include <stdio.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORTNUM 1080
#define BUF_SIZE 1024


/*easy client*/
int main(int argc, char **argv){
	int socks_s, count_r;
	struct sockaddr_in socks_addr;
	u_char buf[BUF_SIZE];
	char buff[BUF_SIZE] = "GET / HTTP/1.1\nHost: google.ru\nUser-Agent: Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.5; en-US; rv:1.9.1.9) Gecko/20100315 Firefox/3.5.9 GTB7.0\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\nAccept-Language: ru,en-us;q=0.7,en;q=0.3\nAccept-Charset: windows-1251,utf-8;q=0.7,*;q=0.7\nKeep-Alive: 300\nProxy-Connection: keep-alive\r\n\r\n";
	struct sock_connection{
		u_char ver;
		u_char cmd;
		u_char rsv;
		u_char atype;
		in_addr_t addr;
		u_short port;
	} bnd, dst;
	struct hostent * hp;
	
	if ((socks_s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("socket");
    exit(0);
  };

	
	if ((hp = gethostbyname(argv[1])) == 0){
		perror("gethostbyname(): ");
		exit(2);
	}
	
	bzero(&socks_addr,sizeof(socks_addr));
	bcopy(hp->h_addr,&socks_addr.sin_addr,hp->h_length);
	socks_addr.sin_family = hp->h_addrtype;
	socks_addr.sin_port = htons(atoi(argv[2]));	
	
	if (connect(socks_s, (struct sockaddr *)&socks_addr, sizeof(socks_addr)) < 0){
		perror("connect1: ");
		exit(0);
	};
	buf[0] = 0x05;
	buf[1] = 0x01;
	buf[2] = 0x00;
	send(socks_s, &buf, 3, 0);
	count_r = recv(socks_s, &buf, 2, 0);
	printf("count_recv: %d\n", count_r);
	
	if ((hp = gethostbyname(argv[3])) == 0){
		perror("gethostbyname(): ");
		exit(2);
	}
	bcopy(hp->h_addr, &bnd.addr, hp->h_length);
	bnd.ver = 0x05;
	bnd.cmd = 0x01;
	bnd.rsv = 0x00;
	bnd.atype = 0x01;
	bnd.port = htons(80);
	send(socks_s, &bnd, sizeof(bnd), 0);
	
	count_r = recv(socks_s, &dst, sizeof(dst), 0);
	if (dst.cmd == 0x00){
		printf("All good.\n");
		send(socks_s, buff, strlen(buff), 0);
		printf("Received: ============\n");
		while ((count_r = recv(socks_s, &buff, BUF_SIZE, 0)) == BUF_SIZE){
			printf("%s", buff);
		};
		printf("%s", buff);
		printf("\n=====\n");
		printf("count_r: %d\n", count_r);
	}	
	return 0;
}














