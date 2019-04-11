#include <stdio.h>
#include <string.h>

int main(void){
	char buffer[] = "GET /  HTTP/1.1";

	char *result = strchr(buffer, '/');
	printf("%s\n",result);
	printf("%c\n", *(result+1));
	if (result[1] == ' ') return 0;
	char *result2 = strtok(result+1, " ");

	printf("%s\n", result2);


	return 0;
}