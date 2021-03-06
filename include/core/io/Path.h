/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 8 февр. 2019 г.
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

#ifndef INCLUDE_CORE_IO_PATH_H_
#define INCLUDE_CORE_IO_PATH_H_

#include <core/status.h>
#include <core/LSPString.h>

namespace lsp
{
    namespace io
    {
        typedef struct fattr_t
        {
            enum ftype_t {
                FT_BLOCK,
                FT_CHARACTER,
                FT_DIRECTORY,
                FT_FIFO,
                FT_SYMLINK,
                FT_REGULAR,
                FT_SOCKET,
                FT_UNKNOWN
            };

            ftype_t     type;       // File type
            size_t      blk_size;   // Block size
            wsize_t     size;       // File size
            wsize_t     inode;      // Index node
            wsize_t     ctime;      // Creation time in milliseconds
            wsize_t     mtime;      // Modification time in milliseconds
            wsize_t     atime;      // Access time in milliseconds
        } fattr_t;

        class Path
        {
            private:
                LSPString   sPath;

            private:
                Path & operator = (const Path &);

                inline void     fixup_path();
                status_t        compute_relative(Path *base);

            public:
                explicit Path();
                ~Path();
                
            public:
                status_t    set(const char *path);
                status_t    set(const LSPString *path);
                status_t    set(const Path *path);

                status_t    set(const char *path, const char *child);
                status_t    set(const char *path, const LSPString *child);
                status_t    set(const char *path, const Path *child);

                status_t    set(const LSPString *path, const char *child);
                status_t    set(const LSPString *path, const LSPString *child);
                status_t    set(const LSPString *path, const Path *child);

                status_t    set(const Path *path, const char *child);
                status_t    set(const Path *path, const LSPString *child);
                status_t    set(const Path *path, const Path *child);

                inline const char *get() const                          { return sPath.get_utf8();  }
                status_t    get(char *path, size_t maxlen) const;
                status_t    get(LSPString *path) const;
                status_t    get(Path *path) const;

                status_t    set_last(const char *path);
                status_t    set_last(const LSPString *path);
                status_t    set_last(const Path *path);

                status_t    get_last(char *path, size_t maxlen) const;
                status_t    get_last(LSPString *path) const;
                status_t    get_last(Path *path) const;

                status_t    get_parent(char *path, size_t maxlen) const;
                status_t    get_parent(LSPString *path) const;
                status_t    get_parent(Path *path) const;

                status_t    set_parent(const char *path);
                status_t    set_parent(LSPString *path);
                status_t    set_parent(Path *path);

                status_t    concat(const char *path);
                status_t    concat(LSPString *path);
                status_t    concat(Path *path);

                status_t    append_child(const char *path);
                status_t    append_child(const LSPString *path);
                status_t    append_child(const Path *path);

                status_t    append(const char *path);
                status_t    append(const LSPString *path);
                status_t    append(const Path *path);

                status_t    remove_last();
                status_t    remove_last(char *path, size_t maxlen);
                status_t    remove_last(LSPString *path);
                status_t    remove_last(Path *path);

                status_t    remove_base(const char *path);
                status_t    remove_base(const LSPString *path);
                status_t    remove_base(const Path *path);

                ssize_t     fmt(const char *fmt...);
                ssize_t     fmt(const LSPString *fmt...);
                ssize_t     vfmt(const char *fmt, va_list args);
                ssize_t     vfmt(const LSPString *fmt, va_list args);

                bool        is_absolute() const;
                bool        is_relative() const;
                bool        is_canonical() const;
                bool        is_root() const;
                bool        is_dot() const;
                bool        is_dotdot() const;
                inline bool is_empty() const                        { return sPath.is_empty();  }
                inline size_t   length() const                      { return sPath.length();            }

                inline void clear()                                 { sPath.clear();    }

                inline void swap(Path *path)                        { sPath.swap(&path->sPath); }

                status_t    canonicalize();

                status_t    root();
                status_t    current();
                status_t    parent();

                status_t    get_canonical(char *path, size_t maxlen) const;
                status_t    get_canonical(LSPString *path) const;
                status_t    get_canonical(Path *path) const;

                status_t    as_relative(const char *path);
                status_t    as_relative(const LSPString *path);
                status_t    as_relative(const Path *path);

                bool        equals(const Path *path) const;
                bool        equals(const LSPString *path) const;
                bool        equals(const char *path) const;

                inline const LSPString *as_string() const           { return &sPath; }
                inline const char *as_utf8() const                  { return sPath.get_utf8(); }
                inline const char *as_native(const char *charset = NULL) const { return sPath.get_native(charset); }
                inline void take(Path *src) { sPath.take(&src->sPath); }
                void take(LSPString *src);

            public:
                status_t    stat(fattr_t *attr) const;
                status_t    sym_stat(fattr_t *attr) const;
                wssize_t    size() const;
                bool        exists() const;
                bool        is_reg() const;
                bool        is_dir() const;
                bool        is_block_dev() const;
                bool        is_char_dev() const;
                bool        is_fifo() const;
                bool        is_symlink() const;
                bool        is_socket() const;
                status_t    mkdir() const;
                status_t    mkdir(bool recursive) const;
                status_t    remove() const;
        };
    }
} /* namespace lsp */

#endif /* INCLUDE_CORE_IO_PATH_H_ */
