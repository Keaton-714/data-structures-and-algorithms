#ifndef FLIGHT_H
#define FLIGHT_H
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
using namespace std;


class Graph
{
    private:
        unordered_map<string, list<pair<string, int>>> adjList;
    public:
        Graph();
        void add(string st, string en, int dis);
        void print();
        vector<string> bfs(string origin, string destination);
        void routeSearch1(string origin, string destination, int layOvers);
        void routeSearch2(string origin, string lay1, string lay2, string destination);
};


#endif