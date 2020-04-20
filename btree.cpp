#include <iostream>
#include <vector> 
#include <cmath>

template <typename T>
class SS_Traits{
public:
  typedef T  value_t;
  typedef std::vector<value_t> container_t;
  typedef typename container_t::iterator iterator_t;
  
  class simple_search{
  public:
    int operator() (container_t a, value_t v){
      return 0;
    }
  };

  class post_order_print{
  public:
    void operator() (void){
      std::cout << "post order" << std::endl;
    }
  };

  typedef simple_search functor_t;
  typedef post_order_print print_t;
};

template <typename T>
class BS_Traits{
public:
  typedef T  value_t;
  typedef std::vector<value_t> container_t;
  typedef typename container_t::iterator iterator_t;
  
  class binary_search{
  public:
    int operator() (container_t a, value_t v){
      return 0;
    }
  };

  class pre_order_print{
  public:
    void operator() (void){
      std::cout << "pre order" << std::endl;
    }
  };

  typedef binary_search functor_t;
  typedef pre_order_print print_t;
};

template <typename T, int S> 
class BNode {
public:
  typedef typename T::value_t value_t;
  typedef typename T::container_t container_t;
  typedef typename T::iterator_t iterator_t;
  typedef std::vector< BNode<T,S>* > pcontainer_t;

  container_t keys;
  pcontainer_t ptrs;
  std::size_t  order;
  int n;
  bool leaf;

  BNode(void):order(S), n(0), leaf(false) {
    keys = container_t(order - 1, 0);
    ptrs = pcontainer_t(order, nullptr);

  }

  ~BNode(void){}
  
  void insertInNode(value_t val) {
    int i = n - 1;

    if (leaf) {
      while (i >= 0 && keys[i] > val) {
        keys[i+1] = keys[i];
        i--;
      }

      keys[i+1] = val;
      n++;
    } else {
      while (i >= 0 && keys[i] > val) i--;

      if (ptrs[i+1]->n == order - 1) {
        splitNode(i+1, ptrs[i+1]);
        if (keys[i+1] < val) i++;
      }
      ptrs[i+1]->insertInNode(val);
    }
  }

  void splitNode(int i, BNode<T,S>* node) {
    BNode<T,S>* newNode = new BNode<T,S>();
    newNode->leaf = node->leaf;
    newNode->n = std::ceil(order / 2) - 1;

    for (int j = 0; j < std::ceil(order / 2) - 1; j++) {
      newNode->keys[j] = node->keys[j+newNode->n+1];
      node->keys[j+newNode->n+1] = 0;
    }

    if (node->leaf == false) {
      for (int j = 0; j < std::ceil(order / 2); j++)
        newNode->ptrs[j] = node->ptrs[j+newNode->n];
    }

    node->n = std::ceil(order / 2) - 1;

    ptrs[i+1] = newNode;

    for (int j = n - 1; j >= i; j--)
      keys[j+1] = keys[j];

    keys[i] = node->keys[std::ceil(order/2)-1];
    node->keys[std::ceil(order/2)-1] = 0;

    n++;
  }
};

template <typename T, int S>
class BTree {
public: 
  typedef typename T::value_t value_t;
  typedef typename T::container_t container_t;
  typedef typename T::functor_t functor_t;
  typedef typename T::print_t print_t;

  BNode<T,S>* root;
  print_t print;
  functor_t search;

  BTree(void):root(nullptr){
  }

  ~BTree(void){}

  void insert(const value_t& val = 0){
    // TODO :: INSERT
    if (root == nullptr) {
      root = new BNode<T,S>(); 
      root->keys[0] = val;
      root->n = 1;
      root->leaf = true;
    } else {
      if (root->n == root->order - 1) {
        BNode<T,S> *ptr = new BNode<T,S>();
        ptr->ptrs[0] = root;
        ptr->splitNode(0, root); 
        
        int i = 0;
        if (ptr->keys[0] < val) i++;
        ptr->ptrs[i]->insertInNode(val);

        root = ptr;
      } else
        root->insertInNode(val);
    }
  }

  bool find(const value_t = 0) const{
    // TODO :: SEARCH
    // search(x); inside each page
    return false;
  }

  friend std::ostream& operator<<(std::ostream& out, BTree<T,S> tree){
    tree.print();// (out)
    // IN PRE POST LEVEL ORDER
    return out;
  }

};

int main() {
  typedef BS_Traits<int> btrait_t;
  BTree<btrait_t,4> tree;
  tree.find(10);
  std::cout<<tree<< std::endl;

  typedef SS_Traits<float> strait_t;
  BTree<strait_t,4> stree; 
  stree.insert(1);
  std::cout<<stree<< std::endl;
}

