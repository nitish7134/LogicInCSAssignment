/* Logic Homework 3, Part 2 */
/* Team Number: 58 */
/* Team Members:
1. Nitish Mittal 2018A3PS1076H <ID #>
2. Ayush Deep 2018A3PS0516H
3. Shardul Khadye 2018A8PS0945H
4. Prabhav Sharma 2018A3PS0337H
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 2048 // macro indicating the maximum size of stack As we have maximum of 9 atoms. this we can have 2^9 lines and including symbols and spaces aprox 2^11

/***************************************************************/
/********************stack operations***************************/

// Inserting data onto top of stack. Takes as arguments the data to be pushed, the array used for implementing the stack and an integer pointer referencing the index of the top of that stack.

void push(char data, char stack[], int *top)
{
    if (*top != MAX - 1) // if stack is not full
    {
        *top = *top + 1;
        stack[*top] = data;
    }
    else
    {
        printf("Could not insert data, Stack is full.\n");
    }
}

// Removing element from top of stack. Takes as arguments the array used for implementing the stack and an integer pointer referencing the index of the top of that stack. Returns the popped character.

char pop(char stack[], int *top)
{
    char data;

    if (*top != -1) //checking whether stack contains some elements
    {
        data = stack[*top];
        *top = *top - 1;
        return data;
    }

    else
    {
        printf("Could not retrieve data, Stack is empty.\n");
    }
}

// NOTE:
// A pointer to the variable top is passed instead of passing the top variable itself. This is done to ensure top is passed as reference and any modifications to the top variable
// would be reflected in the calling function

/***************************************************************/
/********************* implementation **************************/


//Process As described in the Problem Document
//Takes in operand stack and operator to process  as parameters and returns nothing
void process(char operand_stack[], int *operand_top, char operator)
{
    char op1 = pop(operand_stack, operand_top);
    if (operator== '~') //Unary Operator
    {
        if (op1 == 'T')
        {
            push('F', operand_stack, operand_top);
        }
        else
        {
            push('T', operand_stack, operand_top);
        }
    }
    else //Binary Operator
    {
        char op2 = pop(operand_stack, operand_top);
        switch (operator)
        {
        case 'V':
            if (op1 == 'T' || op2 == 'T')
                push('T', operand_stack, operand_top);
            else
            {
                push('F', operand_stack, operand_top);
            }

            break;
        case '^':
            if (op1 == 'T' && op2 == 'T')
                push('T', operand_stack, operand_top);
            else
            {
                push('F', operand_stack, operand_top);
            }

            break;
        case '>':
            if (op1 == 'T' || op2 == 'F')
                push('T', operand_stack, operand_top);
            else
            {
                push('F', operand_stack, operand_top);
            }

            break;
        default:
            printf("INVALID OPERATOR DETECTED: %c .\n", operator);
        }
    }
}

// function to implement the solution for Part 1. Takes as arguments the number of atoms, the character array to store the completely parenthesized input formula and the array to store the valuation of the atoms
// returns the final result of evaluating the formula (either T or F)

char eval_formula(int n, char formula[], char operand_stack_val[])
{
    unsigned int NumOfoperator_stack = 0, NumOfoperand_stacks = 0;
    for (char *i = formula; *i != '\0'; i++)
    {
        if (*i == ' ')
            continue;
        if ((int)*i >= 48 && (int)*i <= 57)
        {
            NumOfoperand_stacks++;
        }
        else
        {
            NumOfoperator_stack++;
        }
    }

    char *operator_stack = (char *)malloc(NumOfoperator_stack * sizeof(char)); // character array to implement operand stack
    char *operand_stack = (char *)malloc(NumOfoperand_stacks * sizeof(char));  // character array to implement operator stack
    int operand_top = -1;                                                      // integer pointing to the top of the operand stack
    int operator_top = -1;                                                     // integer pointing to the top of the operand stack

    for (char *i = formula; *i != '\0'; i++)
    {
        if (*i == ' ') //Ignore if blank space added as input
            continue;
        if ((int)*i >= 48 && (int)*i <= 57)     //48 and 57 are ASCII values of 1 and 9 respectively
        {
            push(operand_stack_val[(int)(*i) - '1'], operand_stack, &operand_top);  //Push if an operand in operand stack
        }
        else if (*i == ')') //Process till current blacket closed
        {
            char operator= pop(operator_stack, &operator_top);
            while (operator!= '(')
            { //PROCESS
                process(operand_stack, &operand_top, operator);
                operator= pop(operator_stack, &operator_top);
            }
        }
        else
        {
            push(*i, operator_stack, &operator_top); //If nothing then it is a operator thus push in operator stack
        }
    }
    while (operator_top != -1) //Process the remaining
    {
        //Process
        char operator= pop(operator_stack, &operator_top);
        process(operand_stack, &operand_top, operator);
    }
    if (operand_top != 0)
        printf("CHECK ERROR! %d", operand_top);
    return pop(operand_stack, &operand_top);
}

void main()
{

    int n;                      // number of operand_stacks
    char formula[MAX];          // character array to store the input formula
    char operand_stack_val[10]; // array to store the valuation of operand_stacks (either T or F)

    scanf("%d", &n);
    scanf("\n%[^\n]%c", formula);

    int noOfValues = (int)1 << n;
    int trueCtr = 0;
    char CNF[MAX];
    int CNFi = 0;

    for (int i = 0; i < noOfValues; i++)
    { //ith Line in TruthTable
        for (int j = 0; j < n; j++)
        { //VALUE OF Jth atom
            if ((i & (1 << j)) == 0)
            {
                operand_stack_val[j] = 'F';
            }
            else
            {
                operand_stack_val[j] = 'T';
            }
        }
        int ans = eval_formula(n, formula, operand_stack_val);
        if (ans == 'T')
            trueCtr++;
        else
        {
            if (CNFi != 0)
            {
                CNF[CNFi++] = ' ';
                CNF[CNFi++] = ')';
                CNF[CNFi++] = ' ';
                CNF[CNFi++] = '^';
                CNF[CNFi++] = ' ';
            }
            CNF[CNFi++] = '(';
            CNF[CNFi++] = ' ';
            for (int j = 0; j < n; j++)
            {
                if (operand_stack_val[j] == 'T')
                {
                    CNF[CNFi++] = '(';

                    CNF[CNFi++] = '~';
                    CNF[CNFi++] = j + '1';
                    CNF[CNFi++] = ')';
                }
                else
                    CNF[CNFi++] = j + '1';
                if (j + 1 != n)
                {
                    CNF[CNFi++] = ' ';
                    CNF[CNFi++] = 'V';
                    CNF[CNFi++] = ' ';
                }
            }
        }
    }
    CNF[CNFi++] = ' ';
    CNF[CNFi++] = ')';
    CNF[CNFi++] = ' ';
    if (trueCtr != 0)
    {
        printf("Formula is satisfiable\n");
    }
    else
    {
        printf("Formula is satisfiable\n");
    }
    if (trueCtr == noOfValues)
        printf("Formula is valid\n");
    else
        printf("Formula is not valid\n");
    for (int i = 0; i < CNFi; i++)
    {
        printf("%c", CNF[i]);
    }
}