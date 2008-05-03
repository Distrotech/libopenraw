/*
 * libopenraw - neffile.cpp
 *
 * Copyright (C) 2006-2008 Hubert Figuiere
 * Copyright (C) 2008 Novell, Inc.
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */


#include <iostream>
#include <libopenraw++/thumbnail.h>
#include <libopenraw++/rawdata.h>

#include "debug.h"
#include "ifd.h"
#include "ifdfilecontainer.h"
#include "ifddir.h"
#include "ifdentry.h"
#include "io/file.h"
#include "neffile.h"

using namespace Debug;

namespace OpenRaw {


	namespace Internals {

		RawFile *NEFFile::factory(IO::Stream* _filename)
		{
			return new NEFFile(_filename);
		}

		NEFFile::NEFFile(IO::Stream* _filename)
			: TiffEpFile(_filename, OR_RAWFILE_TYPE_NEF)
		{
		}


		NEFFile::~NEFFile()
		{
		}

		bool NEFFile::isCompressed(RawContainer & container, uint32_t offset)
		{
			int i;
			uint8_t buf[256];
			size_t real_size = container.fetchData(buf, offset, 
												   256);
			if(real_size != 256) {
				return true;
			}
			for(i = 15; i < 256; i+= 16) {
				if(buf[i]) {
					Trace(DEBUG1) << "isCompressed: true\n";
					return true;
				}
			}
			Trace(DEBUG1) << "isCompressed: false\n";
			return false;
		}

		::or_error NEFFile::_getRawData(RawData & data, uint32_t /*options*/)
		{
			::or_error ret = OR_ERROR_NONE;
			m_cfaIfd = _locateCfaIfd();
			Trace(DEBUG1) << "_getRawData()\n";

			if(m_cfaIfd) {
				ret = _getRawDataFromDir(data, m_cfaIfd);
			}
			else {
				ret = OR_ERROR_NOT_FOUND;
			}
			return ret;
		}

	}
}

