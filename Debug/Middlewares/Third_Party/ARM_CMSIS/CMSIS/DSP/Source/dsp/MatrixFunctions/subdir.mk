################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/MatrixFunctions.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/MatrixFunctionsF16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cholesky_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cholesky_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cholesky_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_inverse_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_inverse_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_inverse_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_ldlt_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_ldlt_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_fast_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_fast_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_opt_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_q7.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_lower_triangular_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_lower_triangular_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_lower_triangular_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_upper_triangular_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_upper_triangular_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_upper_triangular_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_q7.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_q7.c 

OBJS += \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/MatrixFunctions.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/MatrixFunctionsF16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cholesky_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cholesky_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cholesky_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_inverse_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_inverse_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_inverse_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_ldlt_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_ldlt_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_fast_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_fast_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_opt_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_q7.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_lower_triangular_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_lower_triangular_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_lower_triangular_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_upper_triangular_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_upper_triangular_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_upper_triangular_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_q7.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_q7.o 

C_DEPS += \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/MatrixFunctions.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/MatrixFunctionsF16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_add_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cholesky_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cholesky_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cholesky_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_mult_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_cmplx_trans_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_init_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_inverse_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_inverse_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_inverse_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_ldlt_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_ldlt_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_fast_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_fast_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_opt_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_mult_q7.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_scale_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_lower_triangular_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_lower_triangular_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_lower_triangular_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_upper_triangular_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_upper_triangular_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_solve_upper_triangular_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_sub_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_trans_q7.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/arm_mat_vec_mult_q7.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/%.o: ../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/%.c Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/MatrixFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -D__FPU_PRESENT=1 -DARM_MATH_CM7 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../PDM2PCM/App -I../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

