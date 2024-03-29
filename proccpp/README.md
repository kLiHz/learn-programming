# proccpp

Process your `.cpp` source file: removing all the comments and/or the definitions. 

- Written in C++. 
- Expected to be used in command line. 

Actually, this is a piece of **homework** of OOP. 

This might be useful when you want to share your code with your friend(s), but not with all the functions' definitions or even the comments. 

`decomment.cpp` can be used to remove all the comments, while `proccpp.cpp` will remove all the comments **as well as** all function definitions.

**What's new:** Now "remove definitions" and other task options are optional for `pcpp` through command line parameters, check it out at `pcpp.cpp`.

**Dependencies**: boost libraries.

## Usage

Use command line to process your file. Assuming that the bin file is named as `pcpp`, then:

```bash
./pcpp -i test.cpp -o test_1.cpp --rmcom
```

Then the program receives the file named `test.cpp` and will save the processed file to `test_1.cpp`. 

`--rmcom` means to remove comments from the source file, while you can also add `--rmdef` to remove definitions.



## Acknowledgement

**`pcpp`**: This source file was improved by one of my friends back in 2020 (to be exactly, about 1 a.m. on July 1, 2020) from my poor original  `proccpp`. However, I was not familiar with either CMake or boost at that time, so reading the code was like reading ancient Greek for me. But now I think I might be able to figure out how this code works. 

(In fact, I was preparing to use CMake for this program. Then I realized that this piece of code is still lying at my 'Download' folder, and I think it's necessary to commemorate this.)



