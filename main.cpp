#include "splay_tree.h"
#include <iostream>

int main() {
    // проверка поворота
    section("Rotation test");
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

    // проверка пустоты дерева
    section("Empty tree");
    Node* tree = nullptr;
    printStats(tree);

    // проверка вставки
    section("Insert 10, 20, 30");
    tree = insert(tree, 10);
    tree = insert(tree, 20);
    tree = insert(tree, 30);
    printStats(tree);
    cout << "Root: " << tree->key << "\n";

    // проверка поиска существующего ключа
    section("Find 10");
    tree = find(tree, 10);
    cout << "Root after find: " << tree->key << "\n";
    printStats(tree);

    // проверка поиска отсутствующего ключа
    section("Find missing 999");
    tree = find(tree, 999);
    printStats(tree);

    // проверка удаления существующего ключа
    section("Remove 20");
    tree = remove(tree, 20);
    printStats(tree);

    // проверка удаления отсутствующего ключа
    section("Remove missing 999");
    tree = remove(tree, 999);
    printStats(tree);

    // проверка повторной вставки
    section("Duplicate insert 30");
    tree = insert(tree, 30);
    printStats(tree);
    
    // проверка удаления корня
    section("Remove root");
    tree = remove(tree, tree->key);
    printStats(tree);

    // проверка удаления последнего узла
    section("Remove last node");
    tree = remove(tree, tree->key);
    printStats(tree);

    // проверка очистки
    section("Clear");
    clear(tree);
    printStats(tree);

    // проверка с возрастающей последовательностью
    section("Sorted insert 1..10");
    Node* sorted = nullptr;
    for (int i = 1; i <= 10; i++) sorted = insert(sorted, i);
    printStats(sorted);
    cout << "Root: " << sorted->key << "\n";
    clear(sorted);
    
    return 0;
}
