#include <iostream>

/*
-- Tasks to complete --
Lexer Development: Your main task is to develop a lexer that can recognize the MiniJava
language constructs defined in the grammar (Listing 1). You can use the ”getting started” example
as a basis and build upon it to create your lexer.
• Token Generation: For each identified language construct within the MiniJava grammar, generate
appropriate tokens. These tokens will be later used by the parser to understand the structure of
MiniJava programs.
• Testing and Validation: Utilize the provided sets of valid Java classes in the test classes/valid
folder of the ”getting started” example. Additionally, there is a collection of lexically incorrect
classes in the test classes/lexical errors folder. These samples can assist you in testing your lexer’s
ability to identify lexical errors. It is highly recommended to expand these sets by adding additional
examples to ensure that your lexer can recognize all lexically valid Java programs and correctly
report errors for those that are not recognized.


-- Recommended approach --
• Lexer Rules for Language Constructs: Begin by defining lexer rules that can identify all the
language constructs specified in the MiniJava grammar. For each recognized construct, print the
corresponding token name. For instance, when the scanner encounters the keyword ”while,” you
should print the token name WHILE. Similarly, if it encounters a symbol like ”+,” you can print
ADDOP. You can use the defined USE LEX ONLY macro to control the behavior of lex actions.
E.g. "while" if(USE LEX ONLY) {print("WHILE");} else{return YY::PARSER::make WHILE(yytext);}
• Token Generation: After successfully identifying language constructs, proceed to generate actual
tokens that will be used by the parser (as outlined in Section 3). Create tokens for each recognized
construct and assign appropriate token names, such as IDENTIFIER, INTEGER, etc.
• Handling Lexical Errors: Flex will automatically report any unrecognized tokens, which can
help you identify lexical errors. You can utilize the provided methods in the getting started
example to handle these errors effectively.
*/

// External variables
extern int yylex();
extern char *yytext;
extern FILE *yyin;

// Main function
int main(int argc, char **argv)
{
    /*
    The main function does the following:
    1. Reads from file if a file name is passed as an argument. Otherwise, reads from stdin.
    2. Calls the lexical analyzer.
    3. If the USE_LEX_ONLY macro is defined, the lexical analyzer prints the token names. Otherwise, it re
    */
	// Reads from file if a file name is passed as an argument. Otherwise, reads from stdin.
	if (argc > 1)
	{
		if (!(yyin = fopen(argv[1], "r")))
		{
			perror(argv[1]);
			return 1;
		}
	}

    // Tokenize the input
    yylex();

    // Close the file (if opened)
    if (argc > 1)
    {
        fclose(yyin);
    }

    return 0;
}
