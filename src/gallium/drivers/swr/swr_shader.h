/****************************************************************************
 * Copyright (C) 2015 Intel Corporation.   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ***************************************************************************/

#pragma once

struct swr_vertex_shader;
struct swr_fragment_shader;
struct swr_jit_fs_key;
struct swr_jit_vs_key;

PFN_VERTEX_FUNC
swr_compile_vs(struct swr_context *ctx, swr_jit_vs_key &key);

PFN_PIXEL_KERNEL
swr_compile_fs(struct swr_context *ctx, swr_jit_fs_key &key);

void swr_generate_fs_key(struct swr_jit_fs_key &key,
                         struct swr_context *ctx,
                         swr_fragment_shader *swr_fs);

void swr_generate_vs_key(struct swr_jit_vs_key &key,
                         struct swr_context *ctx,
                         swr_vertex_shader *swr_vs);

struct swr_jit_sampler_key {
   unsigned nr_samplers;
   unsigned nr_sampler_views;
   struct swr_sampler_static_state sampler[PIPE_MAX_SHADER_SAMPLER_VIEWS];
};

struct swr_jit_fs_key : swr_jit_sampler_key {
   unsigned nr_cbufs;
   unsigned light_twoside;
   unsigned flatshade;
   ubyte vs_output_semantic_name[PIPE_MAX_SHADER_OUTPUTS];
   ubyte vs_output_semantic_idx[PIPE_MAX_SHADER_OUTPUTS];
};

struct swr_jit_vs_key : swr_jit_sampler_key {
};

namespace std
{
template <> struct hash<swr_jit_fs_key> {
   std::size_t operator()(const swr_jit_fs_key &k) const
   {
      return util_hash_crc32(&k, sizeof(k));
   }
};

template <> struct hash<swr_jit_vs_key> {
   std::size_t operator()(const swr_jit_vs_key &k) const
   {
      return util_hash_crc32(&k, sizeof(k));
   }
};
};

bool operator==(const swr_jit_fs_key &lhs, const swr_jit_fs_key &rhs);
bool operator==(const swr_jit_vs_key &lhs, const swr_jit_vs_key &rhs);
