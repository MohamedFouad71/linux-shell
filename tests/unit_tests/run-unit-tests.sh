#!/usr/bin/env bash

################## vars ##################
UNIT_TEST_SCRIPTS_PATH="$(git rev-parse --show-toplevel)/tests/unit_tests/unit_test_scripts"
YELLOW="\033[1;33m"
GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

################## build ##################
# temp directory for testing
mkdir -p "$TEMP_TEST_DIR"
cd "$TEMP_TEST_DIR"

# build the project
echo -e "${YELLOW}Building the project${RESET}"
make

# check if build was successful
if [ $? -eq 0 ]; then
    echo -e "${GREEN}Success: project built successfully!${RESET}"
else
    echo -e "${RED}Error: Build failed!${RESET}"
    exit 1
fi

################## tests ##################
echo "Granting permissons"
chmod +x $UNIT_TEST_SCRIPTS_PATH/*.sh

echo -e "${YELLOW}Running unit tests${RESET}"
for test in $UNIT_TEST_SCRIPTS_PATH/*.sh; do
    echo -e "${YELLOW}Running test $test${RESET}"
    bash "$test"
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Success: $test passed!${RESET}"
    else
        echo -e "${RED}Error: $test failed!${RESET}"
        exit 1
    fi
done

echo -e "${GREEN}All tests passed with success!${RESET}"