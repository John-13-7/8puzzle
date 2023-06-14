#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <iterator>
using namespace std;
class node
{
public:
    vector<int> goal_state = {1, 2, 3, 4, 5, 6, 7, 8, 0}; // goal
    struct VectorHash                                     // has function to make the code like its on steroids
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
    unordered_set<vector<int>, VectorHash> visited_nodes; // unordered set for linear lookups
    priority_queue<vector<int>> queued_nodes;             // pq for next nodes
    int created_nodes = 0;                                // curiousity to see how many nodes are created, however not all are visited

    void check_moves(vector<int> v)
    {
        int space;
        auto it = find(v.begin(), v.end(), 0); // Finds 0 "empty space"
        if (it != v.end())
        {
            int pos = std::distance(v.begin(), it);
            space = pos + 1;
        }

        vector<int> temp;

        // 1
        // right and down
        if (space == 1)
        {
            temp = v;
            swap(temp[0], temp[1]);
            if (visited_nodes.count(temp) == 0)
            {
                queued_nodes.push(temp);
                created_nodes++;
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[0], temp[3]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
        }
        // 2
        // left, right, down
        else if (space == 2)
        {
            temp = v;
            swap(temp[1], temp[2]); // right
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[1], temp[0]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[1], temp[4]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
        }
        // 3
        // left, down
        else if (space == 3)
        {
            temp = v;
            swap(temp[2], temp[1]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[2], temp[5]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
        }
        // 4
        // up, right, down
        else if (space == 4)
        {
            temp = v;
            swap(temp[3], temp[0]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[3], temp[4]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[3], temp[6]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
        }
        // 5
        // up, down, right, left,
        else if (space == 5)
        {
            temp = v;
            swap(temp[4], temp[3]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[4], temp[5]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[4], temp[1]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[4], temp[7]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
        }
        // 6
        // up, left, down
        else if (space == 6)
        {
            temp = v;
            swap(temp[5], temp[4]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[5], temp[2]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[5], temp[8]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
        }
        // 7
        // up, right
        else if (space == 7)
        {
            temp = v;
            swap(temp[6], temp[7]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[6], temp[3]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
        }
        // 8 left, up, right
        else if (space == 8)
        {
            temp = v;
            swap(temp[7], temp[6]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[7], temp[8]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[7], temp[4]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
        }
        // 9
        // left, up
        else if (space == 9)
        {
            temp = v;
            swap(temp[8], temp[7]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
            temp = v;
            swap(temp[8], temp[5]);
            if (visited_nodes.count(temp) == 0)
            {
                created_nodes++;
                queued_nodes.push(temp);
            }
            visited_nodes.insert(temp);
        }
    };
};

void uniform_c(vector<int> v)
{
    node n;
    // Base case, its already solved
    if (n.goal_state == v)
    {
        cout << "Goal state" << endl;
    }
    // First run, get the first visited nodes, and start putting them into the queue
    n.check_moves(v);
    int iterations = 0;
    while (!n.queued_nodes.empty())
    {
        iterations++;
        vector<int> top_element = n.queued_nodes.top();
        n.queued_nodes.pop();

        if (top_element == n.goal_state)
        {
            for (int i = 0; i < top_element.size(); i += 3)
            {
                for (int j = 0; j < 3 && i + j < top_element.size(); j++)
                {
                    cout << top_element[i + j] << " ";
                }
                cout << std::endl;
            }

            cout << "goal found! " << endl;
            cout << "total created nodes: " << n.created_nodes << endl;
            return;
        }
        else
        {
            n.check_moves(top_element);
        }
    }
    cout << "Not found, total nodes: " << n.created_nodes << endl;
};