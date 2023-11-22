#include <iostream>
#include <windows.h>

int wmain(int argc, wchar_t* argv[])
{
    if (argc < 2)
    {
        std::wcout
            << L"Not enough arguments\n"
            << L"\n"
            << L"Usage: FileLocker.exe <file>" << std::endl;
        return ERROR_BAD_ARGUMENTS;
    }

    auto handle = CreateFileW(
        argv[1],
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (!handle || handle == INVALID_HANDLE_VALUE)
    {
        auto error = GetLastError();
        std::wcout << L"Failed to open handle to file \"" << argv[1] << L"\" with error: " << error << std::endl;
        return error;
    }

    std::wcout << L"Handle opened for file \"" << argv[1] << L"\"" << std::endl;
    std::system("pause");

    CloseHandle(handle);
    return ERROR_SUCCESS;
}
