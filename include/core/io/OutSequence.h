/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 18 июн. 2018 г.
 *
 * lsp-plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-plugins. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CORE_IO_OUTSEQUENCE_H_
#define CORE_IO_OUTSEQUENCE_H_

#include <stdio.h>
#include <core/types.h>
#include <core/io/charset.h>
#include <core/io/Path.h>
#include <core/io/File.h>
#include <core/io/CharsetEncoder.h>
#include <core/io/IOutStream.h>
#include <core/io/IOutSequence.h>

namespace lsp
{
    namespace io
    {
        class OutSequence: public IOutSequence
        {
            protected:
                IOutStream     *pOS;
                size_t          nWrapFlags;
                CharsetEncoder  sEncoder;
    
            protected:
                status_t        flush_buffer_internal(bool force);

            private:
                OutSequence & operator = (const OutSequence &);

            public:
                explicit OutSequence();
                virtual ~OutSequence();

            public:
                using IOutSequence::write;
                using IOutSequence::write_ascii;

            public:
                status_t wrap(FILE *fd, bool close, const char *charset = NULL);

                status_t wrap_native(lsp_fhandle_t fd, bool close, const char *charset = NULL);

                status_t wrap(File *fd, size_t flags, const char *charset = NULL);

                status_t wrap(IOutStream *os, size_t flags, const char *charset = NULL);

                status_t open(const char *path, size_t mode, const char *charset = NULL);

                status_t open(const LSPString *path, size_t mode, const char *charset = NULL);

                status_t open(const Path *path, size_t mode, const char *charset = NULL);

                virtual status_t write(lsp_wchar_t c);

                virtual status_t write(const lsp_wchar_t *c, size_t count);

                virtual status_t write_ascii(const char *s, size_t count);

                virtual status_t flush();

                virtual status_t close();
        };
    }
} /* namespace lsp */

#endif /* CORE_IO_OUTSEQUENCE_H_ */
