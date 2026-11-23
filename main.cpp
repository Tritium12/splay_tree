#include "splay_tree.h"
#include <iostream>

int main() {
    Node* root = new Node(10);
    root->left = new Node(5);
    root->left->parent = root;

    std::cout << "До поворота: корень = " << root->key 
              << ", левый ребенок = " << root->left->key << "\n";

    rotateRight(root, root); // Поднимаем 5 наверх

    std::cout << "После поворота: корень = " << root->key 
              << ", правый ребенок = " << root->right->key << "\n";
    std::cout << "Количество поворотов: " << Node::rotations << "\n";

    if (root->right->parent == root) {
        std::cout << "Указатели parent корректны!\n";
    } else {
        std::cout << "ОШИБКА: Указатели parent сломаны!\n";
    }

    clear(root);
    return 0;
}