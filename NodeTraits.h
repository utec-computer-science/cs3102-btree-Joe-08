#ifndef NODE_TRAITS_H
#define NODE_TRAITS_H

#include <iostream>
#include "BNode.h"

template <typename Node, typename ValueNode>
struct NodeTraits {
  static const int flag_type = 0;
};

template <typename ValueNode>
struct NodeTraits<BNode<ValueNode>, ValueNode> {
  static const int flag_type = B_NODE_FLAGXX;
};

#endif
