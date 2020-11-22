#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_LENGTH 50
#define Max_Atoms 9

char evalv(int n, char propLogic[], char values[], int NumOfOperators, int NumOfOperands)
{
    char *operators = (char *)malloc(NumOfOperators * sizeof(char));
    char *operand = (char *)malloc(NumOfOperands * sizeof(char));
    int topOperator = -1;
    int topOperand = -1;
    for (char *i = propLogic; *i != '\0'; i++)
    {

        if (*i == ' ')
            continue;
        if ((int)*i >= 48 && (int)*i <= 57)
        {
            topOperand++;
            operand[topOperand] = values[(int)(*i) - '1'];
        }
        else if (*i == ')')
        {
            while (operators[topOperator] != '(')
            { //PROCESS

                char op1 = operand[topOperand];
                char operator= operators[topOperator];
                if (operator== '~') //Unary Operator
                {
                    if (operand[topOperand] == 'T')
                    {
                        operand[topOperand] = 'F';
                    }
                    else
                    {
                        operand[topOperand] = 'T';
                    }
                }
                else //Binary Operator
                {
                    topOperand--;
                    char op2 = operand[topOperand];

                    switch (operator)
                    {
                    case 'V':
                        if (op1 == 'T' || op2 == 'T')
                            operand[topOperand] = 'T';
                        else
                        {
                            operand[topOperand] = 'F';
                        }

                        break;
                    case '^':
                        if (op1 == 'T' && op2 == 'T')
                            operand[topOperand] = 'T';
                        else
                        {
                            operand[topOperand] = 'F';
                        }

                        break;
                    case '>':
                        if (op1 == 'T' || op2 == 'F')
                            operand[topOperand] = 'T';
                        else
                        {
                            operand[topOperand] = 'F';
                        }

                        break;
                    default:
                        printf("INVALID OPERATOR DETECTED\n");
                        return 'E';
                    }
                }
                topOperator--; //pop
            }
            topOperator--;
        }
        else
        {

            topOperator++;
            operators[topOperator] = *i;
        }
    }
    while (topOperator != -1)
    {
        //Process
        char op1 = operand[topOperand];
        char operator= operators[topOperator];
        if (operator== '~') //Unary Operator
        {
            if (operand[topOperand] == 'T')
            {
                operand[topOperand] = 'F';
            }
            else
            {
                operand[topOperand] = 'T';
            }
        }
        else //Binary Operator
        {
            topOperand--;
            char op2 = operand[topOperand];

            switch (operator)
            {
            case 'V':
                if (op1 == 'T' || op2 == 'T')
                    operand[topOperand] = 'T';
                else
                {
                    operand[topOperand] = 'F';
                }

                break;
            case '^':
                if (op1 == 'T' && op2 == 'T')
                    operand[topOperand] = 'T';
                else
                {
                    operand[topOperand] = 'F';
                }

                break;
            case '>':
                if (op1 == 'F' || op2 == 'T')
                    operand[topOperand] = 'T';
                else
                {
                    operand[topOperand] = 'F';
                }

                break;
            default:
                printf("INVALID OPERATOR DETECTED\n");
                return 'E';
            }
        }
        topOperator--; //pop
    }
    if (topOperand != 0)
        printf("CHECK ERROR! %d", topOperand);
    return operand[topOperand];
}

void main()
{
    unsigned int n;

    char propLogic[MAX_STRING_LENGTH], values[Max_Atoms];
    scanf("%d", &n);
    scanf("\n%[^\n]%c", propLogic);
    unsigned int NumOfOperators = 0, NumOfOperands = 0;
    for (char *i = propLogic; *i != '\0'; i++)
    {
        if (*i == ' ')
            continue;
        if ((int)*i >= 48 && (int)*i <= 57)
        {
            NumOfOperands++;
        }
        else
        {
            NumOfOperators++;
        }
    }

    int noOfValues = (int)1 << n;
    int trueCtr = 0;
    char CNF[MAX_STRING_LENGTH];
    int CNFi = 0;

    for (int i = 0; i < noOfValues; i++)
    { //ith Line in TruthTable
        for (int j = 0; j < n; j++)
        { //VALUE OF Jth atom
            if ((i & (1 << j)) == 0)
            {
                values[j] = 'F';
            }
            else
            {
                values[j] = 'T';
            }
        }
        int ans = evalv(n, propLogic, values, NumOfOperators, NumOfOperands);
        if (ans == 'T')
            trueCtr++;
        else
        {
            printf("hi %d %C%C%C\n", i, values[0], values[1], values[2]);
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
                if (values[j] == 'T')
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