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
///
using System;
using System.Runtime.InteropServices;

namespace P2PAPI
{
	/// <summary>
	/// Summary description for FTKernelAPI.
	/// </summary>
	public class FTKernelAPI
	{
		public FTKernelAPI()
		{
			//
			// TODO: Add constructor logic here
			//			
		}

		/////////////////////////////////////////////////////////////////////////////////////
		///

		
		//用户标识的长度
		//length of client identifier
		public enum IDSZ
		{
			IDSIZE = 20
		}

		//BitTorrent 客户端版本信息长度
		//bitorrent client version information
		public enum AGENTSZ
		{
			AGENTSIZE = 64
		}

		//生成的SHA的散列的长度
		//Length of SHA1
		public enum SAH1_DL
		{
			SHA1_DIGEST_LENGTH = 20
		}
		
		//代理的类型
		//Proxytypes
		public enum PROXYTYPE
		{
			PROXYTYPE_NOPROXY = 0,
			PROXYTYPE_SOCKS4 = 1,
			PROXYTYPE_SOCKS4A = 2,
			PROXYTYPE_SOCKS5 = 3,
			PROXYTYPE_HTTP11 = 4
		}

		////////////////////////
		//下载状态
		//Download status
		public enum DLSTATE 
		{ 
			DLSTATE_NONE = 0, 
			DLSTATE_ALLOCING, 
			DLSTATE_CHECKING,
			DLSTATE_DOWNLOAD,
			DLSTATE_PAUSING,
			DLSTATE_CHECKEND,
			DLSTATE_FETALERR,
			DLSTATE_TERMINATE
		}

		//定义Piece的状态
		//Piece status
		public enum PIECESTATE
		{
			PIECESTATE_INCOMPLETE =	0,
			PIECESTATE_DOWNLOADING = 1,
			PIECESTATE_COMPLETE	= 2
		}

		//Port type of Firewall and UPnP
		//操做Windows防火墙或者UPnP时的端口类型定义
		public enum WCXT
		{
			WCXT_TCP_PORT = 1,
			WCXT_UDP_PORT = 2
		}

		/////////////////////////////////////////////////////////////////////////////////////

		//定义被动通知的回调函数
		//Define callback function type
		public delegate bool FTK_CALLBACK_FUNC( uint nSocket, IntPtr pData );

		/////////////////////////////////////////////////////////////////////////////////////
		

		[StructLayout(LayoutKind.Sequential,Pack = 8, CharSet=CharSet.Ansi)] 
		public struct _tagPeerData 
		{ 
			public uint m_dwIP;
			public ushort m_nPort;
			[MarshalAs(UnmanagedType.ByValArray, SizeConst=(int)IDSZ.IDSIZE)]
			public byte [] m_pPeerID;
	
			//-------------------------------------
	
			public byte m_bIsLocal;
			[MarshalAs(UnmanagedType.ByValTStr, SizeConst=(int)AGENTSZ.AGENTSIZE)] 
			public string m_szVersion;
			public ulong m_ulPeerHaveSize;
			public float m_fDownRate;
			public float m_fUpRate;
			public ulong m_ulDownloaded;
			public ulong m_ulUploaded;
			public float m_fTimeElapsed;
			public float m_fPeerDownRate;
			[MarshalAs(UnmanagedType.ByValTStr, SizeConst=256)] 
			public string m_szExtInfo;
		}

		[StructLayout(LayoutKind.Sequential,Pack = 8)] 
		public struct _tagMiniPeerData
		{
			public uint	m_dwIP;
			public ushort m_nPort;
		};

		[StructLayout(LayoutKind.Sequential,Pack = 8, CharSet=CharSet.Ansi)] 
		public struct _tagAnnounceData
		{
			[MarshalAs(UnmanagedType.ByValTStr, SizeConst=512)] 
			public string m_szURL;
			public byte m_bWorking;
			public byte m_bHeader;
			public uint m_nCount;
			public uint m_nFailed;
			public float m_fTimeLeft;
			public float m_fLastTime;
			[MarshalAs(UnmanagedType.ByValTStr, SizeConst=512)] 
			public string m_szExtInfo;
		};
		
		[StructLayout(LayoutKind.Sequential,Pack = 8, CharSet=CharSet.Ansi)] 
		public struct _tagFileInfo
		{
			[MarshalAs(UnmanagedType.ByValTStr, SizeConst=512)] 
			public string m_szFileName;
			public ulong m_ulFileSize;
		};

		[StructLayout(LayoutKind.Sequential,Pack = 8, CharSet=CharSet.Ansi)] 
		public struct _tagErrInfo
		{
			[MarshalAs(UnmanagedType.ByValTStr, SizeConst=1024)]
			string m_szErrInfo;
		};

		//////////////////////////////////////////////////////////////////////////
		//Libary License Interface
	
		//Set license key
		//设置license的密钥
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_License_Set", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_License_Set( string sLicense );

		//////////////////////////////////////////////////////////////////////////
		//Library version information
	
		//获取当前库的版本信息, 例如: nMajor = 1, nMinor = 1 => ver: 1.1
		//Get library major version, example: nMajor = 1, nMinor = 1 => ver: 1.1
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Version_Info", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Version_Info( ref int nMajor, ref int nMinor );
	
		//////////////////////////////////////////////////////////////////////////
		//Define yourself protocol identifier string
	
		//Define yourself protocol identifier string(to avoid Router filter)
		//定义你自己的网络协议标识，可以避开某些网络运营商的协议封锁
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Protocol_IDS", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Protocol_IDS( string sIDS, bool bAllowOtherIDS );
	
		//////////////////////////////////////////////////////////////////////////
		//Define yourself user identifier
	
		//Define yourself user identifier(read by tracker)
		//定义自己的用户标识信息(Tracker服务器可以获取到)
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Identifier_String10", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Identifier_String10( string sS );

		//////////////////////////////////////////////////////////////////////////
		//Define yourself http tracker "UserAgent"
	
		//Define yourself http tracker "UserAgent"
		//定义自己的提交给http tracker的http协议中的"UserAgent"
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Http_UserAgent", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Http_UserAgent( string sUA );

		//////////////////////////////////////////////////////////////////////////
		//Config INI file interface
	
		//创建一个新的配置文件句柄
		//Create a new Config INI file handle
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Config_Open", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Config_Open();
	
		//销毁一个存在的配置文件句柄
		//Destroy a HConfigIni hanle
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Config_Close", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Config_Close( uint hConfigIni );
	
		//设置字符串选项
		//Set string value item
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Config_SetStr", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Config_SetStr( uint hConfigIni, string sName, string sValue );
	
		//设置整型值选项
		//Set integer value item
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Config_SetInt", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Config_SetInt( uint hConfigIni, string sName, ulong nValue );
	
		//设置浮点型选项
		//Set float value item
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Config_SetFloat", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Config_SetFloat( uint hConfigIni, string sName, double fValue );

		/////////////////////////////////////////////////////////////////////////////////////
		///

		//环境初始化
		//Initialize context
		//@sIniFile: kernel configuration file - INI file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_Init", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Context_Init( string sIniFile, bool bLogbLog );

		//环境初始化2
		//Initialize context2
		//@hConfigIni: kernel configuration file handle - INI file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_Init2", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Context_Init2( uint hConfigIni, bool bLog );
	
		//设置被动通知的回调函数
		//Set callback funtion pointer
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_NotifyCB", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Context_NotifyCB( FTK_CALLBACK_FUNC pfn );

		//释放整个环境
		//Release context
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_Release", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Context_Release();

		//整个环境的事件驱动引擎
		//Context event driver
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_Run", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Context_Run();

		//强迫退出环境, 停止运行
		//在停止时要退出正在运行的线程所以可能要稍微等待
		//Stop context event driver
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_Stop", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Context_Stop();

		//重新根据配置文件绑定端口
		//Rebind listen port
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_ReBindListenPort", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Context_ReBindListenPort();

		//判断是否已经初始化
		//Is context initialized?
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_IsInit", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Context_IsInit();

		//是否监听成功了端口
		//Is context running?
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_IsRunning", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_FTK_Context_IsRunning();

		//判断是否已经运行
		//Return context thread ID
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_GetThreadID", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Context_GetThreadID();

		//获取线程的ID
		//Return listening port
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_GetListenPort", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern ushort FTK_Context_GetListenPort();

		//重新指定端口绑定操作
		//Return binding ip address
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_GetBindIP", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern string FTK_Context_GetBindIP();

		//判断是否绑定端口操作成功
		//return bind listen port status
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Context_IsBindListenPort", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Context_IsBindListenPort();

		//设置兼容某些常见的错误torrent格式
		//Set to open some mistake mistaken TORRENT file
		[DllImport("FTKernelAPI.dll",
  　　　　EntryPoint="FTK_Context_TorrentFile", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Context_TorrentFile( bool bValidEof, bool bValidSort );

		//设置日志的语言文件
		//Set language to write log
		[DllImport("FTKernelAPI.dll",
  　　　　EntryPoint="FTK_Context_OpenLanguageFile", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Context_OpenLanguageFile( string sLanguageFile );

		/////////////////////////////////////////////////////////////////////////////////////
		
		//Create a new uint handle
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_Open", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern uint FTK_Downloader_Open();

		//Destroy a uint hanle
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_Close", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Downloader_Close( uint hDownloader );

		//提前的初始化IP过滤对象的函数(FTK_Downloader_Init* 函数之前调用), 过滤某些段的IP地址, "ipfilter.dat" 文件和eMule(电骡)兼容
		//Previous Initialize IP filter object to filter some peer's IP, "ipfilter.dat" file is compatiable with eMule.
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_PreInitIPFilter", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Downloader_PreInitIPFilter( uint hDownloader, string sIPFilterFile, uint nLevel );
	
		//提前的初始化, 按照块的先后顺序进行下载(适用于边下载边播放的情况)
		//Previous Initialize, Tell kernel to sequential download piece
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_PreInitSEQMode", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Downloader_PreInitSEQMode( uint hDownloader );
	
		//预先初始化文件选择下载的优先级别
		//数组中，每个元素的值表示: -2:不下载, -1: 低, 0: 一般, 1:高
		//Previous Initialize, Tell kernel to Set priority of file
		//-2: no download, -1: low, 0: middle, 1: high
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_PreInitFilePriority", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Downloader_PreInitFilePriority( uint hDownloader, string sFilePriority, int nFilesCount );

		//初始化下载对象
		//Initialize a uint
		//@sTorrentFileName: a torrent file name
		//@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
		//@nPreAllocFileLen: length of preallocated array
		//@bOnlyCheckFile: only verify data of files
		//@sDestFileName: the downloaded filename
		//@sConfig: kernel configuration file - INI file
		//@sLogFileName: output log filename
		//@sStatusFileName: downloading status filename
		//@sDesKey: DES-EDE2 password
		//@nCodePage: code page of the torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_Init", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Downloader_Init( 
			uint hDownloader, 
			String sTorrentFileName, 
			[MarshalAs(UnmanagedType.LPArray)] byte[] pPreAllocFile, 
			int nPreAllocFileLen, 
			bool bOnlyCheckFile,
			String sDestFileName,
			String sConfigFile,
			String sLogFileName,
			String sStatusFileName,
			bool bQuicklySeed,
			String sDesKey,
			uint nCodePage );

		//初始化下载对象2
		//Initialize a uint
		//@sTorrentFileName: a torrent file name
		//@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
		//@nPreAllocFileLen: length of preallocated array
		//@bOnlyCheckFile: only verify data of files
		//@sDestFileName: the downloaded filename
		//@hConfigIni: kernel configuration file handle - INI file
		//@sLogFileName: output log filename
		//@sStatusFileName: downloading status filename
		//@sDesKey: DES-EDE2 password
		//@nCodePage: code page of the torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_Init2", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Downloader_Init2( 
			uint hDownloader, 
			String sTorrentFileName, 
			[MarshalAs(UnmanagedType.LPArray)] byte[] pPreAllocFile, 
			int nPreAllocFileLen, 
			bool bOnlyCheckFile,
			String sDestFileName,
			uint hConfigFile,
			String sLogFileName,
			String sStatusFileName,
			bool bQuicklySeed,
			String sDesKey,
			uint nCodePage );

		//初始化下载对象3
		//Initialize a uint
		//@pData: a torrent binary object, a pointer to a binary torrent file content
		//@nLength: the length of a torrent binary object
		//@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
		//@nPreAllocFileLen: length of preallocated array
		//@bOnlyCheckFile: only verify data of files
		//@sDestFileName: the downloaded filename
		//@sConfig: kernel configuration file - INI file
		//@sLogFileName: output log filename
		//@sStatusFileName: downloading status filename
		//@sDesKey: DES-EDE2 password
		//@nCodePage: code page of the torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_Init3", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Downloader_Init3( 
			uint hDownloader,
			[MarshalAs(UnmanagedType.LPArray)] byte[] pData, 
			int nLength,
			int nPreAllocFileLen, 
			bool bOnlyCheckFile,
			String sDestFileName,
			String sConfigFile,
			String sLogFileName,
			String sStatusFileName,
			bool bQuicklySeed,
			String sDesKey,
			uint nCodePage );
	
		//初始化下载对象4
		//Initialize a uint
		//@pData: a torrent binary object, a pointer to a binary torrent file content
		//@nLength: the length of a torrent binary object
		//@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
		//@nPreAllocFileLen: length of preallocated array
		//@bOnlyCheckFile: only verify data of files
		//@sDestFileName: the downloaded filename
		//@hConfigIni: kernel configuration file handle - INI file
		//@sLogFileName: output log filename
		//@sStatusFileName: downloading status filename
		//@sDesKey: DES-EDE2 password
		//@nCodePage: code page of the torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_Init4", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Downloader_Init4( 
			uint hDownloader,
			[MarshalAs(UnmanagedType.LPArray)] byte[] pData, 
			int nLength,
			[MarshalAs(UnmanagedType.LPArray)] byte[] pPreAllocFile, 
			int nPreAllocFileLen, 
			bool bOnlyCheckFile,
			String sDestFileName,
			uint hConfigFile,
			String sLogFileName,
			String sStatusFileName,
			bool bQuicklySeed,
			String sDesKey,
			uint nCodePage );

		//释放下载对象
		//Release downloader handle
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_Release", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Downloader_Release( uint hDownloader );

		//执行下载线程
		//Execute downloader
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_Execute", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Downloader_Execute( uint hDownloader );

		//暂停下载
		//Pause downloader
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_Pause", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Downloader_Pause( uint hDownloader );

		//恢复下载
		//Resume downloader
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_Resume", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Downloader_Resume( uint hDownloader );

		//是否已经初始化
		//Is downloader intialized?
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_IsInit", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Downloader_IsInit( uint hDownloader );

		//获取下载任务目前的阶段状态
		//Return downloader state
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_GetState", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern DLSTATE FTK_Downloader_GetState( uint hDownloader );

		//是否只是进行文件检查
		//Only checking file, don't downloading...
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_IsOnlyCheckFile", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Downloader_IsOnlyCheckFile( uint hDownloader );

		//是否已经完成了下载(判断选择文件下载)
		//Is all selected files finished?
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_IsFinished", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Downloader_IsFinished( uint hDownloader );

		//是否已经完成了下载(全部下载)
		//Is all files finished?
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_IsAllFinished", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Downloader_IsAllFinished( uint hDownloader );

		//连接指定的Peer
		//Add external source peer
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_AddSource", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Downloader_AddSource( uint hDownloader, string sIP, ushort nPort, [MarshalAs(UnmanagedType.LPArray)] byte[] pPeerID );

		//连接指定的User
		//Add external source peer(socket handle)
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_AddSourceExt", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Downloader_AddSourceExt( uint hDownloader, uint nSocket );

		//外部动态增加辅助的Announce
		//Add external announce
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_AddExtAnnounce", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Downloader_AddExtAnnounce( uint hDownloader, string sAnnounce );

		//手动控制Announce马上进行连接
		//Reannounce manually
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_ReannounceAll", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Downloader_ReannounceAll( uint hDownloader );

		//按照块的先后顺序进行下载(适用于边下载边播放的情况)
		//Tell kernel to sequential download piece
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_SetSeqPicker", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Downloader_SetSeqPicker( uint hDownloader, bool bSeq );

		//设置下载文件的优先级别
		// -2:不下载, -1: 低, 0: 一般, 1:高
		//Set priority of file
		//-2: no download, -1: low, 0: middle, 1: high		
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_SetFilePriority", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Downloader_SetFilePriority( uint hDownloader, int nIndex, sbyte chPriority, bool bDoPriority );

		//强制立刻重新将文件的优先级赋值给Piece
		//Force to set priority of all piece immediately 
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_ForceFilePriority", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Downloader_ForceFilePriority( uint hDownloader );

		//外部调用, 手动设置最大的下载率限制(0.0表示没有限制)
		//Set fixed max download rate
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_SetFixMaxDownloadRate", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Downloader_SetFixMaxDownloadRate( uint hDownloader, double fMaxDownloadRate );

		//外部调用, 获取手动设置最大的下载率限制(0.0表示没有限制)
		//Get fixed max download rate
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_GetFixMaxDownloadRate", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Downloader_GetFixMaxDownloadRate( uint hDownloader );

		//外部调用, 获取手动设置最大的上传率限制(0.0表示没有限制)
		//Get fixed max upload rate
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_SetFixMaxUploadRate", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Downloader_SetFixMaxUploadRate( uint hDownloader, double fMaxUploadRate );

		//外部调用, 获取手动设置最大的上传率限制(0.0表示没有限制)
		//Get fixed max upload rate
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_GetFixMaxUploadRate", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Downloader_GetFixMaxUploadRate( uint hDownloader );
	
		//主动限制某些特定的种子服务器(SEED), 给自己的最大的上传率(0表示没有限制, 注意单位是: KB)
		//Set fixed max upload rate of SOME CERTAIN SEED to me, 0 means no limit, UNIT is KB 
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_SetSeedMaxUPSpeed", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Downloader_SetSeedMaxUPSpeed( uint hDownloader, ushort nSpeed );
	
		//多少秒中内，禁止某个IP的连接, 只在当前任务存在期间有效
		//Ban IP for X seconds, ONLY for the current active uint 
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_BanPeerIP", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Downloader_BanPeerIP( uint hDownloader, string sIP, uint nBannedSeconds );
	
		//获取线程的ID
		//Get thread ID
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Downloader_GetThreadID", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern uint FTK_Downloader_GetThreadID( uint hDownloader );

		/////////////////////////////////////////////////////////////////////////////////////
		//全局参数设置
		//Global settings

		//将某个Torrent文件的SHA1值加入队列
		//Add torrent into SHA1 list
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_GlobalVar_AddTorrentSHA1", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_GlobalVar_AddTorrentSHA1( string sSHA1, uint hDownloader );

		//将某个Torrent文件的SHA1值从队列中删除
		//Remove torrent from SHA1 list
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_GlobalVar_RemoveTorrentSHA1", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_GlobalVar_RemoveTorrentSHA1( string sSHA1 );

		/////////////////////////////////////////////////////////////////////////////////////
		//代理服务器函数列表
		//Proxy interface

		//设置仅在连接Tracker时使用代理服务器
		//Only tracker using proxy settings
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Proxy_SetOnlyTracker", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Proxy_SetOnlyTracker( bool bOnlyTracker);
	
		//清空当前的代理信息(仅用于PROXYTYPE_NOPROXY)
		//Only PROXYTYPE_NOPROXY
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Proxy_SetType", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Proxy_SetType( int nProxyType );
	
		//设置代理(不能是PROXYTYPE_NOPROXY)
		//May not be PROXYTYPE_NOPROXY
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Proxy_SetProxy", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Proxy_SetProxy( int nProxyType, string sProxyHost, int ProxyPort );
	
		//设置SOCKS5和HTTP1.1需要认证信息的代理
		//Only SOCKS5 and HTTP1.1 proxies
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Proxy_SetAuthProxy", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Proxy_SetAuthProxy( int nProxyType, string sProxyHost, int ProxyPort, string sProxyUser, string sProxyPass );
	
		//获取代理的类型
		//Return proxy type
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Proxy_GetProxyType", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern int FTK_Proxy_GetProxyType();

		//////////////////////////////////////////////////////////////////////////
		//Downloader statistic information interface

		//获取总共已经下载(验证成功)的数据
		//Get the size of having received data for all file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetTotalFileHaveSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern ulong FTK_Stat_GetTotalFileHaveSize( uint hDownloader );

		//获取选择已经下载(验证成功)的数据
		//Get the size of having received data for a file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetSelectedFileHaveSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetSelectedFileHaveSize( uint hDownloader );
		
		//获取已经顺序下载的目前可以从头开始播放的数据长度
		//Get the size of sequential piece from file front
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetStartSeqFileSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetStartSeqFileSize( uint hDownloader );
		
		//获取最近一次下载的字节数
		//Get the size of lasted receiving data
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetLastDataSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetLastDataSize( uint hDownloader );
		
		//获取总共丢弃的字节数
		//Get the size of bad data
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetBadDataSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetBadDataSize( uint hDownloader );
		
		//当前总共的连接的个数
		//Get the number of total peer
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetTotalPeerCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetTotalPeerCount( uint hDownloader );
		
		//当前主动连接的个数
		//Get the number of active peer
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetActivePeerCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetActivePeerCount( uint hDownloader );
		
		//当前的被动连接的个数
		//Get the number of passive peer
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetPassivePeerCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetPassivePeerCount( uint hDownloader );
		
		//当前正在连接中的个数
		//Get number of connecting peer
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetConnectingPeerCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetConnectingPeerCount( uint hDownloader );
		
		//获取已经连接的种子的个数
		//Get number of seed
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetSeedCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetSeedCount( uint hDownloader );
		
		//获取正在上传的连接的个数
		//Get the number of uploading peer
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetUploadPeerCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetUploadPeerCount( uint hDownloader );
		
		//获取正在下载的连接的个数
		//Get the number of downloading peer
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetDownloadPeerCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetDownloadPeerCount( uint hDownloader );
		
		//获取总共可以获取的Seed的个数
		//Get the number of total available seed
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetTotalAvailSeedCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Stat_GetTotalAvailSeedCount( uint hDownloader );
		
		//获取总共可以获取的Peer的个数
		//Get the number of peer
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetTotalAvailPeerCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Stat_GetTotalAvailPeerCount( uint hDownloader );
		
		//旧的种子的个数
		//Get old seed number
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetOldSeedPeerCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Stat_GetOldSeedPeerCount( uint hDownloader );
		
		//获取是否至少已经有一个Tracker连接成功
		//Is any tracker successfull?
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_IsAnyTrackerOK", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern bool FTK_Stat_IsAnyTrackerOK( uint hDownloader );
		
		//本次运行已经下载的数据长度
		//Get downloaded bytes
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetDownloaded", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern ulong FTK_Stat_GetDownloaded( uint hDownloader );
		
		//本次运行已经上传的数据长度
		//Get uploaded bytes
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetUploaded", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern ulong FTK_Stat_GetUploaded( uint hDownloader );
		
		//本次已经运行时间(运行时间不同与下载时间)
		//Get total running time
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetRunningTime", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern double FTK_Stat_GetRunningTime( uint hDownloader );
		
		//本次下载的时间(如果是做种, 则下载时间永远为0)
		//Get total downloaded time
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetDownloadTime", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern double FTK_Stat_GetDownloadTime( uint hDownloader );
		
		//本次下载剩余的时间, 根据下载率计算
		//Get the left time to download
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetLeftTime", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern double FTK_Stat_GetLeftTime( uint hDownloader );

		//获取当前的上传率
		//Get upload rate
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetUploadRate", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern double FTK_Stat_GetUploadRate( uint hDownloader );

		//获取当前的下载率
		//Get downloading rate
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetDownloadRate", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern double FTK_Stat_GetDownloadRate( uint hDownloader );

		//获取指定的Piece的下载进度
		//Get the progress of a piece
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetPieceState", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetPieceState( uint hDownloader, [MarshalAs(UnmanagedType.LPArray)] byte[] Piece, int nCount );
	
		//获取检查文件的进度
		//Get the progress of cheching piece
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetCheckPieceSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetCheckPieceSize( uint hDownloader );

		//获取检查的Piece的个数
		//Get number of checked piece
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetCheckPieceCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern uint FTK_Stat_GetCheckPieceCount( uint hDownloader );

		//获取已经分配空间的大小
		//Get the size of allocated file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetAllocSpaceSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetAllocSpaceSize( uint hDownloader );
	
		//获取当前的健康率
		//Get healthy rate
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetHealthRate", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Stat_GetHealthRate( uint hDownloader );
	
		//获取当前的最大缓存大小
		//Get the size of max cache
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetMaxCacheSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetMaxCacheSize( uint hDownloader );
	
		//获取已经使用的缓存大小
		//Get the size of used cache
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetUseCacheSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetUseCacheSize( uint hDownloader );
	
		//获取本次写硬盘的总的次数
		//Get writed disk count
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetWriteDiskCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetWriteDiskCount( uint hDownloader );
	
		//获取本次真正写硬盘的次数
		//Get really writed disk count
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetRealWriteDiskCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetRealWriteDiskCount( uint hDownloader );
	
		//获取本次读硬盘的总的次数
		//Get readed disk count
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetReadDiskCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetReadDiskCount( uint hDownloader );
	
		//获取本次真正读硬盘的次数
		//Get really readed disk count
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetRealReadDiskCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetRealReadDiskCount( uint hDownloader );
	
		//获取写硬盘的频率(次/秒)
		//Get writing disk frenqence(number/second)
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetWriteDiskFrenq", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Stat_GetWriteDiskFrenq( uint hDownloader );
	
		//获取真正写硬盘的频率(次/秒)
		//Get really writing disk frenqence(number/second)
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetRealWriteDiskFrenq", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Stat_GetRealWriteDiskFrenq( uint hDownloader );
	
		//获取读硬盘的频率(次/秒)
		//Get reading disk frenqence(number/second)
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetReadDiskFrenq", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Stat_GetReadDiskFrenq( uint hDownloader );
	
		//获取真正读硬盘的频率(次/秒)
		//Get really reading disk frenqence(number/second)
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetRealReadDiskFrenq", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Stat_GetRealReadDiskFrenq( uint hDownloader );
	
		//获取当前日志文件的路径+名称
		//Get log file name
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetLogPathFileName", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetLogPathFileName( uint hDownloader, string sFileName );
	
		//获取指定的文件的进度
		//Get the progress of a file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetFileHaveSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetFileHaveSize( uint hDownloader, int nIndex );
	
		//获取当前用户状态信息的列表
		//Get the peers information
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetPeerData", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetPeerData( uint hDownloader, IntPtr pData, ref int nRetCount, int nMaxCount );
	
		//获取当前部分用户状态信息的列表
		//Get the some peers information
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetPeerRangeData", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetPeerRangeData( uint hDownloader, IntPtr pData, int nFrom, int nTo, ref int nRetCount, int nMaxCount, bool bExtInfo );
	
		//获取当前用户状态信息的列表(只获取IP和端口)
		//Get the peers information(only IP and port)
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetMiniPeerData", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetMiniPeerData( uint hDownloader, IntPtr pData, ref int nRetCount, int nMaxCount );
	
		//获取当前Announce状态信息的列表
		//Get the status of announces
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetAnnounceData", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetAnnounceData( uint hDownloader, IntPtr pData, ref int nRetCount, int nMaxCount );
	
		//获取当前任务的调试信息
		//Get the debug information of downloader
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Stat_GetBTDownloaderInfo", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern string FTK_Stat_GetBTDownloaderInfo( uint hDownloader );

		//////////////////////////////////////////////////////////////////////////
		//打开Torrent文件获取信息的函数列表
		//Torrent file interface

		//判断是不是自己定义的加密的Torrent文件
		//Return boolean, tell us is a cipher torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_IsCipherTorrent", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Torrent_IsCipherTorrent( string sFileName );

		//执行从文件中读取数据并初始化对象操作
		//Open a torrent file handle
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_Open", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern uint FTK_Torrent_Open( string sFileName, uint nCodePage, string sDesKey, bool bValidEOF, bool bValidSort );

		//执行从文件中读取数据并初始化对象操作, 如果失败, 返回错误信息
		//Open a torrent file handle, if failed, return error information
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_SafeOpen", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Torrent_SafeOpen( string sFileName, uint nCodePage, string sDesKey, bool bValidEOF, bool bValidSort, ref _tagErrInfo pErrInfo );
	
		//判断是不是自己定义的加密的Torrent数据流对象
		//Return boolean, tell us is a cipher torrent binary data
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_IsCipherTorrentObj", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Torrent_IsCipherTorrentObj( [MarshalAs(UnmanagedType.LPArray)] byte[] pData, int nLength );
	
		//执行从Torrent binary object中读取数据并初始化对象操作
		//Open a torrent binary object
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_OpenObj", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Torrent_OpenObj( [MarshalAs(UnmanagedType.LPArray)] byte[] pData, int nLength, uint nCodePage, string sDesKey, bool bValidEOF, bool bValidSort, ref _tagErrInfo pErrInfo );

		//关闭当前打开的Torrent文件
		//Close Torrent file handle
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_Close", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern void FTK_Torrent_Close( uint hTorrentFile );

		//判断是目录还是文件
		//Return boolean, tell us is only a single file in torrent
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_IsFile", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern bool FTK_Torrent_IsFile( uint hTorrentFile );

		//获取 Torrent 名称
		//Get the name of torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetTorrentName", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern string FTK_Torrent_GetTorrentName( uint hTorrentFile );

		//获取torrent中的文件的个数(至少一个)
		//Get total number of files
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetFilesCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern int FTK_Torrent_GetFilesCount( uint hTorrentFile );

		//获取torrent中的文件列表(至少一个)
		//Get a pointer to file list
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetFiles", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Torrent_GetFiles( uint hTorrentFile, ref _tagFileInfo pFileInfo );
	
		//获取torrent中的文件列表中的某个文件的信息
		//Get a pointer to a file of file list
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetFileInfo", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Torrent_GetFileInfo( uint hTorrentFile, int nIndex, ref _tagFileInfo pFileInfo );
	
		//获取Info的Hash值, 内部使用
		//Get the binary info hash of torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetInfoHash", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern byte[] FTK_Torrent_GetInfoHash( uint hTorrentFile );

		//获取info的Hash值, 十六进制
		//Get the hex encoding info hash of torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetHexInfoHash", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern string FTK_Torrent_GetHexInfoHash( uint hTorrentFile );

		//获取 main annouce url
		//Get mainb announce url
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetMainAnnounce", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern string FTK_Torrent_GetMainAnnounce( uint hTorrentFile );
	
		//获取 Announce 分组的个数
		//Get the number of all announce list
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetAnnouncesCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern int FTK_Torrent_GetAnnouncesCount( uint hTorrentFile );
	
		//获取指定的 Announce 分组包含的Announce的个数
		//Get the size of a announce list
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetAnnounceSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern int FTK_Torrent_GetAnnounceSize( uint hTorrentFile, int nGroupIndex );
	
		//获取指定的 Announce 分组中指定位置的Announce
		//Get a annoucne of a announce list
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetAnnouncesVal", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern string FTK_Torrent_GetAnnouncesVal( uint hTorrentFile, int nGroupIndex, int nIndex );
	
		//获取 注释
		//Get the comments
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetComments", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern string FTK_Torrent_GetComments( uint hTorrentFile );
	
		//获取 Torrent 创建时间
		//Get the creation time of torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetCreateTime", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Torrent_GetCreateTime( uint hTorrentFile );
	
		//获取piece块的大小
		//Get the size of piece
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetPieceSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Torrent_GetPieceSize( uint hTorrentFile );

		//获取文件的大小
		//Get the total file size to transfer
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetFileSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern ulong FTK_Torrent_GetFileSize( uint hTorrentFile );
		
		//Piece块的个数
		//Get the total number of piece
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetPieceCount", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  　　　　public static extern uint FTK_Torrent_GetPieceCount( uint hTorrentFile );

		//获取Piece Hash 的列表
		//Get a pointer to piece hash list
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetPieceHashList", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern byte [] FTK_Torrent_GetPieceHashList( uint hTorrentFile );

		//释放PieceHash列表
		//Release piece hash memory
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_FreePieceHashList", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Torrent_FreePieceHashList( uint hTorrentFile );
	
		//获取Torrent文件的语言编码
		//Get language code page of torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Torrent_GetLanCodePage", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Torrent_GetLanCodePage( uint hTorrentFile );

		//////////////////////////////////////////////////////////////////////////
		//制作Torrent文件的函数列表
		//Create torrent file interface
	
		//打开一个制作torrent文件的句柄
		//Open a making torrent handle
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_Open", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_MT_Open();
	
		//关闭打开的制作Torrent文件的句柄
		//Close a making torrent handle
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_Close", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_Close( uint hMakeTorrent );
	
		//执行生成对象的操作
		//Start to making torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_MakeTorrent", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_MT_MakeTorrent( uint hMakeTorrent );
	
		//停止Torrent文件制作
		//Stop making torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_StopMake", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_StopMake( uint hMakeTorrent );
	
		//获取制作文件的进度
		//Get progress of making torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_GetMTProgress", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_MT_GetMTProgress( uint hMakeTorrent );
	
		//另存为Torrent文件
		//Save as a torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_SaveAsTorrentFile", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_MT_SaveAsTorrentFile( uint hMakeTorrent, string sFileName, string sDesKey );
	
		//设置 annouce url
		//Set a main announce url
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_SetAnnounceUrl", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetAnnounceUrl( uint hMakeTorrent, string sValue );
	
		//添加额外的Announce 列表
		//Add a announce list
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_AddAnnounceList", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_AddAnnounceList( uint hMakeTorrent, string [] Announces, int nCount );
	
		//添加额外的Announce 列表, example: announce1;announce2;announce3;
		//Add a announce list, example: announce1;announce2;announce3;
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_AddAnnounceList2", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_AddAnnounceList2( uint hMakeTorrent, string sAnnounces );
	
		//清空额外的Announce 列表
		//Clear all announce list
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_ClearAnnounceList", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_ClearAnnounceList( uint hMakeTorrent );
	
		//设置 注释
		//Set comments
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_SetComments", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetComments( uint hMakeTorrent, string sValue );
	
		//设置piece块的大小
		//Set piece size to making torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_SetPieceSize", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetPieceSize( uint hMakeTorrent, uint nPieceSize );
	
		//设置torrent中的文件
		//Set the sourece file to making torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_SetFile", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetFile( uint hMakeTorrent, string sFileName );
	
		//设置torrent中的文件目录(多个文件)
		//Set the source path to making torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_SetPath", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetPath( uint hMakeTorrent, string sPathName );
	
		//设置Torrent文件的语言代码(只对文件名称, 注释等有效)
		//Set language code of torrent file
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_MT_SetLangCodePage", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetLangCodePage( uint hMakeTorrent, uint nCodePage );
	
		//////////////////////////////////////////////////////////////////////////
		//Tracker interface, to get status of one torrent from tracker: peer count/seed count
	
		//HTTP tracker接口， 用于获取http Tracker某任务的状态信息
		//HTTP Tracker interface, to get status of one torrent from http tracker
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Tracker_Http1", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Tracker_Http1( string sTracker, string sInfoHash, ulong ulFileSize, ref uint nPeerCount, ref uint nSeedCount, ref bool bNetwordErr, string sErrInfo, int nLength );
	
		//HTTP tracker接口， 用于获取http Tracker某任务的状态信息
		//HTTP Tracker interface, to get status of one torrent from http tracker
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Tracker_Http2", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Tracker_Http2( string sTorrentFileName, ref uint nPeerCount, ref uint nSeedCount, ref bool bNetwordErr, string  sErrInfo, int nLength );
	
		//UDP tracker接口， 用于获取UDP Tracker某任务的状态信息
		//UDP Tracker interface, to get status of one torrent from UDP tracker
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Tracker_UDP1", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Tracker_UDP1( string sTracker, string sInfoHash, ulong ulFileSize, ref uint nPeerCount, ref uint nSeedCount, ref bool bNetwordErr, string sErrInfo, int nLength );
	
		//UDP tracker接口， 用于获取UDP Tracker某任务的状态信息
		//UDP Tracker interface, to get status of one torrent from UDP tracker
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Tracker_UDP2", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Tracker_UDP2( string sTorrentFileName, ref uint nPeerCount, ref uint nSeedCount, ref bool bNetwordErr, string sErrInfo, int nLength );
	
		//////////////////////////////////////////////////////////////////////////
		//Disk cache Settings
	
		//Set Disk cache size
		//设置磁盘缓存的大小
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Disk_SetCache", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Disk_SetCache( uint nMinCacheSize, uint nMaxCacheSize, uint nPhyMemorySize );
	
		//////////////////////////////////////////////////////////////////////////
		//Windows environment related interfaces
	
		//Get local machine ip address(get the first ip or best ip if there are more than one NICs)
		//获取本机的IP地址(在有多个的情况下，选择第一个，或者按照一定算法选择最合适的一个)
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Win_GetLocalIP", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern string FTK_Win_GetLocalIP( ref bool bPrivateIP );
	
		//Open Windows ICS/ICF(Windows XP/Windows 2003) 
		//打开操作系统的网络连接防火墙和网络连接共享(Windows XP/Windows 2003)
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Win_OpenWinXPICSF", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Win_OpenWinXPICSF( ushort nPort, ref bool bOpenFirewall, ref bool bPortMapping, byte nProtocol, string  sIP, string sAppName );
	
		//Open UPnP port mapping(Win9x/WinME/Win2000/WinXP/Win2003)
		//执行对于支持UPnP协议的Router进行自动的端口映射配置(内网处于Router后的机器必用)
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Win_AddUPnPPortMapping", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Win_AddUPnPPortMapping( ushort nPort, byte nProtoco, string sIP );
	
		//Patch Windows XP SP2 tcpip.sys file for best TCP/IP performance
		//对于Windows XP SP2 的tcpip.sys打补丁，破解连接数的限制，提高网络性能
		[DllImport("FTKernelAPI.dll", 
  　　　　EntryPoint="FTK_Win_PacthSP2TCPIPLimitFile", 
  　　　　CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern int FTK_Win_PacthSP2TCPIPLimitFile( int nLimit );
	
		//////////////////////////////////////////////////////////////////////////
	}
}
