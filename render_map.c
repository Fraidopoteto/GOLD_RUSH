/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Furaido <Furaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 06:48:00 by Furaido           #+#    #+#             */
/*   Updated: 2024/11/15 07:55:04 by Furaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


t_textures load_textures(void *mlx)
{
	t_textures textures;
	int img_width, img_height;

	textures.wall = mlx_xpm_file_to_image(mlx, "kaktus04.xpm", &img_width, &img_height);
	textures.player = mlx_xpm_file_to_image(mlx, "cowboy_knife00.xpm", &img_width, &img_height);
	textures.floor = mlx_xpm_file_to_image(mlx, "floor00.xpm", &img_width, &img_height);
	textures.exit = mlx_xpm_file_to_image(mlx, "chest02.xpm", &img_width, &img_height);
	textures.coin = mlx_xpm_file_to_image(mlx, "coin02.xpm", &img_width, &img_height);
	textures.enemy_y = mlx_xpm_file_to_image(mlx, "cowboy_Y00.xpm", &img_width, &img_height);
	textures.enemy_x = mlx_xpm_file_to_image(mlx, "cowboy_X00.xpm", &img_width, &img_height);

	return (textures);
}

void render_cell(t_game *game, int x, int y)
{
    void *img = NULL;
    char cell = game->map[y][x];

    if (cell == '1')
        img = game->textures.wall;
    else if (cell == 'P')
        img = game->textures.player;
    else if (cell == 'C')
        img = game->textures.coin;
    else if (cell == 'E')
        img = game->textures.exit;
    else if (cell == '0')
        img = game->textures.floor;
    else if (cell == 'Y')
        img = game->textures.enemy_y;
    else if (cell == 'X')
        img = game->textures.enemy_x;

    if (img)
        mlx_put_image_to_window(game->mlx, game->win, img, x * 32, y * 32);
    else
        printf("Warning: Null image pointer for map[%d][%d]\n", y, x);
}

void render_row(t_game *game, int y)
{
    for (int x = 0; x < game->max_x; x++)
    {
        render_cell(game, x, y);
    }
}

void render_map(t_game *game)
{
    for (int y = 0; y < game->max_y; y++)
    {
        render_row(game, y);
    }
}
int load_game_assets(t_game *game)
{
    game->textures = load_textures(game->mlx);
    render_map(game);
    return (0);
}
