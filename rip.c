#include <stdio.h>

size_t	ft_strlen(char *str)
{
	size_t	res;

	res = 0;
	if (!str)
		return (res);
	while (str[res])
		res++;
	return (res);
}

void	ft_clear_input(char *str)
{
	size_t	start;
	size_t	end;

	if (!str)
		return ;
	start = 0;
	end = ft_strlen(str);
	while (str[start] && str[start] == ')')
	{
		str[start] = ' ';
		start++;
	}
	while (end-- > 0 && str[end] == '(')
		str[end] = ' ';
}

int	ft_balance(char *str, int *rm_right)
{
	int	balance;

	balance = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '(')
			balance++;
		else if (*str == ')' && balance > 0)
			balance--;
		else if (balance == 0)
		{
			if (*str == ')')
				(*rm_right)++;
		}
		str++;
	}
	return (balance);
}

int	ft_valid_balance(char *str)
{
	int	balance;

	balance = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '(')
			balance++;
		else if (*str == ')')
			balance--;
		if (balance < 0)
			return (-1);
		str++;
	}
	return (balance);
}

int	ft_recursion(char *str, int rm_left, int rm_right, size_t cur)
{
	if (!str[cur])
	{
		if (rm_left == 0 && rm_right == 0 && ft_valid_balance(str) == 0)
			puts(str);
		return (0);
	}
	if (str[cur] && str[cur] == '(')
	{
		if (rm_left > 0)
		{
			str[cur] = ' ';
			ft_recursion(str, rm_left - 1, rm_right, cur + 1);
		}
		str[cur] = '(';
		ft_recursion(str, rm_left, rm_right, cur + 1);
	}
	else if (str[cur] && str[cur] == ')')
	{
		if (rm_right > 0)
		{
			str[cur] = ' ';
			ft_recursion(str, rm_left, rm_right - 1, cur + 1);
		}
		str[cur] = ')';
		ft_recursion(str, rm_left, rm_right, cur + 1);
	}
	if (str[cur] && str[cur] == ' ')
		ft_recursion(str, rm_left, rm_right, cur + 1);
	return (0);
}

int	ft_rip(char *str)
{
	int		balance;
	int		rm_left;
	int		rm_right;

	rm_left = 0;
	rm_right = 0;
	balance = ft_balance(str, &rm_right);
	//printf("BALANCE: %d\n", balance);
	if (balance > 0)
		rm_left = balance;
	//printf("LEFT %d\n RIGHT %d\n",rm_left, rm_right);
	ft_recursion(str, rm_left, rm_right, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (-1);
	ft_clear_input(argv[1]);
	//puts(argv[1]);
	//printf("%d\n", ft_valid_balance(argv[1]));
	if (ft_valid_balance(argv[1]) == 0)
	{
		puts(argv[1]);
		return (0);
	}
	ft_rip(argv[1]);
	return (0);
}
