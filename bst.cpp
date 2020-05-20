#include <iostream>

using namespace std;

struct node
{
    int key;
    struct node *left;
    struct node *right;
};

// B Tree
struct node* newNode(int data)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));

    node->key = data;

    node->left = NULL;
    node->right = NULL;
    return (node);
}

// BST
void inorder(struct node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

node *constructTreeUtil(int pre[], int *preIndex, int low, int high, int size)
{
    if (*preIndex >= size || low > high)
        return NULL;
    
    node *root = newNode(pre[*preIndex]);
    *preIndex = *preIndex + 1;

    if (low == high)
        return root;

    int i;
    for (i = low; i <= high; ++i)
        if (pre[i] > root->key)
            break;
    
    root->left = constructTreeUtil(pre, preIndex, *preIndex, i - 1, size);
    root->right = constructTreeUtil(pre, preIndex, i, high, size);
    
    return root;
}

node *constructTree(int pre[], int size)
{
    int preIndex = 0;
    return constructTreeUtil(pre, &preIndex, 0, size - 1, size);
}

// BST
struct node* insert(struct node *root, int key)
{
    if (root == NULL)
        return newNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

// BST
struct node * minValuenode(struct node* node)
{
    struct node* current = node;

    while (current && current -> left != NULL)
        current = current->left;
    return current;
}

// BST
struct node* deleteNode(struct node* root, int key)
{
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValuenode(root->right);

        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int isIdentical(node *root1, node *root2)
{
    if (root1 == NULL && root2 == NULL)
        return 1;
    else if (root1 != NULL && root2 == NULL)
        return 0;
    else if (root1 == NULL && root2 != NULL)
        return 0;
    
    if (root1->key == root2->key && isIdentical(root1->left, root2->left) && isIdentical(root1->right, root2->right))
        return 1;
    return 0;
}

int main()
{
    // BST
    struct node *root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    cout << "Inorder traversal of the given tree \n";
    inorder(root);

    // cout << "\nDelete 20\n";
    // root = deleteNode(root, 20);
    // cout << "Inorder traversal of the modified tree \n";
    // inorder(root);

    // cout << "\nDelete 30\n";
    // root = deleteNode(root, 30);
    // cout << "Inorder traversal of the modified tree \n";
    // inorder(root);

    // cout << "\nDelete 50\n";
    // root = deleteNode(root, 50);
    // cout << "Inorder traversal of the modified tree \n";
    // inorder(root);
    // cout << endl;

    return 0;
}