bool InjectDll(DWORD dwPid, char *szDllName)
{
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPid);
    if (hProcess)
    {
        LPVOID pLoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
        LPVOID pAllocAddr = VirtualAllocEx(hProcess , NULL, strlen(szDllName), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        WriteProcessMemory(hProcess , pAllocAddr, szDllName, strlen(szDllName), NULL);
        
        HANDLE hThread = CreateRemoteThread(hProcess , NULL, NULL, (LPTHREAD_START_ROUTINE)pLoadLibAddr, pAllocAddr, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);
        
        VirtualFreeEx(hProcess , pAllocAddr, strlen(szDllName), MEM_RELEASE);
        CloseHandle(hThread);
        CloseHandle(hProcess);
        
        return true;
    }
    
    return false;
}