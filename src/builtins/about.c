#include "../../include/shell.h"

void about() {
    const char* blue   = "\033[1;34m";
    const char* green  = "\033[1;32m";
    const char* yellow = "\033[1;33m";
    const char* magenta= "\033[1;35m";
    const char* reset  = "\033[0m";

    printf("%s============================================%s\n", magenta, reset);
    printf("%s✨ Glitchy ✨%s\n", blue, reset);
    printf("%sIntoduced To:%s Eng. Omar Al-Hussiny.\n", green, reset);
    printf("%sDeveloped by:%s Kareem Hany, Muhammed Fouad, Muhammed Ashraf, Muhammed Fatooh, Yehya Hamdy, Ahmed Abdullatif and Somia Khaled.\n", green, reset);
    printf("%s--------------------------------------------%s\n", magenta, reset);
    printf("%s📄 Description:%s\n", yellow, reset);
    printf("Glitchy is a lightweight Linux-like terminal designed for learning\n");
    printf("and experimentation. It provides a fully functional command-line interface\n");
    printf("with support for external commands, built-in commands, and advanced\n");
    printf("features such as piping, I/O redirection, and command history.\n\n");
    printf("%s⚡ Key Features:%s\n", yellow, reset);
    printf("  • Built-in commands: cd, exit, help, history, about, clear, count\n");
    printf("  • Execute external Linux commands via fork() and execvp()\n");
    printf("  • Command piping (|) to chain multiple commands\n");
    printf("  • Input/output redirection using >, >>, and <\n");
    printf("  • Colored prompt showing username@hostname\n");
    printf("  • Persistent command history saved to file\n");
    printf("  • Error handling for invalid commands\n");
    printf("  • Multi-platform compatible (tested on Linux-based systems)\n");
    printf("  • Educational: Understand shell internals and system calls\n\n");
    printf("%s💡 Tips:%s\n", yellow, reset);
    printf("  • Use 'help' to see all available commands.\n");
    printf("  • Commands support standard Linux arguments and options.\n");
    printf("  • Use 'history' to quickly repeat previous commands.\n\n");
    printf("%s🚀 Enjoy exploring your Glitchy!%s\n", green, reset);
    printf("%s============================================%s\n", magenta, reset);
}