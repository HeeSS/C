#pragma comment(lib, "iphlpapi.lib" )//mac �ּҸ� ����

#include "header.h"
#include <IPHlpApi.h>// mac �ּ� �˱� ���� ���

char* getMAC()
{
	char strMac[256];
	DWORD size = sizeof(PIP_ADAPTER_INFO);
	PIP_ADAPTER_INFO info;
	int result;
	ZeroMemory(&info, size);
	result = GetAdaptersInfo(info, &size); //ù��° ��ī�� MAC address ��������
	if (result == ERROR_BUFFER_OVERFLOW) { // GetAdaptersInfo�� �޸𸮰� �����ϸ� �� �Ҵ��ϰ� ��ȣ��
		info = (PIP_ADAPTER_INFO)malloc(size);
		GetAdaptersInfo(info, &size);
	}
	if (!info) return 0;

	sprintf(strMac, "%0.2X-%0.2X-%0.2X-%0.2X-%0.2X-%0.2X",
		info->Address[0], info->Address[1], info->Address[2],
		info->Address[3], info->Address[4], info->Address[5]);
	return strMac;
}