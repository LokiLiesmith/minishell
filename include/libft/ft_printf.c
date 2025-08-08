/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:30:40 by mrazem            #+#    #+#             */
/*   Updated: 2025/04/06 15:39:32 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, format);
	if (!format)
		return (-1);
	ft_printed(-1);
	while (format[i])
	{
		if (format[i] != '%')
		{
			if (ft_safe_write(1, &format[i++], 1) == -1)
				return (va_end(ap), -1);
		}
		else
		{
			i++;
			if (ft_typehandler(&ap, format[i++]) == -1)
				return (va_end(ap), -1);
		}
	}
	va_end(ap);
	return (ft_printed(0));
}

int	ft_typehandler(va_list *ap, char specifier)
{
	if (specifier == 'd' || specifier == 'i')
		return (ft_printnum(va_arg(*ap, int), 1));
	else if (specifier == 's')
		return (ft_printstring(va_arg(*ap, char *)));
	else if (specifier == 'c')
		return (ft_printchar(va_arg(*ap, int)));
	else if (specifier == 'p')
		return (ft_printptr(va_arg(*ap, void *)));
	else if (specifier == 'u')
		return (ft_printunsigned(va_arg(*ap, unsigned int)));
	else if (specifier == 'x')
		return (ft_printhex(va_arg(*ap, unsigned int), 0));
	else if (specifier == 'X')
		return (ft_printhex(va_arg(*ap, unsigned int), 1));
	else if (specifier == '%')
		return (ft_safe_write(1, "%", 1));
	return (0);
}
/* 
//TESTERFUNK
int	main(void)
{
	char	*string;
	int		decimal;

	string = "ThisIsTen!11";
	decimal = -5;

	ft_printf(">>>FT_PRINTF - STRING<<<\n");
	ft_printf("four\n%s\nfive5\n", string);
	ft_printf("four\n%s\nfive5\n", NULL);
	printf(">>>PRINTF - STRING<<<\n", NULL);
	printf("Count: %d", printf("four\n%s\nfive5\n", NULL));
	
	ft_printf(">>>FT_PRINTF - Decimal<<<\n");
	ft_printf("%d\n", decimal);
	ft_printf("This is a test!\n%s\n%d\n", string, decimal);
	printf(">>>PRINTF - Decimal<<<\n");
	printf("Count: %d\n", printf("%d\n", decimal));
		
	printf("\n");
	ft_printf("----- FT_PRINTF - CHAR -----\n");
	printf("Returned chars: %d\n", ft_printf("%c\n", 'c'));
	printf("----- PRINTF - CHAR -----\n");
	printf("Count: %d\n", printf("%c\n", '3'));

	printf("\n");
	ft_printf("----- FT_PRINTF - POINTER -----\n");
	printf("Returned chars: %d\n", ft_printf("%p\n", &decimal));
	printf("----- PRINTF - POINTER -----\n");
	printf("Count: %d\n", printf("%p\n", &decimal));
	
	printf("\n");
	ft_printf("----- FT_PRINTF - HExxx -----\n");
	printf("Returned chars: %d\n", ft_printf("%x\n", 1000));
	printf("----- PRINTF - HExxx -----\n");
	printf("Count: %d\n", printf("%x\n", 1000));
	
	printf("\n");
	ft_printf("----- FT_PRINTF - HEXXX -----\n");
	printf("Returned chars: %d\n", ft_printf("%X\n", 1000));
	printf("----- PRINTF - HEXXX -----\n");
	printf("Count: %d\n", printf("%X\n", 1000));
	
	

	return (0);
}
 */