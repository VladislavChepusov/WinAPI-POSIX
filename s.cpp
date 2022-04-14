#include <WinSock2.h>
#include <Windows.h>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <thread>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

// �������� ������(�������)
SOCKET connections[100] = {0};
int index = 0;
int number;
//��������� ��� ����������
struct black_list {
  string IP;
  time_t timeblock;
  int count_error = 0;
};
black_list mylist[6];
//������� �������� �������� ���������
bool database(char x[]) {
  char user1[] = "test@mail.ruqwerty1";
  char user2[] = "test2@mail.ruqwerty2";
  ;
  char user3[] = "test3@mail.ruqwerty3";
  ;
  if (strcmp(x, user1) == 0) {
    return true;
  } else if (strcmp(x, user2) == 0) {
    return true;
  } else if (strcmp(x, user3) == 0) {
    return true;
  } else
    return false;
}

void Thread(int c) {
  LONG64 s;
  char recvbuf[32] = "";
  char recvbuf2[32] = "";
  recv(connections[c], recvbuf, 32, 0);
  recv(connections[c], recvbuf2, 32, 0);
  // recv(connections[c], recvbuf2, 32, 0);

  std::cout << "Client login: " << recvbuf << std::endl;
  std::cout << "Client password: " << recvbuf2 << std::endl;
  strcat(recvbuf, recvbuf2);
  bool db = database(recvbuf);
  //   cout <<"result="<< db  <<endl ;

  if (db == true) {

    char sendbuf[64] = "Welcome again";
    send(connections[c], sendbuf, strlen(sendbuf), 0);
    //   cout << "number=" << number << endl;
    mylist[number].count_error = 0;

  } else {
    //   cout << "number=" << number << endl;
    char sendbuf[64] = "wrong login or password";
    send(connections[c], sendbuf, strlen(sendbuf), 0);
    mylist[number].count_error += 1;
  }

  closesocket(connections[c]);
  connections[c] = NULL;
};

int main(int argc, char *argv[]) {
  // ������� ������ .
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
    printf("Error at WSAStartup()\n");

  // �������� ������
  SOCKET m_socket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));

 

  if (m_socket == INVALID_SOCKET) {
    printf("Error at socket(): %ld\n", WSAGetLastError());
    WSACleanup();
    return 1;
  }
  // ������������	������
  struct sockaddr_in service;
  service.sin_family = AF_INET; //� ���������	�������	��������
  service.sin_addr.s_addr = inet_addr("192.168.56.1");
  service.sin_port = htons(
      atoi(argv[1])); //� �����	�����,	�	�������	�����	������ �����.

  //�������� ������� �����y
  if (bind(m_socket, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR) {
    printf("bind failed.\n");
    closesocket(m_socket);
    return 1;
  }

  // ������������� ������ m_socket
  if (listen(m_socket, 0) == SOCKET_ERROR)
    printf("Error listening on socket.\n");
  printf("Server was started.\n");
  printf("ip_servera= ");
  printf("%s\n", inet_ntoa(service.sin_addr));

  while (true) {
    int size = sizeof(service);
    // accept
    connections[index] = accept(m_socket, (sockaddr *)&service, &size);
    char *ip = inet_ntoa(service.sin_addr);
    printf("___________________________________________________________________"
           "____ ");
    cout << endl;
    printf("client ip= ");
    printf("%s\n", ip);
    if (connections[index] == NULL) {
      printf("Connection error.\n");
    }
    printf("Client Connected.\n");
    const time_t CONEC = time(NULL);
    for (int i = 0; i < 6; i++) {
      if (mylist[i].IP == inet_ntoa(service.sin_addr)) {
        number = i;
        if (mylist[i].count_error >= 3) {
          if (mylist[i].timeblock == 0) {
            const time_t timer = time(NULL);
            mylist[i].timeblock = timer;
            mylist[i].timeblock += 60;
            //    cout << "Current Datetime:" << timer << endl;
            //    cout << "Current Datetime structu:[" << i << "]" <<
            //    mylist[i].timeblock << endl;
            char sendbuf[64] = "You are locked until: ";
            tm *timeinfo =
                localtime(&mylist[i].timeblock); //����������� � ��������� tm
                                                 //��� ��������� ��������� ����
            strcat(sendbuf, asctime(timeinfo));
            cout << sendbuf << endl;
            send(connections[index], sendbuf, sizeof(sendbuf), 0);
            closesocket(connections[index]);
            connections[index] = NULL;
            i = 7;
          } else

              if (mylist[i].timeblock <= CONEC) {

            mylist[i].count_error = 0;
            mylist[i].timeblock = 0;
            i = 7;

          } else if (mylist[i].timeblock > CONEC) {

            //      cout << " TIMEBLOC MY=" << mylist[i].timeblock << endl;
            // cout << "TIMMEE:" << CONEC << endl;
            char sendbuf[64] = "You are locked until: ";
            tm *timeinfo = localtime(&mylist[i].timeblock);
            strcat(sendbuf, asctime(timeinfo));
            cout << sendbuf << endl;
            send(connections[index], sendbuf, sizeof(sendbuf), 0);
            closesocket(connections[index]);
            connections[index] = NULL;
            i = 7;
          }
        }
        i = 7;
      } else if (mylist[i].IP.empty()) {
        mylist[i].IP = inet_ntoa(service.sin_addr);
        mylist[i].count_error = 0;
        mylist[i].timeblock;
        i = 7;
      }
    }

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)(index), 0, 0);
    index++;
  }

  WSACleanup();
  return 0;
}
