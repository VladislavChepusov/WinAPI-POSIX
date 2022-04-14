#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//result client

int client(int argc, char* argv[])
{
 
 if(argc !=3){
	perror("Error:Invalid number of arguments!");
	return  1;
}

 if(inet_addr(argv[2]) == INADDR_NONE)
{
	perror("Error:Invalid value for IP!");
	return 2;
}

 if(atoi(argv[1]) == 0)
{
	perror("Error:Invalid value for Port!");
	return 2;
}

 if(atoi(argv[1])>49151||atoi(argv[1])<1024)
{
	perror("Error:The value is not in the user port interval!");
	return 3;
}

 
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
//SOCK_STREAM-способ передачи данных по сети
//0, что соответствует протоколу по умолчанию.
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;//Internet-домен//Семейство адресов
    addr.sin_port = htons(atoi(argv[1])); //Номер порта
    addr.sin_addr.s_addr = inet_addr(argv[2]);//IP-адрес


  
//tut povotor podkl 
//установления соединения
//sock-сокет, который будет использоваться для обмена данными с сервером
//serv_addrсодержит указатель на структуру с адресом сервера, а addrlen - длину этой структуры
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
{
	printf("no connection..\n");
 	//_exit(2);
	return 4;		 
}
 
 


//send Здесь sockfd - это, как всегда, дескриптор сокета, через который происходит обмен данными, msg- указатель на буфер с данными, len - длина буфера в байтах, а flags - набор битовых флагов, управляющих работой функции (если флаги не используются, в качестве значения этого параметра функции следует передать 0).
   char sendbuf[32] = "";
   char sendbufpassword[32] = "";
   char recvbuf[64] = "";
   printf("Enter login: ");
 //  scanf("%s", sendbuf);
   printf("Enter password: ");
 //  scanf("%s", sendbufpassword);
   send( sock, sendbuf, strlen(sendbuf), 0 );
   send( sock, sendbufpassword, 10, 0 );
   recv( sock, recvbuf, 64, 0 );
   char * token = strtok(recvbuf, "$");
   printf( "Server answer: %s\n", token);
  // close(sock);
   return 0;
}
