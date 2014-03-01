#include <iostream>  
#include <cstdio>  
#include <Winsock2.h> 
#include <ws2tcpip.h> 
  
//using namespace std;  
  
int main()  
{  
	int result = 0;
// ����socket��̬���ӿ�(dll)  
    WORD wVersionRequested;  
    WSADATA wsaData;    // ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��  
    int err;  
       
    wVersionRequested = MAKEWORD( 2, 2 );   // ����1.1�汾��WinSock��  
       
    err = WSAStartup( wVersionRequested, &wsaData );  
    if ( err != NO_ERROR ) {  
		printf("startup error");
        return 1;          // ����ֵΪ���ʱ���Ǳ�ʾ�ɹ�����WSAStartup  
    }  
    /*   
    if ( LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1 ) {  
        // ���������ֽ��ǲ���1�����ֽ��ǲ���1��ȷ���Ƿ������������1.1�汾  
        // ����Ļ�������WSACleanup()�����Ϣ����������  
        WSACleanup( );  
        return -1;   
    }  
      */
// ����socket������������ʽ�׽��֣������׽��ֺ�sockSrv  
    // SOCKET socket(int af, int type, int protocol);  
    // ��һ��������ָ����ַ��(TCP/IPֻ����AF_INET��Ҳ��д��PF_INET)  
    // �ڶ�����ѡ���׽��ֵ�����(��ʽ�׽���)�����������ض���ַ�������Э�飨0Ϊ�Զ���  
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);     
	if(sockSrv == INVALID_SOCKET){
		WSACleanup();
		printf("sock error");
	}
// �׽���sockSrv�뱾�ص�ַ����  
    // int bind(SOCKET s, const struct sockaddr* name, int namelen);  
    // ��һ��������ָ����Ҫ�󶨵��׽��֣�  
    // �ڶ���������ָ�����׽��ֵı��ص�ַ��Ϣ���õ�ַ�ṹ�������õ�����Э��Ĳ�ͬ����ͬ  
    // ������������ָ��������Э���ַ�ĳ���  
    // PS: struct sockaddr{ u_short sa_family; char sa_data[14];};  
    //                      sa_familyָ���õ�ַ���壬 sa_data��ռλռ��һ���ڴ������������  
    //     ��TCP/IP�У���ʹ��sockaddr_in�ṹ�滻sockaddr���Է�����д��ַ��Ϣ  
    //   
    //     struct sockaddr_in{ short sin_family; unsigned short sin_port; struct in_addr sin_addr; char sin_zero[8];};  
    //     sin_family��ʾ��ַ�壬����IP��ַ��sin_family��Ա��һֱ��AF_INET��  
    //     sin_portָ����Ҫ������׽��ֵĶ˿ڡ�  
    //     sin_addr�����׽��ֵ�����IP��ַ��  
    //     sin_zero[8]�������������sockaddr_in��sockaddr�ṹ�ĳ���һ����  
    //     ��IP��ַָ��ΪINADDR_ANY�������׽������κη�������ػ�����IP��ַ���ͻ�������ݡ�  
    //     �����ֻ���׽���ʹ�ö��IP�е�һ����ַ����ָ��ʵ�ʵ�ַ����inet_addr()������  
    SOCKADDR_IN addrSrv;  
    //addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // ��INADDR_ANYת��Ϊ�����ֽ��򣬵��� htonl(long��)��htons(����)  
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    addrSrv.sin_family = AF_INET; 
    addrSrv.sin_port = htons(12001);  
  
    if(SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(addrSrv)))
		printf("bind error");// �ڶ�����Ҫǿ������ת��  
  
// ���׽�������Ϊ����ģʽ���������󣩣� listen()֪ͨTCP������׼���ý�������  
    // int listen(SOCKET s,  int backlog);  
    // ��һ������ָ����Ҫ���õ��׽��֣��ڶ�������Ϊ���ȴ����Ӷ��е���󳤶ȣ�  
    if(SOCKET_ERROR == listen(sockSrv, 10))
		printf("listen error");  

	SOCKADDR_IN  addrClient;  
    int len = sizeof(SOCKADDR);  
    char recvbuf[257];
    while(true){    // ���ϵȴ��ͻ�������ĵ���  
        SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);  
		if(INVALID_SOCKET == sockConn)
		  printf("accept error");
	//	result = recv(sockSrv, recvbuf, 512, 0);
	//	for (int i=0;i<512;i++)
	//	printf("%c",recvbuf[4]);
	//char *p = addrClient.sin_addr;
	//printf(%s",p);
    connect(sockSrv, (SOCKADDR*)&sockConn, sizeof(sockConn));
    char *strclient = inet_ntoa(addrClient.sin_addr);
	printf("%s\n",strclient);
//	do{
		result = recv(sockConn, recvbuf, sizeof(recvbuf), 0);
	//	printf("%d\n",result);
		recvbuf[result] = 0;
		printf("%s",recvbuf);
	//}while(result>0);
//	printf("%d",result);
	//printf("%s",recvbuf);
  closesocket(sockConn);
	}
  return 0;
}
