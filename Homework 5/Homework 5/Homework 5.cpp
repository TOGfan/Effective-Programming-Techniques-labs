
#include <iostream>
#include <vector>
using namespace std;

class CNodeStatic{
public:
    CNodeStatic() { 
        i_val = 0;
        parent = NULL;
    };
    CNodeStatic(CNodeStatic* f_parent) {
        parent = f_parent;
    }
    CNodeStatic(CNodeStatic* f_parent, CNodeStatic*a) {
        copy(a);
        parent = f_parent;
    }
    ~CNodeStatic() {
        //vPrint();
    };
    void vSetValue(int iNewVal) { i_val = iNewVal; };
    int iGetChildrenNumber() { return(v_children.size()); };
    void vAddNewChild() {
        v_children.push_back(*new CNodeStatic(this));
    };
    void vAddNewChild(CNodeStatic*a) {
        v_children.push_back(*new CNodeStatic(this,a));
        //*a->parent = this;
    };
    void copy(CNodeStatic* a) {
        i_val = a->i_val;
        //parent = a->parent;
        v_children.clear();
        for (int i = 0; i < a->iGetChildrenNumber(); i++) {
            vAddNewChild(a->pcGetChild(i));
        }
    }
    CNodeStatic* pcGetChild(int iChildOffset) {
        return &v_children[iChildOffset];
    };
    void vPrint() { cout << " " << i_val; };
    void vPrintAllBelow() {
        vPrint();
        for (int i = 0; i < v_children.size(); i++) {
            v_children[i].vPrintAllBelow();
        }
    };
    void vPrintUp() {
        vPrint();
        if(parent!=NULL)
            parent->vPrintUp();
    }
    int iPrintDistanceToNode() {
        if (parent == NULL)
            return 0;
        return 1 + parent->iPrintDistanceToNode();
    }
    void removeNode(CNodeStatic* a) {
        for (int i = 0; i < v_children.size(); i++) {
            if (v_children[i].i_val==a->i_val) {
                v_children.erase(v_children.begin() + i);
                break;
            }
        }

        //v_children.erase(v_children.begin());
    }
private:
    vector<CNodeStatic> v_children;
    int i_val;
    CNodeStatic* parent;
};


class CTreeStatic
{
public:
    CTreeStatic() {
        //c_root =new CNodeStatic();
        //c_root.vSetValue(1);
    };
    ~CTreeStatic() {};
    CNodeStatic* pcGetRoot() { return(&c_root); }
    void vPrintTree() {
        pcGetRoot()->vPrintAllBelow();
    };
    bool bMoveSubtree(CNodeStatic* pcParentNode, CNodeStatic* pcNewChildNode, CNodeStatic* pc2ParentNode) {
        pcParentNode->vAddNewChild(pcNewChildNode);
        pc2ParentNode->removeNode(pcNewChildNode);
        return true;
    };

private:
    CNodeStatic c_root;
};//class CTreeStatic

class CNodeDynamic
{
public:
    CNodeDynamic() { i_val = 0; };
    ~CNodeDynamic() {
        vPrint();
        for (int i = 0; i < v_children.size(); i++) {
            delete(v_children[i]);
        }
    };
    void vSetValue(int iNewVal) { i_val = iNewVal; };
    int iGetChildrenNumber() { return(v_children.size()); };
    void vAddNewChild() {
        v_children.push_back(new CNodeDynamic());
    };
    void vAddNewChild(CNodeDynamic*a) {
        v_children.push_back(a);
    };
    CNodeDynamic* pcGetChild(int iChildOffset) {
        return v_children[iChildOffset];
    };
    void vPrint() { cout << " " << i_val; };
    void vPrintAllBelow() {
        vPrint();
        for (int i = 0; i < v_children.size(); i++) {
            v_children[i]->vPrintAllBelow();
        }
    };
    void removeNode(CNodeDynamic* a) {
        for (int i = 0; i < v_children.size(); i++) {
            if (v_children[i] == a) {
                v_children.erase(v_children.begin()+i);
                break;
            }
        }

    }
private:
    vector<CNodeDynamic*> v_children;
    int i_val;
};//class CNodeDynamic
class CTreeDynamic
{
public:
    CTreeDynamic() {
        pc_root = new CNodeDynamic();
    };
    ~CTreeDynamic() {
        delete(pc_root);
    };
    CNodeDynamic* pcGetRoot() { return(pc_root); }
    void vPrintTree() {
        pcGetRoot()->vPrintAllBelow();
    };
    bool bMoveSubtree(CNodeDynamic* pcParentNode, CNodeDynamic* pcNewChildNode, CNodeDynamic* pc2ParentNode) {
        pcParentNode->vAddNewChild(pcNewChildNode);
        pc2ParentNode->removeNode(pcNewChildNode);
        return true;
    };
private:
    CNodeDynamic* pc_root;
};//class CTreeStatic;



void v_static_tree_test()
{
    cout << "Static tree test:" << endl;
    CTreeStatic c_tree;
    CNodeStatic c_root=c_tree.pcGetRoot();
    c_root.vSetValue(1);
    c_root.vAddNewChild();
    c_root.vAddNewChild();
    c_root.pcGetChild(0)->vSetValue(1);
    c_root.pcGetChild(1)->vSetValue(2);
    c_root.pcGetChild(0)->vAddNewChild();
    c_root.pcGetChild(0)->vAddNewChild();
    c_root.pcGetChild(0)->pcGetChild(0)->vSetValue(11);
    c_root.pcGetChild(0)->pcGetChild(1)->vSetValue(12);
    c_root.pcGetChild(1)->vAddNewChild();
    c_root.pcGetChild(1)->vAddNewChild();
    c_root.pcGetChild(1)->pcGetChild(0)->vSetValue(21);
    c_root.pcGetChild(1)->pcGetChild(1)->vSetValue(22);
    c_root.vPrintAllBelow();
    cout << endl<<"Print up test:"<<endl;
    c_root.pcGetChild(0)->pcGetChild(1)->vPrintUp();
    cout << "\nDistance between the root and the specified node is:\n ";
    cout<<c_root.pcGetChild(0)->pcGetChild(1)->iPrintDistanceToNode();

    //cout <<endl<<"Destructor test:" << endl;
}

void v_dynamic_tree_test()
{
    cout << "\nDynamic tree test:" << endl;
    CTreeDynamic* c_tree = new CTreeDynamic();
    CNodeDynamic* c_root=c_tree->pcGetRoot();
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
    c_root->vPrintAllBelow();
    cout << endl << "Destructor test:" << endl;
    delete(c_tree);
}

void v_move_subtree_test_dynamic()
{
    cout << "\nDynamic move subtree test:" << endl;
    CTreeDynamic* c_tree = new CTreeDynamic();
    CNodeDynamic* c_root = c_tree->pcGetRoot();
    c_root->vAddNewChild();
    c_root->vAddNewChild();
    c_root->vAddNewChild();
    c_root->pcGetChild(0)->vSetValue(1);
    c_root->pcGetChild(1)->vSetValue(2);
    c_root->pcGetChild(2)->vSetValue(3);
    c_root->pcGetChild(2)->vAddNewChild();
    c_root->pcGetChild(2)->pcGetChild(0)->vSetValue(4);
    cout << "First tree:" << endl;
    c_tree->vPrintTree();
    cout << endl;

    CTreeDynamic* c_tree2 = new CTreeDynamic();
    CNodeDynamic* c_root2 = c_tree2->pcGetRoot();
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
    c_tree2->vPrintTree();
    cout << endl;
    c_tree->bMoveSubtree(c_root->pcGetChild(2), c_root2->pcGetChild(0), c_root2);
    cout << "First tree after moving:" << endl;
    c_tree->vPrintTree();
    cout << "\nSecond tree after moving:" << endl;
    c_tree2->vPrintTree();
}

void v_move_subtree_test_static()
{
    cout << "\nStatic move subtree test:" << endl;

    CTreeStatic c_tree;
    CNodeStatic *c_root= c_tree.pcGetRoot();
    c_root->vSetValue(0);
    c_root->vAddNewChild();
    c_root->vAddNewChild();
    c_root->vAddNewChild();
    c_root->pcGetChild(0)->vSetValue(1);
    c_root->pcGetChild(1)->vSetValue(2);
    c_root->pcGetChild(2)->vSetValue(3);
    c_root->pcGetChild(2)->vAddNewChild();
    c_root->pcGetChild(2)->pcGetChild(0)->vSetValue(4);
    cout << "First tree:" << endl;
    c_tree.vPrintTree();
    cout << endl;

    CTreeStatic c_tree2 = CTreeStatic();
    CNodeStatic* c_root2 = c_tree2.pcGetRoot();
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
    c_tree2.vPrintTree();
    cout << endl;
    c_tree.bMoveSubtree(c_root->pcGetChild(2), c_root2->pcGetChild(0), c_root2);
    cout << "First tree after moving:" << endl;
    c_tree.vPrintTree();
    cout << "\nSecond tree after moving:" << endl;
    c_tree2.vPrintTree();
}

int main()
{
    v_static_tree_test();
    //v_dynamic_tree_test();
    //v_move_subtree_test_static();
    //v_move_subtree_test_dynamic();
}

