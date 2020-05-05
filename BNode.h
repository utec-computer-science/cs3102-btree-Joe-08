#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <vector>
#include <cmath>
#include "Macros.h"

template <typename T>
class BNode {
  public:
    typedef T value_t;
    typedef std::vector<value_t> container_t;
    typedef std::vector<BNode*> pcontainer_t;
    typedef typename std::vector<value_t>::iterator iterator_t; 

    unsigned int order;
    container_t data;
    pcontainer_t children;
    bool leaf;

    BNode(unsigned int order = 1):order(order), 
    leaf(false) {
      data.reserve(order);
      children.reserve(order + 1);
    }

    void insert(value_t key, value_t *val, BNode*& node) {
      if (leaf == false) {
        int i = 0;

        while (i < data.size() && key > data[i]) i++;

        children[i]->insert(key, val, node);

        if (node == nullptr) return;
        if (data.size() < order - 1) {
          data.insert(data.begin() + i, *val);
          children.insert(children.begin() + i + 1, node);
          node = nullptr;
        } else {
          data.insert(data.begin() + i, *val);
          children.insert(children.begin() + i + 1, node);
          split(val, node);
        }
      } else {
        iterator_t it;
        it = lower_bound(data.begin(), data.end(), key);

        int m = std::ceil(order / 2) - 1;

        data.insert(it, key);

        if (data.size() == order) {
          node = new BNode(order);
          node->leaf = true;

          *val = this->data[m];

          for (int i = m + 1; i < order; i++)
            node->data.push_back(this->data[i]);

          this->data.resize(m);
        }
      }
    }
  
    void split(value_t *val, BNode*& node) {
      node = new BNode(order);

      int m = std::ceil(order / 2) - 1;
      *val = this->data[m];

      for (int i = m + 1; i < order; i++)
        node->data.push_back(this->data[i]);

      this->data.resize(m);

      for (int i = m + 1; i <= order; i++)
        node->children.push_back(this->children[i]);

      this->children.resize(m + 1);
    }

    BNode* makeNewRoot(value_t val, BNode *node) {
      BNode* root = new BNode(order);

      root->data.push_back(val);

      root->children.push_back(this);
      root->children.push_back(node);
      return root;
    }

    bool find(value_t val) {
      int i = 0;
      while (i < data.size() && data[i] < val) i++;

      if (data[i] == val) return true;

      if (leaf) return false;

      return children[i]->find(val);
    }

    ~BNode(void) {}
};

#endif
