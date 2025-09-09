#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

typedef struct s_token
{
	int			    i;
	struct s_token	*next;
}	t_token;


void    fill_list(t_token **head, int i)
{
    int     j = 0;
    t_token *new;
    t_token *tail = NULL;

    while (j < i)
    {
        new = malloc(sizeof(t_token));
        new->i = j;
        new->next = NULL;

        if (*head == NULL)
        {
            *head = new;
            tail = new;
        }
        else
        {
            tail->next = new;
            tail = new;
        }
        j++;
    }    
}

void free_list(t_token *head)
{
    t_token *tmp;
    while(head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_list(t_token *head)
{
    while (head)
    {
        printf("-------------\n");
        printf("Node[%d]\n", head->i);
        printf("head->i: %d\n", head->i);
        head = head->next;
    }
}

void    append_list(int nr)
{
    printf("IN APPEND LIST %d\n", nr);
}

void splice(t_token **head, t_token** second_list)
{
    t_token **link = head;
    t_token *tail_second = *second_list;
    t_token *next;
 
    while (tail_second && tail_second->next)
        tail_second = tail_second->next;
 
    while (*link)
    {
        if ((*link)->i == 2)
        {
            printf("SPLICE AT i == 2 ==\n");
            next = (*link)->next;
            free(*link);
            *link = *second_list;
            tail_second->next = next;
            return ;
        }
        link = &(*link)->next;
    }
}

void splice_new_list(t_token **head)
{
    t_token *second_list;
    second_list = NULL;
    fill_list(&second_list, 3);
    printf("\n========== 2nd list ===========\n\n");
    print_list(second_list);
    // (void)*head;
    splice(&(*head), &second_list);
}
int main(void)
{
    t_token *tokens;
    tokens = NULL;

    int i = 5;
    fill_list(&tokens, i);
    print_list(tokens);
    splice_new_list(&tokens);
    print_list(tokens);
    free_list(tokens);

    return (0);
}