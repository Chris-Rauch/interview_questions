#include "binaryTree.h"
#include <cstddef>
#include <iomanip>
#include <iostream>


/// @brief Determines the height difference of the roots two subtrees.
/// @param root The root of the tree or subtree.
/// @return The height difference of the root's subtrees as an int. 
int BinaryTree::_balanceFactor(node* root)
{
    if(root == nullptr) return 0;
    return _height(root->left) - _height(root->right);
}

/// @brief Inserts value into the container. See _insertNode().
/// @param value The value to be inserted.
/// @return None.
void BinaryTree::insert(const int &value)
{
    _root = _insertNode(_root, value);
    ++_size;
}

bool BinaryTree::remove(const int& value)
{
    if(_root == nullptr) return false;

    _removeNode(_root,value );

    return true;
}

/// @brief
BinaryTree::node* BinaryTree::_removeNode(node* root, const int& value)
{
    // end of the branch
    if(root == nullptr) return root;

    // recursively search for the value
    if(value > root->data)
    {
        root->right = _removeNode(root->right, value);
    }
    else if(value < root->data)
    {
        root->left = _removeNode(root->left, value);
    }
    // node was found. Delete it and replace it with successor if necessary
    else 
    {
        // no children
        if(root->right == nullptr && root->left ==nullptr)
        {
            delete root;
            return nullptr;
        }

        // left child
        else if(root->right == nullptr)
        {
            node* temp = root->left;
            delete root;
            return temp;
        }

        // right child
        else if (root->left == nullptr) 
        {
            node* temp = root->right;
            delete root;
            return temp;
        }

        // two children. Find the in order predecessor or successor
        else 
        {
            int balance = _balanceFactor(root);
            node* inOrder;
            if(balance > 1)
            {
                inOrder = _popBiggest(root->left); // in order predecessor
            }
            else 
            {
                inOrder = _popSmallest(root->right); // in order successor
            }

            // Replace the root's data with that of its successor
            root->data = inOrder->data;
            delete inOrder; // Delete the in-order predecessor/successor
        }
    }

    // update the height
    root->height = 1 + std::max(_height(root->left), _height(root->right));

    // rebalance if necessary
    return _rebalance(root);
}

/// @brief - Inserts value into to the tree. It rotates and self balances as 
/// necessary. Return the new root to the tree.
/// @param root - The root of the tree or subtree.
/// @param value - The value to be inserted.
/// @return The new root of the tree or subtree after insertion
BinaryTree::node* BinaryTree::_insertNode(node* root, const int& value)
{
    // found where the node should go. base case
    if(root == nullptr)
    {
        return new node(value);
    }

    if(root->data > value)
    {
        root->left = _insertNode(root->left, value);
    }
    else if (root->data < value)
    {
        root->right = _insertNode(root->right, value);
    }
    else
    {
        return root; // no duplicates
    }

    // begin updating heights of each ancestor node
    root->height = 1 + std::max(_height(root->left), _height(root->right));

    // rebalance if necessary
    return _rebalance(root);
}


/// @brief Return true if value is in the tree
bool BinaryTree::contains(const int &value)
{
    return _containsNode(_root, value);
}

/// @brief Performs a DFS with conditional branching.
/// @param root Starting node for the search. 
/// @param value The value that is being searched for
/// @return true if the value is found. Otherwise false.
bool BinaryTree::_containsNode(node *root, const int &value) 
{
    // base case
    if(root == nullptr) return false;

    // check which half to travers
    if(root->data > value)
    {
        return _containsNode(root->left, value);
    }
    else if(root->data < value)
    {
        return _containsNode(root->right, value);
    }
    else
    {
        return true;
    }
}

/// @brief Performs a right rotation on a given node. Designed to handle 
/// left-heavy trees.
/// @param root The root of the tree or subtree 
BinaryTree::node* BinaryTree::_rotateRight(node* root)
{
    if(root == nullptr || root->left == nullptr) return root;

    // perform rotation
    node* left = root->left;
    root->left = left->right;
    left->right = root;

    // update heights
    root->height = 1 + std::max(_height(root->left), _height(root->right));
    left->height = 1 + std::max(_height(left->left), _height(left->right));

    return left;
}

/// @brief Performs a left rotation on a given node. Designed to handle 
/// right-heavy trees.
BinaryTree::node* BinaryTree::_rotateLeft(node* root)
{
    if(root == nullptr || root->right == nullptr) return root;

    // perform left rotation
    node* right = root->right;
    root->right = right->left;
    right->left = root;

    // update heights
    root->height = 1 + std::max(_height(root->left), _height(root->right));
    right->height = 1 + std::max(_height(right->left), _height(right->right));

    return right;
}

/// @brief Finds the greatest value in the tree and returns it. It does not
/// release it from memory.
/// @param root A reference to the pointer pointing to root. Any changes to
/// root will change the structure of the tree.
BinaryTree::node* BinaryTree::_popBiggest(node*& root)
{
    // base case
    if(root == nullptr) return nullptr;

    // largest value found
    if(root->right == nullptr)
    {
        node* largest = root;
        root = root->left; // since root is a ref, this will actually change the tree's structure  
        return largest;
    }
    
    // otherwise keep searching
    node* largest = _popBiggest(root->right);

    // update height
    root->height = 1 + std::max(_height(root->left), _height(root->right));

    // rebalance if necessary
    root = _rebalance(root);

    return largest;
}

/// @brief Finds the smallest value in the tree and returns it. It does not
/// release it from memory.
/// @param root A reference to the pointer pointing to root. Any changes to
/// root will change the structure of the tree.
BinaryTree::node* BinaryTree::_popSmallest(node* root)
{
    // base case
    if(root == nullptr) return nullptr;

    // largest value found
    if(root->left == nullptr)
    {
        node* smallest = root;
        root = root->right; // since root is a ref, this will actually change the tree's structure  
        return smallest;
    }
    
    // otherwise keep searching
    node* smallest = _popBiggest(root->left);

    // update heights
    root->height = 1 + std::max(_height(root->left), _height(root->right));

    // rebalance if necessary
    root = _rebalance(root);

    return smallest;
}

BinaryTree::node* BinaryTree::_rebalance(node* root)
{
    if(root == nullptr) return nullptr;

    // check balance factor
    int balance = _balanceFactor(root);

    // tree is left heavy
    if(balance > 1)
    {
        node* leftChild = root->left;

        // right rotate
        if(_balanceFactor(leftChild) >= 0)
        {
            return _rotateRight(root);
        }
        // left right rotate
        else
        {
            root->left = _rotateLeft(root->left);
            return _rotateRight(root);
        }
    }
    // right heavy
    else if(balance < -1)
    {
        node* rightChild = root->right;

        // left rotate
        if(_balanceFactor(rightChild) <= 0)
        {
            return _rotateLeft(root);
        }
        // right left rotate
        else 
        {
            root->right = _rotateRight(rightChild);
            return _rotateLeft(root);
        }
    }

    // no rotation necessary
    return root;
}

/// @brief Deletes a branch. Releases from memory
/// @param root The tree or subtree to be deleted
/// @return 
void BinaryTree::_deleteBranch(node* root)
{
    if(root == nullptr) return;

    _deleteBranch(root->left);
    _deleteBranch(root->right);
    
    delete root;
}

/// @brief 
void BinaryTree::printTree()
{
    int height = _height(_root); // Get the height of the tree
    int indentSpace = (1 << height) - 1; // Initial indent space

    _printTree(_root, 0, indentSpace);
    std::cout << std::endl;
}

void BinaryTree::_printTree(node* root, int level, int indentSpace)
{
    if (root == nullptr) {
        return; // Base case
    }

    // Print the right child first (to go to the next level)
    _printTree(root->right, level + 1, indentSpace);

    // Print the current node
    if (level == 0) {
        std::cout << std::setw(indentSpace) << root->data << std::endl; // Root node
    } else {
        std::cout << std::setw(indentSpace) << root->data << std::endl; // Child nodes
    }

    // Print the left child
    _printTree(root->left, level + 1, indentSpace);
}