# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 12:30:07 by rduro-pe          #+#    #+#              #
#    Updated: 2025/06/22 16:29:07 by rduro-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -->┊( NAMES )┊.´-★☆★
NAME	=	libft.a

# -->┊( COMMANDS AND FLAGS )┊.´-★☆★
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g

# -->┊( DIRECTORIES )┊.´-★☆★
OBJ_DIR	=	obj


# -->┊( SOURCES AND OBJS )┊.´-★☆★
SRC_GET		=	$(addprefix ft_get/, get_next_line.c get_next_line_utils.c)

SRC_IS		=	$(addprefix ft_is/, ft_isalnum.c ft_isalpha.c ft_isascii.c \
				ft_isdigit.c ft_isprint.c ft_iswhitespace.c)

SRC_LST		=	$(addprefix ft_lst/, ft_lstadd_back.c ft_lstadd_front.c \
				ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
				ft_lstmap.c ft_lstnew.c ft_lstsize.c)
				
SRC_MATRIX	=	$(addprefix ft_matrix/, free_matrix_until.c free_matrix.c \
				ft_matrixlen.c ft_split.c matrix_add_front.c \
				matrix_add_to_index.c matrix_dup_char.c)

SRC_NUM		=	$(addprefix ft_num/, ft_atoi.c ft_itoa.c int_check.c \
				long_check.c)

SRC_PRINT	=	$(addprefix ft_print/, conversions.c conversions_fd.c \
				ft_printf.c printf_fd.c ft_putchar_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_putstr_fd.c)

SRC_STR		=	$(addprefix ft_str/, ft_strchr.c ft_strcmp.c ft_strdup.c \
				ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
				ft_strmapi.c ft_strncmp.c ft_strndup.c ft_strnstr.c ft_strrchr.c \
				ft_strtrim.c ft_substr.c)

SRC_UTILS	=	$(addprefix ft_utils/, ft_bzero.c ft_calloc.c ft_memchr.c \
				ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
				ft_tolower.c ft_toupper.c)

SRCS		=	$(SRC_GET) $(SRC_IS) $(SRC_MATRIX) $(SRC_NUM) \
				$(SRC_PRINT) $(SRC_STR) $(SRC_UTILS)

OBJS		=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
OBJS_LST	=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRC_LST:.c=.o)))


# -->┊( RULES )┊.´-★☆★
all: $(NAME)

$(NAME): $(OBJS)
	$(M_COMOBJS)
	$(M_ARC)
	@ar rcs $(NAME) $(OBJS)
	
$(OBJ_DIR)/%.o: ft_get/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: ft_is/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: ft_lst/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: ft_matrix/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: ft_num/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: ft_print/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: ft_str/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: ft_utils/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

bonus: $(OBJS) $(OBJS_LST)
	$(M_COMOBJS)
	$(M_COMBONUS)
	$(M_ARCBONUS)
	@ar rcs $(NAME) $(OBJS) $(OBJS_LST) 

clean:
	$(M_REMOBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	$(M_REM)
	@rm -rf $(NAME)

re:	fclean all
	@echo "Re-Done!!"

.PHONY: all clean fclean re bonus


# -->┊( COSMETICS )┊.´-★☆★

# -‵,┊ normal colors
DEF	=	\e[0;39m
GRY	=	\e[0;30m
BLU	=	\e[0;34m
GRN	=	\e[0;32m
YEL =	\e[0;33m

# -‵,┊ bold colors
BYEL	=	\e[1;33m

# -‵,┊ background colors
YELB	=	\e[43m

# -‵,┊ messages
M_COMOBJS	= @echo "$(GRY)-->┊$(GRN)  Compiling: $(BYEL)$(NAME)/objs $(GRY)$(DEF)"
M_COMBONUS	= @echo "$(GRY)-->┊$(GRN)  Compiling: $(BYEL)$(NAME) bonus objs $(GRY)$(DEF)"
M_ARC		= @echo "$(GRY)-->┊$(YEL)  Archiving: $(DEF)$(YELB) $(NAME) $(GRY)$(DEF)"
M_ARCBONUS	= @echo "$(GRY)-->┊$(YEL)  Archiving: $(DEF)$(YELB) $(NAME) bonus $(GRY)$(DEF)"
M_REMOBJS	= @echo "$(GRY)-->┊$(BLU)  Removing: $(BYEL) $(NAME)/objs $(GRY)$(DEF)"
M_REM		= @echo "$(GRY)-->┊$(BLU)  Removing: $(DEF)$(YELB) $(NAME) $(GRY)$(DEF)"