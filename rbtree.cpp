#include <iostream>
#include "rbtree.h"
#include "filesystem.h"

RBNode* createRBNode(const Entry& e) {
    RBNode* node = new RBNode;
    node->data = e;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

void leftRotate(RBNode*& root, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void rightRotate(RBNode*& root, RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == NULL) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

void rbInsertFixup(RBNode*& root, RBNode* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        RBNode* gp = z->parent->parent;
        if (z->parent == gp->left) {
            RBNode* y = gp->right; // uncle
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                rightRotate(root, gp);
            }
        } else {
            RBNode* y = gp->left; // uncle
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                leftRotate(root, gp);
            }
        }
    }
    if (root != NULL) {
        root->color = BLACK;
    }
}

void rbInsert(RBNode*& root, RBNode* z) {
    RBNode* y = NULL;
    RBNode* x = root;

    while (x != NULL) {
        y = x;
        int cmp = compareNames(z->data.name, x->data.name);
        if (cmp < 0) {
            x = x->left;
        } else if (cmp > 0) {
            x = x->right;
        } else {
            // duplicate name, do nothing
            return;
        }
    }

    z->parent = y;
    if (y == NULL) {
        root = z;
    } else {
        int cmp = compareNames(z->data.name, y->data.name);
        if (cmp < 0) {
            y->left = z;
        } else {
            y->right = z;
        }
    }

    rbInsertFixup(root, z);
}

RBNode* rbSearch(RBNode* root, const char name[]) {
    RBNode* curr = root;
    while (curr != NULL) {
        int cmp = compareNames(name, curr->data.name);
        if (cmp == 0) return curr;
        else if (cmp < 0) curr = curr->left;
        else curr = curr->right;
    }
    return NULL;
}

void inorderPrint(RBNode* root) {
    if (root == NULL) return;
    inorderPrint(root->left);
    std::cout << root->data.name;
    if (root->data.type == DIR_ENTRY) {
        std::cout << "/";
    }
    std::cout << "\n";
    inorderPrint(root->right);
}
