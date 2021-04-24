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
class Queue
{
    int end = -1;
    char operators[500];
    public:
    bool isEmpty(){
        return (end<0);
    }
    void push(char c){
        operators[++end]=c;
    }
    int size(){
        return end;
    }
    char getIndexOf(int index)
    {
        return operators[index];
    }
    void print(){
        int index = 0;
        while(index<=end)
        {
            printf("%c",operators[index++]);
        }
    }};
int getPrecedence(char);
bool isOperator(char);
void Execute(Queue);
int main()
{
    Queue q;
    Stack stack;
    std::string expression = "(4/2)";
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
                            //printf("%c", stack.pop());
                            q.push(stack.pop());
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
                        //printf("\n%c will be compared with %c\n",stack.topItem(),expression[k]);
                        //printf("\nPrecedence of incoming operators %d\n",getPrecedence(expression[k]));
                        //printf("\nPrecedence of stack top operator %d\n",getPrecedence(stack.topItem()));

                        if ((getPrecedence(stack.topItem()) >= getPrecedence(expression[k]))&&(getPrecedence(expression[k])!=0)&&(getPrecedence(stack.topItem())!=0))
                        {
                            //printf("%c", stack.pop());
                            q.push(stack.pop());
                            //printf("Stack size is %d \n",stack.size());
                        }
                        else
                        {
                            break;
                        }
                    }
                    //Then push it onto the stack
                    stack.push(expression[k]);
                    //printf("\n%c size : %d\n",stack.topItem(),stack.size());
                    ///printf("Stack size is %d \n",stack.size());

                }
            }
        }
        else
        {
            //Print it
            //printf("%c", expression[k]);
            q.push(expression[k]);
        }
        k++;
    }
    //After the looping if some operators remains then pop those on to the print
    //if they are not '(' or ')'.
    while (!stack.isEmpty())
    {
        //printf("%c", (stack.pop()));
        q.push(stack.pop());
        //printf("Stack size is %d \n",stack.size());
    }
    q.print();
    Execute(q);
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
        break;
    case '*':
        precedence = 2;
        break;
    case '/':
        precedence = 2;
        break;
    default:
        precedence = 0;
        break;
    }
    return precedence;
}





void Execute(Queue temp){
Stack operands;
int index = 0;
//temp.print();
while(index<=temp.size())
{
    char token = temp.getIndexOf(index);
    //printf("%c",token);
    if(!isOperator(token))
    {
    //printf(" \n Pushed to %c",temp.getIndexOf(index));
    operands.push(token);
    }
    else
    {
           int op1;
           int op2;
           char op01 = operands.pop();
           char op02 = operands.pop();
           op1 = op01 - '0';
           op2 = op02 - '0';
        if(token=='+')
        {
            char result = '0'+(op1+op2);
            operands.push(result);
        }
        if(token=='-')
        {
            char result = '0'+(op1-op2);
            operands.push(result);
        }
        if(token=='*')
        {
            char result = '0'+(op1*op2);
            operands.push(result);
        }
        if(token=='/')
        {
            char result = '0'+(op1/op2);
            operands.push(result);
        }
    }
    index++;
}
printf("%c",operands.pop());
}
