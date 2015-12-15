#include <iostream>
#include "1.BST.to.Sorted.Double.Linked.List.h"

TreeNode * generate_a_sample_BST() {
    TreeNode * p = new TreeNode( 10 );
    p->left = new TreeNode( 6 );
    p->right = new TreeNode( 14 );
    p->left->left = new TreeNode( 4 );
    p->left->right = new TreeNode( 8 );
    p->right->left = new TreeNode( 12 );
    p->right->right = new TreeNode( 16 );
    return p;
}

void print_BST_list( TreeNode * head ) {
    std::cout << "head to tail: ";
    TreeNode * prev = nullptr;
    TreeNode * p = head;
    while ( p ) {
        std::cout << p->val << " ";
        prev = p;
        p = p->right;
    }
    std::cout << std::endl;
    
    std::cout << "tail to head: ";
    while ( prev ) {
        std::cout << prev->val << " ";
        prev = prev->left;
    }
    std::cout << std::endl;
}

void test_driver() {
    TreeNode * p = generate_a_sample_BST();
    
    Solution sln;
    TreeNode * head = sln.toDoubleLinkedList( p );
    print_BST_list( head );
}

void test_driver2() {
    TreeNode * p = generate_a_sample_BST();
    
    SolutionJuly sln;
    TreeNode * head = sln.toDoubleLinkedList( p );
    print_BST_list( head );
}

int main() {
    test_driver();
    test_driver2();
       
    return 0;
}
