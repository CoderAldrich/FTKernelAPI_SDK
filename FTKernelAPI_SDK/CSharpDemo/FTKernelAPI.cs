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

		
		//�û���ʶ�ĳ���
		//length of client identifier
		public enum IDSZ
		{
			IDSIZE = 20
		}

		//BitTorrent �ͻ��˰汾��Ϣ����
		//bitorrent client version information
		public enum AGENTSZ
		{
			AGENTSIZE = 64
		}

		//���ɵ�SHA��ɢ�еĳ���
		//Length of SHA1
		public enum SAH1_DL
		{
			SHA1_DIGEST_LENGTH = 20
		}
		
		//���������
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
		//����״̬
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

		//����Piece��״̬
		//Piece status
		public enum PIECESTATE
		{
			PIECESTATE_INCOMPLETE =	0,
			PIECESTATE_DOWNLOADING = 1,
			PIECESTATE_COMPLETE	= 2
		}

		//Port type of Firewall and UPnP
		//����Windows����ǽ����UPnPʱ�Ķ˿����Ͷ���
		public enum WCXT
		{
			WCXT_TCP_PORT = 1,
			WCXT_UDP_PORT = 2
		}

		/////////////////////////////////////////////////////////////////////////////////////

		//���屻��֪ͨ�Ļص�����
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
		//����license����Կ
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_License_Set", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_License_Set( string sLicense );

		//////////////////////////////////////////////////////////////////////////
		//Library version information
	
		//��ȡ��ǰ��İ汾��Ϣ, ����: nMajor = 1, nMinor = 1 => ver: 1.1
		//Get library major version, example: nMajor = 1, nMinor = 1 => ver: 1.1
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Version_Info", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Version_Info( ref int nMajor, ref int nMinor );
	
		//////////////////////////////////////////////////////////////////////////
		//Define yourself protocol identifier string
	
		//Define yourself protocol identifier string(to avoid Router filter)
		//�������Լ�������Э���ʶ�����Աܿ�ĳЩ������Ӫ�̵�Э�����
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Protocol_IDS", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Protocol_IDS( string sIDS, bool bAllowOtherIDS );
	
		//////////////////////////////////////////////////////////////////////////
		//Define yourself user identifier
	
		//Define yourself user identifier(read by tracker)
		//�����Լ����û���ʶ��Ϣ(Tracker���������Ի�ȡ��)
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Identifier_String10", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Identifier_String10( string sS );

		//////////////////////////////////////////////////////////////////////////
		//Define yourself http tracker "UserAgent"
	
		//Define yourself http tracker "UserAgent"
		//�����Լ����ύ��http tracker��httpЭ���е�"UserAgent"
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Http_UserAgent", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Http_UserAgent( string sUA );

		//////////////////////////////////////////////////////////////////////////
		//Config INI file interface
	
		//����һ���µ������ļ����
		//Create a new Config INI file handle
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Config_Open", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Config_Open();
	
		//����һ�����ڵ������ļ����
		//Destroy a HConfigIni hanle
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Config_Close", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Config_Close( uint hConfigIni );
	
		//�����ַ���ѡ��
		//Set string value item
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Config_SetStr", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Config_SetStr( uint hConfigIni, string sName, string sValue );
	
		//��������ֵѡ��
		//Set integer value item
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Config_SetInt", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Config_SetInt( uint hConfigIni, string sName, ulong nValue );
	
		//���ø�����ѡ��
		//Set float value item
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Config_SetFloat", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Config_SetFloat( uint hConfigIni, string sName, double fValue );

		/////////////////////////////////////////////////////////////////////////////////////
		///

		//������ʼ��
		//Initialize context
		//@sIniFile: kernel configuration file - INI file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_Init", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Context_Init( string sIniFile, bool bLogbLog );

		//������ʼ��2
		//Initialize context2
		//@hConfigIni: kernel configuration file handle - INI file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_Init2", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Context_Init2( uint hConfigIni, bool bLog );
	
		//���ñ���֪ͨ�Ļص�����
		//Set callback funtion pointer
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_NotifyCB", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Context_NotifyCB( FTK_CALLBACK_FUNC pfn );

		//�ͷ���������
		//Release context
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_Release", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Context_Release();

		//�����������¼���������
		//Context event driver
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_Run", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Context_Run();

		//ǿ���˳�����, ֹͣ����
		//��ֹͣʱҪ�˳��������е��߳����Կ���Ҫ��΢�ȴ�
		//Stop context event driver
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_Stop", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Context_Stop();

		//���¸��������ļ��󶨶˿�
		//Rebind listen port
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_ReBindListenPort", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Context_ReBindListenPort();

		//�ж��Ƿ��Ѿ���ʼ��
		//Is context initialized?
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_IsInit", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Context_IsInit();

		//�Ƿ�����ɹ��˶˿�
		//Is context running?
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_IsRunning", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_FTK_Context_IsRunning();

		//�ж��Ƿ��Ѿ�����
		//Return context thread ID
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_GetThreadID", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Context_GetThreadID();

		//��ȡ�̵߳�ID
		//Return listening port
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_GetListenPort", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern ushort FTK_Context_GetListenPort();

		//����ָ���˿ڰ󶨲���
		//Return binding ip address
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_GetBindIP", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern string FTK_Context_GetBindIP();

		//�ж��Ƿ�󶨶˿ڲ����ɹ�
		//return bind listen port status
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Context_IsBindListenPort", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Context_IsBindListenPort();

		//���ü���ĳЩ�����Ĵ���torrent��ʽ
		//Set to open some mistake mistaken TORRENT file
		[DllImport("FTKernelAPI.dll",
  ��������EntryPoint="FTK_Context_TorrentFile", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Context_TorrentFile( bool bValidEof, bool bValidSort );

		//������־�������ļ�
		//Set language to write log
		[DllImport("FTKernelAPI.dll",
  ��������EntryPoint="FTK_Context_OpenLanguageFile", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Context_OpenLanguageFile( string sLanguageFile );

		/////////////////////////////////////////////////////////////////////////////////////
		
		//Create a new uint handle
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_Open", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern uint FTK_Downloader_Open();

		//Destroy a uint hanle
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_Close", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Downloader_Close( uint hDownloader );

		//��ǰ�ĳ�ʼ��IP���˶���ĺ���(FTK_Downloader_Init* ����֮ǰ����), ����ĳЩ�ε�IP��ַ, "ipfilter.dat" �ļ���eMule(����)����
		//Previous Initialize IP filter object to filter some peer's IP, "ipfilter.dat" file is compatiable with eMule.
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_PreInitIPFilter", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Downloader_PreInitIPFilter( uint hDownloader, string sIPFilterFile, uint nLevel );
	
		//��ǰ�ĳ�ʼ��, ���տ���Ⱥ�˳���������(�����ڱ����ر߲��ŵ����)
		//Previous Initialize, Tell kernel to sequential download piece
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_PreInitSEQMode", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Downloader_PreInitSEQMode( uint hDownloader );
	
		//Ԥ�ȳ�ʼ���ļ�ѡ�����ص����ȼ���
		//�����У�ÿ��Ԫ�ص�ֵ��ʾ: -2:������, -1: ��, 0: һ��, 1:��
		//Previous Initialize, Tell kernel to Set priority of file
		//-2: no download, -1: low, 0: middle, 1: high
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_PreInitFilePriority", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern void FTK_Downloader_PreInitFilePriority( uint hDownloader, string sFilePriority, int nFilesCount );

		//��ʼ�����ض���
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
  ��������EntryPoint="FTK_Downloader_Init", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Downloader_Init( 
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

		//��ʼ�����ض���2
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
  ��������EntryPoint="FTK_Downloader_Init2", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Downloader_Init2( 
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

		//��ʼ�����ض���3
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
  ��������EntryPoint="FTK_Downloader_Init3", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
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
	
		//��ʼ�����ض���4
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
  ��������EntryPoint="FTK_Downloader_Init4", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
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

		//�ͷ����ض���
		//Release downloader handle
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_Release", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Downloader_Release( uint hDownloader );

		//ִ�������߳�
		//Execute downloader
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_Execute", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Downloader_Execute( uint hDownloader );

		//��ͣ����
		//Pause downloader
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_Pause", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Downloader_Pause( uint hDownloader );

		//�ָ�����
		//Resume downloader
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_Resume", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Downloader_Resume( uint hDownloader );

		//�Ƿ��Ѿ���ʼ��
		//Is downloader intialized?
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_IsInit", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Downloader_IsInit( uint hDownloader );

		//��ȡ��������Ŀǰ�Ľ׶�״̬
		//Return downloader state
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_GetState", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern DLSTATE FTK_Downloader_GetState( uint hDownloader );

		//�Ƿ�ֻ�ǽ����ļ����
		//Only checking file, don't downloading...
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_IsOnlyCheckFile", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Downloader_IsOnlyCheckFile( uint hDownloader );

		//�Ƿ��Ѿ����������(�ж�ѡ���ļ�����)
		//Is all selected files finished?
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_IsFinished", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Downloader_IsFinished( uint hDownloader );

		//�Ƿ��Ѿ����������(ȫ������)
		//Is all files finished?
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_IsAllFinished", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Downloader_IsAllFinished( uint hDownloader );

		//����ָ����Peer
		//Add external source peer
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_AddSource", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Downloader_AddSource( uint hDownloader, string sIP, ushort nPort, [MarshalAs(UnmanagedType.LPArray)] byte[] pPeerID );

		//����ָ����User
		//Add external source peer(socket handle)
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_AddSourceExt", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Downloader_AddSourceExt( uint hDownloader, uint nSocket );

		//�ⲿ��̬���Ӹ�����Announce
		//Add external announce
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_AddExtAnnounce", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Downloader_AddExtAnnounce( uint hDownloader, string sAnnounce );

		//�ֶ�����Announce���Ͻ�������
		//Reannounce manually
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_ReannounceAll", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Downloader_ReannounceAll( uint hDownloader );

		//���տ���Ⱥ�˳���������(�����ڱ����ر߲��ŵ����)
		//Tell kernel to sequential download piece
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_SetSeqPicker", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Downloader_SetSeqPicker( uint hDownloader, bool bSeq );

		//���������ļ������ȼ���
		// -2:������, -1: ��, 0: һ��, 1:��
		//Set priority of file
		//-2: no download, -1: low, 0: middle, 1: high		
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_SetFilePriority", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Downloader_SetFilePriority( uint hDownloader, int nIndex, sbyte chPriority, bool bDoPriority );

		//ǿ���������½��ļ������ȼ���ֵ��Piece
		//Force to set priority of all piece immediately 
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_ForceFilePriority", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Downloader_ForceFilePriority( uint hDownloader );

		//�ⲿ����, �ֶ�������������������(0.0��ʾû������)
		//Set fixed max download rate
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_SetFixMaxDownloadRate", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Downloader_SetFixMaxDownloadRate( uint hDownloader, double fMaxDownloadRate );

		//�ⲿ����, ��ȡ�ֶ�������������������(0.0��ʾû������)
		//Get fixed max download rate
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_GetFixMaxDownloadRate", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Downloader_GetFixMaxDownloadRate( uint hDownloader );

		//�ⲿ����, ��ȡ�ֶ����������ϴ�������(0.0��ʾû������)
		//Get fixed max upload rate
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_SetFixMaxUploadRate", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Downloader_SetFixMaxUploadRate( uint hDownloader, double fMaxUploadRate );

		//�ⲿ����, ��ȡ�ֶ����������ϴ�������(0.0��ʾû������)
		//Get fixed max upload rate
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_GetFixMaxUploadRate", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Downloader_GetFixMaxUploadRate( uint hDownloader );
	
		//��������ĳЩ�ض������ӷ�����(SEED), ���Լ��������ϴ���(0��ʾû������, ע�ⵥλ��: KB)
		//Set fixed max upload rate of SOME CERTAIN SEED to me, 0 means no limit, UNIT is KB 
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_SetSeedMaxUPSpeed", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Downloader_SetSeedMaxUPSpeed( uint hDownloader, ushort nSpeed );
	
		//���������ڣ���ֹĳ��IP������, ֻ�ڵ�ǰ��������ڼ���Ч
		//Ban IP for X seconds, ONLY for the current active uint 
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_BanPeerIP", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Downloader_BanPeerIP( uint hDownloader, string sIP, uint nBannedSeconds );
	
		//��ȡ�̵߳�ID
		//Get thread ID
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Downloader_GetThreadID", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern uint FTK_Downloader_GetThreadID( uint hDownloader );

		/////////////////////////////////////////////////////////////////////////////////////
		//ȫ�ֲ�������
		//Global settings

		//��ĳ��Torrent�ļ���SHA1ֵ�������
		//Add torrent into SHA1 list
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_GlobalVar_AddTorrentSHA1", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_GlobalVar_AddTorrentSHA1( string sSHA1, uint hDownloader );

		//��ĳ��Torrent�ļ���SHA1ֵ�Ӷ�����ɾ��
		//Remove torrent from SHA1 list
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_GlobalVar_RemoveTorrentSHA1", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_GlobalVar_RemoveTorrentSHA1( string sSHA1 );

		/////////////////////////////////////////////////////////////////////////////////////
		//��������������б�
		//Proxy interface

		//���ý�������Trackerʱʹ�ô��������
		//Only tracker using proxy settings
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Proxy_SetOnlyTracker", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Proxy_SetOnlyTracker( bool bOnlyTracker);
	
		//��յ�ǰ�Ĵ�����Ϣ(������PROXYTYPE_NOPROXY)
		//Only PROXYTYPE_NOPROXY
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Proxy_SetType", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Proxy_SetType( int nProxyType );
	
		//���ô���(������PROXYTYPE_NOPROXY)
		//May not be PROXYTYPE_NOPROXY
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Proxy_SetProxy", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Proxy_SetProxy( int nProxyType, string sProxyHost, int ProxyPort );
	
		//����SOCKS5��HTTP1.1��Ҫ��֤��Ϣ�Ĵ���
		//Only SOCKS5 and HTTP1.1 proxies
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Proxy_SetAuthProxy", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Proxy_SetAuthProxy( int nProxyType, string sProxyHost, int ProxyPort, string sProxyUser, string sProxyPass );
	
		//��ȡ���������
		//Return proxy type
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Proxy_GetProxyType", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern int FTK_Proxy_GetProxyType();

		//////////////////////////////////////////////////////////////////////////
		//Downloader statistic information interface

		//��ȡ�ܹ��Ѿ�����(��֤�ɹ�)������
		//Get the size of having received data for all file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetTotalFileHaveSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern ulong FTK_Stat_GetTotalFileHaveSize( uint hDownloader );

		//��ȡѡ���Ѿ�����(��֤�ɹ�)������
		//Get the size of having received data for a file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetSelectedFileHaveSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetSelectedFileHaveSize( uint hDownloader );
		
		//��ȡ�Ѿ�˳�����ص�Ŀǰ���Դ�ͷ��ʼ���ŵ����ݳ���
		//Get the size of sequential piece from file front
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetStartSeqFileSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetStartSeqFileSize( uint hDownloader );
		
		//��ȡ���һ�����ص��ֽ���
		//Get the size of lasted receiving data
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetLastDataSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetLastDataSize( uint hDownloader );
		
		//��ȡ�ܹ��������ֽ���
		//Get the size of bad data
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetBadDataSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetBadDataSize( uint hDownloader );
		
		//��ǰ�ܹ������ӵĸ���
		//Get the number of total peer
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetTotalPeerCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetTotalPeerCount( uint hDownloader );
		
		//��ǰ�������ӵĸ���
		//Get the number of active peer
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetActivePeerCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetActivePeerCount( uint hDownloader );
		
		//��ǰ�ı������ӵĸ���
		//Get the number of passive peer
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetPassivePeerCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetPassivePeerCount( uint hDownloader );
		
		//��ǰ���������еĸ���
		//Get number of connecting peer
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetConnectingPeerCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetConnectingPeerCount( uint hDownloader );
		
		//��ȡ�Ѿ����ӵ����ӵĸ���
		//Get number of seed
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetSeedCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetSeedCount( uint hDownloader );
		
		//��ȡ�����ϴ������ӵĸ���
		//Get the number of uploading peer
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetUploadPeerCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetUploadPeerCount( uint hDownloader );
		
		//��ȡ�������ص����ӵĸ���
		//Get the number of downloading peer
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetDownloadPeerCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetDownloadPeerCount( uint hDownloader );
		
		//��ȡ�ܹ����Ի�ȡ��Seed�ĸ���
		//Get the number of total available seed
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetTotalAvailSeedCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Stat_GetTotalAvailSeedCount( uint hDownloader );
		
		//��ȡ�ܹ����Ի�ȡ��Peer�ĸ���
		//Get the number of peer
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetTotalAvailPeerCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Stat_GetTotalAvailPeerCount( uint hDownloader );
		
		//�ɵ����ӵĸ���
		//Get old seed number
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetOldSeedPeerCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Stat_GetOldSeedPeerCount( uint hDownloader );
		
		//��ȡ�Ƿ������Ѿ���һ��Tracker���ӳɹ�
		//Is any tracker successfull?
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_IsAnyTrackerOK", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern bool FTK_Stat_IsAnyTrackerOK( uint hDownloader );
		
		//���������Ѿ����ص����ݳ���
		//Get downloaded bytes
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetDownloaded", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern ulong FTK_Stat_GetDownloaded( uint hDownloader );
		
		//���������Ѿ��ϴ������ݳ���
		//Get uploaded bytes
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetUploaded", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern ulong FTK_Stat_GetUploaded( uint hDownloader );
		
		//�����Ѿ�����ʱ��(����ʱ�䲻ͬ������ʱ��)
		//Get total running time
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetRunningTime", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern double FTK_Stat_GetRunningTime( uint hDownloader );
		
		//�������ص�ʱ��(���������, ������ʱ����ԶΪ0)
		//Get total downloaded time
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetDownloadTime", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern double FTK_Stat_GetDownloadTime( uint hDownloader );
		
		//��������ʣ���ʱ��, ���������ʼ���
		//Get the left time to download
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetLeftTime", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern double FTK_Stat_GetLeftTime( uint hDownloader );

		//��ȡ��ǰ���ϴ���
		//Get upload rate
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetUploadRate", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern double FTK_Stat_GetUploadRate( uint hDownloader );

		//��ȡ��ǰ��������
		//Get downloading rate
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetDownloadRate", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern double FTK_Stat_GetDownloadRate( uint hDownloader );

		//��ȡָ����Piece�����ؽ���
		//Get the progress of a piece
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetPieceState", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetPieceState( uint hDownloader, [MarshalAs(UnmanagedType.LPArray)] byte[] Piece, int nCount );
	
		//��ȡ����ļ��Ľ���
		//Get the progress of cheching piece
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetCheckPieceSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetCheckPieceSize( uint hDownloader );

		//��ȡ����Piece�ĸ���
		//Get number of checked piece
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetCheckPieceCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern uint FTK_Stat_GetCheckPieceCount( uint hDownloader );

		//��ȡ�Ѿ�����ռ�Ĵ�С
		//Get the size of allocated file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetAllocSpaceSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetAllocSpaceSize( uint hDownloader );
	
		//��ȡ��ǰ�Ľ�����
		//Get healthy rate
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetHealthRate", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Stat_GetHealthRate( uint hDownloader );
	
		//��ȡ��ǰ����󻺴��С
		//Get the size of max cache
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetMaxCacheSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetMaxCacheSize( uint hDownloader );
	
		//��ȡ�Ѿ�ʹ�õĻ����С
		//Get the size of used cache
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetUseCacheSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Stat_GetUseCacheSize( uint hDownloader );
	
		//��ȡ����дӲ�̵��ܵĴ���
		//Get writed disk count
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetWriteDiskCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetWriteDiskCount( uint hDownloader );
	
		//��ȡ��������дӲ�̵Ĵ���
		//Get really writed disk count
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetRealWriteDiskCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetRealWriteDiskCount( uint hDownloader );
	
		//��ȡ���ζ�Ӳ�̵��ܵĴ���
		//Get readed disk count
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetReadDiskCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetReadDiskCount( uint hDownloader );
	
		//��ȡ����������Ӳ�̵Ĵ���
		//Get really readed disk count
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetRealReadDiskCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetRealReadDiskCount( uint hDownloader );
	
		//��ȡдӲ�̵�Ƶ��(��/��)
		//Get writing disk frenqence(number/second)
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetWriteDiskFrenq", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Stat_GetWriteDiskFrenq( uint hDownloader );
	
		//��ȡ����дӲ�̵�Ƶ��(��/��)
		//Get really writing disk frenqence(number/second)
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetRealWriteDiskFrenq", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Stat_GetRealWriteDiskFrenq( uint hDownloader );
	
		//��ȡ��Ӳ�̵�Ƶ��(��/��)
		//Get reading disk frenqence(number/second)
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetReadDiskFrenq", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Stat_GetReadDiskFrenq( uint hDownloader );
	
		//��ȡ������Ӳ�̵�Ƶ��(��/��)
		//Get really reading disk frenqence(number/second)
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetRealReadDiskFrenq", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_Stat_GetRealReadDiskFrenq( uint hDownloader );
	
		//��ȡ��ǰ��־�ļ���·��+����
		//Get log file name
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetLogPathFileName", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetLogPathFileName( uint hDownloader, string sFileName );
	
		//��ȡָ�����ļ��Ľ���
		//Get the progress of a file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetFileHaveSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern ulong FTK_Stat_GetFileHaveSize( uint hDownloader, int nIndex );
	
		//��ȡ��ǰ�û�״̬��Ϣ���б�
		//Get the peers information
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetPeerData", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetPeerData( uint hDownloader, IntPtr pData, ref int nRetCount, int nMaxCount );
	
		//��ȡ��ǰ�����û�״̬��Ϣ���б�
		//Get the some peers information
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetPeerRangeData", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetPeerRangeData( uint hDownloader, IntPtr pData, int nFrom, int nTo, ref int nRetCount, int nMaxCount, bool bExtInfo );
	
		//��ȡ��ǰ�û�״̬��Ϣ���б�(ֻ��ȡIP�Ͷ˿�)
		//Get the peers information(only IP and port)
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetMiniPeerData", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetMiniPeerData( uint hDownloader, IntPtr pData, ref int nRetCount, int nMaxCount );
	
		//��ȡ��ǰAnnounce״̬��Ϣ���б�
		//Get the status of announces
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetAnnounceData", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Stat_GetAnnounceData( uint hDownloader, IntPtr pData, ref int nRetCount, int nMaxCount );
	
		//��ȡ��ǰ����ĵ�����Ϣ
		//Get the debug information of downloader
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Stat_GetBTDownloaderInfo", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern string FTK_Stat_GetBTDownloaderInfo( uint hDownloader );

		//////////////////////////////////////////////////////////////////////////
		//��Torrent�ļ���ȡ��Ϣ�ĺ����б�
		//Torrent file interface

		//�ж��ǲ����Լ�����ļ��ܵ�Torrent�ļ�
		//Return boolean, tell us is a cipher torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_IsCipherTorrent", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Torrent_IsCipherTorrent( string sFileName );

		//ִ�д��ļ��ж�ȡ���ݲ���ʼ���������
		//Open a torrent file handle
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_Open", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern uint FTK_Torrent_Open( string sFileName, uint nCodePage, string sDesKey, bool bValidEOF, bool bValidSort );

		//ִ�д��ļ��ж�ȡ���ݲ���ʼ���������, ���ʧ��, ���ش�����Ϣ
		//Open a torrent file handle, if failed, return error information
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_SafeOpen", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Torrent_SafeOpen( string sFileName, uint nCodePage, string sDesKey, bool bValidEOF, bool bValidSort, ref _tagErrInfo pErrInfo );
	
		//�ж��ǲ����Լ�����ļ��ܵ�Torrent����������
		//Return boolean, tell us is a cipher torrent binary data
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_IsCipherTorrentObj", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Torrent_IsCipherTorrentObj( [MarshalAs(UnmanagedType.LPArray)] byte[] pData, int nLength );
	
		//ִ�д�Torrent binary object�ж�ȡ���ݲ���ʼ���������
		//Open a torrent binary object
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_OpenObj", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Torrent_OpenObj( [MarshalAs(UnmanagedType.LPArray)] byte[] pData, int nLength, uint nCodePage, string sDesKey, bool bValidEOF, bool bValidSort, ref _tagErrInfo pErrInfo );

		//�رյ�ǰ�򿪵�Torrent�ļ�
		//Close Torrent file handle
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_Close", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern void FTK_Torrent_Close( uint hTorrentFile );

		//�ж���Ŀ¼�����ļ�
		//Return boolean, tell us is only a single file in torrent
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_IsFile", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern bool FTK_Torrent_IsFile( uint hTorrentFile );

		//��ȡ Torrent ����
		//Get the name of torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetTorrentName", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern string FTK_Torrent_GetTorrentName( uint hTorrentFile );

		//��ȡtorrent�е��ļ��ĸ���(����һ��)
		//Get total number of files
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetFilesCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern int FTK_Torrent_GetFilesCount( uint hTorrentFile );

		//��ȡtorrent�е��ļ��б�(����һ��)
		//Get a pointer to file list
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetFiles", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Torrent_GetFiles( uint hTorrentFile, ref _tagFileInfo pFileInfo );
	
		//��ȡtorrent�е��ļ��б��е�ĳ���ļ�����Ϣ
		//Get a pointer to a file of file list
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetFileInfo", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Torrent_GetFileInfo( uint hTorrentFile, int nIndex, ref _tagFileInfo pFileInfo );
	
		//��ȡInfo��Hashֵ, �ڲ�ʹ��
		//Get the binary info hash of torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetInfoHash", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern byte[] FTK_Torrent_GetInfoHash( uint hTorrentFile );

		//��ȡinfo��Hashֵ, ʮ������
		//Get the hex encoding info hash of torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetHexInfoHash", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern string FTK_Torrent_GetHexInfoHash( uint hTorrentFile );

		//��ȡ main annouce url
		//Get mainb announce url
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetMainAnnounce", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern string FTK_Torrent_GetMainAnnounce( uint hTorrentFile );
	
		//��ȡ Announce ����ĸ���
		//Get the number of all announce list
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetAnnouncesCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern int FTK_Torrent_GetAnnouncesCount( uint hTorrentFile );
	
		//��ȡָ���� Announce ���������Announce�ĸ���
		//Get the size of a announce list
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetAnnounceSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern int FTK_Torrent_GetAnnounceSize( uint hTorrentFile, int nGroupIndex );
	
		//��ȡָ���� Announce ������ָ��λ�õ�Announce
		//Get a annoucne of a announce list
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetAnnouncesVal", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern string FTK_Torrent_GetAnnouncesVal( uint hTorrentFile, int nGroupIndex, int nIndex );
	
		//��ȡ ע��
		//Get the comments
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetComments", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern string FTK_Torrent_GetComments( uint hTorrentFile );
	
		//��ȡ Torrent ����ʱ��
		//Get the creation time of torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetCreateTime", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Torrent_GetCreateTime( uint hTorrentFile );
	
		//��ȡpiece��Ĵ�С
		//Get the size of piece
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetPieceSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)]
		public static extern uint FTK_Torrent_GetPieceSize( uint hTorrentFile );

		//��ȡ�ļ��Ĵ�С
		//Get the total file size to transfer
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetFileSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern ulong FTK_Torrent_GetFileSize( uint hTorrentFile );
		
		//Piece��ĸ���
		//Get the total number of piece
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetPieceCount", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
  ��������public static extern uint FTK_Torrent_GetPieceCount( uint hTorrentFile );

		//��ȡPiece Hash ���б�
		//Get a pointer to piece hash list
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetPieceHashList", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern byte [] FTK_Torrent_GetPieceHashList( uint hTorrentFile );

		//�ͷ�PieceHash�б�
		//Release piece hash memory
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_FreePieceHashList", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Torrent_FreePieceHashList( uint hTorrentFile );
	
		//��ȡTorrent�ļ������Ա���
		//Get language code page of torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Torrent_GetLanCodePage", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_Torrent_GetLanCodePage( uint hTorrentFile );

		//////////////////////////////////////////////////////////////////////////
		//����Torrent�ļ��ĺ����б�
		//Create torrent file interface
	
		//��һ������torrent�ļ��ľ��
		//Open a making torrent handle
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_Open", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern uint FTK_MT_Open();
	
		//�رմ򿪵�����Torrent�ļ��ľ��
		//Close a making torrent handle
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_Close", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_Close( uint hMakeTorrent );
	
		//ִ�����ɶ���Ĳ���
		//Start to making torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_MakeTorrent", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_MT_MakeTorrent( uint hMakeTorrent );
	
		//ֹͣTorrent�ļ�����
		//Stop making torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_StopMake", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_StopMake( uint hMakeTorrent );
	
		//��ȡ�����ļ��Ľ���
		//Get progress of making torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_GetMTProgress", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern double FTK_MT_GetMTProgress( uint hMakeTorrent );
	
		//���ΪTorrent�ļ�
		//Save as a torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_SaveAsTorrentFile", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_MT_SaveAsTorrentFile( uint hMakeTorrent, string sFileName, string sDesKey );
	
		//���� annouce url
		//Set a main announce url
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_SetAnnounceUrl", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetAnnounceUrl( uint hMakeTorrent, string sValue );
	
		//��Ӷ����Announce �б�
		//Add a announce list
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_AddAnnounceList", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_AddAnnounceList( uint hMakeTorrent, string [] Announces, int nCount );
	
		//��Ӷ����Announce �б�, example: announce1;announce2;announce3;
		//Add a announce list, example: announce1;announce2;announce3;
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_AddAnnounceList2", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_AddAnnounceList2( uint hMakeTorrent, string sAnnounces );
	
		//��ն����Announce �б�
		//Clear all announce list
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_ClearAnnounceList", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_ClearAnnounceList( uint hMakeTorrent );
	
		//���� ע��
		//Set comments
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_SetComments", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetComments( uint hMakeTorrent, string sValue );
	
		//����piece��Ĵ�С
		//Set piece size to making torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_SetPieceSize", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetPieceSize( uint hMakeTorrent, uint nPieceSize );
	
		//����torrent�е��ļ�
		//Set the sourece file to making torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_SetFile", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetFile( uint hMakeTorrent, string sFileName );
	
		//����torrent�е��ļ�Ŀ¼(����ļ�)
		//Set the source path to making torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_SetPath", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetPath( uint hMakeTorrent, string sPathName );
	
		//����Torrent�ļ������Դ���(ֻ���ļ�����, ע�͵���Ч)
		//Set language code of torrent file
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_MT_SetLangCodePage", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_MT_SetLangCodePage( uint hMakeTorrent, uint nCodePage );
	
		//////////////////////////////////////////////////////////////////////////
		//Tracker interface, to get status of one torrent from tracker: peer count/seed count
	
		//HTTP tracker�ӿڣ� ���ڻ�ȡhttp Trackerĳ�����״̬��Ϣ
		//HTTP Tracker interface, to get status of one torrent from http tracker
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Tracker_Http1", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Tracker_Http1( string sTracker, string sInfoHash, ulong ulFileSize, ref uint nPeerCount, ref uint nSeedCount, ref bool bNetwordErr, string sErrInfo, int nLength );
	
		//HTTP tracker�ӿڣ� ���ڻ�ȡhttp Trackerĳ�����״̬��Ϣ
		//HTTP Tracker interface, to get status of one torrent from http tracker
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Tracker_Http2", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Tracker_Http2( string sTorrentFileName, ref uint nPeerCount, ref uint nSeedCount, ref bool bNetwordErr, string  sErrInfo, int nLength );
	
		//UDP tracker�ӿڣ� ���ڻ�ȡUDP Trackerĳ�����״̬��Ϣ
		//UDP Tracker interface, to get status of one torrent from UDP tracker
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Tracker_UDP1", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Tracker_UDP1( string sTracker, string sInfoHash, ulong ulFileSize, ref uint nPeerCount, ref uint nSeedCount, ref bool bNetwordErr, string sErrInfo, int nLength );
	
		//UDP tracker�ӿڣ� ���ڻ�ȡUDP Trackerĳ�����״̬��Ϣ
		//UDP Tracker interface, to get status of one torrent from UDP tracker
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Tracker_UDP2", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Tracker_UDP2( string sTorrentFileName, ref uint nPeerCount, ref uint nSeedCount, ref bool bNetwordErr, string sErrInfo, int nLength );
	
		//////////////////////////////////////////////////////////////////////////
		//Disk cache Settings
	
		//Set Disk cache size
		//���ô��̻���Ĵ�С
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Disk_SetCache", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern void FTK_Disk_SetCache( uint nMinCacheSize, uint nMaxCacheSize, uint nPhyMemorySize );
	
		//////////////////////////////////////////////////////////////////////////
		//Windows environment related interfaces
	
		//Get local machine ip address(get the first ip or best ip if there are more than one NICs)
		//��ȡ������IP��ַ(���ж��������£�ѡ���һ�������߰���һ���㷨ѡ������ʵ�һ��)
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Win_GetLocalIP", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern string FTK_Win_GetLocalIP( ref bool bPrivateIP );
	
		//Open Windows ICS/ICF(Windows XP/Windows 2003) 
		//�򿪲���ϵͳ���������ӷ���ǽ���������ӹ���(Windows XP/Windows 2003)
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Win_OpenWinXPICSF", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Win_OpenWinXPICSF( ushort nPort, ref bool bOpenFirewall, ref bool bPortMapping, byte nProtocol, string  sIP, string sAppName );
	
		//Open UPnP port mapping(Win9x/WinME/Win2000/WinXP/Win2003)
		//ִ�ж���֧��UPnPЭ���Router�����Զ��Ķ˿�ӳ������(��������Router��Ļ�������)
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Win_AddUPnPPortMapping", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern bool FTK_Win_AddUPnPPortMapping( ushort nPort, byte nProtoco, string sIP );
	
		//Patch Windows XP SP2 tcpip.sys file for best TCP/IP performance
		//����Windows XP SP2 ��tcpip.sys�򲹶����ƽ������������ƣ������������
		[DllImport("FTKernelAPI.dll", 
  ��������EntryPoint="FTK_Win_PacthSP2TCPIPLimitFile", 
  ��������CharSet=CharSet.Ansi,CallingConvention=CallingConvention.StdCall)] 
		public static extern int FTK_Win_PacthSP2TCPIPLimitFile( int nLimit );
	
		//////////////////////////////////////////////////////////////////////////
	}
}
