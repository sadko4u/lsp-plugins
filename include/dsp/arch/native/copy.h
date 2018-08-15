/*
 * copy.h
 *
 *  Created on: 12 авг. 2018 г.
 *      Author: sadko
 */

#ifndef DSP_ARCH_NATIVE_COPY_H_
#define DSP_ARCH_NATIVE_COPY_H_

#ifndef __DSP_NATIVE_IMPL
    #error "This header should not be included directly"
#endif /* __DSP_NATIVE_IMPL */

void copy(float *dst, const float *src, size_t count)
{
    if (dst == src)
        return;
    memcpy(dst, src, count * sizeof(float));
}

void move(float *dst, const float *src, size_t count)
{
    if (dst == src)
        return;
    memmove(dst, src, count * sizeof(float));
}

void fill(float *dst, float value, size_t count)
{
    while (count--)
        *(dst++) = value;
}

void fill_zero(float *dst, size_t count)
{
    while (count--)
        *(dst++) = 0.0f;
}

void fill_one(float *dst, size_t count)
{
    while (count--)
        *(dst++) = 1.0f;
}

void fill_minus_one(float *dst, size_t count)
{
    while (count--)
        *(dst++) = -1.0f;
}

void reverse1(float *dst, size_t count)
{
    float *src      = &dst[count];
    count >>= 1;
    while (count--)
    {
        float   tmp = *dst;
        *(dst++)    = *(--src);
        *src        = tmp;
    }
}

void reverse2(float *dst, const float *src, size_t count)
{
    if (dst == src)
    {
        reverse1(dst, count);
        return;
    }

    src         = &src[count];
    while (count--)
        *(dst++)    = *(--src);
}

#endif /* DSP_ARCH_NATIVE_COPY_H_ */
