#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include <windows.h>

extern short int debug;

void mlog(char* template, ...)
{
    va_list args;
    unsigned int counter = 0;
    unsigned int end;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);

    end = strlen(template);

    va_start(args, template);

    while(counter < end) {
        if(template[counter] == '%') {
            counter++;
            if(template[counter] == '%') {
                putchar('%');
            } else if(template[counter] == 'i') {
                printf("%i", va_arg(args, int));
            } else if(template[counter] == 'u') {
                printf("%u", va_arg(args, unsigned int));
            } else if(template[counter] == 'c') {
                printf("%c", va_arg(args, unsigned int));
            } else if(template[counter] == 'f') {
                printf("%f", va_arg(args, double));
            } else if(template[counter] == 's') {
                printf("%s", va_arg(args, char*));
            } else if(template[counter] == 'd') {
                printf("%d", va_arg(args, int));
            } else if(template[counter] == 'x') {
                printf("%x", va_arg(args, int));
            } else if(template[counter] == 'X') {
                printf("%X", va_arg(args, int));
            } else if(template[counter] == 'p') {
                printf("%p", va_arg(args, void*));
            }
        } else {
            putchar(template[counter]);
        }

        counter++;
    }

    va_end(args);

    putchar('\n');

    return;
}

void mwarn(char* template, ...)
{
    va_list args;
    unsigned int counter = 0;
    unsigned int end;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);

    end = strlen(template);

    va_start(args, template);

    while(counter < end) {
        if(template[counter] == '%') {
            counter++;
            if(template[counter] == '%') {
                putchar('%');
            } else if(template[counter] == 'i') {
                printf("%i", va_arg(args, int));
            } else if(template[counter] == 'u') {
                printf("%u", va_arg(args, unsigned int));
            } else if(template[counter] == 'c') {
                printf("%c", va_arg(args, unsigned int));
            } else if(template[counter] == 'f') {
                printf("%f", va_arg(args, double));
            } else if(template[counter] == 's') {
                printf("%s", va_arg(args, char*));
            } else if(template[counter] == 'd') {
                printf("%d", va_arg(args, int));
            } else if(template[counter] == 'x') {
                printf("%x", va_arg(args, int));
            } else if(template[counter] == 'X') {
                printf("%X", va_arg(args, int));
            } else if(template[counter] == 'p') {
                printf("%p", va_arg(args, void*));
            }
        } else {
            putchar(template[counter]);
        }

        counter++;
    }

    va_end(args);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
    putchar('\n');

    return;
}

void merror(char* template, ...)
{
    va_list args;
    unsigned int counter = 0;
    unsigned int end;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_RED|FOREGROUND_INTENSITY);

    end = strlen(template);

    va_start(args, template);

    while(counter < end) {
        if(template[counter] == '%') {
            counter++;
            if(template[counter] == '%') {
                putchar('%');
            } else if(template[counter] == 'i') {
                printf("%i", va_arg(args, int));
            } else if(template[counter] == 'u') {
                printf("%u", va_arg(args, unsigned int));
            } else if(template[counter] == 'c') {
                printf("%c", va_arg(args, unsigned int));
            } else if(template[counter] == 'f') {
                printf("%f", va_arg(args, double));
            } else if(template[counter] == 's') {
                printf("%s", va_arg(args, char*));
            } else if(template[counter] == 'd') {
                printf("%d", va_arg(args, int));
            } else if(template[counter] == 'x') {
                printf("%x", va_arg(args, int));
            } else if(template[counter] == 'X') {
                printf("%X", va_arg(args, int));
            } else if(template[counter] == 'p') {
                printf("%p", va_arg(args, void*));
            }
        } else {
            putchar(template[counter]);
        }

        counter++;
    }

    va_end(args);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
    putchar('\n');

    return;
}

void mdebug(char* template, ...)
{
    if(debug == 1) {
        va_list args;
        unsigned int counter = 0;
        unsigned int end;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_GREEN|FOREGROUND_INTENSITY);

        end = strlen(template);

        va_start(args, template);

        while(counter < end) {
            if(template[counter] == '%') {
                counter++;
                if(template[counter] == '%') {
                    putchar('%');
                } else if(template[counter] == 'i') {
                    printf("%i", va_arg(args, int));
                } else if(template[counter] == 'u') {
                    printf("%u", va_arg(args, unsigned int));
                } else if(template[counter] == 'c') {
                    printf("%c", va_arg(args, unsigned int));
                } else if(template[counter] == 'f') {
                    printf("%f", va_arg(args, double));
                } else if(template[counter] == 's') {
                    printf("%s", va_arg(args, char*));
                } else if(template[counter] == 'd') {
                    printf("%d", va_arg(args, int));
                } else if(template[counter] == 'x') {
                    printf("%x", va_arg(args, int));
                } else if(template[counter] == 'X') {
                    printf("%X", va_arg(args, int));
                } else if(template[counter] == 'p') {
                    printf("%p", va_arg(args, void*));
                }
            } else {
                putchar(template[counter]);
            }

            counter++;
        }

        va_end(args);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
        putchar('\n');
    }
    return;
}
