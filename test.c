#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main(int argc, char **argv)
{
	int pid = 1;
	char *ptr = NULL;
	size_t size = 10240;
	ptr = (char*)malloc(size);
	long status = syscall(335, id, ptr, size);
	printf("System call, status = %ld\n", status);
	if (status != -1) {
		for (int i = 0; i < size; ++i) {
			printf("%c", ptr[i]);
		}
	}
	return 0;
}
