#include <bits/stdc++.h>

using namespace std;

template <typename T> // the template allows the weight of an edge to take any numeric data type (denoted by T).
class Graph {

public:

    /* define your data structure to represent a weighted undirected graph */
    vector<string> vertexVector; // The Vector that store Vertex
    vector<pair<string, pair<string, T>>> adj;//The main structure to store data {key: string/from, map(key: string/destination, value: int/weight)}
    vector<string> DFSList;
    map<string, bool> IsBool;// Make boolean judgment in DFSList

    /* test1 */
    Graph(); // the contructor function.
    ~Graph(); // the destructor function.
    size_t num_vertices(); // returns the total number of vertices in the graph.
    size_t num_edges(); // returns the total number of edges in the graph.

    /* test2 */
    void add_vertex(const string&); // adds a vertex to the graph -- every vertex uses a string as its unique identifier.
    bool contains(const string&); // checks if a vertex is in the graph -- returns true if the graph contains the given vertex; otherwise, returns false.
    //void test();
    /* test3 */
    vector<string> get_vertices(); // returns a vector of all the vertices in the graph.返回图中所有顶点的向量。

    /* test4 */
    void add_edge(const string&, const string&, const T&); // adds a weighted edge to the graph -- the two strings represent the incident vertices; the third parameter represents the edge's weight.
    bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the graph -- returns true if the edge exists; otherwise, returns false.

    /* test5 */
    vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the graph -- each edge is represented by a pair of vertices incident to the edge.

    /* test6 */
    vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex by an edge.
    size_t degree(const string&); // returns the degree of a vertex.

    /* test7 */
    void remove_edge(const string&, const string&); // removes the edge between two vertices, if it exists.

    /* test8 */
    void remove_vertex(const string&); // delete the given vertex from the graph -- note that, all incident edges of the vertex should be deleted as well.

    /* test9 */
    vector<string> depth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a depth-first traversal from the given vertex.
    //vector<pair<string, pair<string, int>>> orderVector();
    void initialIsBool();
    /* test10 */
    vector<string> breadth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a breadth-first traversal from the given vertex.

    /* test11 */
    bool contain_cycles(); // check if the graph contains any cycle -- returns true if there exists a path from a vertex to itself; otherwise, return false.
    bool cycle_helper(string node, map<string, bool> visited, string parent);
    /* test12 */
    Graph<T> minimum_spanning_tree(); // returns a spanning tree of the graph -- the returned tree is preferably a minimum spanning tree.

};

/* test1 */

template <typename T>
Graph<T>::Graph() {}

template <typename T>
Graph<T>::~Graph() {}


template <typename T>
size_t Graph<T>::num_vertices() {
    return vertexVector.size();// get the size of VertexVector
}

template <typename T>
size_t Graph<T>::num_edges() {
    return adj.size()/2; //Because it is unweighted graph. So we need divide 2
}

/* test2 */

template <typename T>
void Graph<T>::add_vertex(const string& u) {
    vertexVector.push_back(u); // add u value in vertexVector
}

/*
template <typename T>
void Graph<T>:: test(){
    // test is  adj work?
    for(typename vector<pair<string, pair<string, int>>>::const_iterator it = adj.begin(); it!=adj.end(); it++){
        cout << "{" << it->first << " ," << it->second.first << ", " << it->second.second <<"}";
    }
    cout<< endl;
}
*/

template <typename T>
bool Graph<T>::contains(const string& u) {
    // First I traverse vertexVector. Then if the value in vertexVector is equal to u. I return true. else it's false.
    for(vector<string>::const_iterator it = vertexVector.begin(); it!=vertexVector.end(); it++){
        if (*it == u){
            return true;
        }
    }
    return false;
}

/* test3 */

template <typename T>
vector<string> Graph<T>::get_vertices() {
    // directly return vertexVector
    return vertexVector;
    //cout << "{" << v.first << " ," << v.second.first << ", " << v.second.second <<"}"<< endl;
}

/* test4 */

template <typename T>
void Graph<T>::add_edge(const string& u, const string& v, const T& weight) {
    // Notice that I have to add both heads and tails because it's an undirected graph
    adj.push_back(make_pair(u, make_pair(v, weight)));
    adj.push_back(make_pair(v, make_pair(u, weight)));
}

template <typename T>
bool Graph<T>::adjacent(const string& u, const string& v) {
    /*check if there is an edge between the two vertices in the graph --
     * returns true if the edge exists; otherwise, returns false.
     *
     * */
    for(auto it = adj.begin(); it!=adj.end(); it++){
        //cout<< "it->first: "<<it->first <<" it->second.first:" << it->second.first<< endl;
        //cout<< "U is "<<u <<" ; V is " << v<< endl;
        if (it->first==u && it->second.first==v){
            return true;
        }
    }

    return false;
}

/* test5 */

template <typename T>
vector<pair<string,string>> Graph<T>::get_edges() {
    /*
     * returns a vector of all the edges in the graph --
     * each edge is represented by a pair of vertices incident to the edge.
     *
     *vector<pair<string,string>>
     */
    vector<pair<string,string>> ve2;
    // Because I only need One route. So I don't want an odd number of values
    T i = 0;
    for(typename vector<pair<string, pair<string, T>>>::const_iterator it = adj.begin(); it!=adj.end(); it++) {
        if (i%2==0){
            ve2.push_back(make_pair(it->first, it->second.first));
        }
        i++;
    }
    /*
    for(typename  vector<pair<string,string>>::const_iterator it = ve2.begin(); it!=ve2.end(); it++){
        cout << "{" << it->first << " ," << it->second << "} ";
    }
    cout<<endl;
    */
    //cout << ve2[1].first <<endl;
    return ve2;
}

/* test6 */

template <typename T>
vector<string> Graph<T>::get_neighbours(const string& u) {
    /*
     * returns a vector of all the vertices,
     * each of which is directly connected with the given vertex by an edge.
     * get_edges
     * traverse the vertex, and determine if it is the same as u. If it is, add it into neighbours.
     */
    vector<string> neighbours={};
    //cout<<"size: "<<get_vertices().size()<<endl;
    for(T i = 0; i < get_vertices().size(); i++){
        //{A ,B} {A ,C} {C ,D} {C ,E} {B ,E} {A ,E}
        if (get_edges()[i].first==u){
            //cout<<*get_vertices()[i]->second<<endl;
            neighbours.push_back(get_edges()[i].second);
        }

        if (get_edges()[i].second==u){
            //cout<<*get_vertices()[i]->first<<endl;
            neighbours.push_back(get_edges()[i].first);
        }

        //cout<<get_edges()[i].first<<endl;
    }
    /*
    for(vector<string>::const_iterator it = neighbours.begin(); it!=neighbours.end(); it++){
        cout<<" { "<<*it<<""<< " } "<<endl;
    }
     */

    return neighbours;
}

template <typename T>
size_t Graph<T>::degree(const string& u) {
    T i = 0;
    for(auto it = adj.begin(); it!=adj.end(); it++){
        if((it->first == u) || (it->second.first==u)){
            i++;
        }
    }
    return i/2;
    // I enter vertex vertex and determine how many edges are nearby
}

/* test7 */

template <typename T>
void Graph<T>::remove_edge(const string& u, const string& v) {
    for(auto it = adj.begin(); it!=adj.end(); it++){
        if((it->first == u && it->second.first==v) || (it->first == v && it->second.first==u)){
            //cout<<"The starting vertex for: "<<it->first<<" The finish vertex for: "<<it->second.first<<endl;
            it = adj.erase(it);
            it--;
        }
    }
    //cout<< endl;
    initialIsBool();
}

/* test8 */

template <typename T>
void Graph<T>::remove_vertex(const string& u) {
    for(vector<string>::const_iterator it = vertexVector.begin(); it!=vertexVector.end(); it++) {
        /*
         * Deletes the VertexVector nodes
         */
        if (*it == u){
            it = vertexVector.erase(it);
            it--;
        }
    }

    for(auto it = adj.begin(); it!=adj.end(); it++){
        if(it->first == u || it->second.first==u){
            /*
            * Delete the corresponding edge
            */
            //cout<<"The starting vertex: "<<it->first<<"The ending vertex: "<<it->second.first<<endl;
            it = adj.erase(it);
            it--;
        }
    }
    //cout<<endl;
    // Edges and Vertex are removed
}

/* test9 */

template <typename T>
vector<string> Graph<T>::depth_first_traversal(const string& u) {
    IsBool[u] = true; //A 0 B 1 C 0 D 0 E 0 F 0
    DFSList.push_back(u);

    for(auto it = adj.begin(); it!=adj.end(); it++) {
        if (it->first == u){
            //cout << "This number right here is: " << it->second.first<<", ";
            if (!IsBool[it->second.first]) {
                //cout <<it->second.first<< " is false in IsBool" << endl;
                depth_first_traversal(it->second.first);
            }
        }
    }
    return DFSList;
}
/*
template <typename T>
vector<pair<string, pair<string, int>>> Graph<T>::orderVector() {
    //return {A ,B, 7}{A ,C, 2}{A ,E, 6}{B ,A, 7}{B ,E, 10}{C ,A, 2}{C ,D, 4}{C ,E, 8}{D ,C, 4}{E ,C, 8}{E ,B, 10}{E ,A, 6}

    vector<pair<string, pair<string, T>>> orderedVector;
    for(vector<string>::const_iterator it = vertexVector.begin(); it!=vertexVector.end(); it++) {
        for (int i = 0; i < adj.size(); ++i) {
            if (*it == adj[i].first){
                orderedVector.push_back(adj[i]);
            }
        }
    }


    for(vector<pair<string, pair<string, int>>>::const_iterator it = orderedVector.begin(); it!=orderedVector.end(); it++) {
        cout << "{" << it->first << " ," << it->second.first << ", " << it->second.second <<"}";
    }

    return orderedVector;
}
*/
template <typename T>
void Graph<T>:: initialIsBool(){
    for (T i = 0; i < vertexVector.size(); ++i) {
        IsBool[vertexVector[i]] = false;
    }
    /*
    for(auto it = IsBool.begin(); it!=IsBool.end(); it++) {
        cout<<" " <<it->first<< " " << it->second <<" "<<endl;
    }
     */

}
/* test10 */

template <typename T>
vector<string> Graph<T>::breadth_first_traversal(const string& u) {
    //{A ,B, 7}{B ,A, 7}{A ,C, 2}{C ,A, 2}{C ,D, 4}{D ,C, 4}{C ,E, 8}{E ,C, 8}{B ,E, 10}{E ,B, 10}{A ,E, 6}{E ,A, 6}
    vector<string> bfsList;
    map<string, bool> visited;
    queue<string> q;//Set up a first in first out, last in last out queue

    q.push(u);//Add the number we started with to the queue
    visited[u] = true; //Then set that the number has already been accessed
    while(!q.empty()){
        string node = q.front();
        q.pop();
        //cout << node << " ";
        bfsList.push_back(node);
        for(string nbr: get_neighbours(node)){
            if (!visited[nbr])
                q.push(nbr);
            // mark that nbr as visited
            visited[nbr] = true;
        }
    }

    return bfsList;
}

/* test11 */
template <typename T>
bool Graph<T>::cycle_helper(string node, map<string, bool> visited, string parent){
    visited[node] = true;// So we're going to go ahead and find the value is true, which means it's traversed
    for(auto nbr:get_neighbours(node)){
        // two cases
        if (!visited[nbr]){//If not visited
            //go and recursively visit the nbr
            bool cycle_mila = cycle_helper(nbr, visited, node);
            if (cycle_mila){
                return true;
            }
        }else if(nbr!=parent){
            // neighbour is visited but nbr should not be equal to parent
            return true;
        }
    }
    return false;
}


template <typename T>
bool Graph<T>::contain_cycles() {
    /*
     * check if the graph contains any cycle -- returns true if there exists a path from a vertex to itself; otherwise, return false.
     */
    //bool *visited = new bool [vertexVector.size()];//Create a new array of visited functions to store the data
    /*
    map<string, bool> visited;
    for (int i = 0; i < vertexVector.size(); ++i) {
        //Visited[i] = false;
        visited[vertexVector[i]] = false;
    }

    for(auto it = visited.begin(); it!=visited.end(); it++) {
        cout<<" "<< it->first << ", "<< it->second<< " " << endl;
    }
*/
    //return cycle_helper(vertexVector[0], visited, "null");
    return  false;
}

/* test12 */

template <typename T>
Graph<T> Graph<T>::minimum_spanning_tree() {

    return Graph<T>();
}
