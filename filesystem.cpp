#include <iostream>
#include "filesystem.h"
#include "rbtree.h"

Directory* rootDir = NULL;
Directory* currentDir = NULL;

int compareNames(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0;
    if (a[i] == '\0') return -1;
    return 1;
}

void copyName(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

Directory* createDirectory(const char name[], Directory* parent) {
    Directory* dir = new Directory;
    dir->parent = parent;
    dir->childrenRoot = NULL;

    dir->self.type = DIR_ENTRY;
    copyName(dir->self.name, name);
    dir->self.dirPtr = dir;

    return dir;
}

void initFileSystem() {
    rootDir = createDirectory("/", NULL);
    currentDir = rootDir;
}

// Helper: search child by name in a directory
RBNode* findChild(Directory* dir, const char name[]) {
    return rbSearch(dir->childrenRoot, name);
}

// Helper: insert entry into directory's RB tree
void insertEntryInDirectory(Directory* dir, const Entry& e) {
    RBNode* z = createRBNode(e);
    rbInsert(dir->childrenRoot, z);
}

void fs_mkdir(const char name[]) {
    if (name[0] == '\0') {
        std::cout << "mkdir: missing operand\n";
        return;
    }

    // check if already exists
    RBNode* existing = findChild(currentDir, name);
    if (existing != NULL) {
        std::cout << "mkdir: cannot create directory '" << name
                  << "': File exists\n";
        return;
    }

    Directory* newDir = createDirectory(name, currentDir);
    insertEntryInDirectory(currentDir, newDir->self);
}
void fs_touch(const char name[]) {
    if (name[0] == '\0') {
        std::cout << "touch: missing file name\n";
        return;
    }

    // Check if something with this name already exists
    RBNode* existing = findChild(currentDir, name);
    if (existing != NULL) {
        std::cout << "touch: cannot create file '" << name
                  << "': File or directory exists\n";
        return;
    }

    Entry e;
    copyName(e.name, name);
    e.type = FILE_ENTRY;
    e.dirPtr = NULL;  // not a directory

    insertEntryInDirectory(currentDir, e);
}

void fs_ls() {
    inorderPrint(currentDir->childrenRoot);
}

void fs_cd(const char name[]) {
    if (name[0] == '\0') {
        return; // do nothing
    }

    // cd ..
    if (name[0] == '.' && name[1] == '.' && name[2] == '\0') {
        if (currentDir->parent != NULL) {
            currentDir = currentDir->parent;
        }
        return;
    }

    RBNode* node = findChild(currentDir, name);
    if (node == NULL || node->data.type != DIR_ENTRY) {
        std::cout << "cd: no such directory: " << name << "\n";
        return;
    }

    currentDir = node->data.dirPtr;
}

void printPathRec(Directory* dir) {
    if (dir->parent == NULL) {
        std::cout << "/";
        return;
    }
    printPathRec(dir->parent);
    if (dir != rootDir) {
        std::cout << dir->self.name << "/";
    }
}

void fs_pwd() {
    if (currentDir == rootDir) {
        std::cout << "/\n";
        return;
    }
    printPathRec(currentDir);
    std::cout << "\n";
}
