#include <sys/types.h>
#include <sys/socket.h>
#define PORTNUM 1500
#define BUF_SIZE 1024
void true_exit(int a){
	exit(a);
}

int main(){
	int pid;
	int size_accept, size, addr_size, count_r;
  int s, nport = PORTNUM;
  struct sockaddr_in serv_addr, client_addr, host_addr;
	struct sock_connection{
		char ver;
		char cmd;
		char rsv;
		char atype;
		in_addr_t addr;
		short port;
	} bnd, dst;
	char buf[1024];
	int fl;
	
  nport = htons((u_short) nport);
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.fin_family = AF_INET;
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
  
	while(1){
		size_accept = sizeof(client_addr);
		bzero(&client_addr, size_accept);
    if ((client_s = accept(s, (struct sockaddr *)&client_addr, &size_accept)) < 0) {
			if (errno == EINTR){
				continue;
			}
			perror("accept");
			true_exit(2);
		}
		if ((pid = fork()) < 0){
			perror("fork");
			true_exit(2);
		}
		
		if (pid == 0){
			recv(client_s, &buf, 2, MSG_WAITALL);
			if (buf[0] != 0x05){
				buf[0] = 0x05;
				buf[1] = 0xFF;
				send(client_s, buf, 2, 0);
				true_exit(0);
			}
			size = buf[1];
			recv(client_s, &buf, size, MSG_WAITALL);
			fl = 0;
			for (i = 0; i < size; i++){
				if (buf[i] == 0x00){
					fl = 1;
					break;
				}
			}
			if (fl){
				buf[0] = 0x05;
				buf[1] = 0x00;
				send(client_s, buf, 2, 0);
			}else{
				buf[0] = 0x05;
				buf[1] = 0xFF;
				send(client_s, buf, 2, 0);
				true_exit(2);
			}
			
			/*connection*/
			recv(client_s, &dst, sizeof(dst), MSG_WAITALL);
			if (dst.ver != 0x05 || dst.cmd != 0x01 || dst.atype != 0x01){
				buf[0] = 0x05;
				buf[1] = 0x07;
				send(client_s, &buf, 2, 0);
				true_exit(0);
			}
			
			host_addr.sin_family = AF_INET;
			host_addr.sin_port = htons(dst.port);
			host_addr.in_addr.sin_addr = dst.addr;
			bnd.ver = 0x05;
			bnd.rsv = 0x00;
			bnd.atype = 0x01;
			bnd.addr = dst.addr;
			bnd.port = dst.port;
			if ((host_s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		    perror("socket");
		    true_exit(0);
		  }; 
			
			while (1){		  
				if (connect(host_s, &host_addr, sizeof(host_addr)) < 0){
					switch(errno){
						case (ENETDOWN || ENETUNREACH) :
							bnd.cmd = 0x03;
							break;
						case (EADDRNOTAVAIL || EHOSTUNREACH) : 
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
					send(client_s, &bnd, sizeof(bnd), 0);
					true_exit(0);
				}else{
					break;
				}
			}
			bnd.cmd = 0x00;
			send(client_s, &bnd, sizeof(bnd), 0);
			/*connection resolved.*/
			while(1){
				while(1){
					if ((count_r = recv(client_s, &buf, BUF_SIZE, 0)) < 0){
						switch (errno){
							case EINTR : continue;
							
						}
					}
				}
				if (count_r == 0){
					/*Заканчиваем когда откуда-нибудь получили EOF...*/
					/*close socket*/
					break;
				}
				send(host_s, &buf, count_r, 0);
				if ((count_r = recv(host_s, &buf, BUF_SIZE, 0)) < 0){
						
				}
				if (count_r == 0){
					/*Заканчиваем когда откуда-нибудь получили EOF...*/
					/*close socket*/
					break;
				}
				send(client_s, &buf, count_r, 0);
			}
		}
  }
}
