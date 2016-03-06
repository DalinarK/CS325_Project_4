#include "quicksort.h"

// An iterative implementation of quick sort found at
// http://www.geeksforgeeks.org/iterative-quick-sort/
// adapted
 
// A utility function to swap two elements


void swap ( int* a, int* b )
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
/* This function is same in both iterative and recursive*/
int partition (int arr[], int l, int h, vector <int> arrAlt)
{
    int x = arr[h];
    int i = (l - 1);
    int temp;
 
    for (int j = l; j <= h- 1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap (&arr[i], &arr[j]);
            cout << "before swap" <<arrAlt[i];
            temp = arrAlt[i];
            arrAlt[i] = arrAlt[j];
            arrAlt[j] = temp;
            cout << " after swap" << arrAlt[i] << endl;
        }
    }
    swap (&arr[i + 1], &arr[h]);
    temp = arrAlt[i + 1];
    arrAlt[i + 1] = arrAlt[h];
    arrAlt[h] = temp;
    return (i + 1);
}
 
/* A[] --> Array to be sorted, l  --> Starting index, h  --> Ending index */
void quickSortIterative (int arr[], int l, int h, vector <int> arrAlt)
{
    // Create an auxiliary stack
    vector <int> stackAlt;
    // initialize top of stack
    int top = -1;

 
    stackAlt.push_back(l);
    top++;
    cout << "pushed" <<stackAlt.back() << endl;
    stackAlt.push_back(h);
    top++;
    cout << "pushed" << stackAlt.back() << endl;
 
    // Keep popping from stack while is not empty
    while ( top >= 0 )
    {
        // Pop h and l
        h = stackAlt[ top-- ];
        l = stackAlt[ top-- ];

        cout << "h is " << h << " " << l << endl;
 
        // Set pivot element at its correct position in sorted array
        int p = partition( arr, l, h, arrAlt);
 
        // If there are elements on left side of pivot, then push left
        // side to stack
        if ( p-1 > l )
        {
            stackAlt[ ++top ] = l;
            stackAlt[ ++top ] = p - 1;
        }
 
        // If there are elements on right side of pivot, then push right
        // side to stack
        if ( p+1 < h )
        {
            stackAlt[ ++top ] = p + 1;
            stackAlt[ ++top ] = h;
        }
    }
}
 
// A utility function to print contents of arr
void printArr( int arr[], int n, vector <int> arrAlt )
{
     cout << "size is" << arrAlt.size() << endl;
    int i;
    for ( i = 0; i < n; ++i )
    {
        printf( "%d ", arr[i] );
        // printf("Alt %d", arrAlt[i]);
    }
    cout << endl;
    for ( i = 0; i < n; ++i )
    {
        
        printf("%d " , arrAlt[i]);
    }
}
 
// Driver program to test above functions
int main()
{
    neighbors neightborhood; 

    vector <int> arrAlt = {4, 3, 5, 2, 1, 3, 2, 3};
    int arr[] = {4, 3, 5, 2, 1, 3, 2, 3};
    int n = sizeof( arr ) / sizeof( *arr );
    quickSortIterative( arr, 0, n - 1, arrAlt);
    printArr( arr, n, arrAlt );
    return 0;
}