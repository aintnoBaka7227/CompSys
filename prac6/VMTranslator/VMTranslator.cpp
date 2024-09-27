#include <string>

#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

string VMTranslator::format(string segment, int offset) {
    if (segment == "static") {
        return to_string(16 + offset);
    }
    else if (segment == "constant") {
        return to_string(offset);
    }
    else if (segment == "pointer") {
        return "R" + to_string(3+offset);
    }
    else if (segment == "temp") {
        return "R" + to_string(5+offset);
    }
    else if (segment == "argument") {
        return "ARG";
    }
    else if (segment == "local") {
        return "LCL";
    }
    else if (segment == "this") {
        return "THIS";
    }
    else if (segment == "that") {
        return "THAT";
    }
    return segment;
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){
    string push = "@" + format(segment, offset) + "\n";
    // take the value and store in D register
    if (segment == "static" || segment == "constant" || segment == "pointer" || segment == "temp") {
        if (segment == "constant") {
            push += "D=A\n";
        }
        else {
            push += "D=M\n";
        }
    }
    else if (segment == "local" || segment == "argument" || segment == "that" || segment == "this") {
        push += "D=M\n";
        push += "@" + to_string(offset) + "\n";
        push += "A=D+A\n";
        push += "D=M\n"; 
    }

    // handle stack , increase stack pointer by one after push
    push += "@SP\n";
    push += "A=M\n";
    push += "M=D\n";
    push += "@SP\n";
    push += "M=M+1";
    return push;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){ 
    string pop = "@" + format(segment, offset) + "\n";
    // get the address of the selected segment 
    if (segment == "static" || segment == "temp" || segment == "pointer") {
        pop += "D=A\n";
    }  
    else if (segment == "local" || segment == "argument" || segment == "this" || segment == "that") {
        pop += "D=M\n";
        pop += "@" + to_string(offset) + "\n";
        pop += "D=D+A\n";
    }
    // pop it into selected segment, handle stack, decrease stack pointer by one
    // r13,14,15 can be used to store selected address temporarily 
    pop += "@R15\n";
    pop += "M=D\n";
    pop += "@SP\n";
    pop += "AM=M-1\n";
    pop += "D=M\n";
    pop += "@R15\n";
    pop += "A=M\n";
    pop += "M=D";

    return pop;
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    // decrease stack pointer down by 1
    string add = "@SP\n";
    add += "AM=M-1\n";
    // get the second value
    add += "D=M\n";
    // add to the first value
    add += "A=A-1\n";
    add += "M=D+M";
    return add;
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    return "";
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    return "";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    return "";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return "";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return "";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    return "";
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    return "";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    return "";
}