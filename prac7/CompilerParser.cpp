#include "CompilerParser.h"


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokens = tokens;
    this->current_itr = this->tokens.begin();
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    if (tokens.size() == 0) {
        throw ParseException();
    }
    if (have("keyword", "class")) {
            return compileClass();
    }
    else {
            throw ParseException();
    }
    return NULL;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    ParseTree* class_tree = new ParseTree("class", "");

    if (!have("keyword", "class")) {
        throw ParseException();
        return NULL;
    }
    class_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    std::string class_name = current()->getValue();
    if (!have("identifier", class_name)) {
        throw ParseException();
        return NULL;
    }
    class_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (!have("symbol", "{")){
        throw ParseException();
        return NULL;
    }
    class_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    while (current_itr != tokens.end() && !have("symbol", "}")) {
        if (have("keyword", "function") || have("keyword", "method") || have("keyword", "constructor")){
            class_tree->addChild(compileSubroutine());
        }
        else if (have("keyword", "static") || have("keyword", "field")){
            class_tree->addChild(compileClassVarDec());
        }
        else {
            throw ParseException();
        }
        next();
    }

    if (!have("symbol", "}")){
        throw ParseException();
        return NULL;
    }
    class_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    
    return class_tree;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    return NULL;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    return NULL;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    if (current_itr != tokens.end()) {
        ++current_itr;
    }
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    if (current_itr != tokens.end()) {
        return *current_itr;
    }
    else {
        throw ParseException();
    }
    return NULL;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    if(current()->getType() == expectedType && current()->getValue() == expectedValue) {
        return true;
    } else if(current()->getType() == expectedType && expectedValue.find(current()->getValue()) != std::string::npos){
        return true;
    } 
    else {
        throw ParseException();
    }
    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if (!this->have(expectedType,expectedValue)) {
        throw ParseException();
        return NULL;
    }
    Token* current_token = this->current();
    this->next();
    return current_token;
}

void CompilerParser::prev() {
    if (current_itr != tokens.begin()) {
        --current_itr;
    } else {
        throw ParseException();
    }
    return;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
