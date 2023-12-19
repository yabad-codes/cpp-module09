SRC = $(wildcard *.cpp)

OBJ = $(SRC:.cpp=.o)

NAME = PmergeMe

CC = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJ) $(wildcard *.hpp)
	$(CC) $(CXXFLAGS) $(OBJ) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re