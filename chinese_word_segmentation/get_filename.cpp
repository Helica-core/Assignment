#include <cstdio>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

void get_filename(const char *dir ,vector <string> &file_list)
{
    cout << "travel :" << dir << endl;

    WIN32_FIND_DATA wfd;
    HANDLE hFind;

    hFind = FindFirstFile(dir,&wfd);

    do{
        cout << wfd.cFileName << endl;
        file_list.push_back(wfd.cFileName);
    }while(FindNextFile(hFind,&wfd));

    FindClose(hFind);
}

void travel_folder()
{
    string addr = "/*.*";

    vector <string> folder_name;
    get_filename("./*",folder_name);
    vector <string> file_list;

    vector <string>::iterator it;
    for(it = folder_name.begin();it!=folder_name.end();it++) if(*it != "." && *it != "..")
    {
        file_list.clear();
        string dir = "./" + *it + addr;

        get_filename(dir.c_str(),file_list);


    }
}

int main()
{
    travel_folder();

    system("PAUSE");
}
