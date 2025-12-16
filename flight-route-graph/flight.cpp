#include "flight.h"
#include <algorithm>
using namespace std;

Graph::Graph() {}

// unordered_map<string, list<string>> adjList; 
// could also do unordered_map<string, vector<string>> adjList; (would be more efficient)
void Graph::add(string st, string en, int dis)
{
    adjList[st].push_back({en, dis}); // EX: New York | {Chicago, 790}, {Atlanta, 870}, {London, 3450}

}

void Graph::print()
{
    for (auto& pair : adjList) // pair.first = start city, pair.second = list of destinations
    {
        cout << pair.first << " -> ";
        for (auto& dest : pair.second) // dest.first = end city, dest.second = distance
        {
            cout << "{" << dest.first << ", " << dest.second << "} ";
        }
        cout << endl;
    }
}

vector<string> Graph::bfs(string origin, string destination)
{
    auto it = adjList.find(origin);
    if (it == adjList.end())
    {
        return {};
    }

    queue<string> q;
    unordered_map<string, string> parent; // tracks where we came from
    unordered_map<string, bool> visited; // tracks if city has been visited
    
    for (auto dest : it->second)
    {
        if (dest.first == destination)
        {
            return {origin, destination}; // if found then direct flight to city exists
        }
        q.push(dest.first);
        parent[dest.first] =  origin;
        visited[dest.first] = true;
    }
    bool found = false;
    while(!q.empty() && !found)
    {
        string currentCity = q.front();
        q.pop();
        auto it = adjList.find(currentCity);
        if (it != adjList.end())
        {
            for (auto dest : it->second)
            {
                if (!visited[dest.first])
                {
                    q.push(dest.first);
                    parent[dest.first] = currentCity;
                    visited[dest.first] = true;
                }
                if (dest.first == destination)
                {
                    parent[dest.first] = currentCity; // ensure parent is set
                    found = true;
                    break;
                }
            }
        }
    }
    if (found)
    {
        vector<string> path;
        string city = destination;
        while(city != origin)
        {
            path.push_back(city);
            city = parent[city];
        }
        path.push_back(origin);
        reverse(path.begin(), path.end());
        return path;
    }
    return {}; // not found

}

// Route with smallest number of connections from start to destination
void Graph::routeSearch1(string origin, string destination, int layOvers)
{
    cout << "Searching..." << endl;
    vector<string> route;
    route = bfs(origin, destination);
    if (route.empty())
    {
        cout << "No route available from " << origin << " to " << destination << endl;
        return;
    }
    if (route.size()-2 <= layOvers)
    {
        cout << "Fastest route found: ";
        for (auto city : route)
        {
            cout << city << " ";
        }
        cout << endl;
        return;
    }
    cout << "Fastest route found, but with " << route.size() -2 << " layovers: ";
    for (auto city : route)
    {
        cout << city << " ";
    }
    cout << endl;
}

// Route with the smallest number of connections from city “A” to city “D” through city “B” and “C”.
void Graph::routeSearch2(string origin, string lay1, string lay2, string destination)
{
    // first search a->b then b->c then c->d
    cout << "Searching..." << endl;
    vector<string> route1 = bfs(origin, lay1);
    vector<string> route2 = bfs(lay1, lay2);
    vector<string> route3 = bfs(lay2, destination);
    if (route1.empty() || route2.empty() || route3.empty())
    {
        cout << "No route available" << endl;
        return;
    }
    vector<string> path;
    path = route1;
    path.insert(path.end(), route2.begin() + 1, route2.end());
    path.insert(path.end(), route3.begin() + 1, route3.end());
    cout << "Fastest route found with your preferred layovers: ";
    for (auto city : path)
    {
        cout << city << " ";
    }
    cout << endl;
}