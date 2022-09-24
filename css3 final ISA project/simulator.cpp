// simulator.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

int bin_to_dec(string bin);

int main()
{   
  

    ifstream fin("sum.binary");             // the file with binary code (0s and 1s)

    if(fin.fail())                          // make sure file opened okay
    {
        cout << "File open failed\n";
        exit(0);
    }

    string instruction;                     // hold the entire binary instruction
    string opcode;                          // hold the binary opcode (5 bits)
    
    map<string, int> reg_map;               // a map from strings to ints used for registers
    map<string, vector<int>> ary_map;       // a map from strings to vector<int> used for arrays
    vector<string> memory;                 // load instructions in vector to represent memory
    
    
    //for 16 register we need 4 bits for upcode and for each register 
  
    reg_map["0000"] = 0;                     //r1 register set to zero                
    reg_map["0001"] = 0;                     //r2 register set to zero
    reg_map["0010"] = 0;                     //r3 register set to zero
    reg_map["0011"] = 0;                     //r4 register set to zero
    reg_map["0100"] = 0;                     //r5 register set to zero
    reg_map["0101"] = 0;                     //r6 register set to zero
    reg_map["0110"] = 0;                     //r7 register set to zero
    reg_map["0111"] = 0;                     //r8 register set to zero
    reg_map["1000"] = 0;                     //r9 register set to zero                
    reg_map["1001"] = 0;                     //r10 register set to zero
    reg_map["1010"] = 0;                     //r11 register set to zero
    reg_map["1011"] = 0;                     //r12 register set to zero
    reg_map["1100"] = 0;                     //r13 register set to zero
    reg_map["1101"] = 0;                     //r14 register set to zero
    reg_map["1110"] = 0;                     //r15 register set to zero
    reg_map["1111"] = 0;                     //r16 register set to zero 

    while(fin >> instruction)               // read in the entire line of instruction (13 bits)
    {         
        memory.push_back(instruction);      // place it into our memory vector
    }

    fin.close();                            // program is loaded.

    for(unsigned i = 0; i < memory.size(); i++)     // for loop to iterate through vector of instructions
    {             
        instruction = memory.at(i);                 // retrieve the current instruction
        opcode = instruction.substr(0,5);           // take the first 5 bits of the instruction
        //clear
        if(opcode == "11111") //CLEAR               // if the first 5 bits are opcode for PUT
        {//11111 00000000000000000000000 0000
           
    reg_map["0000"] = 0;                     //r1 register set to zero                
    reg_map["0001"] = 0;                     //r2 register set to zero
    reg_map["0010"] = 0;                     //r3 register set to zero
    reg_map["0011"] = 0;                     //r4 register set to zero
    reg_map["0100"] = 0;                     //r5 register set to zero
    reg_map["0101"] = 0;                     //r6 register set to zero
    reg_map["0110"] = 0;                     //r7 register set to zero
    reg_map["0111"] = 0;                     //r8 register set to zero
    reg_map["1000"] = 0;                     //r9 register set to zero                
    reg_map["1001"] = 0;                     //r10 register set to zero
    reg_map["1010"] = 0;                     //r11 register set to zero
    reg_map["1011"] = 0;                     //r12 register set to zero
    reg_map["1100"] = 0;                     //r13 register set to zero
    reg_map["1101"] = 0;                     //r14 register set to zero
    reg_map["1110"] = 0;                     //r15 register set to zero
    reg_map["1111"] = 0;                     //r16 register set to zero 
       
        }

       else if(opcode == "00001") //STORE                 // if the first 5 bits are opcode for PUT
        {//  00001 0000 0000 0000 00000000001 0011 
            string n = instruction.substr(5,23);     // read the 6 bits related to numerical value
            int val = bin_to_dec(n);                // convert binary to decimal

            string regis = instruction.substr(28,4);    // find the 4 bits related to the register
            reg_map[regis] = val;                       // use those  bits as location to store value
            //cout << "Input a numbers to add:"<< endl;
            //cin >> reg_map[regis];
        }
      
        else if(opcode == "00010") //SUM                 // SUM instruction is followed by three registers
        {   //00010 0010 0011 0011 00000000  
            
            string regisA = instruction.substr(5,4);    // bits 5-6 are the first register
            string regisB = instruction.substr(9,4);    // bits 7-9 are the second register
            string regisC = instruction.substr(13,4);   // bits 10-12 are the last register
            
            int sum_result = reg_map[regisA] + reg_map[regisB]; // add the first two registers
            reg_map[regisC] = sum_result;                       // place the result in the third register

        }
        
        else if(opcode == "00011") //OUTput                 // print to screen
        {// 00011  0011 0000 0000 000000000000000
       
            string regis = instruction.substr(5,4);     // find which register to print
            cout << reg_map[regis] << endl;             // use those 3 bits with map to find value.
        }
        
        //Halt
        else if(opcode == "00000")                       // Stops the program
        {
            cout << "Program has finished running.\n";  
            break;         
        }
        
        
       //loop
       else if(opcode=="01000")
       {
          
         string regisA = instruction.substr(5,4);
         string regisB = instruction.substr(9,4);
         if(reg_map[regisA]>1)
         {
           reg_map[regisA]--;
           i-=reg_map[regisB];

         }
    
       }
       //input
          else if(opcode=="01001"){
            
            string regis = instruction.substr(5,4);
            cout<<"Input Value:"<<endl;     
            cin >> reg_map[regis];
            
          }
        else
        {
            cout << "ERROR. OPCODE NOT FOUND. PROGRAM WILL TERMINATE.\n";
            exit(2);
        }
    }

    return 0;
}

int bin_to_dec(string bin) 
{
    int num = 0;
    for (int i = 0; i < bin.length(); i++) 
        if (bin[i] == '1')
            num += pow(2, bin.length() - 1 - i);
    
    return num;
}

/*

11111 00000000000000000000000 0000
00001 00000000000000000000010 0011 
00001 0000000000000000000101 0000
00001 00000000000000000000010 0001
00010 0010 0011 0011 000000000000000 
01000 00000000000000000000000 0000 0011
00011  0011 00000000000000000000000 
00000 000000000000000000000000000


OUTPUT:
 clang++-7 -pthread -std=c++17 -o main main.cpp
 ./main
7
Program has finished running.
 

11111 00000000000000000000000 0000
00001 00000000000000000000010 0011 
00001 0000000000000000000101 0000
00001 00000000000000000000010 0001
00010 0010 0011 0011 000000000000000 
01000 00000000000000000000000 0000 0011
00011  0011 00000000000000000000000 
00000 000000000000000000000000000

*/

// 11111000000000000000000000000000
// 00001000000000000000000010000001 

// 00001000000000000000000001000010

// 00010000100100011000000000000000
// 00011001100000000000000000000000 
// 00000000000000000000000000000000
