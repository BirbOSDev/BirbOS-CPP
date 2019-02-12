#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <direct.h>
#include "libs/sha256.h"
#include <typeinfo>

void print(std::string str){
    std::cout << str << std::endl;
};
void wait(int sec){
    Sleep(sec * 1000);
};


int main(){
    sys_start:
    string osbuild="BirbOS C++ 0.2 Beta";
    SetConsoleTitle("BirbOS C++ 0.2 Beta");
    wait(2);
    system("cls");
    print("BirbOS c++ is booting...");
    wait(3);
    print("Booted successfuly!");
    login:
    system("cls");
    print("Login to birbOS. (Type \"Guest\" for guest account, and type \"shutdown\" to shutdown.)");
    print("");
    print("List of available users:");
    print("Guest");
    system("dir /b users");
    print("");
    string u;
    string p;
    cout << "Username>> ";
    getline(cin, u);
    if(u.empty()){
            print("Please enter an username!");
            goto login;
    }
    int skip = 0;
    if(u=="Guest"){
    skip = 1;
    }
    if(u=="shutdown"){
        print("Shutting down.. Please wait");
        wait(3);
        return 0;
    }
    if(skip != 1){
    std::string folder =
    "users/" +
    u + "/";
    if(GetFileAttributes(folder.c_str()) != INVALID_FILE_ATTRIBUTES){
    }
    else{
        print("User does not exist.");
        goto login;
    };
    std::string pwordfile =
    "users/" +
    u + "/.birbuser";
    ifstream ifile(pwordfile.c_str());
    if (ifile) {
    cout << "Password>> ";
    getline(cin, p);
    if(u.empty()){
            print("Please enter password!");
            goto login;
    }
    char *cp = &p[0u];
    std::ifstream ifs (pwordfile.c_str());
    std::string s;
    getline (ifs, s, (char) ifs.eof());
    std::string s1 = s.erase(64,3);
    std::string s2 = SHA256(cp);
    char *str1 = &s1[0u];
    char *str2 = &s2[0u];
    if(strcmp(str1, str2) != 0){
        print("Password is incorrect!");
        goto login;
    };
    }
    ifile.close();
    }
    p = "";
    logon:
    print("Login successful.");
    print("");
    print("");
    print("       °°°°      °     °°°°°°      °°°°       °°°°      °°°°°");
    print("       °   °           °     °     °   °     °    °    °");
    print("       °    °    °     °     °     °    °    °    °   °");
    print("       °°°°°     °     °°°°°°°     °°°°°     °    °   °°°°°°°");
    print("       °    °    °     °°          °    °    °    °         °");
    print("       °   °     °     °  °        °   °     °    °        °");
    print("       °°°°      °     °   °°      °°°°       °°°°    °°°°°");
    print("");
    print("");
    wait(1);
    system("color 1a");
    wait(1);
    system("color 2b");
    wait(1);
    system("color 3c");
    wait(1);
    system("color 0f");
    print("Welcome, " + u);
    wait(2);
    cmdprompt:
    string input;
    cout << u + "$birbOS >>";
    cin >> input;
    if(input=="calculator"){
        string exp;
        cout << "Enter expression: ";
        cin >> exp;
        if(exp.empty()){
            print("Please enter expression!");
            goto cmdprompt;
        }
        print("This feature is in works..");
        goto cmdprompt;
    }
    if(input == "reboot /refresh"){
        print("Rebooting...");
        wait(2);
        goto sys_start;
    }
    if(input == "reboot"){
        print("Rebooting..");
        wait(2);
        system("birbtool");
        return 0;
    }
    if(input == "shutdown"){
        print("BirbOS is shutting down.");
        wait(2);
        print("See you later!");
        wait(1);
        return 0;
    }
    if(input == "bsod"){
        system("cls");
        wait(0.5);
        system("color 9f");
        wait(0.25);
        print("BirbOS has been unexpectedly shutdown.");
        print("");
        print("Please report this error if it is important : ");
        print("ERR : USER_INITIATED_CRASH");
        print("0;0;01");
        print("");
        print("");
        print("Press ENTER to restart.");
        system("pause > nul");
        ShellExecute(NULL, "open", "birbtool.exe", NULL, NULL, SW_SHOWDEFAULT);
        return 1;
        }
    if(input == "help"){
        print("Commands : reboot [/refresh], shutdown, help, clear, about, logoff, folder, writedoc, readdoc, clean");
        goto cmdprompt;
    }
    if(input == "clear"){
        system("cls");
        goto cmdprompt;
    }
    if(input == "about"){
        print(osbuild);
        print("Developed by ad2017.");
        goto cmdprompt;
    }
    if(input == "logoff"){
        print("Logging off..");
        wait(3);
        system("cls");
        goto login;
    }
    if(input == "makedir"){
        string f;
        cout << "Enter folder name : ";
        cin >> f;
        std::string folder =
        "users/" +
        u + "/" + f + "/";
        mkdir(folder.c_str());
        print("Folder created!");
        goto cmdprompt;
    }
    if(input == "writedoc"){
        print("Feature coming soon..");
        goto cmdprompt;
    }
    if(input == "readdoc"){
        print("Feature coming soon..");
        goto cmdprompt;
    }
    if(input == "clean"){
        print("This command has no use because apps are not implemented yet.");
        goto cmdprompt;
    }
    if(input == "set-theme"){
        string theme;
        print("Themes : dark, light");
        cin >> theme;
        if(theme == "dark"){
            system("color 0f");
            goto cmdprompt;
        }
        if(theme == "light"){
            system("color f0");
            goto cmdprompt;
        }
        print("Invalid theme.");
        goto cmdprompt;
    }
    print("Invalid command");
    goto cmdprompt;
}
