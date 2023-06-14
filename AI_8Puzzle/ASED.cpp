#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <functional>
#include <algorithm>
#include <cmath>
using namespace std;
class Puzzle;
struct VectorHashEuclid // hash function
{
    size_t operator()(const vector<int> &v) const
    {
        hash<int> hasher;
        size_t seed = 0;
        for (int i : v)
        {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

int find_sliding_piece_euclid(vector<int> v) // finds the zero or the sliding peice
{
    int space;
    auto it = find(v.begin(), v.end(), 0);
    if (it != v.end())
    {
        space = distance(v.begin(), it);
    }
    return space; // values from 0-8
};

float distance_to_goal(int space, int valid_move) // valid move is the actual value to shift, not the cell
{
    int x1, y1, x2, y2;
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
    if (valid_move == 0)
    {
        x2 = 3;
        y2 = 1;
    }
    else if (valid_move == 1)
    {
        x2 = 1;
        y2 = 3;
    }
    else if (valid_move == 2)
    {
        x2 = 2;
        y2 = 3;
    }
    else if (valid_move == 3)
    {
        x2 = 3;
        y2 = 3;
    }
    else if (valid_move == 4)
    {
        x2 = 1;
        y2 = 2;
    }
    else if (valid_move == 5)
    {
        x2 = 2;
        y2 = 2;
    }
    else if (valid_move == 6)
    {
        x2 = 3;
        y2 = 2;
    }
    else if (valid_move == 7)
    {
        x2 = 1;
        y2 = 1;
    }
    else if (valid_move == 8)
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
};

class PuzzleEuclid
{
public:
    vector<int> goal_state = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    unordered_set<vector<int>, VectorHashEuclid> visited_nodes;
    priority_queue<pair<float, vector<int>>, vector<pair<float, vector<int>>>, greater<pair<float, vector<int>>>> queued_nodes;
    int space;
    int g_function = 0;

    void find_possible_goals(vector<int> v, int space) // left, right, down, or up
    {
        if (space == 1 || space == 2 || space == 4 || space == 5 || space == 7 || space == 8) // left
        {
            push_nodes(v, space, "left");
        }
        if (space == 0 || space == 1 || space == 3 || space == 4 || space == 6 || space == 7) // right
        {
            push_nodes(v, space, "right");
        }
        if (space == 0 || space == 1 || space == 2 || space == 3 || space == 4 || space == 5) // down
        {
            push_nodes(v, space, "down");
        }
        if (space == 3 || space == 4 || space == 5 || space == 6 || space == 7 || space == 8) // up
        {
            push_nodes(v, space, "up");
        }
    };
    void push_nodes(vector<int> v, int space, string path)
    {
        int move;
        if (path == "left")
        {
            move = v[space - 1];
            swap(v[space], v[space - 1]);
        }
        else if (path == "right")
        {
            move = v[space + 1];
            swap(v[space], v[space + 1]);
        }
        else if (path == "down")
        {
            move = v[space + 3];
            swap(v[space], v[space + 3]);
        }
        else if (path == "up")
        {
            move = v[space - 3];
            swap(v[space], v[space - 3]);
        }
        // get euclid distance
        float cost = distance_to_goal(space, move);
        if (visited_nodes.count(v) == 0)
        {
            g_function++;
            cout << "Node expanded: g(n) = " << g_function << " h(n) = " << cost << endl;
            cout << "\n";
            queued_nodes.push(make_pair(cost, v));
        }
        visited_nodes.insert(v);
    };
};

void euclid_distance(vector<int> puzzle)
{
    PuzzleEuclid p;
    if (puzzle == p.goal_state)
    {
        cout << "Base case. Goal found on first try." << endl;
        return;
    }
    p.space = find_sliding_piece_euclid(puzzle);
    p.find_possible_goals(puzzle, p.space);

    while (!p.queued_nodes.empty())
    {
        vector<int> top_node = p.queued_nodes.top().second;
        p.queued_nodes.pop();
        for (vector<int>::size_type i = 0; i < top_node.size(); i += 3)
        {
            for (vector<int>::size_type j = 0; j < 3 && i + j < top_node.size(); j++)
            {
                cout << top_node[i + j] << " ";
            }
            cout << endl;
        }
        cout << "\n";
        if (top_node == p.goal_state)
        {
            cout << "Found" << endl;
            return;
        }
        else
        {
            p.space = find_sliding_piece_euclid(top_node);
            p.find_possible_goals(top_node, p.space);
        }
    }
    cout << "Nothing last forever ponyboy";
};