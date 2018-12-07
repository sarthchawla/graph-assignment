#include <bits/stdc++.h>
#include <cstring>
using namespace std;
struct node
{
    char data[50];
    int wt;
    struct node *next;
};
struct stack1
{
    struct node *p;
    struct stack1 *next;
};
struct stack1 *push(struct stack1 *s, struct node *add)
{
    struct stack1 *n = new struct stack1, *ptr;
    n->p = add;
    n->next = NULL;
    if (s == NULL)
    {
        s = n;
    }
    else
    {
        ptr = s;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = n;
    }
    return s;
}
struct stack1 *pop(struct stack1 *s)
{
    if (s == NULL)
    {
        return NULL;
    }
    else if (s->next == NULL)
    {
        delete s;
        return NULL;
    }
    else
    {
        struct stack1 *p = s, *ss = s;
        while (ss->next != NULL)
        {
            p = ss;
            ss = ss->next;
        }
        p->next = NULL;
        delete ss;
        return s;
    }
}
struct stack1 *pop_Q(struct stack1 *s)
{
    if (s == NULL || s->next == NULL)
        return NULL;
    struct stack1 *p = s;
    s = s->next;
    delete p;
    return s;
}
struct node *top(struct stack1 *s)
{
    if (s == NULL)
        return NULL;
    while (s->next != NULL)
    {
        s = s->next;
    }
    return s->p;
}
void p1(struct stack1 *s)
{
    while (s != NULL)
    {
        printf("*%s*", s->p->data);
        s = s->next;
    }
    printf("\n");
}
struct node *insert(struct node *start, char *x, int y)
{
    struct node *n = new struct node, *ptr;
    n->next = NULL;
    strcpy(n->data, x);
    n->wt = y;
    if (start == NULL)
    {
        start = n;
    }
    else
    {
        ptr = start;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = n;
    }

    return start;
}
int check_ref(string *ref, string x, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (ref[i] == x)
            return i;
    }
    return -1;
}
void print(struct node *start)
{
    while (start != NULL)
    {
        cout << "->" << start->data << "(" << start->wt << ")";
        start = start->next;
    }
    printf("\n\n");
}
int len(struct node *start, int op)
{
    int c = 0, d = 0;
    while (start != NULL)
    {
        if (start->wt > 0)
        {
            c++;
        }
        d++;
        start = start->next;
    }
    if (op == 0)
        return c;
    if (op == 1)
    {
        return d;
    }
    return 0;
}
void influence_controversial(string *ref, struct node **start, int n, int op)
{
    int max = 0, i, x;
    for (i = 0; i < n; i++)
    {
        x = len(start[i], op);
        if (max < x)
        {
            max = x;
        }
    }
    for (i = 0; i < n; i++)
    {
        x = len(start[i], op);
        if (x == max)
        {
            cout << ref[i] << " ";
        }
    }
}
void mark_it(string str, string *ref, int *mark, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (str == ref[i])
            break;
    }
    mark[i] = 1;
}
int check_mark(string str, string *ref, int *mark, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (ref[i] == str)
            break;
    }
    if (mark[i] > 0)
        return 1;
    return 0;
}
int outreach(string *ref, struct node **start, string str, int n)
{
    int i, d = 0;
    int *mark = new int[n];
    for (i = 0; i < n; i++)
    {
        if (ref[i] == str)
        {
            break;
        }
    }
    struct stack1 *s = NULL;
    struct node *ptr = start[i];
    mark[i] = 1;
    do
    {
        while (ptr != NULL)
        {
            if (check_mark(ptr->data, ref, mark, n) == 0)
            {
                s = push(s, ptr);
                mark_it(ptr->data, ref, mark, n);
                //printf("%s ", ptr->data);
                d++;
            }
            ptr = ptr->next;
        }
        ptr = start[check_ref(ref, top(s)->data, n)];
        s = pop(s);
        //printf("\n");
    } while (s != NULL);
    delete s, mark, ptr;
    return d;
}
struct node **update(struct node **start, string *ref, int n, string user, string u2, int wt)
{
    struct node *ptr = start[check_ref(ref, user, n)];
    while (ptr != NULL)
    {
        if (ptr->data == u2)
        {
            ptr->wt = wt;
            break;
        }
    }
    return start;
}
void quit(struct node **start, string *ref, int n, string dir)
{
    struct node *ptr;
    fstream file;
    file.open(dir.c_str());
    int i = 0;
    file << n << "\n";
    while (i < n)
    {
        file << ref[i] << "\n";
        i++;
    }
    for (i = 0; i < n; i++)
    {
        ptr = start[i];
        while (ptr != NULL)
        {
            file << ref[i] << " " << ptr->data << " " << ptr->wt << "\n";
            ptr = ptr->next;
        }
    }
}
void shotest_path(string str, string u2, struct node **start, string *ref, int n)
{
    int i, d = 0, f = 0;
    int *mark = new int[n];
    string *pre = new string[n];
    for (i = 0; i < n; i++)
    {
        if (ref[i] == str)
        {
            break;
        }
    }
    // for (i = 0; i < n; i++)
    //     pre[i] = "-1";
    struct stack1 *s = NULL;
    struct node *ptr = start[i], *p = ptr;
    mark[i] = 1;
    do
    {
        //cout << "*" << p->data;
        while (ptr != NULL)
        {
            if (check_mark(ptr->data, ref, mark, n) == 0 && ptr->wt > 0)
            {
                if (d == 0)
                    pre[check_ref(ref, ptr->data, n)] = ref[i];
                else
                    pre[check_ref(ref, ptr->data, n)] = p->data;
                s = push(s, ptr);
                mark_it(ptr->data, ref, mark, n);
                if (ptr->data == u2)
                {
                    f = 1;
                    break;
                }
            }
            ptr = ptr->next;
        }
        d++;
        //p1(s);
        ptr = start[check_ref(ref, s->p->data, n)];
        p = s->p;
        s = pop_Q(s);
        cout << endl;
    } while (s != NULL && f == 0);
    if (f == 0)
    {
        cout << "\nno path found\n";
        return;
    }
    vector<string> path;
    int crawl = check_ref(ref, u2, n);
    path.push_back(u2);
    //cout << ref[crawl] << pre[crawl];
    while (pre[crawl] != "")
    {
        //cout << pre[crawl];
        path.push_back(pre[crawl]);
        crawl = check_ref(ref, pre[crawl], n);
    }
    cout << "\nPath is::\n";
    for (i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
}
int main(int argc, char const *argv[])
{
    string dir = argv[1];
    fstream file;
    char *word = new char[50], *w2 = new char[50], *w1 = new char[50];
    int n, i, j, wt, index;
    file.open(dir.c_str());
    file >> n;
    //cout << "size=" << n;
    string *ref = new string[n];
    struct node **start = new struct node *[n];
    i = 0;
    while (file >> word)
    {
        if (i < n)
        {
            ref[i] = word;
            //cout << ref[i] << endl;
        }
        else
        {
            break;
        }
        i++;
    }
    //cout << word << endl;
    strcpy(w1, word);
    for (j = 1; file >> word; j++)
    {
        //cout << word << " " << j << "\n";
        switch (j)
        {
        case 0:
            strcpy(w1, word);
            break;
        case 1:
            strcpy(w2, word);
            break;
        case 2:
            if (strcmp(word, "-1") == 0)
            {
                wt = -1;
            }
            else
            {
                wt = 1;
            }

            j = -1;
            index = check_ref(ref, w1, n);
            //cout << w1 << " " << w2 << " " << wt << "\n";
            start[index] = insert(start[index], w2, wt);
            //print(start[index]);
            break;
        }
    }
    cout << "\n\t\tretrived linked list\n\n";
    for (i = 0; i < n; i++)
    {
        cout << ref[i] << " ";
        print(start[i]);
    }
    int a;
    string user, u2;
    do
    {
        cout << "\nenter\n1 for influence()\n2 for controversial()\n3 for outreach_user()\n4 to find shortest path\n5 to update an entry\n-1 to quit\n\n";
        cin >> a;
        switch (a)
        {
        case 1:
            cout << "influence = ";
            influence_controversial(ref, start, n, 0);
            cout << endl;
            break;
        case 2:
            cout << "controversial = ";
            influence_controversial(ref, start, n, 1);
            cout << endl;
            break;
        case 3:
            cout << "\nenter user name to be outreached\n";
            cin >> user;
            cout << "outreach users=" << outreach(ref, start, user, n) << endl;
            break;
        case 4:
            cout << "\nenter the name of user 1 and user 2 for which min distance path is required\n";
            cin >> user >> u2;
            shotest_path(user, u2, start, ref, n);
            cout << endl;
            break;
        case 5:
            cout << "\nenter user 1 name to user 2 name and distance respectively to update\n";
            cin >> user >> u2 >> wt;
            start = update(start, ref, n, user, u2, wt);
            for (i = 0; i < n; i++)
            {
                cout << ref[i] << " ";
                print(start[i]);
            }
            break;
        case -1:
            quit(start, ref, n, dir);
            cout << "\nafter quit() function launch ,updates have been written to input file too\n";
            break;
        }
    } while (a != -1);
    return 0;
}
