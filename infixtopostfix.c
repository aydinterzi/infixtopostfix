#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
    char data;
    struct Node *next;
} node;
int j=0;
char postfix[20];
node *root=NULL;
node *temp=NULL;
int valueofsymbol(char a)
{
    switch(a)
    {
    case '^':
        return 4;
    case '*':
    case '/':
        return 3;
    case '+':
    case '-':
        return 2;
    default:
        return 0;
    }
}
char pop()
{

    node *iter=root;
    if(iter->next==NULL)
    {
        char rvalue=temp->data;
        free(temp);
        root=NULL;
        return rvalue;

    }
    while(iter->next->next!=NULL)
        iter=iter->next;
    temp=iter->next;
    char rvalue = temp->data;
    free(temp);
    temp=iter;
    temp->next=NULL;
    iter=root;
     while(iter->next!=NULL)
    {
        printf("%c",iter->data);
        iter=iter->next;
    }
    printf("%c\t\t",iter->data,postfix);
    printf("%s\n",postfix);
    return rvalue;

}
void push(char symbol)
{
    if(root==NULL)
    {
        root=(node*)malloc(sizeof(node));
        root->data=symbol;
        root->next=NULL;
        temp=root;
    }
    else
    {
        node *iter=root;
        temp=(node*)malloc(sizeof(node));
        while(iter->next!=NULL)
            iter=iter->next;
        temp->data=symbol;
        iter->next=temp;
        temp->next=NULL;

    }
    node *iter=root;
    while(iter->next!=NULL)
    {
        printf("%c",iter->data);
        iter=iter->next;
    }
    printf("%c\t\t%s\n",iter->data,postfix);
}
void infixtopostfix(char infix[],int length)
{
	int i;
    for(i=0; i<length; i++)
    {
        if(infix[i]=='*' || infix[i]=='/' || infix[i]=='+' || infix[i]=='-' || infix[i]=='^')
        {
            while(root!=NULL)
            {
                if(temp->data=='(')
                    break;

                if(valueofsymbol(temp->data)>=valueofsymbol(infix[i]))
                {
                    postfix[j++]=pop();
                     printf("\t\t%s\n",postfix);
                }
                else
                    break;
            }
            push(infix[i]);
        }
        else if(infix[i]==')')
        {
            while(root!=NULL)
            {
                if(temp->data=='(')
                {
                    pop();
                    break;
                }

                postfix[j++]=pop();

                 printf("\t\t%s\n",postfix);
            }
        }
        else if(infix[i]=='(')
        {
            push(infix[i]);
        }
        else
        {
            postfix[j++]=infix[i];
             printf("\t\t%s\n",postfix);
        }

    }
    while(root!=NULL)
    {
        postfix[j++]=pop();
    }

}
int main()
{
    printf("INFIX\t\tPOSTFIX\n");
    printf("-----\t\t--------\n");
    char infix[30]="a*(b+c)*d";
    int length=strlen(infix);
    infixtopostfix(infix,length);
    printf("\t\t%s",postfix);
}
