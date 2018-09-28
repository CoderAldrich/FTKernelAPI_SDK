using System;
using System.Runtime.InteropServices;

namespace P2PAPI
{
	/// <summary>
	/// Class1 ��ժҪ˵����
	/// </summary>
	public class MarshalExt
	{
		public MarshalExt()
		{
			//
			// TODO: �ڴ˴���ӹ��캯���߼�
			//
		}

		//////////////////////////////////////////////////////////////////////////
		//Allocate/Free regular heap memory
		//////////////////////////////////////////////////////////////////////////
		
		[DllImport("kernel32.dll")]
		public static extern IntPtr LocalAlloc(int fuFlags, int cbBytes);

		public const int LMEM_FIXED = 0x0000;
		public const int LMEM_ZEROINIT = 0x0040;

		public static IntPtr AllocHGlobal(int cb)
		{
			return LocalAlloc( LMEM_FIXED | LMEM_ZEROINIT, cb);
		}

		[DllImport("kernel32.dll")]
		public static extern IntPtr LocalFree( IntPtr hMem);

		public static void FreeHGlobal(IntPtr hGlobal)
		{
			LocalFree( hGlobal );
		}
	}
}
