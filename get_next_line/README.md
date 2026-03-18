*This project has been created as part of the 42 curriculum by ryatan*

---

# get_next_line

---

## Project Description

This aim of this project is the create a function; get_next_line(). This function returns a line from a file specified for each call. 

The prototype of the function is as follows: 
```c 
char    *get_next_line(int fd)
```
Stateful processing is achieved in this project by using a static variable to preserve the state between calls.

#### helper functions

```c
char    *ft_read_line(int fd, char **storage)
```
Reads a line from the text file and stores it into the static variable "storage".

```c
void    ft_append_storage(char *data, char **storage)
```
Adds the scanned line into the storage.

```c
void    *ft_scan_storage(char match, char **storage)
```
Scans the storage after adding to scan for a newline character or terminating character.

```c
void    ft_remove_from_strorage(char match, char **storage)
```

Remove from storage if a newline character is detected and then updates the storage to only contain the remainder after the newline character.

---

## Instruction

Testing with file path hard coded:

##### main.c
```c
#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	const char	*file_path;
	int			fd;
	char		*line_got;
	
	file_path = "./testfile.txt";
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	while ((line_got = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line_got);
		free(line_got);
	}
	close(fd);
	return (0);
}
```

Testing from terminal input:

##### main_term_input.c
```c
#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	const char	*user_input_file_path;
	char		*line_got;
	int			fd;
	
	if (argc < 1)
		return (1);
	user_input_file_path = argv[1];
	fd = open(user_input_file_path, O_RDONLY);
	if (fd == -1)
	{
		printf("File not opened\n");
		return (1);
	}
	while ((line_got = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line_got);
		free(line_got);
	}
	close(fd);
	return (0);
}
``` 
Example test file:

##### testfile.txt
```txt
hello there
    what is
        your
    name
```
Compile the program into an executable:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl
```
or if you want to specify a buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```
and run

```bash
./gnl
```
or
```bash
./gnl testfile.txt
```
---
## Resources
---
