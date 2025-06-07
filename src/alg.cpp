// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <algorithm>
#include  <memory>
#include  <vector>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& el) {
  if (el.empty()) {
    root = nullptr;
    tPerm = 0;
    return;
  }
  tPerm = factorial(el.size());
  root = std::make_unique<Node>('\0');
  for (char oneMoreEl : el) {
    root->vecCH.push_back(std::make_unique<Node>(oneMoreEl));
  }
  for (auto& child : root->vecCH) {
    std::vector<char> rem;
    for (char oneMoreEl : el) {
      if (oneMoreEl != child->znach) {
        rem.push_back(oneMoreEl);
      }
    }
    buildTree(child.get(), rem);
  }
}

void PMTree::buildTree(Node* parent, const std::vector<char>& rem) {
  if (rem.empty()) {
    return;
  }
  for (char oneMoreEl : rem) {
    parent->vecCH.push_back(std::make_unique<Node>(oneMoreEl));
    std::vector<char> newRem;
    for (char e : rem) {
      if (e != oneMoreEl) {
        newRem.push_back(e);
      }
    }
    buildTree(parent->vecCH.back().get(), newRem);
  }
}

std::vector<std::vector<char>> PMTree::getAllPerms() const {
  std::vector<std::vector<char>> res;
  if (!root) return res;
  std::vector<char> cur;
  for (const auto& child : root->vecCH) {
    collectPerms(child.get(), cur, res);
  }
  return res;
}

void PMTree::collectPerms(const Node* n, std::vector<char>& cur,
                         std::vector<std::vector<char>>& res) const {
  cur.push_back(n->znach);
  if (n->vecCH.empty()) {
    res.push_back(cur);
  } else {
    for (const auto& child : n->vecCH) {
      collectPerms(child.get(), cur, res);
    }
  }
  cur.pop_back();
}

std::vector<char> PMTree::getPerm1(int num) const {
  if (num < 1 || num > tPerm || !root) {
    return {};
  }
  std::vector<char> res;
  int rem = num;
  for (const auto& child : root->vecCH) {
    if (getPermByTraversal(child.get(), rem, res)) {
      return res;
    }
  }
  return {};
}

bool PMTree::getPermByTraversal(const Node* n, int& rem,
                               std::vector<char>& res) const {
  res.push_back(n->znach);
  if (n->vecCH.empty()) {
    rem--;
    if (rem == 0) {
      return true;
    }
  } else {
    for (const auto& child : n->vecCH) {
      if (getPermByTraversal(child.get(), rem, res)) {
        return true;
      }
    }
  }
  res.pop_back();
  return false;
}

std::vector<char> PMTree::getPerm2(int num) const {
  if (num < 1 || num > tPerm || !root) {
    return {};
  }
  std::vector<char> res;
  int rem = num - 1;
  for (const auto& child : root->vecCH) {
    int chPerms = factorial(root->vecCH.size() - 1);
    if (rem < chPerms) {
      res.push_back(child->znach);
      if (getPermByNavigation(child.get(), rem, res)) {
        return res;
      }
      break;
    }
    rem -= chPerms;
  }
  return res;
}

bool PMTree::getPermByNavigation(const Node* n, int rem,
                                std::vector<char>& res) const {
  if(n->vecCH.empty()) {
    return true;
  }
  int chPerms = factorial(n->vecCH.size() - 1);
  for (const auto& child : n->vecCH) {
    if (rem < chPerms) {
      res.push_back(child->znach);
      return getPermByNavigation(child.get(), rem, res);
    }
    rem -= chPerms;
  }
  return false;
}

int PMTree::factorial(int n) const {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  return tree.getAllPerms();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  return tree.getPerm1(num);
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  return tree.getPerm2(num);
}

