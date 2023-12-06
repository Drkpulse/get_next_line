/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:28:38 by joseferr          #+#    #+#             */
/*   Updated: 2023/12/06 14:25:49 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*content;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	content = read_file(fd, content);
	if (!content)
		return (NULL);
	line = extract_line(content);
	content = extract_next_line(content);
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
