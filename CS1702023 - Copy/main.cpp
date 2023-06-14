#include <iostream>
#include "astar_euclid.cpp"
#include "uniform_cost.cpp"
#include "UC.cpp"
#include "ASED.cpp"
#include "ASMT.cpp"
#include <set>
using namespace std;
int menu(vector<int> &puzzle)
{
    int choice;
    cout << "SID: 862127298" << endl;
    cout << "\n";
    cout << "Here are your choices: " << endl;
    cout << "<1> Uniform Cost" << endl;
    cout << "<2> A* Missing Tile" << endl;
    cout << "<3> A* Euclid Distance" << endl;
    cout << "> ";
    cin >> choice;
    cout << "Enter puzzle " << endl;
    for (int i = 0; i < 9; i++)
    {
        int temp;
        cin >> temp;
        puzzle.push_back(temp);
    }
    return choice;
}
void choice(vector<int> &puzzle)
{
    // {1, 2, 3, 4, 5, 6, 8, 7, 0} shouldnt work
    // {8,7,1,6,0,2,5,4,3} hard puzzle
    // {8,6,7,2,5,4,3,0,1} hard puzzle 
    // uniform_c(puzzle); OLD VERSION
    // astart_euclid(puzzle); OLD VERSION
    // 8 7 1 6 0 2 5 4 3 Oh boy
    // 8 6 7 2 5 4 3 0 1 random online one
    // 1 2 3 4 5 6 8 7 0 impossible
    // 1 2 3 4 5 6 7 8 0 trivial
    // 1 2 0 4 5 3 7 8 6 easy
    // 1 2 3 4 5 6 7 0 8 very easy
    // 0 1 2 4 5 3 7 8 6 doable
    int pick = menu(puzzle);
    if (pick == 1)
    {
        uniform_cost(puzzle); // uniform cost
    }
    else if (pick == 2)
    {
        missing_tile(puzzle);
    }
    else if (pick == 3)
    {
        euclid_distance(puzzle); // a star with euclid distance heuristic
    }
    else
    {
        cout << "Invalid selection!" << endl;
    }
}

int main()
{
    vector<int> puzzle;
    choice(puzzle);
    return 0;
};