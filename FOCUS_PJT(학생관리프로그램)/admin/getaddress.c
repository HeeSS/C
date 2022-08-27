#pragma comment(lib, "iphlpapi.lib" )//mac ¡÷º“∏¶ ¿ß«ÿ

#include "header.h"
#include <IPHlpApi.h>// mac ¡÷º“ æÀ±‚ ¿ß«— «Ï¥ı

char* getMAC()//»˜»˜»˜∆R ¿ﬂ √£æ“æÓ
{
	char strMac[256];//mac¡÷º“∏¶ ¿ß«ÿ!!!! ∞©Ω√¥Ÿ!!!
	DWORD size = sizeof(PIP_ADAPTER_INFO);//π∫¡ˆ¥¬ ≥™µµ ∏∏ß.
	PIP_ADAPTER_INFO info;
	int result;
	ZeroMemory(&info, size);
	result = GetAdaptersInfo(info, &size); //√ππ¯¬∞ ∑£ƒ´µÂ MAC address ∞°¡Æø¿±‚
	if (result == ERROR_BUFFER_OVERFLOW) {// GetAdaptersInfo∞° ∏ﬁ∏∏Æ∞° ∫Œ¡∑«œ∏È ¿Á «“¥Á«œ∞Ì ¿Á»£√‚
		info = (PIP_ADAPTER_INFO)malloc(size);
		GetAdaptersInfo(info, &size);
	}
	if (!info) return 0;

	sprintf(strMac, "%0.2X-%0.2X-%0.2X-%0.2X-%0.2X-%0.2X",
		info->Address[0], info->Address[1], info->Address[2],
		info->Address[3], info->Address[4], info->Address[5]);
	return strMac;
}