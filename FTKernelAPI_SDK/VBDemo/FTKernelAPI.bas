Attribute VB_Name = "FTKernelAPI"
'FTKernelAPI.bas is an declaration for VB.
'
' English Notes:
'
' Copyright @ 2004-2006 p2plib.com All rights reserved.
' MSN: FlashBT@Hotmail.com
' Homepage: http:'www.p2plib.com
'
' FTKernelAPI is a kernel API based on Bittorrent protocol.
'
' Please use and enjoy. Please let me know of any bugs'mods'improvements
' that you have found and I will fix them into this library.
'
' Please visit http:'www.p2plib.com for the detailed information.
'
' ***********************************************************************
' Chinese Notes:
'
' ��Ȩ���� 2004-2006 �������������缼�����޹�˾ ��������Ȩ��. �й�.
' �ٷ���վ: http:'www.p2plib.com'
'
' FTKernelAPI �ǻ���BitTorrentЭ����ں˿�' ������ǿ����չ. ���԰�����
' ���ٵĿ����Լ���P2P���ϵͳ.
'
' FTKernelAPI ����BTЭ���ں˿�' ��Ϊ4���汾:
' 1. ��Ѱ汾' ʹ��������' ֻ֧��һ����������' �޼���֧��
' 2. �����汾' �踶��' ֧�ֶ�����񲢷�' �м���֧��
' 3. �м��汾' �踶��' ֧���Զ���Э��' ���ݼ���' ����ָ��IP' ���ٵȹ���' �м���֧��
' 4. �߼��汾' �踶��' ֧��˳������' ��ý��㲥' �����ص���������' �м���֧��
'
' ��������κδ���'����' ��֪ͨ����' ���ǽ����Ժ�İ汾�кܿ�Ľ���ʵ��.
' ����ϸ��Ϣ������ҵ���վ: http:'www.p2plib.com
'

'�û���ʶ�ĳ���
'length of client identifier
Const IDSIZE = 20

'BitTorrent �ͻ��˰汾��Ϣ����
'bitorrent client version information
Const AGENTSIZE = 64

'���ɵ�SHA��ɢ�еĳ���
'Length of SHA1
Const SHA1_DIGEST_LENGTH = 20

'���������
'Proxytypes
Const PROXYTYPE_NOPROXY = 0
Const PROXYTYPE_SOCKS4 = 1
Const PROXYTYPE_SOCKS4A = 2
Const PROXYTYPE_SOCKS5 = 3
Const PROXYTYPE_HTTP11 = 4

''''''''''''
'����״̬
'Download status
Public Enum enmFTK_Downloader_State
    DLSTATE_NONE = 0
    DLSTATE_ALLOCING = 1
    DLSTATE_CHECKING = 2
    DLSTATE_DOWNLOAD = 3
    DLSTATE_PAUSING = 4
    DLSTATE_CHECKEND = 5
    DLSTATE_FETALERR = 6
    DLSTATE_TERMINATE = 7
End Enum


'����Piece��״̬
'Piece status
Const PIECESTATE_INCOMPLETE = 0
Const PIECESTATE_DOWNLOADING = 1
Const PIECESTATE_COMPLETE = 2

'Port type of Firewall and UPnP
'����Windows����ǽ����UPnPʱ�Ķ˿����Ͷ���
Const WCXT_TCP_PORT = 1
Const WCXT_UDP_PORT = 2

'Declaration for compatible VB6.0 only
Type TwoLong
    LowLong As Long
    HighLong As Long
End Type

Type tagPeerData

    m_dwIP As Long
    m_nPort As Integer
    m_pPeerID(IDSIZE) As Byte

    '-------------------------------------

    m_bIsLocal As Byte
    m_szVersion(AGENTSIZE - 1) As Byte
    m_qwPeerHaveSize As TwoLong
    m_fDownRate As Single
    m_fUpRate As Single
    m_qwDownloaded As TwoLong
    m_qwUploaded As TwoLong
    m_fTimeElapsed As Single
    m_fPeerDownRate As Single
    m_szExtInfo(256 - 1) As Byte
    
End Type

Type tagMiniPeerData

    m_dwIP As Long
    m_nPort As Integer

End Type
  
Type tagAnnounceData

    m_szURL(512 - 1) As Byte
    m_bWorking As Byte
    m_bHeader As Byte
    m_nCount As Long
    m_nFailed As Long
    m_fTimeLeft As Single
    m_fLastTime As Single
    m_szExtInfo(512 - 1) As Byte
    
End Type

Type tagFileInfo

    m_szFileName(512 - 1) As Byte
    m_qwFileSize As TwoLong
    
End Type
  
Type tagErrInfo

    m_szErrInfo(1024 - 1) As Byte
    
End Type


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    
'���屻��֪ͨ�Ļص�����
'Define callback function type
'Declare Function FTK_CALLBACK_FUNC( ByVal nSocket As Int32, ByRef pData As Byte ) As Boolean


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Library version information

'ȡ��ǰ��İ汾��Ϣ, ����: nMajor = 1, nMinor = 1 => ver: 1.1
'Get library major version, example: nMajor = 1, nMinor = 1 => ver: 1.1
Declare Sub FTK_Version_Info Lib "FTKernelAPI" (ByRef nMajor As Long, ByRef nMinor As Long)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Libary License Interface

'Set license key
'����license����Կ
Declare Sub FTK_License_Set Lib "FTKernelAPI" (ByVal lpszLicense As String)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Define yourself protocol identifier string

'Define yourself protocol identifier string(to avoid Router filter)
'�������Լ�������Э���ʶ�����Աܿ�ĳЩ������Ӫ�̵�Э�����
Declare Sub FTK_Protocol_IDS Lib "FTKernelAPI" (ByVal pIDS As String, ByVal bAllowOtherIDS As Boolean)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''Define yourself user identifier

''Define yourself user identifier(read by tracker)
''�����Լ����û���ʶ��Ϣ(Tracker���������Ի�ȡ��)
Declare Sub FTK_Identifier_String10 Lib "FTKernelAPI" (ByVal pS As String)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''Define yourself http tracker "UserAgent"

''Define yourself http tracker "UserAgent"
''�����Լ����ύ��http tracker��httpЭ���е�"UserAgent"
Declare Sub FTK_Http_UserAgent Lib "FTKernelAPI" (ByVal lpszUA As String)
    

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Config INI file interface

'����һ���µ������ļ����
'Create a new Config INI file handle
Declare Function FTK_Config_Open Lib "FTKernelAPI" () As Long

'����һ�����ڵ������ļ����
'Destroy a HConfigIni hanle
Declare Sub FTK_Config_Close Lib "FTKernelAPI" (ByVal hConfigIni As Long)

'�����ַ���ѡ��
'Set string value item
Declare Sub FTK_Config_SetStr Lib "FTKernelAPI" (ByVal hConfigIni As Long, ByVal lpszName As String, ByVal lpszName As String)

'��������ֵѡ��
'Set integer value item
Declare Sub FTK_Config_SetInt Lib "FTKernelAPI" (ByVal hConfigIni As Long, ByVal lpszName As String, ByVal nValue As TwoLong)

'���ø�����ѡ��
'Set float value item
Declare Sub FTK_Config_SetFloat Lib "FTKernelAPI" (ByVal hConfigIni As Long, ByVal lpszName As String, ByVal fValue As Double)

'''''''''''''''''''''''''''''''''''''
'Context interface

'������ʼ��
'Initialize context
'@lpszIniFile: kernel configuration file - INI file
Declare Function FTK_Context_Init Lib "FTKernelAPI" (ByVal lpszIniFile As String, ByVal bLog As Boolean) As Long

'������ʼ��
'Initialize context
'@lpszIniFile: kernel configuration file - INI file
Declare Function FTK_Context_Init2 Lib "FTKernelAPI" (ByVal hConfigIni As Long, ByVal bLog As Boolean) As Long

'���ñ���֪ͨ�Ļص�����
'Set callback funtion pointer
Declare Sub FTK_Context_NotifyCB Lib "FTKernelAPI" (ByVal pfn As Long)

'�ͷ���������
'Release context
Declare Sub FTK_Context_Release Lib "FTKernelAPI" ()

'�����������¼���������
'Context event driver
Declare Function FTK_Context_Run Lib "FTKernelAPI" () As Long

'ǿ���˳�����, ֹͣ����
'��ֹͣʱҪ�˳��������е��߳����Կ���Ҫ��΢�ȴ�
'Stop context event driver
Declare Sub FTK_Context_Stop Lib "FTKernelAPI" ()

'���¸��������ļ��󶨶˿�
'Rebind listen port
Declare Sub FTK_Context_ReBindListenPort Lib "FTKernelAPI" ()

'�ж��Ƿ��Ѿ���ʼ��
'Is context initialized?
Declare Function FTK_Context_IsInit Lib "FTKernelAPI" () As Long

'�Ƿ�����ɹ��˶˿�
'Is context running?
Declare Function FTK_Context_IsRunning Lib "FTKernelAPI" () As Long

'�ж��Ƿ��Ѿ�����
'Return context thread ID
Declare Function FTK_Context_GetThreadID Lib "FTKernelAPI" () As Long

'��ȡ�̵߳�ID
'Return listening port
Declare Function FTK_Context_GetListenPort Lib "FTKernelAPI" () As Integer

'����ָ���˿ڰ󶨲���
'Return binding ip address
Declare Function FTK_Context_GetBindIP Lib "FTKernelAPI" () As String

''�ж��Ƿ�󶨶˿ڲ����ɹ�
''return bind listen port status
Declare Function FTK_Context_IsBindListenPort Lib "FTKernelAPI" () As Boolean


''���ü���ĳЩ�����Ĵ���torrent��ʽ
''Set to open some mistake mistaken TORRENT file
Declare Sub FTK_Context_TorrentFile Lib "FTKernelAPI" (ByVal bValidEOF As Boolean, ByVal bValidSort As Boolean)

''������־�������ļ�
''Set language to write log
Declare Sub FTK_Context_OpenLanguageFile Lib "FTKernelAPI" (ByVal lpszLanguageFile As String)

'''''''''''''''''''''''''''''''''''''
'Downloader interface

'Create a new HDownloader handle
Declare Function FTK_Downloader_Open Lib "FTKernelAPI" () As Long

'Destroy a HDownloader hanle
Declare Sub FTK_Downloader_Close Lib "FTKernelAPI" (ByVal HDownloader As Long)

''��ǰ�ĳ�ʼ��IP���˶���ĺ���(FTK_Downloader_Init* ����֮ǰ����), ����ĳЩ�ε�IP��ַ, "ipfilter.dat" �ļ���eMule(����)����
''Previous Initialize IP filter object to filter some peer's IP, "ipfilter.dat" file is compatiable with eMule.
Declare Function FTK_Downloader_PreInitIPFilter Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal lpszIPFilterFile As String, ByVal nLevel As Long) As Boolean


''��ǰ�ĳ�ʼ��, ���տ���Ⱥ�˳���������(�����ڱ����ر߲��ŵ����)
''Previous Initialize, Tell kernel to sequential download piece
Declare Sub FTK_Downloader_PreInitSEQMode Lib "FTKernelAPI" (ByVal HDownloader As Long)

''Ԥ�ȳ�ʼ���ļ�ѡ�����ص����ȼ���
''�����У�ÿ��Ԫ�ص�ֵ��ʾ: -2:������, -1: ��, 0: һ��, 1:��
''Previous Initialize, Tell kernel to Set priority of file
''-2: no download, -1: low, 0: middle, 1: high
Declare Sub FTK_Downloader_PreInitFilePriority Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal pFilePriority As String, ByVal nFilesCount As Long)

'��ʼ�����ض���
'Initialize a HDownloader
'@lpszTorrentFileName: a torrent file name
'@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
'@nPreAllocFileLen: length of preallocated array
'@bOnlyCheckFile: only verify data of files
'@lpszDestFileName: the downloaded filename
'@lpszConfig: kernel configuration file - INI file
'@lpszLogFileName: output log filename
'@lpszStatusFileName: downloading status filename
'@lpszDesKey: DES-EDE2 password
'@nCodePage: code page of the torrent file
Declare Function FTK_Downloader_Init Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal lpszTorrentFileName As String, ByRef pPreAllocFile As Byte, ByVal nPreAllocFileLen As Long, ByVal bOnlyCheckFile As Long, ByVal lpszDestFileName As String, ByVal lpszConfig As String, ByVal lpszLogFileName As String, ByVal lpszStatusFileName As String, ByVal bQuicklySeed As Boolean, ByVal lpszDesKey As String, ByVal nCodePage As Long) As Long

'Mod by Leo
'��ʼ�����ض���
'Initialize a HDownloader
'@lpszTorrentFileName: a torrent file name
'@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
'@nPreAllocFileLen: length of preallocated array
'@bOnlyCheckFile: only verify data of files
'@lpszDestFileName: the downloaded filename
'@lpszConfig: kernel configuration file - INI file
'@lpszLogFileName: output log filename
'@lpszStatusFileName: downloading status filename
'@lpszDesKey: DES-EDE2 password
'@nCodePage: code page of the torrent file
Declare Function FTK_Downloader_Init2 Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal lpszTorrentFileName As String, ByRef pPreAllocFile As Byte, ByVal nPreAllocFileLen As Long, ByVal bOnlyCheckFile As Long, ByVal lpszDestFileName As String, ByVal hConfigIni As Long, ByVal lpszLogFileName As String, ByVal lpszStatusFileName As String, ByVal bQuickySeed As Boolean, ByVal lpszDesKey As String, ByVal nCodePage As Long) As Long

''��ʼ�����ض���3
''Initialize a HDownloader
''@pData: a torrent binary object, a pointer to a binary torrent file content
''@nLength: the length of a torrent binary object
''@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
''@nPreAllocFileLen: length of preallocated array
''@bOnlyCheckFile: only verify data of files
''@lpszDestFileName: the downloaded filename
''@lpszConfig: kernel configuration file - INI file
''@lpszLogFileName: output log filename
''@lpszStatusFileName: downloading status filename
''@lpszDesKey: DES-EDE2 password
''@nCodePage: code page of the torrent file
Declare Function FTK_Downloader_Init3 Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pData As Byte, ByVal nLength As Long, ByRef pPreAllocFile As Byte, ByVal nPreAllocFileLen As Long, ByVal bOnlyCheckFile As Long, ByVal lpszDestFileName As String, ByVal lpszConfig As String, ByVal lpszLogFileName As String, ByVal lpszStatusFileName As String, ByVal bQuicklySeed As Boolean, ByVal lpszDesKey As String, ByVal nCodePage As Long) As Long

''��ʼ�����ض���4
''Initialize a HDownloader
''@pData: a torrent binary object, a pointer to a binary torrent file content
''@nLength: the length of a torrent binary object
''@pPreAllocFile: a array of preallocated files, 0->no, 1->yes
''@nPreAllocFileLen: length of preallocated array
''@bOnlyCheckFile: only verify data of files
''@lpszDestFileName: the downloaded filename
''@hConfigIni: kernel configuration file handle - INI file
''@lpszLogFileName: output log filename
''@lpszStatusFileName: downloading status filename
''@lpszDesKey: DES-EDE2 password
''@nCodePage: code page of the torrent file
Declare Function FTK_Downloader_Init4 Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pData As Byte, ByVal nLength As Long, ByRef pPreAllocFile As Byte, ByVal nPreAllocFileLen As Long, ByVal bOnlyCheckFile As Long, ByVal lpszDestFileName As String, ByVal hConfig As Long, ByVal lpszLogFileName As String, ByVal lpszStatusFileName As String, ByVal bQuicklySeed As Boolean, ByVal lpszDesKey As String, ByVal nCodePage As Long) As Long

'�ͷ����ض���
'Release downloader handle
Declare Function FTK_Downloader_Release Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'ִ�������߳�
'Execute downloader
Declare Function FTK_Downloader_Execute Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ͣ����
'Pause downloader
Declare Sub FTK_Downloader_Pause Lib "FTKernelAPI" (ByVal HDownloader As Long)

'�ָ�����
'Resume downloader
Declare Sub FTK_Downloader_Resume Lib "FTKernelAPI" (ByVal HDownloader As Long)

'�Ƿ��Ѿ���ʼ��
'Is downloader intialized?
Declare Function FTK_Downloader_IsInit Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ȡ��������Ŀǰ�Ľ׶�״̬
'Return downloader state
Declare Function FTK_Downloader_GetState Lib "FTKernelAPI" (ByVal HDownloader As Long) As enmFTK_Downloader_State

'�Ƿ�ֻ�ǽ����ļ����
'Only checking file, don't downloading...
Declare Function FTK_Downloader_IsOnlyCheckFile Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'�Ƿ��Ѿ���������� Lib "FTKernelAPI"(�ж�ѡ���ļ�����)
'Is all selected files finished?
Declare Function FTK_Downloader_IsFinished Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'�Ƿ��Ѿ���������� Lib "FTKernelAPI"(ȫ������)
'Is all files finished?
Declare Function FTK_Downloader_IsAllFinished Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'����ָ����Peer
'Add external source peer
Declare Sub FTK_Downloader_AddSource Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal pchIP As String, ByVal nPort As Integer, ByRef pPeerID As Byte)

''����ָ����User
''Add external source peer(socket handle)
Declare Sub FTK_Downloader_AddSourceExt Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal nSocket As Long)

'�ⲿ��̬���Ӹ�����Announce
'Add external announce
Declare Sub FTK_Downloader_AddExtAnnounce Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal lpszAnnounce As String)

'�ֶ�����Announce���Ͻ�������
'Reannounce manually
Declare Sub FTK_Downloader_ReannounceAll Lib "FTKernelAPI" (ByVal HDownloader As Long)

'Leo Mod: 2005-10-16
'���տ���Ⱥ�˳���������(�����ڱ����ر߲��ŵ����)
'Tell kernel to sequential download piece
Declare Sub FTK_Downloader_SetSeqPicker Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal bSeq As Long)

'���������ļ������ȼ���
' -2:������, -1: ��, 0: һ��, 1:��
'Set priority of file
'-2: no download, -1: low, 0: middle, 1: high
Declare Sub FTK_Downloader_SetFilePriority Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal nIndex As Long, ByVal chPriority As Byte, ByVal bDoPriority As Long)

'ǿ���������½��ļ������ȼ���ֵ��Piece
'Force to set priority of all piece immediately
Declare Sub FTK_Downloader_ForceFilePriority Lib "FTKernelAPI" (ByVal HDownloader As Long)

'�ⲿ����, �ֶ������������������� Lib "FTKernelAPI"(0.0��ʾû������)
'Set fixed max download rate
Declare Sub FTK_Downloader_SetFixMaxDownloadRate Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal fMaxDownloadRate As Double)

'�ⲿ����, ��ȡ�ֶ�������������������(0.0��ʾû������)
'Get fixed max download rate
Declare Function FTK_Downloader_GetFixMaxDownloadRate Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double


'�ⲿ����, �ֶ����������ϴ������� Lib "FTKernelAPI"(0.0��ʾû������)
'Set fixed max upload rate
Declare Sub FTK_Downloader_SetFixMaxUploadRate Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal fMaxUploadRate As Double)

'�ⲿ����, ��ȡ�ֶ����������ϴ�������(0.0��ʾû������)
'Get fixed max upload rate
Declare Function FTK_Downloader_GetFixMaxUploadRate Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'��������ĳЩ�ض������ӷ�����(SEED), ���Լ��������ϴ���(0��ʾû������, ע�ⵥλ��: KB)
'Set fixed max upload rate of SOME CERTAIN SEED to me, 0 means no limit, UNIT is KB
Declare Sub FTK_Downloader_SetSeedMaxUPSpeed Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal nSpeed As Integer)

'���������ڣ���ֹĳ��IP������, ֻ�ڵ�ǰ��������ڼ���Ч
'Ban IP for X seconds, ONLY for the current active HDownloader
Declare Sub FTK_Downloader_BanPeerIP Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal lpszIP As String, ByVal nBannedSeconds As Long)


'��ȡ�̵߳�ID
'Get thread ID
Declare Function FTK_Downloader_GetThreadID Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'''''''''''''''''''''''''''''''''''''
'ȫ�ֲ�������
'Global settings

'��ĳ��Torrent�ļ���SHA1ֵ�������
'Add torrent into SHA1 list
Declare Sub FTK_GlobalVar_AddTorrentSHA1 Lib "FTKernelAPI" (ByVal lpszSHA As String, ByVal HDownloader As Long)

'��ĳ��Torrent�ļ���SHA1ֵ�Ӷ�����ɾ��
'Remove torrent from SHA1 list
Declare Sub FTK_GlobalVar_RemoveTorrentSHA1 Lib "FTKernelAPI" (ByVal lpszSHA As String)

'''''''''''''''''''''''''''''''''''''
'��������������б�
'Proxy interface

'���ý�������Trackerʱʹ�ô��������
'Only tracker using proxy settings
Declare Sub FTK_Proxy_SetOnlyTracker Lib "FTKernelAPI" (ByVal bOnlyTracker As Long)

'��յ�ǰ�Ĵ�����Ϣ Lib "FTKernelAPI"(������PROXYTYPE_NOPROXY)
'Only PROXYTYPE_NOPROXY
Declare Sub FTK_Proxy_SetType Lib "FTKernelAPI" (ByVal nProxyType As Long)

'���ô��� Lib "FTKernelAPI"(������PROXYTYPE_NOPROXY)
'May not be PROXYTYPE_NOPROXY
Declare Sub FTK_Proxy_SetProxy Lib "FTKernelAPI" (ByVal nProxyType As Long, ByVal pProxyHost As String, ByVal ProxyPort As Long)

'����SOCKS5��HTTP1.1��Ҫ��֤��Ϣ�Ĵ���
'Only SOCKS5 and HTTP1.1 proxies
Declare Sub FTK_Proxy_SetAuthProxy Lib "FTKernelAPI" (ByVal nProxyType As Long, ByVal pProxyHost As String, ByVal ProxyPort As Long, ByVal pProxyUser As String, ByVal pProxyPass As String)

'��ȡ���������
'Return proxy Type
Declare Function FTK_Proxy_GetProxyType Lib "FTKernelAPI" () As Long

'''''''''''''''''''''''''''''''''''''
'Downloader statistic information interface

'��ȡ�ܹ��Ѿ����� Lib "FTKernelAPI"(��֤�ɹ�)������
'Get the size of having received data for all file
Declare Function FTK_Stat_GetTotalFileHaveSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'��ȡѡ���Ѿ����� Lib "FTKernelAPI"(��֤�ɹ�)������
'Get the size of having received data for a file
Declare Function FTK_Stat_GetSelectedFileHaveSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'Leo Mod: 2005-10-16
'��ȡ�Ѿ�˳�����ص�Ŀǰ���Դ�ͷ��ʼ���ŵ����ݳ���
'Get the size of sequential piece from file front
Declare Function FTK_Stat_GetStartSeqFileSize Lib "FTKernelAPI" (HDownloader As Long) As TwoLong

'��ȡ���һ�����ص��ֽ���
'Get the size of lasted receiving data
Declare Function FTK_Stat_GetLastDataSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ȡ�ܹ��������ֽ���
'Get the size of bad data
Declare Function FTK_Stat_GetBadDataSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'��ǰ�ܹ������ӵĸ���
'Get the number of total peer
Declare Function FTK_Stat_GetTotalPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ǰ�������ӵĸ���
'Get the number of active peer
Declare Function FTK_Stat_GetActivePeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ǰ�ı������ӵĸ���
'Get the number of passive peer
Declare Function FTK_Stat_GetPassivePeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ǰ���������еĸ���
'Get number of connecting peer
Declare Function FTK_Stat_GetConnectingPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ȡ�Ѿ����ӵ����ӵĸ���
'Get number of seed
Declare Function FTK_Stat_GetSeedCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ȡ�����ϴ������ӵĸ���
'Get the number of uploading peer
Declare Function FTK_Stat_GetUploadPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ȡ�������ص����ӵĸ���
'Get the number of downloading peer
Declare Function FTK_Stat_GetDownloadPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ȡ�ܹ����Ի�ȡ��Seed�ĸ���
'Get the number of total available seed
Declare Function FTK_Stat_GetTotalAvailSeedCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ȡ�ܹ����Ի�ȡ��Peer�ĸ���
'Get the number of peer
Declare Function FTK_Stat_GetTotalAvailPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'�ɵ����ӵĸ���
'Get old seed number
Declare Function FTK_Stat_GetOldSeedPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'���������Ѿ����ص����ݳ���
'Get downloaded bytes
Declare Function FTK_Stat_GetDownloaded Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'���������Ѿ��ϴ������ݳ���
'Get uploaded bytes
Declare Function FTK_Stat_GetUploaded Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'�����Ѿ�����ʱ�� Lib "FTKernelAPI"(����ʱ�䲻ͬ������ʱ��)
'Get total running time
Declare Function FTK_Stat_GetRunningTime Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'�������ص�ʱ�� Lib "FTKernelAPI"(���������, ������ʱ����ԶΪ0)
'Get total downloaded time
Declare Function FTK_Stat_GetDownloadTime Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'��������ʣ���ʱ��, ���������ʼ���
'Get the left time to download
Declare Function FTK_Stat_GetLeftTime Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'��ȡ��ǰ���ϴ���
'Get upload rate
Declare Function FTK_Stat_GetUploadRate Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'��ȡ��ǰ��������
'Get downloading rate
Declare Function FTK_Stat_GetDownloadRate Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'��ȡָ����Piece�����ؽ���
'Get the progress of a piece
Declare Sub FTK_Stat_GetPieceState Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pPiece As Byte, ByVal nCount As Long)

'��ȡ����ļ��Ľ���
'Get the progress of cheching piece
Declare Function FTK_Stat_GetCheckPieceSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'��ȡ����Piece�ĸ���
'Get number of checked piece
Declare Function FTK_Stat_GetCheckPieceCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ȡ�Ѿ�����ռ�Ĵ�С
'Get the size of allocated file
Declare Function FTK_Stat_GetAllocSpaceSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'��ȡ��ǰ�Ľ�����
'Get healthy rate
Declare Function FTK_Stat_GetHealthRate Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'��ȡ��ǰ����󻺴��С
'Get the size of max cache
Declare Function FTK_Stat_GetMaxCacheSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ȡ�Ѿ�ʹ�õĻ����С
'Get the size of used cache
Declare Function FTK_Stat_GetUseCacheSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'��ȡ����дӲ�̵��ܵĴ���
'Get writed disk count
Declare Function FTK_Stat_GetWriteDiskCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'��ȡ��������дӲ�̵Ĵ���
'Get really writed disk count
Declare Function FTK_Stat_GetRealWriteDiskCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'��ȡ���ζ�Ӳ�̵��ܵĴ���
'Get readed disk count
Declare Function FTK_Stat_GetReadDiskCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'��ȡ����������Ӳ�̵Ĵ���
'Get really readed disk count
Declare Function FTK_Stat_GetRealReadDiskCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'��ȡдӲ�̵�Ƶ�� Lib "FTKernelAPI"(��'��)
'Get writing disk frenqence Lib "FTKernelAPI"(number'second)
Declare Function FTK_Stat_GetWriteDiskFrenq Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'��ȡ����дӲ�̵�Ƶ�� Lib "FTKernelAPI"(��'��)
'Get really writing disk frenqence Lib "FTKernelAPI"(number'second)
Declare Function FTK_Stat_GetRealWriteDiskFrenq Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'��ȡ��Ӳ�̵�Ƶ�� Lib "FTKernelAPI"(��'��)
'Get reading disk frenqence Lib "FTKernelAPI"(number'second)
Declare Function FTK_Stat_GetReadDiskFrenq Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'��ȡ������Ӳ�̵�Ƶ�� Lib "FTKernelAPI"(��'��)
'Get really reading disk frenqence Lib "FTKernelAPI"(number'second)
Declare Function FTK_Stat_GetRealReadDiskFrenq Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'��ȡ��ǰ��־�ļ���·��+����
'Get log file name
Declare Sub FTK_Stat_GetLogPathFileName Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal lpszFileName As String)

'��ȡָ�����ļ��Ľ���
'Get the progress of a file
Declare Function FTK_Stat_GetFileHaveSize Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal nIndex As Long) As TwoLong

'��ȡ��ǰ�û�״̬��Ϣ���б�
'Get the peers information
Declare Sub FTK_Stat_GetPeerData Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pData As tagPeerData, ByRef nRetCount As Long, ByVal nMaxCount As Long)

'��ȡ��ǰ�����û�״̬��Ϣ���б�
'Get the some peers information
Declare Sub FTK_Stat_GetPeerRangeData Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pData As tagPeerData, ByVal nFrom As Long, ByVal nTo As Long, ByRef nRetCount As Long, ByVal nMaxCount As Long, ByVal bExtInfo As Boolean)


'��ȡ��ǰ�û�״̬��Ϣ���б� Lib "FTKernelAPI"(ֻ��ȡIP�Ͷ˿�)
'Get the peers information Lib "FTKernelAPI"(only IP and port)
Declare Sub FTK_Stat_GetMiniPeerData Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pData As tagMiniPeerData, ByRef nRetCount As Long, ByVal nMaxCount As Long)

'��ȡ��ǰAnnounce״̬��Ϣ���б�
'Get the status of announces
Declare Sub FTK_Stat_GetAnnounceData Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pData As tagAnnounceData, ByRef nRetCount As Long, ByVal nMaxCount As Long)

''��ȡ��ǰ����ĵ�����Ϣ
''Get the debug information of downloader
Declare Function FTK_Stat_GetBTDownloaderInfo Lib "FTKernelAPI" (ByVal HDownloader As Long) As String

'''''''''''''''''''''''''''''''''''''
'��Torrent�ļ���ȡ��Ϣ�ĺ����б�
'Torrent file interface

'�ж��ǲ����Լ�����ļ��ܵ�Torrent�ļ�
'Return boolean, tell us is a cipher torrent file
Declare Function FTK_Torrent_IsCipherTorrent Lib "FTKernelAPI" (ByVal lpszFileName As String) As Long

'ִ�д��ļ��ж�ȡ���ݲ���ʼ���������
'Open a torrent file handle
Declare Function FTK_Torrent_Open Lib "FTKernelAPI" (ByVal lpszFileName As String, ByVal nCodePage As Long, ByVal lpszDesKey As String, ByVal bValidEOF As Boolean, ByVal bValidSort As Boolean) As Long

''ִ�д��ļ��ж�ȡ���ݲ���ʼ���������, ���ʧ��, ���ش�����Ϣ
''Open a torrent file handle, if failed, return error information
Declare Function FTK_Torrent_SafeOpen Lib "FTKernelAPI" (ByVal lpszFileName As String, ByVal nCodePage As Long, ByVal lpszDesKey As String, ByVal bValidEOF As Boolean, ByVal bValidSort As Boolean, ByRef pErrInfo As tagErrInfo) As Long

''�ж��ǲ����Լ�����ļ��ܵ�Torrent����������
''Return boolean, tell us is a cipher torrent binary data
Declare Function FTK_Torrent_IsCipherTorrentObj Lib "FTKernelAPI" (ByRef pData As Byte, ByVal nLength As Long) As Boolean

''ִ�д�Torrent binary object�ж�ȡ���ݲ���ʼ���������
''Open a torrent binary object
Declare Function FTK_Torrent_OpenObj Lib "FTKernelAPI" (ByRef pData As Byte, ByVal nLength As Long, ByVal nCodePage As Long, ByVal lpszDesKey As String, ByVal bValidEOF As Boolean, ByVal bValidSort As Boolean, ByRef pErrInfo As tagErrInfo) As Long

'�رյ�ǰ�򿪵�Torrent�ļ�
'Close Torrent file handle
Declare Sub FTK_Torrent_Close Lib "FTKernelAPI" (ByVal hTorrentFile As Long)

'�ж���Ŀ¼�����ļ�
'Return boolean, tell us is only a single file in torrent
Declare Function FTK_Torrent_IsFile Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'��ȡ Torrent ����
'Get the name of torrent file
Declare Function FTK_Torrent_GetTorrentName Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As String

'��ȡtorrent�е��ļ��ĸ��� Lib "FTKernelAPI"(����һ��)
'Get total number of files
Declare Function FTK_Torrent_GetFilesCount Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'��ȡtorrent�е��ļ��б� Lib "FTKernelAPI"(����һ��)
'Get a pointer to file list
Declare Sub FTK_Torrent_GetFiles Lib "FTKernelAPI" (ByVal hTorrentFile As Long, ByRef pFileInfo As tagFileInfo)

'��ȡtorrent�е��ļ��б��е�ĳ���ļ�����Ϣ
'Get a pointer to a file of file list
Declare Sub FTK_Torrent_GetFileInfo Lib "FTKernelAPI" (ByVal hTorrentFile As Long, ByVal nIndex As Long, ByRef pFileInfo As tagFileInfo)

'��ȡInfo��Hashֵ, �ڲ�ʹ��
'Get the binary info hash of torrent file
Declare Function FTK_Torrent_GetInfoHash Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'��ȡinfo��Hashֵ, ʮ������
'Get the hex encoding info hash of torrent file
Declare Function FTK_Torrent_GetHexInfoHash Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As String

'��ȡ main annouce url
'Get mainb announce url
Declare Function FTK_Torrent_GetMainAnnounce Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As String

'��ȡ Announce ����ĸ���
'Get the number of all announce list
Declare Function FTK_Torrent_GetAnnouncesCount Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'��ȡָ���� Announce ���������Announce�ĸ���
'Get the size of a announce list
Declare Function FTK_Torrent_GetAnnounceSize Lib "FTKernelAPI" (ByVal hTorrentFile As Long, ByVal nGroupIndex As Long) As Long

'��ȡָ���� Announce ������ָ��λ�õ�Announce
'Get a annoucne of a announce list
Declare Function FTK_Torrent_GetAnnouncesVal Lib "FTKernelAPI" (ByVal hTorrentFile As Long, ByVal nGroupIndex As Long, ByVal nIndex As Long) As String

'��ȡ ע��
'Get the comments
Declare Function FTK_Torrent_GetComments Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As String

'��ȡ Torrent ����ʱ��
'Get the creation time of torrent file
Declare Function FTK_Torrent_GetCreateTime Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'��ȡpiece��Ĵ�С
'Get the size of piece
Declare Function FTK_Torrent_GetPieceSize Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'��ȡ�ļ��Ĵ�С
'Get the total file size to transfer
Declare Function FTK_Torrent_GetFileSize Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As TwoLong

'Piece��ĸ���
'Get the total number of piece
Declare Function FTK_Torrent_GetPieceCount Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'��ȡPiece Hash ���б�
'Get a pointer to piece hash list
Declare Function FTK_Torrent_GetPieceHashList Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'�ͷ�PieceHash�б�
'Release piece hash memory
Declare Sub FTK_Torrent_FreePieceHashList Lib "FTKernelAPI" (ByVal hTorrentFile As Long)

'��ȡTorrent�ļ������Ա���
'Get language code page of torrent file
Declare Sub FTK_Torrent_GetLanCodePage Lib "FTKernelAPI" (ByVal hTorrentFile As Long)

'''''''''''''''''''''''''''''''''''''
'����Torrent�ļ��ĺ����б�
'Create torrent file interface

'��һ������torrent�ļ��ľ��
'Open a making torrent handle
Declare Function FTK_MT_Open Lib "FTKernelAPI" () As Long

'�رմ򿪵�����Torrent�ļ��ľ��
'Close a making torrent handle
Declare Sub FTK_MT_Close Lib "FTKernelAPI" (ByVal hMakeTorrent As Long)

'ִ�����ɶ���Ĳ���
'Start to making torrent file
Declare Function FTK_MT_MakeTorrent Lib "FTKernelAPI" (ByVal hMakeTorrent As Long) As Long

'ֹͣTorrent�ļ�����
'Stop making torrent file
Declare Sub FTK_MT_StopMake Lib "FTKernelAPI" (ByVal hMakeTorrent As Long)

'��ȡ�����ļ��Ľ���
'Get progress of making torrent file
Declare Function FTK_MT_GetMTProgress Lib "FTKernelAPI" (ByVal hMakeTorrent As Long) As Double

'���ΪTorrent�ļ�
'Save as a torrent file
Declare Function FTK_MT_SaveAsTorrentFile Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszFileName As String, ByVal lpszDesKey As String) As Long

'���� annouce url
'Set a main announce url
Declare Sub FTK_MT_SetAnnounceUrl Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszValue As String)

'��Ӷ����Announce �б�
'Add a announce list
Declare Sub FTK_MT_AddAnnounceList Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByRef Announces As String, ByVal nCount As Long)

'��Ӷ����Announce �б�, example: announce1;announce2;announce3;
'Add a announce list, example: announce1;announce2;announce3;
Declare Sub FTK_MT_AddAnnounceList2 Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszValue As String)

'��ն����Announce �б�
'Clear all announce list
Declare Sub FTK_MT_ClearAnnounceList Lib "FTKernelAPI" (ByVal hMakeTorrent As Long)

'���� ע��
'Set comments
Declare Sub FTK_MT_SetComments Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszValue As String)

'����piece��Ĵ�С
'Set piece size to making torrent file
Declare Sub FTK_MT_SetPieceSize Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal dwPieceSize As Long)

'����torrent�е��ļ�
'Set the sourece file to making torrent file
Declare Sub FTK_MT_SetFile Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszFileName As String)

'����torrent�е��ļ�Ŀ¼ Lib "FTKernelAPI"(����ļ�)
'Set the source path to making torrent file
Declare Sub FTK_MT_SetPath Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszPathName As String)

'����Torrent�ļ������Դ��� Lib "FTKernelAPI"(ֻ���ļ�����, ע�͵���Ч)
'Set language code of torrent file
Declare Sub FTK_MT_SetLangCodePage Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal nCodePage As Long)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''Tracker interface, to get status of one torrent from tracker: peer count'seed count

''HTTP tracker�ӿڣ� ���ڻ�ȡhttp Trackerĳ�����״̬��Ϣ
''HTTP Tracker interface, to get status of one torrent from http tracker
Declare Function FTK_Tracker_Http1 Lib "FTKernelAPI" (ByVal lpszTracker As String, ByVal pInfoHash As String, ByVal qwFileSize As TwoLong, ByRef nPeerCount As Long, ByRef nSeedCount As Long, ByRef bNetwordErr As Boolean, ByVal lpszErrInfo As String, ByVal nLength As Long) As Boolean


''HTTP tracker�ӿڣ� ���ڻ�ȡhttp Trackerĳ�����״̬��Ϣ
''HTTP Tracker interface, to get status of one torrent from http tracker
Declare Function FTK_Tracker_Http2 Lib "FTKernelAPI" (ByVal lpszTorrentFileName As String, ByRef nPeerCount As Long, ByRef nSeedCount As Long, ByRef bNetwordErr As Boolean, ByVal lpszErrInfo As String, ByVal nLength As Long) As Boolean

''UDP tracker�ӿڣ� ���ڻ�ȡUDP Trackerĳ�����״̬��Ϣ
''UDP Tracker interface, to get status of one torrent from UDP tracker
Declare Function FTK_Tracker_UDP1 Lib "FTKernelAPI" (ByVal lpszTracker As String, ByVal pInfoHash As String, ByVal qwFileSize As TwoLong, ByRef nPeerCount As Long, ByRef nSeedCount As Long, ByRef bNetwordErr As Boolean, ByVal lpszErrInfo As String, ByVal nLength As Long) As Boolean

''UDP tracker�ӿڣ� ���ڻ�ȡUDP Trackerĳ�����״̬��Ϣ
''UDP Tracker interface, to get status of one torrent from UDP tracker
Declare Function FTK_Tracker_UDP2 Lib "FTKernelAPI" (ByVal lpszTorrentFileName As String, ByRef nPeerCount As Long, ByRef nSeedCount As Long, ByRef bNetwordErr As Boolean, ByVal lpszErrInfo As String, ByVal nLength As Long) As Boolean
    

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Disk cache Settings

'Set Disk cache size
'���ô��̻���Ĵ�С
Declare Sub FTK_Disk_SetCache Lib "FTKernelAPI" (ByVal nMinCacheSize As Long, ByVal nMaxCacheSize As Long, ByVal nPhyMemorySize As Long)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''Windows environment related interfaces

''Get local machine ip address(get the first ip or best ip if there are more than one NICs)
''��ȡ������IP��ַ(���ж��������£�ѡ���һ�������߰���һ���㷨ѡ������ʵ�һ��)
Declare Function FTK_Win_GetLocalIP Lib "FTKernelAPI" (ByRef bPrivateIP As Boolean) As String

''Open Windows ICS'ICF(Windows XP'Windows 2003)
''�򿪲���ϵͳ���������ӷ���ǽ���������ӹ���(Windows XP'Windows 2003)
Declare Sub FTK_Win_OpenWinXPICSF Lib "FTKernelAPI" (ByVal nPort As Integer, ByRef bOpenFirewall As Boolean, ByRef bPortMapping As Boolean, ByVal nProtocol As Byte, ByVal lpszIP As String, ByVal lpszAppName As String)

''Open UPnP port mapping(Win9x'WinME'Win2000'WinXP'Win2003)
''ִ�ж���֧��UPnPЭ���Router�����Զ��Ķ˿�ӳ������(��������Router��Ļ�������)
Declare Function FTK_Win_AddUPnPPortMapping Lib "FTKernelAPI" (ByVal nPort As Integer, ByVal nProtocol As Byte, ByVal lpszIP As String) As Boolean

''Patch Windows XP SP2 tcpip.sys file for best TCP'IP performance
''����Windows XP SP2 ��tcpip.sys�򲹶����ƽ������������ƣ������������
Declare Function FTK_Win_PacthSP2TCPIPLimitFile Lib "FTKernelAPI" (nLimit As Long) As Long

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Other Functions, to convert from TwoLong to Double
'������������ת���ĺ���, ���Զ����TwoLong����ת��ΪDouble����
Public Function GetDoubleFromTwoLong(ByRef twLong As TwoLong) As Double
    Dim dbValue As Double
    dbValue = IIf(twLong.HighLong < 0, 4294967296# + twLong.HighLong, twLong.HighLong)
    dbValue = dbValue * 4294967296#
    dbValue = dbValue + IIf(twLong.LowLong < 0, 4294967296# + twLong.LowLong, twLong.LowLong)
    GetDoubleFromTwoLong = dbValue
End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
