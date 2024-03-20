SRC = \
	  env/destroy_env.c \
	  env/init_env.c \
	  env/ms_getenv.c \
	  env/ms_getnenv.c \
	  env/ms_setenv.c \
	  env/print_env.c \
	  \
	  expander/add_escaping.c \
	  expander/expand_substring.c \
	  expander/expand_tokens.c \
	  expander/next_char.c \
	  expander/treat_noquote.c \
	  \
	  lexer/init_lexer.c \
	  lexer/fill_lexer.c \
	  lexer/print_lexer.c \
	  lexer/clear_lexer.c \
	  lexer/add_newline_tok.c \
	  lexer/char_filter/is_blank.c \
	  lexer/char_filter/is_operand.c \
	  lexer/char_filter/is_word.c \
	  lexer/char_filter/is_quote.c \
	  lexer/char_filter/to_next_quote.c \
	  \
	  parser/validate_input.c \
	  \
	  quote_removal/quote_removal.c \
	  \
	  wildcard/expand_wildcards.c \
	  wildcard/fill_pattern.c \
	  wildcard/get_matching_filenames.c \
	  wildcard/is_wildcard_match.c \
	  wildcard/sort_filenames.c \
	  \
	  main.c \
	  parse_input.c \
