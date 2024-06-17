
#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    class Vertex
    {
    public:
        unordered_map<string, int> nbrs;
    };

    unordered_map<string, Vertex> vtces;

    int numVertex()
    {
        return vtces.size();
    }

    bool containsVertex(const string &vname)
    {
        return vtces.find(vname) != vtces.end();
    }

    void addVertex(const string &vname)
    {
        Vertex vtx;
        vtces[vname] = vtx;
    }

    void removeVertex(const string &vname)
    {
        auto it = vtces.find(vname);
        if (it != vtces.end())
        {
            for (auto &pair : it->second.nbrs)
            {
                vtces[pair.first].nbrs.erase(vname);
            }
            vtces.erase(it);
        }
    }

    int numEdges()
    {
        int count = 0;
        for (auto &pair : vtces)
        {
            count += pair.second.nbrs.size();
        }
        return count / 2;
    }

    bool containsEdge(const string &vname1, const string &vname2)
    {
        auto it1 = vtces.find(vname1);
        auto it2 = vtces.find(vname2);
        if (it1 == vtces.end() || it2 == vtces.end())
            return false;
        return it1->second.nbrs.find(vname2) != it1->second.nbrs.end();
    }

    void addEdge(const string &vname1, const string &vname2, int value)
    {
        auto it1 = vtces.find(vname1);
        auto it2 = vtces.find(vname2);
        if (it1 == vtces.end() || it2 == vtces.end())
            return;
        it1->second.nbrs[vname2] = value;
        it2->second.nbrs[vname1] = value;
    }

    void removeEdge(const string &vname1, const string &vname2)
    {
        auto it1 = vtces.find(vname1);
        auto it2 = vtces.find(vname2);
        if (it1 == vtces.end() || it2 == vtces.end())
            return;
        it1->second.nbrs.erase(vname2);
        it2->second.nbrs.erase(vname1);
    }

    void displayMap()
    {
        for (auto &pair : vtces)
        {
            cout << pair.first << " => ";
            for (auto &nbr : pair.second.nbrs)
            {
                cout << nbr.first << "(" << nbr.second << "), ";
            }
            cout << endl;
        }
    }

    void displayStations()
    {
        for (auto &pair : vtces)
        {
            cout << pair.first << endl;
        }
    }

    bool hasPath(const string &vname1, const string &vname2, unordered_map<string, bool> &processed)
    {
        if (containsEdge(vname1, vname2))
            return true;
        processed[vname1] = true;
        for (auto &nbr : vtces[vname1].nbrs)
        {
            if (!processed[nbr.first] && hasPath(nbr.first, vname2, processed))
            {
                return true;
            }
        }
        return false;
    }

    int dijkstra(const string &src, const string &des, bool nan)
    {
        unordered_map<string, int> dist;
        unordered_map<string, bool> visited;
        for (auto &pair : vtces)
        {
            dist[pair.first] = INT_MAX;
        }
        dist[src] = 0;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push({0, src});

        while (!pq.empty())
        {
            auto curr = pq.top();
            pq.pop();
            if (visited[curr.second])
                continue;
            visited[curr.second] = true;

            for (auto &nbr : vtces[curr.second].nbrs)
            {
                if (!visited[nbr.first])
                {
                    int newDist = curr.first + nbr.second;
                    if (newDist < dist[nbr.first])
                    {
                        dist[nbr.first] = newDist;
                        pq.push({newDist, nbr.first});
                    }
                }
            }
        }

        return dist[des];
    }

    string getMinimumDistance(const string &src, const string &dst)
    {
        int dist = dijkstra(src, dst, true);
        if (dist == INT_MAX)
            return "No path exists";
        return "The minimum distance from " + src + " to " + dst + " is " + to_string(dist) + " units.";
    }

    string getMinimumTime(const string &src, const string &dst)
    {
        // Assume distance in km and train speed 40km/h
        int dist = dijkstra(src, dst, true);
        if (dist == INT_MAX)
            return "No path exists";
        double time = dist / 40.0;
        return "The minimum time from " + src + " to " + dst + " is " + to_string(time) + " hours.";
    }

    vector<string> getInterchanges(const string &str)
    {
        vector<string> interchanges;
        for (auto &pair : vtces[str].nbrs)
        {
            if (vtces[pair.first].nbrs.size() > 2)
            {
                interchanges.push_back(pair.first);
            }
        }
        return interchanges;
    }

    static void createMetroMap(Graph &g)
    {
        g.addVertex("A");
        g.addVertex("B");
        g.addVertex("C");
        g.addVertex("D");
        g.addEdge("A", "B", 5);
        g.addEdge("A", "C", 10);
        g.addEdge("B", "D", 15);
        g.addEdge("C", "D", 20);
    }

    static vector<string> printCodeList()
    {
        return {"A - Station A", "B - Station B", "C - Station C", "D - Station D"};
    }
};

int main()
{
    Graph g;
    Graph::createMetroMap(g);
    g.displayMap();
    cout << g.getMinimumDistance("A", "D") << endl;
    cout << g.getMinimumTime("A", "D") << endl;
    vector<string> interchanges = g.getInterchanges("A");
    for (const string &str : interchanges)
    {
        cout << str << endl;
    }
    vector<string> codeList = Graph::printCodeList();
    for (const string &code : codeList)
    {
        cout << code << endl;
    }
    return 0;
}
