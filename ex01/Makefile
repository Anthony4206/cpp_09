NAME 			= RPN

SRC				= main.cpp RPN.cpp

OBJ 			= ${SRC:.cpp=.o}
			
CC 				= c++

CFLAGS 			= -Wall -Wextra -Werror -std=c++98

RM 				= rm -rf

GREEN			:= "\033[0;32m"
CYAN			:= "\033[0;36m"
RESET			:= "\033[0m"

%.o:			%.cpp
				@${CC} ${CFLAGS} -o $@ -c $<

all: 			${NAME}

${NAME}:		${OBJ}
				@${CC} ${CFLAGS} -o ${NAME} ${OBJ}
				@echo ${GREEN}"Compiled '${NAME}' with success" ${RESET}

clean:
				@${RM} ${OBJ}
				@echo ${CYAN}"Cleaned '${NAME}' objects with success"${RESET}
				
fclean:			clean
				@${RM} ${NAME}
				@echo ${CYAN}"Removed '${NAME}' with success"${RESET}

re:				fclean all

.PHONY: 		all clean fclean re