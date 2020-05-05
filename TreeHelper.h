#ifndef TREE_HELPER_H
#define TREE_HELPER_H

#include <iostream>
#include <queue>
#include "BNode.h"

template <typename Node, typename ValueNode, int Flag>
struct TreeHelper {
  typedef Node node_t;
  typedef typename node_t::value_t value_t;

  static void insert(node_t **head, const value_t &val, 
      unsigned int order) {
    std::cout << "El tipo de dato no es compatible" << std::endl;
  }

  static void print(node_t **head, std::ostream &out) {
  }

  static bool find(node_t **head, const value_t &val) {
    return false;
  }
};

template <typename ValueNode>
struct TreeHelper<BNode<ValueNode>, ValueNode, B_NODE_FLAGXX> {
  typedef BNode<ValueNode> node_t;
  typedef typename node_t::value_t value_t;

  static void insert(node_t **head, const value_t &val,
      unsigned int order) {
    std::cout << "Insertando " << val 
              << " para un nodo B" << std::endl;
    node_t *nNode = nullptr;
    value_t v = 0;

    (*head)->insert(val, &v, nNode);
    
    if (nNode != nullptr)
      (*head) = (*head)->makeNewRoot(v, nNode);
  }

  static void print(node_t **head, std::ostream &out) {
    if ((*head)->data.size() == 0) return;
    
    std::queue<node_t*> q;

    q.push((*head));

    while (!q.empty()) {
      int size = q.size();

      while (size > 0) {
        node_t *lvlNode = q.front();
        
        for (int i = 0; i < lvlNode->data.size(); i++) {
          if (i == lvlNode->data.size() - 1)
            std::cout << lvlNode->data[i];
          else 
            std::cout << lvlNode->data[i] << "-";
        }
        
        q.pop();

        for (int i = 0; i < lvlNode->children.size(); i++) 
          if (lvlNode->children[i] != nullptr) 
            q.push(lvlNode->children[i]);

        std::cout << "  ";
        size--;
      }
      std::cout << std::endl;
    }
  }

  static bool find(node_t **head, const value_t &val) {
    if ((*head)->data.size() == 0) return false;
    return (*head)->find(val);
  }
};

#endif 
