# Assembler-Emulator

## Title: Claims  
### Author: Devarasetty Sri Vaibhav  
#### Roll No.: 2101CS24  
#### Student ID: [devarasetty_2101cs24@iitp.ac.in](mailto:devarasetty_2101cs24@iitp.ac.in)

---

## Declaration of Authorship  
This README file, along with the source files `asm.c`, `emu.c`, and `claims.txt`, is part of the mini-project for CS209/CS210 at the Department of Computer Science and Engineering, IIT Patna.  

---

## Files  
- **Source files**: `asm.c`, `emu.c`, and `claims.txt`.  
- Each file includes the author's name, student ID, and a declaration of authorship.  
- **Evidence files**:
  - For assembler: 
    - `test1` (3 output files)
    - `test2` (3 output files)
    - `test3` (1 output file)
    - `memcpy` (3 output files)
    - `triangle` (3 output files)
  - For emulator:
    - Output files: `memcpy.txt`, `triangle.txt`.  

---

## Compilation Details  
- Programs were compiled without errors or warnings using:
  ```bash
  gcc -std=c89 -pedantic
  gcc -std=c89 -pedantic -W -Wall -Wpointer-arith -Wwrite-strings -Wstrict-prototypes
  ```
- Both programs are compilable using:
  ```bash
  gcc asm.c -o asm
  gcc emu.c -o emu
  ```

---

## Program Features  

### 1. Assembler
- Two data structures to store labels and a mnemonic table with expected operands.  
- Implements a single routine for both passes.  
- Detects label errors.  
- Consistent formatting and sensible structure.  
- Meaningful variable, function, and type names with explanatory comments.  
- Produces an advanced listing file.  
- Assembles test programs.  
- Implements and demonstrates the instruction `SET`.  

### 2. Emulator
- Three data structures for memory, mnemonic table with expected operands, and a linked list structure word.  
- Loads object files.  
- Produces memory dump before or after execution using flags (`-before` / `-after`).  
- Prints execution results with the `-trace` flag.  
- Detects and handles errant programs.  

---

## Testing  

### Assembler  
Tested on five examples:  

#### Test 1
- **Input**: `asm test1.asm`  
- **Output**:  
  - `test1.l`  
  - `test1.log` (No errors)  
  - `test1.o`  

#### Test 2  
- **Input**: `asm test2.asm`  
- **Output**:  
  - `test2.l`  
  - `test2.log` (with errors)  
  - `test2.o`  

Errors:
```
ERROR: A duplicate label was found on line 4
ERROR: There is a non-numerical value on line 6
ERROR: A numerical value was expected on line 7
ERROR: A numerical value was not expected on line 8
ERROR: Only one numerical value was expected on line 9
ERROR: A bogus label name was found on line 10
ERROR: An unknown mnemonic was found on line 11
ERROR: An unknown mnemonic was found on line 12
ERROR: A non-existent label was found on line 5
```

#### Test 3  
- **Input**: `asm test3.asm`  
- **Output**:  
  - `test3.l`  
  - `test3.log` (No errors)  
  - `test3.o`  

#### Test 4  
- **Input**: `asm memcpy.asm`  
- **Output**:  
  - `memcpy.l`  
  - `memcpy.log` (No errors)  
  - `memcpy.o`  

#### Test 5  
- **Input**: `asm triangle.asm`  
- **Output**:  
  - `triangle.l`  
  - `triangle.log` (No errors)  
  - `triangle.o`  

---

### Emulator  
Tested on six examples:  

#### Test 1  
- **Input**: `emu test1.o`  
- **Output**: `test1.trace`  

#### Test 2  
- **Input**: `emu test2.o`  
- **Output**: `test2.trace`  

#### Test 3  
- **Input**: `emu test3.o`  
- **Output**:  
  - `test3.trace`  
  - **Error**:  
    ```
    PC=00000000, SP=08049596, A=008172D0, B=0804958C Fatal error occurred! No instruction can be found!
    ```

#### Test 4  
- **Input**: `emu test4.o`  
- **Output**: `test4.trace`  

#### Test 5  
- **Input**: `emu test5.o`  
- **Output**: `test5.trace`  

#### Test 6  
- **Input**: `emu test7.o`  
- **Output**: `test7.trace`  

---

## Usage Instructions  
- **Assembler**: Run using `./asm <input_file>.asm`.  
- **Emulator**: Run using `./emu <input_file>.o`.  

---

## Notes  
- The programs and test cases function as expected without warnings or errors during compilation and execution.  
- All outputs have been validated against the assignment results.  

