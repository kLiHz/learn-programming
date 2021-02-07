# proccpp

Process your `.cpp` source file, i.e. remove all the comments or the definitions.

This might be useful when you want to share your code with your friend(s), but not all the functions' definitions or even the comments. ~~To be honest this might probably be just a imaginary scenario...~~

`decomment.cpp` can be used to remove all the comments, while `proccpp.cpp` will remove all the comments **as well as** all function definitions.



**What's new:** Now "remove definitions" and other task options are **almost** optional for `proccpp`, check it out at `procpp_class.cpp`.



- Written in C++. 

- Expected to be used in command line. 

- It's ~~also~~ a piece of **homework**. 



## usage

Use command line to process your file. Let's assume that the bin file is named `proccpp`:

```bash
./proccpp test.cpp test_1.cpp
```

Then the program receives the file named `test.cpp` and would save the processed file to `test_1.cpp`.
