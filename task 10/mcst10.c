#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int maxLen    = 1000;
const int maxVarCnt =  100;
const int nameLen   =   50;

typedef struct {
    char name[nameLen];
    int value;
} IntVar;

IntVar vars[maxVarCnt];

int GetN(const char* name);
int GetOr(char** s);
int GetAnd(char** s);
int GetNot(char** s);
void SkipSpaces(char** s);
void SyntaxError();

int main() {
    FILE* fp = fopen("text.txt", "r");
    if (!fp) {
        printf("Text file opening error.");
        return -1;
    }

	int varCnt = 0;
    char* reads = (char*) calloc(maxLen + 1, sizeof(char));
    if (!reads) {
        printf("Memory allocation error.");
        return -2;
    }

    fgets(reads, maxLen, fp);
    fclose(fp);

    char* s = reads;
    SkipSpaces(&s);

    int result = GetOr(&s);
    printf("Result: %d\n", result);

    free(reads);
    return 0;
}

int GetN(const char* name) {
    for (int i = 0; i < varCnt; i++) {
        if (strcmp(vars[i].name, name) == 0)
            return vars[i].value;
    }
    printf("Enter value for %s (typically 0 or 1): ", name);
    int val;
    scanf("%d", &val);
    vars[varCnt].value = val;
    strcpy(vars[varCnt].name, name);
    varCnt++;
    return val;
}

int GetOr(char** s) {
    int val = GetAnd(s);
    while (strncmp(*s, "OR", 2) == 0) {
        *s += 2;
        int val2 = GetAnd(s);
        val = val || val2;
    }
    return val;
}

int GetAnd(char** s) {
    int val = GetNot(s);
    SkipSpaces(s);
    while (strncmp(*s, "AND", 3) == 0) {
        *s += 3;
        int val2 = GetNot(s);
        val = val && val2;
    }
    return val;
}

int GetNot(char** s) {
    SkipSpaces(s);
    if (strncmp(*s, "NOT", 3) == 0) {
        *s += 3;
        return !GetNot(s);
    }
    
    if (**s == '(') {
        (*s)++;
        int val = GetOr(s);
        if (**s != ')') 
			SyntaxError();
        (*s)++;
        return val;
    }
    
    char varName[nameLen];
    int i = 0;
    while (isalpha(**s) && (i < (nameLen - 1))) {
        varName[i++] = **s;
        (*s)++;
    }
    varName[i] = '\0';

    if (i == 0) 
		SyntaxError();
    return GetN(varName);
}

void SyntaxError() {
    printf("Syntax Error\n");
    exit(1);
}
