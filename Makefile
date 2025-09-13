# ========= Config =========
LIBFT_PATH := include/libft
CC         := cc
CFLAGS     := -Wall -Wextra -Werror -I include
LIBFT_LIB  := $(LIBFT_PATH)/libft.a

# pick which test to build: make T=parser (defaults ot minishell)
# or you can make run-parser
T ?= minishell
UC_T := $(shell echo $(T) | tr '[:lower:]' '[:upper:]')


# ***********			1.	UPDATE SRCES 		 ********************
# *******************************************************************

# ========= Sources per target =========
# add more SRC DIRECTORIES etc.)
SRC_MINISHELL 	:= src/main/main.c
SRC_PARSER    	:= src/parser/parser_test.c
SRC_LEXER	 	:= src/lexer/lexer_test.c src/lexer/scan_operator.c src/lexer/scan_word.c src/lexer/tokenize.c
SRC_BUILT_INS	:= src/built_ins/built_ins_test.c
# SRC_EXPANDER 	:= src/expander/expander_test.c src/expander/expansion_len.c src/expander/expansion_utils_1.c \
				src/expander/var_utils.c src/expander/expansion_fill.c
# SRC_SPLIT		:= src/split_field/split_field_test.c src/split_field/split_and_splice.c src/split_field/split_utils.c


# common sources (if any) go here, e.g. tokenizer, utils, …
SRC_COMMON := src/lexer/scan_operator.c src/lexer/scan_word.c src/lexer/tokenize.c \
			src/expander/expansion_len.c src/expander/expansion_utils_1.c \
			src/expander/var_utils.c src/expander/expansion_fill.c \
			src/split_field/split_and_splice.c src/split_field/split_utils.c \
			src/main/shell_loop.c src/main/signals.c

# ========= Resolve chosen set =========
SELECTED_SRC := $(SRC_$(UC_T)) $(SRC_COMMON)

#error if T doesn't match any SRC_*
ifeq ($(strip $(SELECTED_SRC)),)
$(error Unknown T='$(T)'. Valid options: minishell parser input built_ins)
endif

# ========= Output/layout =========
OBJDIR := obj
BINDIR := bin
NAME   := $(T)                    # binary name follows selected word
OBJ    := $(SELECTED_SRC:src/%.c=$(OBJDIR)/%.o)

# ========= Main targets =========
all: $(BINDIR)/$(NAME)

$(BINDIR)/$(NAME): $(OBJ) $(LIBFT_LIB) | $(BINDIR)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_PATH) -lft -lreadline -o $@
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

VG_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1
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

.PHONY: all minishell parser built_ins lexer run valgrind debug clean expander split fclean re san
minishell parser built_ins lexer expander split:
	@$(MAKE) T=$@ $(BINDIR)/$@
