/*
 * HC.13.PostorderNoRecursion2.cpp
 *
 * Problem: Implement postorder traversal without recursion.
 *
 *  Created on: Jan 12, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>

using namespace std;

// Solution: Clearly we will have to implement recursion using stack
//
//          The main difference between recursion for postorder and stack is that recursion can
//          remember if one subtree has been explored or not. With two recursive calls back to back,
//          we know when to explore the right call stack and when both are done an we can process the
//          node, that is it is just following binary tree structure.
//
//          But simple stack is linear and one node in stack has only previous element. But in tree,
//          two element has one parent. So no direct replacement. We need to remember which child to
//          explore next or whether all of them has been explored and its time to process/print current.
//
//          The solution used here does it by inspecting where the last visited node relative to the
//          current node.
//
//          We maintain a stack of nodes which evolve exactly as the sequence of nodes that the
//          recursive algorithm calls.
//          When we get a non leaf node at the top of the stack we need to know if we are moving back
//          up the tree, and if so, which side of this non-leaf we are returning from.
//
//          So we will maintain a previous pointer and use that to determine which branch we are coming
//          from.
//          **Only thing is we should not push both left and right together then the previous can be in
//          left subtree when we pop a right node and we will not be able to figure where we came from.
//
// **Learning: Learned a lot regarding how to use smart pointers with containers.
//             STL containers always copy objects. So you cannot create container of references.
//             Instead, create container of raw pointers and then to get raw pointer from
//             unique_ptr use get() function.
//
//             For simple applications, moving the ownership to container using std::move() will work,
//             But not for complex cases.
//

struct BinaryTreeNode{
    int data;
    unique_ptr<BinaryTreeNode> left, right;

    //For unique_ptr initialization either use std::move function or take raw pointer and make unique pointer
    BinaryTreeNode (int a, unique_ptr<BinaryTreeNode> b, unique_ptr<BinaryTreeNode> c) : data(a), left(move(b)), right(move(c)) {}
};

typedef unique_ptr<BinaryTreeNode> UBTI;
typedef BinaryTreeNode BTI;

void PostorderNoRecursion(UBTI& root)
{
    stack<BTI *> path;
    BTI* prev = nullptr;

    path.push(root.get());

    cout << "Postorder: " << endl;

    while(!path.empty()) {
        BTI* curr = path.top();

        if(prev == nullptr || prev->left.get() == curr || prev->right.get() == curr) {  // Came from parent
            if(curr->left.get() != nullptr) {   // Traverse left
                path.push(curr->left.get());
            }
            else if(curr->right.get() != nullptr) {     // Traverse right when no left
                path.push(curr->right.get());
            } else {                            // Leaf node, so visit current node
                cout << " " << curr->data ;
                path.pop();
            }
        }
        else if(prev == curr->left.get()) {     // Done with non-empty left. Now traverse right
            if(curr->right.get() != nullptr) {      // Traverse right when no left is done
                path.push(curr->right.get());
            } else {                            // Only left but no right child. Process this node now
                cout << " " << curr->data ;
                path.pop();
            }
        } else {    // Finished both left and right, so process current
            cout << " " << curr->data ;
            path.pop();
        }

        prev = curr;    // Set prev
    }
    cout << endl;
}


int main()
{
    UBTI root = UBTI(new BTI(1,
                        UBTI(new BTI(2,
                                UBTI(new BTI(4,
                                        UBTI(new BTI(8, nullptr, nullptr)),
                                        UBTI(new BTI(9, nullptr, nullptr)))),
                                UBTI(new BTI(5,
                                        nullptr,
                                        UBTI(new BTI(10,
                                                UBTI(new BTI(13, nullptr, nullptr)),
                                                nullptr)))))),
                        UBTI(new BTI(3,
                                UBTI(new BTI(6,
                                        nullptr,
                                        UBTI(new BTI(11,
                                                UBTI(new BTI(14,nullptr,
                                                        UBTI(new BTI(16,nullptr,nullptr)))),
                                                UBTI(new BTI(15,nullptr,nullptr)))))),
                                UBTI(new BTI(7,
                                        nullptr,
                                        UBTI(new BTI(12, nullptr, nullptr))))))));

    PostorderNoRecursion(root);

    //Postorder: 8, 9, 4, 13, 10, 5, 2, 16, 14, 15, 11, 6, 12, 7, 3, 1
}
