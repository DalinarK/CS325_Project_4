//! \brief Performs a recursive merge sort on the given vector
//! \param vec The vector to be sorted using the merge sort
//! \return The sorted resultant vector after merge sort is
//! complete.
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
// got from https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Merge_sort
//! \brief Merges two sorted vectors into one sorted vector
//! \param left A sorted vector of integers
//! \param right A sorted vector of integers
//! \return A sorted vector that is the result of merging two sorted
//! vectors.
vector<int> merge(vector<int> &vec,const vector<int>& left, const vector<int>& right)
{
    // Fill the resultant vector with sorted results from both vectors
    vector<int> result;
    unsigned left_it = 0, right_it = 0;

    while(left_it < left.size() && right_it < right.size())
    {
        // If the left value is smaller than the right it goes next
        // into the resultant vector
        if(left[left_it] < right[right_it])
        {
            result.push_back(left[left_it]);
            left_it++;
        }
        else
        {
            result.push_back(right[right_it]);
            right_it++;
        }
    }

    // Push the remaining data from both vectors onto the resultant
    while(left_it < left.size())
    {
        result.push_back(left[left_it]);
        left_it++;
    }

    while(right_it < right.size())
    {
        result.push_back(right[right_it]);
        right_it++;
    }
    // //show merge process..
    //   int i;
    //   for(i=0;i<result.size();i++)
    //      {                                
    //      cout<<result[i]<<" ";
    //      }
    // // break each line for display purposes..
    //     cout<<"***********"<<endl; 

    //take a source vector and parse the result to it. then return it.  
    vec = result;               
    return vec;
}

vector<int> merge_sort(vector<int>& vec)
{
    // Termination condition: List is completely sorted if it
    // only contains a single element.
    if(vec.size() == 1)
    {
        return vec;
    }

    // Determine the location of the middle element in the vector
    std::vector<int>::iterator middle = vec.begin() + (vec.size() / 2);

    vector<int> left(vec.begin(), middle);
    vector<int> right(middle, vec.end());

    // Perform a merge sort on the two smaller vectors
    left = merge_sort(left);
    right = merge_sort(right);

    return merge(vec,left, right);
}


int main()
{
    // vector <int> unsorted = {5,4,6,1,3};
    // for (int i = 0; i < unsorted.size(); i++)
    // {
    //     cout << unsorted[i] << " ";
    // }
    // cout << "in main" << endl;

    // vector <int> sorted = merge_sort(unsorted);

    // for (int i = 0; i < sorted.size(); i++)
    // {
    //     cout << sorted[i] << " ";
    // }

    vector <int> test;
    test.resize(25);
    test[20] = 5;

    cout << test[20] << endl;
    return 0;
}