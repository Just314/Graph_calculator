#include "graph_io.h"

using namespace std;
typedef unsigned short int ushort;
typedef unsigned short int u_int16_t;
/*

// Reserved code for unix/win separate filepath delimiter definition

#ifdef __unix__

const string OTHER_FOLDER = "/";
const string EXAMPLES_FOLDER = "examples/";

#endif

#if defined(_WIN32) || defined(_WIN64)

const string OTHER_FOLDER = "\\";
const string EXAMPLES_FOLDER = "examples\\";

#endif*/

//Default file dilimmiter
const string OTHER_FOLDER = "/";

//Default file search folder
const string EXAMPLES_FOLDER = "examples/";

Graph_io::Graph_io(string name){ 

    //Check .ag extension
    if (name.find(FILE_EXTENSION)==std::string::npos){
        string dilimiter = ".";
        if (name.find(dilimiter)!= std::string::npos){
            name = name.substr(1,name.find(dilimiter));

        }
        name.append(FILE_EXTENSION);
    }

    //Check folder
    if (name.find(OTHER_FOLDER)==std::string::npos){
        name = EXAMPLES_FOLDER+name;
    }

    st = Waiting;
    file_name = name; 
}

//Custom exception for Corrupted binary files
class InadequateFile: public exception
{
    const char* what() const throw(){
        return "File does not exist or is corrupted";
    }
};

//Open file for read
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

//Create new file if does not exist or open if exist
void Graph_io::Create(){
    file.open(file_name, ios::out | ios::binary);
    file.close();
    file.open(file_name, ios::out | ios::in | ios::binary);
}

//Closing shortcut
void Graph_io::Close(){
    file.close();
}

//Initialise pointer to a provided for write Graph*
void Graph_io::SetGraph(Graph setted){
    g = setted;
}

// NO IN USE ANY MORE!!!!!! Kept for reserve
template<typename T>
std::ostream& binary_write(std::ostream& stream, const T& value){
    return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template<typename T>
std::istream & binary_read(std::istream& stream, T& value){
    return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}
// END OF FALLBACK CODE


void Graph_io::Write(string data){
    Create();
    file.seekp(0);

    u_int16_t meta = g.type;
    file.write((char*)&meta,sizeof(meta));

    u_short vcount = g.getVertCount();
    u_short ecount = g.getEdgesCount();

    file.write((char*)&vcount,sizeof(u_short));
    file.write((char*)&ecount,sizeof(u_short));
    
    bool hvw = g.hasVW(); bool hew = g.hasEW();
    file.write((char*)&hvw,sizeof(bool));
    file.write((char*)&hew,sizeof(bool));
    

    if(hvw){
        for (u_short i =0; i<vcount;i++){
            auto w = g.getVWeigth(i);
            file.write((char*)&w,sizeof(u_short));
        }
    }

    if(hew){
        for(u_short i =0;i<ecount;i++){
            auto w = g.getEWeight(i);
            file.write((char*)&w,sizeof(u_short));
        }
    }

    for(u_short i =0; i<ecount;i++){
        auto ed = g.getEdge(i);
        file.write((char*)&ed.first,sizeof(u_short));
        file.write((char*)&ed.second,sizeof(u_short));
    }
   

    Close();
}

Graph* Graph_io::Read(){
    Open();
    u_short vnum, enums; bool hvw,hew;

    u_int16_t meta;

    file.read((char*)&meta, sizeof(meta));

    file.read((char*)&vnum,sizeof(u_short));
    file.read((char*)&enums,sizeof(u_short));
    file.read((char*)&hvw,sizeof(bool));
    file.read((char*)&hew,sizeof(bool));

    Graph* gr = new Graph(vnum);

    if(hvw){
        for (u_short i = 0; i < vnum; i++)
        {
            ushort temp;
            file.read((char*)&temp,sizeof(u_short));
            gr->addVWeight(temp);
        }
    }

    if(hew){
        for (u_short i = 0; i < enums; i++)
        {
            ushort temp;
            file.read((char*)&temp,sizeof(u_short));
            gr->addEWeight(temp);
        }
    }


    for (u_short i = 0; i < enums; i++)
    {
        u_short a,b;
        file.read((char*)&a,sizeof(u_short));
        file.read((char*)&b,sizeof(u_short));
        gr->addEdge(a,b);
    }
    
    gr->type = static_cast<GraphClassify> (meta);

    Close();
    return gr;
}
