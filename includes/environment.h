/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:43:58 by mgovinda          #+#    #+#             */
/*   Updated: 2024/05/24 21:44:00 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "typedefs.h"

void	set_env(t_msh *msh, char **envp);
char	*get_envp_key(char *envp);
char	*get_envp_value(char *envp);
void	set_default_values_to_critical_vars_if_not_set(t_hash **envp);
char	**env_conv(t_hash *vars);

#endif
