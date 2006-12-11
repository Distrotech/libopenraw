/*
 * libopenraw - thumbc.c
 *
 * Copyright (C) 2006 Hubert Figuiere
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */



#include <stdio.h>

#include <libopenraw/libopenraw.h>

int
main(int argc, char **argv)
{
	char thumbFile[256];
	char *filename = argv[1];
	ORThumbnailRef thumbnail = NULL;

	or_debug_set_level(DEBUG2);

	if(filename && *filename)
	{
		void *thumbnailData;
		or_data_type thumbnailFormat;
		int thumbnailSize;
		size_t dataSize;
		FILE *output;
		uint32_t x, y;

		or_get_extract_thumbnail(filename, 
								 160, &thumbnail);

		thumbnailFormat = or_thumbnail_format(thumbnail);
		dataSize = or_thumbnail_data_size(thumbnail);
		or_thumbnail_dimensions(thumbnail, &x, &y);

		switch (thumbnailFormat) {
		case OR_DATA_TYPE_JPEG:
			printf("Thumbnail in JPEG format, thumb size is %u, %u\n", x, y);
			break;
		case OR_DATA_TYPE_PIXMAP_8RGB:
			printf("Thumbnail in 8RGB format, thumb size is %u, %u\n", x, y);
			break;
		default:
			printf("Thumbnail in UNKNOWN format, thumb size is %u, %u\n", x, y);
			break;
		}
		output = fopen("thumb.jpg", "wb");
		thumbnailData = or_thumbnail_data(thumbnail);
		fwrite(thumbnailData, dataSize, 1, output);
		fclose(output);
		printf("output %d bytes\n", dataSize);
		or_thumbnail_release(thumbnail);
	}
	else {
		printf("No input file name\n");
	}

	return 0;
}