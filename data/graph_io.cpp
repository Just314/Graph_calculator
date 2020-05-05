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


//Open file for read
void Graph_io::Open(){
    file.open(file_name, ios::out | ios::in | ios::binary);
    if (file.fail()){
        throw  InadequateFile();
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

    //16 bits of meatdata from GraphClassify bitmask!!! DO NOT CHANGE OR FILES WILL BECOME CORRUPTED!!!
    //Changed in Graph model 2.0 version // serves as legacy and backward-compatible writer for Model v2 
    u_int16_t meta = g.type;
    file.write((char*)&meta,sizeof(meta));

    //------------------------------------------
    //------Meta set for correct file read------
    //------------------------------------------
    u_short vcount = g.getVertCount();
    u_short ecount = g.getEdgesCount();

    file.write((char*)&vcount,sizeof(u_short));
    file.write((char*)&ecount,sizeof(u_short));
    
    bool hvw = g.hasVW(); bool hew = g.hasEW();
    file.write((char*)&hvw,sizeof(bool));
    file.write((char*)&hew,sizeof(bool));
    //------------End of Meta set---------------

    //------------Set vertex weights------------
    //DEPRECATED!!!! DO NOT CHANGE OR FILES WILL BE CORRUPTED!!!
    if(hvw){
        for (u_short i =0; i<vcount;i++){
            auto w = g.getVWeigth(i);
            file.write((char*)&w,sizeof(u_short));
        }
    }

    //----------Set of edges weights------------

    // Does not utilized directly DO NOT CHANGE!!!
    if(hew){
        for(u_short i =0;i<ecount;i++){
            auto w = g.getEWeight(i);
            file.write((char*)&w,sizeof(u_short));
        }
    }

    //--------------EDGES SETTER---------------
    for(u_short i =0; i<ecount;i++){
        auto ed = g.getEdge(i);
        file.write((char*)&ed.first,sizeof(u_short));
        file.write((char*)&ed.second,sizeof(u_short));
    }
   

   //-------------Weight Matrix Setter-------------
    if(hvw){
        auto adj = g.MatrixWeighted();
        for (u_short i = 0; i < vcount; i++)
        {
            for (u_short j = 0; j < vcount; j++)
            {
                file.write((char*)&adj[i][j],sizeof(adj[0][0]));
            }
            
        }
        
    }

    //Close writing stream
    Close();
}

Graph* Graph_io::Read(){
    Open();

    //--------Meta definiton------------
    u_short vnum, enums; bool hvw,hew;

    u_int16_t meta;

    //----------------------------------
    //-----------Meta Reading-----------
    //----------------------------------
    file.read((char*)&meta, sizeof(meta));

    file.read((char*)&vnum,sizeof(u_short));
    file.read((char*)&enums,sizeof(u_short));
    file.read((char*)&hvw,sizeof(bool));
    file.read((char*)&hew,sizeof(bool));
    //----------End of meta read--------

    //Create new graph pointer for retern value
    // Is not weighted by default - if weighted, property will be automaticlly setted
    Graph* gr = new Graph(vnum);

    //----------Read Vertex Weights------------
    /////Deprecated///// DO NOT CHANGE!!!!!!
    if(hvw){
        for (u_short i = 0; i < vnum; i++)
        {
            ushort temp;
            file.read((char*)&temp,sizeof(u_short));
            gr->addVWeight(temp);
        }
    }

    //----------Read Edges Weights------------
    //IS NOT USED DIRECTLY -- DO NOT TOUCH
    if(hew){
        for (u_short i = 0; i < enums; i++)
        {
            ushort temp;
            file.read((char*)&temp,sizeof(u_short));
            gr->addEWeight(temp);
        }
    }

    //----------EDGES READ---------------
    for (u_short i = 0; i < enums; i++)
    {
        u_short a,b;
        file.read((char*)&a,sizeof(u_short));
        file.read((char*)&b,sizeof(u_short));
        gr->addEdge(a,b);
    }
    
    //-------------Weight Matrix Read----------
    if (hvw){
        for (u_short i = 0; i < vnum; i++)
        {
            for (u_short j = 0; j < vnum; j++)
            {
                u_short temp;
                file.read((char*)&temp,sizeof(temp));
                gr->setAWeight(i,j,temp);
            }
            
        }
        
    }

    //Set meta  --- currently is not used --- META IS KEPT FOR Graph Model v2
    gr->type = static_cast<GraphClassify> (meta);

    //Close reading stream
    Close();
    return gr;
}



/*   ----------- .AG   FILE FORMAT GUIDE  -------------
.         ------------------------------------
.         -------------Meta  Header-----------
.         ------------------------------------
.         ------- Tags bit mask - 16 bit -----
.         ------------------------------------
.         --------Vertex number - 16 bit -----
.         ------- Edges number - 16 bit ------
.         ------------------------------------
.         ----Has weighted Vertecies? - 1 bit-
.         ----Has weighted Edges? - 1 bit-----
.         ------------------------------------
.         --------- End of Meta Header -------
.         ------------------------------------
.         ----------------DATA----------------
.         ------------------------------------
.         ---Edges - 32 * dec(Edges Number)---
.         --Weight Matrix - 16 * (Vert Num)^2-
.         ------------------------------------
.         -------------END OF DATA------------
.         ------------------------------------
*/