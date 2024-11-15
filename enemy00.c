/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Furaido <Furaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 06:00:54 by Furaido           #+#    #+#             */
/*   Updated: 2024/11/15 11:11:07 by Furaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void can_move_horizontalX(t_game *game)
{
	if (game->direction_h > 0)
	{
		if (game->map[game->enemy_h_y][game->enemy_h_x + 1] == '1' ||\
			game->map[game->enemy_h_y][game->enemy_h_x + 1] == 'E' ||\
			game->map[game->enemy_h_y][game->enemy_h_x + 1] == 'C' ||\
			game->map[game->enemy_h_y][game->enemy_h_x + 1] == 'Y')
			game->direction_h *= -1;
		if (check_player_collisionX(game))
			exit(0);
	}
	else
	{
		if (game->map[game->enemy_h_y][game->enemy_h_x - 1] == '1' ||\
			game->map[game->enemy_h_y][game->enemy_h_x - 1] == 'E' ||\
			game->map[game->enemy_h_y][game->enemy_h_x - 1] == 'C' ||\
			game->map[game->enemy_h_y][game->enemy_h_x - 1] == 'Y')
			game->direction_h *= -1;
		if (check_player_collisionX(game))
			exit(0);
	}
}

int check_player_collisionX(t_game *game)
{
	if (game->direction_h > 0)
	{
		if (game->map[game->enemy_h_y][(game->enemy_h_x + game->direction_h) - 1] == 'P')
		{
			printf("\nBLUE_COWBOY: HAND OVER THE GOLD,\n	     YA VARMINT! *BANG*\n\n");
			printf("\n==========\nYOUR DEAD.\n==========\n\n");
			return (1);
		}
	}
	else
	{
		if (game->map[game->enemy_h_y][(game->enemy_h_x + game->direction_h) - 1] == 'P' ||
			game->map[game->enemy_h_y][game->enemy_h_x + game->direction_h] == 'P')
		{
			printf("\nBLUE_COWBOY: Y'AIN'T GOIN' NOWHERE!\n	     *BANG*\n\n");
			printf("\n==========\nYOUR DEAD.\n==========\n\n");
			return (1);
		}
	}
	if (game->enemy_h_y == game->player_y && game->enemy_h_x == game->player_x )
		{
			printf("\nBLUE_COWBOY: HAND OVER THE GOLD,\n	     YA VARMINT! *BANG*\n\n");
			printf("\n==========\nYOUR DEAD.\n==========\n\n");
			return (1);
		}
	return (0);
}

void update_enemy_positionX(t_game *game)
{
	game->map[game->enemy_h_y][game->enemy_h_x] = '0';
	game->map[game->enemy_h_y][(game->enemy_h_x + game->direction_h)] = 'X';
	game->enemy_h_x = (game->enemy_h_x + game->direction_h);
}
int move_enemy_X(t_game *game)
{
if (game->enemy_h_dead > 0)
	return (0);
can_move_horizontalX(game);
update_enemy_positionX(game);
return (1);
}
