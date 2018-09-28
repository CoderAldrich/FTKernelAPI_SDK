# FTKernelAPI_SDK
FTKernelAPI
is a p2p file-sharing library fully compatible with Bittorrent, which
is one of the most popular p2p protocol designed for high-speed
distribution of 100MB or GB sized files. FTKernelAPI is a powerful,
fast, and easy-to-use bittorrent library. It supports simultaneous
downloads, download queue, selected downloads in torrent package,
fast-resume, disk cache, speed limits etc. BitZam is a demo,
tell you how to use FTKernelAPI library. You needn't to pay a attention
to networking programing and BitTorrent protocol, can quickly develop
yourself BitTorrent program based on FTKernelAPI library. FlashBT
is a famous BitTorrent client, based on FTKernelAPI library, developed
from 2004. About 1 million users today use FlashBT. So, FTKernelAPI is
very powerfull and stable, The author of FTKernelAPI is working to make
it best everyday. Any one, have experience on networking program, can
easily develop a program based on FTKernel, in Visual C++, Visual
Basic, Delphi, C++ Builder languages.
序号	描述
1	全新高效的网络内核，高效稳定，高速下载时依然占用很少的CPU
2	支持通用的BitTorrent下载算法, 支持下载通用的BitTorrent种子。
3	支持多任务下载，而只需要侦听一个TCP Socket端口
4	下载时支持磁盘缓存，并且支持设置磁盘缓存的大小
5	支持多HTTP和UDP Tracker协议，UTF-8扩展，UDP Tracker v2协议
6	可以主动控制单个任务的下载和上传速度
7	断点续传, 自动保存上一次的下载状态，下次下载自动续传, 不必每次重新自检
8	支持手动对于文件的完整性进行单独的检测
9	持两种磁盘分配方式：边下载边分配，预先分配，可以灵活选择
10	支持代理服务器, 支持Socks4, Socks4a, Socks5, Http1.1代理协议
11	支持用户间连接信息自动交换, 减轻Tracker的负载压力
12	支持UPnP协议自动配置路由器端口映射，实现内网免配置(要求路由器支持UPnP)
13	防火墙配置，全自动配置XP网络连接防火墙(ICF)和网络连接共享(ICS)
14	支持一个Torrent文件中的多个文件有选择的下载，支持文件下载的优先级别设定
15	支持单个文件或者目录制作成Torrent文件，支持加密的Torrent文件（DES算法加密）
16	支持打开兼容官方标准协议的Torrent文件，支持打开自己制作的加密的Torrent文件。（DES算法解密）, 支持UTF-8扩展，支持多语言
17	支持获取当前Announce URL连接的状态信息
18	支持获取当前所有连接的用户的状态信息
19	支持获取运行任务的磁盘读写次数和节省的比率
20	支持获取目前占用缓存的大小
21	支持获取当前下载任务的健康率
22	支持获取总的下载进度和某个块的下载状态和进度
23	支持顺序下载，以便于边下载边播放的实现, 用于实现电影点播平台
24	支持被动的回调触发做种子，只有有人请求下载时才加载任务到内存中
25	支持临时和永久封IP，兼容eMule的IP规则配置文件：ipfilter.dat
26	支持DHKE密钥交换算法，支持加密的BitTorrent协议流，避免网络封锁
27	支持自己定义协议标识，以便组成自己的私有的P2P协议网络
28	支持自己定义和Http Tracker通信时的UserAgent标识
29	支持自己定义自己的用户标识，以便和其他的帐号兼容
30	支持快速加载任务到内存中，做种子，避免漫长的检查时间
31	支持从指定的Tracker上获取某个Torrent文件的种子和用户信息
32	内网互联（NAT Traversal）技术，突破网关，自动实现不同内网间的互联传输
33	支持通过公用DHT网络，实现无TrackerTorrent文件下载
