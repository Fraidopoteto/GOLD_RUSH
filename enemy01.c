/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Furaido <Furaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 06:32:59 by Furaido           #+#    #+#             */
/*   Updated: 2024/11/15 12:40:03 by Furaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void can_move_verticalY(t_game *game)
{
	if (game->direction_v > 0)
	{
		if (game->map[game->enemy_v_y + 1][game->enemy_v_x] == '1' ||\
			game->map[game->enemy_v_y + 1][game->enemy_v_x] == 'E' ||\
			game->map[game->enemy_v_y + 1][game->enemy_v_x] == 'C' ||\
			game->map[game->enemy_v_y + 1][game->enemy_v_x] == 'X')
			game->direction_v *= -1;
		if (check_player_collisionY(game))
			exit(0);
	}
	else
	{
		if (game->map[game->enemy_v_y- 1][game->enemy_v_x] == '1' ||\
			game->map[game->enemy_v_y- 1][game->enemy_v_x] == 'E' ||\
			game->map[game->enemy_v_y- 1][game->enemy_v_x] == 'C' ||\
			game->map[game->enemy_v_y- 1][game->enemy_v_x] == 'X')
			game->direction_v *= -1;
		if (check_player_collisionY(game))
			exit(0);
	}
}

int check_player_collisionY(t_game *game)
{
	if (game->direction_v > 0)
	{
		if (game->map[game->enemy_v_y + 1][game->enemy_v_x] == 'P' ||
			game->map[game->enemy_v_y + game->direction_v][game->enemy_v_x] == 'P')
		{
			printf("\nBLUE_COWBOY: HAND OVER THE GOLD,\n	     YA VARMINT! *BANG*\n\n");
			printf("\n==========\nYOUR DEAD.\n==========\n\n");
			return (1);
		}
	}
	else
	{
		if (game->map[game->enemy_v_y - 1][game->enemy_v_x] == 'P' ||
			game->map[game->enemy_v_y + game->direction_v][game->enemy_v_x] == 'P')
		{
			printf("\nBLUE_COWBOY: Y'AIN'T GOIN' NOWHERE!\n	     *BANG*\n\n");
			printf("\n==========\nYOUR DEAD.\n==========\n\n");
			return (1);
		}
	}
	if (game->enemy_v_y == game->player_y && game->enemy_v_x == game->player_x )
		{
			printf("\nBLUE_COWBOY: HAND OVER THE GOLD,\n	     YA VARMINT! *BANG*\n\n");
			printf("\n==========\nYOUR DEAD.\n==========\n\n");
			return (1);
		}
	return (0);
}


void update_enemy_positionY(t_game *game)
{
	game->map[game->enemy_v_y][game->enemy_v_x] = '0';
	game->map[(game->enemy_v_y + game->direction_v)][game->enemy_v_x] = 'Y';
	game->enemy_v_y = (game->enemy_v_y + game->direction_v);
}

int move_enemy_Y(t_game *game)
{
	if (game->enemy_v_dead > 0)
		return (0);
	can_move_verticalY(game);
	update_enemy_positionY(game);
	return (1);
}
