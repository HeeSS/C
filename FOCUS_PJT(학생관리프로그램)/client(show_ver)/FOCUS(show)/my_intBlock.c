#include "header.h"
//������ ���� data�� buf�� ����Ǿ� �ִ� ����

UINT WINAPI InternetBlock_Thread(void *arg) {
	while (1) {
		Sleep(1 * 10 * SECOND);
		if (internetBlock == 1) {
			system("@echo off");

			//���ͳ� �ͽ��÷η� ����
			system("taskkill \/f \/im iexplore.exe");
			
			//���� ũ�� ����
			system("taskkill \/f \/im chrome.exe");
			
			//īī���� ����
			system("taskkill \/f \/im KakaoTalk.exe");
			
			//����� ����
			system("taskkill \/f \/im TeamViewer.exe");
		}
	}
}