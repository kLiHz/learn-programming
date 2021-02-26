# proccpp

Process your `.cpp` source file: removing all the comments and/or the definitions. 

- Written in C++. 
- Expected to be used in command line. 

Actually, this is a piece of **homework** of OOP. 

This might be useful when you want to share your code with your friend(s), but not with all the functions' definitions or even the comments. 

`decomment.cpp` can be used to remove all the comments, while `proccpp.cpp` will remove all the comments **as well as** all function definitions.

**What's new:** Now "remove definitions" and other task options are **almost** optional for `proccpp` (which means it's not yet made optional through command line parameters), check it out at `procpp_class.cpp`.

## usage

Use command line to process your file. Assuming that the bin file is named as `proccpp`:

```bash
./proccpp test.cpp test_1.cpp
```

Then the program receives the file named `test.cpp` and would save the processed file to `test_1.cpp`.
