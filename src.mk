SRC = \
	  env/destroy_env.c \
	  env/init_env.c \
	  env/ms_getenv.c \
	  env/ms_setenv.c \
	  env/print_env.c \
	  \
	  expander/expand_tokens.c \
	  \
	  lexer/init_lexer.c \
	  lexer/fill_lexer.c \
	  lexer/print_lexer.c \
	  lexer/clear_lexer.c \
	  lexer/char_filter/is_blank.c \
	  lexer/char_filter/is_operand.c \
	  lexer/char_filter/is_word.c \
	  lexer/char_filter/is_quote.c \
	  lexer/char_filter/to_next_quote.c \
	  \
	  parser/validate_input.c \
	  \
	  main.c \
