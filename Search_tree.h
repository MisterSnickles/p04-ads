template <class Record>
class Search_tree: public Binary_tree<Record> {
public:
   Error_code insert(const Record &new_data);
   Error_code remove(const Record &old_data);
   Error_code tree_search(Record &target) const;
protected:
   // Auxiliary functions
   Error_code search_and_insert(Binary_node<Record>* &sub_root, const Record &new_data);
   Error_code search_and_delete(Binary_node<Record>* &sub_root, const Record &target);
   Binary_node<Record>* search_for_node(Binary_node<Record>* sub_root, const Record &target) const;
};


template <class Record>
Error_code Search_tree<Record>::insert(const Record &new_data)
{
   return search_and_insert(this->root, new_data);
}


template <class Record>
Error_code Search_tree<Record>::search_and_insert(
           Binary_node<Record> *&sub_root, const Record &new_data)
{
   if (sub_root == NULL) {
      sub_root = new Binary_node<Record>(new_data);
      return success;
   }
   else if (new_data < sub_root->data)
      return search_and_insert(sub_root->left, new_data);
   else if (new_data > sub_root->data)
      return search_and_insert(sub_root->right, new_data);
   else return duplicate_error;
}


template <class Record>
Error_code Search_tree<Record>::remove(const Record &target)
/*
Post: If a Record with a key matching that of target belongs to the
      Search_tree, a code of success is returned, and the corresponding node
      is removed from the tree.  Otherwise, a code of not_present is returned.
Uses: Function search_and_destroy
*/
{
   return search_and_delete(this->root, target);
}


template <class Record>
Error_code Search_tree<Record>::search_and_delete(
           Binary_node<Record>* &sub_root, const Record &target)
/*
Pre:  sub_root is either NULL or points to a subtree of the Search_tree.
Post: If the key of target is not in the subtree, a code of not_present
      is returned.  Otherwise, a code of success is returned and the subtree
      node containing target has been removed in such a way that
      the properties of a binary search tree have been preserved.
Uses: Functions search_and_delete recursively
*/
{
   if (sub_root == NULL)
      return not_present;
   else if (sub_root->data == target) {
      if (sub_root->right == NULL) { // No right child
         Binary_node<Record> *to_delete = sub_root;  //  Remember node to delete at end.
         sub_root = sub_root->left;
         delete to_delete;
         to_delete = nullptr;
      } else if (sub_root->left == NULL) { // No left child
         Binary_node<Record> *to_delete = sub_root;  //  Remember node to delete at end.
         sub_root = sub_root->right;
         delete to_delete;
         to_delete = nullptr;
      } else { // subroot has two children
         // search for the immediate predecessor 
         Binary_node<Record> *predecessor_node = sub_root->left; 
         while (predecessor_node->right != NULL) { 
            predecessor_node = predecessor_node->right;
         }
         // replace the target with the immediate predecessor
         sub_root->data = predecessor_node->data;  
         // delete the redundant immediate predecessor
         search_and_delete(sub_root->left, sub_root->data);
      }
   } else if (target < sub_root->data)
      return search_and_delete(sub_root->left, target);
   else
      return search_and_delete(sub_root->right, target);
   return success;
}


template <class Record>
Error_code Search_tree<Record>::tree_search(Record &target) const
/*
Post: If there is an entry in the tree whose key matches that in target,
      the parameter target is replaced by the corresponding record from
      the tree and a code of success is returned.  Otherwise
      a code of not_present is returned.
Uses: function search_for_node
*/
{
   Error_code result = success;
   Binary_node<Record> *found = search_for_node(this->root, target);
   if (found == NULL)
      result = not_present;
   else
      target = found->data;
   return result;
}


template <class Record>
Binary_node<Record> *Search_tree<Record>::search_for_node(
            Binary_node<Record>* sub_root, const Record &target) const
{
   if (sub_root == NULL || sub_root->data == target) return sub_root;
   else if (sub_root->data < target)
      return search_for_node(sub_root->right, target);
   else return search_for_node(sub_root->left, target);
}


