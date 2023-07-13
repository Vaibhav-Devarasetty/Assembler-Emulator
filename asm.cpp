/*
********************************************************************************************
TITLE: asm																																
AUTHOR: Devarasetty Sri Vaibhav
ROLL NO.: 2101CS24
STUDENT ID: devarasetty_2101cs24@iitp.ac.in

#DECLARATION OF AUTHORSHIP
All contents of this file have been solely written by me for CS210 assignment at the Dept.
of Computer Science and Engineering IIT Patna.

#NOTE:
This file is compatible with g++ (V 11.2.0) compiler, file name has to be passed through
console which will be read using argc and argv.
********************************************************************************************
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<string> errors;
void collectErrors(int c, string l) //Used for collecting all the errors in parsedsentences
{
    /*
        0 - More Than 1 Argument Has Passed
        1 - 1 Argument But Unknown Mnemonic
        2 - 0 Argument But Unknown Mnemonic
        3 - Random Bogus Label 
        4 - Invalid Number
        5 - No Such Label
        6 - Duplicate Label
        7 - Infinite Loop
    */
    string x; //Giving Different Error Statement for Different Errors
    switch (c) {
        case 0:
            x = "ERROR: Unknown mnemonic \"" + l + "\" found with more than one argument\n";
            errors.push_back(x);
            break;
        case 1:
            x = "ERROR: Unknown mnemonic \"" + l + "\" found. With one argument\n";
            errors.push_back(x);
            break;
        case 2:
            x = "ERROR: Unknown mnemonic \"" + l + "\"  found. With no argument\n";
            errors.push_back(x);
            break;
        case 3:
            x = "ERROR: Bogus Label Name \"" + l + "\"\n";
            errors.push_back(x);
            break;
        case 4:
            x = "ERROR: Invalid Number Entered \"" + l + "\"\n";
            errors.push_back(x);
            break;
        case 5:
            x = "ERROR: No such label \"" + l + "\" exists\n";
            errors.push_back(x);
            break;
        case 6:
            x = "ERROR: Duplicate label \"" + l + "\" found\n";
            errors.push_back(x);
            break;
        case 7:
            x = "WARNING: Infinite loop detected\n";
            errors.push_back(x);
            break;
        default:
            break;
    }
}

vector<string> getWords(string s)
{
    //This Function is to readwords in the testasm file
    vector<string> tokens;
    s += '\n';
    string token = "";
    for(char x : s)
    {
        if (x == ';')
        {
            if (!token.empty()) 
            {
                tokens.push_back(token);
            }
            break;
        }

        if (x == '\t' || x == ' ' || x == ':' || x == '\n' || x == ',')
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        if (x != ' ')
        {
            if(x != '\t')
            {
                if(x != ',')
                {
                    token += x;
                }
            }
        }
    }
    return tokens;
}

bool validLabel(string lab) //For Checking Whether the Label is valid or not
{
    if (isalpha(lab[0]))
    {
        for (int i = 1; i < lab.length(); i++)
        {
            if (!iswalnum(lab[i]))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

unordered_map <string, int> labelTable;
unordered_set<string> labelSet;

bool checkValidNumber(string n);

int numericalNumber(string n) //For Changing the string to integer value
{
    int value;
    value = strtol(n.c_str(), NULL, 0);
    return value;
}

vector<string> removeLabels(vector<string> n, int index)
{
    if(n.size() > 1)
    {
        if(n[1] == ":")
        {
            vector<string> ins;
            if(validLabel(n[0]))
            {
                if(labelTable.find(n[0]) == labelTable.end())
                {
                    if(n.size() > 2)
                    {
                        if(n[2] == "SET")
                        {
                            labelTable[n[0]] = numericalNumber(n[3]);
                        }
                        else
                        {
                            labelTable[n[0]] = index;
                        }
                    }
                    else
                    { 
                        labelTable[n[0]] = index;
                    }
                    labelSet.insert(n[0]);
                }
                else
                    collectErrors(6, n[0]);
            }
            else
            {
                collectErrors(3, n[0]);
            }
            for(int i = 2; i < n.size(); i++)
            {
                ins.push_back(n[i]);
            }
            return ins;
        }
        else
        {
            return n;
        }
    }
    return n;
}

string tohexa(int number) //For Converting the number to hexadecimal
{
    int i = 0;
    string arr = "000000";
    while(number != 0)
    {
        int temp = 0;
        temp = number % 16;
        if(temp < 10)
        {
            arr[5-i] = temp + 48;
        }
        else
        {
            arr[5-i] = temp + 55;
        }
        i++;
        number = number/16;
   }
   return arr;
}

bool checkValidNo(string number) //For checking whether the number is valid or not
{
    transform(number.begin(), number.end(), number.begin(), ::tolower);
    int leng = number.length();
    if(leng == 0)
    {
        return false;
    }
    if(number[0] == '+' || number[0] == '-')
    {
        if(leng < 2)
        {
            return false;
        }
        number = number.substr(1, leng - 1);
    }

    if(number[0] == '0')
    {
        if(number[1] == 'x')
        {   
            for(int i = 2; i < number.length(); i++)
            {
                if(!((number[i] >= '0' && number[i] <= '9') || (number[i] >= 'a' && number[i] <= 'f')))
                {
                    collectErrors(4, number);
                    return false;
                }
            }
            return true;
        }
        else
        {
            for(int i = 0; i < number.length(); i++)
            {
                if(!(number[i] >= '0' && number[i] <= '7'))
                {
                    collectErrors(4, number);
                    return false;
                }
            }
            return true;
        }
    }
    for(int i = 0; i < number.length(); i++)
    {
        if(!(number[i] >= '0' && number[i] <= '9'))
        {
            return false;
        }
    }
    return true;
}

string getNumbers(string number) //for evaulating the number from the string
{
    ll val;
    val = strtol(number.c_str(), NULL, 0);
    if(val >= 0)
    {
        return tohexa(val);
    }
    else
    {
        val = 16777216 + val;
        return tohexa(val);
    }
    return "000000";
}

string getNumberorLabel(string val, int pc)
{
    if(checkValidNo(val))
    {
        return getNumbers(val);
    }
    else
    {
        if(labelTable.find(val) != labelTable.end())
        {
            return getNumbers(to_string(labelTable[val] - pc - 1));
        }
        else
        {
            if(validLabel(val)) collectErrors(5, val);
        }
    }
    
    return "000000";
}

string getLabels(string val, int pc)
{
    if(checkValidNo(val))
    {
        return getNumbers(val);
    }   
    else
    {
        if(labelTable.find(val) != labelTable.end())
        {
            return getNumbers(to_string(labelTable[val]));
        }
        else
        {
            if(validLabel(val))
            {
                collectErrors(5, val);
            }
        }
    }
    return "000000";
}

string getInstruction(vector<string> line, int pc)
{
    if(line.size() == 2)
    {
        string mnemonic, val, operand, opcode;
        mnemonic = line[0];
        val = line[1];
        
        if(mnemonic == "ldc")
        {
            opcode = "00";
            operand = getLabels(val, pc);
            return operand + opcode;
        }
        else if (mnemonic == "adc")
        {
            opcode = "01";
            operand = getNumberorLabel(val, pc);
            return operand + opcode;
        }

        else if(mnemonic == "ldl")
        {
            opcode = "02";
            operand = getNumberorLabel(val, pc);
            return operand + opcode;
        }

        else if(mnemonic == "stl")
        {
            opcode = "03";
            operand = getNumberorLabel(val, pc);
            return operand + opcode;
        }

        else if(mnemonic == "ldnl")
        {
            opcode = "04";
            operand = getNumberorLabel(val, pc);
            return operand + opcode;
        }

        else if(mnemonic == "stnl")
        {
            opcode = "05";
            operand = getNumberorLabel(val, pc);
            return operand + opcode;
        }

        else if(mnemonic == "adj")
        {
            opcode = "0A";
            operand = getNumberorLabel(val, pc);
            return operand + opcode;
        }

        else if(mnemonic == "call")
        {
            opcode = "0D";
            operand = getNumberorLabel(val, pc);
            return operand + opcode;
        }

        else if(mnemonic == "brz")
        {
            opcode = "0F";
            operand = getNumberorLabel(val, pc);
            return operand + opcode;
        }

        else if(mnemonic == "brlz")
        {
            opcode = "10";
            operand = getNumberorLabel(val, pc);
            return operand + opcode;
        }

        else if(mnemonic == "br")
        {
            opcode = "11";
            operand = getNumberorLabel(val, pc);
            if(operand == "000000") collectErrors(7, val);
            return operand + opcode;
        }
        
        else if(mnemonic == "data")
        {
            opcode = "13";
            operand = getNumberorLabel(val, pc);
            return operand + opcode;
        }
        else if(mnemonic == "SET")
        {
            opcode = "00";
            operand = "000000";
            return "";
        }
        else collectErrors(1, mnemonic);
    }

    else if (line.size() == 1)
    {
        string mnemonic, value, opcode, operand = "000000";
        mnemonic = line[0];

        if(mnemonic == "add")
        {
            opcode = "06";
            return operand + opcode;
        }
        
        else if (mnemonic == "sub")
        {
            opcode = "07";
            return operand + opcode;
        }
        
        else if (mnemonic == "shl")
        {
            opcode = "08";
            return operand + opcode;
        }

        else if (mnemonic == "shr")
        {
            opcode = "09";
            return operand + opcode;
        }

        else if (mnemonic == "a2sp")
        {
            opcode = "0B";
            return operand + opcode;
        }

        else if (mnemonic == "sp2a")
        {
            opcode = "0C";
            return operand + opcode;
        }

        else if (mnemonic == "return")
        {
            opcode = "0E";
            return operand + opcode;
        }

        else if(mnemonic == "HALT")
        {
            opcode = "12";
            return operand + opcode;
        }
        else{
            collectErrors(2, mnemonic);
        }
    }
    
    else if(line.size()){
        collectErrors(0, *line.begin());
    }
    return "";
}

int main(int argc, char** argv)
{
    //Main Pipeline for the assembler
    string testfile;
    if(argc == 2)
    {
        testfile = argv[1];
    }
    else
    {
        cout<<"ASSEMBLY FAILED: Invalid number of arguments passed ("<<argc - 1<<") Only the file name is to be entered."<<endl;
        exit(1);
    }
    ifstream in(testfile);
    if(!in.is_open())
    {
        cout<<"ASSEMBLY FAILED: No file named \""<<testfile<<"\" exists."<<endl;
        exit(1);
    }
    cout<<"FILE OPENED SUCCESSFULLY"<<endl;
    vector<vector <string>> parsedLines;
    while(in.eof() == 0)
    {
        string code, comment;
        getline(in, code);
        vector<string> words = getWords(code);
        if(words.size()){
            parsedLines.push_back(words);
        }
    }
    cout<<"1/6 FILE PARSED SUCCESSFULLY"<<endl;
    in.close();

    vector<vector<string>> inst;
    int index = 0;
    for(auto line: parsedLines)
    {
        vector<string> labelled = removeLabels(line, index);
        inst.push_back(labelled);
        if(labelled.size())
        {
            index++;
        }
    }
    cout<<"2/6 LABELS EXAMINED SUCCESSFULLY"<<endl;

    int pc = 0;
    int i = 0;
    string binaryCode = "";
    string outputCode = "";
    for(auto v: inst)
    {
        string num = getNumbers(to_string(pc));
        string temp = getInstruction(v, pc);
        binaryCode += "00" + num + " " + temp;
        outputCode += "00" + num + " ";
        outputCode += temp + " ";
        for(auto s: parsedLines[i])
        {
            outputCode += s + " ";
        }
        binaryCode += "\n";
        outputCode += "\n";
        if(v.size())
        {
            pc++;
        }
        i++;
    }
    cout<<"3/6 OUTPUT LOG SUCCESSFULLY GENERATED"<<endl;

    string errorString = "; NO ERROR FOUND\n";
    if(errors.size() != 0)
    {
        errorString = "";
        for(auto s: errors){
            errorString += s;
        }
    }
    cout<<"4/6 ERROR CODE GENERATED"<<endl;

    string ofn = "", efn, bfn;
    for(int i = 0; i < testfile.length(); i++)
    {
        
        if(testfile[i] == '.')
            break;
        else
        
            ofn += testfile[i];
    }
    
    efn = ofn + ".log";
    bfn = ofn + ".o";
    ofn += ".lst";
    cout<<"5/6 FILE NAMES GENERATED"<<endl;
    
    ofstream out(ofn);
    out<<outputCode;
    out.close();

    ofstream outError(efn);
    outError<<errorString;
    outError.close();

    ofstream outBin(bfn);
    outBin<<binaryCode;
    outBin.close();

    cout<<"6/6 ALL OUTPUT FILES GENERATED"<<endl;

    return 0;
}
