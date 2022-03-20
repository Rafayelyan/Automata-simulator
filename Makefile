SOURCES		= automata.cpp source.cpp
OBJS		= ${SOURCES:.cpp=.o}
CC			= g++
RM			= rm -f
FLAGS		= -Wall -Wextra -Werror

%.o : %.cpp
	${CC} ${FLAGS} -c $< -o ${<:.cpp=.o}

all : ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o automata

debug	:	FLAGS += -D DEBUG
debug	:	re

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} automata

re : fclean all

.PHONY: all clean fclean bonus re .c.o