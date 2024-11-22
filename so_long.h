/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:44:22 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/19 14:57:11 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <unistd.h>

# define TILE_SIZE 16
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 800
# define MOVE_SPEED 6
# define MOVE_SPEED_ENEMY 1
# define WALL_TILE 13
# define FLOOR_TILE 20
# define COLECTIBLE_TILE
# define EXIT_TILE 75
# define ANIMATION_SPEED 8
# define KEY_W 13
# define KEY_HAUT 126
# define KEY_S 1
# define KEY_BAS 125
# define KEY_A 0
# define KEY_GAUCHE 123
# define KEY_D 2
# define KEY_DROITE 124
# define KEY_SPACE 49

typedef enum e_game_state
{
	PLAYING,
	GAME_OVER
}					t_game_state;

typedef struct s_queue
{
	int				x;
	int				y;
	struct s_queue	*next;
}					t_queue;

typedef struct s_queue_info
{
	t_queue			*front;
	t_queue			*rear;
}					t_queue_info;

typedef struct s_spdata
{
	void			*frames[4][3];
	int				current_direction;
	int				current_frame;
	int				x;
	int				y;
	int				tile_x;
	int				tile_y;
}					t_spdata;

typedef struct s_enemy
{
	void			*frames[4][3];
	int				current_direction;
	int				current_frame;
	int				x;
	int				y;
	struct s_enemy	*next;
}					t_enemy;

typedef struct s_collect
{
	void			*frame[6];
	int				current_frame;
	int				x;
	int				y;
}					t_collect;

typedef struct s_img_data
{
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img_data;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*tilesheet_img;
	void			*player_tilesheet_img;
	void			*piece_tilesheet_img;
	void			*enemy_tilesheet_img;
	void			*img_gameover;
	void			**tile_images;
	void			*img;
	char			*addr;
	char			**map_initial;
	int				offset_x;
	int				offset_y;
	int				bits_per_pixel;
	int				line_length;
	int				move_count;
	int				endian;
	int				img_width;
	int				img_height;
	int				img_piece_width;
	int				img_piece_height;
	int				img_enemy_width;
	int				img_enemy_height;
	int				img_gameover_width;
	int				img_gameover_height;
	int				tiles_per_row;
	int				tiles_per_col;
	char			**map;
	int				map_width;
	int				map_height;
	int				cur_input;
	int				total_collect;
	int				collect_collecter;
	int				enemy_count;
	int				blink_counter;
	t_game_state	game_state;
	t_enemy			*enemies;
	t_spdata		player;
	t_collect		piece;
}					t_data;

int					init_mlx(t_data *data);
int					load_tilesheet(t_data *data, char *path);
void				load_tiles(t_data *data);
void				free_tiles(t_data *data);
int					render_map(t_data *data);
void				*get_tile_images(t_data *data, int tile_x, int tile_y);
void				animate_player(t_data *data);
int					load_player_frames(t_data *data);
void				*extract_frame(t_data *data, void *source_img, int x,
						int y);
int					key_press(int keycode, t_data *data);
int					exit_game(t_data *data);
int					find_player_position(t_data *data);
void				draw_image_on_buffer(t_data *data, void *img, int x, int y);
void				draw_map(t_data *data);
void				draw_player(t_data *data);
int					load_map(t_data *data, char *filename);
void				animate_collect(t_data *data);
void				draw_collects(t_data *data);
void				count_collectibles(t_data *data);
int					load_collect_frames(t_data *data);
void				add_enemy(t_data *data, int x, int y);
t_enemy				*create_enemy(t_data *data, int x, int y);
void				animate_enemies(t_data *data);
void				move_enemies(t_data *data);
int					handle_enemy_collision(t_data *data);
int					load_enemy_frames(t_data *data);
void				init_enemies(t_data *data);
int					read_map(t_data *data, char *filename);
int					validate_map(t_data *data);
char				*get_next_line(int fd);
int					initialize_visited(t_data *data, int ***visited);
void				bfs_search(t_data *data, int **visited, int player_x,
						int player_y);
void				explore_neighbors(t_data *data, int **visited,
						t_queue_info *queue_info, t_point pos);
int					check_unreachable(t_data *data, int **visited);
void				free_visited(int **visited, int height);
int					count_map_elements(t_data *data, int *player_count,
						int *exit_count, int *collect_count);
int					validate_counts(int player_count, int exit_count,
						int collect_count);
int					check_unknown_chars(t_data *data);
int					check_empty_map(t_data *data);
int					check_rectangular_map(t_data *data);
void				initialize_enemies(t_data *data);
int					initialize_data(t_data *data);
int					load_resources(t_data *data, char *map_file);
int					load_map_and_tiles(t_data *data, char *map_file);
int					load_images(t_data *data);
int					load_frames(t_data *data);
int					initialize_game(t_data *data);
int					initialize_enemies_and_player(t_data *data);
int					initialize_window_and_image(t_data *data);
int					initialize_hooks(t_data *data);
void				start_game_loop(t_data *data);
void				handle_movement(int keycode, t_data *data, int *new_x,
						int *new_y);
int					is_movement_key(int keycode);
void				process_movement(int keycode, t_data *data, int *new_x,
						int *new_y);
void				update_player_position(int keycode, t_data *data, int new_x, int new_y);
void				check_tile(t_data *data, int map_x, int map_y);
int					count_map_height(char *filename, int *map_height);
int					allocate_map(t_data *data);
int					read_map_lines(t_data *data, char *filename);
void				update_enemy_direction(t_enemy *enemy);
void				calculate_new_position(t_enemy *enemy, int *new_x,
						int *new_y);
int					is_move_valid(t_data *data, int new_x, int new_y);
void				move_enemy(t_data *data, t_enemy *enemy);
void				copy_tile_image(t_img_data *tilesheet, t_img_data *tile,
						int tile_x, int tile_y);
void				copy_pixel(t_img_data *tilesheet, t_img_data *tile,
						t_point src, t_point dest);
void				copy_frame_pixels(t_img_data *src, t_img_data *dst,
						int src_x, int src_y);
void				draw_map_row(t_data *data, int y);
void				draw_tile(t_data *data, char tile, int x, int y);
int					load_player_tilesheet(t_data *data);
int					load_piece_tilesheet(t_data *data);
int					load_enemy_tilesheet(t_data *data);
void				free_enemy_frames(t_data *data, t_enemy *enemy);
void				free_enemy(t_data *data, t_enemy *enemy);
void				free_enemies(t_data *data);
void				free_player_frames(t_data *data);
int					allocate_visited(t_data *data, int ***visited);
void				initialize_visited_rows(t_data *data, int **visited);
size_t				copy_and_free_s1(char *str, char *s1);
void				copy_s2(char *str, const char *s2, size_t i);
int					dequeue(t_queue **front, t_queue **rear, int *x, int *y);
void				enqueue(t_queue **front, t_queue **rear, int x, int y);
void				free_map(t_data *data);
int					check_path(t_data *data);
void				draw_enemies(t_data *data);
void				display_game_over(t_data *data);
int					load_gameover_img(t_data *data);
int					reset_game(t_data *data);
int					reset_map(t_data *data);
int					reinit_map(t_data *data);
void				free_current_map(t_data *data);
int					copy_initial_map(t_data *data);
int					display_move_count(t_data *data);
void				draw_and_animate_elements(t_data *data);
#endif