#include "screen.h"
#include "keyboard.h"
#include "string.h"
#include "syscall.h"

void start_shell() {
    clear_screen();
    print_string("Minimaru OS Shell\n");
    print_string("Type 'help' for commands\n");

    char cmd[128];
    while (1) {
        print_string("> ");
        get_line(cmd, sizeof(cmd));
        // Trim whitespace, newlines, and carriage returns
        int len = strlen(cmd);
        int i;
        for (i = len - 1; i >= 0 && (cmd[i] == ' ' || cmd[i] == '\n' || cmd[i] == '\r'); i--) {
            cmd[i] = 0;
            len--;
        }
        /* Commented out debug logging
        // print_string("Debug: Raw command buffer: [");
        // print_string(cmd);
        // print_string("]\n");
        // print_string("Debug: Trimmed command buffer: [");
        // print_string(cmd);
        // print_string("]\n");
        // print_string("Debug: Command length: ");
        // print_hex(len);
        // print_string("\n");
        */
        if (len == 0) {
            // print_string("Debug: Empty command, skipping\n");
            continue; // Skip empty commands
        }
        if (strcmp(cmd, "help") == 0) {
            // print_string("Debug: Help command matched\n");
            print_string("Available commands:\n");
            print_string("  help  - Display this help message\n");
            print_string("  clear - Clear the screen\n");
            print_string("  snake - Launch the snake game\n");
            print_string("  echo  - Print a message (e.g., echo hello)\n");
            print_string("  mem   - Display memory information\n");
            print_string("  ps    - List running processes\n");
            print_string("  halt  - Shut down the system\n");
        } else if (strcmp(cmd, "clear") == 0) {
            // print_string("Debug: Clear command matched\n");
            clear_screen();
        } else if (strcmp(cmd, "snake") == 0) {
            // print_string("Debug: Snake command matched\n");
            asm volatile("int $0x80" : : "a"(1));
        } else if (strncmp(cmd, "echo ", 5) == 0) {
            // print_string("Debug: Echo command matched\n");
            asm volatile("int $0x80" : : "a"(0), "b"(cmd + 5));
        } else if (strcmp(cmd, "mem") == 0) {
            // print_string("Debug: Mem command matched\n");
            asm volatile("int $0x80" : : "a"(2));
        } else if (strcmp(cmd, "ps") == 0) {
            // print_string("Debug: Ps command matched\n");
            asm volatile("int $0x80" : : "a"(3));
        } else if (strcmp(cmd, "halt") == 0) {
            // print_string("Debug: Halt command matched\n");
            asm volatile("int $0x80" : : "a"(4));
        } else {
            print_string("Unknown command: ");
            print_string(cmd);
            print_string("\n");
        }
    }
}