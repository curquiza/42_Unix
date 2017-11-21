/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 16:42:46 by curquiza          #+#    #+#             */
/*   Updated: 2017/06/30 16:55:00 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TC_H
# define TC_H

#include "libft.h"
#include <term.h>
#include <sys/ioctl.h>

# define TC_SIZE 2048

typedef struct		s_tc
{
	char	buff[TC_SIZE];
	int		nbr_char;
	int		prompt_len;
	int		x_max;
	int		y_max;
	int		curs_x;
	int		curs_y;
}					t_tc;

#endif
