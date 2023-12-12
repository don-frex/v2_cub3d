void raycast(float player_x, float player_y, float ray_angle, char **map) {
    float ray_dir_x = cos(ray_angle);
    float ray_dir_y = sin(ray_angle);

    float step_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
    float step_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));

    int map_x = (int)player_x;
    int map_y = (int)player_y;

    int hit = 0;
    int side; // 0 for horizontal, 1 for vertical

    // Incrementally check for intersections with walls
    while (!hit) {
        if (step_x < step_y) {
            step_x += sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
            map_x += (ray_dir_x > 0) ? 1 : -1;
            side = 0;
        } else {
            step_y += sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
            map_y += (ray_dir_y > 0) ? 1 : -1;
            side = 1;
        }

        // Check if the ray has hit a wall
        if (map[map_y][map_x] == '1') {
            hit = 1;
        }
    }

    // Calculate distance from player to the wall in pixels
    float distance;
    if (side == 0) {
        distance = fabs((map_x - player_x + (1 - (ray_dir_x > 0))) / ray_dir_x) * CELL_SIZE;
    } else {
        distance = fabs((map_y - player_y + (1 - (ray_dir_y > 0))) / ray_dir_y) * CELL_SIZE;
    }

    // Calculate wall position in pixels
    int wall_x = map_x * CELL_SIZE;
    int wall_y = map_y * CELL_SIZE;

    printf("Distance to wall: %.2f pixels\n", distance);
    printf("Wall position (x, y): %d, %d pixels\n", wall_x, wall_y);
}


int    check_player_on_wall(t_eng *eng, double player_x, double player_y)
{
    int    x;
    int    y;
    char    **map;

    map = eng->parser.map;
    x = player_x / squir_size; 
    y = player_y / squir_size;
    if (y < 0  y >= twod_size(map))
        return (1);
    if (x < 0  x > (int)ft_strlen(map[y]))
        return (1);
    if (map[y][x] == '1')
        return (1);
    return (0);
}