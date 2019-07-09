#include <stdio.h>

int left(long ax, long ay, long bx, long by)
{
	return (ax * by) - (ay * bx) < 0;
}

long hausdorff_point(long ax, long ay, long bx, long by, long px, long py)
{
	long rx = bx + (ay - by);
	long ry = by + (bx - ax);
	long sx = ax + (ay - by);
	long sy = ay + (bx - ax);
	if (left(rx - bx, ry - by, px - rx, py - ry) +
			left(rx - bx, ry - by, ax - rx, ay - ry) != 1)
		return 0;
	if (left(sx - ax, sy - ay, px - sx, py - sy) +
			left(sx - ax, sy - ay, bx - sx, by - sy) != 1)
		return 0;
	return 0;
}

int main(void)
{
	return 0;
}
