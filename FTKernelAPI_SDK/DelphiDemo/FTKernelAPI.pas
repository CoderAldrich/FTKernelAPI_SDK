{
//////////////////////////////////////////////////////////////////////////
// FTKernelAPI.pas
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
// ��Ȩ���� 2004-2006 ���������������缼�����޹�˾ ��������Ȩ��. �й�.
// �ٷ���վ: http://www.p2plib.com/
//
// FTKernelAPI �ǻ���BitTorrentЭ����ں˿�, ������ǿ����չ. ���԰�����
// ���ٵĿ����Լ���P2P����ϵͳ.
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
}

unit FTKernelAPI;

interface

uses
  windows, SysUtils;

type

  //����64λ�޷��ų�����
  //Define 64bit long integer type
  QWORD = int64;

  //���������ļ�����ľ��
  //Define Config INI file handle
  HConfigIni = PLongWord;

  //������������ľ��
  //Define downloader handle
  HDownloader = PLongWord;

  //�����ȡTorrent�ļ��ľ��
  //Define Torrent file handle
  HTorrentFile = PLongWord;

  //��������Torrent�ļ��ľ��
  //Define Making Torrent file handle
  HMakeTorrent = PLongWord;

  //����һ����ӦC�����е��ֽ�����
  //Define Array of byte like C language
  ArrayByte = array of BYTE;

  //���屻��֪ͨ�Ļص�����
  //Define callback function type
  FTK_CALLBACK_FUNC = function(nSocket: UINT = 0; pData: PByte = nil): Boolean; stdcall;

const

  //FTKernelAPI ��̬�������
  //Name of FTKernelAPI dynamic library
  FTKernelAPI_Library = 'FTKernelAPI.dll';

  //�û���ʶ�ĳ���
  //length of client identifier
  IDSIZE = 20;

  //BitTorrent �ͻ��˰汾��Ϣ����
  //bitorrent client version information
  AGENTSIZE = 64;

  //���ɵ�SHA��ɢ�еĳ���
  //Length of SHA1
  SHA1_DIGEST_LENGTH = 20;

  //����������
  //Proxytypes
  PROXYTYPE_NOPROXY = 0;
  PROXYTYPE_SOCKS4 = 1;
  PROXYTYPE_SOCKS4A = 2;
  PROXYTYPE_SOCKS5 = 3;
  PROXYTYPE_HTTP11 = 4;

  ////////////////////////
  //����״̬
  //Download status

  DLSTATE_NONE = 0;
  DLSTATE_ALLOCING = 1;
  DLSTATE_CHECKING = 2;
  DLSTATE_DOWNLOAD = 3;
  DLSTATE_PAUSING = 4;
  DLSTATE_CHECKEND = 5;
  DLSTATE_FETALERR = 6;
  DLSTATE_TERMINATE = 7;

  //����Piece��״̬
  //Piece status
  PIECESTATE_INCOMPLETE = 0;
  PIECESTATE_DOWNLOADING = 1;
  PIECESTATE_COMPLETE = 2;

  //Port type of Firewall and UPnP
  //����Windows����ǽ����UPnPʱ�Ķ˿����Ͷ���
  WCXT_TCP_PORT = 1;
  WCXT_UDP_PORT = 2;

type
  _tagPeerData = packed record
    m_dwIP: DWORD;
    m_nPort: WORD;
    m_pPeerID: array[0..IDSIZE - 1] of BYTE;

    //-------------------------------------

    m_bIsLocal: BYTE;
    m_szVersion: array[0..AGENTSIZE - 1] of Char;
    m_qwPeerHaveSize: QWORD;
    m_fDownRate: Single;
    m_fUpRate: Single;
    m_qwDownloaded: QWORD;
    m_qwUploaded: QWORD;
    m_fTimeElapsed: Single;
    m_fPeerDownRate: Single;
    m_szExtInfo: array[0..256 - 1] of char;
  end;

  ArrayPeerData = array of _tagPeerData;

type
  _tagMiniPeerData = packed record
    m_dwIP: DWORD;
    m_nPort: WORD;
  end;

  ArrayMiniPeerData = array of _tagMiniPeerData;

type
  _tagAnnounceData = packed record
    m_szURL: array[0..512 - 1] of char;
    m_bWorking: BYTE;
    m_bHeader: BYTE;
    m_nCount: UINT;
    m_nFailed: UINT;
    m_fTimeLeft: Single;
    m_fLastTime: Single;
    m_szExtInfo: array[0..512 - 1] of char;
  end;

  ArrayAnnounceData = array of _tagAnnounceData;

type
  _tagFileInfo = packed record
    m_szFileName: array[0..512 - 1] of char;
    m_qwFileSize: QWORD;
  end;

  ArrayFileInfo = array of _tagFileInfo;
  PFileInfoX = ^_tagFileInfo;

type
  _tagErrInfo = packed record
    m_szErrInfo: array[0..1024 - 1] of char;
  end;

  PErrorInfo = ^_tagErrInfo;

type
  _tagAnnounce = packed record
    m_szAnnounce: array[0..512 - 1] of char;
    m_szStatus: array[0..512 - 1] of char;
    m_fLastTime: double;
    m_nTotalCount: UINT;
    m_nFailCount: UINT;
    m_nTimeOut: UINT;
  end;

  ArrayAnnounce = array of _tagAnnounce;

  //////////////////////////////////////////////////////////////////////////
  //Libary License Interface

  //Set license key
  //����license����Կ
procedure FTK_License_Set(lpszLicense: PChar); stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//Library version information

//��ȡ��ǰ��İ汾��Ϣ, ����: nMajor = 1, nMinor = 1 => ver: 1.1
//Get library major version, example: nMajor = 1, nMinor = 1 => ver: 1.1
procedure FTK_Version_Info(nMajor: PInteger; nMinor: PInteger); stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//Define yourself protocol identifier string

//Define yourself protocol identifier string(to avoid Router filter)
//�������Լ�������Э���ʶ�����Աܿ�ĳЩ������Ӫ�̵�Э�����
procedure FTK_Protocol_IDS(pIDS: PChar; bAllowOtherIDS: Boolean = False); stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//Define yourself user identifier

//Define yourself user identifier(read by tracker)
//�����Լ����û���ʶ��Ϣ(Tracker���������Ի�ȡ��)
procedure FTK_Identifier_String10(pS: PChar); stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//Define yourself http tracker "UserAgent"

//Define yourself http tracker "UserAgent"
//�����Լ����ύ��http tracker��httpЭ���е�"UserAgent"
procedure FTK_Http_UserAgent(lpszUA: PChar); stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//Config INI file interface

//����һ���µ������ļ����
//Create a new Config INI file handle
function FTK_Config_Open(): HConfigIni; stdcall; external FTKernelAPI_Library;

//����һ�����ڵ������ļ����
//Destroy a HConfigIni hanle
procedure FTK_Config_Close(hConfigIni: HConfigIni); stdcall; external FTKernelAPI_Library;

//�����ַ���ѡ��
//Set string value item
procedure FTK_Config_SetStr(hConfigIni: HConfigIni; lpszName: LPCTSTR; lpszValue: LPCTSTR); stdcall; external FTKernelAPI_Library;

//��������ֵѡ��
//Set integer value item
procedure FTK_Config_SetInt(hConfigIni: HConfigIni; lpszName: LPCTSTR; nValue: QWORD); stdcall; external FTKernelAPI_Library;

//���ø�����ѡ��
//Set float value item
procedure FTK_Config_SetFloat(hConfigIni: HConfigIni; lpszName: LPCTSTR; fValue: double); stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//Context interface

//������ʼ��
//Initialize context
//@lpszIniFile: kernel configuration file - INI file
function FTK_Context_Init(lpszIniFile: LPCTSTR = nil; bLog: Boolean = True): boolean; stdcall; external FTKernelAPI_Library;

//������ʼ��
//Initialize context
//@lpszIniFile: kernel configuration file - INI file
function FTK_Context_Init2(hConfigIni: HConfigIni; bLog: Boolean = True): boolean; stdcall; external FTKernelAPI_Library;

//���ñ���֪ͨ�Ļص�����
//Set callback funtion pointer
procedure FTK_Context_NotifyCB(pfn: FTK_CALLBACK_FUNC); stdcall; external FTKernelAPI_Library;

//�ͷ���������
//Release context
procedure FTK_Context_Release(); stdcall; external FTKernelAPI_Library;

//�����������¼���������
//Context event driver
function FTK_Context_Run(): boolean; stdcall; external FTKernelAPI_Library;

//ǿ���˳�����, ֹͣ����
//��ֹͣʱҪ�˳��������е��߳����Կ���Ҫ��΢�ȴ�
//Stop context event driver
procedure FTK_Context_Stop(); stdcall; external FTKernelAPI_Library;

//���¸��������ļ��󶨶˿�
//Rebind listen port
procedure FTK_Context_ReBindListenPort(); stdcall; external FTKernelAPI_Library;

//�ж��Ƿ��Ѿ���ʼ��
//Is context initialized?
function FTK_Context_IsInit(): boolean; stdcall; external FTKernelAPI_Library;

//�Ƿ�����ɹ��˶˿�
//Is context running?
function FTK_Context_IsRunning(): boolean; stdcall; external FTKernelAPI_Library;

//�ж��Ƿ��Ѿ�����
//Return context thread ID
function FTK_Context_GetThreadID(): DWord; stdcall; external FTKernelAPI_Library;

//��ȡ�̵߳�ID
//Return listening port
function FTK_Context_GetListenPort(): Word; stdcall; external FTKernelAPI_Library;

//����ָ���˿ڰ󶨲���
//Return binding ip address
function FTK_Context_GetBindIP(): PChar; stdcall; external FTKernelAPI_Library;

//�ж��Ƿ�󶨶˿ڲ����ɹ�
//return bind listen port status
function FTK_Context_IsBindListenPort(): Boolean; stdcall; external FTKernelAPI_Library;

//�޸�ǿ���ں��ύTracker��IP��ַ
//Tell kernel the ip address to submit to tracker
procedure FTK_Context_SetForceIP(lpszIP: LPCTSTR); stdcall; external FTKernelAPI_Library;

//���ü���ĳЩ�����Ĵ���torrent��ʽ
//Set to open some mistake mistaken TORRENT file
procedure FTK_Context_TorrentFile(bValidEof: Boolean = True; bValidSort: Boolean = True); stdcall; external FTKernelAPI_Library;

//������־�������ļ�
//Set language to write log
procedure FTK_Context_OpenLanguageFile(lpszLanguageFile: LPCTSTR); stdcall; external FTKernelAPI_Library;

//�ͷŴ��ݸ��ⲿʹ�õ����Ӷ����ָ��(���ûص�����ʹ��, ���ӻص�����ʱ�������)
//Free socket handle to external module
procedure FTK_Context_CloseExtSocket(nSocket: Integer); stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//Context active sharing files

//����һ��Hashֵ(��д�Ĳ���'%'��HEX�ַ���)�Ͷ�Ӧ����Ϣ����
procedure FTK_Context_ShareTorrent(lpszInfoHex: LPCTSTR; lpszAnnounce: LPCTSTR); stdcall; external FTKernelAPI_Library;

//ɾ��һ��Hashֵ���丽���Ķ�Ӧ��Ϣ
procedure FTK_Context_UnshareTorrent(lpszInfoHex: LPCTSTR); stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//Downloader interface

//Create a new HDownloader handle
function FTK_Downloader_Open(): HDownloader; stdcall; external FTKernelAPI_Library;

//Destroy a HDownloader hanle
procedure FTK_Downloader_Close(hDownloader: HDownloader); stdcall; external FTKernelAPI_Library;

//��ǰ�ĳ�ʼ��IP���˶���ĺ���(FTK_Downloader_Init* ����֮ǰ����), ����ĳЩ�ε�IP��ַ, "ipfilter.dat" �ļ���eMule(����)����
//Previous Initialize IP filter object to filter some peer's IP, "ipfilter.dat" file is compatiable with eMule.
function FTK_Downloader_PreInitIPFilter(hDownloader: HDownloader; lpszIPFilterFile: LPCTSTR; nLevel: UINT = 127): Boolean; stdcall; external FTKernelAPI_Library;

//��ǰ�ĳ�ʼ��, ���տ���Ⱥ�˳���������(�����ڱ����ر߲��ŵ����)
//Previous Initialize, Tell kernel to sequential download piece
procedure FTK_Downloader_PreInitSEQMode(hDownloader: HDownloader); stdcall; external FTKernelAPI_Library;

//Ԥ�ȳ�ʼ���ļ�ѡ�����ص����ȼ���
//�����У�ÿ��Ԫ�ص�ֵ��ʾ: -2:������, -1: ��, 0: һ��, 1:��
//Previous Initialize, Tell kernel to Set priority of file
//-2: no download, -1: low, 0: middle, 1: high
procedure FTK_Downloader_PreInitFilePriority(hDownloader: HDownloader; pFilePriority: PChar; nFilesCount: Integer); stdcall; external FTKernelAPI_Library;

//Ԥ�ȳ�ʼ��Tracker�б���ʹ���ⲿ�ṩ��Tracker�б������Torrent�ļ��е�Tracker�б�
//Tracker1;Tracker2;Tracker3|Tracker1;Tracker2|Tracker1;Tracker2
procedure FTK_Downloader_PreInitTrackers(hDownloader: HDownloader; lpszAnnouces: LPCTSTR); stdcall; external FTKernelAPI_Library;

//Ԥ�ȳ�ʼ��Զ�������Լ���Socket�ľ��ֵ
//Previous Initialize, Tell kernel to add a remote [socket] to queue
procedure FTK_Downloader_PreInitSocket(hDownloader: HDownloader; nSocket: Integer); stdcall; external FTKernelAPI_Library;

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
function FTK_Downloader_Init(
  hDownloader: HDownloader;
  lpszTorrentFileName: LPCTSTR;
  pPreAllocFile: PByte;
  nPreAllocFileLen: Integer;
  bOnlyCheckFile: boolean = FALSE;
  lpszDestFileName: LPCTSTR = nil;
  lpszConfig: LPCTSTR = nil;
  lpszLogFileName: LPCTSTR = nil;
  lpszStatusFileName: LPCTSTR = nil;
  bQuickySeed: Boolean = False;
  lpszDesKey: LPCTSTR = nil;
  nCodePage: UINT = CP_ACP): boolean; stdcall; external FTKernelAPI_Library;

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
function FTK_Downloader_Init2(
  hDownloader: HDownloader;
  lpszTorrentFileName: LPCTSTR;
  pPreAllocFile: PByte;
  nPreAllocFileLen: Integer;
  bOnlyCheckFile: boolean = FALSE;
  lpszDestFileName: LPCTSTR = nil;
  hConfigIni: HConfigIni = nil;
  lpszLogFileName: LPCTSTR = nil;
  lpszStatusFileName: LPCTSTR = nil;
  bQuickySeed: Boolean = False;
  lpszDesKey: LPCTSTR = nil;
  nCodePage: UINT = CP_ACP): boolean; stdcall; external FTKernelAPI_Library;

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
function FTK_Downloader_Init3(
  hDownloader: HDownloader;
  pData: PChar;
  nLength: Integer;
  pPreAllocFile: PByte;
  nPreAllocFileLen: Integer;
  bOnlyCheckFile: Boolean = False;
  lpszDestFileName: LPCTSTR = nil;
  lpszConfig: LPCTSTR = nil;
  lpszLogFileName: LPCTSTR = nil;
  lpszStatusFileName: LPCTSTR = nil;
  bQuicklySeed: Boolean = False;
  lpszDesKey: LPCTSTR = nil;
  nCodePage: UINT = CP_ACP): boolean; stdcall; external FTKernelAPI_Library;

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
function FTK_Downloader_Init4(
  hDownloader: HDownloader;
  pData: PChar;
  nLength: Integer;
  pPreAllocFile: PByte;
  nPreAllocFileLen: Integer;
  bOnlyCheckFile: Boolean = False;
  lpszDestFileName: LPCTSTR = nil;
  hConfigIni: HConfigIni = nil;
  lpszLogFileName: LPCTSTR = nil;
  lpszStatusFileName: LPCTSTR = nil;
  bQuicklySeed: Boolean = False;
  lpszDesKey: LPCTSTR = nil;
  nCodePage: UINT = CP_ACP): boolean; stdcall; external FTKernelAPI_Library;

//�ͷ����ض���
//Release downloader handle
function FTK_Downloader_Release(hDownloader: HDownloader): boolean; stdcall; external FTKernelAPI_Library;

//ִ�������߳�
//Execute downloader
function FTK_Downloader_Execute(hDownloader: HDownloader): boolean; stdcall; external FTKernelAPI_Library;

//��ͣ����
//Pause downloader
procedure FTK_Downloader_Pause(hDownloader: HDownloader); stdcall; external FTKernelAPI_Library;

//�ָ�����
//Resume downloader
procedure FTK_Downloader_Resume(hDownloader: HDownloader); stdcall; external FTKernelAPI_Library;

//�Ƿ��Ѿ���ʼ��
//Is downloader intialized?
function FTK_Downloader_IsInit(hDownloader: HDownloader): boolean; stdcall; external FTKernelAPI_Library;

//��ȡ��������Ŀǰ�Ľ׶�״̬
//Return downloader state
function FTK_Downloader_GetState(hDownloader: HDownloader): Integer stdcall; external FTKernelAPI_Library;

//�Ƿ�ֻ�ǽ����ļ����
//Only checking file, don't downloading...
function FTK_Downloader_IsOnlyCheckFile(hDownloader: HDownloader): boolean; stdcall; external FTKernelAPI_Library;

//�Ƿ��Ѿ����������(�ж�ѡ���ļ�����)
//Is all selected files finished?
function FTK_Downloader_IsFinished(hDownloader: HDownloader): boolean; stdcall; external FTKernelAPI_Library;

//�Ƿ��Ѿ����������(ȫ������)
//Is all files finished?
function FTK_Downloader_IsAllFinished(hDownloader: HDownloader): boolean; stdcall; external FTKernelAPI_Library;

//����ָ����Peer
//Add external source peer
procedure FTK_Downloader_AddSource(hDownloader: HDownloader; const pchIP: PChar; nPort: Word; const pPeerID: PByte = nil); stdcall; external FTKernelAPI_Library;

//����ָ����User
//Add external source peer(socket handle)
procedure FTK_Downloader_AddSourceExt(hDownloader: HDownloader; nSocket: UINT); stdcall; external FTKernelAPI_Library;

//�ⲿ��̬���Ӹ�����Announce
//Add external announce
procedure FTK_Downloader_AddExtAnnounce(hDownloader: HDownloader; lpszAnnounce: LPCTSTR); stdcall; external FTKernelAPI_Library;

//�ֶ�����Announce���Ͻ�������
//Reannounce manually
procedure FTK_Downloader_ReannounceAll(hDownloader: HDownloader); stdcall; external FTKernelAPI_Library;

//���տ���Ⱥ�˳���������(�����ڱ����ر߲��ŵ����)
 //Tell kernel to sequential download piece
procedure FTK_Downloader_SetSeqPicker(hDownloader: HDownloader; bSeq: Boolean = False; nSEQFileIndex: Integer = 0); stdcall; external FTKernelAPI_Library;

//���������ļ������ȼ���
// -2:������, -1: ��, 0: һ��, 1:��
//Set priority of file
//-2: no download, -1: low, 0: middle, 1: high
procedure FTK_Downloader_SetFilePriority(hDownloader: HDownloader; nIndex: Integer; chPriority: Byte = 0; bDoPriority: boolean = TRUE); stdcall; external FTKernelAPI_Library;

//ǿ���������½��ļ������ȼ���ֵ��Piece
//Force to set priority of all piece immediately
procedure FTK_Downloader_ForceFilePriority(hDownloader: HDownloader); stdcall; external FTKernelAPI_Library;

//�ⲿ����, �ֶ�������������������(0.0��ʾû������)
//Set fixed max download rate
procedure FTK_Downloader_SetFixMaxDownloadRate(hDownloader: HDownloader; fMaxDownloadRate: Double = 0.0); stdcall; external FTKernelAPI_Library;

//�ⲿ����, ��ȡ�ֶ�������������������(0.0��ʾû������)
//Get fixed max download rate
function FTK_Downloader_GetFixMaxDownloadRate(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//�ⲿ����, �ֶ����������ϴ�������(0.0��ʾû������)
//Set fixed max upload rate
procedure FTK_Downloader_SetFixMaxUploadRate(hDownloader: HDownloader; fMaxUploadRate: Double = 0.0); stdcall; external FTKernelAPI_Library;

//�ⲿ����, ��ȡ�ֶ����������ϴ�������(0.0��ʾû������)
//Get fixed max upload rate
function FTK_Downloader_GetFixMaxUploadRate(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//��������ĳЩ�ض������ӷ�����(SEED), ���Լ��������ϴ���(0��ʾû������, ע�ⵥλ��: KB)
//Set fixed max upload rate of SOME CERTAIN SEED to me, 0 means no limit, UNIT is KB
procedure FTK_Downloader_SetSeedMaxUPSpeed(hDownloader: HDownloader; nSpeed: UINT = 0); stdcall; external FTKernelAPI_Library;

//���������ڣ���ֹĳ��IP������, ֻ�ڵ�ǰ��������ڼ���Ч
//Ban IP for X seconds, ONLY for the current active HDownloader
procedure FTK_Downloader_BanPeerIP(hDownloader: HDownloader; lpszIP: LPCTSTR; nBannedSeconds: UINT); stdcall; external FTKernelAPI_Library;

//��ȡ�̵߳�ID
//Get thread ID
function FTK_Downloader_GetThreadID(hDownloader: HDownloader): DWord; stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//ȫ�ֲ�������
//Global settings

//��ĳ��Torrent�ļ���SHA1ֵ�������
//Add torrent into SHA1 list
procedure FTK_GlobalVar_AddTorrentSHA1(lpszSHA: LPCTSTR; hDownloader: HDownloader); stdcall; external FTKernelAPI_Library;

//��ĳ��Torrent�ļ���SHA1ֵ�Ӷ�����ɾ��
//Remove torrent from SHA1 list
procedure FTK_GlobalVar_RemoveTorrentSHA1(lpszSHA: LPCTSTR); stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//���������������б�
//Proxy interface

//���ý�������Trackerʱʹ�ô���������
//Only tracker using proxy settings
procedure FTK_Proxy_SetOnlyTracker(bOnlyTracker: boolean = FALSE); stdcall; external FTKernelAPI_Library;

//��յ�ǰ�Ĵ�����Ϣ(������PROXYTYPE_NOPROXY)
//Only PROXYTYPE_NOPROXY
procedure FTK_Proxy_SetType(nProxyType: Integer); stdcall; external FTKernelAPI_Library;

//���ô���(������PROXYTYPE_NOPROXY)
//May not be PROXYTYPE_NOPROXY
procedure FTK_Proxy_SetProxy(nProxyType: Integer; const pProxyHost: PChar; ProxyPort: Integer); stdcall; external FTKernelAPI_Library;

//����SOCKS5��HTTP1.1��Ҫ��֤��Ϣ�Ĵ���
//Only SOCKS5 and HTTP1.1 proxies
procedure FTK_Proxy_SetAuthProxy(nProxyType: Integer; const pProxyHost: PChar; ProxyPort: Integer; const pProxyUser: PChar; const pProxyPass: PChar); stdcall; external FTKernelAPI_Library;

//��ȡ����������
//Return proxy type
function FTK_Proxy_GetProxyType(): Integer; stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//Downloader statistic information interface

//��ȡ�ܹ��Ѿ�����(��֤�ɹ�)������
//Get the size of having received data for all file
function FTK_Stat_GetTotalFileHaveSize(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//��ȡѡ���Ѿ�����(��֤�ɹ�)������
//Get the size of having received data for a file
function FTK_Stat_GetSelectedFileHaveSize(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//��ȡ�Ѿ�˳�����ص�Ŀǰ���Դ�ͷ��ʼ���ŵ����ݳ���
//Get the size of sequential piece from file front
function FTK_Stat_GetStartSeqFileSize(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//��ȡ���һ�����ص��ֽ���
//Get the size of lasted receiving data
function FTK_Stat_GetLastDataSize(hDownloader: HDownloader): DWord; stdcall; external FTKernelAPI_Library;

//��ȡ�ܹ��������ֽ���
//Get the size of bad data
function FTK_Stat_GetBadDataSize(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//��ǰ�ܹ������ӵĸ���
//Get the number of total peer
function FTK_Stat_GetTotalPeerCount(hDownloader: HDownloader): Integer; stdcall; external FTKernelAPI_Library;

//��ǰ�������ӵĸ���
//Get the number of active peer
function FTK_Stat_GetActivePeerCount(hDownloader: HDownloader): Integer; stdcall; external FTKernelAPI_Library;

//��ǰ�ı������ӵĸ���
//Get the number of passive peer
function FTK_Stat_GetPassivePeerCount(hDownloader: HDownloader): Integer; stdcall; external FTKernelAPI_Library;

//��ǰ���������еĸ���
//Get number of connecting peer
function FTK_Stat_GetConnectingPeerCount(hDownloader: HDownloader): Integer; stdcall; external FTKernelAPI_Library;

//��ȡ�Ѿ����ӵ����ӵĸ���
//Get number of seed
function FTK_Stat_GetSeedCount(hDownloader: HDownloader): Integer; stdcall; external FTKernelAPI_Library;

//��ȡ�����ϴ������ӵĸ���
//Get the number of uploading peer
function FTK_Stat_GetUploadPeerCount(hDownloader: HDownloader): Integer; stdcall; external FTKernelAPI_Library;

//��ȡ�������ص����ӵĸ���
//Get the number of downloading peer
function FTK_Stat_GetDownloadPeerCount(hDownloader: HDownloader): Integer; stdcall; external FTKernelAPI_Library;

//��ȡ�ܹ����Ի�ȡ��Seed�ĸ���
//Get the number of total available seed
function FTK_Stat_GetTotalAvailSeedCount(hDownloader: HDownloader): Integer; stdcall; external FTKernelAPI_Library;

//��ȡ�ܹ����Ի�ȡ��Peer�ĸ���
//Get the number of peer
function FTK_Stat_GetTotalAvailPeerCount(hDownloader: HDownloader): Integer; stdcall; external FTKernelAPI_Library;

//�ɵ����ӵĸ���
//Get old seed number
function FTK_Stat_GetOldSeedPeerCount(hDownloader: HDownloader): Integer; stdcall; external FTKernelAPI_Library;

//��ȡ�Ƿ������Ѿ���һ��Tracker���ӳɹ�
//Is any tracker successfull?
function FTK_Stat_IsAnyTrackerOK(hDownloader: HDownloader): Boolean; stdcall; external FTKernelAPI_Library;

//���������Ѿ����ص����ݳ���
//Get downloaded bytes
function FTK_Stat_GetDownloaded(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//���������Ѿ��ϴ������ݳ���
//Get uploaded bytes
function FTK_Stat_GetUploaded(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//�����Ѿ�����ʱ��(����ʱ�䲻ͬ������ʱ��)
//Get total running time
function FTK_Stat_GetRunningTime(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//�������ص�ʱ��(���������, ������ʱ����ԶΪ0)
//Get total downloaded time
function FTK_Stat_GetDownloadTime(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//��������ʣ���ʱ��, ���������ʼ���
//Get the left time to download
function FTK_Stat_GetLeftTime(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//��ȡ��ǰ���ϴ���
//Get upload rate
function FTK_Stat_GetUploadRate(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//��ȡ��ǰ��������
//Get downloading rate
function FTK_Stat_GetDownloadRate(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//��ȡָ����Piece�����ؽ���
//Get the progress of a piece
procedure FTK_Stat_GetPieceState(hDownloader: HDownloader; pPiece: PByte; nCount: Integer); stdcall; external FTKernelAPI_Library;

//��ȡ����ļ��Ľ���
//Get the progress of cheching piece
function FTK_Stat_GetCheckPieceSize(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//��ȡ����Piece�ĸ���
//Get number of checked piece
function FTK_Stat_GetCheckPieceCount(hDownloader: HDownloader): DWord; stdcall; external FTKernelAPI_Library;

//��ȡ�Ѿ�����ռ�Ĵ�С
//Get the size of allocated file
function FTK_Stat_GetAllocSpaceSize(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//��ȡ��ǰ�Ľ�����
//Get healthy rate
function FTK_Stat_GetHealthRate(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//��ȡ��ǰ����󻺴��С
//Get the size of max cache
function FTK_Stat_GetMaxCacheSize(hDownloader: HDownloader): DWord; stdcall; external FTKernelAPI_Library;

//��ȡ�Ѿ�ʹ�õĻ����С
//Get the size of used cache
function FTK_Stat_GetUseCacheSize(hDownloader: HDownloader): DWord; stdcall; external FTKernelAPI_Library;

//��ȡ����дӲ�̵��ܵĴ���
//Get writed disk count
function FTK_Stat_GetWriteDiskCount(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//��ȡ��������дӲ�̵Ĵ���
//Get really writed disk count
function FTK_Stat_GetRealWriteDiskCount(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//��ȡ���ζ�Ӳ�̵��ܵĴ���
//Get readed disk count
function FTK_Stat_GetReadDiskCount(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//��ȡ����������Ӳ�̵Ĵ���
//Get really readed disk count
function FTK_Stat_GetRealReadDiskCount(hDownloader: HDownloader): QWORD; stdcall; external FTKernelAPI_Library;

//��ȡдӲ�̵�Ƶ��(��/��)
//Get writing disk frenqence(number/second)
function FTK_Stat_GetWriteDiskFrenq(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//��ȡ����дӲ�̵�Ƶ��(��/��)
//Get really writing disk frenqence(number/second)
function FTK_Stat_GetRealWriteDiskFrenq(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//��ȡ��Ӳ�̵�Ƶ��(��/��)
//Get reading disk frenqence(number/second)
function FTK_Stat_GetReadDiskFrenq(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//��ȡ������Ӳ�̵�Ƶ��(��/��)
//Get really reading disk frenqence(number/second)
function FTK_Stat_GetRealReadDiskFrenq(hDownloader: HDownloader): Double; stdcall; external FTKernelAPI_Library;

//��ȡ��ǰ��־�ļ���·��+����
//Get log file name
procedure FTK_Stat_GetLogPathFileName(hDownloader: HDownloader; lpszFileName: PChar); stdcall; external FTKernelAPI_Library;

//��ȡָ�����ļ��Ľ���
//Get the progress of a file
function FTK_Stat_GetFileHaveSize(hDownloader: HDownloader; nIndex: Integer): QWORD; stdcall; external FTKernelAPI_Library;

//��ȡ��ǰ�û�״̬��Ϣ���б�
//Get the peers information
procedure FTK_Stat_GetPeerData(hDownloader: HDownloader; pData: ArrayPeerData; nRetCount: PInteger; nMaxCount: Integer); stdcall; external FTKernelAPI_Library;

//��ȡ��ǰ�����û�״̬��Ϣ���б�
//Get the some peers information
procedure FTK_Stat_GetPeerRangeData(hDownloader: HDownloader; pData: ArrayPeerData; nFrom: Integer; nTo: Integer; var nRetCount: Integer; nMaxCount: Integer; bExtInfo: Boolean = False); stdcall; external FTKernelAPI_Library;

//��ȡ��ǰ�û�״̬��Ϣ���б�(ֻ��ȡIP�Ͷ˿�)
//Get the peers information(only IP and port)
procedure FTK_Stat_GetMiniPeerData(hDownloader: HDownloader; pData: ArrayMiniPeerData; nRetCount: PInteger; nMaxCount: Integer); stdcall; external FTKernelAPI_Library;

//��ȡ��ǰAnnounce״̬��Ϣ���б�
//Get the status of announces
procedure FTK_Stat_GetAnnounceData(hDownloader: HDownloader; pData: ArrayAnnounceData; nRetCount: PInteger; nMaxCount: Integer); stdcall; external FTKernelAPI_Library;

//��ȡ��ǰ����ĵ�����Ϣ
//Get the debug information of downloader
function FTK_Stat_GetBTDownloaderInfo(hDownloader: HDownloader): LPCTSTR; stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//��Torrent�ļ���ȡ��Ϣ�ĺ����б�
//Torrent file interface

//�ж��ǲ����Լ�����ļ��ܵ�Torrent�ļ�
//Return boolean, tell us is a cipher torrent file
function FTK_Torrent_IsCipherTorrent(lpszFileName: LPCTSTR): boolean; stdcall; external FTKernelAPI_Library;

//ִ�д��ļ��ж�ȡ���ݲ���ʼ���������
//Open a torrent file handle
function FTK_Torrent_Open(lpszFileName: LPCTSTR; nCodePage: UINT = CP_ACP; lpszDesKey: LPCTSTR = nil; bValidEOF: Boolean = True; bValidSort: Boolean = True): HTorrentFile; stdcall; external FTKernelAPI_Library;

//ִ�д��ļ��ж�ȡ���ݲ���ʼ���������, ���ʧ��, ���ش�����Ϣ
//Open a torrent file handle, if failed, return error information
function FTK_Torrent_SafeOpen(lpszFileName: LPCTSTR; nCodePage: UINT = CP_ACP; lpszDesKey: LPCTSTR = nil; bValidEOF: Boolean = True; bValidSort: Boolean = True; pErrInfo: PErrorInfo = nil): HTorrentFile; stdcall; external FTKernelAPI_Library;

//�ж��ǲ����Լ�����ļ��ܵ�Torrent����������
//Return boolean, tell us is a cipher torrent binary data
function FTK_Torrent_IsCipherTorrentObj(pData: PByte; nLength: Integer): Boolean; stdcall; external FTKernelAPI_Library;

//ִ�д�Torrent binary object�ж�ȡ���ݲ���ʼ���������
//Open a torrent binary object
function FTK_Torrent_OpenObj(pData: PByte; nLength: Integer; nCodePage: UINT = CP_ACP; lpszDesKey: LPCTSTR = nil; bValidEOF: Boolean = True; bValidSort: Boolean = True; pErrInfo: PErrorInfo = nil): HTorrentFile; stdcall; external FTKernelAPI_Library;

//�رյ�ǰ�򿪵�Torrent�ļ�
//Close Torrent file handle
procedure FTK_Torrent_Close(hTorrentFile: HTorrentFile); stdcall; external FTKernelAPI_Library;

//�ж���Ŀ¼�����ļ�
//Return boolean, tell us is only a single file in torrent
function FTK_Torrent_IsFile(hTorrentFile: HTorrentFile): boolean; stdcall; external FTKernelAPI_Library;

//��ȡ Torrent ����
//Get the name of torrent file
function FTK_Torrent_GetTorrentName(hTorrentFile: HTorrentFile): LPCTSTR; stdcall; external FTKernelAPI_Library;

//��ȡtorrent�е��ļ��ĸ���(����һ��)
//Get total number of files
function FTK_Torrent_GetFilesCount(hTorrentFile: HTorrentFile): Integer; stdcall; external FTKernelAPI_Library;

//��ȡtorrent�е��ļ��б�(����һ��)
//Get a pointer to file list
procedure FTK_Torrent_GetFiles(hTorrentFile: HTorrentFile; pFileInfo: ArrayFileInfo); stdcall; external FTKernelAPI_Library;

//��ȡtorrent�е��ļ��б��е�ĳ���ļ�����Ϣ
//Get a pointer to a file of file list
procedure FTK_Torrent_GetFileInfo(hTorrentFile: HTorrentFile; nIndex: Integer; pFileInfo: PFileInfoX); stdcall; external FTKernelAPI_Library;

//��ȡInfo��Hashֵ, �ڲ�ʹ��
//Get the binary info hash of torrent file
function FTK_Torrent_GetInfoHash(hTorrentFile: HTorrentFile): PByte; stdcall; external FTKernelAPI_Library;

//��ȡinfo��Hashֵ, ʮ������
//Get the hex encoding info hash of torrent file
function FTK_Torrent_GetHexInfoHash(hTorrentFile: HTorrentFile): LPCTSTR; stdcall; external FTKernelAPI_Library;

//��ȡ main annouce url
//Get mainb announce url
function FTK_Torrent_GetMainAnnounce(hTorrentFile: HTorrentFile): LPCTSTR; stdcall; external FTKernelAPI_Library;

//��ȡ Announce ����ĸ���
//Get the number of all announce list
function FTK_Torrent_GetAnnouncesCount(hTorrentFile: HTorrentFile): Integer; stdcall; external FTKernelAPI_Library;

//��ȡָ���� Announce ���������Announce�ĸ���
//Get the size of a announce list
function FTK_Torrent_GetAnnounceSize(hTorrentFile: HTorrentFile; nGroupIndex: Integer): Integer; stdcall; external FTKernelAPI_Library;

//��ȡָ���� Announce ������ָ��λ�õ�Announce
//Get a annoucne of a announce list
function FTK_Torrent_GetAnnouncesVal(hTorrentFile: HTorrentFile; nGroupIndex: Integer; nIndex: Integer): LPCTSTR; stdcall; external FTKernelAPI_Library;

//��ȡ ע��
//Get the comments
function FTK_Torrent_GetComments(hTorrentFile: HTorrentFile): LPCTSTR; stdcall; external FTKernelAPI_Library;

//��ȡ Torrent ����ʱ��
//Get the creation time of torrent file
function FTK_Torrent_GetCreateTime(hTorrentFile: HTorrentFile): TDateTime; stdcall; external FTKernelAPI_Library;

//��ȡpiece��Ĵ�С
//Get the size of piece
function FTK_Torrent_GetPieceSize(hTorrentFile: HTorrentFile): DWord; stdcall; external FTKernelAPI_Library;

//��ȡ�ļ��Ĵ�С
//Get the total file size to transfer
function FTK_Torrent_GetFileSize(hTorrentFile: HTorrentFile): QWORD; stdcall; external FTKernelAPI_Library;

//Piece��ĸ���
//Get the total number of piece
function FTK_Torrent_GetPieceCount(hTorrentFile: HTorrentFile): DWord; stdcall; external FTKernelAPI_Library;

//��ȡPiece Hash ���б�
//Get a pointer to piece hash list
function FTK_Torrent_GetPieceHashList(hTorrentFile: HTorrentFile): PByte; stdcall; external FTKernelAPI_Library;

//�ͷ�PieceHash�б�
//Release piece hash memory
procedure FTK_Torrent_FreePieceHashList(hTorrentFile: HTorrentFile); stdcall; external FTKernelAPI_Library;

//��ȡTorrent�ļ������Ա���
//Get language code page of torrent file
function FTK_Torrent_GetLanCodePage(hTorrentFile: HTorrentFile): UINT; stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//����Torrent�ļ��ĺ����б�
//Create torrent file interface

//��һ������torrent�ļ��ľ��
//Open a making torrent handle
function FTK_MT_Open(): HMakeTorrent; stdcall; external FTKernelAPI_Library;

//�رմ򿪵�����Torrent�ļ��ľ��
//Close a making torrent handle
procedure FTK_MT_Close(hMakeTorrent: HMakeTorrent); stdcall; external FTKernelAPI_Library;

//ִ�����ɶ���Ĳ���
//Start to making torrent file
function FTK_MT_MakeTorrent(hMakeTorrent: HMakeTorrent): boolean; stdcall; external FTKernelAPI_Library;

//ֹͣTorrent�ļ�����
//Stop making torrent file
procedure FTK_MT_StopMake(hMakeTorrent: HMakeTorrent); stdcall; external FTKernelAPI_Library;

//��ȡ�����ļ��Ľ���
//Get progress of making torrent file
function FTK_MT_GetMTProgress(hMakeTorrent: HMakeTorrent): Double; stdcall; external FTKernelAPI_Library;

//����ΪTorrent�ļ�
//Save as a torrent file
function FTK_MT_SaveAsTorrentFile(hMakeTorrent: HMakeTorrent; lpszFileName: LPCTSTR; lpszDesKey: LPCTSTR = nil): boolean; stdcall; external FTKernelAPI_Library;

//���� annouce url
//Set a main announce url
procedure FTK_MT_SetAnnounceUrl(hMakeTorrent: HMakeTorrent; lpszValue: LPCTSTR); stdcall; external FTKernelAPI_Library;

//���Ӷ����Announce �б�
//Add a announce list
procedure FTK_MT_AddAnnounceList(hMakeTorrent: HMakeTorrent; Announces: array of LPCTSTR; nCount: Integer); stdcall; external FTKernelAPI_Library;

//���Ӷ����Announce �б�, example: announce1;announce2;announce3;
//Add a announce list, example: announce1;announce2;announce3;
procedure FTK_MT_AddAnnounceList2(hMakeTorrent: HMakeTorrent; lpszAnnounces: LPCTSTR); stdcall; external FTKernelAPI_Library;

//��ն����Announce �б�
//Clear all announce list
procedure FTK_MT_ClearAnnounceList(hMakeTorrent: HMakeTorrent); stdcall; external FTKernelAPI_Library;

//���� ע��
//Set comments
procedure FTK_MT_SetComments(hMakeTorrent: HMakeTorrent; lpszValue: LPCTSTR); stdcall; external FTKernelAPI_Library;

//����piece��Ĵ�С
//Set piece size to making torrent file
procedure FTK_MT_SetPieceSize(hMakeTorrent: HMakeTorrent; dwPieceSize: DWord); stdcall; external FTKernelAPI_Library;

//����torrent�е��ļ�
//Set the sourece file to making torrent file
procedure FTK_MT_SetFile(hMakeTorrent: HMakeTorrent; lpszFileName: LPCTSTR); stdcall; external FTKernelAPI_Library;

//����torrent�е��ļ�Ŀ¼(����ļ�)
//Set the source path to making torrent file
procedure FTK_MT_SetPath(hMakeTorrent: HMakeTorrent; lpszPathName: LPCTSTR); stdcall; external FTKernelAPI_Library;

//����Torrent�ļ������Դ���(ֻ���ļ�����, ע�͵���Ч)
//Set language code of torrent file
procedure FTK_MT_SetLangCodePage(hMakeTorrent: HMakeTorrent; nCodePage: UINT = CP_ACP); stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//Disk cache Settings

//Set Disk cache size
//���ô��̻���Ĵ�С
procedure FTK_Disk_SetCache(nMinCacheSize: UINT; nMaxCacheSize: UINT; nPhyMemorySize: UINT); stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////
//Windows environment related interfaces

//Get local machine ip address(get the first ip or best ip if there are more than one NICs)
//��ȡ������IP��ַ(���ж��������£�ѡ���һ�������߰���һ���㷨ѡ������ʵ�һ��)
function FTK_Win_GetLocalIP(bPrivateIP: PInteger): PChar; stdcall; external FTKernelAPI_Library;

//Open Windows ICS/ICF(Windows XP/Windows 2003)
//�򿪲���ϵͳ���������ӷ���ǽ���������ӹ���(Windows XP/Windows 2003)
function FTK_Win_OpenWinXPICSF(nPort: Short; bOpenFirewall: PInteger; bPortMapping: PInteger; nProtocol: Byte = WCXT_TCP_PORT; lpszIP: LPCTSTR = nil; lpszAppName: LPCTSTR = nil): Boolean; stdcall; external FTKernelAPI_Library;

//Open UPnP port mapping(Win9x/WinME/Win2000/WinXP/Win2003)
//ִ�ж���֧��UPnPЭ���Router�����Զ��Ķ˿�ӳ������(��������Router��Ļ�������)
function FTK_Win_AddUPnPPortMapping(nPort: Short; nProtocol: Byte = WCXT_TCP_PORT; lpszIP: LPCTSTR = nil): Boolean; stdcall; external FTKernelAPI_Library;

//Patch Windows XP SP2 tcpip.sys file for best TCP/IP performance
//����Windows XP SP2 ��tcpip.sys�򲹶����ƽ������������ƣ������������
function FTK_Win_PacthSP2TCPIPLimitFile(nLimit: Integer = 10): Integer; stdcall; external FTKernelAPI_Library;

//////////////////////////////////////////////////////////////////////////


implementation

end.
