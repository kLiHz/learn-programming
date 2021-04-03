#include <boost/program_options.hpp>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

class ProcCPP {
    ifstream inFile;
    ofstream outFile;

    bool rm_definition = true;
    bool rm_comment    = true;
    bool rm_in_bracket = false;  // false

    void process();

   public:
    ProcCPP() = default;
    ProcCPP( bool is_rm_def, bool is_rm_com ) : rm_definition(is_rm_def), rm_comment(is_rm_com) {}
    ~ProcCPP() = default;
    auto operator()( const string& srcName, const string& dstName ) -> bool;
};

void ProcCPP::process() {
    char ch             = 0;
    bool str_mode       = false;
    bool char_mode      = false;
    bool in_function    = false;
    bool comment_mode_1 = false;  // // mode
    bool comment_mode_2 = false;  // /**/ mode

    bool after_right_bracket = false;

    bool after_forward_slash = false;
    bool after_backslash     = false;

    bool in_bracket     = false;
    bool after_asterisk = false;
    // char char_to_put = '\0';
    int brace_num_in_func = 0;
    int bracket_num       = 0;

    bool first_bracket = false;
    bool first_brace   = false;
    while ( inFile.get( ch ) ) {
        if ( str_mode ) {
            if ( after_backslash ) {
                after_backslash = false;
            } else if ( ch == '\\' ) {
                after_backslash = true;
            } else if ( ch == '\"' && !after_backslash ) {
                str_mode = false;
            }
        } else if ( char_mode ) {
            if ( after_backslash ) {
                after_backslash = false;
            } else if ( ch == '\\' ) {
                after_backslash = true;
            } else if ( ch == '\'' && !after_backslash ) {
                char_mode = false;
            }
        } else if ( comment_mode_1 ) {
            if ( ch == '\\' ) {
                after_backslash = true;
            } else if ( ch == '\n' && !after_backslash ) {
                comment_mode_1 = false;
            } else {
                if ( after_backslash ) {
                    after_backslash = false;
                }
            }
        } else if ( comment_mode_2 ) {
            if ( ch == '*' ) {
                after_asterisk = true;
            } else if ( ch == '/' && after_asterisk ) {
                after_asterisk = false;
                comment_mode_2 = false;
                continue;
            } else {
                if ( after_asterisk ) {
                    after_asterisk = false;
                }
            }
        } else {
            if ( ch == '/' ) {
                if ( after_forward_slash ) {
                    comment_mode_1      = true;
                    after_forward_slash = false;
                } else {
                    after_forward_slash = true;
                    continue;
                }
            } else if ( ch == '*' ) {
                if ( after_forward_slash ) {
                    comment_mode_2      = true;
                    after_forward_slash = false;
                }
            } else if ( ch == '(' ) {
                if ( !in_function ) {
                    in_bracket          = true;
                    after_right_bracket = false;
                    bracket_num++;
                    if ( bracket_num == 1 ) {
                        first_bracket = true;
                    }
                }
            } else if ( ch == ')' ) {
                if ( !in_function ) {
                    bracket_num--;
                    if ( bracket_num == 0 ) {
                        in_bracket          = false;
                        after_right_bracket = true;
                    }
                }
            } else if ( ch == '{' ) {
                if ( after_right_bracket ) {
                    in_function = true;
                    first_brace = true;
                    // brace_num_in_func++;
                    after_right_bracket = false;
                }
                if ( in_function ) {
                    brace_num_in_func++;
                }
            } else if ( ch == '}' ) {
                if ( in_function ) {
                    brace_num_in_func--;
                    if ( brace_num_in_func == 0 ) {
                        in_function = false;
                    }
                }
            } else if ( ch == ';' ) {
                after_right_bracket = false;
            } else if ( ch == '\"' ) {
                str_mode = true;
            } else if ( ch == '\'' ) {
                char_mode = true;
            }
        }

        if ( after_forward_slash ) {
            outFile.put( '/' );
            after_forward_slash = false;
        }

        bool if_output = true;
        if ( if_output && rm_comment ) {
            if ( comment_mode_1 || comment_mode_2 ) {
                if_output = false;
            }
        }
        if ( if_output && rm_definition ) {
            if ( first_brace && in_function ) {
                first_brace = false;
            } else if ( in_function ) {
                if_output = false;
            }
        }
        if ( if_output && rm_in_bracket ) {
            if ( first_bracket ) {
                first_bracket = false;
            } else if ( in_bracket ) {
                if_output = false;
            }
        }

        if ( if_output ) {
            outFile.put( ch );
        }
    }
}

auto ProcCPP::operator()( const string& srcName, const string& dstName ) -> bool {
    inFile.open( srcName, ios::in );
    if ( !inFile.is_open() ) {
        cout << "Failed to open file '" << srcName << "'." << endl;
        return false;
    }
    outFile.open( dstName, ios::out );
    if ( !outFile.is_open() ) {
        cout << "Failed to open file '" << dstName << "'." << endl;
        inFile.close();
        return false;
    }
    process();
    inFile.clear();
    inFile.close();
    outFile.clear();
    outFile.close();
    return true;
}

auto main( int argc, char* argv[] ) -> int {
    string                                      srcFilename;
    string                                      outFilename;
    bool                                        rm_def = false;
    bool                                        rm_com = false;
    boost::program_options::options_description desc( "options" );
    desc.add_options()( 
        "help,h", "Display help information" )(
        "version,v", "Display program version" )(
        "srcfile,i",
        boost::program_options::value<string>( &srcFilename )
            ->default_value( "in.cpp" )
            ->value_name( "SRCFILE" ),
        "Specify input file" )(
        "outfile,o",
        boost::program_options::value<string>( &outFilename )
            ->default_value( "out.cpp" )
            ->value_name( "OUTFILE" ),
        "Specify output file" )(
        "rmdef", "Remove Function Definition")(
        "rmcom", "Remove comments"
        );
    boost::program_options::positional_options_description pd;
    pd.add( "srcfile", 0 );
    pd.add( "outfile", 1 );
    boost::program_options::variables_map vm;  // 选项存储器,继承自map容器
    try {
        // 对命令行输入参数进行解析,并存入选项存储器
        boost::program_options::store(
            boost::program_options::command_line_parser( argc, argv )
                .options( desc )
                .positional( pd )
                .run(),
            vm );
    } catch ( ... ) {
        cerr << "Illegal option parameter! " << endl;
        return 1;
    }
    boost::program_options::notify( vm );
    if ( vm.count( "help" ) ) {
        cout << "Usage: " << argv[ 0 ] << " [-h] [[-i] SRCFILE] [[-o] OUTFILE] [--rmdef] [--rmcom]"
             << endl;
        cerr << desc;
        exit( EXIT_SUCCESS );
    }
    if ( vm.count( "version" ) ) {
        cout << "proccpp 1.0\n";
        cout << "A program that helps you to proc your cpp source file." << endl;
        exit( EXIT_SUCCESS );
    }
    if ( !vm.count( "srcfile" ) ) {
        cerr << "No infile was given." << endl;
        exit( EXIT_FAILURE );
    }
    if ( !vm.count( "outfile" ) ) {
        cerr << "No outfile was given." << endl;
        exit( EXIT_FAILURE );
    }
    if ( vm.count( "rmdef" )) { rm_def = true; }
    if ( vm.count( "rmcom" )) { rm_com = true; }
    
    ProcCPP pcpp(rm_def, rm_com);
    pcpp( srcFilename, outFilename );
    return 0;
}
