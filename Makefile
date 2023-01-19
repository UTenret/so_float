###########################################################
#### NAME

NAME			= so_long

###########################################################
#### PATH TO SOURCES

PATH_SRCS 		+= srcs/

###########################################################
#### SOURCES

SRCS			+= so_long.c
SRCS			+= args_check.c
SRCS			+= backtracking_check_map.c

vpath %.c $(PATH_SRCS)

###########################################################
#### OBJS

PATH_OBJS		= objs/
OBJS			= $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

###########################################################
#### LIBRARY

LIBFT_PATH 		= libft/
LIBFT 			= $(LIBFT_PATH)/libft.a

###########################################################
#### INCLUDES

INCLUDES 		= -I./includes -I./minilibx-linux -I./$(LIBFT_PATH)/includes
HEADER			= includes/so_long.h
HEADER			+= minilibx-linux/mlx.h
HEADER			+= minilibx-linux/mlx_int.h

###########################################################
#### COMPILATION

CC				= clang
CFLAGS			+= -Wall

ifeq ($(everything),true)
	CFLAGS		+= -Weverything
else
	CFLAGS		+= -Werror
endif

CFLAGS			+= -Wextra
CFLAGS			+= -fPIE


###########################################################
#### RULES

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -L ./minilibx-linux -lmlx -lXext -lX11 $(INCLUDES) -L $(LIBFT_PATH) -lft


$(LIBFT):
	$(MAKE) -sC $(LIBFT_PATH)

$(OBJS): $(PATH_OBJS)/%.o: %.c $(HEADER)
	@mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) 

clean:
	$(RM) -R $(PATH_OBJS)
	$(MAKE) -sC $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -sC $(LIBFT_PATH) fclean

re: fclean
	$(MAKE)

del: fclean
	rm a.out

test: 
	@ $(CC) -o tests/a.out tests/main.c $(NAME) && bash tests/runtests.sh

full_test: fclean all test

norm:
	@norminette $(PATH_SRCS) $(INCLUDES)

.PHONY: all clean fclean re del test full_test

# variables spéciales
# $@ fait référence au nom de la cible
# $< nom première dépendance
# $^ liste dépendance
# $? liste dépendance plus récentes que la cible
# $* nom fichier, sans son extension
# CIBLE > DEPENDANCES > REGLES
