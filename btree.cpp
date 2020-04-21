#include <iostream>
#include <vector> 
#include <cmath>
#include <queue>

template <typename T>
class SS_Traits{
public:
  typedef T  value_t;
  typedef std::vector<value_t> container_t;
  typedef typename container_t::iterator iterator_t;
  
  class simple_search{
  public:
    int operator() (container_t a, value_t v){
      for (int i = 0; i < a.size(); i++)
        if (a[i] == v) return i;
      return -1;
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
  bool leaf;

  BNode(void):order(S), leaf(false) {
    keys.reserve(order);
    ptrs.reserve(order + 1);
  }

  ~BNode(void){}
  
  bool find(value_t val) {
    int i = 0;
    while (i < keys.size() && val > keys[i])
      i++;

    if (keys[i] == val) return true;

    if (leaf) return false;

    return ptrs[i]->find(val);
  }
  
  
  void insert(value_t key, value_t* val, BNode<T,S>*& node) {
    if (leaf == false) {
      int i = 0;

      while (i < keys.size() && key > keys[i]) i++;

      ptrs[i]->insert(key, val, node);

      if (node == nullptr) return;
      if (keys.size() < order - 1) {
        keys.insert(keys.begin() + i, *val);
        ptrs.insert(ptrs.begin() + i + 1, node);
        node = nullptr;
      } else {
        keys.insert(keys.begin() + i, *val);
        ptrs.insert(ptrs.begin() + i + 1, node);
        split(val, node);
      }
    } else {
      iterator_t it;
      it = lower_bound(keys.begin(), keys.end(), key);

      int m = std::ceil(order / 2) - 1;

      keys.insert(it, key);

      if (keys.size() == order) {
        node = new BNode<T,S>();
        node->leaf = true;

        *val = this->keys[m];

        for (int i = m + 1; i < order; i++)
          node->keys.push_back(this->keys[i]);

        this->keys.resize(m);
      }
    }
  }

  void split(value_t *val, BNode<T,S>*& node) {
    node = new BNode<T,S>();

    int m = std::ceil(order / 2) - 1;
    *val = this->keys[m];

    for (int i = m + 1; i < order; i++)
      node->keys.push_back(this->keys[i]);

    this->keys.resize(m);

    for (int i = m + 1; i <= order; i++)
      node->ptrs.push_back(this->ptrs[i]);

    this->ptrs.resize(m + 1);
  }

  BNode<T,S>* makeNewRoot(value_t val, BNode<T,S>* node) {
    BNode<T,S>* root = new BNode<T,S>();

    root->keys.push_back(val);

    root->ptrs.push_back(this);
    root->ptrs.push_back(node);
    return root;
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

  BTree(void) {
    root = new BNode<T,S>();
    root->leaf = true;
  }

  ~BTree(void){}

  void insert(const value_t& key = 0) {
    // TODO :: INSERT
    BNode<T,S> *newNode = nullptr;
    value_t val = 0;

    root->insert(key, &val, newNode);

    if (newNode != nullptr)
      root = root->makeNewRoot(val, newNode);
  }

  bool find(const value_t val = 0) const{
    // TODO :: SEARCH
    // search(x); inside each page
    if (root == nullptr) return false;
    return root->find(val);
  }
  
  void printTree() {
    printTree(root);
  }

  void printTree(BNode<T,S> *node) { //lvl order print
    if (root == nullptr) return;
    
    std::queue<BNode<T,S>*> q;

    q.push(node);

    while (!q.empty()) {
      int size = q.size();

      while (size > 0) {
        BNode<T,S> *lvlNode = q.front();
        
        for (int i = 0; i < lvlNode->keys.size(); i++) {
          if (lvlNode->leaf == false) 
            std::cout << "  ";
          std::cout << lvlNode->keys[i] << " ";
        }
        
        q.pop();

        for (int i = 0; i < lvlNode->ptrs.size(); i++) 
          if (lvlNode->ptrs[i] != nullptr) 
            q.push(lvlNode->ptrs[i]);

        std::cout << "  ";
        size--;
      }
      std::cout << std::endl;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, BTree<T,S> tree){
    tree.printTree();// (out)
    // IN PRE POST LEVEL ORDER
    return out;
  }

};

int main() {
  typedef BS_Traits<int> btrait_t;
  BTree<btrait_t,4> tree;
  std::cout << tree.find(10) << std::endl;
  std::cout << tree << std::endl;

  typedef SS_Traits<float> strait_t;
  BTree<strait_t,4> stree; 
  
  stree.insert(1);
  std::cout << "Insert 1" << std::endl << stree << std::endl;
  stree.insert(2);
  std::cout << "Insert 2" << std::endl << stree << std::endl;
  stree.insert(3);
  std::cout << "Insert 3" << std::endl << stree << std::endl;
  stree.insert(4);
  std::cout << "Insert 4" << std::endl << stree << std::endl;
  stree.insert(5);
  std::cout << "Insert 5" << std::endl << stree << std::endl;
  stree.insert(6);
  
  std::cout << stree.find(1) << std::endl;
  std::cout << stree.find(2) << std::endl;
  std::cout << stree.find(3) << std::endl;
  std::cout << stree.find(4) << std::endl;
  std::cout << stree.find(5) << std::endl;
  std::cout << stree.find(6) << std::endl;
  
  std::cout << std::endl << stree << std::endl;
}

