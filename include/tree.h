// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>

class PMTree {
 public:
  struct Node {
    char znach;
    std::vector<std::unique_ptr<Node>> vecCH;
    explicit Node(char v) : znach(v) {}
  };
  explicit PMTree(const std::vector<char>& el);
  ~PMTree() = default;
  std::vector<std::vector<char>> getAllPerms() const;
  std::vector<char> getPerm1(int num) const;
  std::vector<char> getPerm2(int num) const;
 private:
  std::unique_ptr<Node> root;
  int tPerm;
  void buildTree(Node* p, const std::vector<char>& rem);
  void collectPerms(const Node* n, std::vector<char>& cur,
                   std::vector<std::vector<char>>& res) const;
  bool getPermByTraversal(const Node* n, int& remaining,
                         std::vector<char>& res) const;
  bool getPermByNavigation(const Node* n, int remaining,
                          std::vector<char>& res) const;
  int factorial(int n) const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
