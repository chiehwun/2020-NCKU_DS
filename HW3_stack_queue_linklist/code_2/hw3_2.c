#include <stdio.h>
#include "../code_1/Double_LL.h"
char int2code[][3] = {"\0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
int code2int(const char *code);
void print_card(LinkList *lp, int order);
int main()
{
    LinkList *cards = create_ll();
    char input[10];
    for (int i = 0; i < 13; ++i)
    {
        fscanf(stdin, "%s\n", &input[0]);
        push_node(cards, create_node(code2int(input)));
    }

    int next_code = 13;
    while (next_code > 0)
    {
        print_card(cards, 0);
        if (cards->head->val == next_code)
        {
            pop_front_node(cards);
            --next_code;
        }
        else
        {
            int temp = pop_front_node(cards);
            push_node(cards, create_node(temp));
        }
    }
    return 0;
}

int code2int(const char *code) // 0: invalid code
{
    switch (code[0])
    {
    case 'A':
        return 1;
    case 'J':
        return 11;
    case 'Q':
        return 12;
    case 'K':
        return 13;
    default:
        return atoi(code);
    }
}

void print_card(LinkList *lp, int order) // order=0: sequential, order=1: reverse
{
    if (!lp)
    {
        fprintf(stderr, "printLL(): invalid Link List\n");
        exit(EXIT_FAILURE);
    }
    if (!lp->head)
    {
        fprintf(stdout, "printLL(): empty Link List\n");
        return;
    }
    if (order == 0)
    {
        for (Node *np = lp->head; np->next; np = np->next)
            printf("%s ", int2code[np->val]);
        printf("%s\n", int2code[lp->tail->val]);
    }
    else
    {
        for (Node *np = lp->tail; np->prev; np = np->prev)
            printf("%s ", int2code[np->val]);
        printf("%s\n", int2code[lp->head->val]);
    }
}