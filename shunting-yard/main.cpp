#include <stdio.h>
#include <string>
class Stack
{
    int top = -1;
    char operators[500];

public:
    void push(char in)
    {
        operators[++top] = in;
    }
    char pop()
    {
        if (top < 0)
        {
            return '!';
        }
        return operators[top--];
    }
    bool isEmpty()
    {
        return (top < 0);
    }
    char topItem()
    {
        return operators[top];
    }
    int size(){
        return top+1;
    }
};
int getPrecedence(char);
bool isOperator(char c);
int main()
{
    Stack stack;
    std::string expression = "1+(2*3-1)-2";
    int k = 0;
    while (k < expression.length())
    {
        //printf("%c",expression[k]);
        if (isOperator(expression[k]))
        {
            //Push it into the operator stack
            //Before pushing check whether the first item of the operator stack has an higher precedence than
            //the new operator
            if (stack.isEmpty())
            {
                //if empty push to the stack
                stack.push(expression[k]);
                //printf("Stack size is %d \n",stack.size());

            }
            else
            {
                if (expression[k] == ')')
                {
                    //if the operator was a ')' then pop all the elements till '(' to print. Then pop the '(' but don't print
                    //it to the enque
                    while (!stack.isEmpty())
                    {
                        if (stack.topItem() != '(')
                        {
                            printf("%c", stack.pop());
                        }
                        else
                        {
                            stack.pop();
                            break;
                        }
                    } 
                }
                else
                {
                    //Compare the precedence of the top operator in the stack to that of the incoming operator
                    //if the precedence is higher then pop them until an element with the lower precedence is reached
                    while (!stack.isEmpty())
                    {
                        //printf("top of stack %c \n inc opetator %c \n\n",stack.topItem(),expression[k]);

                        if ((getPrecedence(stack.topItem()) >= getPrecedence(expression[k]))&&(getPrecedence(expression[k])!=0)&&(getPrecedence(stack.topItem())!=0))
                        {
                            printf("%c", stack.pop());
                            //printf("Stack size is %d \n",stack.size());
                        }
                        else
                        {
                            break;
                        }
                    }
                    //Then push it onto the stack
                    //stack.push(expression[k]);
                    ///printf("Stack size is %d \n",stack.size());

                }
            }
        }
        else
        {
            //Print it
            printf("%c", expression[k]);
        }
        k++;
    }
    //After the looping if some operators remains then pop those on to the print
    //if they are not '(' or ')'.
    while (!stack.isEmpty())
    {
        printf("%c", (stack.pop()));
        //printf("Stack size is %d \n",stack.size());
    }
    printf("\n");
}
bool isOperator(char c)
{
    if (c == '+')
    {
        return true;
    }
    if (c == '-')
    {
        return true;
    }
    if (c == '%')
    {
        return true;
    }
    if (c == '*')
    {
        return true;
    }
    if (c == '/')
    {
        return true;
    }
    if (c == '(')
    {
        return true;
    }
    if (c == ')')
    {
        return true;
    }
    return false;
}

int getPrecedence(char op)
{
    int precedence;
    switch (op)
    {
    case '+':
        precedence = 1;
        break;
    case '-':
        precedence = 1;
    case '*':
        precedence = 2;
    case '/':
        precedence = 2;
    default:
        precedence = 0;
        break;
    }
    return precedence;
}