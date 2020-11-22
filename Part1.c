#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 50 //Max Length of Propositional Logic including spaces. For atmost 9 operands.
#define Max_Atoms 9

char evalv(int n,char propLogic[],char values[],int NumOfOperators,int NumOfOperands){
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
    scanf("%s", values);

    
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

    printf("%c", evalv(n,propLogic,values,NumOfOperators,NumOfOperands));

}