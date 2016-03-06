#include "mergesort.h"
#include <list>
#include <numeric>
#include <random>


http://www.lindonslog.com/linux-unix/c-merge-sort-algorithm/

vector<int> merge_sort(const vector<int>& input)
{
    if(input.size()<=1) return input;
    vector<int> output(input.size());
 
    //Split Vector//
    int midpoint=0.5*input.size();
    vector<int> input_left(input.begin(),input.begin()+midpoint);
    vector<int> input_right(input.begin()+midpoint,input.end());
 
    input_left=merge_sort(input_left);
    input_right=merge_sort(input_right);
    merge(input_left.begin(),input_left.end(),input_right.begin(),input_right.end(),output.begin());
 
    return output;
}
 
int main(){
 
    //Create unsorted vector of ints
    vector<int> unsorted(40);
    iota(unsorted.begin(),unsorted.end(),-20);
    shuffle(unsorted.begin(),unsorted.end(),default_random_engine());
 
    //Perform merge_sort//
    vector<int> sorted=merge_sort(unsorted);
 
    //Display results//
    cout << "Unsorted: " <<  endl;
    for(auto value:unsorted)  cout << value << " ";
    cout <<  endl;
    cout << "Sorted: " <<  endl;
    for(auto value:sorted)  cout << value << " ";
    cout <<  endl;
 
}
 