NAME = pathfinder

CC = clang
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

SRCDIR = src
INCDIR = inc
OBJDIR = obj
LIBDIR = libmx
LIBINCDIR = $(LIBDIR)/inc

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

LIBMXMAKEFILE = $(LIBDIR)/Makefile

all: $(NAME)

$(NAME): $(OBJFILES)
	@$(MAKE) -C $(LIBDIR)
	$(CC) $(OBJFILES) -o $(NAME) -Llibmx -lmx

$(OBJDIR)/%.o: $(SRCDIR)/%.c  | $(OBJDIR)
	$(CC) $(FLAGS) -I $(INCDIR) -I $(LIBINCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

uninstall:
	rm -rf $(OBJDIR) $(NAME)
	@$(MAKE) uninstall -C $(LIBDIR)

clean:
	rm -rf $(OBJDIR)
	@$(MAKE) clean -C $(LIBDIR)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
