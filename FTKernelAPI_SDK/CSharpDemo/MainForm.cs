using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Diagnostics;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.IO;
using P2PAPI;

namespace CSharpDemo
{
	/// <summary>
	/// MainForm 的摘要说明。
	/// </summary>
	public class MainForm : System.Windows.Forms.Form
	{
		private String m_sHexInfoVal;
		private uint m_hDownloader;
		private ulong m_ulTotalFileSize;
		private uint m_nPieceCount;

		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.TextBox textBox2;
		private System.Windows.Forms.TextBox textBox4;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Button button4;
		private System.Windows.Forms.ProgressBar progressBar1;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button button5;
		private System.ComponentModel.IContainer components;

		public MainForm()
		{
			//
			// Windows 窗体设计器支持所必需的
			//
			InitializeComponent();

			//
			// TODO: 在 InitializeComponent 调用后添加任何构造函数代码
			//
		}

		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows 窗体设计器生成的代码
		/// <summary>
		/// 设计器支持所需的方法 - 不要使用代码编辑器修改
		/// 此方法的内容。
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.button1 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.textBox2 = new System.Windows.Forms.TextBox();
			this.button3 = new System.Windows.Forms.Button();
			this.button4 = new System.Windows.Forms.Button();
			this.progressBar1 = new System.Windows.Forms.ProgressBar();
			this.timer1 = new System.Windows.Forms.Timer(this.components);
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.textBox4 = new System.Windows.Forms.TextBox();
			this.button5 = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(14, 8);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(377, 21);
			this.textBox1.TabIndex = 0;
			this.textBox1.Text = "";
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(400, 8);
			this.button1.Name = "button1";
			this.button1.TabIndex = 1;
			this.button1.Text = "Torrent";
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(400, 40);
			this.button2.Name = "button2";
			this.button2.TabIndex = 1;
			this.button2.Text = "DestPath";
			this.button2.Click += new System.EventHandler(this.button2_Click);
			// 
			// textBox2
			// 
			this.textBox2.Location = new System.Drawing.Point(14, 40);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new System.Drawing.Size(377, 21);
			this.textBox2.TabIndex = 0;
			this.textBox2.Text = "";
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(24, 184);
			this.button3.Name = "button3";
			this.button3.TabIndex = 1;
			this.button3.Text = "Start";
			this.button3.Click += new System.EventHandler(this.button3_Click);
			// 
			// button4
			// 
			this.button4.Location = new System.Drawing.Point(112, 184);
			this.button4.Name = "button4";
			this.button4.TabIndex = 1;
			this.button4.Text = "Cancel";
			this.button4.Click += new System.EventHandler(this.button4_Click);
			// 
			// progressBar1
			// 
			this.progressBar1.Location = new System.Drawing.Point(16, 72);
			this.progressBar1.Name = "progressBar1";
			this.progressBar1.Size = new System.Drawing.Size(376, 23);
			this.progressBar1.TabIndex = 3;
			// 
			// timer1
			// 
			this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(16, 104);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(152, 16);
			this.label1.TabIndex = 4;
			this.label1.Text = "Down Speed:";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(200, 104);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(152, 16);
			this.label2.TabIndex = 4;
			this.label2.Text = "Up Speed:";
			// 
			// textBox4
			// 
			this.textBox4.Location = new System.Drawing.Point(16, 128);
			this.textBox4.Name = "textBox4";
			this.textBox4.Size = new System.Drawing.Size(377, 21);
			this.textBox4.TabIndex = 0;
			this.textBox4.Text = "";
			// 
			// button5
			// 
			this.button5.Location = new System.Drawing.Point(208, 184);
			this.button5.Name = "button5";
			this.button5.TabIndex = 1;
			this.button5.Text = "torrent";
			this.button5.Click += new System.EventHandler(this.button5_Click);
			// 
			// MainForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 14);
			this.ClientSize = new System.Drawing.Size(480, 238);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.progressBar1);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.textBox2);
			this.Controls.Add(this.button3);
			this.Controls.Add(this.button4);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.textBox4);
			this.Controls.Add(this.button5);
			this.Name = "MainForm";
			this.Text = "MainForm";
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.Closed += new System.EventHandler(this.MainForm_Closed);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// 应用程序的主入口点。
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new MainForm());
		}

		public static bool ftk_cnt_func( uint nSocket, IntPtr pData )
		{
			return false;
		}

		private void StartContext()
		{
			Debug.Assert( !FTKernelAPI.FTK_Context_IsInit() );

			String sLicenseKey = "7C55ACE177773AC56EB1311FFC716F375ACE9C42BF4AF09B0E900BDBEC1D65765A33521B8636BE3BBC508EC87177BBC";
			sLicenseKey += "E892E392FA33864C702AB55779D9E2B5290C066DC6B0FFDB33B4FFCE6419E82E643DDE3CF1AC8410C25B623D7964F35B1E15C";
			sLicenseKey += "98E8628465A71696FDADD05B5F9F5D12393AA77666B868D369685989FDB7";
			FTKernelAPI.FTK_License_Set( sLicenseKey );


			String sStartPath = Application.StartupPath;
			sStartPath += "\\";

			String sConfigFile = sStartPath + "Config.ini";
			Debug.Assert( FTKernelAPI.FTK_Context_Init( sConfigFile, true ) );
			FTKernelAPI.FTK_Context_TorrentFile( false, false );
			Debug.Assert( !FTKernelAPI.FTK_FTK_Context_IsRunning() );
			FTKernelAPI.FTK_Context_Run();
			Debug.Assert( FTKernelAPI.FTK_FTK_Context_IsRunning() );

			FTKernelAPI.FTK_CALLBACK_FUNC ftk_func = new FTKernelAPI.FTK_CALLBACK_FUNC( ftk_cnt_func );
			FTKernelAPI.FTK_Context_NotifyCB( ftk_func );
		}

		private void ReleaseContext()
		{
			if ( FTKernelAPI.FTK_Context_IsInit() )
			{
				FTKernelAPI.FTK_Context_Release();
			}
		}

		private bool StartDownload()
		{
			String sStartupPath = Application.StartupPath;
			uint hTorrentFile = FTKernelAPI.FTK_Torrent_Open( textBox1.Text, 0, null, false, false );
			Debug.Assert( 0 != hTorrentFile );
			int nFileCount = FTKernelAPI.FTK_Torrent_GetFilesCount( hTorrentFile );
			Byte[] pPreAllocFile = new Byte[ nFileCount ];
			for ( int i = 0; i < nFileCount; i++ )
			{
				pPreAllocFile[ i ] = 0;
			}

			String sDestPath = textBox2.Text;
			//Debug.Assert( sDestPath.Length > 0 );
			if ( sDestPath.Length == 0 )
			{
				sDestPath = textBox1.Text;
				int nPos = sDestPath.LastIndexOf( "\\", 0, 1 );
				Debug.Assert( -1 != nPos );
				sDestPath = sDestPath.Substring( 0, nPos );
			}

			m_sHexInfoVal = FTKernelAPI.FTK_Torrent_GetHexInfoHash( hTorrentFile );
			//m_sHexInfoVal.Replace( "%", "" );
			m_sHexInfoVal = m_sHexInfoVal.Replace( "%", "" );

			m_hDownloader = FTKernelAPI.FTK_Downloader_Open();
			MessageBox.Show( sDestPath + "\\" + FTKernelAPI.FTK_Torrent_GetTorrentName( hTorrentFile ) );
			
			bool bRet = false;
			bRet = FTKernelAPI.FTK_Downloader_Init(
				m_hDownloader,
				textBox1.Text,
				pPreAllocFile,
				nFileCount,
				false,
				sDestPath + "\\" + FTKernelAPI.FTK_Torrent_GetTorrentName( hTorrentFile ),
				sStartupPath + "\\Config.INI",
				sStartupPath + "\\Log\\" + "Downloader.log",
				sStartupPath + m_sHexInfoVal + ".status",
				false,
				null,
				0 );

			if ( false == bRet )
			{
				FTKernelAPI.FTK_Downloader_Close( m_hDownloader );
				m_hDownloader = 0;
				return false;
			}

			bRet = FTKernelAPI.FTK_Downloader_Execute( m_hDownloader );
			if ( false == bRet )
			{
				FTKernelAPI.FTK_Downloader_Close( m_hDownloader );
				m_hDownloader = 0;
				return false;
			}

			FTKernelAPI.FTK_GlobalVar_AddTorrentSHA1( m_sHexInfoVal, m_hDownloader );

			m_ulTotalFileSize = FTKernelAPI.FTK_Torrent_GetFileSize( hTorrentFile );
			m_nPieceCount = FTKernelAPI.FTK_Torrent_GetPieceCount( hTorrentFile );

			FTKernelAPI.FTK_Torrent_Close( hTorrentFile );
			hTorrentFile = 0;
			
			return true;
		}

		private void StopDownload()
		{
			if ( 0 == m_hDownloader )
			{
				return;
			}

			FTKernelAPI.FTK_GlobalVar_RemoveTorrentSHA1( m_sHexInfoVal );

			FTKernelAPI.FTK_Downloader_Release( m_hDownloader );
			FTKernelAPI.FTK_Downloader_Close( m_hDownloader );
			m_hDownloader = 0;
		}

		private double PERCENT( ulong n, ulong d )
		{
			return ( 100 * ( ( double )n ) ) / ( ( double ) d );
		}

		private string FormatBytes( ulong nBytes )
		{
			String sResult;
			double fVal = 0.0;

			if ( nBytes >= ( ulong ) 0x10000000000L )
			{
				fVal = nBytes / 1099511627776.0f;
				sResult = fVal.ToString(".00");
				sResult += " TB";
			}
			else if ( nBytes >= 0x40000000 )
			{
				fVal = nBytes / 1073741824.0f;
				sResult = fVal.ToString(".00");
				sResult += " GB";
			}
			else if ( nBytes >= 0x100000 )
			{
				fVal = nBytes / 1048576.0f;
				sResult = fVal.ToString(".00");
				sResult += " MB";
			}
			else if ( nBytes >= 0x400 )
			{
				fVal = nBytes / 1024.0f;
				sResult = fVal.ToString(".00");
				sResult += " KB";
			}
			else
			{
				sResult = nBytes.ToString();
				sResult += " Byte";
			}

			return sResult;
		}

		private void button1_Click(object sender, System.EventArgs e)
		{
			OpenFileDialog openFileDialog = new OpenFileDialog();
			openFileDialog.Filter = "Torrent File|*.torrent|All Files|*.*";
			openFileDialog.RestoreDirectory = true;
			openFileDialog.FilterIndex = 1;
			if ( openFileDialog.ShowDialog()==DialogResult.OK )
			{
				textBox1.Text = openFileDialog.FileName;
			}		
		}

		private void button2_Click(object sender, System.EventArgs e)
		{
			FolderBrowserDialog fbd=new FolderBrowserDialog();
			if ( fbd.ShowDialog()==DialogResult.OK )
			{
				textBox2.Text = fbd.SelectedPath;
				if ( textBox2.Text[ textBox2.TextLength - 1] != '\\' )
				{
					textBox2.Text += "\\";
				}
			}		
		}

		private void button3_Click(object sender, System.EventArgs e)
		{
			if ( textBox1.Text.Length == 0 )
			{
				MessageBox.Show( "Please select the Torrent file!" );
				return;
			}

			if ( !StartDownload() )
			{
				MessageBox.Show( "Failed to sart download, Please visit http://www.p2plib.com to get technical support!" );
				return;
			}

			button1.Enabled = false;
			button2.Enabled = false;
			button3.Enabled = false;		
		}

		private void button4_Click(object sender, System.EventArgs e)
		{
			this.Close();
		}

		private void MainForm_Load(object sender, System.EventArgs e)
		{
			StartContext();

			progressBar1.Maximum = 100;
			progressBar1.Value = 0;

			timer1.Enabled = true;		
		}

		private void MainForm_Closed(object sender, System.EventArgs e)
		{
			StopDownload();
			ReleaseContext();
		}

		private void BytePtr_to_AnnounceData( IntPtr pData, ref FTKernelAPI._tagAnnounceData AnnounceData )
		{
			IntPtr pPos = (IntPtr)0;
			IntPtr pOffset = Marshal.OffsetOf(AnnounceData.GetType(), "m_szURL" );
			
			pPos = (IntPtr)((int)pData + (int)pOffset);
			AnnounceData.m_szURL = Marshal.PtrToStringAnsi( pPos );

			pOffset = Marshal.OffsetOf(AnnounceData.GetType(), "m_bWorking" );

			pPos = (IntPtr)((int)pData + (int)pOffset);
			AnnounceData.m_bWorking = Marshal.ReadByte( pPos );

			pOffset = Marshal.OffsetOf(AnnounceData.GetType(), "m_bHeader" );

			pPos = (IntPtr)((int)pData + (int)pOffset);
			AnnounceData.m_bHeader = Marshal.ReadByte( pPos );

			pOffset = Marshal.OffsetOf(AnnounceData.GetType(), "m_nCount" );

			pPos = (IntPtr)((int)pData + (int)pOffset);
			AnnounceData.m_nCount = (uint)Marshal.ReadInt32( pPos );

			pOffset = Marshal.OffsetOf(AnnounceData.GetType(), "m_nFailed" );

			pPos = (IntPtr)((int)pData + (int)pOffset);
			AnnounceData.m_nFailed = (uint)Marshal.ReadInt32( pPos );

			pOffset = Marshal.OffsetOf(AnnounceData.GetType(), "m_fTimeLeft" );

			pPos = (IntPtr)((int)pData + (int)pOffset);

			float [] fVals = new float[1];
			Marshal.Copy( pPos,fVals, 0, 1 );
			AnnounceData.m_fTimeLeft = fVals[0];

			pOffset = Marshal.OffsetOf(AnnounceData.GetType(), "m_fLastTime" );

			pPos = (IntPtr)((int)pData + (int)pOffset);

			Marshal.Copy( pPos,fVals, 0, 1 );
			AnnounceData.m_fLastTime = fVals[0];

			pOffset = Marshal.OffsetOf(AnnounceData.GetType(), "m_szExtInfo" );
			pPos = (IntPtr)((int)pData + (int)pOffset);
			AnnounceData.m_szExtInfo = Marshal.PtrToStringAnsi( pPos );	
		}

		private void BytePtr_to_Announces_Data( IntPtr pData, FTKernelAPI._tagAnnounceData [] AnnounceData, int nAnnounceCount )
		{
			int nSize = Marshal.SizeOf( AnnounceData[0] );

            for ( int i = 0; i < nAnnounceCount; i++ )
			{
				BytePtr_to_AnnounceData( pData, ref AnnounceData[i] );
				pData = (IntPtr)((int)pData + nSize);
			}
		}

		private void BytePtr_to_PeerData( IntPtr pData, ref FTKernelAPI._tagPeerData PeerData )
		{
			IntPtr pPos = (IntPtr)0;
			IntPtr pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_dwIP" );

			pPos = (IntPtr)((int)pData + (int)pOffset);
			PeerData.m_dwIP = (uint)Marshal.ReadInt32( pPos );
			
			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_nPort" );

			pPos = (IntPtr)((int)pData + (int)pOffset);
			PeerData.m_nPort = (ushort)Marshal.ReadInt16( pPos );

			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_pPeerID" );

			pPos = (IntPtr)((int)pData + (int)pOffset);

			Byte [] pPeerID = new Byte[ (int)FTKernelAPI.IDSZ.IDSIZE ];
		    Marshal.Copy( pPos, pPeerID, 0, (int)FTKernelAPI.IDSZ.IDSIZE );
			PeerData.m_pPeerID = pPeerID;

			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_bIsLocal" );

			pPos = (IntPtr)((int)pData + (int)pOffset);
			PeerData.m_bIsLocal = Marshal.ReadByte( pPos );

			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_szVersion" );

			pPos = (IntPtr)((int)pData + (int)pOffset);
			PeerData.m_szVersion = Marshal.PtrToStringAnsi( pPos );

			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_ulPeerHaveSize" );

			pPos = (IntPtr)((int)pData + (int)pOffset);
			PeerData.m_ulPeerHaveSize = (ulong)Marshal.ReadInt64( pPos );

			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_fDownRate" );

			pPos = (IntPtr)((int)pData + (int)pOffset);

			float [] fVals = new float[1];
			Marshal.Copy( pPos,fVals, 0, 1 );
			PeerData.m_fDownRate = fVals[0];

			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_fUpRate" );

			pPos = (IntPtr)((int)pData + (int)pOffset);

			Marshal.Copy( pPos,fVals, 0, 1 );
			PeerData.m_fUpRate = fVals[0];

			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_ulDownloaded" );

			pPos = (IntPtr)((int)pData + (int)pOffset);
			PeerData.m_ulDownloaded = (ulong)Marshal.ReadInt64( pPos );

			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_ulUploaded" );

			pPos = (IntPtr)((int)pData + (int)pOffset);
			PeerData.m_ulUploaded = (ulong)Marshal.ReadInt64( pPos );

			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_fTimeElapsed" );

			pPos = (IntPtr)((int)pData + (int)pOffset);

			Marshal.Copy( pPos,fVals, 0, 1 );
			PeerData.m_fTimeElapsed = fVals[0];


			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_fPeerDownRate" );

			pPos = (IntPtr)((int)pData + (int)pOffset);

			Marshal.Copy( pPos,fVals, 0, 1 );
			PeerData.m_fPeerDownRate = fVals[0];

			pOffset = Marshal.OffsetOf(PeerData.GetType(), "m_szExtInfo" );
			pPos = (IntPtr)((int)pData + (int)pOffset);
			PeerData.m_szExtInfo = Marshal.PtrToStringAnsi( pPos );	
		}

		private void BytePtr_to_Peers_Data( IntPtr pData, FTKernelAPI._tagPeerData [] PeersData, int nPeerCount )
		{
			int nSize = Marshal.SizeOf( PeersData[0] );

			for ( int i = 0; i < nPeerCount; i++ )
			{
				BytePtr_to_PeerData( pData, ref PeersData[i] );
				pData = (IntPtr)((int)pData + nSize);
			}
		}

		private void timer1_Tick(object sender, System.EventArgs e)
		{
			if ( 0 == m_hDownloader )
			{
				return;
			}

			if ( FTKernelAPI.FTK_Downloader_GetState( m_hDownloader ) == FTKernelAPI.DLSTATE.DLSTATE_CHECKING )
			{
				textBox4.Text = "Status: checking file...";
			}
			else if ( FTKernelAPI.FTK_Downloader_GetState( m_hDownloader ) == FTKernelAPI.DLSTATE.DLSTATE_DOWNLOAD )
			{
				textBox4.Text = "Status: downloading...";
			}
			else if ( FTKernelAPI.FTK_Downloader_GetState( m_hDownloader ) == FTKernelAPI.DLSTATE.DLSTATE_FETALERR )
			{
				textBox4.Text = "Status: downloading error...";
			}
			else if ( FTKernelAPI.FTK_Downloader_GetState( m_hDownloader ) == FTKernelAPI.DLSTATE.DLSTATE_TERMINATE )
			{
				textBox4.Text = "Status: stopping...";
			}

			int nPos = 0;
			if ( FTKernelAPI.FTK_Downloader_GetState( m_hDownloader ) == FTKernelAPI.DLSTATE.DLSTATE_CHECKING )
			{
				nPos = ( int )PERCENT( (ulong)FTKernelAPI.FTK_Stat_GetCheckPieceCount( m_hDownloader ), (ulong)m_nPieceCount );
				progressBar1.Value = nPos;
			}

			if ( FTKernelAPI.FTK_Downloader_GetState( m_hDownloader ) < FTKernelAPI.DLSTATE.DLSTATE_DOWNLOAD || 
				FTKernelAPI.FTK_Downloader_GetState( m_hDownloader ) >= FTKernelAPI.DLSTATE.DLSTATE_FETALERR )
			{
				return;
			}

			P2PAPI.FTKernelAPI._tagPeerData [] PeersData = new P2PAPI.FTKernelAPI._tagPeerData[ 10 ];
			int nRetCount = 10;

			int nSize = Marshal.SizeOf(PeersData[0]);

			IntPtr pData = MarshalExt.AllocHGlobal( nSize * 10 );
			nRetCount = 10;

			FTKernelAPI.FTK_Stat_GetPeerData( m_hDownloader, pData, ref nRetCount, 10 );
			BytePtr_to_Peers_Data( pData, PeersData, nRetCount );
			MarshalExt.FreeHGlobal( pData );
			
			//P2PAPI.FTKernelAPI._tagAnnounceData [] AnnouncesData = new P2PAPI.FTKernelAPI._tagAnnounceData[10];// = new P2PAPI.FTKernelAPI._tagAnnounceData[ 20 ];
			
			P2PAPI.FTKernelAPI._tagAnnounceData [] AnnouncesData = new P2PAPI.FTKernelAPI._tagAnnounceData[10];
			nSize = Marshal.SizeOf(AnnouncesData[0]);

			pData = MarshalExt.AllocHGlobal( nSize * 10 );
			nRetCount = 10;
			
			FTKernelAPI.FTK_Stat_GetAnnounceData( m_hDownloader, pData, ref nRetCount, 10 );
			BytePtr_to_Announces_Data( pData, AnnouncesData, nRetCount );
			MarshalExt.FreeHGlobal( pData );

			ulong ulTotalFileHaveSize = FTKernelAPI.FTK_Stat_GetTotalFileHaveSize( m_hDownloader );
			nPos = ( int )PERCENT( (ulong)ulTotalFileHaveSize, (ulong)m_ulTotalFileSize );
			progressBar1.Value = nPos;

			String sValue;
			sValue = FormatBytes( ( ulong )FTKernelAPI.FTK_Stat_GetDownloadRate( m_hDownloader ) );
			label1.Text = "Down Speed: " + sValue + "/s";

			sValue = FormatBytes( ( ulong )FTKernelAPI.FTK_Stat_GetUploadRate( m_hDownloader ) );
			label2.Text = "Up Speed: " + sValue + "/s";

			sValue = FormatBytes( ulTotalFileHaveSize );
			textBox4.Text += " | Downloaded: " + sValue;

			if ( nPos >= 100 )
			{
				textBox4.Text = "Status: Downloaded OK...";
			}		
		}

		private void button5_Click(object sender, System.EventArgs e)
		{
			uint hTorrentFile = FTKernelAPI.FTK_Torrent_Open( textBox1.Text, 0, null, false, false );
			Debug.Assert( 0 != hTorrentFile );
			String sName = FTKernelAPI.FTK_Torrent_GetTorrentName( hTorrentFile );
			FTKernelAPI.FTK_Torrent_Close( hTorrentFile );
			hTorrentFile = 0;
			MessageBox.Show( sName );
		}
	}
}
