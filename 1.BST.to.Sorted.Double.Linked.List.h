/**
 * July's Selected Microsoft Classic 100 Interview Questions No. 1
 * 
 * Convert Binary Search Tree into a sorted Double Linked List.
 * 
 * For example,
 *      10
 *     /   \
 *    6    14
 *   / \   / \
 *  4   8 12  16
 * 
 * 4 = 6 = 8 = 10 = 12 = 14 = 16
 */

#include <iostream>

struct TreeNode {
    TreeNode( int v ) : val( v ), left( nullptr ), right( nullptr ) {}
    int val;
    TreeNode * left;
    TreeNode * right;
};

class BST {
public:
    BST() : root( nullptr ) {}
    void add( int v ) {
        add_impl( root, v );
    }
    
private:
    void add_impl( TreeNode * & p, int v ) {
        if ( root == nullptr ) {
            root = new TreeNode( v );
        } else {
            if ( v < root->val ) {
                add_impl( root->left, v );
            } else if ( v > root->val ) {
                add_impl( root->right, v );
            } else {
                std::cerr << "duplicated value found" << std::endl;
            }
        }    
    }
    TreeNode * root;
};

/**
 * The idea here is to in-order traversal the BST and connecting the nodes.
 */
class Solution {
public:
    TreeNode * toDoubleLinkedList( TreeNode * root ) {
        TreeNode * head = nullptr;
        TreeNode * tail = nullptr;
        to_double_linked_list_impl( root, head, tail );
        return head;
    }
private:
    void to_double_linked_list_impl(
        TreeNode * p, TreeNode * & head, TreeNode * & tail ) {
        if ( p == nullptr ) {
            head = nullptr;
            tail = nullptr;
            return;
        };
        
        TreeNode * head1 = nullptr;
        TreeNode * tail1 = nullptr;
        to_double_linked_list_impl( p->left, head1, tail1 );
        if ( head1 == nullptr ) head = p;
        else                    head = head1;
        p->left = tail1;
        if ( tail1 != nullptr ) tail1->right = p;
        
        TreeNode * head2 = nullptr;
        TreeNode * tail2 = nullptr;
        to_double_linked_list_impl( p->right, head2, tail2 );
        p->right = head2;
        if ( head2 != nullptr ) head2->left = p;
        if ( tail2 == nullptr ) tail = p;
        else                    tail = tail2;
    }
};

/**
 * Another solution from July
 */
class SolutionJuly {
public:
    TreeNode * toDoubleLinkedList( TreeNode * root ) {
        head = nullptr;
        curr = nullptr;
        to_double_linked_list_impl( root );
        return head;
    }
private:
    void to_double_linked_list_impl( TreeNode * p ) {
        if ( p == nullptr ) {
            return;
        };
        to_double_linked_list_impl( p->left );
        connect( p );
        to_double_linked_list_impl( p->right );
    }
    void connect( TreeNode * p ) {
        p->left = curr;
        if ( curr == nullptr ) {
            head = p;
        } else {
            curr->right = p;
        }
        curr = p;
    }
    
    TreeNode * head;
    TreeNode * curr;//tracking the running tail of the double linked list
};

