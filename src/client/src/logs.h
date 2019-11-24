#pragma once
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define MESG_SIZE 512

extern FILE *LOGGER;
extern int DEBUGGER;
extern int INFO;
extern int WARNING;
extern int ERROR;
extern int CRITIC;

char *MESAGE_NAMES(int NAME_SIZE);
void setup_logger(char *fp, int op);
void debuger(char *msg);
void infolog(char *msg); // Nivel de los logs solicitados
void warning(char *msg);
void error(char *msg);
void critical(char *msg);
void close_logger();
