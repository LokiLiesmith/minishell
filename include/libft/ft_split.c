/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:55:41 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/22 11:23:41 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//COUNT WORDS FOR ARRAY
size_t	ft_count_words(char const *s, char delimiter)
{
	size_t	count;
	int		in_word;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s != delimiter && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == delimiter)
			in_word = 0;
		s++;
	}
	return (count);
}

//SAFE MALLOC
int	safe_malloc(char **result, int position, size_t buffer)
{
	int	i;

	i = 0;
	result[position] = malloc(buffer);
	if (NULL == result[position])
	{
		while (i < position)
		{
			free(result[i++]);
		}
		free(result);
		return (1);
	}
	return (0);
}

int	fill_array(char **result, char const *s, char delimiter)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimiter && *s)
			++s;
		while (*s != delimiter && *s)
		{
			++len;
			++s;
		}
		if (len)
		{
			if (safe_malloc(result, i, len + 1))
				return (1);
			ft_strlcpy(result[i], s - len, len + 1);
			i++;
		}
	}
	result[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	num_words;
	char	**result;

	if (!s)
		return (NULL);
	num_words = 0;
	num_words = ft_count_words(s, c);
	result = malloc((num_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[num_words] = NULL;
	if (fill_array(result, s, c))
		return (NULL);
	return (result);
}

/* //TESTERFUNCS
// cc -Werror -Wextra -Wall ft_split.c ft_strlcpy.c -o splittest
#include <stdio.h>
#include <unistd.h>

void print_split(char **split)
{
	int i = 0;
	while (split[i] != NULL)
	{
		printf("%s\n", split[i]);
		i++;
	}
}
int main (void)
{
	printf("NrOfWords: %zu\n", (ft_count_words("This is a test!", ' ')));
	printf("NrOfWords: %zu\n", (ft_count_words("This    is a test!", ' ')));
	printf("NrOfWords: %zu\n", (ft_count_words("   This is a test!", ' ')));
	printf("NrOfWords: %zu\n", (ft_count_words("This is a test!   ", ' ')));

	char **result = ft_split("This is a test!   ", ' ');
	print_split(result);
	printf("\n");
	free(result);
	
	result = ft_split("   ", ' ');
	print_split(result);
	printf("\n");
	free(result);
	
	result = ft_split(" spa ces every where   ", ' ');
	print_split(result);
	printf("\n");
	free(result);
	
	result = ft_split("split\nthis\nby\nnewline", '\n');
	print_split(result);
	printf("\n");
	free(result);
	return (0);
}
 */