FT= ft_containers

STD = std_containers

CC = clang++

CLFAGS = -Wall -Wextra -Werror -std=c++98

SRC = .cpp

all: $(STD) $(FT)
$(STD):
	$(CC) $(CLFAGS) -o $(STD)  main.cpp

$(FT):
	$(CC) -DFT $(CLFAGS) -o $(FT)  main.cpp

clean:
	rm -rf $(FT) $(STD) diff

fclean: clean

re: fclean all