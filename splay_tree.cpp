#include "splay_tree.h"

long long Node::rotations = 0;

Node::Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}