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

void wait_fork(int nforks){
	int i;
	for (i = 0; i < nforks; i++){
		wait(NULL);
	}
}

ssize_t my_recv(int socket, void *buffer, size_t len){
	int count_r;
	while(1){
		if ((count_r = recv(socket, buffer, len, 0)) < 0){
			if (errno == EINTR){
				continue;
			}
			close(socket);
			perror("recv: ");
			exit(2);
		}else{
			break;
		};
	}
	return count_r;
}

void my_send(int socket, const void *buffer, size_t len){
	while(1){
		if (send(socket, buffer, len, 0) < 0){
			if (errno == EINTR){
				continue;
			}
			close(socket);
			perror("send: ");
			exit(2);
		}else{
			break;
		};
	}
}


int main(){	
	struct hostent *hp, *host_entry;
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
	int nforks = 0;
	char szHostName[255];
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
		close(s);
    exit(2);
  };  
  if (listen(s, 10) < 0){
    perror("listen");
		close(s);
    exit(2);
  };
	printf("Waiting for connections...\n");
	while(1){
		size_accept = sizeof(client_addr);
		bzero(&client_addr, size_accept);
		size_client = sizeof(client_addr);
		printf("lol\n");
    if ((client_s = accept(s, (struct sockaddr *)&client_addr, &size_client)) < 0) {
			perror("accept");
			wait_fork(nforks);
			close(s);
			exit(2);
		}
		printf("Connected:\nIP: %lu\nPort: %hu\n=====\n", (unsigned long) client_addr.sin_addr.s_addr, htons(client_addr.sin_port));
		if ((pid = fork()) < 0){
			perror("fork");
			wait_fork(nforks);
			close(s);
			exit(2);
		}
		printf("forked\n");
		nforks++;
		if (pid == 0){
/*			close(s);*/
			/*receiving version and number of methods of auth*/
			count_r = my_recv(client_s, &buf, BUF_SIZE);
			printf("%d: Received msg:\nversion: %d, number of auth: %d\nsize: %d===\n", getpid(), buf[0], buf[1], count_r);
			if (buf[0] != 0x05 || count_r < 3){
				buf[0] = 0x05;
				buf[1] = 0xFF;
				my_send(client_s, buf, 2);
				close(client_s);
				exit(0);
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
				printf("found.");
				my_send(client_s, buf, 2);
				printf(" sent.\n");
			}else{
				printf("Not found. \n");
				buf[0] = 0x05;
				buf[1] = 0xFF;
				my_send(client_s, buf, 2);
				close(client_s);
				exit(0);
			}
			printf("%d: Starting connection...\n", getpid());
			/*connection*/
			bzero(&dst, sizeof(dst));
			count_r = my_recv(client_s, &dst, 4);
			printf("%d: Dst received\nver: %hd, cmd: %hd, rsv: %hd, atype: %d\n", getpid(), dst.ver, dst.cmd, dst.rsv, dst.atype);
			switch(dst.atype){
				case 0x01: /*IPv4*/
					my_recv(client_s, &dst.addr, BUF_SIZE);
					break;
				case 0x03: /*hostname*/
					my_recv(client_s, &hostname_size, 1);
					printf("size: %d\n", hostname_size);
					hostname = (char *) malloc(hostname_size * sizeof(char));
					count_r = my_recv(client_s, hostname, hostname_size);
					if (count_r != hostname_size){
						printf("Wrong size of hostname(%d). count_r = %d\n", hostname_size, count_r);
					} 
					count_r = my_recv(client_s, &dst.port, 2);
					printf("port: %d\n", htons(dst.port));
					if (count_r < 2){
						printf("! No port.");
						buf[0] = 0x05;
						buf[1] = 0x07;
						my_send(client_s, &buf, 2);
						close(client_s);
						exit(0);
					}
					if ((hp = gethostbyname(hostname)) == 0){
						perror("gethostbyname(): ");
						buf[0] = 0x05;
						buf[1] = 0x07;
						my_send(client_s, &buf, 2);
						close(client_s);
						exit(2);
					}
					bzero(&dst.addr, sizeof(dst.addr));
					bcopy(hp->h_addr,&dst.addr,hp->h_length);
					printf("address: %u", (unsigned int) dst.addr);
					dst.atype = 1;
					free(hostname);
					break;
				case 0x04: /*IPv6*/
					printf("Error: IPv6\n");
					buf[0] = 0x05;
					buf[1] = 0x08;
					my_send(client_s, &buf, 2);
					close(client_s);
					exit(0);
				default:
					printf("atype error\n");
					buf[0] = 0x05;
					buf[1] = 0x07;
					my_send(client_s, &buf, 2);
					close(client_s);
					exit(0);
			}
			printf("%d: Receiving connection:\nver: %hd, cmd: %hd, rsv: %hd\natype: %d\n addr: %u, port: %d\n", 
							getpid(), dst.ver, dst.cmd, dst.rsv, dst.atype, (unsigned int)(dst.addr), htons(dst.port));
			if (dst.ver != 0x05 || dst.cmd != 0x01 || dst.atype != 0x01){
				buf[0] = 0x05;
				buf[1] = 0x07;
				my_send(client_s, &buf, 2);
				true_exit(0);
			}
			printf("%d: Connection received.\n", getpid());
			host_addr.sin_family = AF_INET;
			host_addr.sin_port = dst.port;
			host_addr.sin_addr.s_addr = dst.addr;
			bnd.ver = 0x05;
			bnd.rsv = 0x00;
			bnd.atype = 0x01;
			gethostname(szHostName, 255);
			host_entry = gethostbyname(szHostName);
			bzero(&bnd.addr, sizeof(bnd.addr));
			bcopy(host_entry->h_addr, &bnd.addr, host_entry->h_length);
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
					my_send(client_s, &bnd, sizeof(bnd));
					close(client_s);
					exit(0);
				}else{
					break;
				}
			}
			bnd.cmd = 0x00;
			printf("%d: Connection accepted!\n", getpid());
			my_send(client_s, &bnd, sizeof(bnd));
			printf("\n%d: Starting work...\n", getpid());
			/*connection resolved. Started Work*/
			
			
			while(1){
				printf("%d: Reading...", getpid());
				fl = 0;
				while ((count_r = my_recv(client_s, &buf, BUF_SIZE)) == BUF_SIZE){	
					printf("\nFrom client to host=========\n");
					write(1, buf, count_r);
					printf("\n=====\n");
					printf("%d: Read - %d.\n", getpid(), count_r);
					send(host_s, buf, count_r, 0);
					printf("Sent to Host.\n");
					fl = 1;
					bzero(&buf, BUF_SIZE);
				}
				
				if (fl == 0 && count_r == 0){
					/*Заканчиваем когда откуда-нибудь получили EOF...*/
					printf("EXIT.\n");
					break;
				}else{
					printf("\nFrom client to host=========\n");
					write(1, buf, count_r);
					printf("\n=====\n");
					printf("%d: Read - %d.\n", getpid(), count_r);
					my_send(host_s, buf, count_r);
					printf("Sent to Host.\n");
					fl = 1;
					bzero(&buf, BUF_SIZE);
				}
				printf("%d: Sent. Receiving.\n", getpid());
				fl = 0;
				
				while ((count_r = my_recv(host_s, &buf, BUF_SIZE)) > 0){
					fl = 1;
					printf("\nFrom host to client=========\n%s\n===========\n", buf);
					printf("%d: Read %d.\n", getpid(), count_r);
					my_send(client_s, &buf, count_r);
					printf("Sent to Client.\n");
					bzero(&buf, BUF_SIZE);
				}

				if (fl == 0 && count_r == 0){
					/*Заканчиваем когда откуда-нибудь получили EOF...*/
					/*close socket*/
					printf("EXIT.\n");
					break;
				}
			}
			close(client_s);
			close(host_s);
			exit(0);
		}	
  }
	for (i = 0; i < nforks; i++){
		wait(NULL);
	}
}
