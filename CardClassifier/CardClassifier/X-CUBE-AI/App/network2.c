/**
  ******************************************************************************
  * @file    network2.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue Apr 16 15:53:52 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "network2.h"
#include "network2_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network2
 
#undef AI_NETWORK2_MODEL_SIGNATURE
#define AI_NETWORK2_MODEL_SIGNATURE     "b490b7665fd617555874fa0fbc3bd36a"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Tue Apr 16 15:53:52 2024"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK2_N_BATCHES
#define AI_NETWORK2_N_BATCHES         (1)

static ai_ptr g_network2_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_network2_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  conversion_9_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 54, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 450, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 6, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1536, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 16, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  gemm_7_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 376320, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  gemm_7_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 120, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  gemm_8_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6480, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  gemm_8_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 54, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1284, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 744, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3680, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 896, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  gemm_7_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 3136, AI_STATIC)
/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  gemm_8_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 120, AI_STATIC)
/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_input_10_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 49152, AI_STATIC)
/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  conversion_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 49153, AI_STATIC)
/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 5766, AI_STATIC)
/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3136, AI_STATIC)
/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  transpose_5_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3136, AI_STATIC)
/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  gemm_7_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 120, AI_STATIC)
/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  gemm_8_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 54, AI_STATIC)
/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 6,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0015777165535837412f, 0.0009036802221089602f, 0.0014004471013322473f, 0.003568811807781458f, 0.0014523076824843884f, 0.0016802228055894375f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 16,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0027853366918861866f, 0.0020326978992670774f, 0.0026329902466386557f, 0.0028406560886651278f, 0.002900270279496908f, 0.00283444463275373f, 0.0025942055508494377f, 0.0027593367267400026f, 0.003356789005920291f, 0.0028159627690911293f, 0.002448172541335225f, 0.002070164540782571f, 0.0026460089720785618f, 0.002768060425296426f, 0.0034260668326169252f, 0.002994770649820566f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_7_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002561314031481743f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_8_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002701062709093094f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_scratch1_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08801060169935226f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_scratch1_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07985027879476547f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conversion_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08801060169935226f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07985027879476547f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(transpose_5_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07985027879476547f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_7_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.6084514856338501f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_8_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.8923231363296509f),
    AI_PACK_INTQ_ZP(63)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conversion_9_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 54, 1, 1), AI_STRIDE_INIT(4, 4, 4, 216, 216),
  1, &conversion_9_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  1, 0x1,
  AI_SHAPE_INIT(4, 3, 5, 5, 6), AI_STRIDE_INIT(4, 1, 3, 18, 90),
  1, &conv2d_1_weights_array, &conv2d_1_weights_array_intq)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 6, 1, 1), AI_STRIDE_INIT(4, 4, 4, 24, 24),
  1, &conv2d_1_bias_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_weights, AI_STATIC,
  3, 0x1,
  AI_SHAPE_INIT(4, 6, 4, 4, 16), AI_STRIDE_INIT(4, 1, 6, 96, 384),
  1, &conv2d_3_weights_array, &conv2d_3_weights_array_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_bias, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &conv2d_3_bias_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  gemm_7_weights, AI_STATIC,
  5, 0x1,
  AI_SHAPE_INIT(4, 3136, 120, 1, 1), AI_STRIDE_INIT(4, 1, 3136, 376320, 376320),
  1, &gemm_7_weights_array, &gemm_7_weights_array_intq)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  gemm_7_bias, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 120, 1, 1), AI_STRIDE_INIT(4, 4, 4, 480, 480),
  1, &gemm_7_bias_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  gemm_8_weights, AI_STATIC,
  7, 0x1,
  AI_SHAPE_INIT(4, 120, 54, 1, 1), AI_STRIDE_INIT(4, 1, 120, 6480, 6480),
  1, &gemm_8_weights_array, &gemm_8_weights_array_intq)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  gemm_8_bias, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 54, 1, 1), AI_STRIDE_INIT(4, 4, 4, 216, 216),
  1, &gemm_8_bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch0, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 1284, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1284, 1284),
  1, &conv2d_1_scratch0_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch1, AI_STATIC,
  10, 0x1,
  AI_SHAPE_INIT(4, 1, 6, 62, 2), AI_STRIDE_INIT(4, 1, 1, 6, 372),
  1, &conv2d_1_scratch1_array, &conv2d_1_scratch1_array_intq)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch0, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 3680, 1, 1), AI_STRIDE_INIT(4, 1, 1, 3680, 3680),
  1, &conv2d_3_scratch0_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch1, AI_STATIC,
  12, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 28, 2), AI_STRIDE_INIT(4, 1, 1, 16, 448),
  1, &conv2d_3_scratch1_array, &conv2d_3_scratch1_array_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  gemm_7_scratch0, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 3136, 1, 1), AI_STRIDE_INIT(4, 2, 2, 6272, 6272),
  1, &gemm_7_scratch0_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  gemm_8_scratch0, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 120, 1, 1), AI_STRIDE_INIT(4, 2, 2, 240, 240),
  1, &gemm_8_scratch0_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_input_10_output, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 128, 128), AI_STRIDE_INIT(4, 4, 4, 12, 1536),
  1, &serving_default_input_10_output_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  conversion_0_output, AI_STATIC,
  16, 0x1,
  AI_SHAPE_INIT(4, 1, 3, 128, 128), AI_STRIDE_INIT(4, 1, 1, 3, 384),
  1, &conversion_0_output_array, &conversion_0_output_array_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  17, 0x1,
  AI_SHAPE_INIT(4, 1, 6, 31, 31), AI_STRIDE_INIT(4, 1, 1, 6, 186),
  1, &conv2d_1_output_array, &conv2d_1_output_array_intq)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_output, AI_STATIC,
  18, 0x1,
  AI_SHAPE_INIT(4, 1, 16, 14, 14), AI_STRIDE_INIT(4, 1, 1, 16, 224),
  1, &conv2d_3_output_array, &conv2d_3_output_array_intq)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  transpose_5_output, AI_STATIC,
  19, 0x1,
  AI_SHAPE_INIT(4, 1, 14, 14, 16), AI_STRIDE_INIT(4, 1, 1, 14, 196),
  1, &transpose_5_output_array, &transpose_5_output_array_intq)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  transpose_5_output0, AI_STATIC,
  20, 0x1,
  AI_SHAPE_INIT(4, 1, 3136, 1, 1), AI_STRIDE_INIT(4, 1, 1, 3136, 3136),
  1, &transpose_5_output_array, &transpose_5_output_array_intq)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  gemm_7_output, AI_STATIC,
  21, 0x1,
  AI_SHAPE_INIT(4, 1, 120, 1, 1), AI_STRIDE_INIT(4, 1, 1, 120, 120),
  1, &gemm_7_output_array, &gemm_7_output_array_intq)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  gemm_8_output, AI_STATIC,
  22, 0x1,
  AI_SHAPE_INIT(4, 1, 54, 1, 1), AI_STRIDE_INIT(4, 1, 1, 54, 54),
  1, &gemm_8_output_array, &gemm_8_output_array_intq)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conversion_9_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_8_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_9_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conversion_9_layer, 9,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &conversion_9_chain,
  NULL, &conversion_9_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_8_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_8_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_8_weights, &gemm_8_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_8_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_8_layer, 8,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA,
  &gemm_8_chain,
  NULL, &conversion_9_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_7_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &transpose_5_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_7_weights, &gemm_7_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_7_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_7_layer, 7,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA,
  &gemm_7_chain,
  NULL, &gemm_8_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  transpose_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &transpose_5_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  transpose_5_layer, 5,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &transpose_5_chain,
  NULL, &gemm_7_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_3_scratch0, &conv2d_3_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_3_layer, 4,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_conv2d_sssa8_ch_nl_pool,
  &conv2d_3_chain,
  NULL, &transpose_5_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = AI_HANDLE_PTR(pool_func_mp_array_integer_INT8), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_1_scratch0, &conv2d_1_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 2,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_conv2d_sssa8_ch_nl_pool,
  &conv2d_1_chain,
  NULL, &conv2d_3_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = AI_HANDLE_PTR(pool_func_mp_array_integer_INT8), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conversion_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_input_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conversion_0_layer, 0,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &conversion_0_chain,
  NULL, &conv2d_1_layer, AI_STATIC, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 385572, 1, 1),
    385572, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 196608, 1, 1),
    196608, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK2_IN_NUM, &serving_default_input_10_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK2_OUT_NUM, &conversion_9_output),
  &conversion_0_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 385572, 1, 1),
      385572, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 196608, 1, 1),
      196608, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK2_IN_NUM, &serving_default_input_10_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK2_OUT_NUM, &conversion_9_output),
  &conversion_0_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network2_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_network2_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    serving_default_input_10_output_array.data = AI_PTR(g_network2_activations_map[0] + 0);
    serving_default_input_10_output_array.data_start = AI_PTR(g_network2_activations_map[0] + 0);
    
    conversion_0_output_array.data = AI_PTR(g_network2_activations_map[0] + 0);
    conversion_0_output_array.data_start = AI_PTR(g_network2_activations_map[0] + 0);
    
    conv2d_1_scratch0_array.data = AI_PTR(g_network2_activations_map[0] + 49156);
    conv2d_1_scratch0_array.data_start = AI_PTR(g_network2_activations_map[0] + 49156);
    
    conv2d_1_scratch1_array.data = AI_PTR(g_network2_activations_map[0] + 50440);
    conv2d_1_scratch1_array.data_start = AI_PTR(g_network2_activations_map[0] + 50440);
    
    conv2d_1_output_array.data = AI_PTR(g_network2_activations_map[0] + 51184);
    conv2d_1_output_array.data_start = AI_PTR(g_network2_activations_map[0] + 51184);
    
    conv2d_3_scratch0_array.data = AI_PTR(g_network2_activations_map[0] + 0);
    conv2d_3_scratch0_array.data_start = AI_PTR(g_network2_activations_map[0] + 0);
    
    conv2d_3_scratch1_array.data = AI_PTR(g_network2_activations_map[0] + 3680);
    conv2d_3_scratch1_array.data_start = AI_PTR(g_network2_activations_map[0] + 3680);
    
    conv2d_3_output_array.data = AI_PTR(g_network2_activations_map[0] + 4576);
    conv2d_3_output_array.data_start = AI_PTR(g_network2_activations_map[0] + 4576);
    
    transpose_5_output_array.data = AI_PTR(g_network2_activations_map[0] + 0);
    transpose_5_output_array.data_start = AI_PTR(g_network2_activations_map[0] + 0);
    
    gemm_7_scratch0_array.data = AI_PTR(g_network2_activations_map[0] + 3136);
    gemm_7_scratch0_array.data_start = AI_PTR(g_network2_activations_map[0] + 3136);
    
    gemm_7_output_array.data = AI_PTR(g_network2_activations_map[0] + 9408);
    gemm_7_output_array.data_start = AI_PTR(g_network2_activations_map[0] + 9408);
    
    gemm_8_scratch0_array.data = AI_PTR(g_network2_activations_map[0] + 0);
    gemm_8_scratch0_array.data_start = AI_PTR(g_network2_activations_map[0] + 0);
    
    gemm_8_output_array.data = AI_PTR(g_network2_activations_map[0] + 240);
    gemm_8_output_array.data_start = AI_PTR(g_network2_activations_map[0] + 240);
    
    conversion_9_output_array.data = AI_PTR(g_network2_activations_map[0] + 0);
    conversion_9_output_array.data_start = AI_PTR(g_network2_activations_map[0] + 0);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network2_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_network2_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(g_network2_weights_map[0] + 0);
    conv2d_1_weights_array.data_start = AI_PTR(g_network2_weights_map[0] + 0);
    
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(g_network2_weights_map[0] + 452);
    conv2d_1_bias_array.data_start = AI_PTR(g_network2_weights_map[0] + 452);
    
    conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_weights_array.data = AI_PTR(g_network2_weights_map[0] + 476);
    conv2d_3_weights_array.data_start = AI_PTR(g_network2_weights_map[0] + 476);
    
    conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_bias_array.data = AI_PTR(g_network2_weights_map[0] + 2012);
    conv2d_3_bias_array.data_start = AI_PTR(g_network2_weights_map[0] + 2012);
    
    gemm_7_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_7_weights_array.data = AI_PTR(g_network2_weights_map[0] + 2076);
    gemm_7_weights_array.data_start = AI_PTR(g_network2_weights_map[0] + 2076);
    
    gemm_7_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_7_bias_array.data = AI_PTR(g_network2_weights_map[0] + 378396);
    gemm_7_bias_array.data_start = AI_PTR(g_network2_weights_map[0] + 378396);
    
    gemm_8_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_8_weights_array.data = AI_PTR(g_network2_weights_map[0] + 378876);
    gemm_8_weights_array.data_start = AI_PTR(g_network2_weights_map[0] + 378876);
    
    gemm_8_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_8_bias_array.data = AI_PTR(g_network2_weights_map[0] + 385356);
    gemm_8_bias_array.data_start = AI_PTR(g_network2_weights_map[0] + 385356);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network2_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK2_MODEL_NAME,
      .model_signature   = AI_NETWORK2_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 3452608,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_network2_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK2_MODEL_NAME,
      .model_signature   = AI_NETWORK2_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 3452608,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_network2_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network2_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_network2_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_network2_create(network, AI_NETWORK2_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_network2_data_params_get(&params) != true) {
        err = ai_network2_get_error(*network);
        return err;
    }
#if defined(AI_NETWORK2_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_NETWORK2_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_network2_init(*network, &params) != true) {
        err = ai_network2_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_network2_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_network2_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_network2_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network2_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= network2_configure_weights(net_ctx, params);
  ok &= network2_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network2_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network2_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK2_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

