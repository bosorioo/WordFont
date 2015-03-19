# WordFont
A simple console program that prints to the window characters as if they were pixels, building a shape of the letters of
the string the user must give as input.  
This is one of the assignments from a C++ class. The requirements can be seen in the "Homework Requirements.pdf" file.  

An example execution with it's output can be seen in the file "example.txt".  
The only argument the program accepts is "test". When running with this argument, instead of prompting the user for the inputs,
the program will display all letters of the alphabet, normal and bold, with font size 8 until 12.  
When running with "test" argument, make sure to redirect the standard output to a file, because too many prints will cause 
word wrapping and it is not going to be possible to actually see the letters.  

# How to compile
The following command can be used to compile this project:  
*  g++ -o WordFont.exe main.cpp WordFont.cpp  

# How to run the program
If running with the argument "test" given to it, the output will be same as it can be seen in the file "test.txt".  
Otherwise, the program will ask for a few inputs and print the output to the stdout.  
Example execution:

```
Enter a string (max. of 20 letters) using the following characters: [a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z] -> Example  
Enter the pixel character you want to use to draw: @  
Enter the font size (8-12): 9  
Bold? (0 = No, 1 = Yes, 2 = Uppercase characters will be bolded and lowercase won't): 2  

@@@@@@@@   @       @   @@@@@@@   @       @  @@@@@@@@   @          @@@@@@@@ 
@@@@@@@@    @     @   @       @  @@     @@  @       @  @          @        
@@           @   @    @       @  @ @   @ @  @       @  @          @        
@@@@@@@@      @ @     @       @  @  @ @  @  @       @  @          @        
@@@@@@@@       @      @@@@@@@@@  @   @   @  @@@@@@@@   @          @@@@@@@@ 
@@            @ @     @       @  @       @  @          @          @        
@@           @   @    @       @  @       @  @          @          @        
@@@@@@@@@   @     @   @       @  @       @  @          @          @        
@@@@@@@@@  @       @  @       @  @       @  @          @@@@@@@@@  @@@@@@@@@

Press enter to exit...
```
