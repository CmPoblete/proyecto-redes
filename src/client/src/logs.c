#include <logs.h>

#define MESG_SIZE 512

FILE *LOGGER = NULL;

int DEBUGGER = 0;
int INFO = 1;
int WARNING = 1;
int ERROR = 1;
int CRITIC = 1;

char *get_time_str(char *buf)
{
    struct timeval tmnow;
    struct tm *tm;
    char usec_buf[6];
    gettimeofday(&tmnow, NULL);
    tm = localtime(&tmnow.tv_sec);
    strftime(buf, 30, "%Y/%m/%d-%H:%M:%S", tm);
    strcat(buf, ".");
    sprintf(usec_buf, "%d", (int)tmnow.tv_usec);
    strcat(buf, usec_buf);
    return buf;
}

void setup_logger(char *fp, int op)
{
    if (op)
    {
        LOGGER = fopen(fp, "a+"); // En caso de que también queramos leer
    }
    else
    {
        LOGGER = NULL;
    }
}

void logg(char *msg)
{
    if (LOGGER)
    {
        char buf[30];
        fprintf(LOGGER, "\n[ CLIENT:: %s ]%s\n", get_time_str(buf), msg);
    }
}

char *MESAGE_NAMES(int NAME_SIZE)
{
    switch (NAME_SIZE)
    {
    case 1:
        return "Start Connection";

    case 2:
        return "Connection Established";

    case 3:
        return "Ask Nickname";
    case 4:
        return "Return Nickname";
    case 5:
        return "Opponent Found";
    case 6:
        return "Send IDs";
    case 7:
        return "Start Game";
    case 8:
        return "Scores";
    case 9:
        return "Send Cards";
    case 10:
        return "Send Word";
    case 11:
        return "Response Word";
    case 12:
        return "Round Winner/Loser";
    case 13:
        return "End Game"; // Tu Tuuu TuTuuuuuu Tuuuuuuuuuuuuuuuu Tuuuuuuuuuuuuuuuuuu Tuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu
    case 14:
        return "Game Winner/Loser";
    case 15:
        return "Ask New Game";
    case 16:
        return "Answer New Game";
    case 17:
        return "Disconnect";
    case 20:
        return "Error Bad Package";
    case 64:
        return "Image";
    default:
        return "Not Defined";
    }
}

void debuger(char *msg)
{
    if (DEBUGGER)
    {
        char message[MESG_SIZE];
        sprintf(message, "|[ __DEBUG__ ]|>> %s <<|", msg);
        logg(message);
    }
}

void infolog(char *msg)
{
    if (INFO)
    {
        char message[MESG_SIZE];
        sprintf(message, "|[ __INFO__ ]|>> %s <<|", msg);
        logg(message);
    }
} // Nivel de los loggs solicitados

void warning(char *msg)
{
    if (WARNING)
    {
        char message[MESG_SIZE];
        sprintf(message, "|[ __WARNING__ ]|>> %s <<|", msg);
        logg(message);
    }
}

void error(char *msg)
{
    if (ERROR)
    {
        char message[MESG_SIZE];
        sprintf(message, "|[ __ERROR__ ]|>> %s <<|", msg);
        logg(message);
    }
}

void critical(char *msg)
{
    if (CRITIC)
    {
        char message[MESG_SIZE];
        sprintf(message, "|[ __CRITICAL__ ]|>> %s <<|", msg);
        logg(message);
    }
}

void close_logger(int op)
{
    if (op)
        fclose(LOGGER);
}
