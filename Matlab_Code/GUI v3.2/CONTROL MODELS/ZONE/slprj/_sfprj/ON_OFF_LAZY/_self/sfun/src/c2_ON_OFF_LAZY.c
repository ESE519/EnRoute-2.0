/* Include files */

#include "blascompat32.h"
#include "ON_OFF_LAZY_sfun.h"
#include "c2_ON_OFF_LAZY.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ON_OFF_LAZY_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[18] = { "CriticalStates",
  "DesiredStates", "i", "k", "m", "des", "minVal", "maxVal", "randIndex",
  "nargin", "nargout", "TEMP_IN", "VALVE_IN", "MAX_ALLOWED_ZONES", "LOW_SP",
  "HIGH_SP", "HOT_COLD", "VALVE_OUT" };

/* Function Declarations */
static void initialize_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance);
static void initialize_params_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance);
static void enable_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance);
static void disable_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_ON_OFF_LAZY
  (SFc2_ON_OFF_LAZYInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_ON_OFF_LAZY
  (SFc2_ON_OFF_LAZYInstanceStruct *chartInstance);
static void set_sim_state_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance);
static void sf_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance);
static void c2_chartstep_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance);
static void initSimStructsc2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_VALVE_OUT, const char_T *c2_identifier, real_T c2_y[4]);
static void c2_b_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, real_T
  c2_inData_data[4], int32_T c2_inData_sizes[2]);
static void c2_d_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y_data[4],
  int32_T c2_y_sizes[2]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, real_T c2_outData_data[4],
  int32_T c2_outData_sizes[2]);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_e_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[19]);
static real_T c2_sum(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance, real_T c2_x
                     [4]);
static void c2_eml_li_find(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  boolean_T c2_x[4], int32_T c2_y_data[4], int32_T c2_y_sizes[2]);
static void c2_find(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance, boolean_T
                    c2_x[4], real_T c2_i_data[4], int32_T c2_i_sizes[2]);
static real_T c2_rand(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance);
static void c2_eml_rand_mt19937ar(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  uint32_T c2_state[625]);
static void c2_twister_state_vector(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, uint32_T c2_mt[625], real_T c2_seed, uint32_T c2_b_mt[625]);
static void c2_b_eml_rand_mt19937ar(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, uint32_T c2_state[625], uint32_T c2_b_state[625], real_T *c2_r);
static void c2_eml_error(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_f_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_g_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_b_method, const char_T *c2_identifier);
static uint8_T c2_h_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_i_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_b_twister_state, const char_T *c2_identifier, uint32_T c2_y
  [625]);
static void c2_j_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, uint32_T c2_y[625]);
static uint32_T c2_k_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_b_v4_state, const char_T *c2_identifier);
static uint32_T c2_l_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static uint8_T c2_m_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_ON_OFF_LAZY, const char_T
  *c2_identifier);
static uint8_T c2_n_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_twister_state_vector(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, uint32_T c2_mt[625], real_T c2_seed);
static real_T c2_c_eml_rand_mt19937ar(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, uint32_T c2_state[625]);
static void init_dsm_address_info(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_method_not_empty = FALSE;
  chartInstance->c2_v4_state_not_empty = FALSE;
  chartInstance->c2_twister_state_not_empty = FALSE;
  chartInstance->c2_is_active_c2_ON_OFF_LAZY = 0U;
}

static void initialize_params_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance)
{
}

static void enable_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_ON_OFF_LAZY
  (SFc2_ON_OFF_LAZYInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_ON_OFF_LAZY
  (SFc2_ON_OFF_LAZYInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[4];
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  int32_T c2_i1;
  uint32_T c2_c_u[625];
  const mxArray *c2_d_y = NULL;
  uint32_T c2_b_hoistedGlobal;
  uint32_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  uint8_T c2_c_hoistedGlobal;
  uint8_T c2_e_u;
  const mxArray *c2_f_y = NULL;
  real_T (*c2_VALVE_OUT)[4];
  c2_VALVE_OUT = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(5));
  for (c2_i0 = 0; c2_i0 < 4; c2_i0++) {
    c2_u[c2_i0] = (*c2_VALVE_OUT)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4));
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_method;
  c2_b_u = c2_hoistedGlobal;
  c2_c_y = NULL;
  if (!chartInstance->c2_method_not_empty) {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c2_y, 1, c2_c_y);
  for (c2_i1 = 0; c2_i1 < 625; c2_i1++) {
    c2_c_u[c2_i1] = chartInstance->c2_twister_state[c2_i1];
  }

  c2_d_y = NULL;
  if (!chartInstance->c2_twister_state_not_empty) {
    sf_mex_assign(&c2_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_c_u, 7, 0U, 1U, 0U, 1, 625));
  }

  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_b_hoistedGlobal = chartInstance->c2_v4_state;
  c2_d_u = c2_b_hoistedGlobal;
  c2_e_y = NULL;
  if (!chartInstance->c2_v4_state_not_empty) {
    sf_mex_assign(&c2_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 7, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c2_y, 3, c2_e_y);
  c2_c_hoistedGlobal = chartInstance->c2_is_active_c2_ON_OFF_LAZY;
  c2_e_u = c2_c_hoistedGlobal;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_e_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 4, c2_f_y);
  sf_mex_assign(&c2_st, c2_y);
  return c2_st;
}

static void set_sim_state_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[4];
  int32_T c2_i2;
  uint32_T c2_uv0[625];
  int32_T c2_i3;
  real_T (*c2_VALVE_OUT)[4];
  c2_VALVE_OUT = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                      "VALVE_OUT", c2_dv0);
  for (c2_i2 = 0; c2_i2 < 4; c2_i2++) {
    (*c2_VALVE_OUT)[c2_i2] = c2_dv0[c2_i2];
  }

  chartInstance->c2_method = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 1)), "method");
  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)),
                        "twister_state", c2_uv0);
  for (c2_i3 = 0; c2_i3 < 625; c2_i3++) {
    chartInstance->c2_twister_state[c2_i3] = c2_uv0[c2_i3];
  }

  chartInstance->c2_v4_state = c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 3)), "v4_state");
  chartInstance->c2_is_active_c2_ON_OFF_LAZY = c2_m_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 4)),
     "is_active_c2_ON_OFF_LAZY");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_ON_OFF_LAZY(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance)
{
}

static void sf_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance)
{
  int32_T c2_i4;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  real_T *c2_MAX_ALLOWED_ZONES;
  real_T *c2_HOT_COLD;
  real_T (*c2_VALVE_OUT)[4];
  real_T (*c2_HIGH_SP)[4];
  real_T (*c2_LOW_SP)[4];
  real_T (*c2_VALVE_IN)[4];
  real_T (*c2_TEMP_IN)[4];
  c2_HOT_COLD = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c2_VALVE_OUT = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_HIGH_SP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
  c2_LOW_SP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
  c2_MAX_ALLOWED_ZONES = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_VALVE_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
  c2_TEMP_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i4 = 0; c2_i4 < 4; c2_i4++) {
    _SFD_DATA_RANGE_CHECK((*c2_TEMP_IN)[c2_i4], 0U);
  }

  for (c2_i5 = 0; c2_i5 < 4; c2_i5++) {
    _SFD_DATA_RANGE_CHECK((*c2_VALVE_IN)[c2_i5], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_MAX_ALLOWED_ZONES, 2U);
  for (c2_i6 = 0; c2_i6 < 4; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*c2_LOW_SP)[c2_i6], 3U);
  }

  for (c2_i7 = 0; c2_i7 < 4; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*c2_HIGH_SP)[c2_i7], 4U);
  }

  for (c2_i8 = 0; c2_i8 < 4; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*c2_VALVE_OUT)[c2_i8], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_HOT_COLD, 6U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_ON_OFF_LAZY(chartInstance);
  sf_debug_check_for_state_inconsistency(_ON_OFF_LAZYMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  int32_T c2_i9;
  real_T c2_TEMP_IN[4];
  int32_T c2_i10;
  real_T c2_VALVE_IN[4];
  real_T c2_MAX_ALLOWED_ZONES;
  int32_T c2_i11;
  real_T c2_LOW_SP[4];
  int32_T c2_i12;
  real_T c2_HIGH_SP[4];
  real_T c2_HOT_COLD;
  uint32_T c2_debug_family_var_map[18];
  real_T c2_CriticalStates[4];
  real_T c2_DesiredStates[4];
  real_T c2_i;
  real_T c2_k;
  real_T c2_m;
  int32_T c2_des_sizes[2];
  real_T c2_des_data[4];
  real_T c2_minVal;
  real_T c2_maxVal;
  real_T c2_randIndex;
  real_T c2_nargin = 6.0;
  real_T c2_nargout = 1.0;
  real_T c2_VALVE_OUT[4];
  int32_T c2_i13;
  int32_T c2_i14;
  int32_T c2_i15;
  real_T c2_b_i;
  real_T c2_c_i;
  real_T c2_d_i;
  real_T c2_e_i;
  int32_T c2_i16;
  boolean_T c2_b_CriticalStates[4];
  int32_T c2_tmp_sizes[2];
  int32_T c2_tmp_data[4];
  int32_T c2_loop_ub;
  int32_T c2_i17;
  real_T c2_f_i;
  int32_T c2_i18;
  real_T c2_c_CriticalStates[4];
  int32_T c2_i19;
  real_T c2_b_DesiredStates[4];
  int32_T c2_i20;
  boolean_T c2_c_DesiredStates[4];
  int32_T c2_b_loop_ub;
  int32_T c2_i21;
  int32_T c2_i22;
  boolean_T c2_d_CriticalStates[4];
  int32_T c2_c_loop_ub;
  int32_T c2_i23;
  int32_T c2_i24;
  boolean_T c2_d_DesiredStates[4];
  int32_T c2_i25;
  boolean_T c2_e_DesiredStates[4];
  int32_T c2_b_tmp_sizes[2];
  int32_T c2_b_tmp_data[4];
  int32_T c2_c_tmp_sizes[2];
  int32_T c2_i26;
  int32_T c2_i27;
  int32_T c2_d_loop_ub;
  int32_T c2_i28;
  real_T c2_c_tmp_data[4];
  int32_T c2_e_loop_ub;
  int32_T c2_i29;
  int32_T c2_i30;
  real_T c2_f_DesiredStates[4];
  int32_T c2_i31;
  boolean_T c2_g_DesiredStates[4];
  int32_T c2_d_tmp_sizes[2];
  real_T c2_d_tmp_data[4];
  int32_T c2_des;
  int32_T c2_b_des;
  int32_T c2_f_loop_ub;
  int32_T c2_i32;
  real_T c2_a;
  real_T c2_b;
  real_T c2_y;
  real_T c2_x;
  real_T c2_b_x;
  int32_T c2_i33;
  boolean_T c2_h_DesiredStates[4];
  int32_T c2_g_loop_ub;
  int32_T c2_i34;
  int32_T c2_i35;
  real_T *c2_b_MAX_ALLOWED_ZONES;
  real_T *c2_b_HOT_COLD;
  real_T (*c2_b_VALVE_OUT)[4];
  real_T (*c2_b_HIGH_SP)[4];
  real_T (*c2_b_LOW_SP)[4];
  real_T (*c2_b_VALVE_IN)[4];
  real_T (*c2_b_TEMP_IN)[4];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T exitg1;
  c2_b_HOT_COLD = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c2_b_VALVE_OUT = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_HIGH_SP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
  c2_b_LOW_SP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
  c2_b_MAX_ALLOWED_ZONES = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_b_VALVE_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_TEMP_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_MAX_ALLOWED_ZONES;
  c2_b_hoistedGlobal = *c2_b_HOT_COLD;
  for (c2_i9 = 0; c2_i9 < 4; c2_i9++) {
    c2_TEMP_IN[c2_i9] = (*c2_b_TEMP_IN)[c2_i9];
  }

  for (c2_i10 = 0; c2_i10 < 4; c2_i10++) {
    c2_VALVE_IN[c2_i10] = (*c2_b_VALVE_IN)[c2_i10];
  }

  c2_MAX_ALLOWED_ZONES = c2_hoistedGlobal;
  for (c2_i11 = 0; c2_i11 < 4; c2_i11++) {
    c2_LOW_SP[c2_i11] = (*c2_b_LOW_SP)[c2_i11];
  }

  for (c2_i12 = 0; c2_i12 < 4; c2_i12++) {
    c2_HIGH_SP[c2_i12] = (*c2_b_HIGH_SP)[c2_i12];
  }

  c2_HOT_COLD = c2_b_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 18U, 18U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(c2_CriticalStates, 0U,
    c2_d_sf_marshallOut, c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_DesiredStates, 1U,
    c2_d_sf_marshallOut, c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_i, 2U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_k, 3U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_m, 4U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_dyn_importable(c2_des_data, (const int32_T *)
    &c2_des_sizes, NULL, 0, 5, (void *)c2_c_sf_marshallOut, (void *)
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_minVal, 6U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_maxVal, 7U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_randIndex, 8U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 9U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 10U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_TEMP_IN, 11U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_VALVE_IN, 12U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_MAX_ALLOWED_ZONES, 13U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_LOW_SP, 14U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_HIGH_SP, 15U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_HOT_COLD, 16U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_VALVE_OUT, 17U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  for (c2_i13 = 0; c2_i13 < 4; c2_i13++) {
    c2_CriticalStates[c2_i13] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  for (c2_i14 = 0; c2_i14 < 4; c2_i14++) {
    c2_DesiredStates[c2_i14] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  for (c2_i15 = 0; c2_i15 < 4; c2_i15++) {
    c2_VALVE_OUT[c2_i15] = c2_VALVE_IN[c2_i15];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
  if (CV_EML_IF(0, 0, c2_HOT_COLD == 0.0)) {
    c2_i = 1.0;
    c2_b_i = 1.0;
    while (c2_b_i <= 4.0) {
      c2_i = c2_b_i;
      CV_EML_FOR(0, 0, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 16);
      guard2 = FALSE;
      if (CV_EML_COND(0, 0, c2_TEMP_IN[(int32_T)c2_i - 1] <= c2_LOW_SP[(int32_T)
                      c2_i - 1])) {
        if (CV_EML_COND(0, 1, c2_VALVE_IN[(int32_T)c2_i - 1] <= 90.0)) {
          CV_EML_MCDC(0, 0, TRUE);
          CV_EML_IF(0, 1, TRUE);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 17);
          c2_VALVE_OUT[(int32_T)c2_i - 1] = 90.0;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 18);
          c2_VALVE_IN[(int32_T)c2_i - 1] = 90.0;
        } else {
          guard2 = TRUE;
        }
      } else {
        guard2 = TRUE;
      }

      if (guard2 == TRUE) {
        CV_EML_MCDC(0, 0, FALSE);
        CV_EML_IF(0, 1, FALSE);
      }

      c2_b_i++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 0, 0);
    c2_i = 1.0;
    c2_c_i = 1.0;
    while (c2_c_i <= 4.0) {
      c2_i = c2_c_i;
      CV_EML_FOR(0, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 26);
      if (CV_EML_IF(0, 2, c2_TEMP_IN[(int32_T)c2_i - 1] >= c2_HIGH_SP[(int32_T)
                    c2_i - 1])) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
        c2_CriticalStates[(int32_T)c2_i - 1] = 1.0;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
        c2_VALVE_OUT[(int32_T)c2_i - 1] = 0.0;
      }

      c2_c_i++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 0);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
    if (CV_EML_IF(0, 3, c2_HOT_COLD == 1.0)) {
      c2_i = 1.0;
      c2_d_i = 1.0;
      while (c2_d_i <= 4.0) {
        c2_i = c2_d_i;
        CV_EML_FOR(0, 2, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 39);
        guard1 = FALSE;
        if (CV_EML_COND(0, 2, c2_TEMP_IN[(int32_T)c2_i - 1] >= c2_HIGH_SP
                        [(int32_T)c2_i - 1])) {
          if (CV_EML_COND(0, 3, c2_VALVE_IN[(int32_T)c2_i - 1] <= 90.0)) {
            CV_EML_MCDC(0, 1, TRUE);
            CV_EML_IF(0, 4, TRUE);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 40);
            c2_VALVE_OUT[(int32_T)c2_i - 1] = 90.0;
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 41);
            c2_VALVE_IN[(int32_T)c2_i - 1] = 90.0;
          } else {
            guard1 = TRUE;
          }
        } else {
          guard1 = TRUE;
        }

        if (guard1 == TRUE) {
          CV_EML_MCDC(0, 1, FALSE);
          CV_EML_IF(0, 4, FALSE);
        }

        c2_d_i++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }

      CV_EML_FOR(0, 2, 0);
      c2_i = 1.0;
      c2_e_i = 1.0;
      while (c2_e_i <= 4.0) {
        c2_i = c2_e_i;
        CV_EML_FOR(0, 3, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 49);
        if (CV_EML_IF(0, 5, c2_TEMP_IN[(int32_T)c2_i - 1] <= c2_LOW_SP[(int32_T)
                      c2_i - 1])) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 50);
          c2_CriticalStates[(int32_T)c2_i - 1] = 1.0;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 51);
          c2_VALVE_OUT[(int32_T)c2_i - 1] = 0.0;
        }

        c2_e_i++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }

      CV_EML_FOR(0, 3, 0);
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 55);
  for (c2_i16 = 0; c2_i16 < 4; c2_i16++) {
    c2_b_CriticalStates[c2_i16] = (c2_CriticalStates[c2_i16] == 1.0);
  }

  c2_eml_li_find(chartInstance, c2_b_CriticalStates, c2_tmp_data, c2_tmp_sizes);
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i17 = 0; c2_i17 <= c2_loop_ub; c2_i17++) {
    c2_DesiredStates[c2_tmp_data[c2_i17] - 1] = 0.0;
  }

  c2_i = 1.0;
  c2_f_i = 1.0;
  while (c2_f_i <= 4.0) {
    c2_i = c2_f_i;
    CV_EML_FOR(0, 4, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 61);
    if (CV_EML_IF(0, 6, c2_VALVE_IN[(int32_T)c2_i - 1] < 90.0)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 62);
      c2_DesiredStates[(int32_T)c2_i - 1] = 1.0;
    }

    c2_f_i++;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 4, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 66);
  for (c2_i18 = 0; c2_i18 < 4; c2_i18++) {
    c2_c_CriticalStates[c2_i18] = c2_CriticalStates[c2_i18];
  }

  c2_k = c2_sum(chartInstance, c2_c_CriticalStates);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 67);
  for (c2_i19 = 0; c2_i19 < 4; c2_i19++) {
    c2_b_DesiredStates[c2_i19] = c2_DesiredStates[c2_i19];
  }

  c2_m = c2_sum(chartInstance, c2_b_DesiredStates);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 72);
  if (CV_EML_IF(0, 7, c2_k >= c2_MAX_ALLOWED_ZONES)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 73);
    for (c2_i20 = 0; c2_i20 < 4; c2_i20++) {
      c2_c_DesiredStates[c2_i20] = (c2_DesiredStates[c2_i20] == 1.0);
    }

    c2_eml_li_find(chartInstance, c2_c_DesiredStates, c2_tmp_data, c2_tmp_sizes);
    c2_b_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
    for (c2_i21 = 0; c2_i21 <= c2_b_loop_ub; c2_i21++) {
      c2_VALVE_OUT[c2_tmp_data[c2_i21] - 1] = 90.0;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 74);
    for (c2_i22 = 0; c2_i22 < 4; c2_i22++) {
      c2_d_CriticalStates[c2_i22] = (c2_CriticalStates[c2_i22] == 1.0);
    }

    c2_eml_li_find(chartInstance, c2_d_CriticalStates, c2_tmp_data, c2_tmp_sizes);
    c2_c_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
    for (c2_i23 = 0; c2_i23 <= c2_c_loop_ub; c2_i23++) {
      c2_VALVE_OUT[c2_tmp_data[c2_i23] - 1] = 0.0;
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 76);
    if (CV_EML_IF(0, 8, c2_m <= c2_MAX_ALLOWED_ZONES - c2_k)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 77);
      for (c2_i24 = 0; c2_i24 < 4; c2_i24++) {
        c2_d_DesiredStates[c2_i24] = (c2_DesiredStates[c2_i24] == 1.0);
      }

      c2_eml_li_find(chartInstance, c2_d_DesiredStates, c2_tmp_data,
                     c2_tmp_sizes);
      for (c2_i25 = 0; c2_i25 < 4; c2_i25++) {
        c2_e_DesiredStates[c2_i25] = (c2_DesiredStates[c2_i25] == 1.0);
      }

      c2_eml_li_find(chartInstance, c2_e_DesiredStates, c2_b_tmp_data,
                     c2_b_tmp_sizes);
      c2_c_tmp_sizes[0] = 1;
      c2_c_tmp_sizes[1] = c2_b_tmp_sizes[1];
      c2_i26 = c2_c_tmp_sizes[0];
      c2_i27 = c2_c_tmp_sizes[1];
      c2_d_loop_ub = c2_b_tmp_sizes[0] * c2_b_tmp_sizes[1] - 1;
      for (c2_i28 = 0; c2_i28 <= c2_d_loop_ub; c2_i28++) {
        c2_c_tmp_data[c2_i28] = c2_VALVE_IN[c2_b_tmp_data[c2_i28] - 1];
      }

      sf_debug_size_eq_check_1d(c2_tmp_sizes[1], c2_c_tmp_sizes[1]);
      c2_e_loop_ub = c2_c_tmp_sizes[0] * c2_c_tmp_sizes[1] - 1;
      for (c2_i29 = 0; c2_i29 <= c2_e_loop_ub; c2_i29++) {
        c2_VALVE_OUT[c2_tmp_data[c2_i29] - 1] = c2_c_tmp_data[c2_i29];
      }
    } else {
      exitg1 = 0U;
      while ((exitg1 == 0U) && (c2_k < c2_MAX_ALLOWED_ZONES)) {
        for (c2_i30 = 0; c2_i30 < 4; c2_i30++) {
          c2_f_DesiredStates[c2_i30] = c2_DesiredStates[c2_i30];
        }

        if (c2_sum(chartInstance, c2_f_DesiredStates) > 0.0) {
          CV_EML_WHILE(0, 0, TRUE);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 80);
          for (c2_i31 = 0; c2_i31 < 4; c2_i31++) {
            c2_g_DesiredStates[c2_i31] = (c2_DesiredStates[c2_i31] == 1.0);
          }

          c2_find(chartInstance, c2_g_DesiredStates, c2_d_tmp_data,
                  c2_d_tmp_sizes);
          c2_des_sizes[0] = 1;
          c2_des_sizes[1] = c2_d_tmp_sizes[1];
          c2_des = c2_des_sizes[0];
          c2_b_des = c2_des_sizes[1];
          c2_f_loop_ub = c2_d_tmp_sizes[0] * c2_d_tmp_sizes[1] - 1;
          for (c2_i32 = 0; c2_i32 <= c2_f_loop_ub; c2_i32++) {
            c2_des_data[c2_i32] = c2_d_tmp_data[c2_i32];
          }

          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 81);
          c2_minVal = 1.0;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 82);
          c2_maxVal = (real_T)c2_des_sizes[1];
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 83);
          c2_a = c2_rand(chartInstance);
          c2_b = c2_maxVal - 1.0;
          c2_y = c2_a * c2_b;
          c2_x = 1.0 + c2_y;
          c2_randIndex = c2_x;
          c2_b_x = c2_randIndex;
          c2_randIndex = c2_b_x;
          c2_randIndex = muDoubleScalarCeil(c2_randIndex);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 84);
          c2_VALVE_OUT[(int32_T)c2_des_data[_SFD_EML_ARRAY_BOUNDS_CHECK("des",
            (int32_T)c2_randIndex, 1, c2_des_sizes[1], 1, 0) - 1] - 1] = 0.0;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 85);
          c2_DesiredStates[(int32_T)c2_des_data[_SFD_EML_ARRAY_BOUNDS_CHECK(
            "des", (int32_T)c2_randIndex, 1, c2_des_sizes[1], 1, 0) - 1] - 1] =
            0.0;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 86);
          c2_k++;
          sf_mex_listen_for_ctrl_c(chartInstance->S);
        } else {
          exitg1 = 1U;
        }
      }

      CV_EML_WHILE(0, 0, FALSE);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 88);
      for (c2_i33 = 0; c2_i33 < 4; c2_i33++) {
        c2_h_DesiredStates[c2_i33] = (c2_DesiredStates[c2_i33] == 1.0);
      }

      c2_eml_li_find(chartInstance, c2_h_DesiredStates, c2_tmp_data,
                     c2_tmp_sizes);
      c2_g_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
      for (c2_i34 = 0; c2_i34 <= c2_g_loop_ub; c2_i34++) {
        c2_VALVE_OUT[c2_tmp_data[c2_i34] - 1] = 90.0;
      }
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -88);
  sf_debug_symbol_scope_pop();
  for (c2_i35 = 0; c2_i35 < 4; c2_i35++) {
    (*c2_b_VALVE_OUT)[c2_i35] = c2_VALVE_OUT[c2_i35];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_ON_OFF_LAZY(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i36;
  real_T c2_b_inData[4];
  int32_T c2_i37;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i36 = 0; c2_i36 < 4; c2_i36++) {
    c2_b_inData[c2_i36] = (*(real_T (*)[4])c2_inData)[c2_i36];
  }

  for (c2_i37 = 0; c2_i37 < 4; c2_i37++) {
    c2_u[c2_i37] = c2_b_inData[c2_i37];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_VALVE_OUT, const char_T *c2_identifier, real_T c2_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_VALVE_OUT), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_VALVE_OUT);
}

static void c2_b_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4])
{
  real_T c2_dv1[4];
  int32_T c2_i38;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv1, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i38 = 0; c2_i38 < 4; c2_i38++) {
    c2_y[c2_i38] = c2_dv1[c2_i38];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_VALVE_OUT;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i39;
  SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *)chartInstanceVoid;
  c2_VALVE_OUT = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_VALVE_OUT), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_VALVE_OUT);
  for (c2_i39 = 0; c2_i39 < 4; c2_i39++) {
    (*(real_T (*)[4])c2_outData)[c2_i39] = c2_y[c2_i39];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, real_T
  c2_inData_data[4], int32_T c2_inData_sizes[2])
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_b_inData_sizes[2];
  int32_T c2_loop_ub;
  int32_T c2_i40;
  real_T c2_b_inData_data[4];
  int32_T c2_u_sizes[2];
  int32_T c2_b_loop_ub;
  int32_T c2_i41;
  real_T c2_u_data[4];
  const mxArray *c2_y = NULL;
  SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_inData_sizes[0] = 1;
  c2_b_inData_sizes[1] = c2_inData_sizes[1];
  c2_loop_ub = c2_inData_sizes[1] - 1;
  for (c2_i40 = 0; c2_i40 <= c2_loop_ub; c2_i40++) {
    c2_b_inData_data[c2_b_inData_sizes[0] * c2_i40] =
      c2_inData_data[c2_inData_sizes[0] * c2_i40];
  }

  c2_u_sizes[0] = 1;
  c2_u_sizes[1] = c2_b_inData_sizes[1];
  c2_b_loop_ub = c2_b_inData_sizes[1] - 1;
  for (c2_i41 = 0; c2_i41 <= c2_b_loop_ub; c2_i41++) {
    c2_u_data[c2_u_sizes[0] * c2_i41] = c2_b_inData_data[c2_b_inData_sizes[0] *
      c2_i41];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u_data, 0, 0U, 1U, 0U, 2,
    c2_u_sizes[0], c2_u_sizes[1]));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static void c2_d_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y_data[4],
  int32_T c2_y_sizes[2])
{
  int32_T c2_i42;
  uint32_T c2_uv1[2];
  int32_T c2_i43;
  static boolean_T c2_bv0[2] = { FALSE, TRUE };

  boolean_T c2_bv1[2];
  int32_T c2_tmp_sizes[2];
  real_T c2_tmp_data[4];
  int32_T c2_y;
  int32_T c2_b_y;
  int32_T c2_loop_ub;
  int32_T c2_i44;
  for (c2_i42 = 0; c2_i42 < 2; c2_i42++) {
    c2_uv1[c2_i42] = 1U + 3U * (uint32_T)c2_i42;
  }

  for (c2_i43 = 0; c2_i43 < 2; c2_i43++) {
    c2_bv1[c2_i43] = c2_bv0[c2_i43];
  }

  sf_mex_import_vs(c2_parentId, sf_mex_dup(c2_u), c2_tmp_data, 1, 0, 0U, 1, 0U,
                   2, c2_bv1, c2_uv1, c2_tmp_sizes);
  c2_y_sizes[0] = 1;
  c2_y_sizes[1] = c2_tmp_sizes[1];
  c2_y = c2_y_sizes[0];
  c2_b_y = c2_y_sizes[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i44 = 0; c2_i44 <= c2_loop_ub; c2_i44++) {
    c2_y_data[c2_i44] = c2_tmp_data[c2_i44];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, real_T c2_outData_data[4],
  int32_T c2_outData_sizes[2])
{
  const mxArray *c2_des;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y_sizes[2];
  real_T c2_y_data[4];
  int32_T c2_loop_ub;
  int32_T c2_i45;
  SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *)chartInstanceVoid;
  c2_des = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_des), &c2_thisId, c2_y_data,
                        c2_y_sizes);
  sf_mex_destroy(&c2_des);
  c2_outData_sizes[0] = 1;
  c2_outData_sizes[1] = c2_y_sizes[1];
  c2_loop_ub = c2_y_sizes[1] - 1;
  for (c2_i45 = 0; c2_i45 <= c2_loop_ub; c2_i45++) {
    c2_outData_data[c2_outData_sizes[0] * c2_i45] = c2_y_data[c2_y_sizes[0] *
      c2_i45];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i46;
  real_T c2_b_inData[4];
  int32_T c2_i47;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i46 = 0; c2_i46 < 4; c2_i46++) {
    c2_b_inData[c2_i46] = (*(real_T (*)[4])c2_inData)[c2_i46];
  }

  for (c2_i47 = 0; c2_i47 < 4; c2_i47++) {
    c2_u[c2_i47] = c2_b_inData[c2_i47];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 4));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4])
{
  real_T c2_dv2[4];
  int32_T c2_i48;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv2, 1, 0, 0U, 1, 0U, 2, 1, 4);
  for (c2_i48 = 0; c2_i48 < 4; c2_i48++) {
    c2_y[c2_i48] = c2_dv2[c2_i48];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_DesiredStates;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i49;
  SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *)chartInstanceVoid;
  c2_DesiredStates = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_DesiredStates), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_DesiredStates);
  for (c2_i49 = 0; c2_i49 < 4; c2_i49++) {
    (*(real_T (*)[4])c2_outData)[c2_i49] = c2_y[c2_i49];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_ON_OFF_LAZY_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[19];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i50;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 19));
  for (c2_i50 = 0; c2_i50 < 19; c2_i50++) {
    c2_r0 = &c2_info[c2_i50];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i50);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i50);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i50);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i50);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i50);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i50);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i50);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i50);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[19])
{
  c2_info[0].context = "";
  c2_info[0].name = "sum";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[0].fileTimeLo = 1286840300U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 0U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[1].name = "isequal";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[1].fileTimeLo = 1286840358U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 0U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[2].name = "eml_isequal_core";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c2_info[2].fileTimeLo = 1286840386U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[3].name = "eml_const_nonsingleton_dim";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c2_info[3].fileTimeLo = 1286840296U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[4].name = "eml_scalar_eg";
  c2_info[4].dominantType = "double";
  c2_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[4].fileTimeLo = 1286840396U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[5].name = "eml_index_class";
  c2_info[5].dominantType = "";
  c2_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[5].fileTimeLo = 1286840378U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context = "";
  c2_info[6].name = "eml_li_find";
  c2_info[6].dominantType = "";
  c2_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m";
  c2_info[6].fileTimeLo = 1286840386U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 0U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m!compute_nones";
  c2_info[7].name = "eml_index_plus";
  c2_info[7].dominantType = "int32";
  c2_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[7].fileTimeLo = 1286840378U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context = "";
  c2_info[8].name = "find";
  c2_info[8].dominantType = "logical";
  c2_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/find.m";
  c2_info[8].fileTimeLo = 1286840288U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context = "";
  c2_info[9].name = "rand";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/rand.m";
  c2_info[9].fileTimeLo = 1286840366U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/rand.m";
  c2_info[10].name = "eml_rand_mt19937ar";
  c2_info[10].dominantType = "char";
  c2_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rand_mt19937ar.m";
  c2_info[10].fileTimeLo = 1286840392U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rand_mt19937ar.m!genrandu";
  c2_info[11].name = "eps";
  c2_info[11].dominantType = "";
  c2_info[11].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[11].fileTimeLo = 1286840286U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[12].name = "eml_is_float_class";
  c2_info[12].dominantType = "char";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c2_info[12].fileTimeLo = 1286840382U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c2_info[13].name = "isnan";
  c2_info[13].dominantType = "double";
  c2_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[13].fileTimeLo = 1286840360U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rand_mt19937ar.m!genrandu";
  c2_info[14].name = "mtimes";
  c2_info[14].dominantType = "double";
  c2_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[14].fileTimeLo = 1289541292U;
  c2_info[14].fileTimeHi = 0U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rand_mt19937ar.m!genrandu";
  c2_info[15].name = "eml_error";
  c2_info[15].dominantType = "char";
  c2_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c2_info[15].fileTimeLo = 1286840300U;
  c2_info[15].fileTimeHi = 0U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
  c2_info[16].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/rand.m";
  c2_info[16].name = "eml_rand_mcg16807";
  c2_info[16].dominantType = "char";
  c2_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rand_mcg16807.m";
  c2_info[16].fileTimeLo = 1286840392U;
  c2_info[16].fileTimeHi = 0U;
  c2_info[16].mFileTimeLo = 0U;
  c2_info[16].mFileTimeHi = 0U;
  c2_info[17].context = "";
  c2_info[17].name = "ceil";
  c2_info[17].dominantType = "double";
  c2_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/ceil.m";
  c2_info[17].fileTimeLo = 1286840306U;
  c2_info[17].fileTimeHi = 0U;
  c2_info[17].mFileTimeLo = 0U;
  c2_info[17].mFileTimeHi = 0U;
  c2_info[18].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/ceil.m";
  c2_info[18].name = "eml_scalar_ceil";
  c2_info[18].dominantType = "double";
  c2_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_ceil.m";
  c2_info[18].fileTimeLo = 1286840320U;
  c2_info[18].fileTimeHi = 0U;
  c2_info[18].mFileTimeLo = 0U;
  c2_info[18].mFileTimeHi = 0U;
}

static real_T c2_sum(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance, real_T c2_x
                     [4])
{
  real_T c2_y;
  int32_T c2_k;
  int32_T c2_b_k;
  c2_y = c2_x[0];
  for (c2_k = 1; c2_k + 1 < 5; c2_k++) {
    c2_b_k = c2_k;
    c2_y += c2_x[c2_b_k];
  }

  return c2_y;
}

static void c2_eml_li_find(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  boolean_T c2_x[4], int32_T c2_y_data[4], int32_T c2_y_sizes[2])
{
  int32_T c2_k;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_a;
  const mxArray *c2_y = NULL;
  int32_T c2_tmp_sizes[2];
  int32_T c2_iv0[2];
  int32_T c2_i51;
  int32_T c2_i52;
  int32_T c2_loop_ub;
  int32_T c2_i53;
  int32_T c2_tmp_data[4];
  int32_T c2_i54;
  int32_T c2_j;
  int32_T c2_c_i;
  int32_T c2_d_i;
  int32_T c2_b_a;
  c2_k = 0;
  for (c2_i = 0; c2_i + 1 < 5; c2_i++) {
    c2_b_i = c2_i;
    if (c2_x[c2_b_i]) {
      c2_a = c2_k + 1;
      c2_k = c2_a;
    }
  }

  if (c2_k <= 4) {
  } else {
    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", "Assertion failed.", 15, 0U, 0U, 0U,
      2, 1, strlen("Assertion failed.")));
    sf_mex_call_debug("error", 0U, 1U, 14, c2_y);
  }

  c2_tmp_sizes[0] = 1;
  c2_iv0[0] = 1;
  c2_iv0[1] = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c2_k);
  c2_tmp_sizes[1] = c2_iv0[1];
  c2_i51 = c2_tmp_sizes[0];
  c2_i52 = c2_tmp_sizes[1];
  c2_loop_ub = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c2_k) - 1;
  for (c2_i53 = 0; c2_i53 <= c2_loop_ub; c2_i53++) {
    c2_tmp_data[c2_i53] = 0;
  }

  for (c2_i54 = 0; c2_i54 < 2; c2_i54++) {
    c2_y_sizes[c2_i54] = c2_tmp_sizes[c2_i54];
  }

  c2_j = 1;
  for (c2_c_i = 1; c2_c_i < 5; c2_c_i++) {
    c2_d_i = c2_c_i;
    if (c2_x[c2_d_i - 1]) {
      c2_y_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c2_j, 1, c2_y_sizes[1], 1, 0) -
        1] = c2_d_i;
      c2_b_a = c2_j + 1;
      c2_j = c2_b_a;
    }
  }
}

static void c2_find(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance, boolean_T
                    c2_x[4], real_T c2_i_data[4], int32_T c2_i_sizes[2])
{
  real_T c2_idx;
  int32_T c2_i55;
  real_T c2_ii;
  real_T c2_b_ii;
  boolean_T c2_b0;
  boolean_T c2_b1;
  boolean_T c2_b2;
  int32_T c2_i56;
  int32_T c2_tmp_sizes;
  int32_T c2_loop_ub;
  int32_T c2_i57;
  int32_T c2_tmp_data[4];
  int32_T c2_iv1[2];
  int32_T c2_b_i_sizes[2];
  int32_T c2_b_loop_ub;
  int32_T c2_i58;
  int32_T c2_c_loop_ub;
  int32_T c2_i59;
  real_T c2_b_i_data[4];
  int32_T c2_d_loop_ub;
  int32_T c2_i60;
  boolean_T exitg1;
  boolean_T guard1 = FALSE;
  c2_idx = 0.0;
  for (c2_i55 = 0; c2_i55 < 2; c2_i55++) {
    c2_i_sizes[c2_i55] = 1 + 3 * c2_i55;
  }

  c2_ii = 1.0;
  exitg1 = 0U;
  while ((exitg1 == 0U) && (c2_ii <= 4.0)) {
    c2_b_ii = c2_ii;
    guard1 = FALSE;
    if (c2_x[(int32_T)c2_b_ii - 1]) {
      c2_idx++;
      c2_i_data[(int32_T)c2_idx - 1] = c2_b_ii;
      if (c2_idx >= 4.0) {
        exitg1 = 1U;
      } else {
        guard1 = TRUE;
      }
    } else {
      guard1 = TRUE;
    }

    if (guard1 == TRUE) {
      c2_ii++;
    }
  }

  c2_b0 = (1.0 > c2_idx);
  c2_b1 = c2_b0;
  c2_b2 = c2_b1;
  if (c2_b2) {
    c2_i56 = 0;
  } else {
    c2_i56 = _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)c2_idx, 1, 4, 0, 0);
  }

  c2_tmp_sizes = c2_i56;
  c2_loop_ub = c2_i56 - 1;
  for (c2_i57 = 0; c2_i57 <= c2_loop_ub; c2_i57++) {
    c2_tmp_data[c2_i57] = 1 + c2_i57;
  }

  c2_iv1[0] = 1;
  c2_iv1[1] = c2_tmp_sizes;
  c2_b_i_sizes[0] = c2_iv1[0];
  c2_b_i_sizes[1] = c2_iv1[1];
  c2_b_loop_ub = c2_iv1[1] - 1;
  for (c2_i58 = 0; c2_i58 <= c2_b_loop_ub; c2_i58++) {
    c2_c_loop_ub = c2_iv1[0] - 1;
    for (c2_i59 = 0; c2_i59 <= c2_c_loop_ub; c2_i59++) {
      c2_b_i_data[c2_i59 + c2_b_i_sizes[0] * c2_i58] =
        c2_i_data[c2_tmp_data[c2_i59 + c2_iv1[0] * c2_i58] - 1];
    }
  }

  c2_i_sizes[0] = 1;
  c2_i_sizes[1] = c2_b_i_sizes[1];
  c2_d_loop_ub = c2_b_i_sizes[1] - 1;
  for (c2_i60 = 0; c2_i60 <= c2_d_loop_ub; c2_i60++) {
    c2_i_data[c2_i_sizes[0] * c2_i60] = c2_b_i_data[c2_b_i_sizes[0] * c2_i60];
  }
}

static real_T c2_rand(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance)
{
  uint32_T c2_uv2[625];
  int32_T c2_i61;
  int32_T c2_i62;
  uint32_T c2_b_twister_state[625];
  real_T c2_d1;
  int32_T c2_i63;
  if (!chartInstance->c2_method_not_empty) {
    chartInstance->c2_method = 2U;
    chartInstance->c2_method_not_empty = TRUE;
  }

  if (!chartInstance->c2_twister_state_not_empty) {
    c2_eml_rand_mt19937ar(chartInstance, c2_uv2);
    for (c2_i61 = 0; c2_i61 < 625; c2_i61++) {
      chartInstance->c2_twister_state[c2_i61] = c2_uv2[c2_i61];
    }

    chartInstance->c2_twister_state_not_empty = TRUE;
  }

  for (c2_i62 = 0; c2_i62 < 625; c2_i62++) {
    c2_b_twister_state[c2_i62] = chartInstance->c2_twister_state[c2_i62];
  }

  c2_d1 = c2_c_eml_rand_mt19937ar(chartInstance, c2_b_twister_state);
  for (c2_i63 = 0; c2_i63 < 625; c2_i63++) {
    chartInstance->c2_twister_state[c2_i63] = c2_b_twister_state[c2_i63];
  }

  return c2_d1;
}

static void c2_eml_rand_mt19937ar(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  uint32_T c2_state[625])
{
  int32_T c2_i64;
  for (c2_i64 = 0; c2_i64 < 625; c2_i64++) {
    c2_state[c2_i64] = 0U;
  }

  c2_b_twister_state_vector(chartInstance, c2_state, 5489.0);
}

static void c2_twister_state_vector(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, uint32_T c2_mt[625], real_T c2_seed, uint32_T c2_b_mt[625])
{
  int32_T c2_i65;
  for (c2_i65 = 0; c2_i65 < 625; c2_i65++) {
    c2_b_mt[c2_i65] = c2_mt[c2_i65];
  }

  c2_b_twister_state_vector(chartInstance, c2_b_mt, c2_seed);
}

static void c2_b_eml_rand_mt19937ar(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, uint32_T c2_state[625], uint32_T c2_b_state[625], real_T *c2_r)
{
  int32_T c2_i66;
  for (c2_i66 = 0; c2_i66 < 625; c2_i66++) {
    c2_b_state[c2_i66] = c2_state[c2_i66];
  }

  *c2_r = c2_c_eml_rand_mt19937ar(chartInstance, c2_b_state);
}

static void c2_eml_error(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance)
{
  int32_T c2_i67;
  static char_T c2_varargin_1[37] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'r', 'a', 'n', 'd', '_', 'i', 'n', 'v', 'a', 'l',
    'i', 'd', 'T', 'w', 'i', 's', 't', 'e', 'r', 'S', 't', 'a', 't', 'e' };

  char_T c2_u[37];
  const mxArray *c2_y = NULL;
  for (c2_i67 = 0; c2_i67 < 37; c2_i67++) {
    c2_u[c2_i67] = c2_varargin_1[c2_i67];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 37));
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c2_y));
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static int32_T c2_f_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i68;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i68, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i68;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_g_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_b_method, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_method),
    &c2_thisId);
  sf_mex_destroy(&c2_b_method);
  return c2_y;
}

static uint8_T c2_h_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_method_not_empty = FALSE;
  } else {
    chartInstance->c2_method_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
    c2_y = c2_u0;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_i_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_b_twister_state, const char_T *c2_identifier, uint32_T c2_y
  [625])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_twister_state),
                        &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_twister_state);
}

static void c2_j_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, uint32_T c2_y[625])
{
  uint32_T c2_uv3[625];
  int32_T c2_i69;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_twister_state_not_empty = FALSE;
  } else {
    chartInstance->c2_twister_state_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_uv3, 1, 7, 0U, 1, 0U, 1, 625);
    for (c2_i69 = 0; c2_i69 < 625; c2_i69++) {
      c2_y[c2_i69] = c2_uv3[c2_i69];
    }
  }

  sf_mex_destroy(&c2_u);
}

static uint32_T c2_k_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_b_v4_state, const char_T *c2_identifier)
{
  uint32_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_v4_state),
    &c2_thisId);
  sf_mex_destroy(&c2_b_v4_state);
  return c2_y;
}

static uint32_T c2_l_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint32_T c2_y;
  uint32_T c2_u1;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_v4_state_not_empty = FALSE;
  } else {
    chartInstance->c2_v4_state_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u1, 1, 7, 0U, 0, 0U, 0);
    c2_y = c2_u1;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static uint8_T c2_m_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_ON_OFF_LAZY, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_ON_OFF_LAZY), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_ON_OFF_LAZY);
  return c2_y;
}

static uint8_T c2_n_emlrt_marshallIn(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u2;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u2, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u2;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_twister_state_vector(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, uint32_T c2_mt[625], real_T c2_seed)
{
  uint32_T c2_r;
  real_T c2_mti;
  real_T c2_b_mti;
  real_T c2_d2;
  real_T c2_d3;
  real_T c2_d4;
  uint32_T c2_u3;
  c2_r = 5489U;
  c2_mt[0] = 5489U;
  for (c2_mti = 2.0; c2_mti <= 624.0; c2_mti++) {
    c2_b_mti = c2_mti;
    c2_d2 = c2_b_mti - 1.0;
    c2_d3 = c2_d2;
    c2_d3 = c2_d3 < 0.0 ? muDoubleScalarCeil(c2_d3 - 0.5) : muDoubleScalarFloor
      (c2_d3 + 0.5);
    c2_d4 = c2_d3;
    if (c2_d4 < 4.294967296E+9) {
      if (c2_d4 >= 0.0) {
        c2_u3 = (uint32_T)c2_d4;
      } else {
        c2_u3 = 0U;
      }
    } else if (c2_d4 >= 4.294967296E+9) {
      c2_u3 = MAX_uint32_T;
    } else {
      c2_u3 = 0U;
    }

    c2_r = (c2_r ^ c2_r >> 30U) * 1812433253U + c2_u3;
    c2_mt[(int32_T)c2_b_mti - 1] = c2_r;
  }

  c2_mt[624] = 624U;
}

static real_T c2_c_eml_rand_mt19937ar(SFc2_ON_OFF_LAZYInstanceStruct
  *chartInstance, uint32_T c2_state[625])
{
  int32_T c2_i70;
  uint32_T c2_u[2];
  real_T c2_j;
  real_T c2_b_j;
  uint32_T c2_mti;
  real_T c2_kk;
  real_T c2_b_kk;
  uint32_T c2_y;
  uint32_T c2_b_y;
  uint32_T c2_c_y;
  real_T c2_c_kk;
  uint32_T c2_d_y;
  uint32_T c2_e_y;
  uint32_T c2_f_y;
  uint32_T c2_g_y;
  real_T c2_a;
  real_T c2_h_y;
  real_T c2_b;
  real_T c2_b_r;
  boolean_T c2_b3;
  boolean_T c2_isvalid;
  int32_T c2_k;
  int32_T c2_b_a;
  boolean_T guard1 = FALSE;
  int32_T exitg1;
  boolean_T exitg2;

  /* <LEGAL>   This is a uniform (0,1) pseudorandom number generator based on: */
  /* <LEGAL> */
  /* <LEGAL>    A C-program for MT19937, with initialization improved 2002/1/26. */
  /* <LEGAL>    Coded by Takuji Nishimura and Makoto Matsumoto. */
  /* <LEGAL> */
  /* <LEGAL>    Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura, */
  /* <LEGAL>    All rights reserved. */
  /* <LEGAL> */
  /* <LEGAL>    Redistribution and use in source and binary forms, with or without */
  /* <LEGAL>    modification, are permitted provided that the following conditions */
  /* <LEGAL>    are met: */
  /* <LEGAL> */
  /* <LEGAL>      1. Redistributions of source code must retain the above copyright */
  /* <LEGAL>         notice, this list of conditions and the following disclaimer. */
  /* <LEGAL> */
  /* <LEGAL>      2. Redistributions in binary form must reproduce the above copyright */
  /* <LEGAL>         notice, this list of conditions and the following disclaimer in the */
  /* <LEGAL>         documentation and/or other materials provided with the distribution. */
  /* <LEGAL> */
  /* <LEGAL>      3. The names of its contributors may not be used to endorse or promote */
  /* <LEGAL>         products derived from this software without specific prior written */
  /* <LEGAL>         permission. */
  /* <LEGAL> */
  /* <LEGAL>    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS */
  /* <LEGAL>    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT */
  /* <LEGAL>    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR */
  /* <LEGAL>    A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR */
  /* <LEGAL>    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, */
  /* <LEGAL>    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, */
  /* <LEGAL>    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR */
  /* <LEGAL>    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF */
  /* <LEGAL>    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING */
  /* <LEGAL>    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS */
  /* <LEGAL>    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
  do {
    exitg1 = 0U;
    for (c2_i70 = 0; c2_i70 < 2; c2_i70++) {
      c2_u[c2_i70] = 0U;
    }

    for (c2_j = 1.0; c2_j <= 2.0; c2_j++) {
      c2_b_j = c2_j;
      c2_mti = c2_state[624] + 1U;
      if ((real_T)c2_mti >= 625.0) {
        for (c2_kk = 1.0; c2_kk <= 227.0; c2_kk++) {
          c2_b_kk = c2_kk;
          c2_y = (c2_state[(int32_T)c2_b_kk - 1] & 2147483648U) | (c2_state
            [(int32_T)(c2_b_kk + 1.0) - 1] & 2147483647U);
          c2_b_y = c2_y;
          c2_c_y = c2_b_y;
          if ((real_T)(c2_c_y & 1U) == 0.0) {
            c2_c_y >>= 1U;
          } else {
            c2_c_y = c2_c_y >> 1U ^ 2567483615U;
          }

          c2_state[(int32_T)c2_b_kk - 1] = c2_state[(int32_T)(c2_b_kk + 397.0) -
            1] ^ c2_c_y;
        }

        for (c2_c_kk = 228.0; c2_c_kk <= 623.0; c2_c_kk++) {
          c2_b_kk = c2_c_kk;
          c2_y = (c2_state[(int32_T)c2_b_kk - 1] & 2147483648U) | (c2_state
            [(int32_T)(c2_b_kk + 1.0) - 1] & 2147483647U);
          c2_d_y = c2_y;
          c2_e_y = c2_d_y;
          if ((real_T)(c2_e_y & 1U) == 0.0) {
            c2_e_y >>= 1U;
          } else {
            c2_e_y = c2_e_y >> 1U ^ 2567483615U;
          }

          c2_state[(int32_T)c2_b_kk - 1] = c2_state[(int32_T)((c2_b_kk + 1.0) -
            228.0) - 1] ^ c2_e_y;
        }

        c2_y = (c2_state[623] & 2147483648U) | (c2_state[0] & 2147483647U);
        c2_f_y = c2_y;
        c2_g_y = c2_f_y;
        if ((real_T)(c2_g_y & 1U) == 0.0) {
          c2_g_y >>= 1U;
        } else {
          c2_g_y = c2_g_y >> 1U ^ 2567483615U;
        }

        c2_state[623] = c2_state[396] ^ c2_g_y;
        c2_mti = 1U;
      }

      c2_y = c2_state[(int32_T)(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)c2_mti, 1, 625, 1, 0) - 1];
      c2_state[624] = c2_mti;
      c2_y ^= c2_y >> 11U;
      c2_y ^= c2_y << 7U & 2636928640U;
      c2_y ^= c2_y << 15U & 4022730752U;
      c2_y ^= c2_y >> 18U;
      c2_u[(int32_T)c2_b_j - 1] = c2_y;
    }

    c2_u[0] >>= 5U;
    c2_u[1] >>= 6U;
    c2_a = (real_T)c2_u[0];
    c2_h_y = c2_a * 6.7108864E+7;
    c2_b = c2_h_y + (real_T)c2_u[1];
    c2_b_r = 1.1102230246251565E-16 * c2_b;
    if (c2_b_r == 0.0) {
      guard1 = FALSE;
      if ((real_T)c2_state[624] >= 1.0) {
        if ((real_T)c2_state[624] < 625.0) {
          c2_b3 = TRUE;
        } else {
          guard1 = TRUE;
        }
      } else {
        guard1 = TRUE;
      }

      if (guard1 == TRUE) {
        c2_b3 = FALSE;
      }

      c2_isvalid = c2_b3;
      if (c2_isvalid) {
        c2_isvalid = FALSE;
        c2_k = 0;
        exitg2 = 0U;
        while ((exitg2 == 0U) && ((real_T)(c2_k + 1) < 625.0)) {
          if ((real_T)c2_state[c2_k] == 0.0) {
            c2_b_a = c2_k;
            c2_k = c2_b_a + 1;
          } else {
            c2_isvalid = TRUE;
            exitg2 = 1U;
          }
        }
      }

      if (!c2_isvalid) {
        c2_eml_error(chartInstance);
        c2_b_twister_state_vector(chartInstance, c2_state, 5489.0);
      }
    } else {
      exitg1 = 1U;
    }
  } while (exitg1 == 0U);

  return c2_b_r;
}

static void init_dsm_address_info(SFc2_ON_OFF_LAZYInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_ON_OFF_LAZY_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3660394152U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1278818623U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3880163415U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(78540149U);
}

mxArray *sf_c2_ON_OFF_LAZY_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(2840127774U);
    pr[1] = (double)(1592080268U);
    pr[2] = (double)(133344261U);
    pr[3] = (double)(877236328U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c2_ON_OFF_LAZY(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[10],T\"VALVE_OUT\",},{M[4],M[0],T\"method\",S'l','i','p'{{M1x2[393 399],M[1],T\"/Applications/MATLAB_R2011a_Student.app/toolbox/eml/lib/matlab/elmat/rand.m\"}}},{M[4],M[0],T\"twister_state\",S'l','i','p'{{M1x2[409 422],M[1],T\"/Applications/MATLAB_R2011a_Student.app/toolbox/eml/lib/matlab/elmat/rand.m\"}}},{M[4],M[0],T\"v4_state\",S'l','i','p'{{M1x2[400 408],M[1],T\"/Applications/MATLAB_R2011a_Student.app/toolbox/eml/lib/matlab/elmat/rand.m\"}}},{M[8],M[0],T\"is_active_c2_ON_OFF_LAZY\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_ON_OFF_LAZY_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
    chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_ON_OFF_LAZYMachineNumber_,
           2,
           1,
           1,
           7,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_ON_OFF_LAZYMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_ON_OFF_LAZYMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_ON_OFF_LAZYMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"TEMP_IN");
          _SFD_SET_DATA_PROPS(1,1,1,0,"VALVE_IN");
          _SFD_SET_DATA_PROPS(2,1,1,0,"MAX_ALLOWED_ZONES");
          _SFD_SET_DATA_PROPS(3,1,1,0,"LOW_SP");
          _SFD_SET_DATA_PROPS(4,1,1,0,"HIGH_SP");
          _SFD_SET_DATA_PROPS(5,2,0,1,"VALVE_OUT");
          _SFD_SET_DATA_PROPS(6,1,1,0,"HOT_COLD");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,9,0,0,5,1,4,2);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2864);
        _SFD_CV_INIT_EML_IF(0,0,262,278,749,769);
        _SFD_CV_INIT_EML_IF(0,1,362,409,-1,526);
        _SFD_CV_INIT_EML_IF(0,2,618,645,-1,722);
        _SFD_CV_INIT_EML_IF(0,3,749,769,-1,769);
        _SFD_CV_INIT_EML_IF(0,4,854,902,-1,1019);
        _SFD_CV_INIT_EML_IF(0,5,1111,1137,-1,1214);
        _SFD_CV_INIT_EML_IF(0,6,1321,1340,-1,1378);
        _SFD_CV_INIT_EML_IF(0,7,1466,1491,1688,2860);
        _SFD_CV_INIT_EML_IF(0,8,1697,1730,1875,2856);
        _SFD_CV_INIT_EML_FOR(0,0,342,354,535);
        _SFD_CV_INIT_EML_FOR(0,1,598,610,734);
        _SFD_CV_INIT_EML_FOR(0,2,834,846,1028);
        _SFD_CV_INIT_EML_FOR(0,3,1091,1103,1226);
        _SFD_CV_INIT_EML_FOR(0,4,1305,1317,1386);
        _SFD_CV_INIT_EML_WHILE(0,0,1986,2042,2717);

        {
          static int condStart[] = { 365, 392 };

          static int condEnd[] = { 388, 409 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,0,365,409,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        {
          static int condStart[] = { 857, 885 };

          static int condEnd[] = { 881, 902 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,857,902,2,2,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c2_MAX_ALLOWED_ZONES;
          real_T *c2_HOT_COLD;
          real_T (*c2_TEMP_IN)[4];
          real_T (*c2_VALVE_IN)[4];
          real_T (*c2_LOW_SP)[4];
          real_T (*c2_HIGH_SP)[4];
          real_T (*c2_VALVE_OUT)[4];
          c2_HOT_COLD = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c2_VALVE_OUT = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S,
            1);
          c2_HIGH_SP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
          c2_LOW_SP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
          c2_MAX_ALLOWED_ZONES = (real_T *)ssGetInputPortSignal(chartInstance->S,
            2);
          c2_VALVE_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
          c2_TEMP_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_TEMP_IN);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_VALVE_IN);
          _SFD_SET_DATA_VALUE_PTR(2U, c2_MAX_ALLOWED_ZONES);
          _SFD_SET_DATA_VALUE_PTR(3U, *c2_LOW_SP);
          _SFD_SET_DATA_VALUE_PTR(4U, *c2_HIGH_SP);
          _SFD_SET_DATA_VALUE_PTR(5U, *c2_VALVE_OUT);
          _SFD_SET_DATA_VALUE_PTR(6U, c2_HOT_COLD);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_ON_OFF_LAZYMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c2_ON_OFF_LAZY(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_ON_OFF_LAZYInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c2_ON_OFF_LAZY((SFc2_ON_OFF_LAZYInstanceStruct*)
    chartInstanceVar);
  initialize_c2_ON_OFF_LAZY((SFc2_ON_OFF_LAZYInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_ON_OFF_LAZY(void *chartInstanceVar)
{
  enable_c2_ON_OFF_LAZY((SFc2_ON_OFF_LAZYInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_ON_OFF_LAZY(void *chartInstanceVar)
{
  disable_c2_ON_OFF_LAZY((SFc2_ON_OFF_LAZYInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_ON_OFF_LAZY(void *chartInstanceVar)
{
  sf_c2_ON_OFF_LAZY((SFc2_ON_OFF_LAZYInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_ON_OFF_LAZY(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_ON_OFF_LAZY
    ((SFc2_ON_OFF_LAZYInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_ON_OFF_LAZY();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_ON_OFF_LAZY(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_ON_OFF_LAZY();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_ON_OFF_LAZY((SFc2_ON_OFF_LAZYInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_ON_OFF_LAZY(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_ON_OFF_LAZY(S);
}

static void sf_opaque_set_sim_state_c2_ON_OFF_LAZY(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c2_ON_OFF_LAZY(S, st);
}

static void sf_opaque_terminate_c2_ON_OFF_LAZY(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_ON_OFF_LAZYInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_ON_OFF_LAZY((SFc2_ON_OFF_LAZYInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_ON_OFF_LAZY((SFc2_ON_OFF_LAZYInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_ON_OFF_LAZY(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_ON_OFF_LAZY((SFc2_ON_OFF_LAZYInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_ON_OFF_LAZY(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"ON_OFF_LAZY","ON_OFF_LAZY",2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"ON_OFF_LAZY","ON_OFF_LAZY",2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"ON_OFF_LAZY",
      "ON_OFF_LAZY",2,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"ON_OFF_LAZY","ON_OFF_LAZY",2,6);
      sf_mark_chart_reusable_outputs(S,"ON_OFF_LAZY","ON_OFF_LAZY",2,1);
    }

    sf_set_rtw_dwork_info(S,"ON_OFF_LAZY","ON_OFF_LAZY",2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(619253452U));
  ssSetChecksum1(S,(132086591U));
  ssSetChecksum2(S,(1024175590U));
  ssSetChecksum3(S,(3856896083U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_ON_OFF_LAZY(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "ON_OFF_LAZY", "ON_OFF_LAZY",2);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_ON_OFF_LAZY(SimStruct *S)
{
  SFc2_ON_OFF_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_ON_OFF_LAZYInstanceStruct *)malloc(sizeof
    (SFc2_ON_OFF_LAZYInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_ON_OFF_LAZYInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_ON_OFF_LAZY;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_ON_OFF_LAZY;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_ON_OFF_LAZY;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_ON_OFF_LAZY;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_ON_OFF_LAZY;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_ON_OFF_LAZY;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_ON_OFF_LAZY;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_ON_OFF_LAZY;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_ON_OFF_LAZY;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_ON_OFF_LAZY;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_ON_OFF_LAZY;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_ON_OFF_LAZY_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_ON_OFF_LAZY(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_ON_OFF_LAZY(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_ON_OFF_LAZY(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_ON_OFF_LAZY_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
