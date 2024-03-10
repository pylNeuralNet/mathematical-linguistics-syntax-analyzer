/*
    by pylNeuralNet
    2024
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <memory>
#include <set>
#include <iostream>
#include <chrono>
#include <ctime>

/*
    Top-Down Syntax Analyzer
    algorithm: one symbol look-ahead without backtracking
    grammar:
*/ 

std::string FIRST_W = "0123456789(";
std::string FIRST_C = "0123456789";
std::string FIRST_O = "*:+-^";

bool read_S(std::string &sequence, size_t &i);
bool read_W(std::string &sequence, size_t &i);

bool isElementInFirstSet(const char &sequenceElement, const std::string& FIRST_) {
    return FIRST_.find(sequenceElement) != std::string::npos;
}

bool isSemicolonMissingAtEol(std::string &sequence, size_t &i) {
    if(sequence[i] == '\n' && sequence[i-1] != ';') {
        std::cout << "The sequence did not end with a ';', did you mean to write: '";
        sequence.insert(i, ";");
        std::cout << sequence << "'? (appended the ; at the end)" << std::endl;
        return true;
    }
    return false;
}

int callsCnt = 0;
std::string generateAveryLongString() {
    std::string seq = "((((5.678*3.14159)+1)+2)+3)+111111111111111111111";
    std::string sequence = "";
    for(int i = 0; i < 2000; i++) {
        sequence += seq;
        sequence.append("*");
    }
    sequence += seq;
    sequence += ";\n";
    return sequence;
}

double getTimeDifferenceInMilliseconds(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end) {
    std::chrono::duration<double, std::milli> timeDifference = end - start;
    return timeDifference.count();
}

int main() {
    size_t i = 0;
    std::string sequence = "(1.2*3)+5-(23.4+3)^3;8:3;\n";
    // std::string sequence = "8:3\n"; // missing ;
    // std::string sequence = "(1.2*3;\n"; // missing )
    // std::string sequence = "(1.2*;\n"; // missing ) but also ends with a *
    // std::string sequence = "1.2*;\n"; // ends with a * (incomplete expr)
    // std::string sequence = "not a DFA string\n";
    // std::string sequence = generateAveryLongString();
    // std::cout << sequence << std::endl;
    if (read_S(sequence, i))
        std::cout << "SUMMARY\nThe expression is correct\n";
    else
        std::cout << "SUMMARY\nThe expression is not correct\n";
    std::cout << "Number of calls in this approach: " << callsCnt << std::endl;
    return 0;
}

bool read_S(std::string &sequence, size_t &i) {
    callsCnt++;
    if(sequence[i] == '\n') {
        if(isSemicolonMissingAtEol(sequence, i)) return false;
        return true;
    }
    if(!read_W(sequence, i)) {
        return false;
    }
    if(sequence[i] == '\n') {
        if(isSemicolonMissingAtEol(sequence, i)) return false;
        return true;
    }
    i++;

    return read_S(sequence, i);
}

bool read_W(std::string &sequence, size_t &i) {
    callsCnt++;
    if(sequence[i] == '(') {
        i++;
        if(read_W(sequence, i)) {
            if(sequence[i] == ')') {
                i++;
                if(isElementInFirstSet(sequence[i], FIRST_O)) {
                    i++;
                    return read_W(sequence, i);
                } else {
                    return true;
                }
            } else {
                std::cout << "Expected ')' but read: " << sequence[i] << std::endl;
            }
        } else {
            return false;
        }
    } else if(isElementInFirstSet(sequence[i], FIRST_C)) {
        while(isElementInFirstSet(sequence[i], FIRST_C)) {
            i++;
        }
        if(sequence[i] == '.') {
            i++;
            while(isElementInFirstSet(sequence[i], FIRST_C)) {
                i++;
            }
        }
        if(isElementInFirstSet(sequence[i], FIRST_O)) {
            i++;
            return read_W(sequence, i);
        } else {
            return true;
        }
    } else if(sequence[i] == ';') {
        std::cout << "Prior to ';' there was an operator!" << std::endl;
    }
    return false;
}
