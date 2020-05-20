#include <iostream>

using namespace std;

// Reference:
// https://www.geeksforgeeks.org/total-number-of-possible-binary-search-trees-with-n-keys/?ref=rp

unsigned long int factorial(unsigned int n)
{
    unsigned long int res = 1;

    for (int i = 1; i <= n; ++i)
    {
        res *= i;
    }

    return res;
}

unsigned long int binomialCoeff(unsigned int n, unsigned int k)
{
    unsigned long int res = 1;

    if (k > n - k)
        k = n - k;
    
    for (int i = 0; i < k; ++i)
    {
        res *= (n - i);
        res /= (i + 1);
    }

    return res;
}

unsigned long int catalan(unsigned int n)
{
    unsigned long int c = binomialCoeff(2*n, n);

    return c/(n+1);
}

unsigned long int countBST(unsigned int n)
{
    // unsigned long int count = catalan(n);

    return catalan(n);
}

unsigned long int countBT(unsigned int n)
{
    unsigned long int count = catalan(n);

    return count * factorial(n);
}

int main()
{
    int count1, count2, n = 10;

    count1 = countBST(n);
    count2 = countBT(n);

    cout << "Count of BST with " << n << " nodes is " << count1 << endl;
    cout << "Count of binary trees with " << n << " node is " << count2 << endl;
}