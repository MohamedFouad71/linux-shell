#!/bin/bash

######### Variables ##########
PROJECT_PATH="$(git rev-parse --show-toplevel)"
SHELL_EXEC_PATH="$PROJECT_PATH/shell"
COMMANDS_FILE_PATH="$PROJECT_PATH/tests/valgrind/commands-for-valgrind.txt"

# Colors
YELLOW="\033[1;33m"
GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

######### Build the project ##########
echo -e "${YELLOW}Building the project${RESET}"
make
echo -e "${GREEN}Success: project built successfully!${RESET}"

######### Check if required files exist ##########
if [ ! -f "$SHELL_EXEC_PATH" ]; then
    echo -e "${RED}Error: hit executable not found!${RESET}"
    exit 1
fi

if [ ! -f "$COMMANDS_FILE_PATH" ]; then
    echo -e "${RED}Error: commands file not found!${RESET}"
    exit 1
fi

# count commands in $COMMANDS_FILE_PATH
command_count=$(wc -l < "$COMMANDS_FILE_PATH")

######### Run valgrind on all commands in $COMMANDS_FILE_PATH ##########
# For cross-platform development
echo -e "${YELLOW}Removing \\\r from commands-for-valgrind.txt${RESET}"    
sed -i 's/\r$//' "$COMMANDS_FILE_PATH"

echo -e "${YELLOW}Running valgrind on all commands in $COMMANDS_FILE_PATH${RESET}"

run_count=0
while IFS= read -r command || [ -n "$command" ]; do

    echo -e "${YELLOW}Testing command $command${RESET}"
    echo "$command" | valgrind --error-exitcode=99 --leak-check=full --errors-for-leak-kinds=definite "$SHELL_EXEC_PATH"
    run_count=$((run_count + 1))

    if [ $? -eq 99 ]; then
        echo -e "${RED}Error: $command has memory leaks!${RESET}"
        echo -e "${RED}$run_count out of $command_count commands have been run!${RESET}"
        exit 1
    fi

    echo -e "${GREEN}Success: $command has no memory leaks!${RESET}"
done < "$COMMANDS_FILE_PATH"

######### Cleanup ##########

######### Success ##########
echo -e "${GREEN}All commands have no memory leaks!${RESET}"
echo -e "${GREEN}$run_count out of $command_count commands have been run!${RESET}"