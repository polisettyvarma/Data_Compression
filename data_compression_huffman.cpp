#include <iostream>
#include <cstring>
#include <cstdlib>
#include "data_compression_huffman.hpp"

using namespace std;

//  HEAD points to root of the tree

//Function to take input of string
void huffman :: input()
{
    cout<<"Enter the string:";
    cin.getline(str,99);
}

//Fucntion to give output if input is processed or not
void huffman :: output()
{
    cout<<str<<"  len= "<<strlen(str)<<endl;
    cout<<out<<"  len= "<<strlen(out)<<endl;
}

//Function to count frequency and store the characters
void huffman :: make_data()
{
    int len=strlen(str);
    count=0;
    for(int i=0;i<MAX;i++)
    {
        d[i]=(data*)malloc(sizeof(data));
        d[i]->freq=0;
        d[i]->ch[0]='\0';
        d[i]->left=NULL;
        d[i]->right=NULL;
        d[i]->next=NULL;
    }
    //  use ASCII values as index
    for(int i=0;i<len;i++)
    {
        d[int(str[i])]->freq++;
        d[int(str[i])]->ch[0]=str[i];
        d[int(str[i])]->ch[1]='\0';
        if(d[int(str[i])]->freq==1)
            count++;
    }
    /*for(int i=0;i<MAX;i++)
        cout<<d[i].freq<<" ";
    cout<<endl;
    for(int i=0;i<MAX;i++)
        if(d[i].freq)
            cout<<d[i].ch<<" ";*/
}

void huffman::Sort()
{
    for(int i=0;help_array[i][0]!=0;i++)
    {
        for(int j=i+1;help_array[j][0]!=0;j++)
        {
            if(help_array[i][0]>help_array[j][0])
            {
                int temp=help_array[i][0];
                help_array[i][0]=help_array[j][0];
                help_array[j][0]=temp;
                temp=help_array[i][1];
                help_array[i][1]=help_array[j][1];
                help_array[j][1]=temp;
            }
        }
    }
}

//Function to create linked list of nodes
void huffman :: construct_list()
{
    int j=0;
    //  array help_array is used to sort
    for(int i=0; i<MAX; i++)
    {
        if(d[i]->freq)
        {
            help_array[j][0]=d[i]->freq;
            help_array[j][1]=i;
            j++;
        }
    }
    for( ; j<MAX; j++)
    {
        help_array[j][0]=0;
        help_array[j][1]=-1;
    }
    Sort();
    j=0;cout<<endl;
    HEAD=d[help_array[0][1]];
    while(help_array[j+1][0])
    {
        d[help_array[j][1]]->next=d[help_array[j+1][1]];
        j++;
    }
    if(j==0)
        HEAD->next=NULL;
}

void huffman::construct_tree()
{
    int f,l=MAX;
    while (HEAD->next!=NULL)
    {
        d[l]=(data*)malloc(sizeof(data));
        //  add two minimums and insert into tree
        f=HEAD->freq+HEAD->next->freq;
        d[l]->freq=f;
        strcpy(d[l]->ch,HEAD->ch);
        strcat(d[l]->ch,HEAD->next->ch);
        d[l]->left=HEAD;
        d[l]->right=HEAD->next;
        insert_node(d[l]);
        l++;
    }
}

//  function to insert node into a list in sorted way
void huffman::insert_node(data *temp)
{
    data *curr=HEAD->next->next,*prev=NULL;

    while(curr!=NULL)
    {
        if(curr->freq >= temp->freq)
        {
            break;
        }
        prev=curr;
        curr=curr->next;
    }
    if(prev==NULL)
    {
        temp->next=HEAD->next->next;
        HEAD=temp;
    }
    else if(curr==NULL)
    {
        prev->next=temp;
        temp->next=NULL;
        HEAD=HEAD->next->next;
    }
    else
    {
        temp->next=prev->next;
        prev->next=temp;
        HEAD=HEAD->next->next;
    }
}

//  function to find codes of charactars
void huffman :: make_code(data *temp,int l,char *c)
{
    if(temp->left==NULL && temp->right==NULL)
    {
        strcpy(temp->code,c);
        cout<<temp->ch<<" "<<temp->freq<<" "<<temp->code<<"\n";
        return;
    }
    else
    {
        strcpy(temp->code,c);
        //  left as 0
        c[l]='0';
        c[l+1]='\0';
        make_code(temp->left,l+1,c);
        //  right as 1
        c[l]='1';
        c[l+1]='\0';
        make_code(temp->right,l+1,c);
    }
}

void huffman::encode()
{
    int len=strlen(str);
    for(int i=0;i<len;i++)
    {
        strcat(out,d[(int)str[i]]->code);
    }
}

void huffman::decode()
{
    int len=strlen(out),l=0;
    char s[100]={'\0'};
    data *temp=HEAD;
    for(int i=0;i<len && temp!=NULL && out[i]!='\0';i++)
    {
        if(out[i]=='0')
            temp=temp->left;
        else
            temp=temp->right;
        if(temp!=NULL &&temp->left==NULL && temp->right==NULL)
        {
            s[l++]=temp->ch[0];
            temp=HEAD;
        }
    }
    cout<<"Decoded message is "<<s<<endl;
}

void huffman::solution()
{
    input();
    make_data();
    construct_list();
    construct_tree();
    char c[MAX]="\0";
    make_code(HEAD,0,c);
    encode();
    decode();
    output();
}

int main()
{
    huffman v;
    v.solution();
    return 0;
}
