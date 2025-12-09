#ifndef RBTREE_H
#define RBTREE_H

#include "filesystem.h"

enum Color {
    RED,
    BLACK
};

struct RBNode {
    Entry data;      // directory entry (file or directory)
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
};

RBNode* createRBNode(const Entry& e);
void leftRotate(RBNode*& root, RBNode* x);
void rightRotate(RBNode*& root, RBNode* y);
void rbInsertFixup(RBNode*& root, RBNode* z);
void rbInsert(RBNode*& root, RBNode* z);
RBNode* rbSearch(RBNode* root, const char name[]);
void inorderPrint(RBNode* root);

#endif
