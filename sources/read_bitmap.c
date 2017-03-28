/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 13:48:04 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/28 13:47:50 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	invers_tab(t_bmp_img *img_data)
{
	int	i;

	i = 0;
	img_data->tab_bmp = (unsigned int*)malloc(sizeof(unsigned int)
			* (img_data->bit_map_info.bi_size_image / 3));
	while ((unsigned int)i < img_data->bit_map_info.bi_size_image)
	{
		img_data->tab_bmp[
			((img_data->bit_map_info.bi_size_image / 3) - 1) - (i / 3)] =
			(img_data->str_img[i] << 16)
			+ (img_data->str_img[i + 1] << 8)
			+ (img_data->str_img[i + 2]);
		i += 3;
	}
}

static int	seek_like(int fd, t_bmp_header file_header, char *file)
{
	char	*buff;

	close(fd);
	fd = open(file, O_RDONLY);
	buff = (char*)malloc(sizeof(char) * file_header.image_data_offset);
	read(fd, buff, file_header.image_data_offset);
	free(buff);
	return (fd);
}

t_bmp_img	*read_bmp(char *file)
{
	int					fd;
	t_bmp_img			*img_data;
	t_bmp_header		bit_map_file_header;
	int					verif;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	verif = read(fd, &bit_map_file_header, sizeof(t_bmp_header));
	if (verif < 0 || bit_map_file_header.type != 0x4D42)
		return (NULL);
	img_data = (t_bmp_img*)malloc(sizeof(t_bmp_img));
	verif = read(fd, &(img_data->bit_map_info), sizeof(t_bmp_header_info));
	if (verif < 0)
		return (NULL);
	fd = seek_like(fd, bit_map_file_header, file);
	img_data->str_img =
		(unsigned char*)malloc(img_data->bit_map_info.bi_size_image);
	if (!img_data->str_img)
		return (NULL);
	read(fd, img_data->str_img, img_data->bit_map_info.bi_size_image);
	invers_tab(img_data);
	close(fd);
	return (img_data);
}
