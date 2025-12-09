#include <iostream>
#include "filesystem.h"

void executeCommand(char line[]) {
    char cmd[20];
    char arg[50];

    int i = 0;
    int j = 0;

    // extract command
    while (line[i] != ' ' && line[i] != '\0') {
        cmd[i] = line[i];
        i++;
    }
    cmd[i] = '\0';

    // skip spaces
    while (line[i] == ' ') {
        i++;
    }

    // extract argument
    while (line[i] != '\0') {
        arg[j] = line[i];
        j++;
        i++;
    }
    arg[j] = '\0';

    if (compareNames(cmd, "mkdir") == 0) {
        fs_mkdir(arg);
    } else if (compareNames(cmd, "ls") == 0) {
        fs_ls();
    } else if (compareNames(cmd, "cd") == 0) {
        fs_cd(arg);
    } else if (compareNames(cmd, "pwd") == 0) {
        fs_pwd();
    } else if (compareNames(cmd, "touch") == 0) {      
    fs_touch(arg);
    } else if (cmd[0] != '\0') {
        std::cout << "Unknown command: " << cmd << "\n";
    }
}

int main() {
    initFileSystem();

    char line[100];

    while (true) {
        std::cout << "> ";
        std::cin.getline(line, 100);

        if (compareNames(line, "exit") == 0) {
            break;
        }

        executeCommand(line);
    }

    return 0;
}
