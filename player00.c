/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Furaido <Furaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 05:38:06 by Furaido           #+#    #+#             */
/*   Updated: 2024/11/15 11:33:33 by Furaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int key_hook(int keycode, t_game *game)
{
	int moved = 0;

	if (keycode == 65362)
		moved = move_player(game, game->player_x, (game->player_y - 1));
	else if (keycode == 65364)
		moved = move_player(game, game->player_x, (game->player_y + 1));
	else if (keycode == 65361)
		moved = move_player(game, (game->player_x - 1), game->player_y);
	else if (keycode == 65363)
		moved = move_player(game, (game->player_x + 1), game->player_y);
	else if (keycode == 65307)
		exit(0);
	if (moved)
	{
		ft_gold_drain(game);
		render_map(game);
	}
	return (0);
}

int check_end_game(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'E' && game->found_coins == 0)
	{
		if (game->enemy_h_dead == 0 && game->enemy_v_dead == 0)
		{
			printf("\nPINK_COWBOY: *Tch...* I didn't even\n\
	     need this damn rusty thing\n\
	     to get through!\n\n");
			printf("\nGOOD JOB! c:\n\n");
		}
		else
		{
			printf("\nPINK_COWBOY: *Pew...* that was close...\n\n");
			printf("\nTOO BAD... :c\n\n");
		}
		printf("COINS: %i   +%i\n", game->count_coins, (game->count_coins * 500));
		printf("STEPS: %i  %i\n", game->step_counter, (game->step_counter * -25));
		printf("KILLS: %i   %i\n", (game->enemy_h_dead + game->enemy_v_dead), ((game->enemy_h_dead + game->enemy_v_dead) * -250));
		printf("=========\nHIGHSCORE: %i\n=========\n\n", game->highscore);
		exit(0);
	}
	return (1);
}
int is_blocked(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == '1' || game->map[new_y][new_x] == 'E')
		return (1);
	if ((game->map[game->player_y][(game->player_x - 1)] == 'X') && ((game->player_x - 1) != new_x))
		return (1);
	if ((game->map[(game->player_y + 1)][game->player_x] == 'Y') && ((game->player_y + 1) != new_y))
		return (1);
	return (0);
}
void check_enemy_collisions(t_game *game, int new_x, int new_y)
{
	if ((game->map[new_y][new_x] == 'X' && game->player_y == game->enemy_h_y) ||\
		(game->map[new_y][new_x - 1] == 'X'))
	{
		printf("\n\nCOWBOYS DEAD X");
		printf("\nBLUE_COWBOY: *Oof...*\n\n");
		printf("\nCOWBOY KILLED  -250\n\n");
		game->highscore -= 250;
		game->enemy_h_dead++;
	}
	if (game->map[new_y + 1][new_x] == 'Y')
	{
		printf("\nBLUE_COWBOY: *Arrg!*\n\n");
		printf("\nCOWBOY KILLED  -250\n\n");
		game->highscore -= 250;
		game->enemy_v_dead++;
	}
}
void collect_coin(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->gold_rush = 10;
		game->map[new_y][new_x] = '0';
		game->found_coins--;
		game->highscore += 500;
		printf("\nCOIN COLLECTED +500\n\n");
	}
}
void move_player_update(t_game *game, int new_x, int new_y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
}
void move_enemies(t_game *game)
{
	if (game->enemy_h_dead == 0)
		move_enemy_X(game);
	if (game->enemy_v_dead == 0)
		move_enemy_Y(game);
}
int move_player(t_game *game, int new_x, int new_y)
{
	if (!check_end_game(game, new_x, new_y))
		return (0);
	if (is_blocked(game, new_x, new_y))
		return (0);
	check_enemy_collisions(game, new_x, new_y);
	collect_coin(game, new_x, new_y);
	move_player_update(game, new_x, new_y);
	move_enemies(game);
	return (1);
}
