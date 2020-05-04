#include <iostream>
#include "Tree.h"
using namespace std;

int main() 
{
  typedef BNode<float> b_node;
  typedef Tree<b_node> b_tree;

  b_tree tree(4);
  
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(4);
  tree.insert(5);
  tree.insert(6);
  tree.insert(10.2);
  tree.insert(12);
  tree.insert(15);
  tree.insert(22);
  
  cout << endl << "1 = true, 0 = false" << endl;
  cout << "Buscando 1: " << tree.find(1) << endl;
  cout << "Buscando 2: " << tree.find(2) << endl;
  cout << "Buscando 3: " << tree.find(3) << endl;
  cout << "Buscando 4: " << tree.find(4) << endl;
  cout << "Buscando 5: " << tree.find(6) << endl;
  cout << "Buscando 6: " << tree.find(6) << endl;
  cout << "Buscando 10.2: " << tree.find(10.2) << endl;
  cout << "Buscando 12: " << tree.find(12) << endl;
  cout << "Buscando 15: " << tree.find(15) << endl;
  cout << "Buscando 22: " << tree.find(22) << endl;
  cout << "Buscando 0: " << tree.find(0) << endl;

  cout << endl << "Imprimiendo b-tree:" << endl;
  cout << tree << endl;

  return 0;
}
