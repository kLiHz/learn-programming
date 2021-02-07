#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

class ProcCPP
{
    ifstream* inFile;
    ofstream* outFile;
    //const char* srcName;\
    const char* dstName;
    void process();
public:
    ProcCPP();
    ~ProcCPP();
    bool proc(const char* srcName, const char * dstName);
    void release();
};
ProcCPP::ProcCPP()
{
    inFile = new ifstream();
    outFile = new ofstream();
}
ProcCPP::~ProcCPP()
{
    delete inFile;
    delete outFile;
}
void ProcCPP::process()
{
    bool rm_definition = true;
    bool rm_comment = true; 
    bool rm_in_bracket = false;

    char ch = 0;
    bool str_mode = false;
    bool char_mode = false;
    bool in_function = false;
    bool comment_mode_1 = false; // // mode
    bool comment_mode_2 = false; // /**/ mode

    bool after_right_bracket = false;

    bool after_forward_slash = false;
    bool after_backslash = false;

    bool in_bracket = false;
    bool after_asterisk = false;
    //char char_to_put = '\0';
    int brace_num_in_func = 0;
    int bracket_num = 0;

    bool first_bracket = false;
    bool first_brace = false;
    while(inFile->get(ch))
    {
        if (str_mode)
        {
            if(after_backslash){
                after_backslash = false;
            }
            else if(ch == '\\') after_backslash = true;
            else if (ch == '\"' && !after_backslash) str_mode = false;
        }
        else if (char_mode)
        {
            if(after_backslash){
                after_backslash = false;
            }
            else if(ch == '\\') after_backslash = true;
            else if (ch == '\'' && !after_backslash) char_mode = false;
        }
        else if (comment_mode_1)
        {
            if(ch == '\\') after_backslash = true;
            else if (ch == '\n' && !after_backslash) comment_mode_1 = false;
            else {
                if (after_backslash) after_backslash = false;
            }
        }
        else if (comment_mode_2)
        {
            if (ch == '*') after_asterisk = true;
            else if (ch == '/' && after_asterisk)
            {
                after_asterisk = false;
                comment_mode_2 = false;
                continue;
            }
            else {
                if (after_asterisk) after_asterisk = false;
            }
        }
        else 
        {
            if (ch == '/') 
            {
                if(after_forward_slash) {
                    comment_mode_1 = true;
                    after_forward_slash = false;
                }
                else {
                    after_forward_slash = true;
                    continue;
                }
            }
            else if(ch == '*')
            {
                if(after_forward_slash) {
                    comment_mode_2 = true;
                    after_forward_slash = false;
                }
            }
            else if (ch == '('){
                if(!in_function){
                    in_bracket = true;
                    after_right_bracket = false;
                    bracket_num++;
                    if (bracket_num == 1) first_bracket = true;
                }
            }
            else if (ch == ')')
            {
                if(!in_function){
                    bracket_num--;
                    if (bracket_num == 0) {
                        in_bracket = false;
                        after_right_bracket = true;
                    }
                }
            }
            else if (ch == '{'){
                if (after_right_bracket) {
                    in_function = true;
                    first_brace = true;
                    //brace_num_in_func++;
                    after_right_bracket = false;
                }
                if (in_function){
                    brace_num_in_func++;
                }
            }
            else if(ch=='}')
            {
                if (in_function) {
                    brace_num_in_func--;
                    if (brace_num_in_func == 0) in_function = false;
                }
            }
            else if(ch == ';')
            {
                after_right_bracket = false;
            }
            else if (ch == '\"'){
                str_mode = true;
            }
            else if (ch == '\''){
                char_mode = true;
            }
        }

        if (after_forward_slash){
            outFile->put('/');
            after_forward_slash = false;
        }

        bool if_output = true;
        if(if_output && rm_comment)
        {
            if(comment_mode_1 || comment_mode_2) if_output = false && if_output;
        }
        if (if_output && rm_definition)
        {
            if(first_brace && in_function){
                if_output = true && if_output;
                first_brace = false;
            }
            else if(in_function) {
                if_output = false && if_output;
            }
        }
        if (if_output && rm_in_bracket)
        {
            if (first_bracket)
            {
                if_output = true && if_output;
                first_bracket = false;
            }
            else if (in_bracket)
            {
                if_output = false && if_output;
            }
        }
        
        if(if_output) outFile->put(ch);
    }
}
bool ProcCPP::proc(const char* srcName, const char * dstName)
{
    inFile->open(srcName,ios::in);
    if(!*inFile)
    {
        cout<<"Failed to open file '"<<srcName<<"'."<<endl;
        return false;
    }
    outFile->open(dstName,ios::out);
    if (!*outFile)
    {
        cout<<"Failed to open file '"<<dstName<<"'."<<endl;
        inFile->close();
        return false;
    }
    process();
    inFile->clear();
    inFile->close();
    outFile->clear();
    outFile->close();
    return true;
}

char *srcFilename = nullptr;
char *outFilename = nullptr;

void processConsoleOptions(int argc, char *argv[])
{
    const char * option_help    = "--help";
    const char * option_version = "--version";

    const char * rm_definition  = "-nodef";
    const char * rm_comment     = "-nocom";
    const char * rm_in_bracket  = "-nobrkt";

    int i = 1;
    while (i < argc && argv[i][0] == '-')
    {
        if (strcmp(option_help, argv[i]) == 0) //show 'help'
        {
            cout << "Usage: " << argv[0] << " [options] srcfile dstfile" << endl;
            cout << "Options:" << left << endl;
            cout << "  " << setw(12) << option_help << "Display help information" << endl;
            cout << "  " << setw(12) << option_version << "Display program version" << endl;
            throw 1;
        }
        else if (strcmp(option_version, argv[i]) == 0)
        {
            cout << "proccpp 2.0\n";
            cout << "a program that helps you to proc your source cpp file" << endl;
            throw 1;
        }
        else {
            cout << "Illegal option parameter! Try '" << argv[0] << " --help'." << endl;
            throw 0;
        }
        i++;
    }

    if (argc - i > 2)
    {
        cout << "Too many arguments! Try '" << argv[0] << " --help'." << endl;
        throw 0;
    }
    else if (argc - i < 2)
    {
        cout << "Too few arguments! Try '" << argv[0] << " --help'." << endl;
        throw 0;
    }
    srcFilename = argv[argc-2];
    outFilename = argv[argc-1];
}

int main(int argc, char *argv[])
{
    try {
        processConsoleOptions(argc,argv);
    } catch (int n) {
        if (n == 0 || n == 1) 
        {
            return 0;
        }
    }
    
    ProcCPP* instance;
    instance = new ProcCPP();
    instance->proc(srcFilename,outFilename);
    delete instance;
    return 0;
}
