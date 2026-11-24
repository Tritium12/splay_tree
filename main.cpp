#include "splay_tree.h"
#include <iostream>

int main() {
    Node* root = new Node(10);
    root->left = new Node(5);
    root->left->parent = root;

    std::cout << "Before: root = " << root->key 
              << ", left = " << root->left->key << "\n";

    rotateRight(root, root->left); // Поднимаем 5 наверх

    std::cout << "After: root = " << root->key 
              << ", right = " << root->right->key << "\n";
    std::cout << "Rotations: " << Node::rotations << "\n";

    if (root->right->parent == root && root->right != nullptr) {
        std::cout << "Parent pointers OK.\n";
    } else {
        std::cout << "ERROR: parent pointers broken!\n";
    }

    clear(root);
    return 0;
}
