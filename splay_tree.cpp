#include "splay_tree.h"
#include <climits>

long long Node::rotations = 0;
long long Node::splaySteps = 0;

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

Node* lastVisited(Node* root, int key) {
    Node* cur = root;
    Node* last = nullptr;
    while (cur != nullptr) {
        last = cur;
        if (key == cur->key) break;
        if (key < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    return last;
}

// вставка
Node* insert(Node* root, int key) {
    if (root==nullptr) return new Node(key);  // если пустое дерево
        
    Node* last = lastVisited(root, key);
    root = splay(root, last);            // ближайший узел - в корень
    if (root->key == key) return root;  // если дубликат - ничего не делаем

    Node* node = new Node(key);
    if (key < root->key) {          // если новый узел левее корня
        node->left  = root->left;   // его левое поддерево - старое левое
        if (node->left != nullptr) node->left->parent = node;
        node->right = root;         // корень уходит вправо
        root->parent = node;
        root->left  = nullptr;      // обнуляем, иначе двойная ссылка
    } else {                        // если новый узел правее корня
        node->right = root->right;  // правое поддерево - старое правое
        if (node->right != nullptr) node->right->parent = node;
        node->left  = root;         // корень уходит влево
        root->parent = node;
        root->right = nullptr;      // обнуляем, иначе двойная ссылка
    }
    return node;    // новый корень
}

// поиск
Node* find(Node* root, int key) {
    if (root==nullptr) return nullptr;  // если дерево пустое
    Node* last = lastVisited(root, key);
    root = splay(root, last);    // ближайший узел - в корень
    return (root->key == key) ? root : nullptr; // возвращаем указатель, если значение ровно key, иначе возвращаем nullptr
}

// удаление
Node* remove(Node* root, int key) {
    if (root==nullptr) return nullptr;  // если пустое дерево

    Node* last = lastVisited(root, key);
    root = splay(root, last);            // ближайший узел - в корень
    if (root->key != key) return root;  // такого key нет

    Node* leftSub  = root->left;    // запоминаем левое
    Node* rightSub = root->right;   // запоминаем правое
    delete root;    // удаляем корень

    if (leftSub==nullptr) {
        if (rightSub != nullptr) rightSub->parent = nullptr;
        return rightSub;  // если левого нет - возвращаем правое
    }

    // Максимум левого поддерева - в корень. У него справа пусто, туда и прицепим rightSub.
    leftSub->parent = nullptr;
    leftSub = splay(leftSub, lastVisited(leftSub, INT_MAX)); // поднимаем максимум левого поддерева
    leftSub->right = rightSub;
    if (rightSub != nullptr) rightSub->parent = leftSub;
    return leftSub;
}

int height(Node* root) {
    if (root == nullptr) return 0;
    int l = height(root->left);
    int r = height(root->right);
    return 1 + (l > r ? l : r);
}

int countNodes(Node* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void printStats(Node* root) {
    if (root == nullptr) {
        std::cout << "Tree is empty." << std::endl;
        return;
    }
    std::cout << "Height: " << height(root) << "\n";
    std::cout << "Nodes: " << countNodes(root) << "\n";
    std::cout << "Total rotations: " << Node::rotations << std::endl;
    std::cout << "Total splay steps: " << Node::splaySteps << std::endl;
}

Node* splay(Node* root, Node* x) {
    if (x == nullptr) return root;
    while (x->parent != nullptr) {
        Node* p = x->parent;
        Node* g = p->parent;
        Node::splaySteps++;

        if (g == nullptr) { // Zig
            if (x == p->left) rotateRight(root, p);
            else rotateLeft(root, p);
        }
        else if (x == p->left && p == g->left) { // Zig-Zig
            rotateRight(root, g);
            rotateRight(root, p);
        }
        else if (x == p->right && p == g->right) { // Zig-Zig
            rotateLeft(root, g);
            rotateLeft(root, p);
        }
        else if (x == p->right && p == g->left) { // Zig-Zag
            rotateLeft(root, p);
            rotateRight(root, g);
        }
        else { // Zig-Zag
            rotateRight(root, p);
            rotateLeft(root, g);
        }
    }
    return x; // x теперь корень
}
