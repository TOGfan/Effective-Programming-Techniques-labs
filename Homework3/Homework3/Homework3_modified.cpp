
#include <iostream>
using namespace std;

class CTable {
public:
    CTable() {
        s_name = "";
        cout << "without:\'" << s_name << "\'"<<endl;
        arr = new int[1];
        length = 1;
    }
    CTable(string sName, int iTableLen) {
        s_name = sName;
        cout << "parameter:\'" << s_name << "\'"<<endl;
        arr = new int[iTableLen];
        length = iTableLen;
    }
    CTable(CTable&pcOther) {
        s_name = pcOther.s_name+"_copy";
        cout << "copy:\'" << s_name << "\'"<<endl;
        arr = pcOther.arr;
        length = pcOther.length;
    }
    bool bSetNewSize(int iTableLen) {
        arr = new int[iTableLen];
        length = iTableLen;
        return iTableLen >= 0;
    }
    void vSetName(string sName) {
        s_name = sName;
    }
    CTable* pcClone() {
        CTable* a = this;
        return new CTable(*a);
    }
    void display() {
        cout << s_name << " " << length<< endl;
    }
    ~CTable() {
        cout << "remowing: " << s_name<<endl;
    }
private:
    string s_name;
    int* arr;
    int length;
};
void v_mod_tab(CTable* pcTab, int iNewSize) {
    pcTab->bSetNewSize(iNewSize);

}
void v_mod_tab(CTable cTab, int iNewSize) {
    cTab.bSetNewSize(iNewSize);
}
int main()
{
    cout << "Static allocation:" << endl;
    CTable a; //static allocation
    a.display();
    cout << "Dynamic allocation:" << endl;
    CTable* b = new CTable("Dynamic",5); //dynamic allocation
    CTable* c = b->pcClone();   //dynamic allocation by copying
    b->display();
    c->display();
    cout << "Testing v_mod_tab functions:" << endl;
    cout << "Without pointers:" << endl;
    v_mod_tab(b, 3);
    b->display();
    cout << "With pointers:" << endl;
    v_mod_tab(*c, 3);
    c->display();
    cout << "Deleting the objects:"<<endl;
    delete(b);
    delete(c);
    cout << "Creating array of objets:" << endl;
    CTable* arr = new CTable[5];
    for (int i = 0; i < 5; i++) {
        arr[i].display();
    }
    cout << "Deleting array of objects:" << endl;
    delete[]arr;
}

