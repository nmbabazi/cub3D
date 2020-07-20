
MLX = -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

NAME = cub3D

SRCS = 	main.c \
		ft_ray.c\
		ft_player.c \
		utiles.c \
		ft_texture.c \
		ft_walls.c	\
		ft_sprite.c \
		ft_save.c \
		parsing/ft_parsingscene.c \
		parsing/utils.c \
		parsing/gnl.c \

OBJSRCS = $(SRCS:.c=.o) 

$(NAME) : $(OBJSRCS)
	@echo "\033[33m[Remove last version...]"
	@rm -rf Cub3D
	@echo "\033[33m[Cub3D compilation...]"
	@echo "\033[33m[Libft compilation...]"
	$(MAKE) -C ./libft
	@gcc -o $(NAME) -I include.h $(OBJSRCS) $(MLX) ./libft/libft.a -Wall -Wextra -Werror -g
	@echo "\033[33m[Done !]"

all : $(NAME)

clean :
	rm -rf $(OBJSRCS)
	$(MAKE) clean -C ./libft

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)
	rm -rf cub3d.bmp

re : fclean all