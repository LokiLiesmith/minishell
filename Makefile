# ========= Detect OS and set Readline flags =========
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)     # macOS
	READLINE_PATH := /usr/local/opt/readline
	CFLAGS       += -I$(READLINE_PATH)/include
	LDFLAGS      += -L$(READLINE_PATH)/lib -lreadline -lncurses
else                         # assume Linux
	CFLAGS       += $(shell pkg-config --cflags readline 2>/dev/null || echo "")
	LDFLAGS      += $(shell pkg-config --libs readline 2>/dev/null || echo "-lreadline -lncurses")
endif


# ========= Config =========
LIBFT_PATH := include/libft
CC         := cc
CFLAGS     := -Wall -Wextra -Werror -I include ## -g -fsanitize=address
LIBFT_LIB  := $(LIBFT_PATH)/libft.a

# pick which test to build: make T=parser (defaults ot minishell)
# or you can make run-parser
T ?= minishell
UC_T := $(shell echo $(T) | tr '[:lower:]' '[:upper:]')


# ***********			1.	UPDATE SRCES 		 ********************
# *******************************************************************

# ========= Sources per target =========
# add more SRC DIRECTORIES etc.)
SRC_MINISHELL := src/main/main.c
SRC_PARSER    := src/parser/parser_test.c
SRC_LEXER	  := src/lexer/lexer_test.c
# SRC_BUILT_INS := src/built_ins/built_ins_test.c src/built_ins/cd.c src/built_ins/echo.c \
# 		src/built_ins/env.c src/built_ins/export.c src/built_ins/pwd.c src/built_ins/unset.c
# SRC_EXECUTION := src/execution/execution_test.c \
# 		src/execution/exec_children.c src/execution/exec_redirection.c src/execution/exec_pipe.c \
# 		src/execution/execution.c \
# 		src/execution/utils_path.c src/execution/utils.c


# common sources (if any) go here, e.g. tokenizer, utils, …
# SRC_COMMON := src/lexer/scan_operator.c src/lexer/scan_word.c src/lexer/tokenize.c \
# 			src/expander/expansion_len.c src/expander/expansion_utils_1.c \
# 			src/expander/var_utils.c src/expander/expansion_fill.c \
# 			src/split_field/split_and_splice.c src/split_field/split_utils.c \
# 			src/main/shell_loop.c src/main/signals.c \
# 			src/parser/parse.c src/parser/parse_redirections.c \
# 			src/main/print_pipeline.c

SRC_COMMON := src/lexer/scan_operator.c src/lexer/scan_word.c src/lexer/tokenize.c \
			src/expander/expansion_len.c src/expander/expansion_utils_1.c \
			src/expander/var_utils.c src/expander/expansion_fill.c \
			src/split_field/split_and_splice.c src/split_field/split_utils.c \
			src/main/shell_loop.c src/main/signals.c src/main/main_utils.c src/main/garbage_collector/gc_more_utils.c \
			src/main/garbage_collector/gc.c src/main/garbage_collector/gc_utils.c\
			src/parser/parse.c src/parser/parse_redirections.c \
			src/main/print_pipeline.c \
			src/execution/exec_children.c src/execution/redirection.c src/execution/exec_pipe.c \
			src/execution/execution.c src/execution/exec_builtins.c \
			src/execution/utils_path.c src/execution/utils.c src/execution/utils_exec.c src/execution/utils_redirection.c \
			src/built_ins/cd.c src/built_ins/echo.c \
			src/built_ins/env.c src/built_ins/export.c src/built_ins/pwd.c src/built_ins/unset.c src/built_ins/exit.c \
			src/heredoc/prep_heredoc.c src/heredoc/expand_heredoc.c \

# ========= Resolve chosen set =========
SELECTED_SRC := $(SRC_$(UC_T)) $(SRC_COMMON)

#error if T doesn't match any SRC_*
ifeq ($(strip $(SELECTED_SRC)),)
$(error Unknown T='$(T)'. Valid options: minishell parser input built_ins execution)
endif

# ========= Output/layout =========
OBJDIR := obj
BINDIR := bin
NAME   := $(T)                    # binary name follows selected word
OBJ    := $(SELECTED_SRC:src/%.c=$(OBJDIR)/%.o)

# ========= Main targets =========
all: $(BINDIR)/$(NAME)

# $(BINDIR)/$(NAME): $(OBJ) $(LIBFT_LIB) | $(BINDIR)
# 	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_PATH) -lft -lreadline -o $@
# 	@echo "Built $@"

$(BINDIR)/$(NAME): $(OBJ) $(LIBFT_LIB) | $(BINDIR)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_PATH) -lft $(LDFLAGS) -o $@
	@echo "Built $@"


# ========= Libft =========
$(LIBFT_LIB):
	@$(MAKE) -s -C $(LIBFT_PATH)

# ========= Compile .c → .o =========
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# ========= Dirs =========
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# ========= Run helpers =========
run-%:
	@$(MAKE) T=$* $(BINDIR)/$*
	@$(BINDIR)/$*

VG_FLAGS := valgrind --leak-check=full  --show-leak-kinds=all --track-fds=yes --suppressions=sub.sub
# VG_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1
debug: CFLAGS += -g
debug: clean all

valgrind: debug
	@valgrind $(VG_FLAGS) $(BINDIR)/$(NAME)

# ========= Clean =========
clean:
	-@$(MAKE) -s -C $(LIBFT_PATH) clean
	@rm -rf $(OBJDIR)

fclean: clean
	@$(MAKE) -s -C $(LIBFT_PATH) fclean
	@rm -rf $(BINDIR)

re: fclean all

# ========= Sanitizer (optional) =========
san: CFLAGS += -fsanitize=address -fno-omit-frame-pointer -g
san: clean all


# ***********			2.	UPDATE PHONY 		 ********************
# *******************************************************************

.PHONY: all minishell parser built_ins lexer run valgrind debug clean fclean re san
minishell parser built_ins lexer:
	@$(MAKE) T=$@ $(BINDIR)/$@
