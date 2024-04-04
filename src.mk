SRC = \
	  builtins/clear_args.c \
	  builtins/exec_builtins.c \
	  builtins/exec_test.c \
	  builtins/get_argc.c \
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
	  env/get_envp.c \
	  env/init_env.c \
	  env/ms_getenv.c \
	  env/ms_getnenv.c \
	  env/ms_setenv.c \
	  env/print_env.c \
	  \
	  execution/stds/save_stds.c \
	  execution/stds/restore_stds.c \
	  \
	  execution/execute_commands.c \
	  execution/execute_pipeline.c \
	  execution/execute_simple_command.c \
	  execution/execute_subshell.c \
	  execution/execution_structure.c \
	  execution/get_path.c \
	  execution/next_token.c \
	  execution/perform_redirections.c \
	  execution/run_builtin.c \
	  execution/run_command.c \
	  execution/simplify_tokens.c \
	  execution/wait_children.c \
	  \
	  expansions/parameters/expand_substring.c \
	  expansions/parameters/expand_parameters.c \
	  expansions/parameters/treat_noquote.c \
	  \
	  expansions/quote_removal/quote_removal.c \
	  \
	  expansions/tilde/tilde_expansion.c \
	  \
	  expansions/word_split/word_split.c \
	  \
	  expansions/perform_expansions.c \
	  \
	  lexer/init_lexer.c \
	  lexer/fill_lexer.c \
	  lexer/print_lexer.c \
	  lexer/clear_lexer.c \
	  lexer/clear_lexer_except.c \
	  lexer/clear_token.c \
	  lexer/add_newline_tok.c \
	  lexer/char_filter/is_blank.c \
	  lexer/char_filter/is_operand.c \
	  lexer/char_filter/is_word.c \
	  lexer/char_filter/is_quote.c \
	  lexer/char_filter/to_next_quote.c \
	  \
	  parser/validate_input.c \
	  \
	  signals/setup_signals_child.c \
	  signals/setup_signals_interactive.c \
 	  \
	  util/get_ifs.c \
	  util/next_char.c \
	  \
	  wildcard/expand_wildcards.c \
	  wildcard/fill_pattern.c \
	  wildcard/get_matching_filenames.c \
	  wildcard/is_wildcard_match.c \
	  wildcard/sort_filenames.c \
	  \
	  destroy_minishell.c \
	  main.c \
	  parse_input.c \
