/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 13:08:55 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/29 12:52:44 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H
# pragma pack(push, 1)

typedef struct	s_bmp_header
{
	unsigned short	type;
	unsigned int	size;
	unsigned int	reserved1;
	unsigned int	image_data_offset;
}				t_bmp_header;

typedef struct	s_bmp_header_info
{
	unsigned int	size;
	int				width;
	int				height;
	unsigned short	planes;
	unsigned short	bit_pix;
	unsigned int	bi_compression;
	unsigned int	bi_size_image;
	int				bixpelspermeter;
	int				biypelspermeter;
	unsigned int	biclrused;
	unsigned int	biclrimportant;
}				t_bmp_header_info;

# pragma pack(pop)
#endif
