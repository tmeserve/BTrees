#include <iostream>

using namespace std;

// Reference:
// https://www.geeksforgeeks.org/count-the-number-of-binary-search-trees-present-in-a-binary-tree/?ref=rp

struct Node
{
    struct Node *left;
    struct Node *right;
    int data;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

struct Info
{
    int num_BST;
    int max;
    int min;
    bool isBST;
};

Info NumberOfBST(struct Node *root)
{
    if (root == NULL)
        return {0, -2147483647, 2147483647, true};

    if (root->left == NULL && root->right == NULL)
        return {1, root->data, root->data, true};
    
    Info L = NumberOfBST(root->left);

    Info R = NumberOfBST(root->right);

    Info bst;
    bst.min = min(root->data, (min(L.min, R.min)));
    bst.max = max(root->data, (max(L.max, R.max)));

    if (L.isBST && R.isBST && root->data > L.max && root->data < R.min)
    {
        bst.isBST = true;
        bst.num_BST = 1 + L.num_BST + R.num_BST;
    }
    else
    {
        bst.isBST = false;
        bst.num_BST = L.num_BST + R.num_BST;
    }

    return bst;
}

int main()
{
    struct Node *root = new Node(5);
    root->left = new Node(9);
    root->right = new Node(3);
    root->left->left = new Node(6);
    root->right->right = new Node(4);
    root->left->left->left = new Node(8);
    root->left->left->right = new Node(7);

    Info rootInfo = NumberOfBST(root);

    cout << rootInfo.num_BST << endl;
}