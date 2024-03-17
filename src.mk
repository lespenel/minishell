SRC = \
	  builtins/clear_args.c \
	  builtins/exec_builtins.c \
	  builtins/exec_test.c \
	  builtins/get_args.c \
	  builtins/is_builtin.c \
	  builtins/ms_cd.c \
	  builtins/ms_echo.c \
	  builtins/ms_env.c \
	  builtins/ms_exit.c \
	  builtins/ms_export.c \
	  builtins/ms_pwd.c \
	  builtins/ms_unset.c \
	  \
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
	  lexer/add_newline_tok.c \
	  lexer/char_filter/is_blank.c \
	  lexer/char_filter/is_operand.c \
	  lexer/char_filter/is_word.c \
	  lexer/char_filter/is_quote.c \
	  lexer/char_filter/to_next_quote.c \
	  \
	  parser/validate_input.c \
	  \
	  wildcard/expand_wildcards.c \
	  wildcard/fill_pattern.c \
	  wildcard/get_matching_filenames.c \
	  wildcard/is_wildcard_match.c \
	  wildcard/sort_filenames.c \
	  \
	  main.c \
	  parse_input.c \
