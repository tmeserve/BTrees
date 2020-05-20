#include <iostream>

using namespace std;

// Reference:
// https://www.geeksforgeeks.org/check-if-a-given-number-is-a-perfect-square-using-binary-search/?ref=rp

int checkPerfectSquare(long int N, long int start, long int last)
{
    long int mid = (start + last) / 2;

    if (start > last)
        return -1;
    
    if (mid * mid == N)
        return mid;
    
    else if (mid * mid > N)
        return checkPerfectSquare(N, start, mid - 1);
    
    else
        return checkPerfectSquare(N, mid + 1, last);
}

int main()
{
    long int N = 65;

    cout << checkPerfectSquare(N, 1, N) << endl;
}