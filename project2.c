#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mem {
	int size;
	int start;
	char name[16];
	struct mem *next;
};
typedef struct mem mem;

void bestFit(mem **head, char name[16], int size, int totalMem) {
	mem *currNode = *head;
	if (currNode == NULL) {
		if (size <= totalMem) {
			mem *new = (mem*) malloc(sizeof(mem));
			new->size = size;
			new->start = 0;
			strncpy(new->name, name, 16);
			new->next = NULL;
			*head = new;
			printf("ALLOCATED %s %d\n", name, 0);
		}
		else {
			printf("FAIL REQUEST %s %d\n", name, size);
		}
	}
	else {
		int bestSize = totalMem + 1;
		int bestLocation = -1;
		int curr = 0;
		while (currNode != NULL) {
			if (currNode->start - curr < bestSize && currNode->start - curr >= size) {
				bestSize = currNode->start - curr;
				bestLocation = curr;
			}
			curr = currNode->start + currNode->size;
			currNode = currNode->next;
		}
		if (totalMem - curr < bestSize && totalMem - curr >= size) {
			bestSize = totalMem - curr;
			bestLocation = curr;
		}
		if (bestLocation != -1) {
			mem *new = (mem*) malloc(sizeof(mem));
			new->start = bestLocation;
			new->size = size;
			strncpy(new->name, name, 16);
			mem *start = *head;
			if (start->start > bestLocation) {
				new->next = *head;
				*head = new;
			}
			else {
				currNode = *head;
				while (currNode != NULL && currNode->start + currNode->size < new->start) {
					currNode = currNode->next;
				}
				if (currNode != NULL) {
					new->next = currNode->next;
					currNode->next = new;
				}
			}
			printf("ALLOCATED %s %d\n", name, new->start);
		}
		else {
			printf("FAIL REQUEST %s %d\n", name, size);
		}
	}
}

void firstFit(mem **head, char name[16], int size, int totalMem) {
	mem *currNode = *head;
	if (currNode == NULL) {
		if (size <= totalMem) {
			mem *new = (mem*) malloc(sizeof(mem));
			new->size = size;
			new->start = 0;
			strncpy(new->name, name, 16);
			new->next = NULL;
			*head = new;
			printf("ALLOCATED %s %d\n", name, 0);
		}
		else {
			printf("FAIL REQUEST %s %d\n", name, size);
		}
	}
	else {
		int curr = 0;
		mem *last = NULL;
		while (currNode != NULL) {
			if (currNode->start - curr >= size) {
				mem *new = (mem*) malloc(sizeof(mem));
				new->start = curr;
				new->size = size;
				strncpy(new->name, name, 16);
				if (last != NULL) {
					new->next = last->next;
					last->next = new;
				}
				else {
					new->next = *head;
					*head = new;
				}
				printf("ALLOCATED %s %d\n", name, new->start);
				return;
			}
			curr = currNode->start + currNode->size;
			last = currNode;
			currNode = currNode->next;
		}
		if (totalMem - curr >= size) {
			mem *new = (mem*) malloc(sizeof(mem));
			new->start = curr;
			new->size = size;
			strncpy(new->name, name, 16);
			if (last != NULL) {
				new->next = last->next;
				last->next = new;
			}
			printf("ALLOCATED %s %d\n", name, new->start);
		}
		else {
			printf("FAIL REQUEST %s %d\n", name, size);
		}
	}
}

void nextFit(mem **head, char name[16], int size, int totalMem, mem **next) {
	mem *currNode = *head;
	if (currNode == NULL) {
		if (size <= totalMem) {
			mem *new = (mem*) malloc(sizeof(mem));
			new->size = size;
			new->start = 0;
			strncpy(new->name, name, 16);
			new->next = NULL;
			*head = new;
			printf("ALLOCATED %s %d\n", name, 0);
			*next = new;
		}
		else {
			printf("FAIL REQUEST %s %d\n", name, size);
			*next = NULL;
		}
	}
	else {
		currNode = *next;
		int curr = 0;
		if (currNode != NULL) {
			curr = currNode->start;
		}
		mem *last = NULL;
		while (currNode != NULL) {
			if (currNode->start - curr >= size) {
				mem *new = (mem*) malloc(sizeof(mem));
				new->start = curr;
				new->size = size;
				strncpy(new->name, name, 16);
				if (last != NULL) {
					new->next = last->next;
					last->next = new;
				}
				else {
					new->next = *head;
					*head = new;
				}
				printf("ALLOCATED %s %d\n", name, new->start);
				*next = new;
				return;
			}
			curr = currNode->start + currNode->size;
			last = currNode;
			currNode = currNode->next;
		}
		if (totalMem - curr >= size && last != NULL) {
			mem *new = (mem*) malloc(sizeof(mem));
			new->start = curr;
			new->size = size;
			strncpy(new->name, name, 16);
			new->next = last->next;
			last->next = new;
			printf("ALLOCATED %s %d\n", name, new->start);
			*next = new;
			return;
		}
		currNode = *head;
		curr = 0;
		last = NULL;
		while (currNode != NULL && currNode != *next) {
			if (currNode->start - curr >= size) {
				mem *new = (mem*) malloc(sizeof(mem));
				new->start = curr;
				new->size = size;
				strncpy(new->name, name, 16);
				if (last != NULL) {
					new->next = last->next;
					last->next = new;
				}
				else {
					new->next = *head;
					*head = new;
				}
				printf("ALLOCATED %s %d\n", name, new->start);
				*next = new;
				return;
			}
			curr = currNode->start + currNode->size;
			last = currNode;
			currNode = currNode->next;
		}
		if (totalMem - curr >= size) {
			mem *new = (mem*) malloc(sizeof(mem));
			new->start = curr;
			new->size = size;
			strncpy(new->name, name, 16);
			if (last != NULL) {
				new->next = last->next;
				last->next = new;
			}
			printf("ALLOCATED %s %d\n", name, new->start);
			*next = new;
			return;
		}
		printf("FAIL REQUEST %s %d\n", name, size);
		*next = NULL;
	}
}

void worstFit(mem **head, char name[16], int size, int totalMem) {
	mem *currNode = *head;
	if (currNode == NULL) {
		if (size <= totalMem) {
			mem *new = (mem*) malloc(sizeof(mem));
			new->size = size;
			new->start = 0;
			strncpy(new->name, name, 16);
			new->next = NULL;
			*head = new;
			printf("ALLOCATED %s %d\n", name, 0);
		}
		else {
			printf("FAIL REQUEST %s %d\n", name, size);
		}
	}
	else {
		int worstSize = size - 1;
		int worstLocation = -1;
		int curr = 0;
		while (currNode != NULL) {
			if (currNode->start - curr > worstSize && currNode->start - curr >= size) {
				worstSize = currNode->start - curr;
				worstLocation = curr;
			}
			curr = currNode->start + currNode->size;
			currNode = currNode->next;
		}
		if (totalMem - curr > worstSize && totalMem - curr >= size) {
			worstSize = totalMem - curr;
			worstLocation = curr;
		}
		if (worstLocation != -1) {
			mem *new = (mem*) malloc(sizeof(mem));
			new->start = worstLocation;
			new->size = size;
			strncpy(new->name, name, 16);
			mem *start = *head;
			if (start->start > worstLocation) {
				new->next = *head;
				*head = new;
			}
			else {
				currNode = *head;
				while (currNode != NULL && currNode->start + currNode->size < new->start) {
					currNode = currNode->next;
				}
				new->next = currNode->next;
				currNode->next = new;
			}
			printf("ALLOCATED %s %d\n", name, new->start);
		}
		else {
			printf("FAIL REQUEST %s %d\n", name, size);
		}
	}
}

void release(mem **head, char name[16]) {
	mem *last = NULL;
	mem *memory = *head;
	while (memory != NULL && strcmp(memory->name, name) != 0) {
		last = memory;
		memory = memory->next;
	}
	if (memory != NULL) {
		printf("FREE %s %d %d\n", name, memory->size, memory->start);
		if (last == NULL) {
			*head = memory->next;
		}
		else {
			last->next = memory->next;
		}
		free(memory);
	}
	else {
		printf("FAIL RELEASE %s\n", name);
	}
}

void listAvailable(mem **head, int totalMem) {
	int curr = 0;
	int end = totalMem;
	int full = 1;
	mem *memory = *head;
	while (memory != NULL) {
		if (curr < memory->start) {
			printf("(%d, %d) ", memory->start - curr, curr);
			full = 0;
		}
		curr = memory->start + memory->size;
		memory = memory->next;
	}
	if (curr < end) {
		printf("(%d, %d) ", end - curr, curr);
		full = 0;
	}
	if (full) {
		printf("FULL\n");
	}
	else {
		printf("\n");
	}
}

void listAssigned(mem **head) {
	mem *memory = *head;
	if (memory == NULL) {
		printf("NONE\n");
	}
	else {
		while (memory != NULL) {
			printf("(%s, %d, %d) ", memory->name, memory->size, memory->start);
			memory = memory->next;
		}
		printf("\n");
	}
}

void find(mem **head, char name[16]) {
	int found = 0;
	mem *memory = *head;
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
	int type = -1;
	if (strcmp(argv[1], "BESTFIT") == 0) {
		//printf("Best fit\n");
		type = 0;
	}
	else if (strcmp(argv[1], "FIRSTFIT") == 0) {
		//printf("First fit\n");
		type = 1;
	}
	else if (strcmp(argv[1], "NEXTFIT") == 0) {
		//printf("Next fit\n");
		type = 2;
	}
	else if (strcmp(argv[1], "WORSTFIT") == 0) {
		//printf("Worst fit\n");
		type = 3;
	}
	else {
		//printf("Invalid mode\n");
		return -1;
	}

	mem *next = NULL;

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
			//printf("REQUEST %s %d\n", name, size);
			if (type == 0) {
				bestFit(&memory, name, size, totalMem);
			}
			else if (type == 1) {
				firstFit(&memory, name, size, totalMem);
			}
			else if (type == 2) {
				nextFit(&memory, name, size, totalMem, &next);
			}
			else {
				worstFit(&memory, name, size, totalMem);
			}
		}
		else if (strcmp(command, "RELEASE") == 0) {
			char name[16];
			sscanf(line, "%s %s\n", command, name);
			//printf("RELEASE %s\n", name);
			release(&memory, name);
		}
		else if (strcmp(command, "LIST") == 0) {
			char command2[16];
			sscanf(line, "%s %s\n", command, command2);
			if (strcmp(command2, "AVAILABLE") == 0) {
				//printf("LIST AVAILABLE\n");
				listAvailable(&memory, totalMem);
			}
			else if (strcmp(command2, "ASSIGNED") == 0) {
				//printf("LIST ASSIGNED\n");
				listAssigned(&memory);
			}
			else {
				printf("Invalid command\n");
				return -1;
			}
		}
		else if (strcmp(command, "FIND") == 0) {
			char name[16];
			sscanf(line, "%s %s\n", command, name);
			//printf("FIND %s\n", name);
			find(&memory, name);
		}
		else {
			printf("Invalid command\n");
			return -1;
		}

	}
	return 0;
}
