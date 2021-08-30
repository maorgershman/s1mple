export module Utils;

namespace Utils
{
    export std::wstring get_data_folder_path()
    {
        std::wstringstream ssFolderPath;
        {
            wchar_t* wstrKnownFolderPath = NULL;
            SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, NULL, &wstrKnownFolderPath);
            ssFolderPath << wstrKnownFolderPath << L"\\s1mple";
            CoTaskMemFree(wstrKnownFolderPath);
        }

        return ssFolderPath.str();
    }
}