#include "cui.h"
#include "../data/graph_io.h"
#include "../algorithm/alg_fac_meth.h"
using namespace std;

Cui::Cui(){

}

enum CalcCommand {WriteGraph, CalculateGraph, ReadGraph, Terminate, UnknownResponse};
void CreateGraph();
void DisplayGraph();
CalcCommand CheckMode();
void Executor();

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
            Executor();
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

    cout 
    <<"How many verticies graph has?   "
    ;
    int v_num; cin >> v_num;
    cout << "Are verticies in the graph weighted? y/n\n   ";
    string weight; cin >> weight;

    Graph gr;

    if (weight == "y"){
        gr = Graph(v_num, true);
        gr.type |= Weighted;
        cout << "Please enter weights for all verticies:\n";
        for (u_short i = 0; i < v_num; i++)
        {
            cout << "   " << char(97+i) << "    ";
            u_short w; cin >> w;
            gr.setVWeight(i+1,w);
        }
        
    } else {
        gr = Graph (v_num);
    }


    cout 
    << "\nTo add edges type: e vertex_number vertex_number\n"
    << "To add undirected edge type: u vertex_number vertex_number\n"
    << "To complete graph creation type: finish\n"
    ;

    while(true){
        string response, a, b; cin >> response; 
        
        if(response.find("finish")!=string::npos){
            break;
        }  
        cin >> a >> b;
        if (response=="e"){
            int i = stoi(a); int j = stoi(b);
            gr.addEdge(i,j);
        } else if (response=="u")
        {
            int i = stoi(a); int j = stoi(b);
            gr.addUndirectedEdge(i,j);
        }else{
            cout << "Malfunction of input";
        }
        
        
    }
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
    ;

    if(g->hasVW()){
        cout 
        << "Vertecies Weights:\n"
        ;
        for(u_short i = 0;i<g->getVertCount();i++){
            cout 
            << char(97+i) << " " << g->getVWeigth(i) << "\n"
            ;
        }
    }
    cout 
    <<"--------------------\n\n"
    ;
}

void Executor(){
    cout 
    << "Please enter the name of the file: "
    ;
    string name; cin >> name;
    Graph_io in = Graph_io(name);

    IALGFM* algo = new BuildConnectedness();
    auto ans = algo->ExecuteAlgorithm(&in);
    cout
    << "\n--------------------\n"
    << ans
    << "--------------------\n\n"
    ;
}