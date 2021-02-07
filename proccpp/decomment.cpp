#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout<<"Too few arguments!\n";
        cout<<"Try '" << argv[0] << " [src filename] [dst filename]'"<<endl;
        return 0;
    }
    else if (argc > 3){
        cout<<"Too many arguments!\n";
        cout<<"Try '" << argv[0] << " [src filename] [dst filename]'"<<endl;
        return 0;
    }
    ifstream inFile;
    inFile.open(argv[1],ios::in);
    if(!inFile)
    {
        cout<<"Failed to open source file '"<<argv[0]<<"'."<<endl;
        return 0;
    }
    ofstream outFile;
    outFile.open(argv[2],ios::out);
    if (!outFile)
    {
        cout<<"Failed to open destination file '"<<argv[1]<<"'."<<endl;
        inFile.close();
        return 0;
    }
    char ch,chch;
    bool str_mode = false;
    bool char_mode = false;
    bool comment_mode_1 = false; // //
    bool comment_mode_2 = false; // /*
    while (inFile.get(ch))
    {
        if (str_mode) 
        {
            outFile.put(ch);
            if(ch=='\\') {
                inFile.get(ch);
                outFile.put(ch);
            }
            else if(ch=='\"') str_mode = false;
            continue;
        }
        if (char_mode) 
        {
            outFile.put(ch);
            if(ch=='\\') {
                inFile.get(ch);
                outFile.put(ch);
            }
            else if (ch == '\'') char_mode = false;
            continue;
        }
        else if (comment_mode_1)
        {
            if(ch == '\n') {
                //outFile.put(ch);
                outFile<<'\n';
                comment_mode_1 = false;
            }
            continue;
        }
        else if(comment_mode_2)
        {
            if(ch=='*') 
            {
                inFile.get(chch);
                if(chch == '/') comment_mode_2 = false;
            }
            continue;
        }
        else
        {
            if(ch == '\"') 
            {
                outFile.put(ch);
                str_mode = true;
            }
            else if(ch == '\'') 
            {
                outFile.put(ch);
                char_mode = true;
            }
            else if (ch == '/') 
            {
                inFile.get(chch);
                if(chch == '/'){
                    comment_mode_1 = true;
                }
                else if(chch == '*'){
                    comment_mode_2 = true;
                }
                else {
                    outFile.put(ch);
                    outFile.put(chch);
                }
            }
            else outFile.put(ch);
            cout.put(ch);
        }
    }
    
    inFile.close();
    outFile.close();
    return 0;
}
