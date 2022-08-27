#include "header.h"
//지금은 받은 data가 buf에 저장되어 있는 상태

UINT WINAPI InternetBlock_Thread(void *arg) {
	while (1) {
		Sleep(1 * 10 * SECOND);
		if (internetBlock == 1) {
			system("@echo off");

			//인터넷 익스플로러 차단
			system("taskkill \/f \/im iexplore.exe");
			
			//구글 크롬 차단
			system("taskkill \/f \/im chrome.exe");
			
			//카카오톡 차단
			system("taskkill \/f \/im KakaoTalk.exe");
			
			//팀뷰어 차단
			system("taskkill \/f \/im TeamViewer.exe");
		}
	}
}