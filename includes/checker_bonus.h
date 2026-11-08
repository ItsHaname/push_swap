/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haait-ba <haait-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 12:00:00 by haait-ba          #+#    #+#             */
/*   Updated: 2026/11/08 12:00:00 by haait-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "push_swap.h"

int	read_line(char *buf);
int	apply_swap_push(t_ctx *ctx, char *op);
int	apply_rotate(t_ctx *ctx, char *op);
int	apply_op(t_ctx *ctx, char *op);

#endif
