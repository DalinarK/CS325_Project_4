#include <iostream>
#include <queue>
#include <vector>
 // used http://www.softwareandfinance.com/Visual_CPP/Merge_Sort_Iterative.html and adapted
void DoMerge(int numbers[], int left, int mid, int right)
{
    int temp[25];
    int i, left_end, num_elements, tmp_pos;
 
    left_end = (mid - 1);
    tmp_pos = left;
    num_elements = (right - left + 1);
 
    while ((left <= left_end) && (mid <= right))
    {
        if (numbers[left] <= numbers[mid])
            temp[tmp_pos++] = numbers[left++];
        else
            temp[tmp_pos++] = numbers[mid++];
    }
 
    while (left <= left_end)
        temp[tmp_pos++] = numbers[left++];
 
    while (mid <= right)
        temp[tmp_pos++] = numbers[mid++];
 
    for (i=0; i < num_elements; i++)
        numbers[right--] = temp[right];
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
 
        if(left < right)
        {
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
    int arr[] = { 3, 8, 7, 5, 2, 1, 9, 6, 4 };
    int len = sizeof(arr) / sizeof(arr[0]);
 
    MergeSortHelper(arr, len);
 
    for(int i = 0; i < len; i++)
        std::cout << arr[i] << " ";
 
      return 0;
  }