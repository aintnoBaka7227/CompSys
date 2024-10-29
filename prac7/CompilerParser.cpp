#include "CompilerParser.h"
#include <iostream>
using namespace std;

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokens = tokens;
    this->current_itr = this->tokens.begin();
    count = 0;
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

    class_tree->addChild(mustBe("keyword", "class"));

    std::string name = current()->getValue();
    class_tree->addChild(mustBe("identifier", name));

    class_tree->addChild(mustBe("symbol", "{"));

    while (current_itr != tokens.end() && !have("symbol", "}")) {
        if (have("keyword", "function method constructor")){
            class_tree->addChild(compileSubroutine());
        }
        else if (have("keyword", "static field")){
            class_tree->addChild(compileClassVarDec());
        }
    }

    class_tree->addChild(mustBe("symbol", "}"));
    
    return class_tree;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* var_tree = new ParseTree("classVarDec","");
    std::string value = current()->getValue();
    var_tree->addChild(mustBe("keyword", value));

    std::string type = current()->getValue();
    var_tree->addChild(mustBe("keyword", type));

    std::string var_name = current()->getValue();
    var_tree->addChild(mustBe("identifier", var_name));

    while (current_itr != tokens.end() && have("symbol", ",")){
        
        var_tree->addChild(mustBe("symbol", ","));
        
        var_name = current()->getValue();
        var_tree->addChild(mustBe("identifier", var_name));
    }

    
    var_tree->addChild(mustBe("symbol", ";"));

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

    if (!have("keyword", "int char boolean void") && current()->getType() != "identifier") {
        throw ParseException();
    }
    routine_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    std::string sub_name = current()->getValue();
    routine_tree->addChild(mustBe("identifier", sub_name));

    routine_tree->addChild(mustBe("symbol", "("));

    if (!have("symbol", ")")) {
        routine_tree->addChild(compileParameterList());
    }

    routine_tree->addChild(mustBe("symbol", ")"));

    if (!have("symbol", "{")) {
        throw ParseException();
    }

    routine_tree->addChild(compileSubroutineBody());

    return routine_tree;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* para_list_tree = new ParseTree("parameterList", "");

    if (!have("keyword", "int char boolean") && current()->getType() != "identifier") {
        throw ParseException();
    }
    para_list_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
    next();

    std::string var_name = current()->getValue();
    para_list_tree->addChild(mustBe("identifier", var_name));

    while (current_itr != tokens.end() && have("symbol",",")) {
        para_list_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();

        if (!have("keyword", "int char boolean") && current()->getType() != "identifier") {
            throw ParseException();
        }
        para_list_tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        next();

        std::string new_var_name = current()->getValue();
        para_list_tree->addChild(mustBe("identifier", new_var_name));
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

    // while(current_itr != tokens.end() && !have("symbol", "}")) {
    //     if (have("keyword", "var")){
    //         subroutine_body_tree->addChild(compileVarDec());
    //         continue;
    //     }
    //     subroutine_body_tree->addChild(compileStatements());
    // }

    
    while (have("keyword", "var")) {
        subroutine_body_tree->addChild(compileVarDec());
    }

    subroutine_body_tree->addChild(compileStatements());

    subroutine_body_tree->addChild(mustBe("symbol", "}"));

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

    std::string local_var_name = current()->getValue();
    local_var_tree->addChild(mustBe("identifier", local_var_name));

    while (current_itr != tokens.end() && have("symbol", ",")){
        local_var_tree->addChild(mustBe("symbol", ","));

        std::string new_local_var_name = current()->getValue();
        local_var_tree->addChild(mustBe("identifier", new_local_var_name));
    }

    local_var_tree->addChild(mustBe("symbol", ";"));

    return local_var_tree;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* statement_tree = new ParseTree("statements", "");

    // while (current_itr != tokens.end() && !have("symbol", "}") && have("keyword", "let if while do return")) {
    //     if (current()->getValue() == "let"){
    //         statement_tree->addChild(compileLet());
            
    //     }
    //     else if (current()->getValue() == "if"){
    //         statement_tree->addChild(compileIf());
            
    //     }
    //     else if (current()->getValue() == "while"){
    //         statement_tree->addChild(compileWhile());
            
    //     }
    //     else if (current()->getValue() == "do"){
    //         statement_tree->addChild(compileDo());
    //     }
    //     else if (current()->getValue() == "return"){
    //         statement_tree->addChild(compileReturn());
    //     }
    // }

    while(have("keyword", "let")){
        statement_tree->addChild(compileLet());
    }
    while(have("keyword", "if")){
        statement_tree->addChild(compileIf());
    }
    while(have("keyword", "while")){
        statement_tree->addChild(compileWhile());
    }
    while(have("keyword", "do")){
        statement_tree->addChild(compileDo());
    }
    while(have("keyword", "return")){
        statement_tree->addChild(compileReturn());
    }

    return statement_tree;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* let_tree = new ParseTree("letStatement", "");

    
    let_tree->addChild(mustBe("keyword", "let"));

    
    std::string name = current()->getValue();
    let_tree->addChild(mustBe("identifier", name));

    if (have("symbol", "[")) {
        
        let_tree->addChild(mustBe("symbol", "["));

        let_tree->addChild(compileExpression());

        
        let_tree->addChild(mustBe("symbol", "]"));
    }

    
    let_tree->addChild(mustBe("symbol", "="));

    let_tree->addChild(compileExpression());

    
    let_tree->addChild(mustBe("symbol", ";"));

    return let_tree;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    ParseTree* if_tree = new ParseTree("ifStatement","");

    if_tree->addChild(mustBe("keyword", "if"));

    if_tree->addChild(mustBe("symbol", "("));

    if_tree->addChild(compileExpression());

    if_tree->addChild(mustBe("symbol", ")"));

    if_tree->addChild(mustBe("symbol", "{"));

    if_tree->addChild(compileStatements());

    if_tree->addChild(mustBe("symbol", "}"));

    if (have("keyword", "else")){
        
        if_tree->addChild(mustBe("keyword", "else"));

        
        if_tree->addChild(mustBe("symbol", "{"));
        
        if_tree->addChild(compileStatements());

        
        if_tree->addChild(mustBe("symbol", "}"));
    }

    return if_tree;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    ParseTree* while_tree = new ParseTree("whileStatement", "");

    
    while_tree->addChild(mustBe("keyword", "while"));

    
    while_tree->addChild(mustBe("symbol", "("));

    while_tree->addChild(compileExpression());

    
    while_tree->addChild(mustBe("symbol", ")"));

    
    while_tree->addChild(mustBe("symbol", "{"));

    while_tree->addChild(compileStatements());

    
    while_tree->addChild(mustBe("symbol", "}"));

    return while_tree;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    ParseTree* do_tree = new ParseTree("doStatement","");

    
    do_tree->addChild(mustBe("keyword", "do"));

    do_tree->addChild(compileExpression());
    
    
    do_tree->addChild(mustBe("symbol", ";"));

    return do_tree;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* return_tree = new ParseTree("returnStatement","");

    
    return_tree->addChild(mustBe("keyword", "return"));

    if (have("symbol", ";")){
        
        return_tree->addChild(mustBe("symbol", ";"));
        return return_tree;
    }
    else {
        return_tree->addChild(compileExpression());
    
        return_tree->addChild(mustBe("symbol", ";"));
    }   
    return return_tree;
}
// cap 80 points

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    ParseTree* expression_tree = new ParseTree("expression", "");

    if(current()->getValue() == "skip"){
        expression_tree->addChild(mustBe("keyword", "skip"));
        return expression_tree;
    }

    expression_tree->addChild(compileTerm());

    std::string op;
    if(current() != nullptr){
        op = current()->getValue();
    }

    while (have("symbol", "+-*/&|<>=")){
        expression_tree->addChild(mustBe("symbol", op));

        expression_tree->addChild(compileTerm());

        if(current() == nullptr || current()->getValue() == "]" || current()->getValue() == ")"){
            break;
        }
        op = current()->getValue();
    }
    return expression_tree;
}


/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    ParseTree* term_tree = new ParseTree("term", "");

    if(current()->getType() == "integerConstant" || current()->getType() == "stringConstant"){
        std::string value = current()->getValue();
        term_tree->addChild(mustBe("integerConstant", value));
        return term_tree;
    }

    if(current()->getType() == "keyword"){
        std::string value = current()->getValue();
        term_tree->addChild(mustBe("keyword", value));
        return term_tree;
    }

    if(current()->getType() == "identifier"){
        std::string value = current()->getValue();
        term_tree->addChild(mustBe("identifier", value));

        if(have("symbol", "[")){
            term_tree->addChild(mustBe("symbol", "["));

            term_tree->addChild(compileExpression());

            term_tree->addChild(mustBe("symbol", "]"));
        }

        if(have("symbol", "(") || have("symbol", ".")){
            if(have("symbol", "(")){
                term_tree->addChild(mustBe("symbol", "("));

                term_tree->addChild(compileExpressionList());

                term_tree->addChild(mustBe("symbol", ")"));
            }
            else{
                term_tree->addChild(mustBe("symbol", "."));

                std::string subrou = current()->getValue();
                term_tree->addChild(mustBe("identifier", subrou));

                term_tree->addChild(mustBe("symbol", "("));

                term_tree->addChild(compileExpressionList());
                
                term_tree->addChild(mustBe("symbol", ")"));
            }
            return term_tree;
        }

        return term_tree;
    }

    if(have("symbol", "(")){
        term_tree->addChild(mustBe("symbol", "("));

        term_tree->addChild(compileExpression());

        term_tree->addChild(mustBe("symbol", ")"));

        return term_tree;
    }

    if(have("symbol", "-") || have("symbol", "~")){
        std::string unary_op = current()->getValue();
        term_tree->addChild(mustBe("symbol", unary_op));
        term_tree->addChild(compileTerm());
        return term_tree;
    }

    return term_tree;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    ParseTree* expr_list_tree = new ParseTree("expressionList", "");

    if (current_itr != tokens.end() || current()->getValue() != ")") {
        expr_list_tree->addChild(compileExpression());
    } else {
        return expr_list_tree;
    }

    while (current()->getValue() == ",") {
        expr_list_tree->addChild(mustBe("symbol", ","));

        expr_list_tree->addChild(compileExpression());

        if (current_itr == tokens.end()) {
            break;
        }
    }

    return expr_list_tree;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    if (current_itr != tokens.end()) {
        ++current_itr;
        count++;
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

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
