#include "splay_tree.h"

long long Node::rotations = 0;

Node::Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}


void rotateRight(Node*& root, Node* x) {
    if (x == nullptr || x->left == nullptr) return;
    Node* y = x->left;

    x->left = y->right;
    if (y->right != nullptr) y->right->parent = x;

    y->parent = x->parent;

    if (x->parent != nullptr) {
        if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
    } else {
        root = y;
    }

    y->right = x;
    x->parent = y;

    Node::rotations++;
}
void rotateLeft(Node*& root, Node* x) {
    if (x == nullptr || x->right == nullptr) return;
    Node* y = x->right;

    x->right = y->left;
    if (y->left != nullptr) y->left->parent = x;

    y->parent = x->parent;

    if (x->parent != nullptr) {
        if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
    } else {
        root = y;
    }

    y->left = x;
    x->parent = y;

    Node::rotations++;
}


void clear(Node*& root) {
    if (root == nullptr) return;
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
}

void printStats(Node* root) {
    if (root == nullptr) {
        std::cout << "Tree is empty." << std::endl;
        return;
    }
    std::cout << "Total rotations: " << Node::rotations << std::endl;
}