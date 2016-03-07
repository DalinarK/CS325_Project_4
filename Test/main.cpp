#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
 // used http://www.softwareandfinance.com/Visual_CPP/Merge_Sort_Iterative.html and adapted
void DoMerge(int numbers[], int left, int mid, int right)
{
    int temp[25];

    for (int i = 0; i < 25 ; i++)
    {
        temp[i] = 666;
    }

    for (int i = 0; i < 4; i++)
    {
        cout << numbers[i] << " ";
    }

    int i, left_end, num_elements, tmp_pos;
 
    left_end = (mid - 1);
    tmp_pos = left;
    num_elements = (right - left + 1);
 
    cout << "left " << left << " mid " << mid << " right " << right << endl;

    cout << "number of elements is " << num_elements << endl;

    while ((left <= left_end) && (mid <= right))
    {
        cout << "before position " << tmp_pos << " " << temp[tmp_pos] << endl;
        if (numbers[left] <= numbers[mid])
        {
            cout << "hit!" << endl;
            temp[tmp_pos++] = numbers[left++];
        }    
        else
            cout << "mid is " << mid << endl;
            temp[tmp_pos++] = numbers[mid++];
        cout << "after " << temp[tmp_pos-1] << endl;
    }
        
    while (left <= left_end)
        temp[tmp_pos++] = numbers[left++];
 
    while (mid <= right)
        temp[tmp_pos++] = numbers[mid++];
 
    
    for (i=0; i < num_elements; i++)
    {
        cout << "right is: " << right << endl;
        numbers[right--] = temp[right];
    }
        
}
 
void Merge_Sort_Recursive(int numbers[], int left, int right)
{
  int mid;
 
  if (right > left)
  {
    mid = (right + left) / 2;
    Merge_Sort_Recursive(numbers, left, mid);
    Merge_Sort_Recursive(numbers, (mid+1), right);
 
    DoMerge(numbers, left, (mid+1), right);
  }
}
 
struct MergePosInfo
{
    int left;
    int mid;
    int right;
};
 
void Merge_Sort_Iterative(int numbers[], int left, int right)
{
    int mid;
    if (right <= left)
        return;

    // cout << "initial L R:" << left << " " << right << endl;
 
    std::vector<std::pair<int, int> > list;
    std::vector<MergePosInfo> mlist;
    list.push_back(std::pair<int, int>(left, right));
 
    MergePosInfo info;
    while(1)
    {
        
        if(list.size() == 0)
            break;
 
        left = list.back().first;
        right = list.back().second;
        list.pop_back();
        mid = (right + left) / 2;
 
        // cout << "left: " << left << " right " << right << endl;
        if(left < right)
        {
            // cout << left << " " << right << " " << info.mid << endl;
            info.left = left;
            info.right = right;
            info.mid = mid + 1;
 
            mlist.push_back(info);
            list.push_back(std::pair<int, int>(left, mid));
            list.push_back(std::pair<int, int>((mid+1), right));
        }
    }
 
    for(int i = mlist.size() - 1; i >= 0; i--)
    {
        DoMerge(numbers, mlist[i].left, mlist[i].mid, mlist[i].right);
    }
}
 
void MergeSortHelper(int numbers[], int array_size)
{
    //Merge_Sort_Recursive(numbers, 0, array_size - 1);
    Merge_Sort_Iterative(numbers, 0, array_size - 1);
}
 
 
int main()
{
    int arr[] = {0, 4, 3, 1};
    int len = sizeof(arr) / sizeof(arr[0]);
 
    MergeSortHelper(arr, len);
 
    for(int i = 0; i < len; i++)
        std::cout << arr[i] << " ";
 
      return 0;
  }