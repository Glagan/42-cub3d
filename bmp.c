/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:13:15 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/10 19:01:37 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "cub3d.h"

static int
	write_bmp_header(int fd, int filesize, t_game *game)
{
	t_window		*w;
	unsigned char	bmpfileheader[54] = {
		'B','M', // set to B M
		0, 0, 0, 0, // filesize 4 bytes
		0, 0, // set to 0
		0, 0, // set to 0
		0, 0, 0, 54, // offset to the data [14 bytes here]
		0, 0, 0, 40, // size of the header
		0, 0, 0, 0, // width of the image [19-22]
		0, 0, 0, 0, // height of the image [23-26]
		0, 1, // number of planes ???
		0, 8, // bpp
		0, 0, 0, 0, // compression
		0, 0, 0, 0, // size if compression
		0, 0, 0, 0, // horizontal pixel per meter
		0, 0, 0, 0, // vertical pixel per meter
		0, 0, 0, 0, // number of colors
		0, 0, 0, 0}; // number of 'important' colors ???
	int				tmp;

	// Shift to the right to actually set an unsigned char
	w = &game->window;
	bmpfileheader[2] = (unsigned char)(filesize & 0xFF000000);
	bmpfileheader[3] = (unsigned char)(filesize & 0x00FF0000);
	bmpfileheader[4] = (unsigned char)(filesize & 0x0000FF00);
	bmpfileheader[5] = (unsigned char)(filesize & 0x000000FF);
	tmp = (int)w->size.x;
	bmpfileheader[19] = (unsigned char)(tmp & 0xFF000000);
	bmpfileheader[20] = (unsigned char)(tmp & 0x00FF0000);
	bmpfileheader[21] = (unsigned char)(tmp & 0x0000FF00);
	bmpfileheader[22] = (unsigned char)(tmp & 0x000000FF);
	tmp = (int)w->size.y;
	bmpfileheader[23] = (unsigned char)(tmp & 0xFF000000);
	bmpfileheader[24] = (unsigned char)(tmp & 0x00FF0000);
	bmpfileheader[25] = (unsigned char)(tmp & 0x0000FF00);
	bmpfileheader[26] = (unsigned char)(tmp & 0x000000FF);
	if (write(fd, bmpfileheader, 54) < 0)
		return (0);
	return (1);
}

int
	save_bmp(t_game *game)
{
	t_window		*w;
	int				filesize;
	int				file;
	unsigned char	bmppad[3] = {0,0,0};

	w = &game->window;
	filesize = 54 + 3 * w->size.x * w->size.y;
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, game))
		return (0);


















	int w = game->window.size.x; /* Put here what ever width you want */
    int h = game->window.size.x; /* Put here what ever height you want */
	int red[w][h];
	int green[w][h];
	int blue[w][h];

	FILE *f;
	int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int
	int x;
	int y;
	int r;
	int g;
	int b;

	for(int i=0; i<w; i++)
	{
		for(int j=0; j<h; j++)
		{
			x=i; y=(h-1)-j;
			r = red[i][j]*255;
			g = green[i][j]*255;
			b = blue[i][j]*255;
			if (r > 255) r=255;
			if (g > 255) g=255;
			if (b > 255) b=255;
			img[(x+y*w)*3+2] = (unsigned char)(r);
			img[(x+y*w)*3+1] = (unsigned char)(g);
			img[(x+y*w)*3+0] = (unsigned char)(b);
		}
	}

	unsigned char bmppad[3] = {0,0,0};

	for(int i=0; i<h; i++)
	{
		fwrite(img+(w*(h-i-1)*3),3,w,f);
		fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}
	fclose(f);
	return (1);
}
