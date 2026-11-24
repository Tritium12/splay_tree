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

// вставка
Node* insert(Node* root, int key) {
    if (root==nullptr) return new Node{key, nullptr, nullptr};  // если пустое дерево
        
    root = splay(root, key);            // ближайший узел - в корень
    if (root->key == key) return root;  // если дубликат - ничего не делаем

    Node* node = new Node{key, nullptr, nullptr};
    if (key < root->key) {          // если новый узел левее корня
        node->left  = root->left;   // его левое поддерево - старое левое
        node->right = root;         // корень уходит вправо
        root->left  = nullptr;      // обнуляем, иначе двойная ссылка
    } else {                        // если новый узел правее корня
        node->right = root->right;  // правое поддерево - старое правое
        node->left  = root;         // корень уходит влево
        root->right = nullptr;      // обнуляем, иначе двойная ссылка
    }
    return node;    // новый корень
}

// поиск
Node* find(Node* root, int key) {
    if (root==nullptr) return nullptr;  // если дерево пустое
    root = splay(root, key);    // ближайший узел - в корень
    return (root->key == key) ? root : nullptr; // возвращаем указатель, если значение ровно key, иначе возвращаем nullptr
}

// удаление
Node* remove(Node* root, int key) {
    if (root==nullptr) return nullptr;  // если пустое дерево

    root = splay(root, key);            // ближайший узел - в корень
    if (root->key != key) return root;  // такого key нет

    Node* leftSub  = root->left;    // запоминаем левое
    Node* rightSub = root->right;   // запоминаем правое
    delete root;    // удаляем корень

    if (leftSub==nullptr) return rightSub;  // если левого нет - возвращаем правое

    // Максимум левого поддерева - в корень. У него справа пусто, туда и прицепим rightSub.
    leftSub = splay(leftSub, INT_MAX);
    leftSub->right = rightSub;
    return leftSub;
}

void printStats(Node* root) {
    if (root == nullptr) {
        std::cout << "Tree is empty." << std::endl;
        return;
    }
    std::cout << "Total rotations: " << Node::rotations << std::endl;
}

Node* splay(Node* root, Node* x) {
    if (!x) return root;
    while (x->parent) {
        Node* p = x->parent;
        Node* g = p->parent;
        Node::splaySteps++;

        if (!g) {
            if (x == p->left) root = rotateRight(p);
            else root = rotateLeft(p);
        }
        else if (x == p->left && p == g->left) {
            root = rotateRight(g);
            root = rotateRight(p);
        }
        else if (x == p->right && p == g->right) {
            root = rotateLeft(g);
            root = rotateLeft(p);
        }
        else if (x == p->right && p == g->left) {
            root = rotateLeft(p);
            root = rotateRight(g);
        }
        else {
            root = rotateRight(p);
            root = rotateLeft(g);
        }
    }
    return x; // x теперь корень
}
