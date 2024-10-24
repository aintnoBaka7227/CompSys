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

    class_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (!(current()->getType() == "identifier")){
        throw ParseException();
    }
    class_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (!have("symbol", "{")){
        throw ParseException();
    }
    class_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    while (current_itr != tokens.end() && !have("symbol", "}")) {
        if (have("keyword", "function method constructor") /*|| have("keyword", "method") || have("keyword", "constructor")*/){
            class_tree->addChild(compileSubroutine());
        }
        else if (have("keyword", "static field") /*|| have("keyword", "field")*/){
            class_tree->addChild(compileClassVarDec());
        }
        else {
            throw ParseException();
        }
        next();
    }

    if (!have("symbol", "}")){
        throw ParseException();
    }
    class_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    
    return class_tree;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* var_tree = new ParseTree("classVarDec","");
    var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (!have("keyword", "int char boolean") /*&& current()->getType() != "identifier" && !have("keyword", "char") && !have("keyword", "boolean")*/){
        throw ParseException();
    }
    var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (!(current()->getType() == "identifier")){
        throw ParseException();
    }
    var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    while (current_itr != tokens.end() && have("symbol", ",")){
        var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();
        if (!(current()->getType() == "identifier")){
            throw ParseException();
        }
        var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();
    }

    if (!have("symbol", ";")){
        throw ParseException();
    }
    var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));

    return var_tree;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* routine_tree = new ParseTree("subroutine", "");
    routine_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (!have("keyword", "int char boolean void") /*&& current()->getType() != "identifier"*/) {
        throw ParseException();
    }
    routine_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (current()->getType() != "identifier") {
        throw ParseException();
    }
    routine_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    // routine_tree->addChild(new ParseTree(mustBe("symbol", "(")->getType(), mustBe("symbol", "(")->getValue()));
    if (!have("symbol", "(")) {
        throw ParseException();
    }
    routine_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (!have("symbol", ")")) {
        routine_tree->addChild(compileParameterList());
    }

    // routine_tree->addChild(new ParseTree(mustBe("symbol", ")")->getType(), mustBe("symbol", ")")->getValue()));
    if (!have("symbol", ")")) {
        throw ParseException();
    }
    routine_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    // routine_tree->addChild(new ParseTree(mustBe("symbol", "{")->getType(), mustBe("symbol", "{")->getValue()));
    if (!have("symbol", "{")) {
        throw ParseException();
    }
    routine_tree->addChild(compileSubroutineBody());

    // routine_tree->addChild(new ParseTree(mustBe("symbol", "}")->getType(), mustBe("symbol", "}")->getValue()));
    // back();
    // if (!have("symbol", "}")) {
    //     throw ParseException();
    // }
    // routine_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));

    return routine_tree;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* para_list_tree = new ParseTree("parameterList", "");

    if (!have("keyword", "int char boolean") /*&& current()->getType() != "identifier"*/) {
        throw ParseException();
    }
    para_list_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (current()->getType() != "identifier") {
        throw ParseException();
    }
    para_list_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (!have("symbol", ",")) {
        return para_list_tree;
    }
    para_list_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();
    
    while (current_itr != tokens.end() && !have("symbol",")")) {
        if (!have("keyword", "int char boolean") /*&& current()->getType() != "identifier"*/) {
            throw ParseException();
        }
        para_list_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();

        if (current()->getType() != "identifier") {
            throw ParseException();
        }
        para_list_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();

        if (have("symbol", ",")) {
            para_list_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
            next();
            if (have("symbol", ")")) {
                throw ParseException();
            }
        }
    }
    return para_list_tree;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* subroutine_body_tree = new ParseTree("subroutineBody", "");

    subroutine_body_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    while(current_itr != tokens.end() && !have("symbol", "}")) {
        if (have("keyword", "var")){
            subroutine_body_tree->addChild(compileVarDec());
            next();
            continue;
        }
        subroutine_body_tree->addChild(compileStatements());
    }

    if (!have("symbol", "}")) {
        throw ParseException();
    }
    subroutine_body_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));

    return subroutine_body_tree;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* local_var_tree = new ParseTree("varDec", "");
    local_var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (!have("keyword", "int char boolean") && current()->getType() != "identifier"){
        throw ParseException();
    }
    local_var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (!(current()->getType() == "identifier")){
        throw ParseException();
    }
    local_var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    while (current_itr != tokens.end() && have("symbol", ",")){
        local_var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();

        if (!(current()->getType() == "identifier")){
            throw ParseException();
        }
        local_var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();
    }

    if (!have("symbol", ";")){
        throw ParseException();
    }
    local_var_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));

    return local_var_tree;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* statement_tree = new ParseTree("statements", "");

    while(have("keyword", "let if while do return")) {
        //if (current()->getType() == "keyword") {
            if (current()->getValue() == "let"){
                statement_tree->addChild(compileLet());
            } else if (current()->getValue() == "if"){
                statement_tree->addChild(compileIf());
            } else if (current()->getValue() == "while"){
                statement_tree->addChild(compileWhile());
            } else if (current()->getValue() == "do"){
                statement_tree->addChild(compileDo());
            } else if (current()->getValue() == "return"){
                statement_tree->addChild(compileReturn());
            } else{
                throw ParseException();
            }
        //}
        next();
    }

    return statement_tree;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* let_tree = new ParseTree("let", "");
    let_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    if (current()->getType() != "identifier"){
        throw ParseException();
    }
    let_tree->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    if (have("symbol", "[")) {
        let_tree->addChild(compileExpression());
        let_tree->addChild(new ParseTree(current()->getType(), current()->getValue() ));
        next();
    }

    if (!have("symbol", "=")){
        throw ParseException();
    }
    let_tree->addChild(new ParseTree(current()->getType(), current()->getValue() ));
    next();

    let_tree->addChild(compileExpression());
    if (!have("symbol", ";")){
        throw ParseException();
    }
    let_tree->addChild(new ParseTree(current()->getType(), current()->getValue() ));

    return let_tree;
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
// cap 80 points

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
    else {
        throw ParseException();
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
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    if(current()->getType() == expectedType && current()->getValue() == expectedValue) {
        return true;
    } 
    else if (current()->getType() == expectedType && expectedValue.find(current()->getValue()) != std::string::npos) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if (!have(expectedType,expectedValue)) {
        throw ParseException();
    }
    Token* current_token = current();
    next();
    return current_token;
}

// void CompilerParser::back() {
//     if (current_itr != tokens.begin()) {
//         --current_itr;
//     } else {
//         throw ParseException();
//     }
//     return;
// }

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
