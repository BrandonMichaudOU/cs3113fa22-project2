#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mem {
	int size;
	int start;
	char *name;
	struct mem *next;
};
typedef struct mem mem;

void release(mem *memory, char name[16]) {
	mem *last;
	while (memory != NULL && strcmp(memory->name, name) != 0) {
		last = memory;
		memory = memory->next;
	}
	if (memory != NULL) {
		printf("FREE %s %d %d\n", name, memory->size, memory->start);
		last->next = memory->next;
	}
	else {
		printf("FAIL RELEASE %s\n", name);
	}
}

void listAvailable(mem *memory, int totalMem) {
	int curr = 0;
	int end = totalMem;
	int full = 1;
	while (memory != NULL) {
		if (curr < memory->start) {
			printf("(%d, %d) ", memory->start - curr, curr);
			full = 0;
		}
		curr = memory->start + memory->size;
		memory = memory->next;
	}
	if (curr <= end) {
		printf("(%d, %d) ", end - curr + 1, curr);
		full = 0;
	}
	if (full) {
		printf("FULL\n");
	}
	else {
		printf("\n");
	}
}

void listAssigned(mem *memory) {
	if (memory == NULL) {
		printf("None\n");
	}
	else {
		while (memory != NULL) {
			printf("(%s, %d, %d) ", memory->name, memory->size, memory->start);
			memory = memory->next;
		}
		printf("\n");
	}
}

void find(mem *memory, char name[16]) {
	int found = 0;
	while (memory != NULL) {
		if (strcmp(memory->name, name) == 0) {
			printf("(%s, %d, %d)\n", name, memory->size, memory->start);
			found = 1;
			break;
		}
		memory = memory->next;
	}
	if (found == 0) {
		printf("FAULT\n");
	}
}

int main(int argc, char** argv) {

	int totalMem = atoi(argv[2]);
	mem *memory = NULL;

	FILE *fp = fopen(argv[3], "r");
	if (strcmp(argv[1], "BESTFIT") == 0) {
		printf("Best fit\n");
	}
	else if (strcmp(argv[1], "FIRSTFIT") == 0) {
		printf("First fit\n");
	}
	else if (strcmp(argv[1], "NEXTFIT") == 0) {
		printf("Next fit\n");
	}
	else if (strcmp(argv[1], "WORSTFIT") == 0) {
		printf("Worst fit\n");
	}
	else {
		printf("Invalid mode\n");
	}
	char line[64];
	while (fgets(line, 64, fp) != NULL) {
		if (line[0] == '#') {
			continue;
		}
		char command[16];
		sscanf(line, "%s ", command); 
		if (strcmp(command, "REQUEST") == 0) {
			char name[16];
			int size;
			sscanf(line, "%s %s %d\n", command, name, &size);
			printf("REQUEST %s %d\n", name, size);
		}
		else if (strcmp(command, "RELEASE") == 0) {
			char name[16];
			sscanf(line, "%s %s\n", command, name);
			//printf("RELEASE %s\n", name);
			release(memory, name);
		}
		else if (strcmp(command, "LIST") == 0) {
			char command2[16];
			sscanf(line, "%s %s\n", command, command2);
			if (strcmp(command2, "AVAILABLE") == 0) {
				//printf("LIST AVAILABLE\n");
				listAvailable(memory, totalMem);
			}
			else if (strcmp(command2, "ASSIGNED") == 0) {
				//printf("LIST ASSIGNED\n");
				listAssigned(memory);
			}
			else {
				printf("Invalid command\n");
			}
		}
		else if (strcmp(command, "FIND") == 0) {
			char name[16];
			sscanf(line, "%s %s\n", command, name);
			//printf("FIND %s\n", name);
			find(memory, name);
		}
		else {
			printf("Invalid command\n");
		}

	}
	return 0;
}
