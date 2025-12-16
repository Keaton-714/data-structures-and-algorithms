#include "flight.h"
#include <cctype>
using namespace std;


int main()
{
    ifstream fin;
    fin.open("flight.txt");

    if (!fin.is_open())
    {
        cerr << "File couldn't be opened" << endl;
        return 0;
    }

    string line;
    string start, end;
    int weight;

    Graph graph;
    while (fin)
    {
        getline(fin, start, ',');
        getline(fin, end, ',');
        fin >> weight;
        fin.ignore();
        if (isspace(start[0])) // remove extra space at the beginning
        {
            start.erase(0,1);
        }
        if (isspace(end[0]))
        {
            end.erase(0,1);
        }
        graph.add(start, end, weight); // add cities to graph (duplicate starts not allowed)
        
    }
    fin.close();
    cout << "Available flights: " << endl;
    graph.print();
    cout << endl;

    // Route search 1
    string origin, dest;
    int lay;
    cout << "Enter origin city: ";
    getline(cin, origin);
    cout << "Enter destination: ";
    getline(cin, dest);
    cout << "Enter maximum layovers: ";
    cin >> lay;
    graph.routeSearch1(origin, dest, lay); 
    cin.ignore();

    // Route search 2
    cout << "Enter origin city: ";
    getline(cin, origin);
    cout << "Enter city you wish to have a layover in: ";
    string lay1, lay2;
    getline(cin, lay1);
    cout << "Enter the other city you wish to have a layover in: ";
    getline(cin, lay2);
    cout << "Enter Final destination: ";
    getline(cin, dest);
    graph.routeSearch2(origin, lay1, lay2, dest);

return 0;
}
