#ifndef RECDESC_H
#define RECDESC_H

void SyntaxError();

#define Require(ch) \
if (**s == ch) *s += 1; \
else SyntaxError();

int FileGet(char* reads, FILE *fp);

int GetE(char** s);

int GetN(char** s);

int GetP(char** s);

int GetT(char** s);

int GetG(char* str);
#endif