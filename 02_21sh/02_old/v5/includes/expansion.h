/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 11:26:55 by curquiza          #+#    #+#             */
/*   Updated: 2017/05/27 23:57:53 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "struct.h"

/*
** expansion.c
*/

void	ft_expansion(t_ast *ast);

/*
** exp_parameter.c
*/

void	ft_replace_parameter(char **s, int *i, int len, t_shell *shell);
void	ft_parameter_expansion(char **s, t_shell *shell);

/*
** exp_removal_quote.c
*/

void	ft_escape_char(char **s, int i, char esc_char);
void	ft_rm_quote(char **s, int start, int i);
void	ft_apply_dquote(char **s, int *i);
void	ft_apply_squote(char **s, int *i);
void	ft_quote_removal(char **s);

#endif
