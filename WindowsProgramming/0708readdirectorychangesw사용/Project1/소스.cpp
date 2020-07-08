#include <stdio.h>
#include <Windows.h>
#include <Strsafe.h>

int main() {
    HANDLE hDir = CreateFileW(L"g:\\", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
        0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0);
    CONST DWORD cbBuffer = 1024 * 1024;
    BYTE* pBuffer = (PBYTE)malloc(cbBuffer);
    BOOL bWatchSubtree = FALSE;
    DWORD dwNotifyFilter = FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
        FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE |
        FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION;
    DWORD bytesReturned;
    WCHAR temp[MAX_PATH] = { 0 };

    for (;;)
    {
        FILE_NOTIFY_INFORMATION* pfni;
        BOOL fOk = ReadDirectoryChangesW(hDir, pBuffer, cbBuffer,
            bWatchSubtree, dwNotifyFilter, &bytesReturned, 0, 0);
        if (!fOk)
        {
            DWORD dwLastError = GetLastError();
            printf("error : %d\n", dwLastError);
            break;
        }

        pfni = (FILE_NOTIFY_INFORMATION*)pBuffer;

        do {
            printf("NextEntryOffset(%d)\n", pfni->NextEntryOffset);
            switch (pfni->Action)
            {
            case FILE_ACTION_ADDED:
                wprintf(L"FILE_ACTION_ADDED\n");
                break;
            case FILE_ACTION_REMOVED:
                wprintf(L"FILE_ACTION_REMOVED\n");
                break;
            case FILE_ACTION_MODIFIED:
                wprintf(L"FILE_ACTION_MODIFIED\n");
                break;
            case FILE_ACTION_RENAMED_OLD_NAME:
                wprintf(L"FILE_ACTION_RENAMED_OLD_NAME\n");
                break;
            case FILE_ACTION_RENAMED_NEW_NAME:
                wprintf(L"FILE_ACTION_RENAMED_NEW_NAME\n");
                break;
            default:
                break;
            }
            printf("FileNameLength(%d)\n", pfni->FileNameLength);

            StringCbCopyNW(temp, sizeof(temp), pfni->FileName, pfni->FileNameLength);

            wprintf(L"FileName(%s)\n", temp);

            pfni = (FILE_NOTIFY_INFORMATION*)((PBYTE)pfni + pfni->NextEntryOffset);
        } while (pfni->NextEntryOffset > 0);
    }
}