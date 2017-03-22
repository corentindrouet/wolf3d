/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 13:48:04 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/22 14:03:40 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

t_bmp_img	*read_bmp(char *file)
{
	int					fd;
	t_bmp_img			*img_data;
	t_bmp_header		bit_map_file_header;
	int					verif;
	char				*buff;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	verif = read(fd, &bit_map_file_header, sizeof(t_bmp_header));
	if (verif < 0 || bit_map_file_header.type != 0x4D42)// (bit_map_file_header.type1 != 0x42 && bit_map_file_header.type2 != 0x4D))
		return (NULL);
	img_data = (t_bmp_img*)malloc(sizeof(t_bmp_img));
	verif = read(fd, &(img_data->bit_map_info), sizeof(t_bmp_header_info));
	if (verif < 0)
		return (NULL);
	close(fd);
	fd = open(file, O_RDONLY);
	buff = (char*)malloc(sizeof(char) * bit_map_file_header.image_data_offset);
	read(fd, buff, bit_map_file_header.image_data_offset);
	free(buff);
	img_data->str_img = (unsigned char*)malloc(img_data->bit_map_info.bi_size_image);
	if (!img_data->str_img)
		return (NULL);
	read(fd, img_data->str_img, img_data->bit_map_info.bi_size_image);
	img_data->tab_bmp = (unsigned int*)malloc(sizeof(unsigned int) * (img_data->bit_map_info.bi_size_image / 3));
	verif = 0;
	while ((unsigned int)verif < img_data->bit_map_info.bi_size_image)
	{
		img_data->tab_bmp[((img_data->bit_map_info.bi_size_image / 3) - 1) - (verif / 3)] =
			(img_data->str_img[verif] << 16)
			+ (img_data->str_img[verif + 1] << 8)
			+ (img_data->str_img[verif + 2]);
		verif += 3;
	}
	close(fd);
	return (img_data);
}
