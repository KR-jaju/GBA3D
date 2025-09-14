
int	render()
{
	int triangle_aabb;
	int tile_area;
	int dudx;
	int dvdy;
	int dudy;
	int dvdy;
	int dE0dx;
	int dE1dx;
	int dE0dy;
	int dE1dy;
	int determinant;

	int E0;
	int E1;

	for (int y = triangle_aabb.y_min; y < triangle_aabb.y_max; ++y)
	{
		for (int x = triangle_aabb.x_min; x < triangle_aabb.x_max; ++x)
		{
			minimum = min(E0 + (dE0dx > 0 ? dE0dx : 0), E1 + (dE1dx > 0 ? dE1dx : 0));
			maximum

			minimum = min()



			rasterizeTile(x, y, tile_area);
			E0 += dE0dx;
			E1 += dE1dx;
		}
		E0 += (dE0dy - dE0dx * tile_area.width);
		E1 += (dE1dy - dE1dx * tile_area.width);
	}
}