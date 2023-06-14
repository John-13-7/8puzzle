#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <cmath>
using namespace std;
class Solve
{
public:
    vector<int> goal_state = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    vector<float> distance_vector;
    float distance_arr[4] = {10, 10, 10, 10}; // l,r,d,u
    int move_goal[4] = {-1, -1, -1, -1};      // l,r,d,u
    struct VectorHash
    {
        size_t operator()(const std::vector<int> &v) const
        {
            std::hash<int> hasher;
            size_t seed = 0;
            for (int i : v)
            {
                seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
    unordered_set<vector<int>, VectorHash> visited_nodes;
    priority_queue<vector<int>> queued_nodes;

    float get_coordinates(int space, int move)
    {
        int x1, x2, y1, y2;
        if (space == 0)
        {
            x1 = 1;
            y1 = 3;
        }
        else if (space == 1)
        {
            x1 = 2;
            y1 = 3;
        }
        else if (space == 2)
        {
            x1 = 3;
            y1 = 3;
        }
        else if (space == 3)
        {
            x1 = 1;
            y1 = 2;
        }
        else if (space == 4)
        {
            x1 = 2;
            y1 = 2;
        }
        else if (space == 5)
        {
            x1 = 3;
            y1 = 2;
        }
        else if (space == 6)
        {
            x1 = 1;
            y1 = 1;
        }
        else if (space == 7)
        {
            x1 = 2;
            y1 = 1;
        }
        else if (space == 8)
        {
            x1 = 3;
            y1 = 1;
        }
        else
        {
            cout << "This should not pop up" << endl;
        }

        // x2,y2
        if (move == 0)
        {
            x2 = 3;
            y2 = 1;
        }
        else if (move == 1)
        {
            x2 = 1;
            y2 = 3;
        }
        else if (move == 2)
        {
            x2 = 2;
            y2 = 3;
        }
        else if (move == 3)
        {
            x2 = 3;
            y2 = 3;
        }
        else if (move == 4)
        {
            x2 = 1;
            y2 = 2;
        }
        else if (move == 5)
        {
            x2 = 2;
            y2 = 2;
        }
        else if (move == 6)
        {
            x2 = 3;
            y2 = 2;
        }
        else if (move == 7)
        {
            x2 = 1;
            y2 = 1;
        }
        else if (move == 8)
        {
            x2 = 2;
            y2 = 1;
        }
        else
        {
            cout << "This should not pop up" << endl;
        }
        float dis = sqrt(pow((x2 - x1), 2) + (pow((y2 - y1), 2)));
        return dis;
    }

    void shift_moves(int space, vector<int> puzzle)
    {
        vector<int> puzzle_copy;
        int move;
        float g_distance;
        // left
        if (space == 1 || space == 2 || space == 4 || space == 5 || space == 7 || space == 8)
        {
            puzzle_copy = puzzle;
            move = puzzle_copy[space - 1];
            //move_goal[0] = move; // test this move goal, make sure not to visit it, if moving it takes it away from the goal state
            swap(puzzle_copy[space], puzzle_copy[space - 1]);
            if (visited_nodes.count(puzzle_copy) == 0)
            {
                queued_nodes.push(puzzle_copy);
            }
            g_distance = get_coordinates(space, move);
            distance_arr[0] = g_distance;
        }
        // right
        if (space == 0 || space == 1 || space == 3 || space == 4 || space == 6 || space == 7)
        {
            puzzle_copy = puzzle;
            move = puzzle_copy[space + 1];
            //move_goal[1] = move;
            swap(puzzle_copy[space], puzzle_copy[space + 1]);
            if (visited_nodes.count(puzzle_copy) == 0)
            {
                queued_nodes.push(puzzle_copy);
            }
            g_distance = get_coordinates(space, move);
            distance_arr[1] = g_distance;
        }
        // down
        if (space == 0 || space == 1 || space == 2 || space == 3 || space == 4 || space == 5)
        {
            puzzle_copy = puzzle;
            move = puzzle_copy[space + 3];
            //move_goal[2] = move;
            swap(puzzle_copy[space], puzzle_copy[space + 3]);
            if (visited_nodes.count(puzzle_copy) == 0)
            {
                queued_nodes.push(puzzle_copy);
            }
            g_distance = get_coordinates(space, move);
            distance_arr[2] = g_distance;
        }
        // up
        if (space == 3 || space == 4 || space == 5 || space == 6 || space == 7 || space == 8)
        {
            puzzle_copy = puzzle;
            move = puzzle_copy[space - 3];
            //move_goal[3] = move;
            swap(puzzle_copy[space], puzzle_copy[space - 3]);
            if (visited_nodes.count(puzzle_copy) == 0)
            {
                queued_nodes.push(puzzle_copy);
            }
            g_distance = get_coordinates(space, move);
            distance_arr[3] = g_distance;
        }

        //
        // bool isgoal[4] = {false, false, false, false};

        // get min distance

        vector<int> temp;
        for (int i = 0; i < 4; i++)
        {
            cout << "Distances: " << distance_arr[i] << ", ";
        }

        float min_val = *min_element(distance_arr, distance_arr + 4);
        cout << "min: " << min_val << endl;
        // also make sure that that the value you want to swap is not already in the goal state
        // so check the second swap value, and run it through a function to check if its already in its goal state or not
        if (min_val == distance_arr[0]) // left
        {
            temp = puzzle;
            swap(temp[space], temp[space - 1]);
            visited_nodes.insert(temp);
        }
        else if (min_val == distance_arr[1]) // right
        {
            temp = puzzle;
            swap(temp[space], temp[space + 1]);
            visited_nodes.insert(temp);
        }
        else if (min_val == distance_arr[2]) // down
        {
            temp = puzzle;
            swap(temp[space], temp[space + 3]);
            visited_nodes.insert(temp);
        }
        else if (min_val == distance_arr[3]) // up
        {
            temp = puzzle;
            swap(temp[space], temp[space - 3]);
            visited_nodes.insert(temp);
        }
        distance_arr[0] = 10;
        distance_arr[1] = 10;
        distance_arr[2] = 10;
        distance_arr[3] = 10;
    };
};

void astart_euclid(vector<int> v)
{
    Solve puzz;
    if (v == puzz.goal_state)
    {
        cout << "Goal found at first iteration!" << endl;
        return;
    }

    int empty_space;
    auto it = find(v.begin(), v.end(), 0); // Finds 0 "empty space"
    if (it != v.end())
    {
        empty_space = std::distance(v.begin(), it);
    }
    puzz.shift_moves(empty_space, v);
    while (!puzz.queued_nodes.empty())
    {
        vector<int> top_element = puzz.queued_nodes.top();
        puzz.queued_nodes.pop();
        if (top_element == puzz.goal_state)
        {
            cout << "Goal found homie" << endl;
            return;
        }
        else
        {

            for (vector<int>::size_type i = 0; i < top_element.size(); i += 3)
            {
                for (int j = 0; j < 3 && i + j < top_element.size(); j++)
                {
                    cout << top_element[i + j] << " ";
                }
                cout << endl;
            }
            cout << "\n";
            int empty_space;
            auto it = find(top_element.begin(), top_element.end(), 0); // Finds 0 "empty space"
            if (it != top_element.end())
            {
                empty_space = std::distance(top_element.begin(), it);
            }
            puzz.shift_moves(empty_space, top_element);
        }
    }
};