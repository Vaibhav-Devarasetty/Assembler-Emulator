/*
********************************************************************************************
TITLE: emu																																
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
int A = 0, B = 0, PC = 0, SP = 0;

//Change 500000 to desired value if more than 2MB of memory is to be store.
#define MEMORY_CAPACITY 500000
//Change 2000 to desired value if more than 2000 instructions have to be executed.
#define EXECUTION_LIMIT 200000
int memory[MEMORY_CAPACITY] = {0}; //2MB reserved for emulation
typedef long long int ll;
string history_log = "";
string testfile;

void writetoFile()
{
    string logFileName = "";
    for(int i = 0; i < testfile.length(); i++)
    {
        
        if(testfile[i] == '.')
            break;
        else
        
            logFileName += testfile[i];
    }
    logFileName += ".trace";
    ofstream outBin(logFileName);
    outBin<<history_log;
    outBin.close();
    cout<<"4/4 trace FILE GENERATED"<<endl;
    exit(0);
}

int converttoNo(string n)
{
    int MSB = 0;
    int number = -8388608;
    if((n[0] >= '8' && n[0] <= '9') || (n[0] >= 'A' && n[0] <= 'F'))
    {
        MSB = 1;
    }
    int rawNo = (int)strtol(n.c_str(), NULL, 16);
    if(MSB){
        rawNo += number;
    } 
    
    return (number * MSB + rawNo);
}

string tohexa(ll n)
{
    int i = 0;
    string arr = "00000000";
    if(n < 0)
    {
        long long int val;
        val = 4294967296 + n;
        return tohexa(val);
    }
    while(n != 0)
    {
        int t = 0;
        t = n % 16;
        if(t < 10)
        {
            arr[7-i] = t + 48;
            i++;
        }
        else
        {
            arr[7-i] = t + 55;
            i++;
        }
        n = n / 16;
   }
   return arr;
}

vector<string> getWords(string s)
{
    vector<string> tokens;
    s += '\n';
    string token = "";
    for(char x: s)
    {
        if(x == ' '|| x == '\n')
        {
            if(!token.empty()){
                tokens.push_back(token);
            }
            token.clear();
        }

        if(x != ' '){
            token += x;
        }
    }
    return tokens;
}

void execute(pair<string, string> c)
{
    string operand = c.first;
    string opcode = c.second;

    if(opcode == "00") //ldc
    {
        B = A;
        A = converttoNo(operand);
    }
    else if(opcode == "01") //adc
    {
        A = A + converttoNo(operand);
    }
    else if(opcode == "02") //ldl
    {
        B = A;
        int loc = SP + converttoNo(operand);
        if((loc > MEMORY_CAPACITY) || (loc < 0))
        {
            cout<<"ILLEGAL MEMORY ACCESS!"<<endl;
            exit(0);
        }
        A = memory[loc];
    }
    else if(opcode == "03") //stl
    {
        int loc = SP + converttoNo(operand);
        if((loc > MEMORY_CAPACITY) || (loc < 0))
        {
            cout<<"ILLEGAL MEMORY ACCESS!"<<endl;
            exit(0);
        }
        memory[loc] = A;
        A = B;
    }
    else if(opcode == "04") //ldnl
    {
        int loc = A + converttoNo(operand);
        if((loc > MEMORY_CAPACITY) || (loc < 0))
        {
            cout<<"ILLEGAL MEMORY ACCESS!"<<endl;
            exit(0);
        }
        A = memory[loc];
    }
    else if(opcode == "05") //stnl
    {
        int loc = A + converttoNo(operand);
        if((loc > MEMORY_CAPACITY) || (loc < 0))
        {
            cout<<"ILLEGAL MEMORY ACCESS!"<<endl;
            exit(0);
        }
        memory[A] = B;
    }
    else if(opcode == "06") //add
    {
        A = A + B;
    }
    else if(opcode == "07") //sub
    {
        A = B - A;
    }
    else if(opcode == "08") //shl
    {
        A = (B<<A);
    }
    else if(opcode == "09") //shr
    {
        A = (B>>A);
    }
    else if(opcode == "0a") //adj
    {
        SP = SP + converttoNo(operand);
    }
    else if(opcode == "0b") //a2sp
    {
        SP = A;
        A = B;
    }
    else if(opcode == "0c") //sp2a
    {
        B = A;
        A = SP;
    }
    else if(opcode == "0d") //call
    {
        B = A;
        A = PC;
        PC = PC + converttoNo(operand);
    }
    else if(opcode == "0e") //return
    {
        PC = A;
        A = B;
    }
    else if(opcode == "0f") //brz
    {
        if(A == 0)
            PC = PC + converttoNo(operand);
    }
    else if(opcode == "10") //brlz
    {
        if(A < 0)
            PC = PC + converttoNo(operand);
    }
    else if(opcode == "11") //br
    {
        PC = PC + converttoNo(operand);
    }
    else if(opcode == "12") //Halt
    {
        cout<<"HALT ENCOUNTERED: EMULATION STOPPED"<<endl;
        writetoFile();
    }
    else //data
    {
        int loc = SP;
        if((loc > MEMORY_CAPACITY) || (loc < 0))
        {
            cout<<"ILLEGAL MEMORY ACCESS!"<<endl;
            exit(0);
        }
        memory[loc] = converttoNo(operand);
    }
}

int main(int argc, char** argv)
{
    //test();
    bool trace = false;
    if(argc == 2 || argc == 3)
    {
        testfile =  argv[1];
        if(argc == 3)
        {
            string arg = argv[2];
            if(arg == "-trace")
                trace = true;
            else
            {
                cout<<"EMULATION FAILED: Only -trace is valid 2nd argument. \""<<arg <<"\" Passed (check claims.txt / makefile.txt)"<<endl;
                exit(1);
            }
        }
    }
    else
    {
        cout<<"EMULATION FAILED: Invalid number of arguments passed ("<<argc - 1<<") Only the file name is to be entered with or without -trace (check claims.txt)"<<endl;
        exit(1);
    }
    ifstream in(testfile);
    if(!in.is_open())
    {
        cout<<"EMULATOR FAILED: No file named \""<<testfile<<"\" exists."<<endl;
        exit(1);
    }
    cout<<"1/4 FILE OPENED SUCCESSFULLY"<<endl;
    vector<vector <string>> parsedLines;
    while(in.eof() == 0)
    {
        string code, comment;
        getline(in, code);
        vector<string> words = getWords(code);
        if(words.size())
        {
            parsedLines.push_back(words);
        }
    }
    cout<<"2/4 FILE PARSED SUCCESSFULLY"<<endl;

    vector<pair<string, string>> instructions;
    for(auto v: parsedLines)
    {
        if(v.size() > 1)
        {
            string binary = v[1];
            string opcode = binary.substr(6, 2);
            string operand = binary.substr(0, 6);
            pair<string, string> t;
            t.first = operand;
            t.second = opcode;
            instructions.push_back(t);
        }
    }

    cout<<"3/4 OPCODE AND OPERAND SPLITTED"<<endl;
    int pointer = 0;
    

    int limit = EXECUTION_LIMIT;
    int prevPC = -1;
    while(limit--)
    {
        if(PC > instructions.size() - 1)
        {
            cout<<PC<<" "<<instructions.size()-1<<endl;
            cout<<"FLAG: PC exceeds the instruction set. Termination Stopped / Completed"<<endl;
            break;
        }
        if(trace)
        {
            cout<<instructions[PC].first<<instructions[PC].second<<endl<<" ";
        }
        execute(instructions[PC]);
        string temp = "A: " + tohexa(A) + "\t" + "B: " + tohexa(B) + "\t"
                        "PC: " + tohexa(PC) + "\t" + "SP: " + tohexa(SP) + "\n";
        if(trace)
        {
            cout<<temp;
        }
        history_log += temp;
        if(prevPC == PC)
        {
            cout<<"FLAG: INFINITE LOOP DETECTED\n";
            history_log += "INFINITE LOOP DETECTED\n";
            //cout<<prevPC<<" "<<PC;
            break;
        }
        prevPC = PC;
        PC++;
    }
    
    if(limit <= 0)
    {
        cout<<"\nFLAG: EXECUTION LIMIT CROSSED. (>"<<EXECUTION_LIMIT<<" Executions, to execute more instructions, change \"EXECUTION_LIMIT\" in source code)\n";
        history_log += "\nEXECUTION LIMIT CROSSED. (>" +
        to_string(EXECUTION_LIMIT) + " Executions, to execute more instructions, change \"EXECUTION_LIMIT\" in source code)\n";
    }

    string logFileName = "";
    for(int i = 0; i < testfile.length(); i++)
    {
        
        if(testfile[i] == '.'){
            break;
        }
        else{
            logFileName += testfile[i];
        }
    }   
    logFileName += ".trace";
    ofstream outBin(logFileName);
    outBin<<history_log;
    outBin.close();
    cout<<"4/4 test FILE GENERATED"<<endl;
    return 0;
}