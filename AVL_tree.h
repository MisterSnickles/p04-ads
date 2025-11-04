template <class Record>
class AVL_tree : public Search_tree<Record>
{
public:
   Error_code insert(const Record &new_data);
   Error_code remove(const Record &old_data);

protected:
   //  Auxiliary functions
   Error_code avl_insert(Binary_node<Record> *&sub_root, const Record &new_data, bool &taller);
   Error_code avl_delete(Binary_node<Record> *&sub_root, const Record &target, bool &shorter);

   // changed left/right balance functions to return bool variable so they can communicate with avl_delete
   bool left_balance(Binary_node<Record> *&sub_root);
   bool right_balance(Binary_node<Record> *&sub_root);
   //----------------------------------------------------
   void rotate_left(Binary_node<Record> *&sub_root);
   void rotate_right(Binary_node<Record> *&sub_root);
};

template <class Record>
Error_code AVL_tree<Record>::insert(const Record &new_data)
/*
Post: If the key of new_data is already in the AVL_tree, a code
      of duplicate_error is returned.
      Otherwise, a code of success is returned and the Record new_data
      is inserted into the tree in such a way that the properties of
      an AVL tree are preserved.
Uses: avl_insert.
*/
{
   bool taller;

   return avl_insert(this->root, new_data, taller);
}

template <class Record>
Error_code AVL_tree<Record>::remove(const Record &target)
/*
Post: If a Record with a key matching that of target belongs to the
      AVL_tree, a code of success is returned, and the corresponding node
      is removed from the tree.  Otherwise, a code of not_present is returned.
Uses: Function search_and_destroy
*/
{
   bool shorter;
   return avl_delete(this->root, target, shorter);
}

template <class Record>
Error_code AVL_tree<Record>::avl_insert(Binary_node<Record> *&sub_root,
                                        const Record &new_data, bool &taller)
/*
Pre:  sub_root is either NULL or points to a subtree of the AVL_tree
Post: If the key of new_data is already in the subtree, a
      code of duplicate_error is returned.
      Otherwise, a code of success is returned and the Record new_data
      is inserted into the subtree in such a way that the
      properties of an AVL tree have been preserved.
      If the subtree is increased in height, the parameter taller is set to
      true; otherwise it is set to false.
Uses: Methods of struct AVL_node; functions avl_insert
      recursively, left_balance, and right_balance.
*/
{
   Error_code result = success;
   if (sub_root == NULL)
   {
      sub_root = new AVL_node<Record>(new_data);
      taller = true; // taller is true for every new node creation
   }
   else if (new_data == sub_root->data)
   {
      result = duplicate_error;
      taller = false;
   }
   // insert to LST
   else if (new_data < sub_root->data)
   {
      result = avl_insert(sub_root->left, new_data, taller);
      if (taller == true)
         switch (sub_root->get_balance())
         {
         case left_higher: // lh before insertion, now unbalanced
            left_balance(sub_root);
            taller = false;
            break;
         case equal_height:
            sub_root->set_balance(left_higher);
            break;
         case right_higher:
            sub_root->set_balance(equal_height);
            taller = false;
            break;
         }
   }
   // insert to RST
   else
   {
      result = avl_insert(sub_root->right, new_data, taller);
      if (taller == true)
         switch (sub_root->get_balance())
         {
         case left_higher:
            sub_root->set_balance(equal_height);
            taller = false;
            break;
         case equal_height:
            sub_root->set_balance(right_higher);
            break;
         case right_higher:
            right_balance(sub_root);
            taller = false;
            break;
         }
   }
   return result;
}

template <class Record>
bool AVL_tree<Record>::right_balance(Binary_node<Record> *&sub_root)
/*
Pre:  sub_root points to a subtree of an AVL_tree that
      is unbalanced on the right.
Post: The AVL properties have been restored to the subtree.
*/
{
   Binary_node<Record> *&right_tree = sub_root->right;

   switch (right_tree->get_balance())
   {
   // case right_higher: sigle left rotation
   // O  ub --> subroot
   //  \
   //   O  rh  --> right_tree
   //    \
   //     O
   case right_higher: //  single left rotation
      sub_root->set_balance(equal_height);
      right_tree->set_balance(equal_height);
      rotate_left(sub_root); // pointer adjustment
      return true;
   case equal_height: //  impossible case
      // This is a valid case for deletion, not an error
      sub_root->set_balance(right_higher);
      right_tree->set_balance(left_higher);
      rotate_left(sub_root);
      return false;

   case left_higher:
      Binary_node<Record> *sub_tree = right_tree->left;
      // set balance of sub_root and right_tree assuming rotation is done
      switch (sub_tree->get_balance())
      {
      case equal_height:
         sub_root->set_balance(equal_height);
         right_tree->set_balance(equal_height);
         break;
      case left_higher:
         sub_root->set_balance(equal_height);
         right_tree->set_balance(right_higher);
         break;
      case right_higher:
         sub_root->set_balance(left_higher);
         right_tree->set_balance(equal_height);
         break;
      }
      // set balance of sub_tree after rotation
      sub_tree->set_balance(equal_height);
      // perform actual rotation
      rotate_right(right_tree);
      rotate_left(sub_root);
      return true;
   }
   return true;
}

template <class Record>
void AVL_tree<Record>::rotate_left(Binary_node<Record> *&sub_root)
/*
Pre:  sub_root points to a subtree of the AVL_tree.
      This subtree has a nonempty right subtree.
Post: sub_root is reset to point to its former right child, and the former
      sub_root node is the left child of the new sub_root node.
*/
{
   if (sub_root == NULL || sub_root->right == NULL) //  impossible cases
      cout << "WARNING: program error detected in rotate_left" << endl;
   else
   {
      Binary_node<Record> *right_tree = sub_root->right;
      sub_root->right = right_tree->left;
      right_tree->left = sub_root;
      sub_root = right_tree;
   }
}

template <class Record>
void AVL_tree<Record>::rotate_right(Binary_node<Record> *&sub_root)
/*
Pre:  sub_root points to a subtree of the AVL_tree.
      This subtree has a nonempty left subtree.
Post: sub_root is reset to point to its former left child, and the former
      sub_root node is the right child of the new sub_root node.
*/
{
   // TODO 1
   if (sub_root == NULL || sub_root->left == NULL)
   {
      cout << "WARNING: program error detected in rotate_right" << endl;
   }
   else
   {
      Binary_node<Record> *pivot = sub_root->left;
      sub_root->left = pivot->right;
      pivot->right = sub_root;
      sub_root = pivot;
   }
}

template <class Record>
bool AVL_tree<Record>::left_balance(Binary_node<Record> *&sub_root)
/*
Pre:  sub_root points to a subtree of an AVL_tree that
      is doubly unbalanced on the left.
Post: The AVL properties have been restored to the subtree.
*/
{
   // TODO 2
   Binary_node<Record> *&left_tree = sub_root->left;

   switch (left_tree->get_balance())
   {

   // single right rotation
   case left_higher:
      sub_root->set_balance(equal_height);
      left_tree->set_balance(equal_height);
      rotate_right(sub_root); // pointer adjustment
      return true;

   case equal_height:
      // This is a valid case for deletion, not an error
      sub_root->set_balance(left_higher);
      left_tree->set_balance(right_higher);
      rotate_right(sub_root);
      return false;

   case right_higher:
      Binary_node<Record> *sub_tree = left_tree->right;

      switch (sub_tree->get_balance())
      {
      case equal_height:
         sub_root->set_balance(equal_height);
         left_tree->set_balance(equal_height);
         break;

      case right_higher:
         sub_root->set_balance(equal_height);
         left_tree->set_balance(left_higher);
         break;

      case left_higher:
         sub_root->set_balance(right_higher);
         left_tree->set_balance(equal_height);
         break;
      }

      // set balance of sub_tree after rotation
      sub_tree->set_balance(equal_height);

      // perform actual rotation
      rotate_left(left_tree);
      rotate_right(sub_root);
      return true;
   }
   return true;
}

template <class Record>
Error_code AVL_tree<Record>::avl_delete(Binary_node<Record> *&sub_root,
                                        const Record &target, bool &shorter)
{
   Error_code result = success;

   // TODO 3
   // if node is not found : base case
   if (sub_root == nullptr)
   {
      shorter = false;
      return result = not_present;
   }

   // 1. Recursive search for target
   // left subtree case
   if (target < sub_root->data)
   {
      result = avl_delete(sub_root->left, target, shorter);

      if (shorter) // Left side got shorter, check for rebalance
      {
         switch (sub_root->get_balance())
         {
         case left_higher: // Was left-heavy, now balanced
            sub_root->set_balance(equal_height);
            // shorter stays true
            break;
         case equal_height: // Was balanced, now right-heavy
            sub_root->set_balance(right_higher);
            shorter = false; // Height change absorbed
            break;
         case right_higher:                    // Was right-heavy, now unbalanced
            shorter = right_balance(sub_root); // Call rebalance
            break;
         }
      }
   }

   // right subtree case
   else if (target > sub_root->data)
   {
      result = avl_delete(sub_root->right, target, shorter);
      if (shorter) // Right side got shorter, check for rebalance
      {
         switch (sub_root->get_balance())
         {
         case right_higher: // Was right-heavy, now balanced
            sub_root->set_balance(equal_height);
            // shorter stays true
            break;
         case equal_height: // Was balanced, now left-heavy
            sub_root->set_balance(left_higher);
            shorter = false; // Height change absorbed
            break;
         case left_higher:                    // Was left-heavy, now unbalanced
            shorter = left_balance(sub_root); // Call rebalance
            break;
         }
      }
   }

   // 2. Target found: Perform deletion
   else
   {
      // declare temporary variable that allows for deletion
      Binary_node<Record> *to_delete = sub_root;
      shorter = true; // deletion causes height to potentially be shorter

      // case 1: no left child
      if (sub_root->left == nullptr)
      {
         // since left is null we want try to assign sub_root to sub_root right, and if it is
         // also nullptr, it will go to the else if case below
         sub_root = sub_root->right;
         delete to_delete;
         return result = success;
      }

      // case 2 : no right child
      else if (sub_root->right == nullptr)
      {
         sub_root = sub_root->left;
         delete to_delete;
         return result = success;
      }

      else // case 3 : two children
      {
         // find inorder successor node
         Binary_node<Record> *successor = sub_root->right;
         while (successor->left != nullptr)
         {
            successor = successor->left;
         }

         // copy the successor's data to the current node
         sub_root->data = successor->data;

         // recursively delete the successor from the right subtree
         result = avl_delete(sub_root->right, successor->data, shorter);

         // if the tree needs rebalancing
         if (shorter)
         {
            switch (sub_root->get_balance())
            {
            case right_higher: // Was right-heavy, now balanced
               sub_root->set_balance(equal_height);
               // shorter stays true
               break;
            case equal_height: // Was balanced, now left-heavy
               sub_root->set_balance(left_higher);
               shorter = false; // Height change absorbed
               break;
            case left_higher:                    // Was left-heavy, now unbalanced
               shorter = left_balance(sub_root); // Call rebalance
               break;
            }
         }
      }
   }
   return result;
}