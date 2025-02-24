/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:42:45 by achatzit          #+#    #+#             */
/*   Updated: 2024/06/07 15:53:41 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define DOLLAR 2
# define LESS 3
# define GREAT 4
# define DLESS 5
# define DGREAT 6
# define PIPE 7
# define INTER 8
# define OPENP 9
# define CLOSEP 10
# define AND 11
# define OR 12
# define WILD 13
# define VOIDT 14

# define FAILURE 0
# define SUCCESS 1

# define ERR_UNCLOSED_QUOTE 17

# define DQUOTE 34
# define SQUOTE 39
# define CRITICAL_INFO_LST_EMPTY 666

# define SIG_DEFAULT 0
# define SIG_IGNORE 1
# define SIG_CUSTOM 2
# define SIG_LISTEN 3

# define DFLAGS 268435460 // (SA_RESTART | SA_SIGINFO) but norm

// Regular text
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

// Regular bold text
# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m"

# define CRESET "\e[0m"

#endif
