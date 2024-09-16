LIBFT			=	utils/libft/libft.a

PRINTF			=	utils/ft_printf/libftprintf.a

SRCS			=	./srcs/main.c ./srcs/utils.c ./srcs/utils2.c ./srcs/pipex.c \

SRCS_BONUS		=	./srcs_bonus/main_bonus.c ./srcs_bonus/utils_bonus.c ./srcs_bonus/utils2_bonus.c ./srcs_bonus/pipex_bonus.c ./srcs_bonus/here_doc.c\

OBJS			= $(SRCS:.c=.o)
OBJS_BONUS		= $(SRCS_BONUS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -g3 -Wall -Wextra -Werror

NAME			= pipex
NAME_BONUS 		= pipex_bonus

all:			$(NAME)

$(NAME):		$(OBJS)
					@make -C utils/libft
					@make -C utils/ft_printf
					cc $(OBJS) -o $(NAME)-L. ${LIBFT} ${PRINTF} -o $(NAME)

bonus : ${OBJS_BONUS}
						@make bonus -C utils/libft
						@make -C utils/ft_printf
						$(CC) $(OBJS_BONUS) $(LIBFT) $(PRINTF) -o $(NAME_BONUS)
	

clean:
					make clean -C utils/libft/
					make clean -C utils/ft_printf/
						$(RM) $(OBJS)
					@rm -rf ${OBJS_BONUS} 

fclean:			clean
					make fclean -C utils/libft/
					make fclean -C utils/ft_printf/
						$(RM) $(NAME)
					@rm -rf ${NAME_BONUS}

re:						fclean all

.PHONY:			all clean fclean re
