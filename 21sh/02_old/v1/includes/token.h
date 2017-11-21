/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:43:22 by curquiza          #+#    #+#             */
/*   Updated: 2017/04/29 22:21:27 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

enum	e_token
{
	WORD = 0, // par défaut
	CTRL_OP = 1, // operateur de controle : ;, ;;, |, ||, &, && ...
	RED_OP = 2, // operateur de redirection : <, >, <<, >>, <&, >&, <<- ...
	IO_NBR = 3, // nbr avant les red_op
	NAME = 4, // '_' 'a-z' 'A-Z' et '0-9' (1rst char : not a '0-9') // non géré
	ASS_WORD = 5, // non géré
	NEWLINE = 6 // \n
};

enum	e_op
{
	SEMIC = 1, // ;
	DSEMIC = 11, // ;;
	PIPE = 2, // |
	DPIPE = 22, // ||
	AND = 3, // &
	DAND = 33, // &&
	LESS = 4, // <
	DLESS = 44, // <<
	GREAT = 5, // >
	DGREAT = 55, // >>
	LESSAND = 6, // <& 
	GREATAND = 7, // >&
	LESSGREAT = 8, // <>
	DLESSDASH = 9, // <<-
	CLOBBER = 10 // >|
};

#endif
