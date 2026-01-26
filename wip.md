# What does the process of the program looks like?

So, I'm not sure yet if I can do a scan on demand with this the markdown grammar or not. But I'm thinking that the process might look something like this at a high level:

1. Load Markdown from file into buffer.
2. Tokenisation.
3. Run through the string of tokens and generate an HTML document in buffer.
4. Write the buffer out into a new HTML file.

----------------------

I'm re-reading the "Crafting an Interpreter" book as I go on implementing this project. The clox implementation is using the Pratt parser to implement the parser-compiler program. It looks like a recursive descent parser. I'm thinking that I should be able to implement the same thing using the grammar I've defined.

https://en.wikipedia.org/wiki/Operator-precedence_parser

# Output HTML formatting

I was thinking about how to output the HTML file. 

Should the whole HTML document be output on a single line?
This was actually my initial plan, but then how would I format the code snippet in the HTML document?

It turns out that there're HTML Numbers for each of the ASCII code. There's even one for newline and tabs as well. So if I want to have the whole HTML document on one line, I could do it with the help of these HTML Numbers to format the code snippets.
For example, there's this HTML Number `&#09;` which is used for inserting a tab into the document.

Another idea was to put a new line on each of the HTML content and element tags, just new lines, no need for tab formatting on non code snippet content. This turns out to also work too. For the code snippet section, I could add in the required space and tabs as ASCII binary code when writting the buffer into the file.

I think in conclusion I want to go with the second approach because the output HTML file will be at least a bit more readable (without having to do an extra document formatting call) than the one-line HTML document.

# What are the components of this compiler?

- Tokeniser
- Parser
- File reader/writer
- Main program

## Main Program
This is the main C program. It takes the input/output file and call the rest of the components.
Does the initialisation of the various modules: Tokeniser and Compiler.
Might need to use a shell script test runner on this component.

## File Reader/Writer
Read data from input file and put it into buffer and calculate the size.
Flush output buffer into output file.
Should be able to use the C test runner on this component.

## Tokeniser
Tokenisation on demand. Go through the input file buffer, create and return tokens.
Should be able to use the C test runner on this component.

## Parser
The main logic. Compose of both the parser and the code generator. Use the tokeniser to get the tokens and parse the input buffer. While parsing, it generate and write the output HTML code into the output buffer.
Should be able to use the C test runner on this component.

# Syntax Directed Translation

Is this compiler just using a Syntax Directed Translation to generate the HTML code? From what I understand (which I'll required to do more research), SDT is normally use to generate syntax tree. 

But if we think about it, an HTML document is kind of a tree. We can have elements within elements. The main HTML tag has multiple childrens. A paragraph tag could have multiple inline formatted text childrens.

----------------------

This compiler is basically only the front end halve of the compiler. It stops at the Parsing phase, because in that phase we're using Syntax Directed Translation to run procedures which output the HTML tags.

----------------------

Additionally, after doing a quick re-read of the dragon compiler book, it looks like this compiler I'm writing is using a Predictive Parser, which is a specific type of Recursive Descend Parser. It uses lookahead(s) to predict the nonterminal productions to use.

----------------------

"Crafting Interpreters" called this compiler a "Single-Pass Compiler". In a single-pass compiler, SDT is use to generate codes from actions that is associated with each productions in the grammar. This is basically what I'm doing in my compiler. So I guess I can call my compiler a single pass compiler. Single-pass compiler generates the output code directly in the parser phase.

----------------------

In a way, this compiler could even be classified as a transcompiler, because it's compiling one high level language to another high level language. Markdown and HTML aren't programming languages, but they're both markup languages. We're just compiling from one markup language to another.

# What kind of grammar is this? Context Free Grammar? Recursive Grammar?
I better re-read the Theory of Computation book or the Dragon Compiler book.

# EOF
I'll be putting a EOF character at the end of the source file buffer so that the tokeniser can recognise the end of the buffer and stop. In the Dragon compiler book, I think this is called a Sentinel character. Is it only one sentinel for the whole source file, or is it just a sentinel per each buffer, given that older compilers might have limited buffer space.

# Clarifying the grammar
SPACE and TAB. I've add some more grammar productions of space and tab. I want to have them as different tokens because they'll be use for formatting purposes in the HTML code/pre tags. In other tags such as bullet points, number list, and heading, they make no difference and will be removed in the output.

# Practical example of why tests are needed
I have initially implemented the EOF token when I was working on the heading tokenisation. I didn't add a test case for the EOF token then and was just assuming that it was working correctly.

I've only recently added a test case for it and found that it was buggy. I've listed the bugs here:
- I used a double qoute on "\0" instead of '\0'. It should have been single qoute because it's a character comparison.
- I didn't add an asterisk in front of the pointer to get the data at the memory address. Was tokeniser.current instead of *tokeniser.current. Without the asterisk, I was comparing a memory address against a character, which is a C semantic error.

----------------------

Now I've just got a quick fun though about syntax vs semantic error. Using normal spoken language as an analogy:
A syntax error is spelling a word incorrectly.
e.g. "windough"

A semantic error is forming a sentence that doesn't make sense or is meaningless.
e.g. "jump fox the rabbit over the"

Like I said, just a fun thought lmao.

# What is a STRING terminal?
I've been at this all morning since 9. It's 1040 now. I'm trying to define what is considered a STRING terminal in the grammar. It's pretty difficult because I want to be able to use special characters in the string too. Some special characters are more special than others though.

I've listed some special characters that are used in the Markdown grammar to identify which production it is. Both underscore and asterisk are used for emphasis such as bold and italic. The exclamation mark is use for image insert. The left/right parenthesis/bracket are use for image and weblink.
- _     underscore
- *     asterisk
- !     exclamation
- ( )   left paren / right paren
- [ ]   left bracket / right bracket
- .

There's also the angled bracket which need to be tokenised because they are needed to escaped in HTML.
- < >   left angled bracket / right angled bracket (need to be escaped in HTML)

So, I think these can still be considered a part of the string, but they just need to be their own tokens. In the case that they are part of a seperate grammar productions, they can be identified properly and use.

Also, if I encounter anymore "special" special characters in the future, I can just seperate them out into their own tokens. But these are just the ones that I've identified so far.

----------------------

To be honest, this part is pretty challenging for me. I found myself reworking and refining alot of the grammar productions and terminals as I work on the compiler. Little tweak here and there. I guess this shows that I can't really fully define a perfect grammar upfront before starting the work on the compiler.

### References
- https://www.w3schools.com/html/html_entities.asp

# How does a C fprintf function knows when to stop writing out a char* buffer?
So I did a quick spike to understand this, as well as go back and read the C file IO section of the x64 Assembly book. The C stdlib knows where a string ends by using the null terminator `\0`.

This is shown in the Assembly book, where the author put a literal 0 binary value at the end of a base string that goes to the C stdlib fprintf function.

My spike also shows that by putting a null terminator at the end of a string (even though it's not at the end of the allocated char array) will stop the C stdlib from writing out any further bytes after that point.

I guess I can create an interface ontop of the char array to make working with it easier such as write string to buffer, expanding the buffer etc.

# Peeking tokens?
What thinking about how a heading rule can goes 2 ways, it's either a heading or a paragraph. If given that the TOKEN_H? follows by a space or tab, then it's a heading rule, but if it's followed by anything else such as a alphabet, number, or some special character then it's considered a content rule which is part of the paragraph rule.

This whole thing is a bit confusing and made me think of adding a peek function to the tokeniser so that the parser could peek at the next token.

Not sure yet if it's needed or not. I guess we'll see.
I do feel like the codebase is starting to get a bit messy though. I need to do a refactor in my next commit.

----------------------

So I did ended up doing a sort of multiple lookahead algorithm. The parser I'm implemented is a predictive parser after all. Right now it's doing a multiple lookahead to determine whether it's an inline code, link, or just normal content. This is because given the opening token of some sort (square bracket, grave accent), there might not be a closing tag. In the scenario that there's no closing tag, then the opening tag should be treated as a string to be displayed in the content rule.

# Confusiong with char pointer and just char
It seems that I *char and char[] is a different beast. I tried to assign a char[] to *char in the buffer, thinking that it would work, but it didn't. I ended up searching for a method online, and the solution is to use malloc instead of the manual char[] creation. Fair enough.

Now I'll also need to deallocate the memory upone exits as well.

----------------------

Also, saving this code snippet to use later for writing the buffer out to a file. fprintf knows when to stop writing from the buffer by looking at the null terminator.

```
FILE *fptr;
    // Open a file in writing mode
    fptr = fopen("filename.html", "w");

    // Write some text to the file    
    fprintf(fptr, "%s", outputBuffer.mem);

    // Close the file
    fclose(fptr); 
```

Pretty good read:
- https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

# code vs pre tag for displaying code snippet
So it seems that when using the pre tag, it automatically put in a new line before staring the code snippet. I guess this is fine for code section in the document, but it's not what I want for displaying inline code.

With inline code, the code shouldn't be on a new line, it should be inline haha. So using the code tag seems to be best for this.

Also, another interesting thing, when inserting a tab into the code tag it only output 1 space character, while in the pre tag it output 2 space characters. I don't know why that is, but it's just an interesting fact.

# string vs number
Looking back, I think I should have implemented the number token differently. Any string of digits should have been considered a number, no matter if it's concatenated with a string or a special character. In the end, the parser will decide how to interpret the tokens anyway. Perhaps I could fix this after the compiler has been implemented. Could be a good exercise of refactoring the code base and TDD.