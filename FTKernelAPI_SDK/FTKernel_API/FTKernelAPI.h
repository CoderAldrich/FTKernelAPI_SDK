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
// ��Ȩ���� 2004-2006 �������������缼�����޹�˾ ��������Ȩ��. �й�. 
// �ٷ���վ: http://www.p2plib.com/
//
// FTKernelAPI �ǻ���BitTorrentЭ����ں˿�, ������ǿ����չ. ���԰�����
// ���ٵĿ����Լ���P2P���ϵͳ.
//
// FTKernelAPI ����BTЭ���ں˿�, ��Ϊ4���汾:
// 1. ��Ѱ汾, ʹ��������, ֻ֧��һ����������, �޼���֧��
// 2. �����汾, �踶��, ֧�ֶ�����񲢷�, �м���֧��
// 3. �м��汾, �踶��, ֧���Զ���Э��, ���ݼ���, ����ָ��IP, ���ٵȹ���, �м���֧��
// 4. �߼��汾, �踶��, ֧��˳������, ��ý��㲥, �����ص���������, �м���֧��
//
// ��������κδ���/����, ��֪ͨ����, ���ǽ����Ժ�İ汾�кܿ�Ľ���ʵ��.
// ����ϸ��Ϣ������ҵ���վ: http://www.p2plib.com
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

//����64λ�޷��ų�����
//Define 64bit long integer type
typedef unsigned __int64 QWORD;

//���������ļ�����ľ��
//Define Config INI file handle
typedef LONG *HConfigIni;

//������������ľ��
//Define downloader handle
typedef LONG *HDownloader;

//�����ȡTorrent�ļ��ľ��
//Define Torrent file handle
typedef LONG *HTorrentFile;

//��������Torrent�ļ��ľ��
//Define Making Torrent file handle
typedef LONG *HMakeTorrent;

//����Http�ӿڴ������þ��
//Define a http proxy settings handle
typedef LONG *HHttpProxy;

//�����Http�ľ��
//Define http handle
typedef LONG *HHttpConnection;

//���巵�ص�Http���ݵľ��
//Define http response data handle
typedef LONG *HHttpResponse;

//�û���ʶ�ĳ���
//length of client identifier
#define IDSIZE 20

//BitTorrent �ͻ��˰汾��Ϣ����
//bitorrent client version information
#define AGENTSIZE 64

//���ɵ�SHA��ɢ�еĳ���
//Length of SHA1
#define SHA1_DIGEST_LENGTH 20 

//���������
//Proxytypes
#define PROXYTYPE_NOPROXY 0
#define PROXYTYPE_SOCKS4 1
#define PROXYTYPE_SOCKS4A 2
#define PROXYTYPE_SOCKS5 3
#define PROXYTYPE_HTTP11 4

////////////////////////
//����״̬
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

//����Piece��״̬
//Piece status
#define PIECESTATE_INCOMPLETE	0
#define PIECESTATE_DOWNLOADING	1
#define PIECESTATE_COMPLETE	2

//Port type of Firewall and UPnP
//����Windows����ǽ����UPnPʱ�Ķ˿����Ͷ���
#define WCXT_TCP_PORT 1
#define WCXT_UDP_PORT 2

#define TUNNEL_NONE ( 0 ) //�޴�͸
#define TUNNEL_UDP_ACTIVE ( 1 ) //UDP ��͸(����)
#define TUNNEL_UDP_PASSIVE ( 2 ) //UDP ��͸(����)
#define TUNNEL_TCP_ACTIVE ( 3 ) //TCP ��͸
#define TUNNEL_TCP_PASSIVE ( 4 ) //TCP ��͸

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
//Nat������

//δ֪
#define NAT_TYPE_UNKNOWN		( 0 )

//����
#define NAT_TYPE_WAN			( 1 )

//δ֪���͵�����
#define NAT_TYPE_UNKNOWN_LAN	( 2 )

//�޷���͸�ĵ�����
#define NAT_TYPE_SYM_LAN		( 3 )

//֧�ִ�͸�ĵ�����
#define NAT_TYPE_CONE_LAN		( 4 )

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

extern "C"
{
	//////////////////////////////////////////////////////////////////////////
	
	//���屻��֪ͨ�Ļص�����
	//Define callback function type
	typedef BOOL ( BTAPI *FTK_CALLBACK_FUNC ) ( unsigned int nSocket, const unsigned char *pData );

	//�ⲿ������������֪ͨ�ص�������ָ��
	//Define callback function for Nat PEER notification
	typedef BOOL ( BTAPI *FTK_NAT_PEER_CALLBACK ) ( BYTE *pInfoHash, const char * lpszIP, unsigned short nPort, BYTE *pPeerID );

	//�ⲿ��������ʼǰ֪ͨ�ص�������ָ��
	typedef void ( BTAPI *FTK_BEFORE_DOWN_CALLBACK ) ( HDownloader hDownloader, HANDLE hEvent, BOOL bOnlyCheckFile = FALSE );

	//�ⲿ��������������Ϻ�֪ͨ�ص�������ָ��
	typedef void ( BTAPI *FTK_ON_COMPLETE_CALLBACK ) ( HDownloader hDownloader, HANDLE hEvent, BOOL bOnlyCheckFile = FALSE );
	
	//////////////////////////////////////////////////////////////////////////
	//Libary License Interface
	
	//Set license key
	//����license����Կ
	FTKERNELAPI_API void BTAPI FTK_License_Set( const char * lpszLicense );
	
	//////////////////////////////////////////////////////////////////////////
	//Library version information
	
	//��ȡ��ǰ��İ汾��Ϣ, ����: nMajor = 1, nMinor = 1 => ver: 1.1
	//Get library major version, example: nMajor = 1, nMinor = 1 => ver: 1.1
	FTKERNELAPI_API void BTAPI FTK_Version_Info( int &nMajor, int &nMinor );
	
	//////////////////////////////////////////////////////////////////////////
	//Define yourself protocol identifier string
	
	//Define yourself protocol identifier string(to avoid Router filter)
	//�������Լ�������Э���ʶ�����Աܿ�ĳЩ������Ӫ�̵�Э�����
	FTKERNELAPI_API void BTAPI FTK_Protocol_IDS( const char *pIDS, BOOL bAllowOtherIDS = FALSE );
	
	//////////////////////////////////////////////////////////////////////////
	//Define yourself user identifier
	
	//Define yourself user identifier(read by tracker)
	//�����Լ����û���ʶ��Ϣ(Tracker���������Ի�ȡ��)
	FTKERNELAPI_API void BTAPI FTK_Identifier_String10( const char *pS );
	
	//////////////////////////////////////////////////////////////////////////
	//Define yourself http tracker "UserAgent"
	
	//Define yourself http tracker "UserAgent"
	//�����Լ����ύ��http tracker��httpЭ���е�"UserAgent"
	FTKERNELAPI_API void BTAPI FTK_Http_UserAgent( const char * lpszUA );
	
	//////////////////////////////////////////////////////////////////////////
	//Config INI file interface
	
	//����һ���µ������ļ����
	//Create a new Config INI file handle
	FTKERNELAPI_API HConfigIni BTAPI FTK_Config_Open();
	
	//����һ�����ڵ������ļ����
	//Destroy a HConfigIni hanle
	FTKERNELAPI_API void BTAPI FTK_Config_Close( HConfigIni hConfigIni );
	
	//�����ַ���ѡ��
	//Set string value item
	FTKERNELAPI_API void BTAPI FTK_Config_SetStr( HConfigIni hConfigIni, const char * lpszName, const char * lpszValue );
	
	//��������ֵѡ��
	//Set integer value item
	FTKERNELAPI_API void BTAPI FTK_Config_SetInt( HConfigIni hConfigIni, const char * lpszName, QWORD nValue );
	
	//���ø�����ѡ��
	//Set float value item
	FTKERNELAPI_API void BTAPI FTK_Config_SetFloat( HConfigIni hConfigIni, const char * lpszName, double fValue );
	
	//////////////////////////////////////////////////////////////////////////
	//Context interface

	//Ԥ�ȳ�ʼ��Context���Ƿ���Ҫ�ػ�ϵͳ���쳣
	//Preinitialize param, whether to handle system exceptions
	FTKERNELAPI_API void BTAPI FTK_Context_PreInitException( BOOL bHandleException = TRUE );
	
	//������ʼ��
	//Initialize context
	//@lpszIniFile: kernel configuration file - INI file
	FTKERNELAPI_API BOOL BTAPI FTK_Context_Init( const char * lpszIniFile = NULL, BOOL bLog = TRUE );
	
	//������ʼ��2
	//Initialize context2
	//@hConfigIni: kernel configuration file handle - INI file
	FTKERNELAPI_API BOOL BTAPI FTK_Context_Init2( HConfigIni hConfigIni, BOOL bLog = TRUE );
	
	//���ñ���֪ͨ�Ļص�����
	//Set callback funtion pointer
	FTKERNELAPI_API void BTAPI FTK_Context_NotifyCB( FTK_CALLBACK_FUNC pfn );

	//���ñ���֪ͨ�Ļص�����
	//Set callback funtion pointer
	FTKERNELAPI_API void BTAPI FTK_Context_NotifyCB( FTK_CALLBACK_FUNC pfn );
	
	//�ͷ���������
	//Release context
	FTKERNELAPI_API void BTAPI FTK_Context_Release();
	
	//�����������¼���������
	//Context event driver
	FTKERNELAPI_API BOOL BTAPI FTK_Context_Run();
	
	//ǿ���˳�����, ֹͣ����
	//��ֹͣʱҪ�˳��������е��߳����Կ���Ҫ��΢�ȴ�
	//Stop context event driver
	FTKERNELAPI_API void BTAPI FTK_Context_Stop();
	
	//���¸��������ļ��󶨶˿�
	//Rebind listen port
	FTKERNELAPI_API void BTAPI FTK_Context_ReBindListenPort();
	
	//�ж��Ƿ��Ѿ���ʼ��
	//Is context initialized?
	FTKERNELAPI_API BOOL BTAPI FTK_Context_IsInit();
	
	//�Ƿ�����ɹ��˶˿�
	//Is context running?
	FTKERNELAPI_API BOOL BTAPI FTK_Context_IsRunning();
	
	//�ж��Ƿ��Ѿ�����
	//Return context thread ID
	FTKERNELAPI_API DWORD BTAPI FTK_Context_GetThreadID();
	
	//��ȡ�̵߳�ID
	//Return listening port
	FTKERNELAPI_API USHORT BTAPI FTK_Context_GetListenPort();
	
	//����ָ���˿ڰ󶨲���
	//Return binding ip address
	FTKERNELAPI_API const char *BTAPI FTK_Context_GetBindIP();
	
	//�ж��Ƿ�󶨶˿ڲ����ɹ�
	//return bind listen port status
	FTKERNELAPI_API BOOL BTAPI FTK_Context_IsBindListenPort();

	//��ȡ������ɵ��û���ID
	//Get random user IDENTIFIER
	FTKERNELAPI_API BYTE * BTAPI FTK_Context_GetMyPeerID();

	//�޸�ǿ���ں��ύTracker��IP��ַ
	//Tell kernel the ip address to submit to tracker
	FTKERNELAPI_API void BTAPI FTK_Context_SetForceIP( const char * lpszIP );
	
	//���ü���ĳЩ�����Ĵ���torrent��ʽ
	//Set to open some mistake mistaken TORRENT file
	FTKERNELAPI_API void BTAPI FTK_Context_TorrentFile( BOOL bValidEof = TRUE, BOOL bValidSort = TRUE );
	
	//������־�������ļ�
	//Set language to write log
	FTKERNELAPI_API void BTAPI FTK_Context_OpenLanguageFile( const char * lpszLanguageFile );

	//�ͷŴ��ݸ��ⲿʹ�õ����Ӷ����ָ��(���ûص�����ʹ��, ���ӻص�����ʱ�������)
	//Free socket handle to external module
	FTKERNELAPI_API void BTAPI FTK_Context_CloseExtSocket( unsigned int nSocket );

	//����UDPTunnel��IP�͵�ַ
	//Set UDP tunnel IP and port
	FTKERNELAPI_API void BTAPI FTK_Context_SetUDPTunnelInfo( const char * lpszIP, unsigned short nPort );

	//��ȡ�ܹ����е�����ĸ���
	//Get total torrent count
	FTKERNELAPI_API int BTAPI FTK_Context_GetTorrentCount();
	
	//////////////////////////////////////////////////////////////////////////
	//Context active sharing files

	//����һ��Hashֵ(��д�Ĳ���'%'��HEX�ַ���)�Ͷ�Ӧ����Ϣ����
	FTKERNELAPI_API void BTAPI FTK_Context_ShareTorrent( const char * lpszInfoHex, const char * lpszAnnounce );
	
	//ɾ��һ��Hashֵ���丽���Ķ�Ӧ��Ϣ
	FTKERNELAPI_API void BTAPI FTK_Context_UnshareTorrent( const char * lpszInfoHex );
	
	//////////////////////////////////////////////////////////////////////////
	//Downloader interface
	
	//Create a new HDownloader handle
	FTKERNELAPI_API HDownloader BTAPI FTK_Downloader_Open();
	
	//Destroy a HDownloader hanle
	FTKERNELAPI_API void BTAPI FTK_Downloader_Close( HDownloader hDownloader );
	
	//��ǰ�ĳ�ʼ��IP���˶���ĺ���(FTK_Downloader_Init* ����֮ǰ����), ����ĳЩ�ε�IP��ַ, "ipfilter.dat" �ļ���eMule(����)����
	//Previous Initialize IP filter object to filter some peer's IP, "ipfilter.dat" file is compatiable with eMule.
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_PreInitIPFilter( HDownloader hDownloader, const char * lpszIPFilterFile, UINT nLevel = 127 );
	
	//��ǰ�ĳ�ʼ��, ���տ���Ⱥ�˳���������(�����ڱ����ر߲��ŵ����)
	//Previous Initialize, Tell kernel to sequential download piece
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitSEQMode( HDownloader hDownloader, int nSEQFileIndex = 0 );
	
	//Ԥ�ȳ�ʼ���ļ�ѡ�����ص����ȼ���
	//�����У�ÿ��Ԫ�ص�ֵ��ʾ: -2:������, -1: ��, 0: һ��, 1:��
	//Previous Initialize, Tell kernel to Set priority of file
	//-2: no download, -1: low, 0: middle, 1: high
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitFilePriority( HDownloader hDownloader, char *pFilePriority, int nFilesCount );

	//Ԥ�ȳ�ʼ��Tracker�б�ʹ���ⲿ�ṩ��Tracker�б����Torrent�ļ��е�Tracker�б�
	//Tracker1;Tracker2;Tracker3|Tracker1;Tracker2|Tracker1;Tracker2
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitTrackers( HDownloader hDownloader, const char * lpszAnnouces );

	//Ԥ�ȳ�ʼ��Զ�������Լ���Socket�ľ��ֵ
	//Previous Initialize, Tell kernel to add a remote [socket] to queue
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitSocket( HDownloader hDownloader, unsigned int nSocket );

	//Ԥ�ȳ�ʼ��Զ�������Լ���UDP���е���Ϣ
	//Previous Initialize, Tell kernel to add a remote ip and port to queue
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitSource( HDownloader hDownloader, const char *pchIP, unsigned short nPort, const BYTE *pPeerID, BYTE nTunnel );

	//Ԥ�ȳ�ʼ���Ƿ��������ʱ�ύSTOP �¼���Tracker��
	//Previous Initialize, Tell kernel whether to report STOP event to TRACKER SERVER
	FTKERNELAPI_API void BTAPI FTK_Downloader_PreInitStopEvent( HDownloader hDownloader, BOOL bReport = FALSE );
	
	//��ʼ�����ض���
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
	
	//��ʼ�����ض���2
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
	
	//��ʼ�����ض���3
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
	
	//��ʼ�����ض���4
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

	//��ʼ�����ض���5
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
	
	//��ʼ�����ض���6
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
	
	//�ͷ����ض���
	//Release downloader handle
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_Release( HDownloader hDownloader );
	
	//ִ�������߳�
	//Execute downloader
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_Execute( HDownloader hDownloader );
	
	//��ͣ����
	//Pause downloader
	FTKERNELAPI_API void BTAPI FTK_Downloader_Pause( HDownloader hDownloader );
	
	//�ָ�����
	//Resume downloader
	FTKERNELAPI_API void BTAPI FTK_Downloader_Resume( HDownloader hDownloader );
	
	//�Ƿ��Ѿ���ʼ��
	//Is downloader intialized?
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_IsInit( HDownloader hDownloader );
	
	//��ȡ��������Ŀǰ�Ľ׶�״̬
	//Return downloader state
	FTKERNELAPI_API UINT BTAPI FTK_Downloader_GetState( HDownloader hDownloader );

	//��ȡ��������Ŀǰ�Ļص�����״̬
	//Return downloader callback function state
	FTKERNELAPI_API UINT BTAPI FTK_Downloader_GetCBState( HDownloader hDownloader );
	
	//�Ƿ�ֻ�ǽ����ļ����
	//Only checking file, don't downloading...
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_IsOnlyCheckFile( HDownloader hDownloader );
	
	//�Ƿ��Ѿ����������(�ж�ѡ���ļ�����)
	//Is all selected files finished?
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_IsFinished( HDownloader hDownloader );
	
	//�Ƿ��Ѿ����������(ȫ������)
	//Is all files finished?
	FTKERNELAPI_API BOOL BTAPI FTK_Downloader_IsAllFinished( HDownloader hDownloader );
	
	//����ָ����Peer
	//Add external source peer
	FTKERNELAPI_API void BTAPI FTK_Downloader_AddSource( HDownloader hDownloader, const char *pchIP, unsigned short nPort, const BYTE *pPeerID = NULL, unsigned char nTunnel = 0 );
	
	//����ָ����User
	//Add external source peer(socket handle)
	FTKERNELAPI_API void BTAPI FTK_Downloader_AddSourceExt( HDownloader hDownloader, unsigned int nSocket );
	
	//�ⲿ��̬���Ӹ�����Announce
	//Add external announce
	FTKERNELAPI_API void BTAPI FTK_Downloader_AddExtAnnounce( HDownloader hDownloader, const char * lpszAnnounce );
	
	//�ֶ�����Announce���Ͻ�������
	//Reannounce manually
	FTKERNELAPI_API void BTAPI FTK_Downloader_ReannounceAll( HDownloader hDownloader );
	
	//���տ���Ⱥ�˳���������(�����ڱ����ر߲��ŵ����)
	//Tell kernel to sequential download piece
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetSeqPicker( HDownloader hDownloader, BOOL bSeq = FALSE, int nSEQFileIndex = 0 );
	
	//���������ļ������ȼ���
	// -2:������, -1: ��, 0: һ��, 1:��
	//Set priority of file
	//-2: no download, -1: low, 0: middle, 1: high
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetFilePriority( HDownloader hDownloader, int nIndex, char chPriority = 0, BOOL bDoPriority = TRUE );
	
	//ǿ���������½��ļ������ȼ���ֵ��Piece
	//Force to set priority of all piece immediately 
	FTKERNELAPI_API void BTAPI FTK_Downloader_ForceFilePriority( HDownloader hDownloader );
	
	//�ⲿ����, �ֶ�������������������(0.0��ʾû������)
	//Set fixed max download rate
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetFixMaxDownloadRate( HDownloader hDownloader, double fMaxDownloadRate = 0.0 );
	
	//�ⲿ����, ��ȡ�ֶ�������������������(0.0��ʾû������)
	//Get fixed max download rate
	FTKERNELAPI_API double BTAPI FTK_Downloader_GetFixMaxDownloadRate( HDownloader hDownloader );
	
	//�ⲿ����, �ֶ����������ϴ�������(0.0��ʾû������)
	//Set fixed max upload rate
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetFixMaxUploadRate( HDownloader hDownloader, double fMaxUploadRate = 0.0 );
	
	//�ⲿ����, ��ȡ�ֶ����������ϴ�������(0.0��ʾû������)
	//Get fixed max upload rate
	FTKERNELAPI_API double BTAPI FTK_Downloader_GetFixMaxUploadRate( HDownloader hDownloader );
	
	//��������ĳЩ�ض������ӷ�����(SEED), ���Լ��������ϴ���(0��ʾû������, ע�ⵥλ��: KB)
	//Set fixed max upload rate of SOME CERTAIN SEED to me, 0 means no limit, UNIT is KB 
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetSeedMaxUPSpeed( HDownloader hDownloader, unsigned short nSpeed = 0 );
	
	//���������ڣ���ֹĳ��IP������, ֻ�ڵ�ǰ��������ڼ���Ч
	//Ban IP for X seconds, ONLY for the current active HDownloader 
	FTKERNELAPI_API void BTAPI FTK_Downloader_BanPeerIP( HDownloader hDownloader, const char * lpszIP, UINT nBannedSeconds );

	//�ⲿ������������֪ͨ�ص�������ָ��
	//Set the callback function pointer for Nat PEER notification
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetNatPeerCB( HDownloader hDownloader, FTK_NAT_PEER_CALLBACK fnNatPeerCB );

	//�ⲿ����֪ͨ�ⲿ��������ǰ����Ļص�����
	//Set the callback function pointer for BEFORE DOWNLOAD notification
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetBeforeDownCB( HDownloader hDownloader, FTK_BEFORE_DOWN_CALLBACK fnBeforeDown );

	//�ⲿ����֪ͨ�ⲿ������ϵĻص�����
	//Set the callback function pointer for ON COMPLETE notification
	FTKERNELAPI_API void BTAPI FTK_Downloader_SetOnComleteCB( HDownloader hDownloader, FTK_ON_COMPLETE_CALLBACK fnOnComlete );
	
	//��ȡ�̵߳�ID
	//Get thread ID
	FTKERNELAPI_API DWORD BTAPI FTK_Downloader_GetThreadID( HDownloader hDownloader );
	
	//////////////////////////////////////////////////////////////////////////
	//ȫ�ֲ�������
	//Global settings
	
	//��ĳ��Torrent�ļ���SHA1ֵ�������
	//Add torrent into SHA1 list
	FTKERNELAPI_API void BTAPI FTK_GlobalVar_AddTorrentSHA1( const char * lpszSHA1, HDownloader hDownloader );
	
	//��ĳ��Torrent�ļ���SHA1ֵ�Ӷ�����ɾ��
	//Remove torrent from SHA1 list
	FTKERNELAPI_API void BTAPI FTK_GlobalVar_RemoveTorrentSHA1( const char * lpszSHA1 );

	//////////////////////////////////////////////////////////////////////////
	//������;�ĺ�����ʵ�ַ�������ʽ�رյ�ǰ�������е�����
	//Special functions, to asyn-close downloader handle

	//��ĳ��InfoHash�ľ�����뵽�첽�رն���
	//Add a downloader handle into asyn-close queue
	FTKERNELAPI_API void BTAPI FTK_Special_AsynClose( const char * lpszSHA1, HDownloader hDownloader );
	
	//��ѯĳ��InfoHash�ľ���Ƿ���һ���رն����д���
	//Get handle's state in the asyn-close queue
	FTKERNELAPI_API BOOL BTAPI FTK_Special_Exists( const char * lpszSHA1 );
	
	//////////////////////////////////////////////////////////////////////////
	//��������������б�
	//Proxy interface
	
	//���ý�������Trackerʱʹ�ô��������
	//Only tracker using proxy settings
	FTKERNELAPI_API void BTAPI FTK_Proxy_SetOnlyTracker( BOOL bOnlyTracker = FALSE );
	
	//��յ�ǰ�Ĵ�����Ϣ(������PROXYTYPE_NOPROXY)
	//Only PROXYTYPE_NOPROXY
	FTKERNELAPI_API void BTAPI FTK_Proxy_SetType( int nProxyType );
	
	//���ô���(������PROXYTYPE_NOPROXY)
	//May not be PROXYTYPE_NOPROXY
	FTKERNELAPI_API void BTAPI FTK_Proxy_SetProxy( int nProxyType, const char * pProxyHost, int ProxyPort );
	
	//����SOCKS5��HTTP1.1��Ҫ��֤��Ϣ�Ĵ���
	//Only SOCKS5 and HTTP1.1 proxies
	FTKERNELAPI_API void BTAPI FTK_Proxy_SetAuthProxy( int nProxyType, const char * pProxyHost, int ProxyPort, const char * pProxyUser, const char * pProxyPass );
	
	//��ȡ���������
	//Return proxy type
	FTKERNELAPI_API int BTAPI FTK_Proxy_GetProxyType();
	
	//////////////////////////////////////////////////////////////////////////
	//Downloader statistic information interface

	//��ȡ�ܹ��ļ��Ĵ�С
	//Get the size of all files
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetTotalFileSize( HDownloader hDownloader );
	
	//��ȡ�ܹ��Ѿ�����(��֤�ɹ�)������
	//Get the size of having received data for all file
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetTotalFileHaveSize( HDownloader hDownloader );

	//��ȡ�ܹ�Ҫѡ�����صĵ����ݳ���
	//Get the size of all selected file
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetSelectedFileSize( HDownloader hDownloader );
	
	//��ȡѡ���Ѿ�����(��֤�ɹ�)������
	//Get the size of having received data for a file
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetSelectedFileHaveSize( HDownloader hDownloader );
	
	//��ȡ�Ѿ�˳�����ص�Ŀǰ���Դ�ͷ��ʼ���ŵ����ݳ���
	//Get the size of sequential piece from file front
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetStartSeqFileSize( HDownloader hDownloader );
	
	//��ȡ���һ�����ص��ֽ���
	//Get the size of lasted receiving data
	FTKERNELAPI_API DWORD BTAPI FTK_Stat_GetLastDataSize( HDownloader hDownloader );
	
	//��ȡ�ܹ��������ֽ���
	//Get the size of bad data
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetBadDataSize( HDownloader hDownloader );
	
	//��ǰ�ܹ������ӵĸ���
	//Get the number of total peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetTotalPeerCount( HDownloader hDownloader );
	
	//��ǰ�������ӵĸ���
	//Get the number of active peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetActivePeerCount( HDownloader hDownloader );
	
	//��ǰ�ı������ӵĸ���
	//Get the number of passive peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetPassivePeerCount( HDownloader hDownloader );
	
	//��ǰ���������еĸ���
	//Get number of connecting peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetConnectingPeerCount( HDownloader hDownloader );
	
	//��ȡ�Ѿ����ӵ����ӵĸ���
	//Get number of seed
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetSeedCount( HDownloader hDownloader );
	
	//��ȡ�����ϴ������ӵĸ���
	//Get the number of uploading peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetUploadPeerCount( HDownloader hDownloader );
	
	//��ȡ�������ص����ӵĸ���
	//Get the number of downloading peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetDownloadPeerCount( HDownloader hDownloader );
	
	//��ȡ�ܹ����Ի�ȡ��Seed�ĸ���
	//Get the number of total available seed
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetTotalAvailSeedCount( HDownloader hDownloader );
	
	//��ȡ�ܹ����Ի�ȡ��Peer�ĸ���
	//Get the number of peer
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetTotalAvailPeerCount( HDownloader hDownloader );
	
	//�ɵ����ӵĸ���
	//Get old seed number
	FTKERNELAPI_API UINT BTAPI FTK_Stat_GetOldSeedPeerCount( HDownloader hDownloader );
	
	//��ȡ�Ƿ������Ѿ���һ��Tracker���ӳɹ�
	//Is any tracker successfull?
	FTKERNELAPI_API BOOL BTAPI FTK_Stat_IsAnyTrackerOK( HDownloader hDownloader );
	
	//���������Ѿ����ص����ݳ���
	//Get downloaded bytes
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetDownloaded( HDownloader hDownloader );
	
	//���������Ѿ��ϴ������ݳ���
	//Get uploaded bytes
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetUploaded( HDownloader hDownloader );
	
	//�����Ѿ�����ʱ��(����ʱ�䲻ͬ������ʱ��)
	//Get total running time
	FTKERNELAPI_API double BTAPI FTK_Stat_GetRunningTime( HDownloader hDownloader );
	
	//�������ص�ʱ��(���������, ������ʱ����ԶΪ0)
	//Get total downloaded time
	FTKERNELAPI_API double BTAPI FTK_Stat_GetDownloadTime( HDownloader hDownloader );
	
	//��������ʣ���ʱ��, ���������ʼ���
	//Get the left time to download
	FTKERNELAPI_API double BTAPI FTK_Stat_GetLeftTime( HDownloader hDownloader );
	
	//��ȡ��ǰ���ϴ���
	//Get upload rate
	FTKERNELAPI_API double BTAPI FTK_Stat_GetUploadRate( HDownloader hDownloader );
	
	//��ȡ��ǰ��������
	//Get downloading rate
	FTKERNELAPI_API double BTAPI FTK_Stat_GetDownloadRate( HDownloader hDownloader );
	
	//��ȡָ����Piece�����ؽ���
	//Get the progress of a piece
	FTKERNELAPI_API void BTAPI FTK_Stat_GetPieceState( HDownloader hDownloader, BYTE *pPiece, int nCount );
	
	//��ȡ����ļ��Ľ���
	//Get the progress of cheching piece
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetCheckPieceSize( HDownloader hDownloader );
	
	//��ȡ����Piece�ĸ���
	//Get number of checked piece
	FTKERNELAPI_API DWORD BTAPI FTK_Stat_GetCheckPieceCount( HDownloader hDownloader );
	
	//��ȡ�Ѿ�����ռ�Ĵ�С
	//Get the size of allocated file
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetAllocSpaceSize( HDownloader hDownloader );
	
	//��ȡ��ǰ�Ľ�����
	//Get healthy rate
	FTKERNELAPI_API double BTAPI FTK_Stat_GetHealthRate( HDownloader hDownloader );
	
	//��ȡ��ǰ����󻺴��С
	//Get the size of max cache
	FTKERNELAPI_API DWORD BTAPI FTK_Stat_GetMaxCacheSize( HDownloader hDownloader );
	
	//��ȡ�Ѿ�ʹ�õĻ����С
	//Get the size of used cache
	FTKERNELAPI_API DWORD BTAPI FTK_Stat_GetUseCacheSize( HDownloader hDownloader );
	
	//��ȡ����дӲ�̵��ܵĴ���
	//Get writed disk count
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetWriteDiskCount( HDownloader hDownloader );
	
	//��ȡ��������дӲ�̵Ĵ���
	//Get really writed disk count
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetRealWriteDiskCount( HDownloader hDownloader );
	
	//��ȡ���ζ�Ӳ�̵��ܵĴ���
	//Get readed disk count
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetReadDiskCount( HDownloader hDownloader );
	
	//��ȡ����������Ӳ�̵Ĵ���
	//Get really readed disk count
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetRealReadDiskCount( HDownloader hDownloader );
	
	//��ȡдӲ�̵�Ƶ��(��/��)
	//Get writing disk frenqence(number/second)
	FTKERNELAPI_API double BTAPI FTK_Stat_GetWriteDiskFrenq( HDownloader hDownloader );
	
	//��ȡ����дӲ�̵�Ƶ��(��/��)
	//Get really writing disk frenqence(number/second)
	FTKERNELAPI_API double BTAPI FTK_Stat_GetRealWriteDiskFrenq( HDownloader hDownloader );
	
	//��ȡ��Ӳ�̵�Ƶ��(��/��)
	//Get reading disk frenqence(number/second)
	FTKERNELAPI_API double BTAPI FTK_Stat_GetReadDiskFrenq( HDownloader hDownloader );
	
	//��ȡ������Ӳ�̵�Ƶ��(��/��)
	//Get really reading disk frenqence(number/second)
	FTKERNELAPI_API double BTAPI FTK_Stat_GetRealReadDiskFrenq( HDownloader hDownloader );
	
	//��ȡ��ǰ��־�ļ���·��+����
	//Get log file name
	FTKERNELAPI_API void BTAPI FTK_Stat_GetLogPathFileName( HDownloader hDownloader, char *lpszFileName );
	
	//��ȡָ�����ļ��Ľ���
	//Get the progress of a file
	FTKERNELAPI_API QWORD BTAPI FTK_Stat_GetFileHaveSize( HDownloader hDownloader, int nIndex );
	
	//��ȡ��ǰ�û�״̬��Ϣ���б�
	//Get the peers information
	FTKERNELAPI_API void BTAPI FTK_Stat_GetPeerData( HDownloader hDownloader, _tagPeerData *pData, int &nRetCount, int nMaxCount );
	
	//��ȡ��ǰ�����û�״̬��Ϣ���б�
	//Get the some peers information
	FTKERNELAPI_API void BTAPI FTK_Stat_GetPeerRangeData( HDownloader hDownloader, _tagPeerData *pData, int nFrom, int nTo, int &nRetCount, int nMaxCount, BOOL bExtInfo = FALSE );
	
	//��ȡ��ǰ�û�״̬��Ϣ���б�(ֻ��ȡIP�Ͷ˿�)
	//Get the peers information(only IP and port)
	FTKERNELAPI_API void BTAPI FTK_Stat_GetMiniPeerData( HDownloader hDownloader, _tagMiniPeerData *pData, int &nRetCount, int nMaxCount );
	
	//��ȡ��ǰAnnounce״̬��Ϣ���б�
	//Get the status of announces
	FTKERNELAPI_API void BTAPI FTK_Stat_GetAnnounceData( HDownloader hDownloader, _tagAnnounceData *pData, int &nRetCount, int nMaxCount );
	
	//��ȡ��ǰ����ĵ�����Ϣ
	//Get the debug information of downloader
	FTKERNELAPI_API const char * BTAPI FTK_Stat_GetBTDownloaderInfo( HDownloader hDownloader );
	
	//////////////////////////////////////////////////////////////////////////
	//��Torrent�ļ���ȡ��Ϣ�ĺ����б�
	//Torrent file interface
	
	//�ж��ǲ����Լ�����ļ��ܵ�Torrent�ļ�
	//Return boolean, tell us is a cipher torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_Torrent_IsCipherTorrent( const char * lpszFileName );
	
	//ִ�д��ļ��ж�ȡ���ݲ���ʼ���������
	//Open a torrent file handle
	FTKERNELAPI_API HTorrentFile BTAPI FTK_Torrent_Open( const char * lpszFileName, UINT nCodePage = CP_ACP, const char * lpszDesKey = NULL, BOOL bValidEOF = TRUE, BOOL bValidSort = TRUE );
	
	//ִ�д��ļ��ж�ȡ���ݲ���ʼ���������, ���ʧ��, ���ش�����Ϣ
	//Open a torrent file handle, if failed, return error information
	FTKERNELAPI_API HTorrentFile BTAPI FTK_Torrent_SafeOpen( const char * lpszFileName, UINT nCodePage = CP_ACP, const char * lpszDesKey = NULL, BOOL bValidEOF = TRUE, BOOL bValidSort = TRUE, _tagErrInfo *pErrInfo = NULL );
	
	//�ж��ǲ����Լ�����ļ��ܵ�Torrent����������
	//Return boolean, tell us is a cipher torrent binary data
	FTKERNELAPI_API BOOL BTAPI FTK_Torrent_IsCipherTorrentObj( const BYTE *pData, int nLength );
	
	//ִ�д�Torrent binary object�ж�ȡ���ݲ���ʼ���������
	//Open a torrent binary object
	FTKERNELAPI_API HTorrentFile BTAPI FTK_Torrent_OpenObj( const BYTE *pData, int nLength, UINT nCodePage = CP_ACP, const char * lpszDesKey = NULL, BOOL bValidEOF = TRUE, BOOL bValidSort = TRUE, _tagErrInfo *pErrInfo = NULL );
	
	//�رյ�ǰ�򿪵�Torrent�ļ�
	//Close Torrent file handle
	FTKERNELAPI_API void BTAPI FTK_Torrent_Close( HTorrentFile hTorrentFile );
	
	//�ж���Ŀ¼�����ļ�
	//Return boolean, tell us is only a single file in torrent
	FTKERNELAPI_API BOOL BTAPI FTK_Torrent_IsFile( HTorrentFile hTorrentFile );
	
	//��ȡ Torrent ����
	//Get the name of torrent file
	FTKERNELAPI_API const char * BTAPI FTK_Torrent_GetTorrentName( HTorrentFile hTorrentFile );
	
	//��ȡtorrent�е��ļ��ĸ���(����һ��)
	//Get total number of files
	FTKERNELAPI_API int BTAPI FTK_Torrent_GetFilesCount( HTorrentFile hTorrentFile );
	
	//��ȡtorrent�е��ļ��б�(����һ��)
	//Get a pointer to file list
	FTKERNELAPI_API void BTAPI FTK_Torrent_GetFiles( HTorrentFile hTorrentFile, _tagFileInfo *pFileInfo );
	
	//��ȡtorrent�е��ļ��б��е�ĳ���ļ�����Ϣ
	//Get a pointer to a file of file list
	FTKERNELAPI_API void BTAPI FTK_Torrent_GetFileInfo( HTorrentFile hTorrentFile, int nIndex, _tagFileInfo *pFileInfo );

	//��ȡtorrent�е�ĳ���ļ���SHA1[SHA1 ����ָ��ĳ��ȱ�����20���ֽ�]
	//Get SHA1 of a file in the file list[SHA1 pointer to a array[20] of BYTE]
	FTKERNELAPI_API void BTAPI FTK_Torrent_GetFileSHA1( HTorrentFile hTorrentFile, int nIndex, BYTE *pFileSHA1 );

	//��ȡInfo��Hashֵ, �ڲ�ʹ��
	//Get the binary info hash of torrent file
	FTKERNELAPI_API const BYTE * BTAPI FTK_Torrent_GetInfoHash( HTorrentFile hTorrentFile );
	
	//��ȡinfo��Hashֵ, ʮ������
	//Get the hex encoding info hash of torrent file
	FTKERNELAPI_API const char * BTAPI FTK_Torrent_GetHexInfoHash( HTorrentFile hTorrentFile );
	
	//��ȡ main annouce url
	//Get mainb announce url
	FTKERNELAPI_API const char * BTAPI FTK_Torrent_GetMainAnnounce( HTorrentFile hTorrentFile );
	
	//��ȡ Announce ����ĸ���
	//Get the number of all announce list
	FTKERNELAPI_API int BTAPI FTK_Torrent_GetAnnouncesCount( HTorrentFile hTorrentFile );
	
	//��ȡָ���� Announce ���������Announce�ĸ���
	//Get the size of a announce list
	FTKERNELAPI_API int BTAPI FTK_Torrent_GetAnnounceSize( HTorrentFile hTorrentFile, int nGroupIndex );
	
	//��ȡָ���� Announce ������ָ��λ�õ�Announce
	//Get a annoucne of a announce list
	FTKERNELAPI_API const char * BTAPI FTK_Torrent_GetAnnouncesVal( HTorrentFile hTorrentFile, int nGroupIndex, int nIndex );
	
	//��ȡ ע��
	//Get the comments
	FTKERNELAPI_API const char * BTAPI FTK_Torrent_GetComments( HTorrentFile hTorrentFile );
	
	//��ȡ Torrent ����ʱ��
	//Get the creation time of torrent file
	FTKERNELAPI_API time_t BTAPI FTK_Torrent_GetCreateTime( HTorrentFile hTorrentFile );
	
	//��ȡpiece��Ĵ�С
	//Get the size of piece
	FTKERNELAPI_API DWORD BTAPI FTK_Torrent_GetPieceSize( HTorrentFile hTorrentFile );
	
	//��ȡ�ļ��Ĵ�С
	//Get the total file size to transfer
	FTKERNELAPI_API QWORD BTAPI FTK_Torrent_GetFileSize( HTorrentFile hTorrentFile );
	
	//Piece��ĸ���
	//Get the total number of piece
	FTKERNELAPI_API DWORD BTAPI FTK_Torrent_GetPieceCount( HTorrentFile hTorrentFile );
	
	//��ȡPiece Hash ���б�
	//Get a pointer to piece hash list
	FTKERNELAPI_API const BYTE *BTAPI FTK_Torrent_GetPieceHashList( HTorrentFile hTorrentFile );

	//�ͷ�PieceHash�б�
	//Release piece hash memory
	FTKERNELAPI_API void BTAPI FTK_Torrent_FreePieceHashList( HTorrentFile hTorrentFile );
	
	//��ȡTorrent�ļ������Ա���
	//Get language code page of torrent file
	FTKERNELAPI_API UINT BTAPI FTK_Torrent_GetLanCodePage( HTorrentFile hTorrentFile );
	
	//////////////////////////////////////////////////////////////////////////
	//����Torrent�ļ��ĺ����б�
	//Create torrent file interface
	
	//��һ������torrent�ļ��ľ��
	//Open a making torrent handle
	FTKERNELAPI_API HMakeTorrent BTAPI FTK_MT_Open();
	
	//�رմ򿪵�����Torrent�ļ��ľ��
	//Close a making torrent handle
	FTKERNELAPI_API void BTAPI FTK_MT_Close( HMakeTorrent hMakeTorrent );
	
	//ִ�����ɶ���Ĳ���
	//Start to making torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_MT_MakeTorrent( HMakeTorrent hMakeTorrent );
	
	//ֹͣTorrent�ļ�����
	//Stop making torrent file
	FTKERNELAPI_API void BTAPI FTK_MT_StopMake( HMakeTorrent hMakeTorrent );

	//��ȡInfo��Hashֵ, �ڲ�ʹ��
	//Get the binary info hash of torrent file
	FTKERNELAPI_API const BYTE * BTAPI FTK_MT_GetInfoHash( HMakeTorrent hMakeTorrent );
	
	//��ȡinfo��Hashֵ, ʮ������
	//Get the hex encoding info hash of torrent file
	FTKERNELAPI_API const char * BTAPI FTK_MT_GetHexInfoHash( HMakeTorrent hMakeTorrent );

	//�������ļ���Ϣ�а��������ļ���SHA1ֵ
	//Set to bring SHA1 of file in dictionary
	FTKERNELAPI_API void BTAPI FTK_MT_SetFileSHA1( HMakeTorrent hMakeTorrent, BOOL bMakeSHA1 = TRUE );
	
	//��ȡ�����ļ��Ľ���
	//Get progress of making torrent file
	FTKERNELAPI_API double BTAPI FTK_MT_GetMTProgress( HMakeTorrent hMakeTorrent );
	
	//���ΪTorrent�ļ�
	//Save as a torrent file
	FTKERNELAPI_API BOOL BTAPI FTK_MT_SaveAsTorrentFile( HMakeTorrent hMakeTorrent, const char * lpszFileName, const char * lpszDesKey = NULL );
	
	//���� annouce url
	//Set a main announce url
	FTKERNELAPI_API void BTAPI FTK_MT_SetAnnounceUrl( HMakeTorrent hMakeTorrent, const char * lpszValue );
	
	//��Ӷ����Announce �б�
	//Add a announce list
	FTKERNELAPI_API void BTAPI FTK_MT_AddAnnounceList( HMakeTorrent hMakeTorrent, const char * Announces[], int nCount );
	
	//��Ӷ����Announce �б�, example: announce1;announce2;announce3;
	//Add a announce list, example: announce1;announce2;announce3;
	FTKERNELAPI_API void BTAPI FTK_MT_AddAnnounceList2( HMakeTorrent hMakeTorrent, const char * lpszAnnounces );
	
	//��ն����Announce �б�
	//Clear all announce list
	FTKERNELAPI_API void BTAPI FTK_MT_ClearAnnounceList( HMakeTorrent hMakeTorrent );

	//���� torrent�е��ļ�����Ŀ¼������, ȱʡ�Զ����������ļ������л�ȡ
	//Set real name
	FTKERNELAPI_API void BTAPI FTK_MT_SetRealName( HMakeTorrent hMakeTorrent, const char * lpszValue );
	
	//���� ע��
	//Set comments
	FTKERNELAPI_API void BTAPI FTK_MT_SetComments( HMakeTorrent hMakeTorrent, const char * lpszValue );
	
	//����piece��Ĵ�С
	//Set piece size to making torrent file
	FTKERNELAPI_API void BTAPI FTK_MT_SetPieceSize( HMakeTorrent hMakeTorrent, DWORD dwPieceSize );

	//��ȡpiece��Ĵ�С
	//Get piece size of torrent file
	FTKERNELAPI_API DWORD BTAPI FTK_MT_GetPieceSize( HMakeTorrent hMakeTorrent );
	
	//����torrent�е��ļ�
	//Set the sourece file to making torrent file
	FTKERNELAPI_API void BTAPI FTK_MT_SetFile( HMakeTorrent hMakeTorrent, const char * lpszFileName );
	
	//����torrent�е��ļ�Ŀ¼(����ļ�)
	//Set the source path to making torrent file
	FTKERNELAPI_API void BTAPI FTK_MT_SetPath( HMakeTorrent hMakeTorrent, const char * lpszPathName );
	
	//����Torrent�ļ������Դ���(ֻ���ļ�����, ע�͵���Ч)
	//Set language code of torrent file
	FTKERNELAPI_API void BTAPI FTK_MT_SetLangCodePage( HMakeTorrent hMakeTorrent, UINT nCodePage = CP_ACP );
	
	//////////////////////////////////////////////////////////////////////////
	//Tracker interface, to get status of one torrent from tracker: peer count/seed count
	
	//HTTP tracker�ӿڣ� ���ڻ�ȡhttp Trackerĳ�����״̬��Ϣ
	//HTTP Tracker interface, to get status of one torrent from http tracker
	FTKERNELAPI_API BOOL BTAPI FTK_Tracker_Http1( const char * lpszTracker, const unsigned char *pInfoHash, QWORD qwFileSize, UINT &nPeerCount, UINT &nSeedCount, BOOL &bNetwordErr, const char * lpszErrInfo = NULL, int nLength = 0 );
	
	//HTTP tracker�ӿڣ� ���ڻ�ȡhttp Trackerĳ�����״̬��Ϣ
	//HTTP Tracker interface, to get status of one torrent from http tracker
	FTKERNELAPI_API BOOL BTAPI FTK_Tracker_Http2( const char * lpszTorrentFileName, UINT &nPeerCount, UINT &nSeedCount, BOOL &bNetwordErr, const char * lpszErrInfo = NULL, int nLength = 0 );
	
	//UDP tracker�ӿڣ� ���ڻ�ȡUDP Trackerĳ�����״̬��Ϣ
	//UDP Tracker interface, to get status of one torrent from UDP tracker
	FTKERNELAPI_API BOOL BTAPI FTK_Tracker_UDP1( const char * lpszTracker, const unsigned char *pInfoHash, QWORD qwFileSize, UINT &nPeerCount, UINT &nSeedCount, BOOL &bNetwordErr, const char * lpszErrInfo = NULL, int nLength = 0 );
	
	//UDP tracker�ӿڣ� ���ڻ�ȡUDP Trackerĳ�����״̬��Ϣ
	//UDP Tracker interface, to get status of one torrent from UDP tracker
	FTKERNELAPI_API BOOL BTAPI FTK_Tracker_UDP2( const char * lpszTorrentFileName, UINT &nPeerCount, UINT &nSeedCount, BOOL &bNetwordErr, const char * lpszErrInfo = NULL, int nLength = 0 );
	
	//////////////////////////////////////////////////////////////////////////
	//Disk cache Settings
	
	//Set Disk cache size
	//���ô��̻���Ĵ�С
	FTKERNELAPI_API void BTAPI FTK_Disk_SetCache( UINT nMinCacheSize, UINT nMaxCacheSize, UINT nPhyMemorySize );
	
	//////////////////////////////////////////////////////////////////////////
	//Windows environment related interfaces
	
	//Get local machine ip address(get the first ip or best ip if there are more than one NICs)
	//��ȡ������IP��ַ(���ж��������£�ѡ���һ�������߰���һ���㷨ѡ������ʵ�һ��)
	FTKERNELAPI_API const char * BTAPI FTK_Win_GetLocalIP( BOOL &bPrivateIP );
	
	//Open Windows ICS/ICF(Windows XP/Windows 2003) 
	//�򿪲���ϵͳ���������ӷ���ǽ���������ӹ���(Windows XP/Windows 2003)
	FTKERNELAPI_API BOOL BTAPI FTK_Win_OpenWinXPICSF( unsigned short nPort, BOOL &bOpenFirewall, BOOL &bPortMapping, BYTE nProtocol = WCXT_TCP_PORT, const char * lpszIP = NULL, const char * lpszAppName = NULL );
	
	//Open UPnP port mapping(Win9x/WinME/Win2000/WinXP/Win2003)
	//ִ�ж���֧��UPnPЭ���Router�����Զ��Ķ˿�ӳ������(��������Router��Ļ�������)
	FTKERNELAPI_API BOOL BTAPI FTK_Win_AddUPnPPortMapping( unsigned short nPort, BYTE nProtocol = WCXT_TCP_PORT, const char * lpszIP = NULL );
	
	//Patch Windows XP SP2 tcpip.sys file for best TCP/IP performance
	//����Windows XP SP2 ��tcpip.sys�򲹶����ƽ������������ƣ������������
	FTKERNELAPI_API int BTAPI FTK_Win_PacthSP2TCPIPLimitFile( int nLimit = 10 );
	
	//////////////////////////////////////////////////////////////////////////
	//extendted functions
	
	//Get CRC of DATA
	//����һ�����ݵ�CRCУ��ֵ
	FTKERNELAPI_API BOOL FTK_Ext_GetCRC( BYTE *pData, int nLength, DWORD &dwCRC );

	//Encrypt data with DES algorithm
	//ʹ��DES�㷨�����ݽ��м���, ���������
	FTKERNELAPI_API BOOL BTAPI FTK_Ext_EncryptWithDes( BYTE *pPlaintext, int nPlaintextLen, BYTE *pCiphertext, int &nCiphertextLen, const char *pPassPhrase );
	
	//Decrypt data with DES algorithm
	//ʹ��DES�㷨�����ݽ��н���, �����
	FTKERNELAPI_API BOOL BTAPI FTK_Ext_DecryptWithDes( BYTE *pCiphertext, int nCiphertextLen, BYTE *pPlaintext, int &nPlaintextLen, const char *passPhrase );

	//��ȡָ�����ļ���SHA1ֵ
	//Get SHA1 of a file
	FTKERNELAPI_API BOOL BTAPI FTK_Ext_GetFileSHA1( const char *lpszFileName, BYTE *pSHA1 );

	//////////////////////////////////////////////////////////////////////////
	//Http functions

	//Open a http proxy settings handle
	//��һ��Http�������þ��
	FTKERNELAPI_API HHttpProxy BTAPI Http_Proxy_Open();

	//Close a http proxy settings handle
	//�ر�һ��Http�������õľ��
	FTKERNELAPI_API void BTAPI Http_Proxy_Close( HHttpProxy hHttpProxy );

	//Only tracker using proxy settings
	//���ý�������Trackerʱʹ�ô��������
	FTKERNELAPI_API void BTAPI Http_Proxy_SetOnlyTracker( HHttpProxy hHttpProxy, BOOL bOnlyTracker = FALSE );

	//Only PROXYTYPE_NOPROXY
	//��յ�ǰ�Ĵ�����Ϣ(������PROXYTYPE_NOPROXY)
	FTKERNELAPI_API void BTAPI Http_Proxy_SetType( HHttpProxy hHttpProxy, int nProxyType );

	//May not be PROXYTYPE_NOPROXY
	//���ô���(������PROXYTYPE_NOPROXY)
	FTKERNELAPI_API void BTAPI Http_Proxy_SetProxy( HHttpProxy hHttpProxy, int nProxyType, const char * pProxyHost, int ProxyPort );

	//Only SOCKS5 and HTTP1.1 proxies
	//����SOCKS5��HTTP1.1��Ҫ��֤��Ϣ�Ĵ���
	FTKERNELAPI_API void BTAPI Http_Proxy_SetAuthProxy( HHttpProxy hHttpProxy, int nProxyType, const char * pProxyHost, int ProxyPort, const char * pProxyUser, const char * pProxyPass );
	
	//Return proxy type
	//��ȡ���������
	FTKERNELAPI_API int BTAPI Http_Proxy_GetProxyType( HHttpProxy hHttpProxy );

	//////////////////////////////////////////////////////////////////////////

	//Open a http connection handle
	//��һ��Http���Ӿ��
	FTKERNELAPI_API HHttpConnection BTAPI Http_URL_Open();

	//Close a http connection handle
	//�ر�һ��Http���Ӿ��
	FTKERNELAPI_API void BTAPI Http_URL_Close( HHttpConnection hHttpConn );

	//To stop http connecting
	//ֹͣһ���������ӵ�Http���
	FTKERNELAPI_API void BTAPI Http_URL_Stop( HHttpConnection hHttpConn );

	//To cancel http connection, release resource
	//ȡ��һ���������ӵ�Http���, �����ͷ���Դ
	FTKERNELAPI_API void BTAPI Http_URL_Cancel( HHttpConnection hHttpConn );

	//Download from URL to write into a local file
	//��ָ���ĵ�ַ����http���ݲ������ݱ��浽ָ���ı����ļ���
	FTKERNELAPI_API BOOL BTAPI Http_URL_Download2File( HHttpConnection hHttpConn, const char * lpszURL, const char * lpszPathFileName, HHttpProxy hHttpProxy = NULL, UINT nTimeOut = 5000, UINT nDNSTimeOut = 5000, HANDLE hEvent = NULL );

	//Download from URL to HHttpResponse object
	//��ָ���ĵ�ַ����http���ݲ������ݱ��浽HHttpResponse���������
	FTKERNELAPI_API HHttpResponse BTAPI Http_URL_Download2Memory( HHttpConnection hHttpConn, const char * lpszURL, HHttpProxy hHttpProxy = NULL, UINT nTimeOut = 5000, UINT nDNSTimeOut = 5000, HANDLE hEvent = NULL );

	//////////////////////////////////////////////////////////////////////////
	
	//��HHttpResponse�����л�ȡ���ݵĳ���
	//Get data length from HHttpResponse object
	FTKERNELAPI_API UINT BTAPI Http_HR_Length( HHttpResponse hHttpResponse );

	//��HHttpResponse�����л�ȡ���ݵ�ָ��
	//Get data poiter from HHttpResponse object
	FTKERNELAPI_API BYTE * BTAPI Http_HR_Data( HHttpResponse hHttpResponse );

	//�ͷ�HHttpResponse����
	//Free HHttpResponse object
	FTKERNELAPI_API void BTAPI Http_HR_Free( HHttpResponse hHttpResponse );

	//////////////////////////////////////////////////////////////////////////
	
	//�ж��Ƿ񷵻ص���Chunk���������
	//Is data of chunk encoding
	FTKERNELAPI_API BOOL BTAPI Http_Chunk_IsEncoding( HHttpResponse hHttpResponse );

	//��ȡChunk�����ĵ�����
	//Encode chunk data to HHttpResponse object
	FTKERNELAPI_API HHttpResponse BTAPI Http_Chunk_Decode( HHttpResponse hHttpResponse );
		
	//////////////////////////////////////////////////////////////////////////
	//��ý����ص�һЩ��������
	//MEDIA related functions

	//��ȡASF/WMV �������ý���ļ���'����'
	//Get ASF/WMV encoding file's Bitrate
	FTKERNELAPI_API unsigned int BTAPI FTK_Media_GetAsfBitrate( const char *lpszAsfFileName );

	//��ȡRM/RMVB �������ý���ļ���'����'
	//Get RM/RMVB encoding file's Bitrate
	FTKERNELAPI_API unsigned int BTAPI FTK_Media_GetRMBitrate( const char *lpszRMFileName );

	//////////////////////////////////////////////////////////////////////////

	//��֤���ӵĺϷ���
	//Verify the 'ftk://****' link URL
	FTKERNELAPI_API BOOL BTAPI FTK_Link_Verify( const char *lpszLinkURL );

	//�������ص�����
	//Get the 'ftk://****' link URL
	FTKERNELAPI_API BOOL BTAPI FTK_Link_GetLink( const char *lpszHexHash, const char *lpszFileName, QWORD qwFileSize, DWORD dwPieceSize, char *lpszOutURL, int nOutLength );

	//�������ص�����(��ָ����Torrent�ļ���)
	//Get the 'ftk://****' link URL by TORRENT file
	FTKERNELAPI_API BOOL BTAPI FTK_Link_GetLink2( const char *lpszTorrentFileName, char *lpszOutURL, int nOutLength, const char *lpszDesKey = NULL, UINT nCodePage = CP_ACP, BOOL bValidEof = TRUE, BOOL bValidSort = TRUE );

	//�������л�ȡ�ƶ�����Ϣ
	//Get information item from LINK URL
	FTKERNELAPI_API BOOL BTAPI FTK_Link_ParseLink( const char * lpszLinkURL, char * lpszOutHexHash, char * lpszOutFileName, QWORD &qwFileSize, DWORD &dwPieceSize );

	//////////////////////////////////////////////////////////////////////////
	//������͸��ص�API�ӿ�
	//APIs of NAT's UDP tunnel

	//֪ͨ�ⲿԶ�̺��н���ĺ����ĺ���
	//Tell external module, a remote call is coming
	typedef void ( WINAPI *FTK_UPDT_PEERCALL_CALLBACK ) ( unsigned char nActive, const char *pPeerIP, unsigned short nTCPPort, const unsigned char *pPeerID, const unsigned char *pInfoHash, unsigned char nNetType, const char *pTransIP, unsigned short nTransPort );

	//Ԥ�������Ƿ���Ҫ�����־���Լ������־�ļ���( -1, �������־ )
	//Pre-initialize to set whether to write logfile( -1, not output logfile )
	FTKERNELAPI_API void BTAPI FTK_UDPT_PreInitLog( int nLogLevel = -1 );

	//Ԥ������Զ�̺��еĻص�����
	//Pre-initialize remote call callback function
	FTKERNELAPI_API void BTAPI FTK_UDPT_PreInitPeerCallCB( FTK_UPDT_PEERCALL_CALLBACK pfn );

	//��ʼ��UDP��͸�Ļ���(����FALSE��ʾʧ��), ��̬���ش�͸��Ҫ�ĸ�����̬��
	//Initialize UDP tunnel context( return false, if failed)
	FTKERNELAPI_API BOOL BTAPI FTK_UDPT_Init( const char * lpszFTKUDPxAPIDllFile, const char * lpszFTKTCPxAPIDllFile, const char * pTCPHostIP, unsigned short nTCPHostPort );

	//�ͷ�UDP��͸�Ļ���
	//Release UDP tunnel context
	FTKERNELAPI_API void BTAPI FTK_UDPT_Release();

	//���ô�͸�������ĵ�ַ�Ͷ˿�
	//Set tunnel server ip and port
	FTKERNELAPI_API void BTAPI FTK_UDPT_SetTunnelInfo( const char * lpszTunnelIP, unsigned short nTunnelPort );

	//���ӵ�½������
	//Build conntection to LOGIN server
	FTKERNELAPI_API BOOL BTAPI FTK_UDPT_Connect( const char * lpszLoginIP, unsigned short nLoginPort );

	//���½�������Ͽ�����
	//Disconnect to LOGIN server
	FTKERNELAPI_API void BTAPI FTK_UDPT_Disconnect();

	//�Ƿ��½�ɹ�
	//LOGIN is OK?
	FTKERNELAPI_API BOOL BTAPI FTK_UDPT_IsLoginOK();

	//��ȡ�Լ�������IP��ַ
	//Get the IP address of myself
	FTKERNELAPI_API const char *BTAPI FTK_UDPT_GetRealIP();

	//��ȡ�Լ���NAT����
	//Get the type of NAT
	FTKERNELAPI_API int BTAPI FTK_UDPT_GetNatType();

	//��ȡ��ǰUDP��½�������ܵ���������
	//Get the total online user count
	FTKERNELAPI_API int BTAPI FTK_UDPT_GetUserCount();

	//����������͸�������¼�����(һ�����������еļ�ʱ��������)
	//UDP tunnel context event driver
	FTKERNELAPI_API void BTAPI FTK_UDPT_DoEvents();

	//����Զ�̵������û�
	//Call remote USER
	FTKERNELAPI_API void BTAPI FTK_UDPT_RemoteCallPeer( unsigned char *pUserID, unsigned char *pInfoHash );

	//////////////////////////////////////////////////////////////////////////
}

#endif//__FTKERNELAPI_H__