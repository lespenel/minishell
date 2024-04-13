SRC = \
	  builtins/exec_builtins.c \
	  builtins/get_argc.c \
	  builtins/is_builtin.c \
	  builtins/ms_cd/ms_cd.c \
	  builtins/ms_cd/get_wd.c \
	  builtins/ms_cd/get_curpath.c \
	  builtins/ms_cd/compare_cdpath.c \
	  builtins/ms_cd/get_canonical_path.c \
	  builtins/ms_cd/remove_dot_dot.c \
	  builtins/ms_cd/get_dir_operand.c \
	  builtins/ms_cd/check_path_size.c \
	  builtins/ms_cd/change_directory.c \
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
	  env/ms_unsetenv.c \
	  env/print_env.c \
	  \
	  execution/stds/save_stds.c \
	  execution/stds/restore_stds.c \
	  \
	  execution/pipeline/execute_pipeline.c \
	  execution/pipeline/execute_pipe_cmd.c \
	  \
	  execution/exec_cmd.c \
	  execution/execute_commands.c \
	  execution/execute_commands_interactive.c \
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
	  expansions/parameters/add_word_tab.c \
	  expansions/parameters/expand_parameters.c \
	  expansions/parameters/expand_nq.c \
	  expansions/parameters/expand_substring.c \
	  expansions/parameters/fill_nq_var.c \
	  expansions/parameters/ft_strtok_ifs.c \
	  expansions/parameters/get_parameter_str.c \
	  expansions/parameters/treat_noquote.c \
	  \
	  expansions/quote_removal/quote_removal.c \
	  \
	  expansions/tilde/tilde_expansion.c \
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
	  parser/get_here_doc.c \
	  parser/syntax_error.c \
	  parser/fill_here_doc.c \
	  \
	  prompt/add_color_to_prompt.c \
	  prompt/add_pwd.c \
	  prompt/get_command_result.c \
	  prompt/get_git_branch.c \
	  prompt/get_prompt.c \
	  \
	  signals/setup_signals_child.c \
	  signals/setup_signals_execution.c \
	  signals/setup_signals_interactive.c \
 	  \
	  termios/get_tty_fd.c \
	  termios/restore_termios.c \
	  termios/setup_termios.c \
	  \
	  util/clear_string_vector.c \
	  util/dup_and_close.c \
	  util/get_ifs.c \
	  util/ms_fork.c \
	  util/ms_strchr.c \
	  util/next_char.c \
	  util/ft_split_vector.c \
	  util/set_exitcode_str.c \
	  \
	  wildcard/pattern/fill_pattern.c \
	  wildcard/pattern/create_pattern.c \
	  wildcard/pattern/create_glob_pattern.c \
	  wildcard/pattern/create_file_pattern.c \
	  wildcard/pattern/create_dir_pattern.c \
	  wildcard/pattern/remove_backslash.c \
	  wildcard/add_file_tok.c \
	  wildcard/add_backslash.c \
	  wildcard/get_dir_path.c \
	  wildcard/compare_globignore.c \
	  wildcard/compare_pattern.c \
	  wildcard/expand_wildcards.c \
	  wildcard/get_file_ls.c \
	  wildcard/get_dir_ls.c \
	  wildcard/get_matching_dirname.c \
	  wildcard/get_matching_filenames.c \
	  wildcard/is_wildcard_match.c \
	  wildcard/ms_strcmp.c \
	  wildcard/sort_filenames.c \
	  wildcard/wildcard_handling.c \
	  \
	  destroy_minishell.c \
	  main.c \
	  parse_input.c \
