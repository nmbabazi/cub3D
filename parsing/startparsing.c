/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:42:00 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/28 16:05:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		ft_pars(t_param *param, char *line, int *tab)
{
	if (*line == '1' || *line == ' ')
		return (-2);
	if (*line == 'R')
		return (ft_resolution(line, param, tab));
	if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
	{
		ft_filltab(line, tab);
		if (ft_checkdoublon(tab, line) == 0)
			return (3);
		return (ft_texture(line, param, tab));
	}
	if (*line == 'C' || *line == 'F')
		return (ft_color(line, param, tab));
	if (*line == '\0' || *line == '\n')
	{
		free(line);
		return (1);
	}
	ft_putstr_fd("ERROR:\n WRONG CHARACTER IN SCENE\n", 1);
	free(line);
	return (0);
}

int		ft_suiteparsing(t_param *param, char *line, int *r, int fd)
{
	int ret;

	ret = 0;
	if (*r == 0)
	{
		free(line);
		return (5);
	}
	if ((ret = ft_buildmap(param, line, r, fd)) != 1)
		return (ret);
	return (1);
}

int		ft_parsingscene(int fd, t_param *param, char *line)
{
	int		r;
	int		*tab;
	int		ret;

	r = 0;
	tab = ft_createtab(tab, 8);
	while ((r = get_next_line(&line, fd)) > 0)
	{
		ret = ft_pars(param, line, tab);
		if (ret == -2)
			break ;
		if (ret != 1)
		{
			free(tab);
			return (ret);
		}
	}
	if ((ret = ft_suiteparsing(param, line, &r, fd)) != 1)
	{
		free(tab);
		return (ret);
	}
	if (ft_checktab(tab, 8) == 0)
		return (6);
	return (ret);
}

void	ft_errormessage(int ret, char *line)
{
	if (ret == 2)
		ft_putstr_fd("ERROR:\n resolution\n", 1);
	else if (ret == 3)
		ft_putstr_fd("ERROR:\n texture\n", 1);
	else if (ret == 4)
		ft_putstr_fd("ERROR:\n colors\n", 1);
	else if (ret == 5)
		ft_putstr_fd("ERROR:\n map\n", 1);
	else if (ret == 6)
		ft_putstr_fd("ERROR:\n WRONG NUMBER OF ELENMENT IN SCENE\n", 1);
}

int		ft_parsing(char *fichier, t_param *param)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 0;
	line = NULL;
	fd = open(fichier, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("ERROR:\n CAN'T OPEN SCENE\n", 1);
		return (0);
	}
	ret = ft_parsingscene(fd, param, line);
	if (ret != 1)
		ft_errormessage(ret, line);
	close(fd);
	return (ret);
}
