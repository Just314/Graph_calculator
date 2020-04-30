#include "graph_io.h"


using namespace std;

Graph_io::Graph_io(string name){ 

    if (name.find(FILE_EXTENSION)==std::string::npos){
        string dilimiter = ".";
        if (name.find(dilimiter)!= std::string::npos){
            name = name.substr(0,name.find(dilimiter));

        }
        name.append(FILE_EXTENSION);
    }
    st = Waiting;
    file_name = name; 
}

class InadequateFile: public exception
{
    const char* what() const throw(){
        return "File does not exist or is corrupted";
    }
};

void Graph_io::Open(){
    try
    {
        file.open(file_name, ios::out | ios::in | ios::binary);
        if (file.fail()){
            throw  InadequateFile();
         }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
}

void Graph_io::Close(){
    file.close();
}

void Graph_io::SetGraph(Graph setted){
    g = setted;
}

template<typename T>
std::ostream& binary_write(std::ostream& stream, const T& value){
    return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template<typename T>
std::istream & binary_read(std::istream& stream, T& value){
    return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

void Graph_io::Write(string data){
    Open();
    file.seekp(0);
    u_short vcount = g.getVertCount();
    u_short ecount = g.getEdgesCount();

    file.write((char*)&vcount,sizeof(u_short));
    file.write((char*)&ecount,sizeof(u_short));
    
    bool hvw = g.hasVW(); bool hew = g.hasEW();
    file.write((char*)&hvw,sizeof(bool));
    file.write((char*)&hew,sizeof(bool));
    
    for(u_short i =0; i<ecount;i++){
        auto ed = g.getEdge(i);
        file.write((char*)&ed.first,sizeof(u_short));
        file.write((char*)&ed.second,sizeof(u_short));
    }
    /*u_short nums = 5;
    u_short data2[5]{1,2,3,4,5};
    
    file.seekp(0);
    file.write(reinterpret_cast<const char*>(&nums),sizeof(nums));
    for (u_short i = 0; i < nums; i++)
        file.write((char*)&data2[i],sizeof(data2[i]));*/

    Close();
}

Graph* Graph_io::Read(){
    Open();
    u_short vnum, enums; bool hvw,hew;
    file.read((char*)&vnum,sizeof(u_short));
    file.read((char*)&enums,sizeof(u_short));
    file.read((char*)&hvw,sizeof(bool));
    file.read((char*)&hew,sizeof(bool));

    cout << vnum << " "<< enums << " "<< hvw << " "<< hew << "\n";

    Graph* gr = new Graph(vnum);
    for (u_short i = 0; i < enums; i++)
    {
        u_short a,b;
        file.read((char*)&a,sizeof(u_short));
        file.read((char*)&b,sizeof(u_short));
        gr->addEdge(a,b);
    }
    

    /*u_short nums;
    file.read(reinterpret_cast<char*>(&nums),sizeof(nums));
    u_short data[nums];
    for (u_short i =0; i < nums;i++)
        file.read((char*)&data[i],sizeof(u_short));*/
    Close();
    return gr;
}
