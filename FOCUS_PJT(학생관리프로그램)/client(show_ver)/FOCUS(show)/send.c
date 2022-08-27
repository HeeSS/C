#include "header.h"

int send_MY(SOCKET s, const char *data, const int size, const int id, const int data_type, int flags) {
	int ret;
	int info[3];
	char *tmp;
	int p[10];

	info[0] = size;
	info[1] = id;
	info[2] = data_type;
	// 앞에 붙는 '정보의 크기'는 header.h에 다음과 같이 정의되어있음
	// #define DATA_INFO sizeof(int)*3 // 12

	tmp = (char *)malloc(size + sizeof(info));
	memset(tmp, NULL, sizeof(tmp));
	memcpy(&tmp[0], info, sizeof(info));
	memcpy(&tmp[12], data, size);
	//memcpy(p, tmp, sizeof(tmp));
	return send(s, tmp, sizeof(info) + size, flags);
}

