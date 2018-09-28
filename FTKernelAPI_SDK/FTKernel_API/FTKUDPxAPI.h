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
	
	//通讯回调函数
	typedef void ( WINAPI *FTK_UDP_EXTPROTOCOL_CALLBACK ) ( unsigned char nExtProtocol, const unsigned char *data, unsigned int length, unsigned int ip, unsigned short port );

	//初始化UDPSocket 通讯接口
	//Initialize UDP Socket API interface
    FTKUDPXAPI_API BOOL UDPXAPI FTK_UDPSocket_Init( unsigned short nPort );

	//初始化通过代理访问的接口
	//Build connect by proxy
    FTKUDPXAPI_API BOOL UDPXAPI FTK_UDPSocket_ProxyConnect( int nProxyType, const char *pProxyHost, int nProxyPort, const char *pProxyUser, const char *pProxyPasswd, int nTimeOut, const char *pTCPHostIP = "", unsigned short nTCPHostPort = 8099 );
	
	//获取绑定的UDP 的端口
	//Get UDP binding port
    FTKUDPXAPI_API unsigned short UDPXAPI FTK_UDPSocket_GetUDPPort();

	//获取绑定的UDP 的Socket 句柄
	//Get UDP binding socket handle
    FTKUDPXAPI_API int UDPXAPI FTK_UDPSocket_GetUDPSocket();
	
	//添加额外的通讯协议标识
	//Add UDP protocol identifier
	FTKUDPXAPI_API unsigned char UDPXAPI FTK_UDPSocket_AddExtProtcol( FTK_UDP_EXTPROTOCOL_CALLBACK cb );
	
	//驱动UDP的通讯事件
	//Process UDP socket's events
    FTKUDPXAPI_API void UDPXAPI FTK_UDPSocket_DoSocketEvents();
	
	//////////////////////////////////////////////////////////////////////////

	//通知外部自己失败的函数
	typedef void ( WINAPI *FTK_UDPX_ERROR_CALLBACK ) ( unsigned char nCmd );

	//通知外部在线人数的函数
	typedef void ( WINAPI *FTK_UDPX_USERCNT_CALLBACK ) ();

	//通知外部自己登陆成功的函数
	typedef void ( WINAPI *FTK_UDPX_LOGIN_CALLBACK ) ();

	//通知外部NAT类型发生了变化的函数
	typedef void ( WINAPI *FTK_UDPX_NATTYPE_CALLBACK ) ();

	//通知外部远程呼叫结果的函数的函数
	typedef void ( WINAPI *FTK_UDPX_PEERCALL_CALLBACK ) ( unsigned char nActive, const char *pPeerIP, unsigned short nTCPPort, const unsigned char *pPeerID, const unsigned char *pInfoHash, unsigned char nNetType, const char *pTransIP, unsigned short nTransPort );

	//////////////////////////////////////////////////////////////////////////
	
	//设置当前使用的UDP句柄[注意必须和其它模块在同一个线程中使用]
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_SetUDPSocket( int nSocket );
	
	//设置扩展的UDP协议头
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_SetUDPExtProtocol( unsigned char nExt );
	
	//设置Log日志的输入级别
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_EnableLog( int nLevel, const char *pLogFileName );

	//使用内核的函数输出日志到和内核一个日志文件
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_WriteLog( int nLevel, const char *pLine );
	
	//事件驱动函数
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_ProcessEvents();
	
	//处理接收到的UDP数据
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_ProcessUDPPacket( const unsigned char *data, unsigned int length, unsigned int ip, unsigned short port );
	
	//自己的真实IP
	FTKUDPXAPI_API const char * UDPXAPI FTK_UDPX_GetRealIP();
	
	//获取自己的NAT IP
	FTKUDPXAPI_API const char * UDPXAPI FTK_UDPX_GetNatIP();
	
	//获取自己的NAT端口
	FTKUDPXAPI_API unsigned short UDPXAPI FTK_UDPX_GetNatPort();
	
	//获取总的在线人数
	FTKUDPXAPI_API unsigned int UDPXAPI FTK_UDPX_GetOnlineUserCnt();
	
	//获取NAT的类型
	FTKUDPXAPI_API unsigned char UDPXAPI FTK_UDPX_GetNatType();
	
	//是否登陆成功
	FTKUDPXAPI_API BOOL UDPXAPI FTK_UDPX_IsLoginOK();
	
	//登陆到的服务器的地址
	FTKUDPXAPI_API LPCTSTR UDPXAPI FTK_UDPX_GetServerIP();
	
	//登陆到的服务器的Port
	FTKUDPXAPI_API unsigned short UDPXAPI FTK_UDPX_GetServerPort();
	
	//////////////////////////////////////////////////////////////////////////
	
	//设置回调函数
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_SetCallback( 
		FTK_UDPX_ERROR_CALLBACK pfnErrCB, 
		FTK_UDPX_USERCNT_CALLBACK pfnUserCntCB, 
		FTK_UDPX_LOGIN_CALLBACK pfnLoginCB,
		FTK_UDPX_NATTYPE_CALLBACK pfnNatTypeCB,
		FTK_UDPX_PEERCALL_CALLBACK pfnPeerCallCB );
	
	//////////////////////////////////////////////////////////////////////////
	
	//登陆到服务器上
	FTKUDPXAPI_API BOOL UDPXAPI FTK_UDPX_Login( const char *pIP, unsigned short nPort, unsigned short nTCPPort, unsigned short nTransPort, char *pUserID = NULL );
	
	//重新登陆
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_Relogin();
	
	//通知服务器退出
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_Logout();
	
	//主动执行一次NAT检查
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_CheckNatType();

	//呼叫某个用户(服务器端返回对方的网络类型，并做相关呼叫处理)
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_RemoteCallPeer( unsigned char *pUserID, unsigned char *pInfoHash );

	//设置客户端的网络忙闲状态(0: 空闲, 1: 忙)
	FTKUDPXAPI_API void UDPXAPI FTK_UDPX_SetNetIdle( unsigned char nNetIdle );
	
	//////////////////////////////////////////////////////////////////////////
}

#endif//__FTKUDPxAPI_H__