#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;
class Puzzle;
struct VectorHash // hash function
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

int find_sliding_piece(vector<int> v) // finds the zero or the sliding peice
{
    int space;
    auto it = find(v.begin(), v.end(), 0);
    if (it != v.end())
    {
        space = distance(v.begin(), it);
    }
    return space; // values from 0-8
};

class Puzzle
{
public:
    vector<int> goal_state = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    unordered_set<vector<int>, VectorHash> visited_nodes;
    priority_queue<vector<int>> queued_nodes;
    int space;
    int h_function = 0;
    int g_function = 0;

    void find_possible_moves(vector<int> v, int space) // left, right, down, or up
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
        if (path == "left")
        {
            swap(v[space], v[space - 1]);
        }
        else if (path == "right")
        {
            swap(v[space], v[space + 1]);
        }
        else if (path == "down")
        {
            swap(v[space], v[space + 3]);
        }
        else if (path == "up")
        {
            swap(v[space], v[space - 3]);
        }
        if (visited_nodes.count(v) == 0)
        {
            g_function++;
            cout << "Node expanded: g(n) = " << g_function << " h(n) = " << h_function << endl;
            cout << "\n";
            queued_nodes.push(v);
        }
        visited_nodes.insert(v);
    };
};

void uniform_cost(vector<int> puzzle)
{
    Puzzle p;
    if (puzzle == p.goal_state)
    {
        cout << "Base case. Goal found on first try." << endl;
        return;
    }
    p.space = find_sliding_piece(puzzle);
    p.find_possible_moves(puzzle, p.space);

    while (!p.queued_nodes.empty())
    {
        vector<int> top_node = p.queued_nodes.top();
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
            p.space = find_sliding_piece(top_node);
            p.find_possible_moves(top_node, p.space);
        }
    }
    cout << "Nothing last forever ponyboy";
};