#include "header.h"
#define ACK_ 100
char message[BUFSIZE];

UINT WINAPI ManageList(void *arg) {
	int i;
	SOCKET Client;
	char ACK[] = "hello";
	TIME Now;

	struct timeval val;
	val.tv_sec = 0;
	val.tv_usec = 100;

	unsigned int option_value = 1;

	Server_Socket = socket(PF_INET, SOCK_STREAM, 0);
	if (Server_Socket == INVALID_SOCKET) {
		printf("#error here 1\n");
		Sleep(10000);
	}

	setsockopt(Server_Socket, SOL_SOCKET, SO_REUSEADDR, (char *)&option_value, sizeof(option_value));

	memset((char *)&sockaddr_in, 0, sizeof(sockaddr_in));
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	sockaddr_in.sin_port = htons(5455);

	if (bind(Server_Socket, (SOCKADDR *)&sockaddr_in, sizeof(sockaddr_in)) < 0) {
		printf("#error here 3\n");
		Sleep(10000);
	}

	if (listen(Server_Socket, CLIENT_SIZE) == -1) {
		printf("#error here 4\n");
		Sleep(10000);
	}

	while (login) {

		Now = time(NULL);
		FD_ZERO(&Socket_Arr);

		FD_SET(Server_Socket, &Socket_Arr);
		 
		for (i = 0; i < howmany_C; i++)
			FD_SET(Client_List[i].Socket, &Socket_Arr);

		Max_Socket = Get_Max_Sock(&Socket_Arr, Server_Socket, ADMINISTRATOR_STATE_SIZE) + 1;

		if (select(Max_Socket, &Socket_Arr, (fd_set *)0, (fd_set *)0, &val) < 0) {
			//printf("select error #55\n");
			//exit(0); /// (요수정) 실패 시, 수정
		}

		// 추가 할 클라이언트가 있나?
		if (FD_ISSET(Server_Socket, &Socket_Arr)) { //FE_ISSET => fd로 전달된 파일 디스크립터 정보가 있으면 양수 반환
			sockaddr_size = sizeof(SOCKADDR);
			Client = accept(Server_Socket, (SOCKADDR*)&sockaddr_in, &sockaddr_size);

			if (Client == -1) {//accept -> 오류시 반환-11
				printf("accept error\n");
				exit(0); /// (요수정) 실패 시, 수정
			}
			else {
				Client_List[howmany_C++].Socket = Client;
				Client_List[i].Time = time(NULL);
				continue;
			}
		}

		// 클라이언트 관리
		for (i = 0; i < howmany_C; i++) {
			// A. 응답 없는 클라이언트 관리
			if (((Now - Client_List[i].Time) / 60)  > FREQUENT) {
				closesocket(Client_List[i].Socket);
				memset(&Client_List[i], NULL, sizeof(State));
				memcpy(&Client_List[i], &Client_List[i + 1], sizeof(State) * (howmany_C - 1 - i));
				howmany_C--;
				i--;
				continue;
			}
			// B. 정기보고 수신
			if (FD_ISSET(Client_List[i].Socket, &Socket_Arr)) {
				memset(message, NULL, sizeof(message));

				if (recv(Client_List[i].Socket, message, DATA_INFO, 0) > 0) {
					memset(message, NULL, sizeof(message));
					recv(Client_List[i].Socket, message, CLIENT_SIZE, 0);
					strcpy(Client_List[i].IP_ADDR, message);
					strcpy(Client_List[i].MAC_ADDR, message + 30);
					Client_List[i].Time = time(NULL);

					if (send_MY(Client_List[i].Socket, ACK, sizeof(ACK), ADMINISTRATOR, ACK_, 0) == -1) {
						closesocket(Client_List[i].Socket);
						memset(&Client_List[i], NULL, sizeof(State));
						memcpy(&Client_List[i], &Client_List[i + 1], sizeof(State)*(howmany_C - 1 - i));
						howmany_C--;
					}
					else {
					}

				}
				else {
					closesocket(Client_List[i].Socket);
					memset(&Client_List[i], NULL, sizeof(State));
					memcpy(&Client_List[i], &Client_List[i + 1], sizeof(State)*(howmany_C - 1 - i));
					howmany_C--;
				}
			} // B
		} // A
	}
	return 0;
}