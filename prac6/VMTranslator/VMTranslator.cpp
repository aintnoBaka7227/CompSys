#include <string>

#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
    label_index = 0;
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

// this is implemented based on mem layout
string VMTranslator::format(string segment, int offset) {
    // 16 -> 255
    if (segment == "static") {
        return "R" + to_string(16 + offset);
    }
    else if (segment == "constant") {
        return to_string(offset);
    }
    // 3,4
    else if (segment == "pointer") {
        return "R" + to_string(3 + offset);
    }
    // 5->12
    else if (segment == "temp") {
        return "R" + to_string(5 + offset);
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
    string return_push = "@" + format(segment, offset) + "\n";
    // take the value and store in D register
    if (segment == "static" || segment == "constant" || segment == "pointer" || segment == "temp") {
        if (segment == "constant") {
            return_push += "D=A\n";
        }
        else {
            return_push += "D=M\n";
        }
    }
    else if (segment == "local" || segment == "argument" || segment == "that" || segment == "this") {
        return_push += "D=M\n";
        return_push += "@" + to_string(offset) + "\n";
        return_push += "A=D+A\n";
        return_push += "D=M\n"; 
    }

    // handle stack , increase stack pointer by one after push
    return_push += "@SP\n";
    return_push += "AM=M+1\n";
    return_push += "A=A-1\n";
    return_push += "M=D\n";
    return return_push;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){ 
    string return_pop = "@" + format(segment, offset) + "\n";
    // get the address of the selected segment 
    if (segment == "static" || segment == "temp" || segment == "pointer") {
        return_pop += "D=A\n";
    }  
    else if (segment == "local" || segment == "argument" || segment == "this" || segment == "that") {
        return_pop += "D=M\n";
        return_pop += "@" + to_string(offset) + "\n";
        return_pop += "D=D+A\n";
    }
    // pop it into selected segment, handle stack, decrease stack pointer by one
    // r13 can be used to store selected address temporarily 
    return_pop += "@R13\n";
    return_pop += "M=D\n";
    return_pop += "@SP\n";
    return_pop += "AM=M-1\n";
    return_pop += "D=M\n";
    return_pop += "@R13\n";
    return_pop += "A=M\n";
    return_pop += "M=D";

    return return_pop;
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    // decrease stack pointer down by 1
    string return_add = "@SP\n";
    return_add += "AM=M-1\n";
    // get the second value
    return_add += "D=M\n";
    // add to the first value
    return_add += "A=A-1\n";
    return_add += "M=D+M";
    return return_add;
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    // decrease stack pointer down by 1
    string return_sub = "@SP\n";
    return_sub += "AM=M-1\n";
    // get the second value
    return_sub += "D=M\n";
    // sub
    return_sub += "A=A-1\n";
    return_sub += "M=D-M";
    return return_sub;
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    std::string return_neg = "@SP\n";
    return_neg += "A=M-1\n";
    return_neg += "M=!M\n";
    return_neg += "M=M+1";
    return return_neg;
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
    string return_and = "@SP\n";
    return_and += "AM=M-1\n";
    return_and += "D=M\n";
    return_and += "A=A-1\n";
    return_and += "M=M&D";
    return return_and;
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    std::string return_or = "@SP\n";
    return_or += "AM = M-1\n";
    return_or += "D = M\n";
    return_or += "A = A-1\n";
    return_or += "M = M|D";
    return return_or;
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    string return_not = "@SP\n";
    return_not += "A=M-1\n";
    return_not += "M=!M";
    return return_not;
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    string return_label = "(" + label + ")";
    return return_label;
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    string return_goto = "@" + label + "\n";
    return_goto += "0;JMP";
    return return_goto;
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    string return_if = "@SP\n"; 
    return_if += "AM = M-1\n";
    return_if += "D = M\n";
    return_if += "@" + label + "\n";
    return_if += "D;JNE"; 
    return return_if;
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    string return_function = "(FUNCTION.DEF." + function_name + ")\n";
    for (int i = 0; i < n_vars; i++) {
        return_function += "@SP\n";
        return_function += "AM=M+1\n";
        return_function += "A=A-1\n";
        return_function += "M=0\n";
    }
    return return_function;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    // generate a unique label 
    std::string label = std::to_string(label_index);
    label_index++;
    // save the return address
    std::string return_call = "@RETURN." + label +"\n";
    return_call += "D=A\n";
    return_call += "@SP\n";
    return_call += "AM=M+1\n";
    return_call += "A=A-1\n";
    return_call += "M=D\n";

    // save LCL, ARG, THIS, THAT of f
    std::string state[4] = {"LCL", "ARG", "THIS", "THAT"};
    for (int i = 0; i < 4; i++) {
        return_call += "@" + state[i] + "\n";
        return_call += "D=M\n";
        return_call += "@SP\n";
        return_call += "AM=M+1\n";
        return_call += "A=A-1\n";
        return_call += "M=D\n";
    }

    // reposition arg = sp - 5 - n_args
    return_call += "@SP\n";
    return_call += "D=M\n";
    return_call += "@5\n";
    return_call += "D=D-A\n";
    return_call += "@" + std::to_string(n_args) + "\n";
    return_call += "D=D-A\n";
    return_call += "@ARG\n";
    return_call += "M=D\n";

    // reposition lcl
    return_call += "@SP\n";
    return_call += "D=M\n";
    return_call += "@LCL\n";
    return_call += "M=D\n";

    // transfer control to g
    return_call += "@FUNCTION.DEF." + function_name + "\n";
    return_call += "0;JMP\n";
    
    // generated label
    return_call += "(RETURN." + label + ")";

    return return_call;
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    // frame = lcl 
    // retAddr = *(frame-5) 
    // frame, ret Addr are temp vars  
    std::string return_return = "@LCL\n";
    return_return += "D=M\n";
    return_return += "@5\n";
    return_return += "D=D-A\n";
    return_return += "@13\n";
    return_return += "M=D\n";

    // *arg = pop 
    // repositions the return value 
    // for the caller
    return_return += "@SP\n";
    return_return += "AM=M-1\n";
    return_return += "D=M\n";
    return_return += "@ARG\n";
    return_return += "A=M\n";
    return_return += "M=D\n";

    // restore the caller's sp 
    return_return += "D=A+1\n";
    return_return += "@SP\n";
    return_return += "M=D\n";

    // restore the caller's that, this, arg, lcl
    std::string state[4] = {"LCL", "ARG", "THIS", "THAT"};
    for (int i = 3; i >= 0; i--) {
        return_return += "@LCL\n";
        return_return += "AM=M-1\n";
        return_return += "D=M\n";
        return_return += "@" + state[i] + "\n";
        return_return += "M=D\n";
    }

    // go to retAddr
    return_return += "@13\n";
    return_return += "A=M\n";
    return_return += "0;JMP";

    return return_return;
}