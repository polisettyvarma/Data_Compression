#define MAX 256
#define FULL (MAX*MAX + MAX)/2

class huffman
{
    struct data
    {
        int freq;
        char code[MAX],ch[MAX];
        struct data *left;
        struct data *right;
        struct data *next;
    };
    data *d[FULL];
    data *HEAD;
    char str[100],out[10000];
    int count;
    int help_array[MAX][2];
public:
    void input();
    void make_data();
    void Sort();
    void construct_list();
    void construct_tree();
    void insert_node(data*);
    void make_code(data*,int,char*);
    void encode();
    void decode();
    void solution();
    void output();
};
