#pragma once
#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;

    static long long rotations; // Счетчик поворотов
    static long long splaySteps; // Счетчик шагов подъема

    Node(int k);
};

// Объявления функций
void rotateRight(Node*& root, Node* x);
void rotateLeft(Node*& root, Node* x);
void clear(Node*& root);
void printStats(Node* root);
int height(Node* root);
int countNodes(Node* root);
Node* lastVisited(Node* root, int key);
Node* insert(Node* root, int key);
Node* find(Node* root, int key);
Node* remove(Node* root, int key);
Node* splay(Node* root, Node* x);
