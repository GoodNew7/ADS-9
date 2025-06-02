// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
 public:
  struct Node {
    char val;
    std::vector<Node*> children;
    explicit Node(char v) : val(v) {}
    ~Node() { for (auto c : children) delete c; }
  };

  explicit PMTree(const std::vector<char>& elems);
  ~PMTree();

  Node* getRoot() const { return root_; }

 private:
  Node* root_;
  void buildTree(Node* node, std::vector<char> remaining);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
