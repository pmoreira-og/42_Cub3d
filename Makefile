# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 12:30:07 by rduro-pe          #+#    #+#              #
#    Updated: 2025/07/28 11:58:26 by pmoreira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -->┊( NAMES )┊.´-★☆★
NAME	=	cub3D
LIBFT	=	./include/libft/libft.a
MLX		=	./include/minilibx_linux/libmlx.a

# -->┊( COMMANDS AND FLAGS )┊.´-★☆★
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
MLXFLAGS	=	-L ./include/minilibx_linux -lmlx_Linux -lX11 -lXext
VAL			=	valgrind --leak-check=full --show-leak-kinds=all \
				--track-origins=yes --track-fds=yes -s

# -->┊( DIRECTORIES )┊.´-★☆★
DIR_SRC		=	src
DIR_OBJ		=	build

DIR_EXEC		= exec
DIR_PARSE		= parse
DIR_UTILS		= utils


# -->┊( SOURCE AND OBJS )┊.´-★☆★
SRC_MAIN	=	main.c

SRC_MAIN_EXTRA	= main_parse.c

SRC_EXEC	=	aux.c dda.c

SRC_PARSE	=

SRC_UTILS	= aux.c constructors.c hooks.c cleaners.c printers.c

SRCS	=	$(addprefix $(DIR_SRC)/, $(SRC_MAIN)) \
			$(addprefix $(DIR_SRC)/, $(addprefix $(DIR_EXEC)/, $(SRC_EXEC))) \
			$(addprefix $(DIR_SRC)/, $(addprefix $(DIR_PARSE)/, $(SRC_PARSE))) \
			$(addprefix $(DIR_SRC)/, $(addprefix $(DIR_UTILS)/, $(SRC_UTILS)))

SRCS_EXTRA = $(addprefix $(DIR_SRC)/, $(SRC_MAIN_EXTRA)) \
			$(addprefix $(DIR_SRC)/, $(addprefix $(DIR_EXEC)/, $(SRC_EXEC))) \
			$(addprefix $(DIR_SRC)/, $(addprefix $(DIR_PARSE)/, $(SRC_PARSE))) \
			$(addprefix $(DIR_SRC)/, $(addprefix $(DIR_UTILS)/, $(SRC_UTILS)))

OBJS	=	$(addprefix $(DIR_OBJ)/, $(SRCS:$(DIR_SRC)/%.c=%.o))

OBJS_EXTRA	=	$(addprefix $(DIR_OBJ)/, $(SRCS_EXTRA:$(DIR_SRC)/%.c=%.o))


# -->┊( COMPILATION RULES )┊.´-★☆★
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(M_COMOBJS)
	$(M_COM)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c #| $(DIR_OBJ)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(LIBFT):
	@make -C ./include/libft -s

$(MLX):
	$(M_COMMLXOBJS)
	@make -C ./include/minilibx_linux -s
	$(M_ARCMLX)

extra: $(OBJS_EXTRA) $(LIBFT) $(MLX)
	$(M_COMP_P)
	@$(CC) $(CFLAGS) $(OBJS_EXTRA) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	$(M_DONE)
	./$(NAME)

# -->┊( EXECUTION RULES )┊.´-★☆★
exe: all
	./$(NAME)

val: all
	$(VAL) ./$(NAME)

# -->┊( STANDARD RULES )┊.´-★☆★
clean:
	@make clean -C ./include/libft -s
	@make clean -C ./include/minilibx_linux -s
	$(M_REMOBJS)
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -rf $(LIBFT)
	$(M_REM)
	@rm -rf $(NAME)

re:	fclean all
	$(M_RE)

.PHONY: all clean fclean re exe val extra


# -->┊( COSMETICS )┊.´-★☆★

#-‵,┊ normal colors
DEF	=	\e[0;39m
BLK	=	\e[0;30m
BLU	=	\e[0;34m
MAG =	\e[0;35m
GRN	=	\e[0;32m

#-‵,┊ bold colors
BCYN	=	\e[1;36m
BBLU	=	\e[1;34m

#-‵,┊ background colors
CYNB	=	\e[46m
YELB	=	\e[43m
BLUB	=	\e[44m

#-‵,┊ messages
M_COMOBJS	= @echo "$(BLK)-->┊$(GRN)  Compiling: $(BBLU)$(NAME)/objs $(BLK)$(DEF)"
M_COM		= @echo "$(BLK)-->┊$(GRN)  Compiling: $(DEF)$(BLUB) $(NAME) $(BLK)$(DEF)\n"
M_REMOBJS	= @echo "$(BLK)-->┊$(BLU)  Removing: $(BBLU) $(NAME)/objs $(BLK)$(DEF)"
M_REM		= @echo "$(BLK)-->┊$(BLU)  Removing:  $(DEF)$(BLUB) $(NAME) $(BLK)$(DEF)\n"
M_RE		= @echo "$(BLK)... $(BLU)  Re Done   $(DEF)$(BCYN) ($(NAME) is ready !!)$(DEF)"
M_COMMLXOBJS	= @echo "$(GRY)-->┊$(GRN)  Compiling: $(BHMAG) libmlx.a/objs $(GRY)$(DEF)"
M_ARCMLX		= @echo "$(GRY)-->┊$(YEL)  Archiving: $(DEF)$(MAGHB) libmlx.a $(GRY)$(DEF)"
M_REMMLX		= @echo "$(GRY)-->┊$(BLU)  Removing: $(DEF)$(MAGHB) libmlx.a $(GRY)$(DEF)"
M_REMMLXOBJS	= @echo "$(GRY)-->┊$(BLU)  Removing: $(BHMAG) libmlx.a/objs $(GRY)$(DEF)"