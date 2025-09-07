#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
typedef enum e_token_type
{
	WORD,
	PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*raw;
	char			*value;
	char			*context;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	t_token_type	op;
	int				i;
	ssize_t			len;
	t_token			*head;
	t_token			*tail;
}	t_lexer;


size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	if (dstsize > 0)
	{
		while ((i < dstsize - 1) && (src[i] != '\0'))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	i;

	copy = (char *)malloc(ft_strlen(s) +1);
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substring = (char *) malloc (len +1);
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, s + start, len + 1);
	return (substring);
}
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src && n > 0)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n)
	{
		*ptr++ = 0;
		n--;
	}
}
void	*ft_calloc(size_t count, size_t size)
{
	void	*empty;

	empty = malloc(count * size);
	if (!empty)
		return (NULL);
	ft_bzero(empty, count * size);
	return (empty);
}

///////////////////////////////////////////////////////////////////////////////
								// SETUP FAKE TOKEN //

void	init_token(t_token *t, char *raw, char *value, char *context)
{
	t->raw = strdup(raw);
	t->value = strdup(value);
	t->context = strdup(context);
}
void 	free_token(t_token *t)
{
	free(t->raw);
	free(t->value);
	free(t->context);
}

void print_token(t_token *t)
{
	printf("raw: %s\n", t->raw);
    printf("val: %s\n", t->value);
    printf("ctx: %s\n", t->context);
}
void ctx_push_token(t_token **head, t_token **tail, t_token_type type, char *start, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	new->raw = malloc(sizeof(char) * len + 1);
	if (!new->raw)
		return ;
	ft_memcpy(new->raw, start, len);
	new->raw[len] = '\0';
	new->value = NULL;
	new->context = NULL;
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}
////////////////////////////////////////////////////////////////////////////////////

static int ft_is_delim(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ctx_split_len(char *str, char *context, int i)
{
	int len;
	
	len = 0;
	while(str[i])
	{
		if ((context[i] == '0' || context[i] == 'e') && (ft_is_delim(str[i])))
			return (len);
		i++;
		len++;
	}
	return (len);
}

void init_ctx_token(t_token *new, int len)
{
	new->type = WORD;
	new->raw = NULL;
	new->value = ft_calloc(len + 1, sizeof(char));
	new->context = ft_calloc(len + 1, sizeof(char));
	new->next = NULL;
}

t_token *ctx_push_token(t_token *h, t_token *t, t_token *old, int i, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if(!new)
		return NULL;
	init_ctx_token(new, len);
	// fill_ctx_token(new, i, len, old);
	if (h == NULL)
	{
		h = new;
		t = new;
	}
	else
	{
		t->next = new;
		t = new;
	}
	return (new);
}

void ctx_split(t_token *t)
{
	int		i;
	int 	len;
	t_token *new_head = NULL;
	t_token *new_tail = NULL;

	i = 0;
	len = 0;
	while(t->value[i])
	{
		len = ctx_split_len(t->value, t->context, i);
		if (len > 0)
		{
			// char *val_chunk = ft_substr(t->value, i, len);
			// char *ctx_chunk = ft_substr(t->context, i, len);
			// printf("Create Token(), i:%d, len: %d\n", i, len);
			// printf("Chunk:%s | ctx:%s\n", val_chunk, ctx_chunk);
			// printf("ctxch: %s\n", ctx_chunk);
			ctx_push_token(&new_head, &new_tail, t, i, len);
			printf("Appended: %s\n", new_head->value);
			printf("Appended: %s\n", new_head->context);
			// free(val_chunk);
			// free(ctx_chunk);
			i += len;
		}
		else
			i++;
	}
	printf("Done splitting.\n");
	printf("Splicing.\n");
	// splice_token_list(t, new_head);
}
// aaa b b b
// aaa

int	main(void)
{
	char	*raw = "\"$VAR\""; // VAR="aaa b b b"
	char	*value = "aaa b b b";
	char	*context = "eee0eeeee";
	
	// Case 2: \n in value, not
	// char	*value = "aa\nbbb\n\nbb";
	// char	*context = "ee0e1e022e";
    t_token	token;

	init_token(&token, raw, value, context);
	print_token(&token);
    ctx_split(&token);
	// print_token(&token);
	free_token(&token);

	return (0);
}