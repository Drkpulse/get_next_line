/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:07:26 by joseferr          #+#    #+#             */
/*   Updated: 2023/12/06 14:25:43 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_comb_free(char *content, char *new)
{
	char	*temp;

	temp = ft_strjoin(content, new);
	free(content);
	return (temp);
}

char	*extract_next_line(char *buff)
{
	int		i;
	int		k;
	char	*line;

	i = 0;
	k = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
		return (free(buff), NULL);
	line = ft_calloc((ft_strlen(buff) - i + 1), sizeof(char));
	i++;
	while (buff[i])
		line[k++] = buff[i++];
	line[k] = '\0';
	free(buff);
	return (line);
}

char	*extract_line(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*read_file(int fd, char *rest)
{
	char	*buffer;
	int		byread;

	if (!rest)
		rest = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byread = 1;
	while (byread > 0)
	{
		byread = read(fd, buffer, BUFFER_SIZE);
		if (byread == -1)
			break ;
		buffer[byread] = '\0';
		rest = ft_comb_free(rest, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	if (!*rest || byread < 0)
		return (free(rest), NULL);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*content[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	content[fd] = read_file(fd, content[fd]);
	if (!content[fd])
		return (NULL);
	line = extract_line(content[fd]);
	content[fd] = extract_next_line(content[fd]);
	return (line);
}
/*
int	main(void)
{
	int		file_descriptor;
	char	*line;

	file_descriptor = open("test.txt", O_RDONLY);
	if (file_descriptor < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(file_descriptor)) != NULL)
	{
		printf("Line: %s", line);
		free(line);
	}
	close(file_descriptor);
	return (0);
}
*/
