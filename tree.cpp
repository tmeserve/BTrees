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

void storeSorted(node *root, int arr[], int &i)
{
    if (root == NULL)
        return;
    storeSorted(root->left, arr, i);
    arr[i++] = root->key;
    storeSorted(root->right, arr, i);
}

node* insert(node *root, int key)
{
    if (root == NULL) return newNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    
    return root;
}

void treeSort(int arr[], int n)
{
    struct node *root = NULL;

    root = insert(root, arr[0]);

    for (int i = 1; i < n; i++)
        root = insert(root, arr[i]);
    
    int i = 0;
    storeSorted(root, arr, i);
}

struct node* search(struct node* root, int key)
{
    if (root == NULL || root->key == key)
        return root;
    
    if (root->key < key)
        return search(root->right, key);
    
    return search(root->left, key);
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

    /* Checks whether or not 2 B Trees are identical */
    // struct node *root1 = newNode(1);
    // struct node *root2 = newNode(1);

    // root1->left = newNode(3);
    // root1->right = newNode(8);
    // root1->left->left = newNode(2);
    // root1->left->right = newNode(4);

    // root2->left = newNode(3);
    // root2->right = newNode(8);
    // root2->left->left = newNode(2);
    // root2->left->right = newNode(4);

    // if (isIdentical(root1, root2))
    //     cout << "Both BSTs are identical" << endl;
    // else
    //     cout << "BSTs are not identical" << endl;

    /* Uses the Tree Sort algorithm */
    int arr[] = {5, 4, 7, 2, 11};
    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "Size of arr[0]: " << sizeof(arr[0]) << endl;

    treeSort(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    
    cout << endl;

    return 0;
}