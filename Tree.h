#ifndef TREE_H
#define TREE_H

#include "BNode.h"
#include "NodeTraits.h"
#include "TreeHelper.h"

template <typename Node>
class Tree {
  public:
    typedef Node node_t;
    typedef typename node_t::value_t value_t;

    node_t* root;
    unsigned int order;

    Tree(unsigned int order = 0):order(order) {
      root = new node_t(order);
      root->leaf = true;
    }

    void insert(const value_t &val) {
      add<NodeTraits<node_t, value_t>::flag_type>(&root, val, 
          order);
    }

    void print(std::ostream &out) {
      print<NodeTraits<node_t, value_t>::flag_type>(&root, 
          out);
    }

    bool find(const value_t &val) {
      return find<NodeTraits<node_t, value_t>::flag_type>(&root,
          val);
    }

    template <int Flag>
    void add(node_t**, const value_t&, unsigned int order);

    template <int Flag>
    void print(node_t**, std::ostream&);

    template <int Flag>
    bool find(node_t**, const value_t&);

    ~Tree(void) {}
};

template <typename Node>
std::ostream& operator<<(std::ostream &out, Tree<Node> tree) {
  tree.print(out);
  return out;
}

template <typename Node> template <int Flag>
void Tree<Node>::add(typename Tree<Node>::node_t **root, const 
    typename Tree<Node>::value_t &val, unsigned int order) {
  TreeHelper<Tree<Node>::node_t, Tree<Node>::value_t, 
    Flag>::insert(root, val, order);
}

template <typename Node> template <int Flag>
void Tree<Node>::print(typename Tree<Node>::node_t **root,
    std::ostream &out) {
  TreeHelper<Tree<Node>::node_t, Tree<Node>::value_t, 
  Flag>::print(root, out);
}

template <typename Node> template <int Flag>
bool Tree<Node>::find(typename Tree<Node>::node_t **root, const
    typename Tree<Node>::value_t &val) {
  return TreeHelper<Tree<Node>::node_t, Tree<Node>::value_t,
  Flag>::find(root, val);
}
#endif
