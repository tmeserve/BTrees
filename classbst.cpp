#include <iostream>

using namespace std;

// Reference:
// https://gist.github.com/harish-r/a7df7ce576dda35c9660
// https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/

class BinarySearchTree
{

    class node
    {
        public:
            int data;
            node *left;
            node *right;
    };

    int order;

    node *root;

    node* makeEmpty(node *t)
    {
        if (t == NULL)
            return NULL;
        
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        
        return NULL;
    };

    node* insert(node *t, int x)
    {
        if (t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if (x < t->data)
            t->left = insert(t->left, x);
        else if (x > t->data)
            t->right = insert(t->right, x);
        
        return t;
    }

    node* findMin(node *t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        return findMin(t->left);
    }

    node* findMax(node *t)
    {
        if (t == NULL)
            return NULL;
        else if (t->right == NULL)
            return t;
        return findMax(t->right);
    }

    node* remove(node *t, int x)
    {
        node *temp;
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            t->left = remove(t->left, x);
        else if (x > t->data)
            t->right = remove(t->right, x);
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->right, t->data);
        }
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void preorder(node *t)
    {
        if (t == NULL)
            return;
        cout << t->data << " ";
        preorder(t->left);
        preorder(t->right);
    }

    void inorder(node *t)
    {
        if (t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    void postorder(node *t)
    {
        if (t == NULL)
            return;
        postorder(t->left);
        postorder(t->right);
        cout << t->data << " ";
    }

    node* find(node *t, int x)
    {
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            return find(t->left, x);
        else if (x > t->data)
            return find(t->right, x);
        return t;
    }

    public:
        BinarySearchTree()
        {
            root = NULL;
            order = 0;
        }

        ~BinarySearchTree()
        {
            root = makeEmpty(root);
            order = 0;
        }

        void insert(int x)
        {
            root = insert(root, x);
        }

        void remove(int x)
        {
            root = remove(root, x);
        }

        void changeOrder(int _order)
        {
            order = _order;
        }

        void display()
        {
            if (order == 0)
                preorder(root);
            else if (order == 1)
                inorder(root);
            else if (order == 2)
                postorder(root);
            else
                cout << "Please enter a value from 0-2\n0: Preorder\n1: Inorder\n2: Postorder";
            cout << endl;
        }

        void displayAll()
        {
            cout << "Pre Order\n";
            preorder(root);
            cout << endl << "In Order\n";
            inorder(root);
            cout << endl << "Post Order\n";
            postorder(root);
        }

        void search(int x)
        {
            root = find(root, x);
        }

};

int main()
{
    BinarySearchTree t;
    t.insert(20);
    t.insert(25);
    t.insert(15);
    t.insert(10);
    t.insert(30);

    t.displayAll();
    cout << endl;

    t.remove(20);
    t.displayAll();
    cout << endl;

    t.remove(25);
    t.displayAll();
    cout << endl;
    
    t.remove(30);
    t.displayAll();
    cout << endl;
}