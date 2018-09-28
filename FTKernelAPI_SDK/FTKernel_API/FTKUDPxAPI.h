//////////////////////////////////////////////////////////////////////////
// FTKUDPxAPI.h : header file
//////////////////////////////////////////////////////////////////////////

#ifndef __FTKUDPxAPI_H__
#define __FTKUDPxAPI_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define FTKUDPXAPI_API

#ifndef UDPXAPI
#define UDPXAPI __stdcall
#endif

typedef long * HUDPXLibrary;

//////////////////////////////////////////////////////////////////////////

extern "C"
{
	//////////////////////////////////////////////////////////////////////////
	//UDPSocket interface
	
	//ͨѶ�ص�����
	typedef void ( WINAPI *FTK_UDP_EXTPROTOCOL_CALLBACK ) ( unsigned char nExtProtocol, const unsigned char *data, unsigned int length, unsigned int ip, unsigned short port );

	//��ʼ��UDPSocket ͨѶ�ӿ�
	//Initialize UDP Socket API interface
    FTKUDPXAPI_API BOOL UDPXAPI FTK_UDPSocket_Init( unsigned short nPort );

	//��ʼ��ͨ��������ʵĽӿ�
	//Build connect by proxy
    FTKUDPXAPI_API BOOL UDPXAPI FTK_UDPSocket_ProxyConnect( int nProxyType, const char *pProxyHost, int nProxyPort, const char *pProxyUser, const char *pProxyPasswd, int nTimeOut, const char *pTCPHostIP = "", unsigned short nTCPHostPort = 8099 );
	
	//��ȡ�󶨵�UDP �Ķ˿�
	//Get UDP binding port
    FTKUDPXAPI_API unsigned short UDPXAPI FTK_UDPSocket_GetUDPPort();

	//��ȡ�󶨵�UDP ��Socket ���
	//Get UDP binding socket handle
    FTKUDPXAPI_API int UDPXAPI FTK_UDPSocket_GetUDPSocket();
	
	//��Ӷ����ͨѶЭ���ʶ
	//Add UDP protocol identifier
	FTKUDPXAPI_API unsigned char UDPXAPI FTK_UDPSocket_AddExtProtcol( FTK_UDP_EXTPROTOCOL_CALLBACK cb );
	
	//����UDP��ͨѶ�¼�
	//Process UDP socket's events
    FTKUDPXAPI_API void UDPXAPI FTK_UDPSocket_DoSocketEvents();
	
	//////////////////////////////////////////////////////////////////////////

	//֪ͨ�ⲿ�Լ�ʧ�ܵĺ���
	typedef void ( WINAPI *FTK_UDPX_ERROR_CALLBACK ) ( unsigned char nCmd );

	//֪ͨ�ⲿ���������ĺ���
	typedef void ( WINAPI *FTK_UDPX_USERCNT_CALLBACK ) ();

	//֪ͨ�ⲿ�Լ���½�ɹ��ĺ���
	typedef void ( WINAPI *FTK_UDPX_LOGIN_CALLBACK ) ();

	//֪ͨ�ⲿNAT���ͷ����˱仯�ĺ���
	typedef void ( WINAPI *FTK_UDPX_NATTYPE_CALLBACK ) ();

	//֪ͨ�ⲿԶ�̺��н���ĺ����ĺ���
	typedef void ( WINAPI *FTK_UDPX_PEERCALL_CALLBACK ) ( unsigned char nActive, const char *pPeerIP, unsigned short nTCPPort, const unsigned char *pPeerID, const unsigned char *pInfoHash, unsigned char nNetType, const char *pTransIP, unsigned short nTransPort );

	//////////////////////////////////////////////////////////////////////////
	
	//���õ�ǰʹ�õ�UDP���[ע����������ģ����ͬһ���߳���ʹ��]
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_SetUDPSocket( int nSocket );
	
	//������չ��UDPЭ��ͷ
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_SetUDPExtProtocol( unsigned char nExt );
	
	//����Log��־�����뼶��
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_EnableLog( int nLevel, const char *pLogFileName );

	//ʹ���ں˵ĺ��������־�����ں�һ����־�ļ�
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_WriteLog( int nLevel, const char *pLine );
	
	//�¼���������
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_ProcessEvents();
	
	//������յ���UDP����
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_ProcessUDPPacket( const unsigned char *data, unsigned int length, unsigned int ip, unsigned short port );
	
	//�Լ�����ʵIP
	FTKUDPXAPI_API const char * UDPXAPI FTK_UDPX_GetRealIP();
	
	//��ȡ�Լ���NAT IP
	FTKUDPXAPI_API const char * UDPXAPI FTK_UDPX_GetNatIP();
	
	//��ȡ�Լ���NAT�˿�
	FTKUDPXAPI_API unsigned short UDPXAPI FTK_UDPX_GetNatPort();
	
	//��ȡ�ܵ���������
	FTKUDPXAPI_API unsigned int UDPXAPI FTK_UDPX_GetOnlineUserCnt();
	
	//��ȡNAT������
	FTKUDPXAPI_API unsigned char UDPXAPI FTK_UDPX_GetNatType();
	
	//�Ƿ��½�ɹ�
	FTKUDPXAPI_API BOOL UDPXAPI FTK_UDPX_IsLoginOK();
	
	//��½���ķ������ĵ�ַ
	FTKUDPXAPI_API LPCTSTR UDPXAPI FTK_UDPX_GetServerIP();
	
	//��½���ķ�������Port
	FTKUDPXAPI_API unsigned short UDPXAPI FTK_UDPX_GetServerPort();
	
	//////////////////////////////////////////////////////////////////////////
	
	//���ûص�����
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_SetCallback( 
		FTK_UDPX_ERROR_CALLBACK pfnErrCB, 
		FTK_UDPX_USERCNT_CALLBACK pfnUserCntCB, 
		FTK_UDPX_LOGIN_CALLBACK pfnLoginCB,
		FTK_UDPX_NATTYPE_CALLBACK pfnNatTypeCB,
		FTK_UDPX_PEERCALL_CALLBACK pfnPeerCallCB );
	
	//////////////////////////////////////////////////////////////////////////
	
	//��½����������
	FTKUDPXAPI_API BOOL UDPXAPI FTK_UDPX_Login( const char *pIP, unsigned short nPort, unsigned short nTCPPort, unsigned short nTransPort, char *pUserID = NULL );
	
	//���µ�½
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_Relogin();
	
	//֪ͨ�������˳�
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_Logout();
	
	//����ִ��һ��NAT���
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_CheckNatType();

	//����ĳ���û�(�������˷��ضԷ����������ͣ�������غ��д���)
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_RemoteCallPeer( unsigned char *pUserID, unsigned char *pInfoHash );

	//���ÿͻ��˵�����æ��״̬(0: ����, 1: æ)
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_SetNetIdle( unsigned char nNetIdle );
	
	//////////////////////////////////////////////////////////////////////////
}

#endif//__FTKUDPxAPI_H__