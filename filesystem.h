#ifndef FILESYSTEM_H
#define FILESYSTEM_H

// Forward declarations
struct Directory;
struct RBNode;

enum EntryType {
    FILE_ENTRY,
    DIR_ENTRY
};

struct Entry {
    char name[50];
    EntryType type;
    Directory* dirPtr; // valid if type == DIR_ENTRY
};

struct Directory {
    Entry self;              // this directory's own entry
    Directory* parent;       // parent directory (NULL for root)
    RBNode* childrenRoot;    // root of RB tree of children
};

// Global directory pointers
extern Directory* rootDir;
extern Directory* currentDir;

// String helpers
int compareNames(const char a[], const char b[]);
void copyName(char dest[], const char src[]);

// Directory helpers
Directory* createDirectory(const char name[], Directory* parent);
void initFileSystem();

// Filesystem commands
void fs_mkdir(const char name[]);
void fs_ls();
void fs_cd(const char name[]);
void fs_pwd();
void fs_touch(const char name[]);

#endif
