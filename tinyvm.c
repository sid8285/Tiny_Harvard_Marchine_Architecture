#include <stdio.h>

#define INSTRUCTION_MEMORY_SIZE 128
#define DATA_MEMORY_SIZE 10

// Instruction opcodes
#define LOAD 1
#define ADD 2
#define STORE 3
#define SUB 4
#define IN 5
#define OUT 6
#define HALT 7
#define JMP 8
#define SKIPZ 9
#define SKIPG 10
#define SKIPL 11

// CPU registers
typedef struct {
    int op;
    int addr;
} InstructionRegister;

InstructionRegister IR;

int PC = 0;  // Program Counter
int A = 0;   // Accumulator

int MAR = 0; // Memory Address Register
int MDR = 0; // Memory Data Register

int IM[INSTRUCTION_MEMORY_SIZE] = {0}; // Instruction Memory
int DM[DATA_MEMORY_SIZE] = {0};        // Data Memory

// Function prototypes
void printFinal();
void printState();

int main(int argc, char *argv[]) {

    // creating a variable viewState that will be used to see if the user wants to see the state of the VM when running the program
    int viewState = 0;

    // Check if the input file is provided
    if (argc != 2) {
        printf("Usage: %s input_file\n", argv[0]);
        return 1;
    }

    // Load instructions into the Instruction Memory (IM) from the input file and sending an error if there is a probblem
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error opening input file.\n");
        return 1;
    }

    
    printf("Welcome to the program! If you would like to view the state of the VM, please enter 1. If not, enter 0. \n");
    scanf("%d", &viewState);

    // asking for the user to input 1, so the subtraction sequence in the multiplication loop works properly
    printf("*** Also, please enter '1' as the first digit, and then the two digits you want to multiply so the machine can perform the function. *** \n");

    int instruction, addr;
    int im_counter = 0;
    while (fscanf(fp, "%d %d", &instruction, &addr) == 2) {
        IM[im_counter++] = instruction;
        IM[im_counter++] = addr;
    }
    fclose(fp);

    if(viewState == 1){
            // Fetch and execute cycle
        while (IM[PC] != HALT) {

            printState();

            // Fetch the instruction from the current PC and load it into the Instruction Register (IR)
            IR.op = IM[PC];
            IR.addr = IM[PC + 1];

            // Increment the Program Counter (PC) by 2 to point to the next instruction
            PC += 2;
            
            
            switch (IR.op) {
            case LOAD:
                // LOAD <x> A <- DM[x]
                MAR = IR.addr;
                MDR = DM[MAR];
                A = MDR;
                break;

            case ADD:
                // ADD <x> A <- A + DM[x]
                MAR = IR.addr;
                MDR = DM[MAR];
                A += MDR;
                break;

            case STORE:
                // STORE <x> DM[x] <- A
                MAR = IR.addr;
                MDR = A;
                DM[MAR] = MDR;
                break;

            case SUB:
                // SUB <x> A <- A - DM[x]
                MAR = IR.addr;
                MDR = DM[MAR];
                A -= MDR;
                break;

            case IN:
                // IN <5> A <- Read from Device (5 represents keyboard)
                printf("Input a value: ");
                scanf("%d", &MDR);
                A = MDR;
                break;

            case OUT:
                // OUT <7> A -> Write to device (7 represents Screen)
                printf("Result is: %d\n", A);
                break;

            case JMP:
                // JMP <x> PC <- x
                PC = IR.addr;
                break;

            case SKIPZ:
                // SKIPZ If A is equal zero, PC = PC + 2
                if (A == 0) {
                    PC += 2;
                }
                break;

            case SKIPG:
                // SKIPG If A > zero, PC = PC + 2
                if (A > 0) {
                    PC += 2;
                }
                break;

            case SKIPL:
                // SKIPL If A < zero, PC = PC + 2
                if (A < 0) {
                    PC += 2;
                }
                break;

            default:
                printf("Invalid opcode encountered: %d\n", IR.op);
                break;
        }
            
        }

        // Print final status
        printFinal();
        return 0;
    }

    if(viewState == 0){
           // Fetch and execute cycle
        while (IM[PC] != HALT) {
            // Fetch the instruction from the current PC and load it into the Instruction Register (IR)
            IR.op = IM[PC];
            IR.addr = IM[PC + 1];

            // Increment the Program Counter (PC) by 2 to point to the next instruction
            PC += 2;
            
            
            switch (IR.op) {
            case LOAD:
                // LOAD <x> A <- DM[x]
                MAR = IR.addr;
                MDR = DM[MAR];
                A = MDR;
                break;

            case ADD:
                // ADD <x> A <- A + DM[x]
                MAR = IR.addr;
                MDR = DM[MAR];
                A += MDR;
                break;

            case STORE:
                // STORE <x> DM[x] <- A
                MAR = IR.addr;
                MDR = A;
                DM[MAR] = MDR;
                break;

            case SUB:
                // SUB <x> A <- A - DM[x]
                MAR = IR.addr;
                MDR = DM[MAR];
                A -= MDR;
                break;

            case IN:
                // IN <5> A <- Read from Device (5 represents keyboard)
                printf("Input a value: ");
                scanf("%d", &MDR);
                A = MDR;
                break;

            case OUT:
                // OUT <7> A -> Write to device (7 represents Screen)
                printf("Result is: %d\n", A);
                break;

            case JMP:
                // JMP <x> PC <- x
                PC = IR.addr;
                break;

            case SKIPZ:
                // SKIPZ If A is equal zero, PC = PC + 2
                if (A == 0) {
                    PC += 2;
                }
                break;

            case SKIPG:
                // SKIPG If A > zero, PC = PC + 2
                if (A > 0) {
                    PC += 2;
                }
                break;

            case SKIPL:
                // SKIPL If A < zero, PC = PC + 2
                if (A < 0) {
                    PC += 2;
                }
                break;

            default:
                printf("Invalid opcode encountered: %d\n", IR.op);
                break;
        }
            
        }

        // Print final status
        printFinal();
        return 0;
    }
}


    

void printFinal() {
    printf("End of Program.\n");
    printf("Final state:\n");
    printf("PC = %d | A = %d | DM = [", PC, A);

    for (int i = 0; i < DATA_MEMORY_SIZE; i++) {
        printf("%d", DM[i]);
        if (i < DATA_MEMORY_SIZE - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void printState() {
    // Function to print the state of the machine after each instruction is read.
    printf("PC = %d | A = %d | DM = [", PC, A);
    for (int i = 0; i < DATA_MEMORY_SIZE; i++) {
        printf("%d", DM[i]);
        if (i < DATA_MEMORY_SIZE - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}