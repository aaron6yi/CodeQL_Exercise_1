#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

// Escape special characters in the file path to prevent command injection
void escapeShellArg(char* dest, const char* src) {
    while (*src) {
        if (*src == '\'' || *src == '"' || *src == '\\') {
            *dest++ = '\\';  // Escape the special character
        }
        *dest++ = *src++;
    }
    *dest = '\0';
}

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) { 
        fprintf(stderr, "Please provide the address of a file as an input.\n");
        return -1;
    }

    // Prepare the command and escape the file path
    char cmd[BUFSIZE] = "wc";
    char escapedFile[BUFSIZE];
    
    // Escape the user input to prevent injection
    escapeShellArg(escapedFile, argv[1]);
    
    // Set up the command arguments
    char* cmdArgs[] = {cmd, "-c", escapedFile, NULL};
    
    // Use execvp to execute the command securely
    if (execvp(cmd, cmdArgs) == -1) {
        perror("Error executing command");
        return -1;
    }

    return 0;
}
