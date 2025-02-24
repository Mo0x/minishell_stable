/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:42:18 by mgovinda          #+#    #+#             */
/*   Updated: 2024/06/15 17:14:29 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "typedefs.h"

int		b_pwd(t_hash *envp, int fd);
/*CD*/
int		b_cd_init(t_hash *envp, char *path);
int		is_absolute_path(const char *path);
char	*do_the_symlink(const char *path, t_hash *envp);
int		chdir_routine(char *path);
int		count_the_simple_path(char **tmp_path);
char	**do_the_simple_path(char *path);
int		do_the_path_thing(char *path, t_hash *envp);
int		do_the_doubledots_thing(t_hash *envp);
void	revert_back(t_hash *envp, char **oldpwds);
int		b_cd(t_hash *envp, char *path);
char	*is_root(char *path);
/*EXPORT*/

int		b_export_init(t_hash *envp, char **param, int fdo);
int		b_export(t_hash *envp, char *key, char *value);
int		ft_split_export(char *param, char **key, char **value, int *sum);
int		ft_check_key_export(char *key);
char	*backslasher(char *str);
int		ft_print_export(t_hash *envp, int fdo);

int		b_unset(t_hash *envp, char **param);
int		b_exit(t_asttree *node, t_hash *envp);
int		b_echo(char **str, int fd);
int		b_env(t_hash *envp, int fdo);
int		is_valid_var(char *s);
int		is_valid_variable_char(char c);

#endif
