template <class Entry>
class Binary_tree {
public:
   Binary_tree();
   bool empty() const;
   void preorder(void (*visit)(Entry &));
   void inorder(void (*visit)(Entry &));
   void postorder(void (*visit)(Entry &));

   int size() const;
   void clear();
   int height() const;

   void print() const; // A method to print out the tree using preorder

   Binary_tree(const Binary_tree<Entry> &original);
   Binary_tree<Entry>& operator =(const Binary_tree<Entry> &original);
   ~Binary_tree();
protected:
   // Auxiliary functions
   void recursive_preorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &));
   void recursive_inorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &));
   void recursive_postorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &));
   int recursive_size(Binary_node<Entry> *sub_root) const;
   void recursive_clear(Binary_node<Entry> *sub_root);
   int recursive_height(Binary_node<Entry> *sub_root) const;
   Binary_node<Entry>* recursive_copy(Binary_node<Entry> *sub_root);

   void recursive_preorder_print_node(Binary_node<Entry> *sub_root) const;

   // Data member
   Binary_node<Entry>* root;
};

template <class Entry>
Binary_tree<Entry>::Binary_tree()
/*
Post: An empty binary tree has been created.
*/
{
   root = NULL;
}

template <class Entry>
Binary_tree<Entry>::Binary_tree(const Binary_tree<Entry> &original) 
/*
Post: A new binary tree has been created with the same structure and content as those of original. 
Uses: The function recursive_copy 
*/
{
  root = recursive_copy(original.root);
}

template <class Entry>
Binary_tree<Entry>& Binary_tree<Entry>::operator =(const Binary_tree<Entry> &original) 
/*  
Post: The binary tree is assigned to copy a parameter 
*/
{
   Binary_tree<Entry> new_tree(original); 
   Binary_node<Entry>* temp_root = root;
   root = new_tree.root;
   new_tree.root = temp_root; // new tree root and its subtrees will be deleted by its destructor when this method returns
   return *this;
}

template <class Entry>
Binary_tree<Entry>::~Binary_tree() {
   clear();
}

template <class Entry>
bool Binary_tree<Entry>::empty() const
/*
Post: A result of true is returned if the binary tree is empty.
      Otherwise, false is returned.
*/
{
   return root == NULL;
}

template <class Entry>
void Binary_tree<Entry>::preorder(void (*visit)(Entry &))
/*
Post: The tree has been traversed in preorder sequence.
Uses: The function recursive_preorder
*/
{
   recursive_preorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::inorder(void (*visit)(Entry &))
/*
Post: The tree has been traversed in inorder sequence.
Uses: The function recursive_inorder
*/
{
   recursive_inorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::postorder(void (*visit)(Entry &))
/*
Post: The tree has been traversed in postorder sequence.
Uses: The function recursive_postorder
*/
{
   recursive_postorder(root, visit);
}

template <class Entry>
int Binary_tree<Entry>::size() const
/* 
Post: The number of entries in the binary tree is returned.
Uses: The function recursive_size
*/
{
   return recursive_size(root);
}


template <class Entry>
void Binary_tree<Entry>::clear()
/* 
Post: Dispose of all the nodes of the binary tree.
Uses: The function recursive_clear.
*/
{
   recursive_clear(root);
   root = NULL;
}

template <class Entry>
int Binary_tree<Entry>::height() const
/* 
Post: The height of the binary tree is returned.
Uses: The function recursive_height
*/
{
   return recursive_height(root);
}


template <class Entry>
void Binary_tree<Entry>::print() const{
/* 
Post: The tree has been traversed in preorder.  Each node and its two children is printed 
Uses: The function recursive_preorder_print_node
*/
   cout << endl;
   cout << "++++++++++++++++++++++" << endl;
   if(root == NULL)
      cout << "EMPTY TREE" << endl;
   else{
      if(root->left == NULL && root->right == NULL)
         cout << root->data << ":  -  -" << endl;

      recursive_preorder_print_node(root);
   }
   cout << "++++++++++++++++++++++" << endl;
   cout << endl;
}

// Functions

template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry> *sub_root,
                                            void (*visit)(Entry &))
/*
Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
Post: The subtree has been traversed in preorder sequence.
Uses: The function recursive_preorder recursively
*/
{
   if (sub_root != NULL) {
      (*visit)(sub_root->data);
      recursive_preorder(sub_root->left, visit);
      recursive_preorder(sub_root->right, visit);
   }
}

template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry> *sub_root,
                                           void (*visit)(Entry &))
/*
Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
Post: The subtree has been traversed in inorder sequence.
Uses: The function recursive_inorder recursively
*/
{
   if (sub_root != NULL) {
      recursive_inorder(sub_root->left, visit);
      (*visit)(sub_root->data);
      recursive_inorder(sub_root->right, visit);
   }
}

template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry> *sub_root,
                                             void (*visit)(Entry &))
/*
Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
Post: The subtree has been traversed in postorder sequence.
Uses: The function recursive_postorder recursively
*/
{
   if (sub_root != NULL) {
      recursive_postorder(sub_root->left, visit);
      recursive_postorder(sub_root->right, visit);
      (*visit)(sub_root->data);
   }
}

template <class Entry>
int Binary_tree<Entry>::recursive_size(Binary_node<Entry> *sub_root) const
/*
Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
Post: The number of entries in the subtree is returned.
Uses: The function recursive_size recursively
*/
{
   if (sub_root == NULL)
      return 0;
   else
      return 1 + recursive_size(sub_root->left) + recursive_size(sub_root->right);
}

template <class Entry>
void Binary_tree<Entry>::recursive_clear(Binary_node<Entry> *sub_root)
/*
Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
Post: All the nodes in the subtree are disposed of in postorder.
Uses: The function recursive_clear recursively
*/
{
   if (sub_root != NULL) {
      recursive_clear(sub_root->left);
      recursive_clear(sub_root->right);
      // Note that at this moment, sub_root->left and sub_root->right may be dangled pointers.
      delete sub_root;
   }
}

template <class Entry>
int Binary_tree<Entry>::recursive_height(Binary_node<Entry> *sub_root) const 
/*
Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
Post: the height of the subtree is returned.
Uses: The function recursive_height recursively
*/
{
   if (sub_root == NULL)
      return 0;
   else {
      int left_height = recursive_height(sub_root->left);
      int right_height = recursive_height(sub_root->right);
      if (left_height >= right_height) 
         return 1 + left_height;
      else
         return 1 + right_height;
   }
}   

template <class Entry>
Binary_node<Entry>* Binary_tree<Entry>::recursive_copy(Binary_node<Entry>* sub_root) 
/*
Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
Post: returns a pointer to the root of a new binary tree that has exactly the same structure and content as those of the subtree.
Uses: The function recursive_copy recursively
*/
{
   if (sub_root == NULL)
      return NULL;
   else {
      Binary_node<Entry>* new_sub_root = new Binary_node<Entry>(sub_root->data);
      new_sub_root->left = recursive_copy(sub_root->left);
      new_sub_root->right = recursive_copy(sub_root->right);
      return new_sub_root;
   }
}


template <class Entry>
void Binary_tree<Entry>::recursive_preorder_print_node(Binary_node<Entry> *sub_root) const
/*
Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
Post: The subtree has been traversed in preorder sequence.
Uses: The function recursive_preorder_print_node recursively
*/
{
   if (sub_root != NULL) {
      if(sub_root->left != NULL || sub_root->right != NULL){
         cout << sub_root->data << ":  ";
         if(sub_root->left != NULL)
            cout << sub_root->left->data << "  ";
         else
            cout << "-  "; // "-" represents no child
         if(sub_root->right != NULL)
            cout << sub_root->right->data << " ";
         else
            cout << "-  "; // "-" represents no child
         //cout << "; ";
         cout << endl;
      }
      recursive_preorder_print_node(sub_root->left);
      recursive_preorder_print_node(sub_root->right);
   }
}

