#include "cui.h"
#include "../data/graph_io.h"
using namespace std;

Cui::Cui(){

}




void Cui::welcome()
{
    std::string welcome_msg { "You are using Graph Concetedness Checker. The programm is written by students of AUCA: Talkanbaev Artur, Daniiarov Alym and Askarbekov Yerkebulan\n\n"} ;
    std::string extension { "This programm uses custom file type - .ag; which stands for AUCA graph. The programm comes with 10 example file for programm testing.\n\n"};
    std::string suggest {"Please provide a file with .ag extension: put it in the derictory of the programm and type the file name in the console.\n"};
    cout << welcome_msg;
    cout << extension;
    cout << suggest;
}

void Cui::loop(){
    while (true)
    {
        cout << "File name or a command:";
        string name;
        cin >> name;

        if (name == "exit"){
            return;
        }
        
        Graph_io in = Graph_io(name);

        Graph gr = Graph(4);
        gr.addEdge(1,2);
        gr.addEdge(2,3);
        gr.addEdge(4,1);
        in.SetGraph(gr);
        in.Write("test");
        Graph g = in.Read();
        cout << g.getVertCount() << " " <<g.getEdgesCount()<<"\n";
        for(auto i : g.getAllEdges())
            cout << i.first << " " <<i.second<<"\n";
        //cout << "If you want to test another graph please type its file name. If you want to leave the programm type \"exit\"\n\n";
    }
}