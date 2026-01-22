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
Does the initialisation of the various modules: Tokeniser and Compiler.
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