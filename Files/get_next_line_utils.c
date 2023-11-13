/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:29:02 by joseferr          #+#    #+#             */
/*   Updated: 2023/11/07 17:30:06 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *strjoin(const char *s1, const char *s2)
{
	int total_size;
	char *res;
	int i;
	int j;

	i = 0;
	total_size = strlen(s1) + strlen(s2);
	res = malloc(sizeof(char) * (total_size + 1));
	if (!res || !s1 || !s2)
		return NULL;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[total_size] = '\0';
	return res;
}

char *strchr(const char *str, int target_char)
{
	char *str_ptr;

	str_ptr = (char *)str;
	while (*str_ptr != target_char && *str_ptr != '\0')
		str_ptr++;
	if (*str_ptr == target_char)
		return str_ptr;
	else
		return NULL;
}

void bzero(void *s, size_t n)
{
	char *str;
	size_t i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void *calloc(size_t count, size_t size)
{
    char *res;

	res = malloc(size * count);
	if (!res)
		return NULL;
	bzero(res, size * count);
	return res;
}

size_t strlen(const char *str)
{
	size_t len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return len;
}

