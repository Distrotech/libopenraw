/*
 * libopenraw - thumbcpp
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



#include <iostream>
#include <libopenraw/libopenraw.h>
#include <libopenraw/debug.h>
#include <libopenraw++/thumbnail.h>
#include <libopenraw++/rawfile.h>


using OpenRaw::Thumbnail;

int
main(int argc, char** argv)
{

	if (argc < 2) {
		std::cerr << "missing parameter" << std::endl;
		return 1;
	}

	OpenRaw::init();
	or_debug_set_level(DEBUG2);
	FILE * f;

	OpenRaw::RawFile * raw_file = OpenRaw::RawFile::newRawFile(argv[1]);
	std::vector<uint32_t> list = raw_file->listThumbnailSizes();
	
	for(std::vector<uint32_t>::iterator i = list.begin();
			i != list.end(); ++i)
	{
		std::cout << "found " << *i << " pixels\n";
	}

	delete raw_file;

	Thumbnail * thumb =
		Thumbnail::getAndExtractThumbnail(argv[1],
													 160);
	if (thumb != NULL) {
		std::cerr << "thumb data size =" << thumb->size() << std::endl;
		std::cerr << "thumb data type =" << thumb->dataType() << std::endl;
		
		f = fopen("thumb.jpg", "wb");
		fwrite(thumb->data(), 1, thumb->size(), f);
		fclose(f);
		
		delete thumb;
	}

	thumb =
		Thumbnail::getAndExtractThumbnail(argv[1],
													 640);

	if (thumb != NULL) {
		std::cerr << "thumb data size =" << thumb->size() << std::endl;
		std::cerr << "thumb data type =" << thumb->dataType() << std::endl;
		
		f = fopen("thumbl.jpg", "wb");
		fwrite(thumb->data(), 1, thumb->size(), f);
		fclose(f);
		
		delete thumb;
	}

	thumb =
		Thumbnail::getAndExtractThumbnail(argv[1],
													 2048);
	if (thumb != NULL) {
		std::cerr << "preview data size =" << thumb->size() << std::endl;
		std::cerr << "preview data type =" << thumb->dataType() << std::endl;
		
		f = fopen("preview.jpg", "wb");
		fwrite(thumb->data(), 1, thumb->size(), f);
		fclose(f);
		
		delete thumb;
	}


	return 0;
}

