#include "cui.h"
#include "../data/graph_io.h"
using namespace std;

Cui::Cui(){

}

enum CalcCommand {WriteGraph, CalculateGraph, ReadGraph, Terminate, UnknownResponse};
void CreateGraph();
void DisplayGraph();
CalcCommand CheckMode();

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
        auto command = CheckMode();
        
        switch (command)
        {
        case WriteGraph:
            CreateGraph();
            break;
        case CalculateGraph:
            break;
        case ReadGraph:
            DisplayGraph();
            break;
        case Terminate:
            return;
        default:
            break;
        }
    }
}



CalcCommand CheckMode(){
    cout 
    << "Please enter one of these Commands:\n"  
    << "    To create new graph enter: \"new\"\n"
    << "    To perform calculations and run algorithms enter: \"run\"\n"
    << "    To display properties of the graph enter: \"read\"\n"
    << "    To leave programm type: \"exit\"\n"
    ;
    
    string response; cin >> response;

    if (response.find("read")!=string::npos){
        return ReadGraph;
    }

    if (response.find("new")!=string::npos){
        return WriteGraph;
    }

    if (response.find("run")!=string::npos){
        return CalculateGraph;
    }

    if (response.find("exit")!=string::npos){
        return Terminate;
    }
    return UnknownResponse;
}

void CreateGraph(){
    cout
    << "Please enter the name of the file: ";
    string name; cin >> name;
    Graph_io in = Graph_io(name);
        Graph gr = Graph(4);
            gr.addEdge(1,2);
            gr.addEdge(2,3);
            gr.addEdge(4,1);
            in.SetGraph(gr);
        
    in.Write("test");
    
    cout 
    << "\n"
    << "Operation is succesful\n"
    << "--------------------\n"
    << "\n"
    ;
}

void DisplayGraph(){
    cout
    << "Please enter the name of the file: ";
    string name; cin >> name;
    Graph_io in = Graph_io(name);
    Graph* g = in.Read();
    cout
    <<"Number of vertecies: " << g->getVertCount() << "\n"
    <<"Number of edeges: " << g->getEdgesCount()<< "\n"
    <<"Adjacency Matrix: \n\n"
    <<g->MatrixToString()
    <<"--------------------\n\n"
    ;
}