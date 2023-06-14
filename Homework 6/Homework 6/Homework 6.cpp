
#include <iostream>
#include <vector>
using namespace std;

template < typename T > class CNodeDynamic
{
public:
    CNodeDynamic() { i_val = 0; };
    ~CNodeDynamic() {
        vPrT();
        for (T i = 0; i < v_children.size(); i++) {
            delete(v_children[i]);
        }
    };
    void vSetValue(T iNewVal) { i_val = iNewVal; };
    int iGetChildrenNumber() { return(v_children.size()); };
    void vAddNewChild() {
        v_children.push_back(new CNodeDynamic());
    };
    void vAddNewChild(CNodeDynamic* a) {
        v_children.push_back(a);
    };
    CNodeDynamic* pcGetChild(T iChildOffset) {
        return v_children[iChildOffset];
    };
    void vPrT() { cout << " " << i_val; };
    void vPrTAllBelow() {
        vPrT();
        for (T i = 0; i < v_children.size(); i++) {
            v_children[i]->vPrTAllBelow();
        }
    };
    void removeNode(CNodeDynamic* a) {
        for (T i = 0; i < v_children.size(); i++) {
            if (v_children[i] == a) {
                v_children.erase(v_children.begin() + i);
                break;
            }
        }

    }
private:
    vector<CNodeDynamic*> v_children;
    T i_val;
};//template < typename T > class CNodeDynamic
template < typename T > class CTreeDynamic
{
public:
    CTreeDynamic() {
        pc_root = new CNodeDynamic<T>();
    };
    ~CTreeDynamic() {
        delete(pc_root);
    };
    CNodeDynamic<T>* pcGetRoot() { return(pc_root); }
    void vPrTTree() {
        pcGetRoot()->vPrTAllBelow();
    };
    bool bMoveSubtree(CNodeDynamic<T>* pcParentNode, CNodeDynamic<T>* pcNewChildNode, CNodeDynamic<T>* pc2ParentNode) {
        pcParentNode->vAddNewChild(pcNewChildNode);
        pc2ParentNode->removeNode(pcNewChildNode);
        return true;
    };
private:
    CNodeDynamic<T>* pc_root;
};//template < typename T > class CTreeStatic;

void v_dynamic_tree_test()
{
    cout << "Dynamic tree test with int:" << endl;
    CTreeDynamic<int>* c_tree = new CTreeDynamic<int>();
    CNodeDynamic<int>* c_root = c_tree->pcGetRoot();
    c_root->vAddNewChild();
    c_root->vAddNewChild();
    c_root->pcGetChild(0)->vSetValue(1);
    c_root->pcGetChild(1)->vSetValue(2);
    c_root->pcGetChild(0)->vAddNewChild();
    c_root->pcGetChild(0)->vAddNewChild();
    c_root->pcGetChild(0)->pcGetChild(0)->vSetValue(11);
    c_root->pcGetChild(0)->pcGetChild(1)->vSetValue(12);
    c_root->pcGetChild(1)->vAddNewChild();
    c_root->pcGetChild(1)->vAddNewChild();
    c_root->pcGetChild(1)->pcGetChild(0)->vSetValue(21);
    c_root->pcGetChild(1)->pcGetChild(1)->vSetValue(22);
    c_root->vPrTAllBelow();
    cout << endl << "Destructor test:" << endl;
    delete(c_tree);
}

void v_dynamic_tree_test_double()
{
    cout << "\nDynamic tree test with double:" << endl;
    CTreeDynamic<double>* c_tree = new CTreeDynamic<double>();
    CNodeDynamic<double>* c_root = c_tree->pcGetRoot();
    c_root->vAddNewChild();
    c_root->vAddNewChild();
    c_root->pcGetChild(0)->vSetValue(1);
    c_root->pcGetChild(1)->vSetValue(2);
    c_root->pcGetChild(0)->vAddNewChild();
    c_root->pcGetChild(0)->vAddNewChild();
    c_root->pcGetChild(0)->pcGetChild(0)->vSetValue(11);
    c_root->pcGetChild(0)->pcGetChild(1)->vSetValue(12);
    c_root->pcGetChild(1)->vAddNewChild();
    c_root->pcGetChild(1)->vAddNewChild();
    c_root->pcGetChild(1)->pcGetChild(0)->vSetValue(21);
    c_root->pcGetChild(1)->pcGetChild(1)->vSetValue(22);
    c_root->vPrTAllBelow();
    cout << endl << "Destructor test:" << endl;
    delete(c_tree);
}

void v_move_subtree_test_dynamic()
{
    cout << "\nDynamic move subtree test:" << endl;
    CTreeDynamic<int>* c_tree = new CTreeDynamic<int>();
    CNodeDynamic<int>* c_root = c_tree->pcGetRoot();
    c_root->vAddNewChild();
    c_root->vAddNewChild();
    c_root->vAddNewChild();
    c_root->pcGetChild(0)->vSetValue(1);
    c_root->pcGetChild(1)->vSetValue(2);
    c_root->pcGetChild(2)->vSetValue(3);
    c_root->pcGetChild(2)->vAddNewChild();
    c_root->pcGetChild(2)->pcGetChild(0)->vSetValue(4);
    cout << "First tree:" << endl;
    c_tree->vPrTTree();
    cout << endl;

    CTreeDynamic<int>* c_tree2 = new CTreeDynamic<int>();
    CNodeDynamic<int>* c_root2 = c_tree2->pcGetRoot();
    c_root2->vSetValue(50);
    c_root2->vAddNewChild();
    c_root2->pcGetChild(0)->vSetValue(54);
    c_root2->vAddNewChild();
    c_root2->pcGetChild(1)->vSetValue(55);
    c_root2->pcGetChild(0)->vAddNewChild();
    c_root2->pcGetChild(0)->pcGetChild(0)->vSetValue(56);
    c_root2->pcGetChild(0)->vAddNewChild();
    c_root2->pcGetChild(0)->pcGetChild(1)->vSetValue(57);
    c_root2->pcGetChild(0)->pcGetChild(0)->vAddNewChild();
    c_root2->pcGetChild(0)->pcGetChild(0)->pcGetChild(0)->vSetValue(58);
    cout << "Second tree:" << endl;
    c_tree2->vPrTTree();
    cout << endl;
    c_tree->bMoveSubtree(c_root->pcGetChild(2), c_root2->pcGetChild(0), c_root2);
    cout << "First tree after moving:" << endl;
    c_tree->vPrTTree();
    cout << "\nSecond tree after moving:" << endl;
    c_tree2->vPrTTree();
}

int main()
{
    v_dynamic_tree_test();
    v_dynamic_tree_test_double();
    //v_move_subtree_test_dynamic();
}

