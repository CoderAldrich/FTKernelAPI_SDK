//////////////////////////////////////////////////////////////////////////
// FTKernelAPI.h : header file
//
// English Notes:
//
// Copyright @ 2004-2006 p2plib.com All rights reserved.
// MSN: FlashBT@Hotmail.com
// Homepage: http://www.p2plib.com
//
// FTKernelAPI is a kernel API based on Bittorrent protocol. 
//
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found and I will fix them into this library. 
//
// Please visit http://www.p2plib.com for the detailed information.
//
// ***********************************************************************
// Chinese Notes:
//
// 版权所有 2004-2006 北京惠软畅联网络技术有限公司 保留所有权利. 中国. 
// 官方网站: http://www.p2plib.com/
//
// FTKernelAPI 是基于BitTorrent协议的内核库, 并做了强大扩展. 可以帮助您
// 快速的开发自己的P2P软件系统.
//
// FTKernelAPI 兼容BT协议内核库, 分为4个版本:
// 1. 免费版本, 使用受限制, 只支持一个并发任务, 无技术支持
// 2. 初级版本, 需付费, 支持多个任务并发, 有技术支持
// 3. 中级版本, 需付费, 支持自定义协议, 数据加密, 封锁指定IP, 限速等功能, 有技术支持
// 4. 高级版本, 需付费, 支持顺序下载, 流媒体点播, 被动回调加载任务, 有技术支持
//
// 如果发现任何错误/建议, 请通知我们, 我们将在以后的版本中很快改进和实现.
// 更详细信息请访问我的网站: http://www.p2plib.com
//////////////////////////////////////////////////////////////////////////

#ifndef __FTKERNELAPI_H__
#define __FTKERNELAPI_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define FTKERNELAPI_API

#ifndef BTAPI
#define BTAPI __stdcall
#endif

//////////////////////////////////////////////////////////////////////////

//定义64位无符号长整型
//Define 64bit long integer type
typedef unsigned __int64 QWORD;

//定义配置文件对象的句柄
//Define Config INI file handle
typedef LONG *HConfigIni;

//定义下载任务的句柄
//Define downloader handle
typedef LONG *HDownloader;

//定义读取Torrent文件的句柄
//Define Torrent file handle
typedef LONG *HTorrentFile;

//定义生成Torrent文件的句柄
//Define Making Torrent file handle
typedef LONG *HMakeTorrent;

//定义Http接口代理设置句柄
//Define a http proxy settings handle
typedef LONG *HHttpProxy;

//定义打开Http的句柄
//Define http handle
typedef LONG *HHttpConnection;

//定义返回的Http数据的句柄
//Define http response data handle
typedef LONG *HHttpResponse;

//用户标识的长度
//length of client identifier
#define IDSIZE 20

//BitTorrent 客户端版本信息长度
//bitorrent client version information
#define AGENTSIZE 64

//生成的SHA的散列的长度
//Length of SHA1
#define SHA1_DIGEST_LENGTH 20 

//代理的类型
//Proxytypes
#define PROXYTYPE_NOPROXY 0
#define PROXYTYPE_SOCKS4 1
#define PROXYTYPE_SOCKS4A 2
#define PROXYTYPE_SOCKS5 3
#define PROXYTYPE_HTTP11 4

////////////////////////
//下载状态
//Download status

#define DLSTATE_NONE				0
#define DLSTATE_ALLOCING			1
#define DLSTATE_CHECKING			2
#define DLSTATE_DOWNLOAD			3
#define DLSTATE_PAUSING				4
#define DLSTATE_CHECKEND			5
#define DLSTATE_FETALERR			6
#define DLSTATE_TERMINATE			7

#define DLSTATE_CB_NONE				0
#define DLSTATE_CB_BEFOREDOWN		1
#define DLSTATE_CB_ONCOMPLETE		2

//定义Piece的状态
//Piece status
#define PIECESTATE_INCOMPLETE	0
#define PIECESTATE_DOWNLOADING	1
#define PIECESTATE_COMPLETE	2

//Port type of Firewall and UPnP
//操做Windows防火墙或者UPnP时的端口类型定义
#define WCXT_TCP_PORT 1
#define WCXT_UDP_PORT 2

#define TUNNEL_NONE ( 0 ) //无穿透
#define TUNNEL_UDP_ACTIVE ( 1 ) //UDP 穿透(主动)
#define TUNNEL_UDP_PASSIVE ( 2 ) //UDP 穿透(被动)
#define TUNNEL_TCP_ACTIVE ( 3 ) //TCP 穿透
#define TUNNEL_TCP_PASSIVE ( 4 ) //TCP 穿透

//////////////////////////////////////////////////////////////////////////

struct _tagPeerData
{
    DWORD m_dwIP;
    USHORT m_nPort;
    BYTE m_pPeerID[ IDSIZE ];
	
    //-------------------------------------
	
    BYTE m_bIsLocal;
    char m_szVersion[ AGENTSIZE ];
    QWORD m_qwPeerHaveSize;
    float m_fDownRate;
    float m_fUpRate;
    QWORD m_qwDownloaded;
    QWORD m_qwUploaded;
    float m_fTimeElapsed;
    float m_fPeerDownRate;
    char m_szExtInfo[ 256 ];
};

struct _tagMiniPeerData
{
    DWORD	m_dwIP;
    USHORT	m_nPort;
};

struct _tagAnnounceData
{
    char m_szURL[ 512 ];
    BYTE m_bWorking;
    BYTE m_bHeader;
    UINT m_nCount;
    UINT m_nFailed;
    float m_fTimeLeft;
    float m_fLastTime;
    char m_szExtInfo[ 512 ];
};

struct _tagFileInfo
{
    char m_szFileName[ 512 ];
    QWORD m_qwFileSize;
};

struct _tagErrInfo
{
    char m_szErrInfo[ 1024 ];
};

//////////////////////////////////////////////////////////////////////////
//Nat的类型

//未知
#define NAT_TYPE_UNKNOWN		( 0 )

//公网
#define NAT_TYPE_WAN			( 1 )

//未知类型的内网
#define NAT_TYPE_UNKNOWN_LAN	( 2 )

//无法穿透的的内网
#define NAT_TYPE_SYM_LAN		( 3 )

//支持穿透的的内网
#define NAT_TYPE_CONE_LAN		( 4 )

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

extern "C"
{
	//////////////////////////////////////////////////////////////////////////
	
	//定义被动通知的回调函数
	//Define callback function type
	typedef BOOL ( BTAPI *FTK_CALLBACK_FUNC ) ( unsigned int nSocket, const unsigned char *pData );

	//外部设置内网连接通知回调函数的指针
	//Define callback function for Nat PEER notification
	typedef BOOL ( BTAPI *FTK_NAT_PEER_CALLBACK ) ( BYTE *pInfoHash, const char * lpszIP, unsigned short nPort, BYTE *pPeerID );

	//外部设置任务开始前通知回调函数的指针
	typedef void ( BTAPI *FTK_BEFORE_DOWN_CALLBACK ) ( HDownloader hDownloader, HANDLE hEvent, BOOL bOnlyCheckFile = FALSE );

	//外部设置任务下载完毕后通知回调函数的指针
	typedef void ( BTAPI *FTK_ON_COMPLETE_CALLBACK ) ( HDownloader hDownloader, HANDLE hEvent, BOOL bOnlyCheckFile = FALSE );
	
	//////////////////////////////////////////////////////////////////////////
	//Libary License Interface
	
	//Set license key
	//设置license的密钥
	FTKERNELAPI_API void BTAPI FTK_License_Set( const char * lpszLicense );
	
	//////////////////////////////////////////////////////////////////////////
	//Library version information
	
	//获取当前库的版本信息, 例如: nMajor = 1, nMinor = 1 => ver: 1.1
	//Get library major version, example: nMajor = 1, nMinor = 1 => ver: 1.1
	FTKERNELAPI_API void BTAPI FTK_Version_Info( int &nMajor, int &nMinor );
	
	//////////////////////////////////////////////////////////////////////////
	//Define yourself protocol identifier string
	
	//Define yourself protocol identifier string(to avoid Router filter)
	//定义你自己的网络协议标识，可以避开某些网络运营商的协议封锁
	FTKERNELAPI_API void BTAPI FTK_Protocol_IDS( const char *pIDS, BOOL bAllowOtherIDS = FALSE );
	
	//////////////////////////////////////////////////////////////////////////
	//Define yourself user identifier
	
	//Define yourself user identifier(read by tracker)
	//定义自己的用户标识信息(Tracker服务器可以获取到)
	FTKERNELAPI_API void BTAPI FTK_Identifier_String10( const char *pS );
	
	//////////////////////////////////////////////////////////////////////////
	//Define yourself http tracker "UserAgent"
	
	//Define yourself http tracker "UserAgent"
	//定义自己的提交给http tracker的http协议中的"UserAgent"
	FTKERNELAPI_API void BTAPI FTK_Http_UserAgent( const char * lpszUA );
	
	//////////////////////////////////////////////////////////////////////////
	//Config INI file interface
	
	//创建一个新的配置文件句柄
	//Create a new Config INI file handle
	FTKERNELAPI_API HConfigIni BTAPI FTK_Config_Open();
	
	//销毁一个存在的配置文件句柄
	//Destroy a HConfigIni hanle
	FTKERNELAPI_API void BTAPI FTK_Config_Close( HConfigIni hConfigIni );
	
	//设置字符串选项
	//Set string value item
	FTKERNELAPI_API void BTAPI FTK_Config_SetStr( HConfigIni hConfigIni, const char * lpszName, const char * lpszValue );
	
	//设置整型值选项
	//Set integer value item
	FTKERNELAPI_API void BTAPI FTK_Config_SetInt( HConfigIni hConfigIni, const char * lpszName, QWORD nValue );
	
	//设置浮点型选项
	//Set float value item
	FTKERNELAPI_API void BTAPI FTK_Config_SetFloat( HConfigIni hConfigIni, const char * lpszName, double fValue );
	
	//////////////////////////////////////////////////////////////////////////
	//Context interface

	//预先初始化Context的是否需要截获系统的异常
	//Preinitialize param, whether to handle system exceptions
	FTKERNELAPI_API void BTAPI FTK_Context_PreInitException( BOOL bHandleException = TRUE );
	
	//环境初始化
	//Initialize context
	//@lpszIniFile: kernel configuration file - INI file
	FTKERNELAPI_API BOOL BTAPI FTK_Context_Init( const char * lpszIniFile = NULL, BOOL bLog = TRUE );
	
	//环境初始化2
	//Initialize context2
	//@hConfigIni: kernel configuration file handle - INI file
	FTKERNELAPI_API BOOL BTAPI FTK_Context_Init2( HConfigIni hConfigIni, BOOL bLog = TRUE );
	
	//设置被动通知的回调函数
	//Set callback funtion pointer
	FTKERNELAPI_API void BTAPI FTK_Context_NotifyCB( FTK_CALLBACK_FUNC pfn );

	//设置被动通知的回调函数
	//Set callback funtion pointer
	FTKERNELAPI_API void BTAPI FTK_Context_NotifyCB( FTK_CALLBACK_FUNC pfn );
	
	//释放整个环境
	//Release context
	FTKERNELAPI_API void BTAPI FTK_Context_Release();
	
	//整个环境的事件驱动引擎
	//Context event driver
	FTKERNELAPI_API BOOL BTAPI FTK_Context_Run();
	
	//强迫退出环境, 停止运行
	//在停止时要退出正在运行的线程所以可能要稍微等待
	//Stop context event driver
	FTKERNELAPI_API void BTAPI FTK_Context_Stop();
	
	//重新根据配置文件绑定端口
	//Rebind listen port
	FTKERNELAPI_API void BTAPI FTK_Context_ReBindListenPort();
	
	//判断是否已经初始化
	//Is context initialized?
	FTKERNELAPI_API BOOL BTAPI FTK_Context_IsInit();
	
	//是否监听成功了端口
	//Is context running?
	FTKERNELAPI_API BOOL BTAPI FTK_Context_IsRunning();
	
	//判断是否已经运行
	//Return context thread ID
	FTKERNELAPI_API DWORD BTAPI FTK_Context_GetThreadID();
	
	//获取线程的ID
	//Return listening port
	FTKERNELAPI_API USHORT BTAPI FTK_Context_GetListenPort();
	
	//重新指定端口绑定操作
	//Return binding ip address
	FTKERNELAPI_API const char *BTAPI FTK_Context_GetBindIP();
	
	//判断是否绑定端口操作成功
	//return bind listen port status
	FTKERNELAPI_API BOOL BTAPI FTK_Context_IsBindListenPort();

	//获取随机生成的用户的ID
	//Get random user IDENTIFIER
	FTKERNELAPI_API BYTE * BTAPI FTK_Context_GetMyPeerID();

	//修改强制内核提交Tracker的IP地址
	//Tell kernel the ip address to submit to tracker
	FTKERNELAPI_API void BTAPI FTK_Context_SetForceIP( const char * lpszIP );
	
	//设置兼容某些常见的错误torrent格式
	//Set to open some mistake mistaken TORRENT file
	FTKERNELAPI_API void BTAPI FTK_Context_TorrentFile( BOOL bValidEof = TRUE, BOOL bValidSort = TRUE );
	
	//设置日志的语言文件
	//Set language to write log
	FTKERNELAPI_API void BTAPI FTK_Context_OpenLanguageFile( const char * lpszLanguageFile );

	//释放传递给外部使用的连接对象的指针(配置回调函数使用, 增加回调处理时的灵活性)
	//Free socket handle to external module
	FTKERNELAPI_API void BTAPI FTK_Context_CloseExtSocket( unsigned int nSocket );

	//设置UDPTunnel的IP和地址
	//Set UDP tunnel IP and port
	FTKERNELAPI_API void BTAPI FTK_Context_SetUDPTunnelInfo( const char * lpszIP, unsigned short nPort );

	//获取总共运行的任务的个数
	//Get total torrent count
	FTKERNELAPI_API int BTAPI FTK_Context_GetTorrentCount();
	
	//////////////////////////////////////////////////////////////////////////
	//Context active sharing files

	//增加一个Hash值(大写的不带'%'的HEX字符串)和对应的信息进来
	FTKERNELAPI_API void BTAPI FTK_Context_ShareTorrent( const char * lpszInfoHex, const char * lpszAnnounce );
	
	//删除一个Hash值及其附带的对应信息
	FTKERNELAPI_API void BTAPI FTK_Context_UnshareTorrent( const char * lpszInfoHex );
	
	//////////////////////////////////////////////////////////////////////////
	//Downloader interface
	
	//Create a new HDownloader handle
	FTKERNELAPI_API HDownloader BTAPI FTK_Downloader_Open();
	
	//Destroy a HDownloader hanle
	FTKERNELAPI_API void BTAPI FTK_Downloader_Close( HDownloader hDownloader );
	
	//提前的初始化IP过滤对象的函数(FTK_Downloader_Init* 函数之前调用), 过滤某些段的IP地址, "ipfilter.dat" 文件和eMule(电骡)兼容
	//Previous Initialize IP filter object to filter some peer's IP, "ipfilter.dat" file is compatiable with eMule.
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_PreInitIPFilter( HDownloader hDownloader, const char * lpszIPFilterFile, UINT nLevel = 127 );
	
	//提前的初始化, 按照块的先后顺序进行下载(适用于边下载边播放的情况)
	//Previous Initialize, Tell kernel to sequential download piece
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitSEQMode( HDownloader hDownloader, int nSEQFileIndex = 0 );
	
	//预先初始化文件选择下载的优先级别
	//数组中，每个元素的值表示: -2:不下载, -1: 低, 0: 一般, 1:高
	//Previous Initialize, Tell kernel to Set priority of file
	//-2: no download, -1: low, 0: middle, 1: high
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitFilePriority( HDownloader hDownloader, char *pFilePriority, int nFilesCount );

	//预先初始化Tracker列表，使用外部提供的Tracker列表，替代Torrent文件中的Tracker列表
	//Tracker1;Tracker2;Tracker3|Tracker1;Tracker2|Tracker1;Tracker2
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitTrackers( HDownloader hDownloader, const char * lpszAnnouces );

	//预先初始化远程连接自己的Socket的句柄值
	//Previous Initialize, Tell kernel to add a remote [socket] to queue
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitSocket( HDownloader hDownloader, unsigned int nSocket );

	//预先初始化远程连接自己的UDP呼叫的信息
	//Previous Initialize, Tell kernel to add a remote ip and port to queue
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitSource( HDownloader hDownloader, const char *pchIP, unsigned short nPort, const BYTE *pPeerID, BYTE nTunnel );

	//预先初始化是否结束任务时提交STOP 事件到Tracker中
	//Previous Initialize, Tell kernel whether to report STOP event to TRACKER SERVER
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitStopEvent( HDownloader hDownloader, BOOL bReport = FALSE );
	
	//初始化下载对象
	//Initialize a HDownloader
	//@lpszTorrentFileName: a torrent file name
	//@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
	//@nPreAllocFileLen: length of preallocated array
	//@bOnlyCheckFile: only verify data of files
	//@lpszDestFileName: the downloaded filename
	//@lpszConfig: kernel configuration file - INI file
	//@lpszLogFileName: output log filename
	//@lpszStatusFileName: downloading status filename
	//@lpszDesKey: DES-EDE2 password
	//@nCodePage: code page of the torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_Init( 
		HDownloader hDownloader,
		const char * lpszTorrentFileName,
		BYTE *pPreAllocFile, int nPreAllocFileLen,
		BOOL bOnlyCheckFile = FALSE,
		const char * lpszDestFileName = NULL,
		const char * lpszConfig = NULL,
		const char * lpszLogFileName = NULL,
		const char * lpszStatusFileName = NULL,
		BOOL bQuicklySeed = FALSE,
		const char * lpszDesKey = NULL,
		UINT nCodePage = CP_ACP );
	
	//初始化下载对象2
	//Initialize a HDownloader
	//@lpszTorrentFileName: a torrent file name
	//@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
	//@nPreAllocFileLen: length of preallocated array
	//@bOnlyCheckFile: only verify data of files
	//@lpszDestFileName: the downloaded filename
	//@hConfigIni: kernel configuration file handle - INI file
	//@lpszLogFileName: output log filename
	//@lpszStatusFileName: downloading status filename
	//@lpszDesKey: DES-EDE2 password
	//@nCodePage: code page of the torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_Init2( 
		HDownloader hDownloader,
		const char * lpszTorrentFileName,
		BYTE *pPreAllocFile, int nPreAllocFileLen,
		BOOL bOnlyCheckFile = FALSE,
		const char * lpszDestFileName = NULL,
		HConfigIni hConfigIni = NULL,
		const char * lpszLogFileName = NULL,
		const char * lpszStatusFileName = NULL,
		BOOL bQuicklySeed = FALSE,
		const char * lpszDesKey = NULL,
		UINT nCodePage = CP_ACP );
	
	//初始化下载对象3
	//Initialize a HDownloader
	//@pData: a torrent binary object, a pointer to a binary torrent file content
	//@nLength: the length of a torrent binary object
	//@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
	//@nPreAllocFileLen: length of preallocated array
	//@bOnlyCheckFile: only verify data of files
	//@lpszDestFileName: the downloaded filename
	//@lpszConfig: kernel configuration file - INI file
	//@lpszLogFileName: output log filename
	//@lpszStatusFileName: downloading status filename
	//@lpszDesKey: DES-EDE2 password
	//@nCodePage: code page of the torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_Init3( 
		HDownloader hDownloader,
		const char *pData, int nLength,
		BYTE *pPreAllocFile, int nPreAllocFileLen,
		BOOL bOnlyCheckFile = FALSE,
		const char * lpszDestFileName = NULL,
		const char * lpszConfig = NULL,
		const char * lpszLogFileName = NULL,
		const char * lpszStatusFileName = NULL,
		BOOL bQuicklySeed = FALSE,
		const char * lpszDesKey = NULL,
		UINT nCodePage = CP_ACP );
	
	//初始化下载对象4
	//Initialize a HDownloader
	//@pData: a torrent binary object, a pointer to a binary torrent file content
	//@nLength: the length of a torrent binary object
	//@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
	//@nPreAllocFileLen: length of preallocated array
	//@bOnlyCheckFile: only verify data of files
	//@lpszDestFileName: the downloaded filename
	//@hConfigIni: kernel configuration file handle - INI file
	//@lpszLogFileName: output log filename
	//@lpszStatusFileName: downloading status filename
	//@lpszDesKey: DES-EDE2 password
	//@nCodePage: code page of the torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_Init4( 
		HDownloader hDownloader,
		const char *pData, int nLength,
		BYTE *pPreAllocFile, int nPreAllocFileLen,
		BOOL bOnlyCheckFile = FALSE,
		const char * lpszDestFileName = NULL,
		HConfigIni hConfigIni = NULL,
		const char * lpszLogFileName = NULL,
		const char * lpszStatusFileName = NULL,
		BOOL bQuicklySeed = FALSE,
		const char * lpszDesKey = NULL,
		UINT nCodePage = CP_ACP );

	//初始化下载对象5
	//Initialize a HDownloader
	//@lpszFTKLink: the link to download
	//@lpszTorrentFileName: a torrent file name
	//@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
	//@nPreAllocFileLen: length of preallocated array
	//@bOnlyCheckFile: only verify data of files
	//@lpszDestFileName: the downloaded filename
	//@lpszConfig: kernel configuration file - INI file
	//@lpszLogFileName: output log filename
	//@lpszStatusFileName: downloading status filename
	//@lpszDesKey: DES-EDE2 password
	//@nCodePage: code page of the torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_Init5( 
		HDownloader hDownloader,
		const char * lpszFTKLink,
		const char * lpszTorrentFileName,
		BYTE *pPreAllocFile, int nPreAllocFileLen,
		BOOL bOnlyCheckFile = FALSE,
		const char * lpszDestFileName = NULL,
		const char * lpszConfig = NULL,
		const char * lpszLogFileName = NULL,
		const char * lpszStatusFileName = NULL,
		BOOL bQuicklySeed = FALSE,
		const char * lpszDesKey = NULL,
		UINT nCodePage = CP_ACP );
	
	//初始化下载对象6
	//Initialize a HDownloader
	//@lpszFTKLink: the link to download
	//@lpszTorrentFileName: a torrent file name
	//@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
	//@nPreAllocFileLen: length of preallocated array
	//@bOnlyCheckFile: only verify data of files
	//@lpszDestFileName: the downloaded filename
	//@hConfigIni: kernel configuration file handle - INI file
	//@lpszLogFileName: output log filename
	//@lpszStatusFileName: downloading status filename
	//@lpszDesKey: DES-EDE2 password
	//@nCodePage: code page of the torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_Init6( 
		HDownloader hDownloader,
		const char * lpszFTKLink,
		const char * lpszTorrentFileName,
		BYTE *pPreAllocFile, int nPreAllocFileLen,
		BOOL bOnlyCheckFile = FALSE,
		const char * lpszDestFileName = NULL,
		HConfigIni hConfigIni = NULL,
		const char * lpszLogFileName = NULL,
		const char * lpszStatusFileName = NULL,
		BOOL bQuicklySeed = FALSE,
		const char * lpszDesKey = NULL,
		UINT nCodePage = CP_ACP );
	
	//释放下载对象
	//Release downloader handle
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_Release( HDownloader hDownloader );
	
	//执行下载线程
	//Execute downloader
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_Execute( HDownloader hDownloader );
	
	//暂停下载
	//Pause downloader
	FTKERNELAPI_API void BTAPI FTK_Downloader_Pause( HDownloader hDownloader );
	
	//恢复下载
	//Resume downloader
	FTKERNELAPI_API void BTAPI FTK_Downloader_Resume( HDownloader hDownloader );
	
	//是否已经初始化
	//Is downloader intialized?
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_IsInit( HDownloader hDownloader );
	
	//获取下载任务目前的阶段状态
	//Return downloader state
	FTKERNELAPI_API UINT BTAPI FTK_Downloader_GetState( HDownloader hDownloader );

	//获取下载任务目前的回调函数状态
	//Return downloader callback function state
	FTKERNELAPI_API UINT BTAPI FTK_Downloader_GetCBState( HDownloader hDownloader );
	
	//是否只是进行文件检查
	//Only checking file, don't downloading...
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_IsOnlyCheckFile( HDownloader hDownloader );
	
	//是否已经完成了下载(判断选择文件下载)
	//Is all selected files finished?
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_IsFinished( HDownloader hDownloader );
	
	//是否已经完成了下载(全部下载)
	//Is all files finished?
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_IsAllFinished( HDownloader hDownloader );
	
	//连接指定的Peer
	//Add external source peer
	FTKERNELAPI_API void BTAPI FTK_Downloader_AddSource( HDownloader hDownloader, const char *pchIP, unsigned short nPort, const BYTE *pPeerID = NULL, unsigned char nTunnel = 0 );
	
	//连接指定的User
	//Add external source peer(socket handle)
	FTKERNELAPI_API void BTAPI FTK_Downloader_AddSourceExt( HDownloader hDownloader, unsigned int nSocket );
	
	//外部动态增加辅助的Announce
	//Add external announce
	FTKERNELAPI_API void BTAPI FTK_Downloader_AddExtAnnounce( HDownloader hDownloader, const char * lpszAnnounce );
	
	//手动控制Announce马上进行连接
	//Reannounce manually
	FTKERNELAPI_API void BTAPI FTK_Downloader_ReannounceAll( HDownloader hDownloader );
	
	//按照块的先后顺序进行下载(适用于边下载边播放的情况)
	//Tell kernel to sequential download piece
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetSeqPicker( HDownloader hDownloader, BOOL bSeq = FALSE, int nSEQFileIndex = 0 );
	
	//设置下载文件的优先级别
	// -2:不下载, -1: 低, 0: 一般, 1:高
	//Set priority of file
	//-2: no download, -1: low, 0: middle, 1: high
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetFilePriority( HDownloader hDownloader, int nIndex, char chPriority = 0, BOOL bDoPriority = TRUE );
	
	//强制立刻重新将文件的优先级赋值给Piece
	//Force to set priority of all piece immediately 
	FTKERNELAPI_API void BTAPI FTK_Downloader_ForceFilePriority( HDownloader hDownloader );
	
	//外部调用, 手动设置最大的下载率限制(0.0表示没有限制)
	//Set fixed max download rate
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetFixMaxDownloadRate( HDownloader hDownloader, double fMaxDownloadRate = 0.0 );
	
	//外部调用, 获取手动设置最大的下载率限制(0.0表示没有限制)
	//Get fixed max download rate
	FTKERNELAPI_API double BTAPI FTK_Downloader_GetFixMaxDownloadRate( HDownloader hDownloader );
	
	//外部调用, 手动设置最大的上传率限制(0.0表示没有限制)
	//Set fixed max upload rate
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetFixMaxUploadRate( HDownloader hDownloader, double fMaxUploadRate = 0.0 );
	
	//外部调用, 获取手动设置最大的上传率限制(0.0表示没有限制)
	//Get fixed max upload rate
	FTKERNELAPI_API double BTAPI FTK_Downloader_GetFixMaxUploadRate( HDownloader hDownloader );
	
	//主动限制某些特定的种子服务器(SEED), 给自己的最大的上传率(0表示没有限制, 注意单位是: KB)
	//Set fixed max upload rate of SOME CERTAIN SEED to me, 0 means no limit, UNIT is KB 
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetSeedMaxUPSpeed( HDownloader hDownloader, unsigned short nSpeed = 0 );
	
	//多少秒中内，禁止某个IP的连接, 只在当前任务存在期间有效
	//Ban IP for X seconds, ONLY for the current active HDownloader 
	FTKERNELAPI_API void BTAPI FTK_Downloader_BanPeerIP( HDownloader hDownloader, const char * lpszIP, UINT nBannedSeconds );

	//外部设置内网连接通知回调函数的指针
	//Set the callback function pointer for Nat PEER notification
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetNatPeerCB( HDownloader hDownloader, FTK_NAT_PEER_CALLBACK fnNatPeerCB );

	//外部设置通知外部进行下载前处理的回掉函数
	//Set the callback function pointer for BEFORE DOWNLOAD notification
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetBeforeDownCB( HDownloader hDownloader, FTK_BEFORE_DOWN_CALLBACK fnBeforeDown );

	//外部设置通知外部下载完毕的回掉函数
	//Set the callback function pointer for ON COMPLETE notification
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetOnComleteCB( HDownloader hDownloader, FTK_ON_COMPLETE_CALLBACK fnOnComlete );
	
	//获取线程的ID
	//Get thread ID
	FTKERNELAPI_API DWORD BTAPI FTK_Downloader_GetThreadID( HDownloader hDownloader );
	
	//////////////////////////////////////////////////////////////////////////
	//全局参数设置
	//Global settings
	
	//将某个Torrent文件的SHA1值加入队列
	//Add torrent into SHA1 list
	FTKERNELAPI_API void BTAPI FTK_GlobalVar_AddTorrentSHA1( const char * lpszSHA1, HDownloader hDownloader );
	
	//将某个Torrent文件的SHA1值从队列中删除
	//Remove torrent from SHA1 list
	FTKERNELAPI_API void BTAPI FTK_GlobalVar_RemoveTorrentSHA1( const char * lpszSHA1 );

	//////////////////////////////////////////////////////////////////////////
	//特殊用途的函数，实现非阻塞方式关闭当前正在运行的任务
	//Special functions, to asyn-close downloader handle

	//将某个InfoHash的句柄加入到异步关闭队列
	//Add a downloader handle into asyn-close queue
	FTKERNELAPI_API void BTAPI FTK_Special_AsynClose( const char * lpszSHA1, HDownloader hDownloader );
	
	//查询某个InfoHash的句柄是否还在一步关闭队列中存在
	//Get handle's state in the asyn-close queue
	FTKERNELAPI_API BOOL BTAPI FTK_Special_Exists( const char * lpszSHA1 );
	
	//////////////////////////////////////////////////////////////////////////
	//代理服务器函数列表
	//Proxy interface
	
	//设置仅在连接Tracker时使用代理服务器
	//Only tracker using proxy settings
	FTKERNELAPI_API void BTAPI FTK_Proxy_SetOnlyTracker( BOOL bOnlyTracker = FALSE );
	
	//清空当前的代理信息(仅用于PROXYTYPE_NOPROXY)
	//Only PROXYTYPE_NOPROXY
	FTKERNELAPI_API void BTAPI FTK_Proxy_SetType( int nProxyType );
	
	//设置代理(不能是PROXYTYPE_NOPROXY)
	//May not be PROXYTYPE_NOPROXY
	FTKERNELAPI_API void BTAPI FTK_Proxy_SetProxy( int nProxyType, const char * pProxyHost, int ProxyPort );
	
	//设置SOCKS5和HTTP1.1需要认证信息的代理
	//Only SOCKS5 and HTTP1.1 proxies
	FTKERNELAPI_API void BTAPI FTK_Proxy_SetAuthProxy( int nProxyType, const char * pProxyHost, int ProxyPort, const char * pProxyUser, const char * pProxyPass );
	
	//获取代理的类型
	//Return proxy type
	FTKERNELAPI_API int BTAPI FTK_Proxy_GetProxyType();
	
	//////////////////////////////////////////////////////////////////////////
	//Downloader statistic information interface

	//获取总共文件的大小
	//Get the size of all files
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetTotalFileSize( HDownloader hDownloader );
	
	//获取总共已经下载(验证成功)的数据
	//Get the size of having received data for all file
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetTotalFileHaveSize( HDownloader hDownloader );

	//获取总共要选择下载的的数据长度
	//Get the size of all selected file
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetSelectedFileSize( HDownloader hDownloader );
	
	//获取选择已经下载(验证成功)的数据
	//Get the size of having received data for a file
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetSelectedFileHaveSize( HDownloader hDownloader );
	
	//获取已经顺序下载的目前可以从头开始播放的数据长度
	//Get the size of sequential piece from file front
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetStartSeqFileSize( HDownloader hDownloader );
	
	//获取最近一次下载的字节数
	//Get the size of lasted receiving data
	FTKERNELAPI_API DWORD BTAPI FTK_Stat_GetLastDataSize( HDownloader hDownloader );
	
	//获取总共丢弃的字节数
	//Get the size of bad data
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetBadDataSize( HDownloader hDownloader );
	
	//当前总共的连接的个数
	//Get the number of total peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetTotalPeerCount( HDownloader hDownloader );
	
	//当前主动连接的个数
	//Get the number of active peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetActivePeerCount( HDownloader hDownloader );
	
	//当前的被动连接的个数
	//Get the number of passive peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetPassivePeerCount( HDownloader hDownloader );
	
	//当前正在连接中的个数
	//Get number of connecting peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetConnectingPeerCount( HDownloader hDownloader );
	
	//获取已经连接的种子的个数
	//Get number of seed
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetSeedCount( HDownloader hDownloader );
	
	//获取正在上传的连接的个数
	//Get the number of uploading peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetUploadPeerCount( HDownloader hDownloader );
	
	//获取正在下载的连接的个数
	//Get the number of downloading peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetDownloadPeerCount( HDownloader hDownloader );
	
	//获取总共可以获取的Seed的个数
	//Get the number of total available seed
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetTotalAvailSeedCount( HDownloader hDownloader );
	
	//获取总共可以获取的Peer的个数
	//Get the number of peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetTotalAvailPeerCount( HDownloader hDownloader );
	
	//旧的种子的个数
	//Get old seed number
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetOldSeedPeerCount( HDownloader hDownloader );
	
	//获取是否至少已经有一个Tracker连接成功
	//Is any tracker successfull?
	FTKERNELAPI_API BOOL BTAPI FTK_Stat_IsAnyTrackerOK( HDownloader hDownloader );
	
	//本次运行已经下载的数据长度
	//Get downloaded bytes
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetDownloaded( HDownloader hDownloader );
	
	//本次运行已经上传的数据长度
	//Get uploaded bytes
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetUploaded( HDownloader hDownloader );
	
	//本次已经运行时间(运行时间不同与下载时间)
	//Get total running time
	FTKERNELAPI_API double BTAPI FTK_Stat_GetRunningTime( HDownloader hDownloader );
	
	//本次下载的时间(如果是做种, 则下载时间永远为0)
	//Get total downloaded time
	FTKERNELAPI_API double BTAPI FTK_Stat_GetDownloadTime( HDownloader hDownloader );
	
	//本次下载剩余的时间, 根据下载率计算
	//Get the left time to download
	FTKERNELAPI_API double BTAPI FTK_Stat_GetLeftTime( HDownloader hDownloader );
	
	//获取当前的上传率
	//Get upload rate
	FTKERNELAPI_API double BTAPI FTK_Stat_GetUploadRate( HDownloader hDownloader );
	
	//获取当前的下载率
	//Get downloading rate
	FTKERNELAPI_API double BTAPI FTK_Stat_GetDownloadRate( HDownloader hDownloader );
	
	//获取指定的Piece的下载进度
	//Get the progress of a piece
	FTKERNELAPI_API void BTAPI FTK_Stat_GetPieceState( HDownloader hDownloader, BYTE *pPiece, int nCount );
	
	//获取检查文件的进度
	//Get the progress of cheching piece
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetCheckPieceSize( HDownloader hDownloader );
	
	//获取检查的Piece的个数
	//Get number of checked piece
	FTKERNELAPI_API DWORD BTAPI FTK_Stat_GetCheckPieceCount( HDownloader hDownloader );
	
	//获取已经分配空间的大小
	//Get the size of allocated file
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetAllocSpaceSize( HDownloader hDownloader );
	
	//获取当前的健康率
	//Get healthy rate
	FTKERNELAPI_API double BTAPI FTK_Stat_GetHealthRate( HDownloader hDownloader );
	
	//获取当前的最大缓存大小
	//Get the size of max cache
	FTKERNELAPI_API DWORD BTAPI FTK_Stat_GetMaxCacheSize( HDownloader hDownloader );
	
	//获取已经使用的缓存大小
	//Get the size of used cache
	FTKERNELAPI_API DWORD BTAPI FTK_Stat_GetUseCacheSize( HDownloader hDownloader );
	
	//获取本次写硬盘的总的次数
	//Get writed disk count
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetWriteDiskCount( HDownloader hDownloader );
	
	//获取本次真正写硬盘的次数
	//Get really writed disk count
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetRealWriteDiskCount( HDownloader hDownloader );
	
	//获取本次读硬盘的总的次数
	//Get readed disk count
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetReadDiskCount( HDownloader hDownloader );
	
	//获取本次真正读硬盘的次数
	//Get really readed disk count
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetRealReadDiskCount( HDownloader hDownloader );
	
	//获取写硬盘的频率(次/秒)
	//Get writing disk frenqence(number/second)
	FTKERNELAPI_API double BTAPI FTK_Stat_GetWriteDiskFrenq( HDownloader hDownloader );
	
	//获取真正写硬盘的频率(次/秒)
	//Get really writing disk frenqence(number/second)
	FTKERNELAPI_API double BTAPI FTK_Stat_GetRealWriteDiskFrenq( HDownloader hDownloader );
	
	//获取读硬盘的频率(次/秒)
	//Get reading disk frenqence(number/second)
	FTKERNELAPI_API double BTAPI FTK_Stat_GetReadDiskFrenq( HDownloader hDownloader );
	
	//获取真正读硬盘的频率(次/秒)
	//Get really reading disk frenqence(number/second)
	FTKERNELAPI_API double BTAPI FTK_Stat_GetRealReadDiskFrenq( HDownloader hDownloader );
	
	//获取当前日志文件的路径+名称
	//Get log file name
	FTKERNELAPI_API void BTAPI FTK_Stat_GetLogPathFileName( HDownloader hDownloader, char *lpszFileName );
	
	//获取指定的文件的进度
	//Get the progress of a file
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetFileHaveSize( HDownloader hDownloader, int nIndex );
	
	//获取当前用户状态信息的列表
	//Get the peers information
	FTKERNELAPI_API void BTAPI FTK_Stat_GetPeerData( HDownloader hDownloader, _tagPeerData *pData, int &nRetCount, int nMaxCount );
	
	//获取当前部分用户状态信息的列表
	//Get the some peers information
	FTKERNELAPI_API void BTAPI FTK_Stat_GetPeerRangeData( HDownloader hDownloader, _tagPeerData *pData, int nFrom, int nTo, int &nRetCount, int nMaxCount, BOOL bExtInfo = FALSE );
	
	//获取当前用户状态信息的列表(只获取IP和端口)
	//Get the peers information(only IP and port)
	FTKERNELAPI_API void BTAPI FTK_Stat_GetMiniPeerData( HDownloader hDownloader, _tagMiniPeerData *pData, int &nRetCount, int nMaxCount );
	
	//获取当前Announce状态信息的列表
	//Get the status of announces
	FTKERNELAPI_API void BTAPI FTK_Stat_GetAnnounceData( HDownloader hDownloader, _tagAnnounceData *pData, int &nRetCount, int nMaxCount );
	
	//获取当前任务的调试信息
	//Get the debug information of downloader
	FTKERNELAPI_API const char * BTAPI FTK_Stat_GetBTDownloaderInfo( HDownloader hDownloader );
	
	//////////////////////////////////////////////////////////////////////////
	//打开Torrent文件获取信息的函数列表
	//Torrent file interface
	
	//判断是不是自己定义的加密的Torrent文件
	//Return boolean, tell us is a cipher torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_Torrent_IsCipherTorrent( const char * lpszFileName );
	
	//执行从文件中读取数据并初始化对象操作
	//Open a torrent file handle
	FTKERNELAPI_API HTorrentFile BTAPI FTK_Torrent_Open( const char * lpszFileName, UINT nCodePage = CP_ACP, const char * lpszDesKey = NULL, BOOL bValidEOF = TRUE, BOOL bValidSort = TRUE );
	
	//执行从文件中读取数据并初始化对象操作, 如果失败, 返回错误信息
	//Open a torrent file handle, if failed, return error information
	FTKERNELAPI_API HTorrentFile BTAPI FTK_Torrent_SafeOpen( const char * lpszFileName, UINT nCodePage = CP_ACP, const char * lpszDesKey = NULL, BOOL bValidEOF = TRUE, BOOL bValidSort = TRUE, _tagErrInfo *pErrInfo = NULL );
	
	//判断是不是自己定义的加密的Torrent数据流对象
	//Return boolean, tell us is a cipher torrent binary data
	FTKERNELAPI_API BOOL BTAPI FTK_Torrent_IsCipherTorrentObj( const BYTE *pData, int nLength );
	
	//执行从Torrent binary object中读取数据并初始化对象操作
	//Open a torrent binary object
	FTKERNELAPI_API HTorrentFile BTAPI FTK_Torrent_OpenObj( const BYTE *pData, int nLength, UINT nCodePage = CP_ACP, const char * lpszDesKey = NULL, BOOL bValidEOF = TRUE, BOOL bValidSort = TRUE, _tagErrInfo *pErrInfo = NULL );
	
	//关闭当前打开的Torrent文件
	//Close Torrent file handle
	FTKERNELAPI_API void BTAPI FTK_Torrent_Close( HTorrentFile hTorrentFile );
	
	//判断是目录还是文件
	//Return boolean, tell us is only a single file in torrent
	FTKERNELAPI_API BOOL BTAPI FTK_Torrent_IsFile( HTorrentFile hTorrentFile );
	
	//获取 Torrent 名称
	//Get the name of torrent file
	FTKERNELAPI_API const char * BTAPI FTK_Torrent_GetTorrentName( HTorrentFile hTorrentFile );
	
	//获取torrent中的文件的个数(至少一个)
	//Get total number of files
	FTKERNELAPI_API int BTAPI FTK_Torrent_GetFilesCount( HTorrentFile hTorrentFile );
	
	//获取torrent中的文件列表(至少一个)
	//Get a pointer to file list
	FTKERNELAPI_API void BTAPI FTK_Torrent_GetFiles( HTorrentFile hTorrentFile, _tagFileInfo *pFileInfo );
	
	//获取torrent中的文件列表中的某个文件的信息
	//Get a pointer to a file of file list
	FTKERNELAPI_API void BTAPI FTK_Torrent_GetFileInfo( HTorrentFile hTorrentFile, int nIndex, _tagFileInfo *pFileInfo );

	//获取torrent中的某个文件的SHA1[SHA1 传入指针的长度必须是20个字节]
	//Get SHA1 of a file in the file list[SHA1 pointer to a array[20] of BYTE]
	FTKERNELAPI_API void BTAPI FTK_Torrent_GetFileSHA1( HTorrentFile hTorrentFile, int nIndex, BYTE *pFileSHA1 );

	//获取Info的Hash值, 内部使用
	//Get the binary info hash of torrent file
	FTKERNELAPI_API const BYTE * BTAPI FTK_Torrent_GetInfoHash( HTorrentFile hTorrentFile );
	
	//获取info的Hash值, 十六进制
	//Get the hex encoding info hash of torrent file
	FTKERNELAPI_API const char * BTAPI FTK_Torrent_GetHexInfoHash( HTorrentFile hTorrentFile );
	
	//获取 main annouce url
	//Get mainb announce url
	FTKERNELAPI_API const char * BTAPI FTK_Torrent_GetMainAnnounce( HTorrentFile hTorrentFile );
	
	//获取 Announce 分组的个数
	//Get the number of all announce list
	FTKERNELAPI_API int BTAPI FTK_Torrent_GetAnnouncesCount( HTorrentFile hTorrentFile );
	
	//获取指定的 Announce 分组包含的Announce的个数
	//Get the size of a announce list
	FTKERNELAPI_API int BTAPI FTK_Torrent_GetAnnounceSize( HTorrentFile hTorrentFile, int nGroupIndex );
	
	//获取指定的 Announce 分组中指定位置的Announce
	//Get a annoucne of a announce list
	FTKERNELAPI_API const char * BTAPI FTK_Torrent_GetAnnouncesVal( HTorrentFile hTorrentFile, int nGroupIndex, int nIndex );
	
	//获取 注释
	//Get the comments
	FTKERNELAPI_API const char * BTAPI FTK_Torrent_GetComments( HTorrentFile hTorrentFile );
	
	//获取 Torrent 创建时间
	//Get the creation time of torrent file
	FTKERNELAPI_API time_t BTAPI FTK_Torrent_GetCreateTime( HTorrentFile hTorrentFile );
	
	//获取piece块的大小
	//Get the size of piece
	FTKERNELAPI_API DWORD BTAPI FTK_Torrent_GetPieceSize( HTorrentFile hTorrentFile );
	
	//获取文件的大小
	//Get the total file size to transfer
	FTKERNELAPI_API QWORD BTAPI FTK_Torrent_GetFileSize( HTorrentFile hTorrentFile );
	
	//Piece块的个数
	//Get the total number of piece
	FTKERNELAPI_API DWORD BTAPI FTK_Torrent_GetPieceCount( HTorrentFile hTorrentFile );
	
	//获取Piece Hash 的列表
	//Get a pointer to piece hash list
	FTKERNELAPI_API const BYTE *BTAPI FTK_Torrent_GetPieceHashList( HTorrentFile hTorrentFile );

	//释放PieceHash列表
	//Release piece hash memory
	FTKERNELAPI_API void BTAPI FTK_Torrent_FreePieceHashList( HTorrentFile hTorrentFile );
	
	//获取Torrent文件的语言编码
	//Get language code page of torrent file
	FTKERNELAPI_API UINT BTAPI FTK_Torrent_GetLanCodePage( HTorrentFile hTorrentFile );
	
	//////////////////////////////////////////////////////////////////////////
	//制作Torrent文件的函数列表
	//Create torrent file interface
	
	//打开一个制作torrent文件的句柄
	//Open a making torrent handle
	FTKERNELAPI_API HMakeTorrent BTAPI FTK_MT_Open();
	
	//关闭打开的制作Torrent文件的句柄
	//Close a making torrent handle
	FTKERNELAPI_API void BTAPI FTK_MT_Close( HMakeTorrent hMakeTorrent );
	
	//执行生成对象的操作
	//Start to making torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_MT_MakeTorrent( HMakeTorrent hMakeTorrent );
	
	//停止Torrent文件制作
	//Stop making torrent file
	FTKERNELAPI_API void BTAPI FTK_MT_StopMake( HMakeTorrent hMakeTorrent );

	//获取Info的Hash值, 内部使用
	//Get the binary info hash of torrent file
	FTKERNELAPI_API const BYTE * BTAPI FTK_MT_GetInfoHash( HMakeTorrent hMakeTorrent );
	
	//获取info的Hash值, 十六进制
	//Get the hex encoding info hash of torrent file
	FTKERNELAPI_API const char * BTAPI FTK_MT_GetHexInfoHash( HMakeTorrent hMakeTorrent );

	//设置在文件信息中包含单个文件的SHA1值
	//Set to bring SHA1 of file in dictionary
	FTKERNELAPI_API void BTAPI FTK_MT_SetFileSHA1( HMakeTorrent hMakeTorrent, BOOL bMakeSHA1 = TRUE );
	
	//获取制作文件的进度
	//Get progress of making torrent file
	FTKERNELAPI_API double BTAPI FTK_MT_GetMTProgress( HMakeTorrent hMakeTorrent );
	
	//另存为Torrent文件
	//Save as a torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_MT_SaveAsTorrentFile( HMakeTorrent hMakeTorrent, const char * lpszFileName, const char * lpszDesKey = NULL );
	
	//设置 annouce url
	//Set a main announce url
	FTKERNELAPI_API void BTAPI FTK_MT_SetAnnounceUrl( HMakeTorrent hMakeTorrent, const char * lpszValue );
	
	//添加额外的Announce 列表
	//Add a announce list
	FTKERNELAPI_API void BTAPI FTK_MT_AddAnnounceList( HMakeTorrent hMakeTorrent, const char * Announces[], int nCount );
	
	//添加额外的Announce 列表, example: announce1;announce2;announce3;
	//Add a announce list, example: announce1;announce2;announce3;
	FTKERNELAPI_API void BTAPI FTK_MT_AddAnnounceList2( HMakeTorrent hMakeTorrent, const char * lpszAnnounces );
	
	//清空额外的Announce 列表
	//Clear all announce list
	FTKERNELAPI_API void BTAPI FTK_MT_ClearAnnounceList( HMakeTorrent hMakeTorrent );

	//设置 torrent中的文件或者目录的名称, 缺省自动从制作的文件名称中获取
	//Set real name
	FTKERNELAPI_API void BTAPI FTK_MT_SetRealName( HMakeTorrent hMakeTorrent, const char * lpszValue );
	
	//设置 注释
	//Set comments
	FTKERNELAPI_API void BTAPI FTK_MT_SetComments( HMakeTorrent hMakeTorrent, const char * lpszValue );
	
	//设置piece块的大小
	//Set piece size to making torrent file
	FTKERNELAPI_API void BTAPI FTK_MT_SetPieceSize( HMakeTorrent hMakeTorrent, DWORD dwPieceSize );

	//获取piece块的大小
	//Get piece size of torrent file
	FTKERNELAPI_API DWORD BTAPI FTK_MT_GetPieceSize( HMakeTorrent hMakeTorrent );
	
	//设置torrent中的文件
	//Set the sourece file to making torrent file
	FTKERNELAPI_API void BTAPI FTK_MT_SetFile( HMakeTorrent hMakeTorrent, const char * lpszFileName );
	
	//设置torrent中的文件目录(多个文件)
	//Set the source path to making torrent file
	FTKERNELAPI_API void BTAPI FTK_MT_SetPath( HMakeTorrent hMakeTorrent, const char * lpszPathName );
	
	//设置Torrent文件的语言代码(只对文件名称, 注释等有效)
	//Set language code of torrent file
	FTKERNELAPI_API void BTAPI FTK_MT_SetLangCodePage( HMakeTorrent hMakeTorrent, UINT nCodePage = CP_ACP );
	
	//////////////////////////////////////////////////////////////////////////
	//Tracker interface, to get status of one torrent from tracker: peer count/seed count
	
	//HTTP tracker接口， 用于获取http Tracker某任务的状态信息
	//HTTP Tracker interface, to get status of one torrent from http tracker
	FTKERNELAPI_API BOOL BTAPI FTK_Tracker_Http1( const char * lpszTracker, const unsigned char *pInfoHash, QWORD qwFileSize, UINT &nPeerCount, UINT &nSeedCount, BOOL &bNetwordErr, const char * lpszErrInfo = NULL, int nLength = 0 );
	
	//HTTP tracker接口， 用于获取http Tracker某任务的状态信息
	//HTTP Tracker interface, to get status of one torrent from http tracker
	FTKERNELAPI_API BOOL BTAPI FTK_Tracker_Http2( const char * lpszTorrentFileName, UINT &nPeerCount, UINT &nSeedCount, BOOL &bNetwordErr, const char * lpszErrInfo = NULL, int nLength = 0 );
	
	//UDP tracker接口， 用于获取UDP Tracker某任务的状态信息
	//UDP Tracker interface, to get status of one torrent from UDP tracker
	FTKERNELAPI_API BOOL BTAPI FTK_Tracker_UDP1( const char * lpszTracker, const unsigned char *pInfoHash, QWORD qwFileSize, UINT &nPeerCount, UINT &nSeedCount, BOOL &bNetwordErr, const char * lpszErrInfo = NULL, int nLength = 0 );
	
	//UDP tracker接口， 用于获取UDP Tracker某任务的状态信息
	//UDP Tracker interface, to get status of one torrent from UDP tracker
	FTKERNELAPI_API BOOL BTAPI FTK_Tracker_UDP2( const char * lpszTorrentFileName, UINT &nPeerCount, UINT &nSeedCount, BOOL &bNetwordErr, const char * lpszErrInfo = NULL, int nLength = 0 );
	
	//////////////////////////////////////////////////////////////////////////
	//Disk cache Settings
	
	//Set Disk cache size
	//设置磁盘缓存的大小
	FTKERNELAPI_API void BTAPI FTK_Disk_SetCache( UINT nMinCacheSize, UINT nMaxCacheSize, UINT nPhyMemorySize );
	
	//////////////////////////////////////////////////////////////////////////
	//Windows environment related interfaces
	
	//Get local machine ip address(get the first ip or best ip if there are more than one NICs)
	//获取本机的IP地址(在有多个的情况下，选择第一个，或者按照一定算法选择最合适的一个)
	FTKERNELAPI_API const char * BTAPI FTK_Win_GetLocalIP( BOOL &bPrivateIP );
	
	//Open Windows ICS/ICF(Windows XP/Windows 2003) 
	//打开操作系统的网络连接防火墙和网络连接共享(Windows XP/Windows 2003)
	FTKERNELAPI_API BOOL BTAPI FTK_Win_OpenWinXPICSF( unsigned short nPort, BOOL &bOpenFirewall, BOOL &bPortMapping, BYTE nProtocol = WCXT_TCP_PORT, const char * lpszIP = NULL, const char * lpszAppName = NULL );
	
	//Open UPnP port mapping(Win9x/WinME/Win2000/WinXP/Win2003)
	//执行对于支持UPnP协议的Router进行自动的端口映射配置(内网处于Router后的机器必用)
	FTKERNELAPI_API BOOL BTAPI FTK_Win_AddUPnPPortMapping( unsigned short nPort, BYTE nProtocol = WCXT_TCP_PORT, const char * lpszIP = NULL );
	
	//Patch Windows XP SP2 tcpip.sys file for best TCP/IP performance
	//对于Windows XP SP2 的tcpip.sys打补丁，破解连接数的限制，提高网络性能
	FTKERNELAPI_API int BTAPI FTK_Win_PacthSP2TCPIPLimitFile( int nLimit = 10 );
	
	//////////////////////////////////////////////////////////////////////////
	//extendted functions
	
	//Get CRC of DATA
	//计算一段数据的CRC校验值
	FTKERNELAPI_API BOOL FTK_Ext_GetCRC( BYTE *pData, int nLength, DWORD &dwCRC );

	//Encrypt data with DES algorithm
	//使用DES算法对数据进行加密, 并输出密文
	FTKERNELAPI_API BOOL BTAPI FTK_Ext_EncryptWithDes( BYTE *pPlaintext, int nPlaintextLen, BYTE *pCiphertext, int &nCiphertextLen, const char *pPassPhrase );
	
	//Decrypt data with DES algorithm
	//使用DES算法对数据进行解密, 并输出
	FTKERNELAPI_API BOOL BTAPI FTK_Ext_DecryptWithDes( BYTE *pCiphertext, int nCiphertextLen, BYTE *pPlaintext, int &nPlaintextLen, const char *passPhrase );

	//获取指定的文件的SHA1值
	//Get SHA1 of a file
	FTKERNELAPI_API BOOL BTAPI FTK_Ext_GetFileSHA1( const char *lpszFileName, BYTE *pSHA1 );

	//////////////////////////////////////////////////////////////////////////
	//Http functions

	//Open a http proxy settings handle
	//打开一个Http代理设置句柄
	FTKERNELAPI_API HHttpProxy BTAPI Http_Proxy_Open();

	//Close a http proxy settings handle
	//关闭一个Http代理设置的句柄
	FTKERNELAPI_API void BTAPI Http_Proxy_Close( HHttpProxy hHttpProxy );

	//Only tracker using proxy settings
	//设置仅在连接Tracker时使用代理服务器
	FTKERNELAPI_API void BTAPI Http_Proxy_SetOnlyTracker( HHttpProxy hHttpProxy, BOOL bOnlyTracker = FALSE );

	//Only PROXYTYPE_NOPROXY
	//清空当前的代理信息(仅用于PROXYTYPE_NOPROXY)
	FTKERNELAPI_API void BTAPI Http_Proxy_SetType( HHttpProxy hHttpProxy, int nProxyType );

	//May not be PROXYTYPE_NOPROXY
	//设置代理(不能是PROXYTYPE_NOPROXY)
	FTKERNELAPI_API void BTAPI Http_Proxy_SetProxy( HHttpProxy hHttpProxy, int nProxyType, const char * pProxyHost, int ProxyPort );

	//Only SOCKS5 and HTTP1.1 proxies
	//设置SOCKS5和HTTP1.1需要认证信息的代理
	FTKERNELAPI_API void BTAPI Http_Proxy_SetAuthProxy( HHttpProxy hHttpProxy, int nProxyType, const char * pProxyHost, int ProxyPort, const char * pProxyUser, const char * pProxyPass );
	
	//Return proxy type
	//获取代理的类型
	FTKERNELAPI_API int BTAPI Http_Proxy_GetProxyType( HHttpProxy hHttpProxy );

	//////////////////////////////////////////////////////////////////////////

	//Open a http connection handle
	//打开一个Http连接句柄
	FTKERNELAPI_API HHttpConnection BTAPI Http_URL_Open();

	//Close a http connection handle
	//关闭一个Http连接句柄
	FTKERNELAPI_API void BTAPI Http_URL_Close( HHttpConnection hHttpConn );

	//To stop http connecting
	//停止一个正在连接的Http句柄
	FTKERNELAPI_API void BTAPI Http_URL_Stop( HHttpConnection hHttpConn );

	//To cancel http connection, release resource
	//取消一个正在连接的Http句柄, 并且释放资源
	FTKERNELAPI_API void BTAPI Http_URL_Cancel( HHttpConnection hHttpConn );

	//Download from URL to write into a local file
	//从指定的地址下载http数据并将数据保存到指定的本地文件中
	FTKERNELAPI_API BOOL BTAPI Http_URL_Download2File( HHttpConnection hHttpConn, const char * lpszURL, const char * lpszPathFileName, HHttpProxy hHttpProxy = NULL, UINT nTimeOut = 5000, UINT nDNSTimeOut = 5000, HANDLE hEvent = NULL );

	//Download from URL to HHttpResponse object
	//从指定的地址下载http数据并将数据保存到HHttpResponse句柄对象中
	FTKERNELAPI_API HHttpResponse BTAPI Http_URL_Download2Memory( HHttpConnection hHttpConn, const char * lpszURL, HHttpProxy hHttpProxy = NULL, UINT nTimeOut = 5000, UINT nDNSTimeOut = 5000, HANDLE hEvent = NULL );

	//////////////////////////////////////////////////////////////////////////
	
	//从HHttpResponse对象中获取数据的长度
	//Get data length from HHttpResponse object
	FTKERNELAPI_API UINT BTAPI Http_HR_Length( HHttpResponse hHttpResponse );

	//从HHttpResponse对象中获取数据的指针
	//Get data poiter from HHttpResponse object
	FTKERNELAPI_API BYTE * BTAPI Http_HR_Data( HHttpResponse hHttpResponse );

	//释放HHttpResponse对象
	//Free HHttpResponse object
	FTKERNELAPI_API void BTAPI Http_HR_Free( HHttpResponse hHttpResponse );

	//////////////////////////////////////////////////////////////////////////
	
	//判断是否返回的是Chunk编码的数据
	//Is data of chunk encoding
	FTKERNELAPI_API BOOL BTAPI Http_Chunk_IsEncoding( HHttpResponse hHttpResponse );

	//获取Chunk解码后的的数据
	//Encode chunk data to HHttpResponse object
	FTKERNELAPI_API HHttpResponse BTAPI Http_Chunk_Decode( HHttpResponse hHttpResponse );
		
	//////////////////////////////////////////////////////////////////////////
	//流媒体相关的一些辅助函数
	//MEDIA related functions

	//获取ASF/WMV 编码的流媒体文件的'码率'
	//Get ASF/WMV encoding file's Bitrate
	FTKERNELAPI_API unsigned int BTAPI FTK_Media_GetAsfBitrate( const char *lpszAsfFileName );

	//获取RM/RMVB 编码的流媒体文件的'码率'
	//Get RM/RMVB encoding file's Bitrate
	FTKERNELAPI_API unsigned int BTAPI FTK_Media_GetRMBitrate( const char *lpszRMFileName );

	//////////////////////////////////////////////////////////////////////////

	//验证链接的合法性
	//Verify the 'ftk://****' link URL
	FTKERNELAPI_API BOOL BTAPI FTK_Link_Verify( const char *lpszLinkURL );

	//生成下载的链接
	//Get the 'ftk://****' link URL
	FTKERNELAPI_API BOOL BTAPI FTK_Link_GetLink( const char *lpszHexHash, const char *lpszFileName, QWORD qwFileSize, DWORD dwPieceSize, char *lpszOutURL, int nOutLength );

	//生成下载的链接(从指定的Torrent文件中)
	//Get the 'ftk://****' link URL by TORRENT file
	FTKERNELAPI_API BOOL BTAPI FTK_Link_GetLink2( const char *lpszTorrentFileName, char *lpszOutURL, int nOutLength, const char *lpszDesKey = NULL, UINT nCodePage = CP_ACP, BOOL bValidEof = TRUE, BOOL bValidSort = TRUE );

	//从链接中获取制定的信息
	//Get information item from LINK URL
	FTKERNELAPI_API BOOL BTAPI FTK_Link_ParseLink( const char * lpszLinkURL, char * lpszOutHexHash, char * lpszOutFileName, QWORD &qwFileSize, DWORD &dwPieceSize );

	//////////////////////////////////////////////////////////////////////////
	//内网穿透相关的API接口
	//APIs of NAT's UDP tunnel

	//通知外部远程呼叫结果的函数的函数
	//Tell external module, a remote call is coming
	typedef void ( WINAPI *FTK_UPDT_PEERCALL_CALLBACK ) ( unsigned char nActive, const char *pPeerIP, unsigned short nTCPPort, const unsigned char *pPeerID, const unsigned char *pInfoHash, unsigned char nNetType, const char *pTransIP, unsigned short nTransPort );

	//预先设置是否需要输出日志，以及输出日志的级别( -1, 不输出日志 )
	//Pre-initialize to set whether to write logfile( -1, not output logfile )
	FTKERNELAPI_API void BTAPI FTK_UDPT_PreInitLog( int nLogLevel = -1 );

	//预先设置远程呼叫的回掉函数
	//Pre-initialize remote call callback function
	FTKERNELAPI_API void BTAPI FTK_UDPT_PreInitPeerCallCB( FTK_UPDT_PEERCALL_CALLBACK pfn );

	//初始化UDP穿透的环境(返回FALSE表示失败), 动态加载穿透需要的辅助动态库
	//Initialize UDP tunnel context( return false, if failed)
	FTKERNELAPI_API BOOL BTAPI FTK_UDPT_Init( const char * lpszFTKUDPxAPIDllFile, const char * lpszFTKTCPxAPIDllFile, const char * pTCPHostIP, unsigned short nTCPHostPort );

	//释放UDP穿透的环境
	//Release UDP tunnel context
	FTKERNELAPI_API void BTAPI FTK_UDPT_Release();

	//设置穿透服务器的地址和端口
	//Set tunnel server ip and port
	FTKERNELAPI_API void BTAPI FTK_UDPT_SetTunnelInfo( const char * lpszTunnelIP, unsigned short nTunnelPort );

	//连接登陆服务器
	//Build conntection to LOGIN server
	FTKERNELAPI_API BOOL BTAPI FTK_UDPT_Connect( const char * lpszLoginIP, unsigned short nLoginPort );

	//与登陆服务器断开连接
	//Disconnect to LOGIN server
	FTKERNELAPI_API void BTAPI FTK_UDPT_Disconnect();

	//是否登陆成功
	//LOGIN is OK?
	FTKERNELAPI_API BOOL BTAPI FTK_UDPT_IsLoginOK();

	//获取自己本机的IP地址
	//Get the IP address of myself
	FTKERNELAPI_API const char *BTAPI FTK_UDPT_GetRealIP();

	//获取自己的NAT类型
	//Get the type of NAT
	FTKERNELAPI_API int BTAPI FTK_UDPT_GetNatType();

	//获取当前UDP登陆服务器总的在线人数
	//Get the total online user count
	FTKERNELAPI_API int BTAPI FTK_UDPT_GetUserCount();

	//驱动内网穿透工作的事件函数(一般在主程序中的计时器中驱动)
	//UDP tunnel context event driver
	FTKERNELAPI_API void BTAPI FTK_UDPT_DoEvents();

	//呼叫远程的内网用户
	//Call remote USER
	FTKERNELAPI_API void BTAPI FTK_UDPT_RemoteCallPeer( unsigned char *pUserID, unsigned char *pInfoHash );

	//////////////////////////////////////////////////////////////////////////
}

#endif//__FTKERNELAPI_H__