#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
#define PORT 1234
 
int main(void){
    int sock, client_sock;
    struct sockaddr_in addr, client_addr;
    char buffer[1024];
    char s1[10];
    int len, addr_len, recv_len;
 
    if((sock = socket(AF_INET, SOCK_STREAM, 0))<0){
        perror("socket ");
        return 1;
    }
 
    memset(&s1, 0x00, sizeof(s1));
    memset(&addr, 0x00, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
 
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("bind ");
        return 1;
    }
 
    if(listen(sock, 5) < 0){
        perror("listen ");
        return 1;
    }
 
    addr_len = sizeof(client_addr);
 
    printf("waiting for clinet..\n");
 
    while((client_sock = accept(sock, (struct sockaddr *)&client_addr, &addr_len)) > 0){
        printf("clinet ip : %s\n", inet_ntoa(client_addr.sin_addr));
        
	while(1) {
        if((recv_len = recv(client_sock, buffer, 1024, 0)) < 0){
            perror("recv ");
            close(client_sock);
            return 1;
            break;
        }
		
	if( recv_len <= 0 ) {
            close(client_sock);
	    break;
	}	    

        buffer[recv_len] = '\0';
        printf(". %s\n", buffer);

	if(strncmp(buffer, "2", 1) == 0)
	{
	   system("sh audio2_enc.sh");
	}
	else if(strncmp(buffer, "3", 1) == 0 )
	{
	   system("sh audio3_enc.sh");
	}
        else if(strncmp(buffer, "quit", 4) == 0)
        {
           break;
        }

	
 	}
        close(client_sock);
	printf("client leave \n");

	scanf("%s", s1);
	if(strncmp(s1, "end", 3) == 0)
	{
	   memset(&s1, 0x00, sizeof(s1));
	   break;
        }
    }

    printf("server end \n");
    close(sock);
    return 0;
}

