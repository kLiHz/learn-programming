#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

void proc(const char* srcName, const char * dstName) //main process
{
    ifstream inFile;
    inFile.open(srcName,ios::in);
    if(!inFile)
    {
        cout<<"Failed to open file '"<<srcName<<"'."<<endl;
        return ;
    }
    ofstream outFile;
    outFile.open(dstName,ios::out);
    if (!outFile)
    {
        cout<<"Failed to open file '"<<dstName<<"'."<<endl;
        inFile.close();
        return ;
    }
    char ch,chch;
    bool str_mode = false;
    bool char_mode = false;
    bool in_function = false;
    bool comment_mode_1 = false; // // mode
    bool comment_mode_2 = false; // /**/ mode
    bool after_right_bracket = false;
    int brace_num = 0;
    while (inFile.get(ch))
    {
        if (str_mode) 
        {
            if(!in_function) outFile.put(ch);
            if(ch=='\\') {
                inFile.get(ch);
                if(!in_function) outFile.put(ch);
            }
            else if(ch=='\"') str_mode = false;
            continue;
        }
        else if (char_mode) 
        {
            if(!in_function) outFile.put(ch);
            if(ch=='\\') {
                inFile.get(ch);
                if(!in_function) outFile.put(ch);
            }
            else if (ch == '\'') char_mode = false;
            continue;
        }
        else if (comment_mode_1)
        {
            if(ch == '\n') {
                if(!in_function) outFile<<'\n';
                comment_mode_1 = false;
            }
            else continue;
        }
        else if (comment_mode_2)
        {
            if(ch=='*') 
            {
                inFile.get(chch);
                if(chch == '/') comment_mode_2 = false;
            }
            else continue;
        }

        else //default mode
        {
            if(ch == '\"') // " means a string begins
            {
                if(!in_function) outFile.put(ch);
                str_mode = true;
            }
            else if(ch == '\'')  // ' means a char begins
            {
                if(!in_function) outFile.put(ch);
                char_mode = true;
            }
            else if(ch == ')') //means after a bracket
            {
                if(!in_function) outFile.put(ch);
                after_right_bracket = true;
            }
            else if (ch == '/') //means a possible comment
            {
                inFile.get(chch);
                if(chch == '/'){
                    comment_mode_1 = true;
                }
                else if(chch == '*'){
                    comment_mode_2 = true;
                }
                else {
                    if(!in_function) outFile.put(ch);
                    if(!in_function) outFile.put(chch);
                    if(chch == '{') {
                        brace_num++;
                    }
                    else if(chch == '}' )
                    {
                        brace_num--;
                        if(brace_num == 0) {
                            in_function = false;
                            after_right_bracket = false;
                            outFile.put(ch);
                        }
                    }
                }
            }
            else if (in_function)
            {
                if(ch == '{') {
                    brace_num++;
                }
                else if(ch == '}' )
                {
                    brace_num--;
                    if(brace_num == 0) {
                        in_function = false;
                        after_right_bracket = false;
                        outFile.put(ch);
                    }
                }
            }
            else if(after_right_bracket && !in_function && !comment_mode_1 && !comment_mode_2 && !str_mode && !char_mode) 
            {
                outFile.put(ch);
                if (ch == ';') after_right_bracket = false;
                else if (ch == '{') {
                    in_function = true;
                    brace_num++;
                }
                else continue;
            }
            else outFile.put(ch);
        }
    }
    inFile.close();
    outFile.close();
}

int main(int argc, char *argv[])
{
    const char *option_help = "--help";
    const char *option_version = "--version";
    int i = 1;
    while (i < argc && argv[i][0] == '-')
    {
        if (strcmp(option_help, argv[i]) == 0) //show 'help'
        {
            cout << "Usage: " << argv[0] << " [options] srcfilename dstfilename" << endl;
            cout << "Options:" << left << endl;
            cout << "  " << setw(12) << option_help << "Display help information" << endl;
            cout << "  " << setw(12) << option_version << "Display program version" << endl;
            return 0;
        }
        else if (strcmp(option_version, argv[i]) == 0)
        {
            cout<<"proccpp 1.0\n";
            cout<<"a program that helps you to proc your source cpp file"<<endl;
            return 0;
        }
        else {
            cout<<"Illegal option parameter! Try'proccpp --help'."<<endl;
            return 0;
        }
        i++;
    }
    char *srcFilename = NULL;
    char *outFilename = NULL;
    if (argc - i > 2)
    {
        cout << "Too many arguments! Try 'proccpp --help'." << endl;
        return 0;
    }
    else if (argc - i < 2)
    {
        cout << "Too few arguments! Try 'proccpp --help'." << endl;
        return 0;
    }
    srcFilename = argv[argc-2];
    outFilename = argv[argc-1];
    proc(srcFilename,outFilename);
    return 0;
}
