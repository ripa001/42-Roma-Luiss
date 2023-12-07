# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 19:39:26 by mmarinel          #+#    #+#              #
#    Updated: 2023/11/25 21:39:47 by mmarinel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#! we will modifie the headers with the name of the team...

SHELL=/bin/bash

# DOCKER RULES
all: 	up
re: 	fclean all
reset: 	kill all

up:
	@printf $(BOLDCYAN)"Makefile: Building containers\n"$(RESET)
	@docker-compose up --build


down:
	@printf $(BOLDCYAN)"Makefile: Stopping containers\n"$(RESET)
	docker-compose down

clean: down
	@printf $(BOLDCYAN)"Makefile: Cleaning unused objects\n"$(RESET)
	@docker container prune -f

fclean: clean
	@printf $(BOLDCYAN)"Makefile: Cleaning images\n"$(RESET)
	@for image_id in $$(docker images -q); do \
		docker rmi $$image_id; \
	done;
	@docker image prune -f

kill: fclean
	@printf $(BOLDCYAN)"Makefile: Cleaning volumes\n"$(RESET)
	@for volume_name in $$(docker volume ls -q); do \
		docker volume rm $$volume_name; \
	done;
	docker system prune -a -f

# reset:
# rm -rf 'frontend-vue-vite/node_modules'
# rm -rf 'backend-nest/node_modules'
# $(MAKE) -C backend-nest/prisma/make re

env_local:
	@printf $(BOLDCYAN)"Makefile: Setting-up env files for a local build\n"$(RESET)
	./env/docker_env local
	@printf $(BOLDCYAN)"\n"$(RESET)

env_docker:
	@printf $(BOLDCYAN)"Makefile: Setting-up env files for a docker build\n"$(RESET)
	./env/docker_env docker
	@printf $(BOLDCYAN)"\n"$(RESET)

local: env_local up

docker: env_docker up

start: env connect 

# GIT RULES
connect:
	@printf $(BOLDCYAN)"Makefile: Connecting team git repositories\n"$(RESET)
	./git_connect_repo.sh

commit : 
	@printf $(BOLDCYAN)"Makefile: Committing changes : \n"$(RESET)
	./git_commit.sh

# Colors
RESET					:= "\033[0m"
BLACK					:= "\033[30m"
RED						:= "\033[31m"
GREEN					:= "\033[32m"
YELLOW					:= "\033[33m"
BLUE					:= "\033[34m"
MAGENTA					:= "\033[35m"
CYAN					:= "\033[36m"
WHITE					:= "\033[37m"
BOLDBLACK				:= "\033[1m\033[30m"
BOLDRED					:= "\033[1m\033[31m"
BOLDGREEN				:= "\033[1m\033[32m"
BOLDYELLOW				:= "\033[1m\033[33m"
BOLDBLUE				:= "\033[1m\033[34m"
BOLDMAGENTA				:= "\033[1m\033[35m"
BOLDCYAN				:= "\033[1m\033[36m"
BOLDWHITE				:= "\033[1m\033[37m"

.PHONY: all clean fclean re up down kill reset git_init start env connect commit 