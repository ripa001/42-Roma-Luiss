#!/bin/bash

# colors
RESET='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'

printf ${CYAN}"\nThis script handles 'git add' and 'git commit'.\n"${RESET}
printf ${CYAN}"\nIf you need to commit specific files, go ahead and add the files you need before moving forward.\n"${RESET}
printf ${RED}"\nIt doesn't handle push, remember to push when you are done.\n"${RESET}
printf ${CYAN}"\nDo not forget to check if you need to pull from master or merge certain branches before moving forward.\n"${RESET}
printf "\n----------------------------- (Press Enter)"
read USER_INPUT
printf ${CYAN}">> Here is the status of changed files in your project:\n"${RESET}
git status
printf "\n----------------------------- (Press Enter)"
read USER_INPUT
printf ${CYAN}">> Did you already add the files you wish to commit ?\nOr would you like to add all changes now ?\n"${RESET}
printf ${RED}"Add all changes ?\n"${RESET}
printf "('y' to 'git add . ' | 'Enter' to skip this step)\n"
read ADD
if [ "$ADD" == "y" ]; then
    printf "Adding all changes now\n"
    git add .
    printf ${CYAN}"\n\n>> File status before committing:\n"${RESET}
    read USER_INPUT
    git status
else
    printf "No further changes were added\n"
fi
printf "\n----------------------------- (Press Enter)"
read USER_INPUT
printf ${CYAN}">> Now preparing the commit message : \n"${RESET}
printf "\nWhat part of the project are you working on ?\n${CYAN}(App | Game | Chat)\n"${RESET}
read SCOPE
printf "\nWhat did you do ?\n"
read DESCRIPTION
printf "\nWhat is the current status of these changes ?\n${CYAN}(wip | testing | functional)\n"${RESET}
read STATUS
COMMIT_MSG="${SCOPE} : ${DESCRIPTION} -- ${STATUS}"
printf "\n>> Your commit message is : ${CYAN}${COMMIT_MSG}\n"${RESET}
printf ${RED}"\n\n>> Enter 'ok' to go forward and commit changes ...\n"${RESET}
read ok
if [ "$ok" == "ok" ]; then
    git commit -m "${COMMIT_MSG}"
else
    printf ${RED}"DID NOT COMMIT\n"${RESET}
fi
printf "\n----------------------------- (Press Enter)"
read USER_INPUT
printf ${CYAN}"Your changes are now ready to push"${RESET}
printf ${RED}"\n\n>> Remember this script doesn't handle push, you still need to push\n"${RESET}
printf "Don't forget to check if you need to pull, merge, checkout from your branch etc before pushing !\n"
printf "\n\nLast but not least\n"
printf ${RED}">> Do not forget to check that your local repo is connected to all team members' repositories before pushing.\n"${RESET}
printf "You need to set this up each time you are cloning the project from github!\n"
printf ${CYAN}"\nUse 'git remote show origin' to check and 'make connect' to set up the connections\n"${RESET}

