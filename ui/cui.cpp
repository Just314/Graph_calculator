#include "cui.h"
#include "../data/graph_io.h"
#include "../algorithm/alg_fac_meth.h"
#include <bits/stdc++.h>

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
    std::cout << welcome_msg;
    std::cout << extension;
    std::cout << suggest;
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
    std::cout 
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
    std::cout
    << "Please enter the name of the file: ";
    string name; cin >> name;
    Graph_io in = Graph_io(name);

    std::cout 
    <<"How many verticies graph has?   "
    ;
    int v_num; cin >> v_num;
    std::cout << "Are verticies in the graph weighted? y/n\n   ";
    string weight; cin >> weight;

    Graph gr;

    if (weight == "y"){
        gr = Graph(v_num, true);
        gr.type |= Weighted;
        gr.addVWeight(1);
        
    } else {
        gr = Graph (v_num);
    }


    std::cout 
    << "\nTo add edges type: e vertex_number vertex_number\n"
    << "To add undirected edge type: u vertex_number vertex_number\n"
    << "To  add weigthed edge type: w vertex_number vertex_number weight\n"
    << "To complete graph creation type: finish\n"
    ;

    while(true){
        string response, a, b, w; cin >> response; 
        
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
        }  else if (response=="w") {
            cin >> w;
            int i = stoi(a); int j = stoi(b); int k = stoi(w);
            gr.addWeightedEdge(i,j,k);
        }
        else{
            std::cout << "Malfunction of input";
        }
        
        
    }
            in.SetGraph(gr);
        
    in.Write("test");
    
    std::cout 
    << "\n"
    << "Operation is succesful\n"
    << "--------------------\n"
    << "\n"
    ;
}

void DisplayGraph(){

    Graph* g;

    while (true)
    {
        std::cout
        << "Please enter the name of the file: ";
        string name; cin >> name;
        Graph_io in = Graph_io(name);
        try
        {
            g = in.Read();
        }
        catch(InadequateFile e){
            std::cerr << e.what() << '\n';
            cout << "Please enter valid name of the file\n";
            continue;
        }
        break;
        
    }
    
    
    std::cout
    <<"Number of vertecies: " << g->getVertCount() << "\n"
    <<"Number of edeges: " << g->getEdgesCount()<< "\n"
    <<"Adjacency Matrix: \n\n"
    <<g->MatrixToString()
    ;

    /*if(g->hasVW()){
        std::cout 
        << "Vertecies Weights:\n"
        ;
        for(u_short i = 0;i<g->getVertCount();i++){
            std::cout 
            << char(97+i) << " " << g->getVWeigth(i) << "\n"
            ;
        }
    }*/
    std::cout << "Weights Matrix: \n\n";
    auto adj = g->MatrixWeighted();
    for (int i = 0; i < g->getVertCount(); i++)
    {
        for (int j = 0; j < g->getVertCount(); j++)
        {
            cout << adj[i][j] <<" ";
        }
        cout << "\n";
    }
    
    std::cout 
    <<"--------------------\n\n"
    ;

    
    
}

void Executor(){


    IALGFM* algo;

    while (true)
    {
        std::cout
        <<  "Please pick the algorithm:\n"
        <<  "   Connectedness\n"
        <<  "   Euler path\n"
        <<  "   Shortest path\n"
        <<  "   Hamiltonian path\n"
        ;
        string pick; 
        std::getline(std::cin >> std::ws, pick);
        if (pick.find("onnected")!=string::npos){
            algo = new BuildConnectedness();
            break;
        } else if( pick.find("uler")!=string::npos){
            algo = new CheckEuler();
            break;
        } else if( pick.find("hortest")!=string::npos){
            algo = new ShortestPath();
            break;
        } else if( pick.find("amiltonian")!=string::npos){
            algo = new Hamiltonian();
            break;
        } else{
            std::cout 
            << "Please enter valid algorithm name\n";
        }
    }

    std::string ans;

    while (true)
    {
        try{
        std::cout 
        << "Please enter the name of the file: "
        ;
        string name; cin >> name;
        Graph_io in = Graph_io(name);
        ans = algo->ExecuteAlgorithm(&in);
        } catch (InadequateFile e){
            cerr << "\n"<<e.what() <<"\n";
            cout << "Please enter valid file name\n\n";
            continue;
        }
        break;
    }
    
    std::cout
    << "\n--------------------\n"
    << ans
    << "--------------------\n\n"
    ;
}