/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "basicgraph.h"
using namespace std;

int main()
{
    BasicGraph graph;
    string name1, name2;
    cout << "Please input the name of the first person!" << endl;
    cin >> name1;
    cout << "Please input the name of the second person!" << endl;
    cin >> name2;
    graph.addVertex(name1);
    graph.addVertex(name2);
    graph.addEdge(name2, name1);
    cout << "Here is the output of the graph!" << endl;
    cout << graph << endl;
    return 0;
}
