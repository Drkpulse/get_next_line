/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:28:38 by joseferr          #+#    #+#             */
/*   Updated: 2023/11/07 17:30:05 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Join and free
char *ft_comb_free(char *acc_content, char *new_content)
{
    char *temp_combined;

    temp_combined = ft_strjoin(acc_content, new_content);
    free(acc_content);
    return temp_combined;
}

// Extract next line
char *extract_next_line(char *buff)
{
    int i_buff = 0;
    int i_line = 0;
    char *line;

    // Find the length of the first line
    while (buff[i_buff] && buff[i_buff] != '\n')
        i_buff++;

    // If end of line is '\0', return NULL
    if (!buff[i_buff])
    {
        free(buff);
        return NULL;
    }

    // Calculate the length of the remaining content after the first line
    line = ft_calloc((ft_strlen(buff) - i_buff + 1), sizeof(char));

    // Skip the newline character
    i_buff++;

    // Copy the remaining content into the 'line' variable
    while (buff[i_buff])
        line[i_line++] = buff[i_buff++];

    free(buff);
    return line;
}

// Extract line for return
char *extract_line(char *buff)
{
    char *line;
    int i_buff = 0;

    // If there is no line, return NULL
    if (!buff[i_buff])
        return NULL;

    // Find the end of the line
    while (buff[i_buff] && buff[i_buff] != '\n')
        i_buff++;

    // Allocate memory for the line (including space for '\n')
    line = ft_calloc(i_buff + 2, sizeof(char));

    // Copy content up to the newline character (or '\0')
    i_buff = 0;
    while (buff[i_buff] && buff[i_buff] != '\n')
    {
        line[i_buff] = buff[i_buff];
        i_buff++;
    }

    // If newline character is found, add it to the line
    if (buff[i_buff] && buff[i_buff] == '\n')
        line[i_buff++] = '\n';

    return line;
}

char *read_file(int fd, char *res)
{
    char *buff;
    int bytes_read;

    // Allocate memory if 'res' doesn't exist
    if (!res)
        res = ft_calloc(1, 1);

    // Allocate memory for the buffer
    buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    bytes_read = 1;

    // Continue reading until the end of file
    while (bytes_read > 0)
    {
        // Read from the file descriptor into the buffer
        bytes_read = read(fd, buff, BUFFER_SIZE);

        // Check for read error
        if (bytes_read == -1)
        {
            free(buff);
            return NULL;
        }

        // Null-terminate the buffer to avoid leaks
        buff[bytes_read] = 0;

        // Combine and free
        res = ft_comb_free(res, buff);

        // Exit loop if newline character is found
        if (ft_strchr(buff, '\n'))
            break;
    }

    free(buff);
    return res;
}

char *get_next_line(int fd)
{
    static char *content_buff;
    char *curr_line;

    // Error handling
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return NULL;

    // Read file and update buffer
    content_buff = read_file(fd, content_buff);

    // Check if there is no more content
    if (!content_buff)
        return NULL;

    // Extract line from the buffer
    curr_line = extract_line(content_buff);

    // Update buffer to exclude the extracted line
    content_buff = extract_next_line(content_buff);

    return curr_line;
}

/*
#define BUFFER_SIZE 42
int main()
{
    int file_descriptor;

    // Open a file for reading
    file_descriptor = open("test.txt", O_RDONLY);

    // Check for file open error
    if (file_descriptor < 0)
    {
        perror("Error opening file");
        return 1; // Exit with an error code
    }

    char *line;

    // Read lines until the end of the file
    while ((line = get_next_line(file_descriptor)) != NULL)
    {
        printf("Line: %s", line);

        // Don't forget to free the allocated memory for each line
        free(line);
    }

    // Close the file descriptor
    close(file_descriptor);

    return 0; // Exit successfully
}
*/
