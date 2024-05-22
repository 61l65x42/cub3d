/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:14:59 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/22 08:46:28 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg2rad(double deg)
{
	return (deg * (M_PI / 180.0));
}

// pythagorean theorem
double	get_hypotenuse(double a, double b)
{
	return (sqrt(pow(a, 2) + pow(b, 2)));
}
