 #include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
//result exoserver
   int main()
       {
	int sock, listener;
        struct sockaddr_in addr;
	char buf[1024]="test";
	int bytes_read;
	listener = socket(AF_INET, SOCK_STREAM, 0);

       if(listener < 0)
       {
	perror("socket");
	exit(1);
       }

	addr.sin_family = AF_INET;
	addr.sin_port = htons(3333);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
	perror("bind");
	exit(2);
	}

	listen(listener, 1);

while(1)
{
sock = accept(listener, NULL, NULL);

if(sock < 0)
{
perror("accept");
exit(3);
}
 
while(1){
 bytes_read = recv(sock, buf, 1024, 0);
 if(bytes_read <= 0) 
 break;
send(sock, buf, bytes_read, 0);
}
 
//close(sock);
}
return 0;
}
