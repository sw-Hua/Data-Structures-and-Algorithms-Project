#include "tree.hpp"

int main(){

    BST<int> t;

	t.add_vertex("C", 5);
	t.add_vertex("A", 1);
	t.add_vertex("H", 30);
	t.add_vertex("B", 3);
	t.add_vertex("D", 10);
	t.add_vertex("G", 20);
	t.add_vertex("E", 15);
	t.add_vertex("F", 17);
	t.add_vertex("B", 17);
	t.add_vertex("E", 17);

    //t.display();
    cout << t.num_vertices() << endl;
    cout << t.num_edges() << endl;
    cout << t.sum_weight() << endl;
    t.deleteInVector("v1");
    for(auto x : t.path("C", "H")){
        cout << x << " ";
    }

    for(auto x : t.path("D", "F")){
        cout << x << " ";
    }
    cout << endl;

    for(auto x : t.path("C", "B")){
        cout << x << " ";
    }
    cout << endl;
}
