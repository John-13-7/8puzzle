#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <functional>
#include <algorithm>
#include <cmath>
using namespace std;
class Puzzle;
struct VectorHashTile // hash function
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

int find_sliding_piece_tile(vector<int> v) // finds the zero or the sliding peice
{
    int space;
    auto it = find(v.begin(), v.end(), 0);
    if (it != v.end())
    {
        space = distance(v.begin(), it);
    }
    return space; // values from 0-8
};

class PuzzleTile
{
public:
    vector<int> goal_state = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    unordered_set<vector<int>, VectorHashTile> visited_nodes;
    priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, greater<pair<int, vector<int>>>> queued_nodes;
    unordered_set<vector<int>, VectorHashTile> misplaced_tile;
    int space;
    int g_function = 0;

    void test_goal_states(vector<int> v) // size of misplaced_tiles gives us the actual amount of missing tiles
    {
        for (auto i = 0; i < v.size() - 1; i++)
        {
            if (v[i] != (i + 1)) // there's a better way, but this is the lazy way
            {
                misplaced_tile.insert({i + 1});
            }
        }
    };

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

    void push_nodes(vector<int> v, int space, string path) // individual paths
    {
        test_goal_states(v); // builds the misplaced_tile vector
        vector<int> move;
        if (path == "left")
        {
            move.push_back(v[space - 1]);
            swap(v[space], v[space - 1]);
        }
        else if (path == "right")
        {
            move.push_back(v[space + 1]);
            swap(v[space], v[space + 1]);
        }
        else if (path == "down")
        {
            move.push_back(v[space + 3]);
            swap(v[space], v[space + 3]);
        }
        else if (path == "up")
        {
            move.push_back(v[space - 3]);
            swap(v[space], v[space - 3]);
        }
        if (visited_nodes.count(v) == 0)
        {
            g_function++;
            queued_nodes.push(make_pair(misplaced_tile.size(), v));
            visited_nodes.insert(v);
            cout << "Node created: g(n) = " << g_function << " h(n) = " << misplaced_tile.size() << endl;
            cout << "\n";
        }
        misplaced_tile.clear();
    };
};

void missing_tile(vector<int> puzzle)
{
    PuzzleTile p;
    if (puzzle == p.goal_state)
    {
        cout << "Base case. Goal found on first try." << endl;
        return;
    }
    p.space = find_sliding_piece_tile(puzzle);
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
            p.space = find_sliding_piece_tile(top_node);
            p.find_possible_goals(top_node, p.space);
        }
    }
    cout << "Nothing last forever ponyboy";
};