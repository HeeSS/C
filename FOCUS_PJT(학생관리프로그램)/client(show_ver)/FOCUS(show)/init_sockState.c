#include "header.h"

void init_sockState(int DataType) {
	switch (DataType) {
	case SERVER:
		getsockname(srvSocket, (SOCKADDR*)&sockaddr_in_S, &SrvSockaddrSize);
		strcpy(s.IP_ADDR, inet_ntoa(sockaddr_in_S.sin_addr));
		strcpy(s.MAC_ADDR, getMAC());
		break;
	case ADMINISTRATOR:
		getsockname(admSocket, (SOCKADDR*)&sockaddr_in_A, &AdmSockaddrSize);
		strcpy(a.IP_ADDR, inet_ntoa(sockaddr_in_A.sin_addr));
		strcpy(a.MAC_ADDR, getMAC());
		a.Time = time(NULL);
		break;
	}
}