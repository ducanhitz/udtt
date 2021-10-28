#include <iostream>
#include <malloc.h>

using namespace std;

struct Call
{
    int n;
    char a, b, c;
};

struct Stack
{
    int top;
    Call *e;
};

void init(Stack &s)
{
    s.top = -1;
    s.e = NULL;
}

bool empty(Stack s)
{
    return s.top == -1;
}

void push(Stack &s, Call call_in)
{
    if (empty(s))
    {
        s.e = new Call[1];
    }
    else
    {
        s.e = (Call *)realloc(s.e, (s.top + 2) * sizeof(Call));
    }
    s.top++;
    s.e[s.top] = call_in;
}

void pop(Stack &s, Call &call_out)
{
    if (empty(s))
        return;
    call_out = s.e[s.top];
    if (s.top == 0)
    {
        delete[] s.e;
        init(s);
    }
    else
    {
        s.e = (Call *)realloc(s.e, s.top * sizeof(Call));
        s.top--;
    }
}

void thapHaNoi(Call first_call)
{
    Call call_in, call_out;
    Stack s;
    init(s);
    call_in = first_call;
    push(s, call_in);
    while(!empty(s))
    {
        pop(s, call_out);
        if(call_out.n == 1)
            cout << "Chuyen 1 dia tu coc " << call_out.a << " sang coc " << call_out.c << endl;
        else {
            call_in.n = call_out.n - 1;
            call_in.a = call_out.b;
            call_in.b = call_out.a;
            call_in.c = call_out.c;
            push(s, call_in);

            call_in.n = call_out.n - 1;
            call_in.a = call_out.a;
            call_in.b = call_out.c;
            call_in.c = call_out.b;
            push(s, call_in);
        }
    }
}

int main()
{
    Call first_call = {3, 'A', 'B', 'C'};

    thapHaNoi(first_call);
}
