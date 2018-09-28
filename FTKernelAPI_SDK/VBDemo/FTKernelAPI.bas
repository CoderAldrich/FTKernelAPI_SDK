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
' 版权所有 2004-2006 北京惠软畅联网络技术有限公司 保留所有权利. 中国.
' 官方网站: http:'www.p2plib.com'
'
' FTKernelAPI 是基于BitTorrent协议的内核库' 并做了强大扩展. 可以帮助您
' 快速的开发自己的P2P软件系统.
'
' FTKernelAPI 兼容BT协议内核库' 分为4个版本:
' 1. 免费版本' 使用受限制' 只支持一个并发任务' 无技术支持
' 2. 初级版本' 需付费' 支持多个任务并发' 有技术支持
' 3. 中级版本' 需付费' 支持自定义协议' 数据加密' 封锁指定IP' 限速等功能' 有技术支持
' 4. 高级版本' 需付费' 支持顺序下载' 流媒体点播' 被动回调加载任务' 有技术支持
'
' 如果发现任何错误'建议' 请通知我们' 我们将在以后的版本中很快改进和实现.
' 更详细信息请访问我的网站: http:'www.p2plib.com
'

'用户标识的长度
'length of client identifier
Const IDSIZE = 20

'BitTorrent 客户端版本信息长度
'bitorrent client version information
Const AGENTSIZE = 64

'生成的SHA的散列的长度
'Length of SHA1
Const SHA1_DIGEST_LENGTH = 20

'代理的类型
'Proxytypes
Const PROXYTYPE_NOPROXY = 0
Const PROXYTYPE_SOCKS4 = 1
Const PROXYTYPE_SOCKS4A = 2
Const PROXYTYPE_SOCKS5 = 3
Const PROXYTYPE_HTTP11 = 4

''''''''''''
'下载状态
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


'定义Piece的状态
'Piece status
Const PIECESTATE_INCOMPLETE = 0
Const PIECESTATE_DOWNLOADING = 1
Const PIECESTATE_COMPLETE = 2

'Port type of Firewall and UPnP
'操做Windows防火墙或者UPnP时的端口类型定义
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
    
'定义被动通知的回调函数
'Define callback function type
'Declare Function FTK_CALLBACK_FUNC( ByVal nSocket As Int32, ByRef pData As Byte ) As Boolean


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Library version information

'取当前库的版本信息, 例如: nMajor = 1, nMinor = 1 => ver: 1.1
'Get library major version, example: nMajor = 1, nMinor = 1 => ver: 1.1
Declare Sub FTK_Version_Info Lib "FTKernelAPI" (ByRef nMajor As Long, ByRef nMinor As Long)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Libary License Interface

'Set license key
'设置license的密钥
Declare Sub FTK_License_Set Lib "FTKernelAPI" (ByVal lpszLicense As String)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Define yourself protocol identifier string

'Define yourself protocol identifier string(to avoid Router filter)
'定义你自己的网络协议标识，可以避开某些网络运营商的协议封锁
Declare Sub FTK_Protocol_IDS Lib "FTKernelAPI" (ByVal pIDS As String, ByVal bAllowOtherIDS As Boolean)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''Define yourself user identifier

''Define yourself user identifier(read by tracker)
''定义自己的用户标识信息(Tracker服务器可以获取到)
Declare Sub FTK_Identifier_String10 Lib "FTKernelAPI" (ByVal pS As String)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''Define yourself http tracker "UserAgent"

''Define yourself http tracker "UserAgent"
''定义自己的提交给http tracker的http协议中的"UserAgent"
Declare Sub FTK_Http_UserAgent Lib "FTKernelAPI" (ByVal lpszUA As String)
    

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Config INI file interface

'创建一个新的配置文件句柄
'Create a new Config INI file handle
Declare Function FTK_Config_Open Lib "FTKernelAPI" () As Long

'销毁一个存在的配置文件句柄
'Destroy a HConfigIni hanle
Declare Sub FTK_Config_Close Lib "FTKernelAPI" (ByVal hConfigIni As Long)

'设置字符串选项
'Set string value item
Declare Sub FTK_Config_SetStr Lib "FTKernelAPI" (ByVal hConfigIni As Long, ByVal lpszName As String, ByVal lpszName As String)

'设置整型值选项
'Set integer value item
Declare Sub FTK_Config_SetInt Lib "FTKernelAPI" (ByVal hConfigIni As Long, ByVal lpszName As String, ByVal nValue As TwoLong)

'设置浮点型选项
'Set float value item
Declare Sub FTK_Config_SetFloat Lib "FTKernelAPI" (ByVal hConfigIni As Long, ByVal lpszName As String, ByVal fValue As Double)

'''''''''''''''''''''''''''''''''''''
'Context interface

'环境初始化
'Initialize context
'@lpszIniFile: kernel configuration file - INI file
Declare Function FTK_Context_Init Lib "FTKernelAPI" (ByVal lpszIniFile As String, ByVal bLog As Boolean) As Long

'环境初始化
'Initialize context
'@lpszIniFile: kernel configuration file - INI file
Declare Function FTK_Context_Init2 Lib "FTKernelAPI" (ByVal hConfigIni As Long, ByVal bLog As Boolean) As Long

'设置被动通知的回调函数
'Set callback funtion pointer
Declare Sub FTK_Context_NotifyCB Lib "FTKernelAPI" (ByVal pfn As Long)

'释放整个环境
'Release context
Declare Sub FTK_Context_Release Lib "FTKernelAPI" ()

'整个环境的事件驱动引擎
'Context event driver
Declare Function FTK_Context_Run Lib "FTKernelAPI" () As Long

'强迫退出环境, 停止运行
'在停止时要退出正在运行的线程所以可能要稍微等待
'Stop context event driver
Declare Sub FTK_Context_Stop Lib "FTKernelAPI" ()

'重新根据配置文件绑定端口
'Rebind listen port
Declare Sub FTK_Context_ReBindListenPort Lib "FTKernelAPI" ()

'判断是否已经初始化
'Is context initialized?
Declare Function FTK_Context_IsInit Lib "FTKernelAPI" () As Long

'是否监听成功了端口
'Is context running?
Declare Function FTK_Context_IsRunning Lib "FTKernelAPI" () As Long

'判断是否已经运行
'Return context thread ID
Declare Function FTK_Context_GetThreadID Lib "FTKernelAPI" () As Long

'获取线程的ID
'Return listening port
Declare Function FTK_Context_GetListenPort Lib "FTKernelAPI" () As Integer

'重新指定端口绑定操作
'Return binding ip address
Declare Function FTK_Context_GetBindIP Lib "FTKernelAPI" () As String

''判断是否绑定端口操作成功
''return bind listen port status
Declare Function FTK_Context_IsBindListenPort Lib "FTKernelAPI" () As Boolean


''设置兼容某些常见的错误torrent格式
''Set to open some mistake mistaken TORRENT file
Declare Sub FTK_Context_TorrentFile Lib "FTKernelAPI" (ByVal bValidEOF As Boolean, ByVal bValidSort As Boolean)

''设置日志的语言文件
''Set language to write log
Declare Sub FTK_Context_OpenLanguageFile Lib "FTKernelAPI" (ByVal lpszLanguageFile As String)

'''''''''''''''''''''''''''''''''''''
'Downloader interface

'Create a new HDownloader handle
Declare Function FTK_Downloader_Open Lib "FTKernelAPI" () As Long

'Destroy a HDownloader hanle
Declare Sub FTK_Downloader_Close Lib "FTKernelAPI" (ByVal HDownloader As Long)

''提前的初始化IP过滤对象的函数(FTK_Downloader_Init* 函数之前调用), 过滤某些段的IP地址, "ipfilter.dat" 文件和eMule(电骡)兼容
''Previous Initialize IP filter object to filter some peer's IP, "ipfilter.dat" file is compatiable with eMule.
Declare Function FTK_Downloader_PreInitIPFilter Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal lpszIPFilterFile As String, ByVal nLevel As Long) As Boolean


''提前的初始化, 按照块的先后顺序进行下载(适用于边下载边播放的情况)
''Previous Initialize, Tell kernel to sequential download piece
Declare Sub FTK_Downloader_PreInitSEQMode Lib "FTKernelAPI" (ByVal HDownloader As Long)

''预先初始化文件选择下载的优先级别
''数组中，每个元素的值表示: -2:不下载, -1: 低, 0: 一般, 1:高
''Previous Initialize, Tell kernel to Set priority of file
''-2: no download, -1: low, 0: middle, 1: high
Declare Sub FTK_Downloader_PreInitFilePriority Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal pFilePriority As String, ByVal nFilesCount As Long)

'初始化下载对象
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
'初始化下载对象
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

''初始化下载对象3
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

''初始化下载对象4
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

'释放下载对象
'Release downloader handle
Declare Function FTK_Downloader_Release Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'执行下载线程
'Execute downloader
Declare Function FTK_Downloader_Execute Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'暂停下载
'Pause downloader
Declare Sub FTK_Downloader_Pause Lib "FTKernelAPI" (ByVal HDownloader As Long)

'恢复下载
'Resume downloader
Declare Sub FTK_Downloader_Resume Lib "FTKernelAPI" (ByVal HDownloader As Long)

'是否已经初始化
'Is downloader intialized?
Declare Function FTK_Downloader_IsInit Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'获取下载任务目前的阶段状态
'Return downloader state
Declare Function FTK_Downloader_GetState Lib "FTKernelAPI" (ByVal HDownloader As Long) As enmFTK_Downloader_State

'是否只是进行文件检查
'Only checking file, don't downloading...
Declare Function FTK_Downloader_IsOnlyCheckFile Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'是否已经完成了下载 Lib "FTKernelAPI"(判断选择文件下载)
'Is all selected files finished?
Declare Function FTK_Downloader_IsFinished Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'是否已经完成了下载 Lib "FTKernelAPI"(全部下载)
'Is all files finished?
Declare Function FTK_Downloader_IsAllFinished Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'连接指定的Peer
'Add external source peer
Declare Sub FTK_Downloader_AddSource Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal pchIP As String, ByVal nPort As Integer, ByRef pPeerID As Byte)

''连接指定的User
''Add external source peer(socket handle)
Declare Sub FTK_Downloader_AddSourceExt Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal nSocket As Long)

'外部动态增加辅助的Announce
'Add external announce
Declare Sub FTK_Downloader_AddExtAnnounce Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal lpszAnnounce As String)

'手动控制Announce马上进行连接
'Reannounce manually
Declare Sub FTK_Downloader_ReannounceAll Lib "FTKernelAPI" (ByVal HDownloader As Long)

'Leo Mod: 2005-10-16
'按照块的先后顺序进行下载(适用于边下载边播放的情况)
'Tell kernel to sequential download piece
Declare Sub FTK_Downloader_SetSeqPicker Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal bSeq As Long)

'设置下载文件的优先级别
' -2:不下载, -1: 低, 0: 一般, 1:高
'Set priority of file
'-2: no download, -1: low, 0: middle, 1: high
Declare Sub FTK_Downloader_SetFilePriority Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal nIndex As Long, ByVal chPriority As Byte, ByVal bDoPriority As Long)

'强制立刻重新将文件的优先级赋值给Piece
'Force to set priority of all piece immediately
Declare Sub FTK_Downloader_ForceFilePriority Lib "FTKernelAPI" (ByVal HDownloader As Long)

'外部调用, 手动设置最大的下载率限制 Lib "FTKernelAPI"(0.0表示没有限制)
'Set fixed max download rate
Declare Sub FTK_Downloader_SetFixMaxDownloadRate Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal fMaxDownloadRate As Double)

'外部调用, 获取手动设置最大的下载率限制(0.0表示没有限制)
'Get fixed max download rate
Declare Function FTK_Downloader_GetFixMaxDownloadRate Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double


'外部调用, 手动设置最大的上传率限制 Lib "FTKernelAPI"(0.0表示没有限制)
'Set fixed max upload rate
Declare Sub FTK_Downloader_SetFixMaxUploadRate Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal fMaxUploadRate As Double)

'外部调用, 获取手动设置最大的上传率限制(0.0表示没有限制)
'Get fixed max upload rate
Declare Function FTK_Downloader_GetFixMaxUploadRate Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'主动限制某些特定的种子服务器(SEED), 给自己的最大的上传率(0表示没有限制, 注意单位是: KB)
'Set fixed max upload rate of SOME CERTAIN SEED to me, 0 means no limit, UNIT is KB
Declare Sub FTK_Downloader_SetSeedMaxUPSpeed Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal nSpeed As Integer)

'多少秒中内，禁止某个IP的连接, 只在当前任务存在期间有效
'Ban IP for X seconds, ONLY for the current active HDownloader
Declare Sub FTK_Downloader_BanPeerIP Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal lpszIP As String, ByVal nBannedSeconds As Long)


'获取线程的ID
'Get thread ID
Declare Function FTK_Downloader_GetThreadID Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'''''''''''''''''''''''''''''''''''''
'全局参数设置
'Global settings

'将某个Torrent文件的SHA1值加入队列
'Add torrent into SHA1 list
Declare Sub FTK_GlobalVar_AddTorrentSHA1 Lib "FTKernelAPI" (ByVal lpszSHA As String, ByVal HDownloader As Long)

'将某个Torrent文件的SHA1值从队列中删除
'Remove torrent from SHA1 list
Declare Sub FTK_GlobalVar_RemoveTorrentSHA1 Lib "FTKernelAPI" (ByVal lpszSHA As String)

'''''''''''''''''''''''''''''''''''''
'代理服务器函数列表
'Proxy interface

'设置仅在连接Tracker时使用代理服务器
'Only tracker using proxy settings
Declare Sub FTK_Proxy_SetOnlyTracker Lib "FTKernelAPI" (ByVal bOnlyTracker As Long)

'清空当前的代理信息 Lib "FTKernelAPI"(仅用于PROXYTYPE_NOPROXY)
'Only PROXYTYPE_NOPROXY
Declare Sub FTK_Proxy_SetType Lib "FTKernelAPI" (ByVal nProxyType As Long)

'设置代理 Lib "FTKernelAPI"(不能是PROXYTYPE_NOPROXY)
'May not be PROXYTYPE_NOPROXY
Declare Sub FTK_Proxy_SetProxy Lib "FTKernelAPI" (ByVal nProxyType As Long, ByVal pProxyHost As String, ByVal ProxyPort As Long)

'设置SOCKS5和HTTP1.1需要认证信息的代理
'Only SOCKS5 and HTTP1.1 proxies
Declare Sub FTK_Proxy_SetAuthProxy Lib "FTKernelAPI" (ByVal nProxyType As Long, ByVal pProxyHost As String, ByVal ProxyPort As Long, ByVal pProxyUser As String, ByVal pProxyPass As String)

'获取代理的类型
'Return proxy Type
Declare Function FTK_Proxy_GetProxyType Lib "FTKernelAPI" () As Long

'''''''''''''''''''''''''''''''''''''
'Downloader statistic information interface

'获取总共已经下载 Lib "FTKernelAPI"(验证成功)的数据
'Get the size of having received data for all file
Declare Function FTK_Stat_GetTotalFileHaveSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'获取选择已经下载 Lib "FTKernelAPI"(验证成功)的数据
'Get the size of having received data for a file
Declare Function FTK_Stat_GetSelectedFileHaveSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'Leo Mod: 2005-10-16
'获取已经顺序下载的目前可以从头开始播放的数据长度
'Get the size of sequential piece from file front
Declare Function FTK_Stat_GetStartSeqFileSize Lib "FTKernelAPI" (HDownloader As Long) As TwoLong

'获取最近一次下载的字节数
'Get the size of lasted receiving data
Declare Function FTK_Stat_GetLastDataSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'获取总共丢弃的字节数
'Get the size of bad data
Declare Function FTK_Stat_GetBadDataSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'当前总共的连接的个数
'Get the number of total peer
Declare Function FTK_Stat_GetTotalPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'当前主动连接的个数
'Get the number of active peer
Declare Function FTK_Stat_GetActivePeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'当前的被动连接的个数
'Get the number of passive peer
Declare Function FTK_Stat_GetPassivePeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'当前正在连接中的个数
'Get number of connecting peer
Declare Function FTK_Stat_GetConnectingPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'获取已经连接的种子的个数
'Get number of seed
Declare Function FTK_Stat_GetSeedCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'获取正在上传的连接的个数
'Get the number of uploading peer
Declare Function FTK_Stat_GetUploadPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'获取正在下载的连接的个数
'Get the number of downloading peer
Declare Function FTK_Stat_GetDownloadPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'获取总共可以获取的Seed的个数
'Get the number of total available seed
Declare Function FTK_Stat_GetTotalAvailSeedCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'获取总共可以获取的Peer的个数
'Get the number of peer
Declare Function FTK_Stat_GetTotalAvailPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'旧的种子的个数
'Get old seed number
Declare Function FTK_Stat_GetOldSeedPeerCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'本次运行已经下载的数据长度
'Get downloaded bytes
Declare Function FTK_Stat_GetDownloaded Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'本次运行已经上传的数据长度
'Get uploaded bytes
Declare Function FTK_Stat_GetUploaded Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'本次已经运行时间 Lib "FTKernelAPI"(运行时间不同与下载时间)
'Get total running time
Declare Function FTK_Stat_GetRunningTime Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'本次下载的时间 Lib "FTKernelAPI"(如果是做种, 则下载时间永远为0)
'Get total downloaded time
Declare Function FTK_Stat_GetDownloadTime Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'本次下载剩余的时间, 根据下载率计算
'Get the left time to download
Declare Function FTK_Stat_GetLeftTime Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'获取当前的上传率
'Get upload rate
Declare Function FTK_Stat_GetUploadRate Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'获取当前的下载率
'Get downloading rate
Declare Function FTK_Stat_GetDownloadRate Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'获取指定的Piece的下载进度
'Get the progress of a piece
Declare Sub FTK_Stat_GetPieceState Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pPiece As Byte, ByVal nCount As Long)

'获取检查文件的进度
'Get the progress of cheching piece
Declare Function FTK_Stat_GetCheckPieceSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'获取检查的Piece的个数
'Get number of checked piece
Declare Function FTK_Stat_GetCheckPieceCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'获取已经分配空间的大小
'Get the size of allocated file
Declare Function FTK_Stat_GetAllocSpaceSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'获取当前的健康率
'Get healthy rate
Declare Function FTK_Stat_GetHealthRate Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'获取当前的最大缓存大小
'Get the size of max cache
Declare Function FTK_Stat_GetMaxCacheSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'获取已经使用的缓存大小
'Get the size of used cache
Declare Function FTK_Stat_GetUseCacheSize Lib "FTKernelAPI" (ByVal HDownloader As Long) As Long

'获取本次写硬盘的总的次数
'Get writed disk count
Declare Function FTK_Stat_GetWriteDiskCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'获取本次真正写硬盘的次数
'Get really writed disk count
Declare Function FTK_Stat_GetRealWriteDiskCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'获取本次读硬盘的总的次数
'Get readed disk count
Declare Function FTK_Stat_GetReadDiskCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'获取本次真正读硬盘的次数
'Get really readed disk count
Declare Function FTK_Stat_GetRealReadDiskCount Lib "FTKernelAPI" (ByVal HDownloader As Long) As TwoLong

'获取写硬盘的频率 Lib "FTKernelAPI"(次'秒)
'Get writing disk frenqence Lib "FTKernelAPI"(number'second)
Declare Function FTK_Stat_GetWriteDiskFrenq Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'获取真正写硬盘的频率 Lib "FTKernelAPI"(次'秒)
'Get really writing disk frenqence Lib "FTKernelAPI"(number'second)
Declare Function FTK_Stat_GetRealWriteDiskFrenq Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'获取读硬盘的频率 Lib "FTKernelAPI"(次'秒)
'Get reading disk frenqence Lib "FTKernelAPI"(number'second)
Declare Function FTK_Stat_GetReadDiskFrenq Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'获取真正读硬盘的频率 Lib "FTKernelAPI"(次'秒)
'Get really reading disk frenqence Lib "FTKernelAPI"(number'second)
Declare Function FTK_Stat_GetRealReadDiskFrenq Lib "FTKernelAPI" (ByVal HDownloader As Long) As Double

'获取当前日志文件的路径+名称
'Get log file name
Declare Sub FTK_Stat_GetLogPathFileName Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal lpszFileName As String)

'获取指定的文件的进度
'Get the progress of a file
Declare Function FTK_Stat_GetFileHaveSize Lib "FTKernelAPI" (ByVal HDownloader As Long, ByVal nIndex As Long) As TwoLong

'获取当前用户状态信息的列表
'Get the peers information
Declare Sub FTK_Stat_GetPeerData Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pData As tagPeerData, ByRef nRetCount As Long, ByVal nMaxCount As Long)

'获取当前部分用户状态信息的列表
'Get the some peers information
Declare Sub FTK_Stat_GetPeerRangeData Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pData As tagPeerData, ByVal nFrom As Long, ByVal nTo As Long, ByRef nRetCount As Long, ByVal nMaxCount As Long, ByVal bExtInfo As Boolean)


'获取当前用户状态信息的列表 Lib "FTKernelAPI"(只获取IP和端口)
'Get the peers information Lib "FTKernelAPI"(only IP and port)
Declare Sub FTK_Stat_GetMiniPeerData Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pData As tagMiniPeerData, ByRef nRetCount As Long, ByVal nMaxCount As Long)

'获取当前Announce状态信息的列表
'Get the status of announces
Declare Sub FTK_Stat_GetAnnounceData Lib "FTKernelAPI" (ByVal HDownloader As Long, ByRef pData As tagAnnounceData, ByRef nRetCount As Long, ByVal nMaxCount As Long)

''获取当前任务的调试信息
''Get the debug information of downloader
Declare Function FTK_Stat_GetBTDownloaderInfo Lib "FTKernelAPI" (ByVal HDownloader As Long) As String

'''''''''''''''''''''''''''''''''''''
'打开Torrent文件获取信息的函数列表
'Torrent file interface

'判断是不是自己定义的加密的Torrent文件
'Return boolean, tell us is a cipher torrent file
Declare Function FTK_Torrent_IsCipherTorrent Lib "FTKernelAPI" (ByVal lpszFileName As String) As Long

'执行从文件中读取数据并初始化对象操作
'Open a torrent file handle
Declare Function FTK_Torrent_Open Lib "FTKernelAPI" (ByVal lpszFileName As String, ByVal nCodePage As Long, ByVal lpszDesKey As String, ByVal bValidEOF As Boolean, ByVal bValidSort As Boolean) As Long

''执行从文件中读取数据并初始化对象操作, 如果失败, 返回错误信息
''Open a torrent file handle, if failed, return error information
Declare Function FTK_Torrent_SafeOpen Lib "FTKernelAPI" (ByVal lpszFileName As String, ByVal nCodePage As Long, ByVal lpszDesKey As String, ByVal bValidEOF As Boolean, ByVal bValidSort As Boolean, ByRef pErrInfo As tagErrInfo) As Long

''判断是不是自己定义的加密的Torrent数据流对象
''Return boolean, tell us is a cipher torrent binary data
Declare Function FTK_Torrent_IsCipherTorrentObj Lib "FTKernelAPI" (ByRef pData As Byte, ByVal nLength As Long) As Boolean

''执行从Torrent binary object中读取数据并初始化对象操作
''Open a torrent binary object
Declare Function FTK_Torrent_OpenObj Lib "FTKernelAPI" (ByRef pData As Byte, ByVal nLength As Long, ByVal nCodePage As Long, ByVal lpszDesKey As String, ByVal bValidEOF As Boolean, ByVal bValidSort As Boolean, ByRef pErrInfo As tagErrInfo) As Long

'关闭当前打开的Torrent文件
'Close Torrent file handle
Declare Sub FTK_Torrent_Close Lib "FTKernelAPI" (ByVal hTorrentFile As Long)

'判断是目录还是文件
'Return boolean, tell us is only a single file in torrent
Declare Function FTK_Torrent_IsFile Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'获取 Torrent 名称
'Get the name of torrent file
Declare Function FTK_Torrent_GetTorrentName Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As String

'获取torrent中的文件的个数 Lib "FTKernelAPI"(至少一个)
'Get total number of files
Declare Function FTK_Torrent_GetFilesCount Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'获取torrent中的文件列表 Lib "FTKernelAPI"(至少一个)
'Get a pointer to file list
Declare Sub FTK_Torrent_GetFiles Lib "FTKernelAPI" (ByVal hTorrentFile As Long, ByRef pFileInfo As tagFileInfo)

'获取torrent中的文件列表中的某个文件的信息
'Get a pointer to a file of file list
Declare Sub FTK_Torrent_GetFileInfo Lib "FTKernelAPI" (ByVal hTorrentFile As Long, ByVal nIndex As Long, ByRef pFileInfo As tagFileInfo)

'获取Info的Hash值, 内部使用
'Get the binary info hash of torrent file
Declare Function FTK_Torrent_GetInfoHash Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'获取info的Hash值, 十六进制
'Get the hex encoding info hash of torrent file
Declare Function FTK_Torrent_GetHexInfoHash Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As String

'获取 main annouce url
'Get mainb announce url
Declare Function FTK_Torrent_GetMainAnnounce Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As String

'获取 Announce 分组的个数
'Get the number of all announce list
Declare Function FTK_Torrent_GetAnnouncesCount Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'获取指定的 Announce 分组包含的Announce的个数
'Get the size of a announce list
Declare Function FTK_Torrent_GetAnnounceSize Lib "FTKernelAPI" (ByVal hTorrentFile As Long, ByVal nGroupIndex As Long) As Long

'获取指定的 Announce 分组中指定位置的Announce
'Get a annoucne of a announce list
Declare Function FTK_Torrent_GetAnnouncesVal Lib "FTKernelAPI" (ByVal hTorrentFile As Long, ByVal nGroupIndex As Long, ByVal nIndex As Long) As String

'获取 注释
'Get the comments
Declare Function FTK_Torrent_GetComments Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As String

'获取 Torrent 创建时间
'Get the creation time of torrent file
Declare Function FTK_Torrent_GetCreateTime Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'获取piece块的大小
'Get the size of piece
Declare Function FTK_Torrent_GetPieceSize Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'获取文件的大小
'Get the total file size to transfer
Declare Function FTK_Torrent_GetFileSize Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As TwoLong

'Piece块的个数
'Get the total number of piece
Declare Function FTK_Torrent_GetPieceCount Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'获取Piece Hash 的列表
'Get a pointer to piece hash list
Declare Function FTK_Torrent_GetPieceHashList Lib "FTKernelAPI" (ByVal hTorrentFile As Long) As Long

'释放PieceHash列表
'Release piece hash memory
Declare Sub FTK_Torrent_FreePieceHashList Lib "FTKernelAPI" (ByVal hTorrentFile As Long)

'获取Torrent文件的语言编码
'Get language code page of torrent file
Declare Sub FTK_Torrent_GetLanCodePage Lib "FTKernelAPI" (ByVal hTorrentFile As Long)

'''''''''''''''''''''''''''''''''''''
'制作Torrent文件的函数列表
'Create torrent file interface

'打开一个制作torrent文件的句柄
'Open a making torrent handle
Declare Function FTK_MT_Open Lib "FTKernelAPI" () As Long

'关闭打开的制作Torrent文件的句柄
'Close a making torrent handle
Declare Sub FTK_MT_Close Lib "FTKernelAPI" (ByVal hMakeTorrent As Long)

'执行生成对象的操作
'Start to making torrent file
Declare Function FTK_MT_MakeTorrent Lib "FTKernelAPI" (ByVal hMakeTorrent As Long) As Long

'停止Torrent文件制作
'Stop making torrent file
Declare Sub FTK_MT_StopMake Lib "FTKernelAPI" (ByVal hMakeTorrent As Long)

'获取制作文件的进度
'Get progress of making torrent file
Declare Function FTK_MT_GetMTProgress Lib "FTKernelAPI" (ByVal hMakeTorrent As Long) As Double

'另存为Torrent文件
'Save as a torrent file
Declare Function FTK_MT_SaveAsTorrentFile Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszFileName As String, ByVal lpszDesKey As String) As Long

'设置 annouce url
'Set a main announce url
Declare Sub FTK_MT_SetAnnounceUrl Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszValue As String)

'添加额外的Announce 列表
'Add a announce list
Declare Sub FTK_MT_AddAnnounceList Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByRef Announces As String, ByVal nCount As Long)

'添加额外的Announce 列表, example: announce1;announce2;announce3;
'Add a announce list, example: announce1;announce2;announce3;
Declare Sub FTK_MT_AddAnnounceList2 Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszValue As String)

'清空额外的Announce 列表
'Clear all announce list
Declare Sub FTK_MT_ClearAnnounceList Lib "FTKernelAPI" (ByVal hMakeTorrent As Long)

'设置 注释
'Set comments
Declare Sub FTK_MT_SetComments Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszValue As String)

'设置piece块的大小
'Set piece size to making torrent file
Declare Sub FTK_MT_SetPieceSize Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal dwPieceSize As Long)

'设置torrent中的文件
'Set the sourece file to making torrent file
Declare Sub FTK_MT_SetFile Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszFileName As String)

'设置torrent中的文件目录 Lib "FTKernelAPI"(多个文件)
'Set the source path to making torrent file
Declare Sub FTK_MT_SetPath Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal lpszPathName As String)

'设置Torrent文件的语言代码 Lib "FTKernelAPI"(只对文件名称, 注释等有效)
'Set language code of torrent file
Declare Sub FTK_MT_SetLangCodePage Lib "FTKernelAPI" (ByVal hMakeTorrent As Long, ByVal nCodePage As Long)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''Tracker interface, to get status of one torrent from tracker: peer count'seed count

''HTTP tracker接口， 用于获取http Tracker某任务的状态信息
''HTTP Tracker interface, to get status of one torrent from http tracker
Declare Function FTK_Tracker_Http1 Lib "FTKernelAPI" (ByVal lpszTracker As String, ByVal pInfoHash As String, ByVal qwFileSize As TwoLong, ByRef nPeerCount As Long, ByRef nSeedCount As Long, ByRef bNetwordErr As Boolean, ByVal lpszErrInfo As String, ByVal nLength As Long) As Boolean


''HTTP tracker接口， 用于获取http Tracker某任务的状态信息
''HTTP Tracker interface, to get status of one torrent from http tracker
Declare Function FTK_Tracker_Http2 Lib "FTKernelAPI" (ByVal lpszTorrentFileName As String, ByRef nPeerCount As Long, ByRef nSeedCount As Long, ByRef bNetwordErr As Boolean, ByVal lpszErrInfo As String, ByVal nLength As Long) As Boolean

''UDP tracker接口， 用于获取UDP Tracker某任务的状态信息
''UDP Tracker interface, to get status of one torrent from UDP tracker
Declare Function FTK_Tracker_UDP1 Lib "FTKernelAPI" (ByVal lpszTracker As String, ByVal pInfoHash As String, ByVal qwFileSize As TwoLong, ByRef nPeerCount As Long, ByRef nSeedCount As Long, ByRef bNetwordErr As Boolean, ByVal lpszErrInfo As String, ByVal nLength As Long) As Boolean

''UDP tracker接口， 用于获取UDP Tracker某任务的状态信息
''UDP Tracker interface, to get status of one torrent from UDP tracker
Declare Function FTK_Tracker_UDP2 Lib "FTKernelAPI" (ByVal lpszTorrentFileName As String, ByRef nPeerCount As Long, ByRef nSeedCount As Long, ByRef bNetwordErr As Boolean, ByVal lpszErrInfo As String, ByVal nLength As Long) As Boolean
    

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Disk cache Settings

'Set Disk cache size
'设置磁盘缓存的大小
Declare Sub FTK_Disk_SetCache Lib "FTKernelAPI" (ByVal nMinCacheSize As Long, ByVal nMaxCacheSize As Long, ByVal nPhyMemorySize As Long)

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''Windows environment related interfaces

''Get local machine ip address(get the first ip or best ip if there are more than one NICs)
''获取本机的IP地址(在有多个的情况下，选择第一个，或者按照一定算法选择最合适的一个)
Declare Function FTK_Win_GetLocalIP Lib "FTKernelAPI" (ByRef bPrivateIP As Boolean) As String

''Open Windows ICS'ICF(Windows XP'Windows 2003)
''打开操作系统的网络连接防火墙和网络连接共享(Windows XP'Windows 2003)
Declare Sub FTK_Win_OpenWinXPICSF Lib "FTKernelAPI" (ByVal nPort As Integer, ByRef bOpenFirewall As Boolean, ByRef bPortMapping As Boolean, ByVal nProtocol As Byte, ByVal lpszIP As String, ByVal lpszAppName As String)

''Open UPnP port mapping(Win9x'WinME'Win2000'WinXP'Win2003)
''执行对于支持UPnP协议的Router进行自动的端口映射配置(内网处于Router后的机器必用)
Declare Function FTK_Win_AddUPnPPortMapping Lib "FTKernelAPI" (ByVal nPort As Integer, ByVal nProtocol As Byte, ByVal lpszIP As String) As Boolean

''Patch Windows XP SP2 tcpip.sys file for best TCP'IP performance
''对于Windows XP SP2 的tcpip.sys打补丁，破解连接数的限制，提高网络性能
Declare Function FTK_Win_PacthSP2TCPIPLimitFile Lib "FTKernelAPI" (nLimit As Long) As Long

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Other Functions, to convert from TwoLong to Double
'辅助进行类型转换的函数, 将自定义的TwoLong类型转换为Double类型
Public Function GetDoubleFromTwoLong(ByRef twLong As TwoLong) As Double
    Dim dbValue As Double
    dbValue = IIf(twLong.HighLong < 0, 4294967296# + twLong.HighLong, twLong.HighLong)
    dbValue = dbValue * 4294967296#
    dbValue = dbValue + IIf(twLong.LowLong < 0, 4294967296# + twLong.LowLong, twLong.LowLong)
    GetDoubleFromTwoLong = dbValue
End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
