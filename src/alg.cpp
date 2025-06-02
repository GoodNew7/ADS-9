// Copyright 2022 NNTU-CS
#include <vector>
#include <algorithm>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& elems) {
  root_ = new Node('\0');
  std::vector<char> sorted_elems = elems;
  std::sort(sorted_elems.begin(), sorted_elems.end());
  buildTree(root_, sorted_elems);
}

PMTree::~PMTree() {
  delete root_;
}

void PMTree::buildTree(Node* node, std::vector<char> remaining) {
  if (remaining.empty()) return;

  std::sort(remaining.begin(), remaining.end());
  for (size_t i = 0; i < remaining.size(); ++i) {
    char current = remaining[i];
    Node* child = new Node(current);
    node->children.push_back(child);

    std::vector<char> next = remaining;
    next.erase(next.begin() + i);
    buildTree(child, next);
  }
}

namespace {
void traverse(PMTree::Node* node, std::vector<char>& current,
              std::vector<std::vector<char>>& output) {
  if (node->val != '\0') current.push_back(node->val);

  if (node->children.empty()) {
    output.push_back(current);
  } else {
    for (auto* child : node->children) {
      traverse(child, current, output);
    }
  }

  if (node->val != '\0') current.pop_back();
}
} // namespace

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> buffer;
  traverse(tree.getRoot(), buffer, result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto all = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(all.size())) return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> symbols;
  for (auto* child : tree.getRoot()->children) {
    symbols.push_back(child->val);
  }

  int n = symbols.size();
  int64_t factorial = 1;
  for (int i = 2; i <= n; ++i) factorial *= i;

  if (num < 1 || num > factorial) return {};

  --num;
  std::vector<char> result;
  std::vector<char> pool = symbols;

  for (int i = n; i >= 1; --i) {
    int64_t fact = 1;
    for (int j = 2; j < i; ++j) fact *= j;

    int index = num / fact;
    result.push_back(pool[index]);
    pool.erase(pool.begin() + index);
    num %= fact;
  }

  return result;
}
