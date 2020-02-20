/*
 * Parameters.h
 *
 *  Created on: 19 февр. 2020 г.
 *      Author: sadko
 */

#ifndef CORE_CALC_PARAMETERS_H_
#define CORE_CALC_PARAMETERS_H_

#include <data/cvector.h>
#include <core/calc/Resolver.h>

namespace lsp
{
    namespace calc
    {
        /**
         * Implements list of optionally named parameters which then can be used for string formatting.
         * Parameters may have duplicate names. From set of named parameters with the same name the parameter
         * with the least index will be visible by the name.
         */
        class Parameters: public Resolver
        {
            private:
                Parameters & operator = (const Parameters &);

            protected:
                typedef struct param_t
                {
                    value_t         value;
                    ssize_t         len;
                    lsp_wchar_t     name[];
                } param_t;

            protected:
                cvector<param_t>    vParams;

            protected:
                param_t            *lookup_by_name(const LSPString *name);
                ssize_t             lookup_idx_by_name(const LSPString *name);
                param_t             *lookup_by_name(const LSPString *name, size_t *idx);
                static param_t     *allocate();
                static param_t     *allocate(const lsp_wchar_t *name, ssize_t len);
                static param_t     *clone(const param_t *src);
                static void         destroy(param_t *p);
                inline static param_t *allocate(const LSPString *name) { return allocate(name->characters(), name->length()); };

                static void         destroy_params(cvector<param_t> &params);

            public:
                explicit Parameters();
                virtual ~Parameters();

            public:
                virtual status_t    resolve(value_t *value, const char *name, size_t num_indexes = 0, const ssize_t *indexes = NULL);

                virtual status_t    resolve(value_t *value, const LSPString *name, size_t num_indexes = 0, const ssize_t *indexes = NULL);

            public:
                inline size_t       size() const            { return vParams.size(); }
                inline void         swap(Parameters *src)   { vParams.swap_data(&src->vParams); }
                inline void         clear()                 { destroy_params(vParams); };

                // Adding: add parameter to the end of list.
                status_t            add_int(const char *name, ssize_t value);
                status_t            add_float(const char *name, double value);
                status_t            add_bool(const char *name, bool value);
                status_t            add_string(const char *name, const char *value, const char *charset = NULL);
                status_t            add_string(const char *name, const LSPString *value);
                status_t            add_null(const char *name);
                status_t            add_undef(const char *name);
                status_t            add(const char *name, const value_t *value);

                status_t            add_int(const LSPString *name, ssize_t value);
                status_t            add_float(const LSPString *name, double value);
                status_t            add_bool(const LSPString *name, bool value);
                status_t            add_string(const LSPString *name, const char *value, const char *charset = NULL);
                status_t            add_string(const LSPString *name, const LSPString *value);
                status_t            add_null(const LSPString *name);
                status_t            add_undef(const LSPString *name);
                status_t            add(const LSPString *name, const value_t *value);

                status_t            add_int(ssize_t value);
                status_t            add_float(double value);
                status_t            add_bool(bool value);
                status_t            add_string(const char *value, const char *charset = NULL);
                status_t            add_string(const LSPString *value);
                status_t            add_null();
                status_t            add_undef();
                status_t            add(const value_t *value);

                status_t            add(const Parameters *p, ssize_t first = 0, ssize_t last = -1);

                // Inserting
                status_t            insert_int(size_t index, const char *name, ssize_t value);
                status_t            insert_float(size_t index, const char *name, double value);
                status_t            insert_bool(size_t index, const char *name, bool value);
                status_t            insert_string(size_t index, const char *name, const char *value, const char *charset = NULL);
                status_t            insert_string(size_t index, const char *name, const LSPString *value);
                status_t            insert_null(size_t index, const char *name);
                status_t            insert_undef(size_t index, const char *name);
                status_t            insert(size_t index, const char *name, const value_t *value);

                status_t            insert_int(size_t index, const LSPString *name, ssize_t value);
                status_t            insert_float(size_t index, const LSPString *name, double value);
                status_t            insert_bool(size_t index, const LSPString *name, bool value);
                status_t            insert_string(size_t index, const LSPString *name, const char *value, const char *charset = NULL);
                status_t            insert_string(size_t index, const LSPString *name, const LSPString *value);
                status_t            insert_null(size_t index, const LSPString *name);
                status_t            insert_undef(size_t index, const LSPString *name);
                status_t            insert(size_t index, const LSPString *name, const value_t *value);

                status_t            insert_int(size_t index, ssize_t value);
                status_t            insert_float(size_t index, double value);
                status_t            insert_bool(size_t index, bool value);
                status_t            insert_string(size_t index, const char *value, const char *charset = NULL);
                status_t            insert_string(size_t index, const LSPString *value);
                status_t            insert_null(size_t index);
                status_t            insert_undef(size_t index);
                status_t            insert(size_t index, const value_t *value);

                status_t            insert(size_t index, const Parameters *p, ssize_t first = 0, ssize_t last = -1);

                // Getting
                status_t            get_int(size_t index, ssize_t *value);
                status_t            get_float(size_t index, double *value);
                status_t            get_bool(size_t index, bool *value);
                status_t            get_string(size_t index, LSPString *value);
                status_t            get_null(size_t index);
                status_t            get_undef(size_t index);
                status_t            get(size_t index, value_t *value);

                status_t            get_int(const char *name, ssize_t *value);
                status_t            get_float(const char *name, double *value);
                status_t            get_bool(const char *name, bool *value);
                status_t            get_string(const char *name, LSPString *value);
                status_t            get_null(const char *name);
                status_t            get_undef(const char *name);
                status_t            get(const char *name, value_t *value);

                status_t            get_int(const LSPString *name, ssize_t *value);
                status_t            get_float(const LSPString *name, double *value);
                status_t            get_bool(const LSPString *name, bool *value);
                status_t            get_string(const LSPString *name, const LSPString *value);
                status_t            get_null(const LSPString *name);
                status_t            get_undef(const LSPString *name);
                status_t            get(const LSPString *name, value_t *value);

                // Setting
                status_t            set_int(const char *name, ssize_t value);
                status_t            set_float(const char *name, double value);
                status_t            set_bool(const char *name, bool value);
                status_t            set_string(const char *name, const char *value, const char *charset = NULL);
                status_t            set_string(const char *name, const LSPString *value);
                status_t            set_null(const char *name);
                status_t            set_undef(const char *name);
                status_t            set(const char *name, const value_t *value);

                status_t            set_int(const LSPString *name, ssize_t value);
                status_t            set_float(const LSPString *name, double value);
                status_t            set_bool(const LSPString *name, bool value);
                status_t            set_string(const LSPString *name, const char *value, const char *charset = NULL);
                status_t            set_string(const LSPString *name, const LSPString *value);
                status_t            set_null(const LSPString *name);
                status_t            set_undef(const LSPString *name);
                status_t            set(const LSPString *name, const value_t *value);

                status_t            set_int(size_t index, ssize_t value);
                status_t            set_float(size_t index, double value);
                status_t            set_bool(size_t index, bool value);
                status_t            set_string(size_t index, const char *value, const char *charset = NULL);
                status_t            set_string(size_t index, const LSPString *value);
                status_t            set_null(size_t index);
                status_t            set_undef(size_t index);

                status_t            set(const Parameters *p, ssize_t first = 0, ssize_t last = -1);

                // Removing
                status_t            remove_int(size_t index, ssize_t *value = NULL);
                status_t            remove_float(size_t index, double *value = NULL);
                status_t            remove_bool(size_t index, bool *value = NULL);
                status_t            remove_string(size_t index, LSPString *value = NULL);
                status_t            remove_null(size_t index);
                status_t            remove_undef(size_t index);
                status_t            remove(size_t index, value_t *value = NULL);

                status_t            remove_int(const char *name, ssize_t *value = NULL);
                status_t            remove_float(const char *name, double *value = NULL);
                status_t            remove_bool(const char *name, bool *value = NULL);
                status_t            remove_string(const char *name, LSPString *value = NULL);
                status_t            remove_null(const char *name = NULL);
                status_t            remove_undef(const char *name = NULL);
                status_t            remove(const char *name, value_t *value = NULL);

                status_t            remove_int(const LSPString *name, ssize_t *value = NULL);
                status_t            remove_float(const LSPString *name, double *value = NULL);
                status_t            remove_bool(const LSPString *name, bool *value = NULL);
                status_t            remove_string(const LSPString *name, LSPString *value = NULL);
                status_t            remove_null(const LSPString *name = NULL);
                status_t            remove_undef(const LSPString *name = NULL);
                status_t            remove(const LSPString *name, value_t *value = NULL);

                // Obtaining type of parameter (negative result on error)
                ssize_t             get_type(size_t index);
                ssize_t             get_type(const char *name);
                ssize_t             get_type(const LSPString *name);

                // Obtaining name of parameter
                ssize_t             get_name(size_t index, LSPString *name);
                const char         *get_name(size_t index);
        };
    
    } /* namespace calc */
} /* namespace lsp */

#endif /* CORE_CALC_PARAMETERS_H_ */
