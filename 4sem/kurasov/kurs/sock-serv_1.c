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

void true_exit(int a){
	exit(a);
}

int main(){	
	int pid;
	int size_accept, size, count_r;
  int s, nport, client_s, host_s;
  struct sockaddr_in serv_addr, client_addr, host_addr;
	struct sock_connection{
		u_char ver;
		u_char cmd;
		u_char rsv;
		u_char atype;
		in_addr_t addr;
		u_short port;
	} bnd, dst;
	int hostname_size;
	u_char buf[BUF_SIZE];
	int fl, i;
	socklen_t size_client;
	char * hostname;
	int fd, fd1;
	fd = open("client.txt", O_WRONLY | O_CREAT | O_TRUNC);
	fd1 = open("host.txt", O_WRONLY | O_CREAT | O_TRUNC);
  nport = htons((u_short) PORTNUM);
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = nport;
  
  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("socket");
    exit(2);
  };
  if (bind(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
    perror("bind");
    exit(2);
  };  
  if (listen(s, 5) < 0){
    perror("listen");
    exit(2);
  };
	printf("Waiting for connections...\n");
	while(1){
		size_accept = sizeof(client_addr);
		bzero(&client_addr, size_accept);
		size_client = sizeof(client_addr);
    if ((client_s = accept(s, (struct sockaddr *)&client_addr, &size_client)) < 0) {
			if (errno == EINTR){
				continue;
			}
			perror("accept");
			true_exit(2);
		}
		printf("Connected:\nIP: %lu\nPort: %hu\n=====\n", (unsigned long) client_addr.sin_addr.s_addr, htons(client_addr.sin_port));
		if ((pid = fork()) < 0){
			perror("fork");
			true_exit(2);
		}
		if (pid == 0){
			/*receiving version and number of methods of auth*/
			count_r = recv(client_s, &buf, BUF_SIZE, 0);
			printf("%d: Received msg:\nversion: %d, number of auth: %d\nsize: %d===\n", getpid(), buf[0], buf[1], count_r);
			if (buf[0] != 0x05){
				buf[0] = 0x05;
				buf[1] = 0xFF;
				send(client_s, buf, 2, 0);
				true_exit(0);
			}
			size = buf[1];
			/*looking auths*/
			printf("%d: Received versions of auth:\n", getpid());
			for (i = 2; i < 2 + size; i++){
				printf("%d: auth%d: %d\n", getpid(), i, buf[i]);
			}
			printf("%d: ====\n", getpid());
			fl = 0;
			/*is there a 'without auth' ?*/
			printf("%d: Finding 'without auth'...", getpid());
			for (i = 2; i < 2 + size; i++){
				if (buf[i] == 0x00){
					fl = 1;
					break;
				}
			}
			
			if (fl){
				/*there is.*/
				buf[0] = 0x05;
				buf[1] = 0x00;
				printf("found. \n");
				send(client_s, buf, 2, 0);
				printf("sent.\n");
			}else{
				printf("Not found. \n");
				buf[0] = 0x05;
				buf[1] = 0xFF;
				send(client_s, buf, 2, 0);
				true_exit(2);
			}
			printf("%d: Starting connection...\n", getpid());
			/*connection*/
			bzero(&dst, sizeof(dst));
			count_r = recv(client_s, &dst, 4, 0);
			printf("%d: Dst received\nver: %hd, cmd: %hd, rsv: %hd, atype: %d\n", getpid(), dst.ver, dst.cmd, dst.rsv, dst.atype);
			switch(dst.atype){
				case 0x01: /*IPv4*/
					recv(client_s, &dst.addr, BUF_SIZE, 0);
					break;
				case 0x03: /*hostname*/
					recv(client_s, &hostname_size, 1, 0);
					printf("size: %d\n", hostname_size);
					hostname = (char *) malloc((hostname_size + 1) * sizeof(char));
					count_r = recv(client_s, hostname, hostname_size, 0);
					
					if (count_r != hostname_size){
						printf("Wrong size of hostname(%d). count_r = %d\n", hostname_size, count_r);
					} 
					count_r = recv(client_s, &dst.port, 2, 0);
					printf("port: %d\n", htons(dst.port));
					if (count_r < 2){
						printf("! No port.");
					}
					dst.addr = inet_addr(hostname);
					printf("address: %u", (unsigned int) dst.addr);
					dst.atype = 1;
					break;
				case 0x04: /*IPv6*/
					printf("Sorry, we dont work with IPv6\n");
					true_exit(0);
					break;
				default:
				printf("atype error\n");
				true_exit(0);
			}
			printf("%d: Receiving connection:\nver: %hd, cmd: %hd, rsv: %hd\natype: %d\n addr: %u, port: %d\n", 
							getpid(), dst.ver, dst.cmd, dst.rsv, dst.atype, (unsigned int)(dst.addr), htons(dst.port));
			if (dst.ver != 0x05 || dst.cmd != 0x01 || dst.atype != 0x01){
				buf[0] = 0x05;
				buf[1] = 0x07;
				send(client_s, &buf, 2, 0);
				true_exit(0);
			}
			printf("%d: Connection received.\n", getpid());
			host_addr.sin_family = AF_INET;
			host_addr.sin_port = dst.port;
			host_addr.sin_addr.s_addr = dst.addr;
			bnd.ver = 0x05;
			bnd.rsv = 0x00;
			bnd.atype = 0x01;
			bnd.addr = inet_addr("127.0.0.1");
			bnd.port = htons(PORTNUM);
			if ((host_s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		    perror("socket");
		    true_exit(0);
		  }; 
			while (1){	 
				printf("\n%d: Connecting remote host...\n", getpid());
				if (connect(host_s, (struct sockaddr *)&host_addr, (socklen_t) sizeof(host_addr)) < 0){
					switch(errno){
						case ENETDOWN :
							bnd.cmd = 0x03;
							break;
						case ENETUNREACH :
							bnd.cmd = 0x03;
							break;
						case EADDRNOTAVAIL : 
							bnd.cmd = 0x04;
							break;
						case EHOSTUNREACH :
							bnd.cmd = 0x04;
							break;
						case ECONNREFUSED :
							bnd.cmd = 0x05;
							break;
						case ETIMEDOUT : 
							bnd.cmd = 0x06;
							break;
						case EINTR : continue;
						default :
						 bnd.cmd = 0x01;
					}
					printf("%d: Error: bnd.cmd %d\n", getpid(), bnd.cmd);
					send(client_s, &bnd, sizeof(bnd), 0);
					true_exit(0);
				}else{
					break;
				}
			}
			bnd.cmd = 0x00;
			printf("%d: Connection accepted!\n", getpid());
			send(client_s, &bnd, sizeof(bnd), 0);
			printf("\n%d: Starting work...\n", getpid());
			/*connection resolved. Started Work*/
			
			
			while(1){
				printf("%d: Reading...", getpid());
				fl = 0;
				while(1){
					bzero(&buf, BUF_SIZE);
					if ((count_r = recv(client_s, &buf, BUF_SIZE, 0)) < 0){
						switch (errno){
							case EINTR : continue;
						}
						perror("recv1");
						true_exit(2);
					}
					
					if (count_r == BUF_SIZE){
						printf("\nFrom client to host=========\n%s\n===========\n", buf);
						write(fd, &buf, count_r);
						printf("%d: Read - %d.\n", getpid(), count_r);
						send(host_s, buf, count_r, 0);
						printf("Sent to Host.\n");
						fl = 1;
						continue;
					}else{
						printf("\nFrom client to host=========\n%s\n===========\n", buf);
						write(fd, &buf, count_r);
						printf("%d: Read - %d.\n", getpid(), count_r);
						send(host_s, buf, count_r, 0);
						printf("Sent to Host.\n");
						break;
					}
				}
				if (fl == 0 && count_r == 0){
					/*Заканчиваем когда откуда-нибудь получили EOF...*/
					/*close socket*/
					printf("EXIT.\n");
					true_exit(0);
					break;
				}
				printf("%d: Sent. Receiving.\n", getpid());
				fl = 0;
				count_r = BUF_SIZE;
				bzero(&buf, BUF_SIZE);
				while ((count_r = recv(host_s, &buf, BUF_SIZE, 0)) == BUF_SIZE){
					fl = 1;
					printf("\nFrom host to client=========\n%s\n===========\n", buf);
					printf("%d: Read %d.\n", getpid(), count_r);
					send(client_s, &buf, count_r, 0);
					printf("Sent to Client.\n");
					bzero(&buf, BUF_SIZE);
				}
				if (fl == 0 && count_r == 0){
					/*Заканчиваем когда откуда-нибудь получили EOF...*/
					/*close socket*/
					printf("EXIT.\n");
					true_exit(0);
					break;
				}else{
					printf("\nFrom host to client=========\n%s\n===========\n", buf);
					printf("%d: Read - %d.\n", getpid(), count_r);
					send(client_s, &buf, count_r, 0);
					printf("Sent to Client.\n");
				}
				close(fd);
				close(fd1);
			}
			
		}
  }
}
