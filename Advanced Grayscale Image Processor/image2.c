#include <stdio.h>
#include <stdlib.h>

/* Map number to character accordingly */
char get_character(int levels, int level) {
	int last = levels - 1;

	if(level > last)
		return -1;

	if(level == 0)
		return ' ';
	else if(level == last)
		return '#';
	else if(level == 1) {
		if(levels == 3)
			return ':';
		else
			return '.';
	}
	else if(level == 2)
		return ':';

	return -1;
}

int main(int argc, char *argv[]) {
	int  grey_levels, level, times, width, height, i, j, k;
	char character;
	int pixels[100][80];

	scanf("%d %d %d", &width, &height, &grey_levels);
 	if(width>=80 || height >=100)
 		return -1;

	/* Store the initial numbers */
 	i=0;
 	j=0;
	while(1) {
		if(scanf("%d %d", &level, &times) == EOF)
			break;

		for(k=0; k<times; k++) {
			pixels[i][j] = level;
			j += 1;
			if(j == width) {
				i += 1;
				j=0;
			}
		}
	}

	/* Calculates grad */
	int p1, p2, p3, p4, gh, gp, gu, gn, max;
	for(i=0; i<height - 1; i++) {
		for(j=0; j<width - 1; j++) {
			p1 = pixels[i][j];
			p2 = pixels[i][j+1];
			p3 = pixels[i+1][j];
			p4 = pixels[i+1][j+1];

			gh = abs((p1 - p2 + p3 - p4)/2);
			gp = abs(p1 - p4);
			max = gh > gp ? gh : gp;

			gu = abs((p1 - p3 + p2 - p4)/2);
			max = max > gu ? max : gu;

			gn = abs(p2 - p3);
			max = max > gn ? max : gn;

			pixels[i][j] = max;
		}
	}

	/* Print the mapped characters */
	for(i=0; i<height - 1; i++) {
		for(j=0; j<width - 1; j++) {
			character = get_character(grey_levels, pixels[i][j]);
			if(character == -1)
				return -1;
			printf("%c", character);
		}
		printf("\n");
	}

	return 0;
}