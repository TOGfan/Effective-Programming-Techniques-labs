#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class CFileLastError {
public:
    CFileLastError() {
        pf_file = NULL;
        b_last_error = false;
    };
    CFileLastError(string sFileName) {
        pf_file = NULL;
        vOpenFile(sFileName);
    };
    ~CFileLastError(){
        if (pf_file != NULL) {
            fclose(pf_file);
        }
    };
    void vOpenFile(string sFileName) {
        if (pf_file != NULL) {
            fclose(pf_file);
        }
        b_last_error = false;
        pf_file = fopen(sFileName.c_str(), "w+");
        if (pf_file == NULL) {
            b_last_error = true; 
        }
    };
    void vPrintLine(string sText) {
        b_last_error = false;
        if (pf_file == NULL) {
            b_last_error = true;
            return;
        }
        fprintf(pf_file, sText.c_str());
    };
    void vPrintManyLines(vector<string> sText) {
        for (int i = 0; i < sText.size(); i++) {
            vPrintLine(sText[i]);
        }
    };
    bool bGetLastError() { return(b_last_error); }
private:
    FILE* pf_file;
    bool b_last_error;
};

class CFileThrowEx
{
public:
    CFileThrowEx() {
        pf_file = NULL;
    };
    CFileThrowEx(string sFileName) {
        vOpenFile(sFileName);
    };
    ~CFileThrowEx() {
        if (pf_file != NULL) {
            fclose(pf_file);
        }
    };
    void vOpenFile(string sFileName) {
        if (pf_file != NULL) {
            fclose(pf_file);
        }
        pf_file = fopen(sFileName.c_str(), "w+");
        if (pf_file == NULL) {
            throw 1;
            return;
        }
    };
    void vPrintLine(string sText) {
        if (pf_file == NULL) {
           throw 1;
            return;
        }
        fprintf(pf_file, sText.c_str());
    };
    void vPrintManyLines(vector<string> sText){
        for (int i = 0; i < sText.size(); i++) {
            vPrintLine(sText[i]);
        }
    }
private:
    FILE* pf_file;
};//class CFileThrowEx

class CFileErrCode
{
public:
    CFileErrCode() {
    };
    CFileErrCode(string sFileName) {
        bOpenFile(sFileName);
    };
    ~CFileErrCode() {
        if (pf_file != NULL) {
            fclose(pf_file);
        }
    };
    bool bOpenFile(string sFileName) {
        if (pf_file != NULL) {
            fclose(pf_file);
        }
        pf_file = fopen(sFileName.c_str(), "w+");
        if (pf_file == NULL) {
            return false;
        }
        return true;
    };
    bool bPrintLine(string sText) {
        if (pf_file == NULL) {
            return false;
        }
        fprintf(pf_file, sText.c_str());
        return true;
    };
    bool bPrintManyLines(vector<string> sText) {
        for (int i = 0; i < sText.size(); i++) {
            if (!bPrintLine(sText[i]))
                return false;
        }
    };
private:
    FILE* pf_file;
};//class CFileErrCode
int main()
{
    CFileLastError* a=new CFileLastError();
    CFileThrowEx* b = new CFileThrowEx();
    CFileErrCode * c = new CFileErrCode();
    string s = "File.txt";
    
    
    a->vPrintLine(s);
    if (a->bGetLastError() == true)
        cout << "Successfully reported error in LastError" << endl;
   
    
    try {
        b->vPrintLine(s);
    }
    catch (int e) {
        cout << "Successfully reported error in ThrowEx" << endl;
    }
   
    
    if (!c->bPrintLine(s))
        cout << "Successfully reported error in ErrCode" << endl;


    for (int i = 0; i < 10; i++) {
        a->vOpenFile(s);
        if (a->bGetLastError() == true)
            cout << "Failed to open " << s<<endl;
        try {
            b->vOpenFile(s);
        }
        catch (int e) {
            cout << "Failed to open " << s<<endl;
        }
        if (!c->bOpenFile(s)) 
            cout << "Failed to open " << s<<endl;
    }
    delete(a, b, c);


    return 0;
}
//answer to the question:
