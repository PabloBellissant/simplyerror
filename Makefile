NAME = simplyerror.a

SRCDIR = src
OBJDIR = .obj
INCDIR = include

SRCS = get_instance.c \
	   print_error_graph.c \
	   register_error.c


OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

CFLAGS = -Werror -Wextra -Wall -MD -MP -I $(INCDIR) -g3
AR = ar -rcs
DEPFLAGS = -MMD -MP

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
