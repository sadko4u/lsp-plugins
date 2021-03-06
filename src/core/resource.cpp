/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 14 июл. 2019 г.
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

#include <core/resource.h>

#ifdef LSP_BUILTIN_RESOURCES
namespace lsp
{
    namespace resource
    {
        const resource_t *get(const char *id, resource_type_t type)
        {
            if (id == NULL)
                return NULL;

            // Iterate list of all resources and lookup for the proper one
            for (const resource_t *res = builtin_resources; (res->id != NULL) && (res->data != NULL); ++res)
            {
                if (strcmp(res->id, id) != 0)
                    continue;
                if ((type == RESOURCE_UNKNOWN) || (res->type == type))
                    return res;
            }
            return NULL;
        }

        const resource_t *all()
        {
            return builtin_resources;
        }

        uint64_t fetch_number(const void **ptr)
        {
            uint64_t offset     = 0;
            size_t shift        = 0;

            const uint8_t *data = reinterpret_cast<const uint8_t *>(*ptr);
            while (true)
            {
                size_t idx          = *(data++);
                offset             |= ((idx & 0x7f) << shift);
                if (!(idx & 0x80))
                    break;
                shift          += 7;
            }

            *ptr                = data;
            return offset;
        }

        const char *fetch_dstring(const void **ptr)
        {
            size_t offset   = fetch_number(ptr);
            return &string_dictionary[offset];
        }

        float fetch_dfloat(const void **ptr)
        {
            size_t index    = fetch_number(ptr);
            return float_dictionary[index];
        }

        uint8_t fetch_byte(const void **ptr)
        {
            const uint8_t *data = reinterpret_cast<const uint8_t *>(*ptr);
            uint8_t val         = *(data++);
            *ptr                = data;
            return val;
        }

        uint8_t get_byte(const void **ptr)
        {
            const uint8_t *data = reinterpret_cast<const uint8_t *>(*ptr);
            return *data;
        }

        ssize_t fetch_bytes(void *dst, const void **ptr, size_t count)
        {
            const uint8_t *data = reinterpret_cast<const uint8_t *>(*ptr);
            ::memcpy(dst, data, count);
            *ptr                = &data[count];
            return count;
        }

        ssize_t skip_bytes(const void **ptr, size_t count)
        {
            const uint8_t *data = reinterpret_cast<const uint8_t *>(*ptr);
            *ptr                = &data[count];
            return count;
        }
    }
}
#else

BUILTIN_RESOURCES_STUB_DEF /* No built-in resources */

namespace lsp
{
    namespace resource
    {
        const resource_t *get(const char *id, resource_type_t type)
        {
            return NULL;
        }

        const resource_t *all()
        {
            return builtin_resources;
        }

        const char *fetch_dstring(const void **ptr)
        {
            return NULL;
        }

        float fetch_dfloat(const void **ptr)
        {
            return 0.0f;
        }

        uint64_t fetch_number(const void **ptr)
        {
            return 0;
        }

        uint8_t fetch_byte(const void **ptr)
        {
            return 0;
        }

        uint8_t get_byte(const void **ptr)
        {
            return 0;
        }

        ssize_t fetch_bytes(void *dst, const void **ptr, size_t count)
        {
            return -1;
        }

        ssize_t skip_bytes(const void **ptr, size_t count)
        {
            return -1;
        }
    }
}
#endif


