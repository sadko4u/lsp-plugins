/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 6 окт. 2017 г.
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

#ifndef CORE_ASSERT_H_
#define CORE_ASSERT_H_


#define LSP_STATUS_ASSERT(x, ...) { status_t __res__ = (x); if (__res__ != STATUS_OK) { __VA_ARGS__; return __res__; } }
#define LSP_VSTATUS_ASSERT(x, ...) { status_t __res__ = (x); if (__res__ != STATUS_OK) { __VA_ARGS__; return; } }
#define LSP_BOOL_ASSERT(x, res, ...) { if (!(x)) { __VA_ARGS__; return res; } }


#endif /* CORE_ASSERT_H_ */
