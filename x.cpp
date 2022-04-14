#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  int sock;
  struct sockaddr_in addr;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  // SOCK_STREAM-способ передачи данных по сети
  // 0, что соответствует протоколу по умолчанию.
  if (sock < 0) {
    perror("socket");
    exit(1);
  }

  addr.sin_family = AF_INET; // Internet-домен//Семейство адресов
  addr.sin_port = htons(atoi(argv[1]));      //Номер порта
  addr.sin_addr.s_addr = inet_addr(argv[2]); // IP-адрес

  //установления соединения
  // sock-сокет, который будет использоваться для обмена данными с сервером
  // serv_addrсодержит указатель на структуру с адресом сервера, а addrlen -
  // длину этой структуры
  if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    printf("no connection..\n");
    exit(2);
  }
  //После того как соединение установлено, можно начинать обмен данными. Для
  //этого используются функции send и recv . send Здесь sockfd - это, как
  // всегда, дескриптор сокета, через который происходит обмен данными, msg-
  // указатель на буфер с данными, len - длина буфера в байтах, а flags - набор
  // битовых флагов, управляющих работой функции (если флаги не используются, в
  // качестве значения этого параметра функции следует передать 0).
  char sendbuf[32] = "";
  char sendbufpassword[32] = "";
  char recvbuf[64] = "";
  printf("Enter login: ");
  scanf("%s", sendbuf);
  printf("Enter password: ");
  scanf("%s", sendbufpassword);
  send(sock, sendbuf, strlen(sendbuf), 0);
  send(sock, sendbufpassword, 10, 0);
  recv(sock, recvbuf, 64, 0);
  char *token = strtok(recvbuf, "$");
  printf("Server answer: %s\n", token);
  close(sock);
  return 0;
}
