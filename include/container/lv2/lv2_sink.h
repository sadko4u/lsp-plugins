/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 21 июн. 2019 г.
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

#ifndef CONTAINER_LV2_LV2_SINK_H_
#define CONTAINER_LV2_LV2_SINK_H_

#include <core/types.h>
#include <core/status.h>

namespace lsp
{
    typedef struct lv2_sink
    {
        uint8_t    *buf;
        size_t      size;
        size_t      cap;
        status_t    res;
        LV2_Atom    stub;

        static LV2_Atom_Forge_Ref sink(LV2_Atom_Forge_Sink_Handle handle, const void *buf, uint32_t size);

        static LV2_Atom *deref(LV2_Atom_Forge_Sink_Handle handle, LV2_Atom_Forge_Ref ref);

        explicit lv2_sink(size_t capacity = 0x100);
        ~lv2_sink();
    } lv2_sink;

    lv2_sink::lv2_sink(size_t capacity)
    {
        buf         = NULL;
        size        = 0;
        cap         = capacity;
        res         = STATUS_OK;
        stub.size   = 0;
        stub.type   = 0;

        if (cap > 0)
        {
            buf     = reinterpret_cast<uint8_t *>(::malloc(capacity));
            if (buf == NULL)
                res     = STATUS_NO_MEM;
        }
    }

    lv2_sink::~lv2_sink()
    {
        if (buf != NULL)
        {
            ::free(buf);
            buf     = NULL;
        }
        size        = 0;
        cap         = 0;
    }

    LV2_Atom_Forge_Ref lv2_sink::sink(LV2_Atom_Forge_Sink_Handle handle, const void *buf, uint32_t size)
    {
        lv2_sink *_this = reinterpret_cast<lv2_sink *>(handle);
        if (_this->res != STATUS_OK)
            return 0;

        size_t offset   = _this->size;
        size_t capacity = offset + size;
        if (capacity > _this->cap)
        {
            capacity       += (capacity >> 1);
            uint8_t *ptr    = reinterpret_cast<uint8_t *>(::realloc(_this->buf, capacity));
            if (ptr == NULL) {
                _this->res      = STATUS_NO_MEM;
                return 0;
            }
            _this->buf      = ptr;
            _this->cap      = capacity;
        }

        ::memcpy(&_this->buf[offset], buf, size);
        _this->size    += size;

        return offset;
    }

    LV2_Atom *lv2_sink::deref(LV2_Atom_Forge_Sink_Handle handle, LV2_Atom_Forge_Ref ref)
    {
        lv2_sink *_this = reinterpret_cast<lv2_sink *>(handle);
        if (_this->res == STATUS_OK)
            return reinterpret_cast<LV2_Atom *>(&_this->buf[ref]);

        return &_this->stub;
    }
}

#endif /* CONTAINER_LV2_LV2_SINK_H_ */
