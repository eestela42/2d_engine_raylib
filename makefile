NAME = BOMBERMAN

CC = gcc

CFLAGS = 

SRC = main.c \
tools.c


SRCS            =  $(addprefix srcs/, $(SRC))

OBJS            = $(addprefix objs/, $(SRC:.c=.o))
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 $(CFLAGS) -o $(NAME)

objs/%.o: srcs/%.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

po: all clean

re: fclean all

.PHONY: all re clean fcleanNAME = PONG