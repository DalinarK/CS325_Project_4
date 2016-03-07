//! \brief Performs a recursive merge sort on the given vector
//! \param vec The vector to be sorted using the merge sort
//! \return The sorted resultant vector after merge sort is
//! complete.
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

struct Person
{
    // Left out making a constructor for simplicity's sake.
    int name;
};

// Sort Container by name function
bool sortByName(const Person &lhs, const Person &rhs) { return lhs.name < rhs.name; }
// A global const variable to hold how many people to ask for input for.
const unsigned numberOfPeople = 5;

int main()
{
    // Make a vector that holds 5 blank Person Objects
    vector<Person> people(numberOfPeople);

    string input;
    // This will ask for user input to populate the container
    // with 5 different indivuals.
    for (vector<Person>::size_type i = 0; i != numberOfPeople; ++i)
    {
        people[i].name = i + 10;
    }

    cout << "\n\n";

    // Sort by name
    sort(people.begin(), people.end(), sortByName);
    for (int i = 0; i < 5; i++)
        cout << people[i].name << " ";

    cout << endl;
    return 0;
}