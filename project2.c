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

void bestFit(mem *mem, FILE *fp) {

}
void firstFit(mem *mem, FILE *fp) {

}

void nextFit(mem *mem, FILE *fp) {

}

void worstFit(mem *mem, FILE *fp) {

}

int main(int argc, char** argv) {

	int totalMem = atoi(argv[2]);
	mem mem;
	mem.size = totalMem;
	mem.start = 0;
	mem.next = NULL;

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
                        printf("RELEASE %s\n", name);
                }
                else if (strcmp(command, "LIST") == 0) {
			char command2[16];
			sscanf(line, "%s %s\n", command, command2);
			if (strcmp(command2, "AVAILABLE") == 0) {
				printf("LIST AVAILABLE\n");
			}
			else if (strcmp(command2, "ASSIGNED") == 0) {
				printf("LIST ASSIGNED\n");
                        }
			else {
				printf("Invalid command\n");
			}
                }
                else if (strcmp(command, "FIND") == 0) {
			char name[16];
                        sscanf(line, "%s %s\n", command, name);
                        printf("FIND %s\n", name);
                }
                else {
                        printf("Invalid command\n");
                }

        }
	return 0;
}
