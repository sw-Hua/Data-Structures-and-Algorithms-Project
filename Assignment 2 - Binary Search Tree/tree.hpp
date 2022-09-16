#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

template<typename T> // the template allows the weight of vertex to take any numeric data type (denoted by T).
class BST {

public:
/* define your data structure to represent a binary search tree (bst) */
    struct node {
        string name;
        int weight;
        node *left;
        node *right;
    };

    node *root;
    vector<node *> nodeVector;
    int count = 0; // vertex and edge number
    int weightSum = 0; // sum of all weight
    node *makeEmpty(node *t) {
        //Initialization, see if it can be put into the construction method
        if (t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node *insert(int weight, string name, node *t) {
        if (t == NULL) {
            t = new node;
            t->weight = weight;
            t->name = name;
            t->left = t->right = NULL;
            nodeVector.push_back(t);
        } else if (contains(name))
            return t;
        else if (weight < t->weight)//<
            t->left = insert(weight, name, t->left);
        else if (weight >= t->weight)
            t->right = insert(weight, name, t->right);
        return t;
    }

    void numberOfVertex(node *t) {
        if (t == NULL)
            return;
        numberOfVertex(t->left);
        count++;
        numberOfVertex(t->right);
    }

    void inorder(node *t) {
        if (t == NULL)
            return;
        inorder(t->left);

        if (t->left != NULL && t->right != NULL) {
            cout << "[Name: " << t->name << ", Weight: " << t->weight << ", left: " << t->left->name << ", right: "
                 << t->right->name << "]" << endl;
        } else if (t->left == NULL && t->right == NULL) {
            cout << "[Name: " << t->name << ", Weight: " << t->weight << ", left: NULL" << ", right: NULL" << "]"
                 << endl;
        } else if (t->left == NULL) {
            cout << "[Name: " << t->name << ", Weight: " << t->weight << ", left: NULL" << ", right: " << t->right->name
                 << "]" << endl;
        } else if (t->right == NULL) {
            cout << "[Name: " << t->name << ", Weight: " << t->weight << ", left: " << t->left->name << ", right: NULL"
                 << "]" << endl;
        }
        inorder(t->right);
    }

    vector<string> PreorderVector;

    void Preorder(node *t) {
        if (t == NULL)
            return;
        PreorderVector.push_back(t->name);
        Preorder(t->left);
        Preorder(t->right);
    }


    vector<string> inVec;

    void inorderVector(node *t) {
        if (t == NULL)
            return;
        inorderVector(t->left);
        inVec.push_back(t->name);
        inorderVector(t->right);
    }

    vector<string> PostorderVector;

    void Postorder(node *t) {
        if (t == NULL)
            return;

        Postorder(t->left);
        Postorder(t->right);
        PostorderVector.push_back(t->name);
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    void sumOfWeight(node *t) {
        if (t == NULL)
            return;
        sumOfWeight(t->left);
        weightSum += t->weight;
        sumOfWeight(t->right);
    }

    bool isExist(const string &u) {
        for (auto t : nodeVector)
            if (u == t->name)
                return true;
        return false;
    }

    vector<string> allVertex;

    void getAllVertex() {
        for (auto x : nodeVector) {
            //cout << x->name << " ";
            allVertex.push_back(x->name);
        }
    }


    vector<string> getAllLeaves() {
        vector<string> leaves;
        for (auto x : nodeVector) {
            if (x->left == NULL && x->right == NULL) {
                leaves.push_back(x->name);
            }
        }
        return leaves;
    }

    bool isNeigh(string u, string v) {
        for (auto x : nodeVector) {
            if (x->name == u) {
                if (x->left != NULL) {
                    if (x->left->name == v)
                        return true;
                }
                if (x->right != NULL) {
                    if (x->right->name == v)
                        return true;
                    else
                        return false;
                }
            } else if (x->name == v) {
                if (x->left != NULL) {
                    if (x->left->name == u)
                        return true;
                }
                if (x->right != NULL) {
                    if (x->right->name == u)
                        return true;
                    else
                        return false;
                }
            }
        }
        return false;
    }

    node *minValueNode(node *t) {
        node *current = t;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }


    int maxDepth(node *t) {
        if (t == NULL)
            return 0;
        else {
            int lDepth = maxDepth(t->left);
            int rDepth = maxDepth(t->right);


            if (lDepth > rDepth)
                return (lDepth + 1);
            else
                return (rDepth + 1);
        }
    }


    void bfs(node *root) {
        int h = maxDepth(root);
        int i;
        for (i = 1; i <= h; i++)
            GivenLevel(root, i);
    }

    vector<string> bfsVector;

    void GivenLevel(node *root, int level) {
        if (root == NULL)
            return;
        if (level == 1)
            //cout <<"[ " <<root->name << ",  " << root->weight << " ]" <<endl;
            bfsVector.push_back(root->name);
        else if (level > 1) {
            GivenLevel(root->left, level - 1);
            GivenLevel(root->right, level - 1);
        }
    }

    bool isLeaves(string u) {
        for (auto x : get_leaves()) {
            if (x == u) {
                return true;
            }
        }
        return false;
    }

    void deleteInVector(string name) {
        for (typename vector<node *>::iterator it = nodeVector.begin(); it != nodeVector.end();) {
            if ((*it)->name == name) {
                it = nodeVector.erase(it);
            } else
                it++;
        }
    }

    void remove(string name) {
        for (typename vector<node *>::iterator it = nodeVector.begin(); it != nodeVector.end();) {
            if ((*it)->name == name) {
                it = nodeVector.erase(it);
            } else
                it++;
        }


        for (typename vector<node *>::iterator it = nodeVector.begin(); it != nodeVector.end();) {
            cout << (*it)->name << endl;
            it++;
        }
    }

    node *deleteVertex(node *t, int w) {
        /*
        int currentWeight; // Input U I know, weight
        for(auto x: nodeVector){
            // Traversing the loop, I get currentWeight
            if (x->name == u){
                currentWeight = x->weight;
            }
        }

         */
        if (t == NULL) {
            return NULL;
        } else if (w < t->weight) {
            t->left = deleteVertex(t->left, w);
        } else if (w > t->weight) {
            t->right = deleteVertex(t->right, w);//Through this step, I find the address value of u where weight is
        } else {

            /*
             * I already find weight here
             * cout << "[ " << t->name << ", " << t->weight << " ]"<<endl;
             * There are three cases: 1 is that leaves directly returns null, which is the right child node
             */


            if (isLeaves(t->name)) {
                t = NULL;
            }

                //Only one child
            else if (t->left == NULL) {
                node *temp = t->right;
                t = NULL;
                return temp;
            } else if (t->right == NULL) {
                node *temp = t->left;
                t = NULL;
                return temp;
            } else {
                node *temp = minValueNode(t->right);
                t->weight = temp->weight;
                t->name = temp->name;
                t->right = deleteVertex(t->right, t->weight);
            }
        }

        return t;
    }

    int ct = 0;

    void refresh(node *t) {
        if (ct == 0) {
            nodeVector.clear();
            ct++;
        }
        if (t == NULL)
            return;
        refresh(t->left);
        nodeVector.push_back(t);
        refresh(t->right);
    }

    int findMaxUtil(node* t, int &res)
    {
        //Base Case
        if (t == NULL)
            return 0;

        //L and R store the maximum path sum through the left and right
        //The right child of y-radical
        int l = findMaxUtil(t->left,res);
        int r = findMaxUtil(t->right,res);

        int max_single = max(max(l, r) + t->weight, t->weight);

        int max_top = max(max_single, l + r + root->weight);

        res = max(res, max_top); // Store max value.

        return max_single;
    }

// Returns maximum path sum in tree with given root
    int findMaxSum(node* t)
    {
        // Initialize result
        int res = 0;

        // Compute and return result
        findMaxUtil(t, res);
        return res;
    }

    bool getPath(node* root, vector<int>& arr, int x)
    {
        if (!root)
            return false;
        arr.push_back(root->weight);

        if (root->weight == x)
            return true;
        if (getPath(root->left, arr, x) || getPath(root->right, arr, x))
            return true;
        arr.pop_back();
        return false;
    }
    string findString(int i){
        for(auto x : nodeVector){
            if(x->weight == i){
                return x->name;
            }
        }
        return "";
    }

    int findInt(string s){
        for(auto x : nodeVector){
            if(x->name == s){
                return x->weight;
            }
        }
        return 0;
    }


    vector<int> allPath;
    void PathBetweenNodes(node* root, int n1, int n2)
    {
        vector<string> path;
        vector<int> path1;
        vector<int> path2;

        getPath(root, path1, n1);
        getPath(root, path2, n2);

        int intersection = -1;

        int i = 0, j = 0;
        while (i != path1.size() || j != path2.size()) {
            if (i == j && path1[i] == path2[j]) {
                i++;
                j++;
            }
            else {
                intersection = j - 1;
                break;
            }
        }

        for (int i = path1.size() - 1; i > intersection; i--)
            allPath.push_back(path1[i]);

        for (int i = intersection; i < path2.size(); i++)
            allPath.push_back(path2[i]);
    }

/* test1 */
    BST(); // the contructor function.
    ~BST(); // the destructor function.
    //node* makeEmpty(node* t);
    size_t num_vertices(); // returns the total number of vertices in the bst.
    size_t num_edges(); // returns the total number of edges in the bst.
    T sum_weight(); // return the total weight of all the vertices in the bst.

/* test2 */
    void add_vertex(const string &,
                    const T &); // adds a vertex, which has a weight, to the tree -- every vertex uses a string as its unique identifier.
    bool contains(
            const string &); // checks if a vertex is in the bst -- returns true if the bst contains the given vertex; otherwise, returns false.

/* test3 */
    vector<string> get_vertices(); // returns a vector of all the vertices in the bst.
    vector<string> get_leaves(); // returns a vector of all the leaves in the bst.
// Leaves are the vertices that do not have any children in the bst.

/* test4 */
    bool adjacent(const string &,
                  const string &); // check if there is an edge between the two vertices in the bst -- returns true if the edge exists; otherwise, returns false.

/* test5 */
    vector<pair<string, string>>
    get_edges(); // returns a vector of all the edges in the bst -- each edge is represented by a pair of vertices incident to the edge.

/* test6 */
    vector<string> get_neighbours(
            const string &); // returns a vector of all the vertices, each of which is directly connected with the given vertex via an edge.
    size_t degree(const string &); // returns the degree of a vertex.

/* test7 */
    vector<string>
    preorder_traversal(); // returns a vector of all the vertices in the visiting order of a preorder traversal over the bst.

/* test8 */
    vector<string>
    inorder_traversal(); // returns a vector of all the vertices in the visiting order of an inorder traversal over the bst.

/* test9 */
    vector<string>
    postorder_traversal(); // returns a vector of all the vertices in the visiting order of a postorder traversal over the bst.

/* test10 */
    vector<string>
    breadth_first_traversal(); // returns a vector of all the vertices in the visiting order of a breadth first traversal over the bst.

/* test11 */
    vector<string> path(const string &,
                        const string &); // returns a vector of all the vertices in the path from the first vertex to the second vertex.
// A path should include the source and destination vertices at the begining and the end, respectively.

/* test12 */
    vector<string> path_with_largest_weight(); // returns a path that has the largest weight in the bst.
// The weight of a path is the sum of the weights of all the vertices (including the source and destination vertices) in the path.

/* test13 */
    size_t
    height(); // returns the height of bst. Height of a tree is the number of edges that form the longest path from root to any leaf.

/* test14 */
    void remove_vertex(
            const string &); // delete the given vertex from bst -- note that, all incident edges of the vertex should be deleted as well.

};

/* test1 */

template<typename T>
BST<T>::BST() {
    root = NULL;
}

template<typename T>
BST<T>::~BST() {
    root = makeEmpty(root);
}


template<typename T>
size_t BST<T>::num_vertices() {
    return nodeVector.size();
}

template<typename T>
size_t BST<T>::num_edges() {
    if (nodeVector.empty()) {
        return 0;
    } else {
        return nodeVector.size() - 1;
    }
}

template<typename T>
T BST<T>::sum_weight() {
    int sum = 0;
    for (auto x : nodeVector) {
        sum += x->weight;
    }
    return sum;

}

/* test2 */

template<typename T>
void BST<T>::add_vertex(const string &u, const T &w) {
    root = insert(w, u, root);
}

template<typename T>
bool BST<T>::contains(const string &u) {
    return isExist(u);
}

/* test3 */

template<typename T>
vector<string> BST<T>::get_vertices() {
    getAllVertex();
    return allVertex;
}

template<typename T>
vector<string> BST<T>::get_leaves() {
    return getAllLeaves();
}

/* test4 */

template<typename T>
bool BST<T>::adjacent(const string &u, const string &v) {
    return isNeigh(u, v);
}

/* test5 */

template<typename T>
vector<pair<string, string>> BST<T>::get_edges() {

    vector<pair<string, string>> edgesVector;

    for (int i = 0; i < nodeVector.size(); ++i) {
        //cout << nodeVector[i]->name << " ";
        if (nodeVector[i]->left != NULL && nodeVector[i]->right != NULL) {
            //左右都不为空
            edgesVector.push_back(make_pair(nodeVector[i]->name, nodeVector[i]->left->name));
            edgesVector.push_back(make_pair(nodeVector[i]->name, nodeVector[i]->right->name));
        } else if (nodeVector[i]->left != NULL) {
            edgesVector.push_back(make_pair(nodeVector[i]->name, nodeVector[i]->left->name));
        } else if (nodeVector[i]->right != NULL) {
            edgesVector.push_back(make_pair(nodeVector[i]->name, nodeVector[i]->right->name));
        }
    }

    return edgesVector;
}


/* test6 */

template<typename T>
vector<string> BST<T>::get_neighbours(const string &u) {
    vector<string> neigh;
    for (auto x: nodeVector) {
        if (x->name == u) {
//Find the node we are looking for
//Return to neighbors
//Find neighbors below
//Search by U axis
            if (x->left != NULL && x->right != NULL) {
                neigh.push_back(x->left->name);
                neigh.push_back(x->right->name);
            } else if (x->left != NULL) {
                neigh.push_back(x->left->name);
            } else if (x->right != NULL) {
                neigh.push_back(x->right->name);
            }

        }
    }

    for (auto x: nodeVector) {
        /*
         * Directly traverse all to find the position of U
         */
        if (x->left != NULL && x->right != NULL) {
            if (x->left->name == u) {
                neigh.push_back(x->name);
            } else if (x->right->name == u) {
                neigh.push_back(x->name);
            }
        } else if (x->left != NULL) {
            if (x->left->name == u) {
                neigh.push_back(x->name);
            }
        } else if (x->right != NULL) {
            if (x->right->name == u) {
                neigh.push_back(x->name);
            }
        }
    }

    return neigh;
}


template<typename T>
size_t BST<T>::degree(const string &u) {
    return get_neighbours(u).size();
}

/* test7 */

template<typename T>
vector<string> BST<T>::preorder_traversal() {
    Preorder(root);
    return PreorderVector;
}

/* test8 */

template<typename T>
vector<string> BST<T>::inorder_traversal() {
    inorderVector(root);
    return inVec;
}

/* test9 */

template<typename T>
vector<string> BST<T>::postorder_traversal() {
    Postorder(root);
    return PostorderVector;
}

/* test10 */

template<typename T>
vector<string> BST<T>::breadth_first_traversal() {
    bfs(root);
    return bfsVector;
}

/* test11 */

template<typename T>
vector<string> BST<T>::path(const string &u, const string &v) {
    /*
     * I didn't done it in ed :( almost finish it.
     */
    vector<string> stringPath;
    PathBetweenNodes(root, findInt(u), findInt(v));
    for(auto x : allPath){
        stringPath.push_back(findString(x));
    }
    //stringPath.push_back(v);

    return stringPath;

}

/* test12 */

template<typename T>
vector<string> BST<T>::path_with_largest_weight() {
    return vector<string>();
}

/* test13 */

template<typename T>
size_t BST<T>::height() {
    return maxDepth(root) - 1;
}

/* test14 */

template<typename T>
void BST<T>::remove_vertex(const string &u) {

    //deleteInVector(u);
    int currentWeight = 0;
    for (auto x: nodeVector) {
        // Traversing the loop, I get currentWeight
        if (x->name == u) {
            currentWeight = x->weight;
        }
    }

    deleteVertex(root, currentWeight);
    refresh(root);
}
