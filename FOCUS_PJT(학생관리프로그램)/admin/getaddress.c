#pragma comment(lib, "iphlpapi.lib" )//mac 주소를 위해

#include "header.h"
#include <IPHlpApi.h>// mac 주소 알기 위한 헤더

char* getMAC()//히히히힣 잘 찾았어
{
	char strMac[256];//mac주소를 위해!!!! 갑시다!!!
	DWORD size = sizeof(PIP_ADAPTER_INFO);//뭔지는 나도 모름.
	PIP_ADAPTER_INFO info;
	int result;
	ZeroMemory(&info, size);
	result = GetAdaptersInfo(info, &size); //첫번째 랜카드 MAC address 가져오기
	if (result == ERROR_BUFFER_OVERFLOW) {// GetAdaptersInfo가 메모리가 부족하면 재 할당하고 재호출
		info = (PIP_ADAPTER_INFO)malloc(size);
		GetAdaptersInfo(info, &size);
	}
	if (!info) return 0;

	sprintf(strMac, "%0.2X-%0.2X-%0.2X-%0.2X-%0.2X-%0.2X",
		info->Address[0], info->Address[1], info->Address[2],
		info->Address[3], info->Address[4], info->Address[5]);
	return strMac;
}