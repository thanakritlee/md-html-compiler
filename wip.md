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
- Compiler
- File reader/writer
- Main program

## Main Program
This is the main C program. It takes the input/output file and call the rest of the components.
Might need to use a shell script test runner on this component.

## File Reader/Writer
Read data from input file and put it into buffer and calculate the size.
Flush output buffer into output file.
Should be able to use the C test runner on this component.

## Tokeniser
Tokenisation on demand. Go through the input file buffer, create and return tokens.
Should be able to use the C test runner on this component.

## Compiler
The main logic. Compose of both the parser and the code generator. Use the tokeniser to get read the tokens and parse the input buffer. While parsing, it generate and write the output HTML code into the output buffer.
Should be able to use the C test runner on this component.

# Syntax Directed Translation

Is this compiler just using a Syntax Directed Translation to generate the HTML code? From what I understand (which I'll required to do more research), SDT is normally use to generate syntax tree. 

But if we think about it, an HTML document is kind of a tree. We can have elements within elements. The main HTML tag has multiple childrens. A paragraph tag could have multiple inline formatted text childrens.

----------------------

This compiler is basically only the front end halve of the compiler. It stops at the Parsing phase, because in that phase we're using Syntax Directed Translation to run procedures which output the HTML tags.

----------------------

Additionally, after doing a quick re-read of the dragon compiler book, it looks like this compiler I'm writing is using a Predictive Parser, which is a specific type of Recursive Descend Parser. It uses lookahead(s) to predict the nonterminal productions to use.

# What kind of grammar is this? Context Free Grammar? Recursive Grammar?
I better re-read the Theory of Computation book or the Dragon Compiler book.