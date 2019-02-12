#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <direct.h>
#include "libs/sha256.h"


void print(std::string str){
    std::cout << str << std::endl;
};
void wait(int sec){
    Sleep(sec * 1000);
};

int main(){
    system("cls");
    SetConsoleTitle("BirbTool");
    wait(3);
    print("Checking for missing folders...");
    mkdir("users");
    mkdir("apps");
    wait(1);
    print("BirbTool v0.1");
    print(
    "Boot options:\n"
    "Use \"shutdown\" to shutdown birbTool.\n"
    "Use \"launch\" to launch default BirbOS mode.\n"
    "Use \"usrtool\" to start up the UserTool.\n"
    "Use \"dsktool\" to check the birbOS installation.\n"
    "Use \"changepass\" to change the password for your account.\n"
    "Use \"deluser\" to delete your account.\n"
    );
    ldr:
    std::string ldr;
    std::cout << "BirbTool>";
    getline(std::cin, ldr);
    if(ldr=="shutdown"){
        system("cls");
        print("Shutting down the system, please wait...");
        wait(5);
        return 0;
    };
    if(ldr=="launch"){
        print("Booting from {3f79bb7-b435b05321-651daefd3}...");
        wait(2);
        try {
        ShellExecute(NULL, "open", "birbOS.exe", NULL, NULL, SW_SHOWDEFAULT);
        }
        catch (...) {
            print("Can't find birbOS.exe. Did you rename it?");
            wait(3);
            return(1);
        }
        return(0);
    };
    if(ldr=="usrtool"){
        print("birbOS UserTool");
        std::string u;
        std::string c;
        std::string p;
        std::cout << "Enter username: ";
        getline(std::cin, u);
        std::string folder =
        "users/" +
        u + "/";
        if(GetFileAttributes(folder.c_str()) != INVALID_FILE_ATTRIBUTES){
            print("User exists.");
            goto ldr;
        }
        std::cout << "Do you want to set a password? (Y/N): ";
        getline(std::cin, c);
        if(c=="N") {
            mkdir(folder.c_str());
            print("Done!");
            goto ldr;
        }
        if(c=="n") {
            mkdir(folder.c_str());
            goto ldr;
        }
        std::cout << "Enter password: ";
        getline(std::cin, p);
        if(p.empty()) {
            print("Please enter a password.");
            goto ldr;
        }
        mkdir(folder.c_str());
        std::string pwordfile =
        "users/" +
        u + "/.birbuser";
        char *cp = &p[0u];
        std::ofstream pass(pwordfile.c_str());

        pass << SHA256(cp) << std::endl;

        pass.close();
        print("Done!");
        goto ldr;
    };
    if(ldr=="dsktool"){
        print("This command is in development...");
        goto ldr;
    };
    if(ldr=="changepass"){
        std::string u;
        std::string p;
        std::string np;
        std::cout << "Please enter your username: ";
       getline(std::cin, u);
        std::string folder =
        "users/" +
        u + "/";
        if(GetFileAttributes(folder.c_str()) != INVALID_FILE_ATTRIBUTES){
        }
        else{
            print("User does not exist.");
            goto ldr;
        };
        std::string pwordfile =
        "users/" +
        u + "/.birbuser";
        ifstream ifile(pwordfile.c_str());
        if (ifile) {
        std::cout << "Please enter your old password: ";
        getline(std::cin, p);
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
            goto ldr;
        };
        }
        ifile.close();
        std::cout << "New password: ";
        getline(std::cin, np);
        remove(pwordfile.c_str());
        char *cp2 = &np[0u];
        std::ofstream pass(pwordfile.c_str());
        pass << SHA256(cp2) << std::endl;
        pass.close();
        print("Done!");
        goto ldr;
    }
    if(ldr == "deluser"){
        string u;
        string p;
        cout << "Username: ";
        getline(std::cin, u);
        std::string folder =
        "users/" +
        u + "/";
        if(GetFileAttributes(folder.c_str()) != INVALID_FILE_ATTRIBUTES){
        }
        else{
            print("User does not exist.");
            goto ldr;
        };
        std::string pwordfile =
        "users/" +
        u + "/.birbuser";
        ifstream ifile(pwordfile.c_str());
        if (ifile) {
        cout << "Password: ";
        getline(std::cin, p);
        char *cp = &p[0u];
        std::ifstream ifs (pwordfile.c_str());
        std::string s;
        getline (ifs, s, (char) ifs.eof());
        ifs.close();
        std::string s1 = s.erase(64,3);
        std::string s2 = SHA256(cp);
        char *str1 = &s1[0u];
        char *str2 = &s2[0u];
        if(strcmp(str1, str2) != 0){
            print("Password is incorrect!");
            goto ldr;
        };
        }
        ifile.close();
        std::string folder2 =
        "users\\" +
        u + "\\";
        string dir = "del /f /q /s " + folder2 + ">nul";
        system(dir.c_str());
        string dir2 = "rd /q " + folder2 + ">nul";
        system(dir2.c_str());
        print("Done!");
        goto ldr;
    }
    if(ldr.empty()){
        goto ldr;
    }
    print("Invalid choice!");
    goto ldr;

}



