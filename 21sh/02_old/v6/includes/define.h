/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:19:55 by curquiza          #+#    #+#             */
/*   Updated: 2017/07/29 17:28:36 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
** execution
*/

# define CMD_FAILURE 1
# define CMD_SUCCESS 0

/*
** termcaps
*/

# define TC_SIZE 2048
# define DEF_TERM "xterm-256color"
# define PROMPT_DEF_SIZE 7

/*
** signals
*/

# define SIG_ON 1
# define SIG_OFF 0

/*
** historic
*/

# define HISTO_SIZE 50
# define HISTO_S_PROMPT "histo_search> "
# define HISTO_ERR_MSG "No match found"
# define HISTO_OK_MSG "Match found"

/*
** completion
*/

# define COMP_SIZE 100
# define COMP_MSG "Too many possibilities"
# define COMP_PROMPT "compl> "

#endif
