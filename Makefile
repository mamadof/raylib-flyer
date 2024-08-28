all:
	gcc -lm -lraylib main.c helpers.c game.c player.c projectile.c render.c sounds.c enemy.c world_interface.c -o out -g