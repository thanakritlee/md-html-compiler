# A Markdown* to HTML Compiler

Markdown with an asterisk because this compiler doesn't currently implement all Markdown grammar rules.

This compiler translate Markdown into HTML.

## Testing

Run the following command in the terminal to create a the project test runner executable:
```
make testrunner
```

Run the following command to execute the test runner:
```
./testrunner
```

For easier view of the test result, you can redirect the STDOUT to an output file:
```
./testrunner > test-output.txt
```

## Running

To run the compiler, first compile it to an executable with the following terminal command:
```
make compiler
```

To compile a Markdown file to a HTML file, run the following command:
```
./compiler {file-name}.md {file-name}.html
```

`{file-name}` is the name of the input/output file. The output file doens't have to be the same as the input file.