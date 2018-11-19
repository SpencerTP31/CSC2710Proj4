// file binary.h

#ifndef BINARYTREE
#define BINARYTREE
int _count;

#include<iostream>
#include "btnode.h"
using namespace std;

template<class T>
class BinaryTree {
   friend class BSTree<T>;
   public:
      BinaryTree() 
      {
         root = 0;
      }

      ~BinaryTree(){}

      bool IsEmpty() const
      {
         return ((root) ? false : true);
      }

      bool Root(T& x) const;

      void MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right);

      void BreakTree(T& element, BinaryTree<T>& left, BinaryTree<T>& right);

      void PostOrder(void(*Visit)(BinaryTreeNode<T> *u))
      {
         PostOrder(Visit, root);
      }

      void PreOrder(void(*Visit)(BinaryTreeNode<T> *u))
      {
         PreOrder(Visit, root);
      }

      void InOrder(void(*Visit)(BinaryTreeNode<T> *u))
      {
          InOrder(Visit, root);
      }

      void PostOutput() 
      {
         PostOrder(Output, root); 
         cout << endl;
      }

      void PreOutput()
      {
          PreOrder(Output, root);
          cout << endl;
      }

      void InOutput()
      {
          InOrder(Output, root);
          cout << endl;
      }

      void Delete() 
      {
         PostOrder(Free, root); 
         root = 0;
      }

      int Height() const 
      {
         return Height(root);
      }

      int Size()
      {
         _count = 0; 
         PostOrder(Add1, root); 
         return _count;
      }
   private:
      BinaryTreeNode<T> *root;  // pointer to root

      void PostOrder(void(*Visit)
            (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);

      void PreOrder(void(*Visit)
            (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);

      void InOrder(void(*Visit)
            (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);

      static void Free(BinaryTreeNode<T> *t) 
      {
         delete t;
      }

      static void Output(BinaryTreeNode<T> *t)
      {
         cout << t->data << ' ';
      }

      static void Add1(BinaryTreeNode<T> *t) 
      {
         _count++;
      }

      int Height(BinaryTreeNode<T> *t) const;
};

template<class T>
bool BinaryTree<T>::Root(T& x) const
{
   // Return root data in x.
   // Return false if no root.
   if (root) {
      x = root->data;
      return true;
   }
   else 
      return false;  // no root
}

template<class T>
void BinaryTree<T>::MakeTree(const T& element,
          BinaryTree<T>& left, BinaryTree<T>& right)
{  
   // Combine left, right, and element to make new tree.
   // left, right, and this must be different trees.
   // create combined tree
   root = new BinaryTreeNode<T> (element, left.root, right.root);

   // deny access from trees left and right
   left.root = right.root = 0;
}


template<class T>
void BinaryTree<T>::BreakTree(T& element,
       BinaryTree<T>& left, BinaryTree<T>& right)
{
   // left, right, and this must be different trees.
   // check if empty
   if (!root) {
      cerr<<"Tree empty"<<endl;
      return; 
   }
   // break the tree
   element = root->data;
   left.root = root->lchildptr;
   right.root = root->rchildptr;

   delete root;
   root = 0;
}

/*PostOrder Function:
*      Function recursively calls itself in order to traverse the tree and put
*      it in proper order
*
*precondition:
*      The function uses the tree created in main and visits each node in the tree
*      to put it in post order
*
*post conditon:
*      Once the function has completed the tree will have been traversed in post order and
*      each node will have been visited
*/
template <class T>
void BinaryTree<T>::PostOrder(
           void(*Visit)(BinaryTreeNode<T> *u),
                        BinaryTreeNode<T> *t)
{// Postorder traversal.
   if (t) {
      PostOrder(Visit, t->lchildptr);
      PostOrder(Visit, t->rchildptr);
      Visit(t);
   }
}

/*PreOrder Function:
*      Function recursively calls itself in order to traverse the tree and put
*      it in proper order
*
*precondition:
*      The function uses the tree created in main and visits each node in the tree
*      to put it in pre order, using the visit function in the beginning
*
*post conditon:
*      Once the function has completed the tree will have been traversed in pre order and
*      each node will have been visited in correct order
*/
template <class T>
void BinaryTree<T>::PreOrder(
        void(*Visit)(BinaryTreeNode<T> *u),
        BinaryTreeNode<T> *t)
{
    if (t) {
        Visit(t);
        PreOrder(Visit, t->lchildptr);
        PreOrder(Visit, t->rchildptr);
    }
}

/*InOrder Function:
*      Function recursively calls itself in order to traverse the tree and put
*      it in proper order
*
*precondition:
*      The function uses the tree created in main and visits each node in the tree
*      to put it in in order, using the visit function in the inbetween the recursion
*
*post conditon:
*      Once the function has completed the tree will have been traversed in in order and
*      each node will have been visited in correct order
*/
template <class T>
void BinaryTree<T>::InOrder(
        void(*Visit)(BinaryTreeNode<T> *u),
        BinaryTreeNode<T> *t)
{
    if (t) {
        InOrder(Visit, t->lchildptr);
        Visit(t);
        InOrder(Visit, t->rchildptr);
    }
}


template <class T>
int BinaryTree<T>::Height(BinaryTreeNode<T> *t) const
{
   // Return height of tree *t.
   if (!t) 
      return 0;               // empty tree
   int hl = Height(t->lchildptr);  // height of left
   int hr = Height(t->rchildptr); // height of right
   if (hl > hr) 
      return ++hl;
   else 
      return ++hr;
}

#endif
