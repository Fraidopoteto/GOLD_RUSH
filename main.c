/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun < joschmun@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:05:54 by joschmun          #+#    #+#             */
/*   Updated: 2024/11/05 14:05:54 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_gold_drain(t_game *game)
{
	game->highscore = (game->highscore - 25);
	game->step_counter++;
	game->gold_rush--;
	printf("GOLD DRAIN: %i\n", game->gold_rush);
	if (game->gold_rush == 0)
	{
		printf("\n=====================\n");
		printf("AIN'T NO GOLD AROUND,\nSO YER SIX FEET DOWN!");
		printf("\n=====================\n");
		exit (0);
	}
}


int init_window_and_map(t_game *game, char *map_filename)
{
	int fd = open(map_filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Fehler: Öffnen der Map-Datei");
		return (1);
	}
	game->map = ft_read_map(fd, &game->max_y, &game->max_x);
	close(fd);
	if (!game->map)
	{
		perror("Fehler: Laden der Map fehlgeschlagen");
		return (1);
	}
	return (0);
}
int create_window(t_game *game)
{
	int screen_size_y = game->max_y * 32;
	int screen_size_x = game->max_x * 32;
	game->win = mlx_new_window(game->mlx, screen_size_x, screen_size_y, "COWBOYS REVENGE");
	if (!game->win)
	{
		perror("Fehler: Erstellen des Fensters fehlgeschlagen");
		return (1);
	}
	return (0);
}
void find_positions_Y(t_game *game)
{
	int x;
	int y;
	int found;

	x = 0;
	y = 0;
	found = 0;
	while (y < game->max_y)
	{
		x = 0;
		while (x < game->max_x)
		{
			if (game->map[y][x] == 'Y')
			{
				game->enemy_v_x = x;
				game->enemy_v_y = y;
				found = 1;
				break;
			}
			x++;
		}
		if (found)
			break;
		y++;
	}
}
void find_positions_X(t_game *game)
{
	int x;
	int y;
	int found;

	x = 0;
	y = 0;
	found = 0;
	while (y < game->max_y)
	{
		x = 0;
		while (x < game->max_x)
		{
			if (game->map[y][x] == 'X')
			{
				game->enemy_h_x = x;
				game->enemy_h_y = y;
				found = 1;
				break;
			}
			x++;
		}
		if (found)
			break;
		y++;
	}
}


void find_positions(t_game *game)
{
	int x;
	int y;
	int found;

	x = 0;
	y = 0;
	found = 0;
	while (y < game->max_y)
	{
		x = 0;
		while (x < game->max_x)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				found = 1;
				break;
			}
			x++;
		}
		if (found)
			break;
		y++;
	}
}

void count_coins(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	game->count_coins = 0;
	while (y < game->max_y)
	{
		x = 0;
		while (x < game->max_x)
		{
			if (game->map[y][x] == 'C')
				game->count_coins++;
			x++;
		}
		y++;
	}
	game->found_coins = game->count_coins;
}
void init_game(t_game *game)
{
	game->found_coins = 0;
	game->count_coins = 0;
	game->max_y = 0;
	game->max_x = 0;
	game->player_y = 0;
	game->player_x = 0;
	game->enemy_h_x = 0;
	game->enemy_h_y = 0;
	game->enemy_v_x = 0;
	game->enemy_v_y = 0;
	game->direction_v = 1;
	game->direction_h = 1;
	game->enemy_h_dead = 0;
	game->enemy_v_dead = 0;
	game->highscore = 0;
	game->coins_highscore = 0;
	game->kill_highscore = 0;
	game->step_counter = 0;
	game->gold_rush = 10;
}

int start_game(t_game *game)
{
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}

void ft_title_screen(void)
{
	printf("    ▗▄▄▖ ▗▄▖ ▗▖   ▗▄▄▄ \n");
	printf("   ▐▌   ▐▌ ▐▌▐▌   ▐▌  █ \n");
	printf("   ▐▌▝▜▌▐▌ ▐▌▐▌   ▐▌  █ \n");
	printf("   ▝▚▄▞▘▝▚▄▞▘▐▙▄▄▖▐▙▄▄▀ \n");
	printf("   ▗▄▄▖ ▗▖ ▗▖ ▗▄▄▖▗▖ ▗▖ \n");
	printf("   ▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌ \n");
	printf("   ▐▛▀▚▖▐▌ ▐▌ ▝▀▚▖▐▛▀▜▌ \n");
	printf("   ▐▌ ▐▌▝▚▄▞▘▗▄▄▞▘▐▌ ▐▌ \n");
	printf("   =====================\n");
	printf("    ===================\n\n\n\n\n");
	printf("!PRESS ARROW KEYS TO MOVE!\n\n\n\n");
	printf("\nPINK_COWBOY: *Sigh...* This rusty old\n\
	     knife won't get me anywhere...\n\
	     unless I sneak up behind 'em!\n\n");
}
int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	t_game game;
	ft_title_screen();
	init_game(&game);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	if (init_window_and_map(&game, argv[argc - 1]))
		return (1);
	if (create_window(&game))
		return (1);
	find_positions(&game);
	find_positions_Y(&game);
	find_positions_X(&game);
	count_coins(&game);
	load_game_assets(&game);
	// ft_copy_map(game.max_y, game.max_x, game.map);
	start_game(&game);
	free(game.map);
	free(game.mlx);
	return (0);
}
