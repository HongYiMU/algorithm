
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#define DEFAULT_BUFFER      2048
#define DEFAULT_MESSAGE     "GET / HTTP/1.1\r\nHost:10.0.10.1\r\n\
Connection:keep-alive\r\n\
Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\
user-Agent:Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/36.0.1985.125 Safari/537.36\r\n\
Accept-Encoding: gzip,deflate,sdch\r\n\
Accept-Language: zh-CN,zh;q=0.8,en;q=0.6\r\n\
\r\n"

int maintt(int argc,char* argv[])
{
	WSADATA       wsd;
	SOCKET        sClient;
	int iPort = 80;
	char *serverIP = "10.0.10.1";
	int		ret;
	char   szBuffer[DEFAULT_BUFFER],
	      szMessage[1024];        // Message to send to sever
	struct sockaddr_in server;
	struct hostent    *host = NULL;
	
	
	if(argc > 1)
	{
		iPort = atoi(argv[1]);
	}
	if(argc > 2)
	{
		serverIP = argv[2];
	}

	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
	{
		printf("Failed to load Winsock library!\n");
		system("pause");
		return 1;
	}

	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET)
	{
		printf("socket() failed: %d\n", WSAGetLastError());
		return 1;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(iPort);
	server.sin_addr.s_addr = inet_addr(serverIP);

	if (server.sin_addr.s_addr == INADDR_NONE)
	{
		host = gethostbyname(serverIP);
		if (host == NULL)
		{
			printf("Unable to resolve server: %s\n", serverIP);
			system("pause");
			return 1;
		}
		CopyMemory(&server.sin_addr, host->h_addr_list[0],
			host->h_length);
	}




	if (connect(sClient, (struct sockaddr *)&server, 
		sizeof(server)) == SOCKET_ERROR)
	{
		printf("connect() failed: %d\n", WSAGetLastError());
		system("pause");
		return 1;
	}

    strcpy(szMessage, DEFAULT_MESSAGE);
	ret = send(sClient, szMessage, strlen(szMessage), 0);
	if (ret == 0)
	{	perror("send();");}
	else if (ret == SOCKET_ERROR)
	{
		printf("send() failed: %d\n", WSAGetLastError());
		
	}
	printf("Send %d bytes\n", ret);

	ret = recv(sClient, szBuffer, DEFAULT_BUFFER, 0);
	if (ret == 0)        // Graceful close
	perror("send();");
	else if (ret == SOCKET_ERROR)
	{
		printf("recv() failed: %d\n", WSAGetLastError());
		
	}
	szBuffer[ret] = '\0';
	printf("RECV [%d bytes]: '%s'\n", ret, szBuffer);

	system("pause");
	closesocket(sClient);

	WSACleanup();

	return 0;
}
