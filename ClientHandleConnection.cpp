// ClientHandleConnection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "Advapi32.lib")
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <WinInet.h>
#include <iomanip>
#include <string>
#include <cstdio>  string
#include <WinCrypt.h>
#include <iostream>
#include <string>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#include <iostream>
BOOL SendFilePacket(const char* ServerIP, const char* FilePath)
{
	std::string Path = FilePath;
	std::string base_filename = Path.substr(Path.find_last_of("/\\") + 1);
	SOCKET ConnectSocket = 0, n = 0, b;
	char rbuff[1024];

	char filepath[1024];
	char sendbuffer[1024] = { 0 };
	char recv_buf[13] = { 0 };
	WSADATA wsaData;
	struct sockaddr_in serv_addr;
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
#ifdef LOG_ENABLED
		Log("WSAStartUpFailed", 1);
#endif
		return 1;
	}

	memset(rbuff, '0', sizeof(rbuff));
	ConnectSocket = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5110);
	serv_addr.sin_addr.s_addr = inet_addr(ServerIP);
	//perror("Connect");

	b = connect(ConnectSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (b == -1) {
#ifdef LOG_ENABLED
		Log("Connection Failed", 1);

#endif

		closesocket(ConnectSocket);
		system("pause");
		return 1;
	}
#ifdef LOG_ENABLED
	Log("Connection Succedded !", 0);
#endif

	sprintf(filepath, FilePath);
	FILE* fp = fopen(filepath, "rb");
	if (fp == NULL) {
#ifdef LOG_ENABLED
		Log("Cann't open File!", 1);
#endif

		closesocket(ConnectSocket);
		system("pause");

		return 2;
	}
#ifdef LOG_ENABLED
	Log("Passing to encrypt text!", 0);
#endif


	if (recv(ConnectSocket
		, (char*)recv_buf, sizeof(recv_buf), 0) == SOCKET_ERROR)
	{
#ifdef LOG_ENABLED
		Log("Failed on Recv Packet!", 1);
#endif
		fclose(fp);
		closesocket(ConnectSocket);
	}
#ifdef LOG_ENABLED
	Log("Encrypted Text Sent!", 0);
	Log("Sending File ..!", 0);
#endif
	while ((b = fread(sendbuffer, 1, sizeof(sendbuffer), fp)) > 0) {


		send(ConnectSocket, sendbuffer, b, 0);

	}
	/**/

#ifdef LOG_ENABLED
	CHAR txt[50];
	CHAR txtrv[50];
	sprintf(txt, "File : %s Sent!", base_filename.c_str());
	Log(txt, 0);
	sprintf(txtrv, "Text Recv : %s Sent!", recv_buf);
	Log(txtrv, 0);

	Log("Closing Socket..!", 0);
#endif

	fclose(fp);
	closesocket(ConnectSocket);
	return true;
}
int main()
{
	
	
	SOCKET ConnectSocket = 0, n = 0, b;
	char rbuff[1024];

	char filepath[1024];
	char sendbuffer[1024] = { 0 };
	char recv_buf[13] = { 0 };
	WSADATA wsaData;
	struct sockaddr_in serv_addr;
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
#ifdef LOG_ENABLED
		Log("WSAStartUpFailed", 1);
#endif
		//	printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	memset(rbuff, '0', sizeof(rbuff));
	ConnectSocket = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(20000);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//perror("Connect");

	b = connect(ConnectSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (b == -1) {
#ifdef LOG_ENABLED
		Log("Connection Failed", 1);

#endif

		closesocket(ConnectSocket);
		system("pause");
		return 1;
	}
#ifdef LOG_ENABLED
	Log("Connection Succedded !", 0);
#endif


#ifdef LOG_ENABLED
	Log("Passing to encrypt text!", 0);
#endif


	if (recv(ConnectSocket
		, (char*)recv_buf, sizeof(recv_buf), 0) == SOCKET_ERROR)
	{
#ifdef LOG_ENABLED
		Log("Failed on Recv Packet!", 1);
#endif
		printf("Recv :: %s ", recv_buf);
		closesocket(ConnectSocket);
	}
	
	printf("Recv :: %s ", recv_buf);
#ifdef LOG_ENABLED
	Log("Encrypted Text Sent!", 0);
	Log("Sending File ..!", 0);
#endif
	
	/**/

#ifdef LOG_ENABLED
	CHAR txt[50];
	CHAR txtrv[50];
	sprintf(txt, "File : %s Sent!", base_filename.c_str());
	Log(txt, 0);
	sprintf(txtrv, "Text Recv : %s Sent!", recv_buf);
	Log(txtrv, 0);

	Log("Closing Socket..!", 0);
#endif

	closesocket(ConnectSocket);
}
