set(QINGKE_V5F_COMMON_OPTIONS
    -march=rv32imafc_zba_zbb_zbc_zbs_xw
    -mabi=ilp32f
    -msmall-data-limit=8
    -msave-restore
    -fsigned-char
    -fsingle-precision-constant
    -Wunused 
    -Wuninitialized
    -fmessage-length=0
    -fmax-errors=5
)

set(QINGKE_V5F_COMPILE_OPTIONS
)

set(QINGKE_V5F_LINK_OPTIONS
)

set(QINGKE_V5F_DEFINITIONS
    __FPU_PRESENT=1
#    ARM_MATH_CM4
#    ARM_MATH_MATRIX_CHECK
#    ARM_MATH_ROUNDING
    Core_V5F
    __DSP_PRESENT=0
    __CCM_PRESENT=0
    __CIDU_PRESENT=0
    __ECLIC_PRESENT=0
    __PMP_PRESENT=0
    __SPMP_PRESENT=0
    __SYSTIMER_PRESENT=0
    __VECTOR_PRESENT=0
)
