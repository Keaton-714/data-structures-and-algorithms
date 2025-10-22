#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stack>
#include "avl.hpp"
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

// Helpers
int getBalance(AvlNode* node)
{
  int lh = node->left ? node->left->height : -1; // if not nullptr return height else -1
  int rh = node->right ? node->right->height : -1;
  return lh - rh;
}

void updateHeight(AvlNode* node)
{
  int lh = node->left ? node->left->height : -1;
  int rh = node->right ? node->right->height : -1;
  node->height = 1 + max(lh, rh);
}

// Rotations
AvlNode* leftLeft(AvlNode* node) // BF = 2 & 1
{
  AvlNode* newRoot = node->left;
  node->left = newRoot->right;
  newRoot->right = node;
  updateHeight(node);
  updateHeight(newRoot);
  return newRoot;
}
AvlNode* rightRight(AvlNode* node) // BF = -2 & -1
{
  AvlNode* newRoot = node->right;
  node->right = newRoot->left;
  newRoot->left = node;
  updateHeight(node);
  updateHeight(newRoot);
  return newRoot;
}
AvlNode* leftRight(AvlNode* node) // BF = 2 -1
{
  node->left = rightRight(node->left);
  return leftLeft(node);
}
AvlNode* rightLeft(AvlNode* node) // BF = -2 1
{
  node->right = leftLeft(node->right);
  return rightRight(node);
}

AvlNode* rebalance(AvlNode* node)
{
    int bf = getBalance(node);

    if (bf > 1) // Left heavy
    {
        // Checking child balance to see if single or double rotation
        if (getBalance(node->left) >= 0)
        {
            // Left Left case
            return leftLeft(node);
        }
        else
        {
            // Left-Right case
            return leftRight(node);
        }
    }
    if (bf < -1) // Right heavy
    {
        if (getBalance(node->right) <= 0)
        {
            // Right Right case
            return rightRight(node);
        }
        else
        {
            // Right Left case
            return rightLeft(node);
        }
    }
    return node; // balanced
}

void insert (const int & info, AvlNode * & root)
{
  bool found = false; // flag
  stack<AvlNode*> path;
  AvlNode* newNode = new AvlNode(info, nullptr, nullptr, 0);
  /*newNode->element = info;
  newNode->left = nullptr;
  newNode->right = nullptr;
  newNode->height = 0;*/

  AvlNode* current = root;
  if (current == nullptr) // root is newNode
  {
    root = newNode;
    found = true;
  }

  while(current != nullptr && !found)
  {
    path.push(current); // to keep track of the path we need to recalculate

    if (info < current->element)
    {
      if (current->left == nullptr)
      {
        current->left = newNode;
        found = true;
      }
      else
      {
        current = current->left;
      }
    }
    else if (info > current->element)
    {
      if (current->right == nullptr)
      {
        current->right = newNode;
        found = true;
      }
      else 
      {
        current = current->right;
      }
    }
    else // duplicate
    {
      cout << info << " already exists and was not added." << endl;
      delete newNode;
      return; // since we do not need to recalculate the tree
    }
  }

  while (!path.empty())
  {
    AvlNode* node = path.top();
    path.pop();

    updateHeight(node);
    AvlNode* newRoot = rebalance(node);

    if (!path.empty()) 
    {
      AvlNode* parent = path.top();
      if (parent->left == node)
      {
        parent->left = newRoot;
      }
      else
      { 
        parent->right = newRoot;
      }
    } 
      else 
      {
        root = newRoot;
      }
  }
}

void remove (const int & info, AvlNode * & root) 
{
  AvlNode* current = root;
  AvlNode* parent = nullptr;
  stack<AvlNode*> path; // Using a stack to store the nodes visited then sending it to the rebalance function
  bool found = false;

  if (current == nullptr)
  {
    cout << "AVL Tree is empty" << endl;
    return;
  }
  path.push(current); // pushing root into stack

  while(current != nullptr && !found)
  {
    if (current->element == info)
    {
      // Case 1: leaf node found
      if (current->left == nullptr && current->right == nullptr)
      {
        if (parent == nullptr) // root found
        {
          root = nullptr;
        }
        else if (parent->left == current)
        {
          parent->left = nullptr;
        }
        else 
        {
          parent->right = nullptr;
        }
        delete current; // clean up
        found = true;
      }
        // Case 2: only has a left child
        else if (current->right == nullptr)
        {
          if (parent == nullptr) // Node is root
          {
            root = current->left;
          }
          else if (parent->left == current)
          {
            parent->left = current->left; // skipping over the current node and linking since it was found
          }
          else
          {
            parent->right = current->left;
          }
          delete current; // clean up
          found = true;
        }
        // Case 3: only has a right child
        else if (current->left == nullptr)
        {
          if (parent == nullptr) // root
          {
            root = current->right;
          }
            else if (parent->left == current)
            {
              parent->left = current->right;
            }
            else
            {
              parent->right = current->right;
            }
            delete current; // clean up
            found = true;
        }
        // Case 4: Node has two children
        else
        {
          // Find successor (leftmost child of right subtree)
          AvlNode* successor = current->right;
          AvlNode* successorParent = current;
          //path.push(successor);
          while (successor->left != nullptr)
          {
            successorParent = successor;
            successor = successor->left;
          }
          
          if (successorParent != current)
          {
            path.push(successorParent);
          }
          // copy successors key to current node (overwrite it)
          current->element = successor->element;

          if (successor->right)
          {
              if (successorParent->left == successor)
              {
                  successorParent->left = successor->right;
              }
              else
              {
                  successorParent->right = successor->right;
              }
          }
          else
          {
              if (successorParent->left == successor)
              {
                  successorParent->left = nullptr;
              }
              else
              {
                  successorParent->right = nullptr;
              }
          }
          delete successor;
          found = true;
        }
    }
    // Case 5: Go right
    else if (current->element < info) // Case 5: go right
    {
      parent = current;
      current = current->right;
      if (current) path.push(current); // if not nullptr push into stack
    }
    else // Case 6: go left
    {
      parent = current;
      current = current->left;
      if (current) path.push(current); // if not nullptr push into stack
    }

  }
  while (!path.empty()) 
  {
    AvlNode* node = path.top();
    path.pop();

    updateHeight(node);
    AvlNode* newRoot = rebalance(node);

    if (!path.empty()) 
    {
        AvlNode* parent = path.top();
        if (parent->left == node)
        {
         parent->left = newRoot;
        }
        else
        {
         parent->right = newRoot;
        }
    }
    else 
    {
        root = newRoot;
    }
  }
}

void print(AvlNode *root, int level, int type) 
{
  if (root == NULL) 
  {
    return;
  }
  if (type == IS_ROOT) 
  {
    std::cout << root -> element << "\n";
  } 
  else 
  {
    for (int i = 1; i < level; i++) 
    {
      std::cout << "| ";
    }
    if (type == IS_LEFT) 
    {
      std::cout << "|l_" << root -> element << "\n";
    }
    else 
    {
      std::cout << "|r_" << root -> element << "\n";
    }
  }
  if (root -> left != NULL) 
  {
    print(root -> left, level + 1, IS_LEFT);
  }
  if (root -> right != NULL) 
  {
    print(root -> right, level + 1, IS_RIGHT);
  }
}
void print(AvlNode *root) 
{
  print(root, 0, IS_ROOT);
}


int main(int argc, const char * argv[]) 
{
  AvlNode *root = NULL;
  std::string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);
  std::string input;
  int data;
  while(std::cin >> input)
  {
    if (input == "insert")
    {
      std::cin>>data;
      insert(data, root);
    } else if(input == "delete")
    {
      std::cin>>data;
      remove(data, root);
    } 
    else if(input == "print")
    {
      print(root);
      std::cout << "\n";
    } else{
      std::cout<<"Data not consistent in file";
      break;
    }
  }
  return 0;
}
