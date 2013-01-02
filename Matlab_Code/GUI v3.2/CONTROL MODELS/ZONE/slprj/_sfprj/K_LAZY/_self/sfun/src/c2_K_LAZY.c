/* Include files */

#include "blascompat32.h"
#include "K_LAZY_sfun.h"
#include "c2_K_LAZY.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "K_LAZY_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[21] = { "CriticalStates",
  "DesiredStates", "basePower", "powerPerAngle", "MAX_ALLOWED_ANGLES", "thresh",
  "i", "t", "k", "m", "mag", "total", "nargin", "nargout", "TEMP_IN", "VALVE_IN",
  "MAX_POWER_ALLOWED", "LOW_SP", "HIGH_SP", "HOT_COLD", "VALVE_OUT" };

/* Function Declarations */
static void initialize_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance);
static void initialize_params_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance);
static void enable_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance);
static void disable_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_K_LAZY(SFc2_K_LAZYInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_K_LAZY(SFc2_K_LAZYInstanceStruct
  *chartInstance);
static void set_sim_state_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance);
static void sf_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance);
static void c2_chartstep_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance);
static void initSimStructsc2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance, const
  mxArray *c2_VALVE_OUT, const char_T *c2_identifier, real_T c2_y[4]);
static void c2_b_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_d_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[14]);
static real_T c2_sum(SFc2_K_LAZYInstanceStruct *chartInstance, real_T c2_x[4]);
static real_T c2_b_sum(SFc2_K_LAZYInstanceStruct *chartInstance, real_T c2_x[4]);
static void c2_eml_li_find(SFc2_K_LAZYInstanceStruct *chartInstance, boolean_T
  c2_x[4], int32_T c2_y_data[4], int32_T c2_y_sizes[2]);
static void c2_floor(SFc2_K_LAZYInstanceStruct *chartInstance, real_T c2_x[4],
                     real_T c2_b_x[4]);
static void c2_b_eml_li_find(SFc2_K_LAZYInstanceStruct *chartInstance, boolean_T
  c2_x[4], int32_T c2_y_data[4], int32_T c2_y_sizes[1]);
static real_T c2_c_sum(SFc2_K_LAZYInstanceStruct *chartInstance, real_T
  c2_x_data[4], int32_T c2_x_sizes[1]);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_e_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_f_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_K_LAZY, const char_T *c2_identifier);
static uint8_T c2_g_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_floor(SFc2_K_LAZYInstanceStruct *chartInstance, real_T c2_x[4]);
static void init_dsm_address_info(SFc2_K_LAZYInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_K_LAZY = 0U;
}

static void initialize_params_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance)
{
}

static void enable_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_K_LAZY(SFc2_K_LAZYInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_K_LAZY(SFc2_K_LAZYInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[4];
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real_T (*c2_VALVE_OUT)[4];
  c2_VALVE_OUT = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(2));
  for (c2_i0 = 0; c2_i0 < 4; c2_i0++) {
    c2_u[c2_i0] = (*c2_VALVE_OUT)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4));
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_K_LAZY;
  c2_b_u = c2_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y);
  return c2_st;
}

static void set_sim_state_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[4];
  int32_T c2_i1;
  real_T (*c2_VALVE_OUT)[4];
  c2_VALVE_OUT = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                      "VALVE_OUT", c2_dv0);
  for (c2_i1 = 0; c2_i1 < 4; c2_i1++) {
    (*c2_VALVE_OUT)[c2_i1] = c2_dv0[c2_i1];
  }

  chartInstance->c2_is_active_c2_K_LAZY = c2_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 1)), "is_active_c2_K_LAZY");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_K_LAZY(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance)
{
}

static void sf_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance)
{
  int32_T c2_i2;
  int32_T c2_i3;
  int32_T c2_i4;
  int32_T c2_i5;
  int32_T c2_i6;
  real_T *c2_MAX_POWER_ALLOWED;
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
  c2_MAX_POWER_ALLOWED = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_VALVE_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
  c2_TEMP_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i2 = 0; c2_i2 < 4; c2_i2++) {
    _SFD_DATA_RANGE_CHECK((*c2_TEMP_IN)[c2_i2], 0U);
  }

  for (c2_i3 = 0; c2_i3 < 4; c2_i3++) {
    _SFD_DATA_RANGE_CHECK((*c2_VALVE_IN)[c2_i3], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_MAX_POWER_ALLOWED, 2U);
  for (c2_i4 = 0; c2_i4 < 4; c2_i4++) {
    _SFD_DATA_RANGE_CHECK((*c2_LOW_SP)[c2_i4], 3U);
  }

  for (c2_i5 = 0; c2_i5 < 4; c2_i5++) {
    _SFD_DATA_RANGE_CHECK((*c2_HIGH_SP)[c2_i5], 4U);
  }

  for (c2_i6 = 0; c2_i6 < 4; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*c2_VALVE_OUT)[c2_i6], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_HOT_COLD, 6U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_K_LAZY(chartInstance);
  sf_debug_check_for_state_inconsistency(_K_LAZYMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  int32_T c2_i7;
  real_T c2_TEMP_IN[4];
  int32_T c2_i8;
  real_T c2_VALVE_IN[4];
  real_T c2_MAX_POWER_ALLOWED;
  int32_T c2_i9;
  real_T c2_LOW_SP[4];
  int32_T c2_i10;
  real_T c2_HIGH_SP[4];
  real_T c2_HOT_COLD;
  uint32_T c2_debug_family_var_map[21];
  real_T c2_CriticalStates[4];
  real_T c2_DesiredStates[4];
  real_T c2_basePower;
  real_T c2_powerPerAngle;
  real_T c2_MAX_ALLOWED_ANGLES;
  real_T c2_thresh[4];
  real_T c2_i;
  real_T c2_t;
  real_T c2_k;
  real_T c2_m;
  real_T c2_mag[4];
  real_T c2_total;
  real_T c2_nargin = 6.0;
  real_T c2_nargout = 1.0;
  real_T c2_VALVE_OUT[4];
  int32_T c2_i11;
  int32_T c2_i12;
  real_T c2_A;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_c_x;
  int32_T c2_i13;
  real_T c2_b[4];
  int32_T c2_i14;
  int32_T c2_i15;
  real_T c2_b_i;
  real_T c2_c_i;
  real_T c2_d_i;
  real_T c2_e_i;
  real_T c2_f_i;
  int32_T c2_i16;
  boolean_T c2_b_CriticalStates[4];
  int32_T c2_tmp_sizes[2];
  int32_T c2_tmp_data[4];
  int32_T c2_loop_ub;
  int32_T c2_i17;
  int32_T c2_i18;
  real_T c2_b_VALVE_OUT[4];
  int32_T c2_i19;
  real_T c2_c_CriticalStates[4];
  int32_T c2_i20;
  real_T c2_b_DesiredStates[4];
  real_T c2_a;
  real_T c2_y;
  real_T c2_b_a;
  real_T c2_b_y;
  int32_T c2_i21;
  boolean_T c2_d_CriticalStates[4];
  int32_T c2_b_loop_ub;
  int32_T c2_i22;
  int32_T c2_i23;
  boolean_T c2_e_CriticalStates[4];
  int32_T c2_c_loop_ub;
  int32_T c2_i24;
  int32_T c2_i25;
  boolean_T c2_c_VALVE_OUT[4];
  int32_T c2_b_tmp_sizes;
  int32_T c2_b_tmp_data[4];
  int32_T c2_d_loop_ub;
  int32_T c2_i26;
  int32_T c2_i27;
  boolean_T c2_f_CriticalStates[4];
  real_T c2_b_A;
  real_T c2_B;
  real_T c2_d_x;
  real_T c2_c_y;
  real_T c2_e_x;
  real_T c2_d_y;
  real_T c2_f_x;
  real_T c2_e_y;
  real_T c2_f_y;
  int32_T c2_e_loop_ub;
  int32_T c2_i28;
  int32_T c2_i29;
  boolean_T c2_g_CriticalStates[4];
  int32_T c2_f_loop_ub;
  int32_T c2_i30;
  int32_T c2_i31;
  int32_T c2_i32;
  real_T c2_b_k;
  real_T c2_c_k;
  real_T c2_g_x;
  real_T c2_h_x;
  int32_T c2_i33;
  boolean_T c2_d_VALVE_OUT[4];
  int32_T c2_g_loop_ub;
  int32_T c2_i34;
  int32_T c2_i35;
  boolean_T c2_h_CriticalStates[4];
  int32_T c2_h_loop_ub;
  int32_T c2_i36;
  int32_T c2_i37;
  boolean_T c2_i_CriticalStates[4];
  int32_T c2_VALVE_OUT_sizes;
  int32_T c2_i_loop_ub;
  int32_T c2_i38;
  real_T c2_VALVE_OUT_data[4];
  int32_T c2_i39;
  int32_T c2_i40;
  int32_T c2_i41;
  real_T c2_b_mag[4];
  int32_T c2_i42;
  boolean_T c2_c_DesiredStates[4];
  int32_T c2_i43;
  boolean_T c2_d_DesiredStates[4];
  int32_T c2_c_tmp_sizes[2];
  int32_T c2_c_tmp_data[4];
  int32_T c2_A_sizes;
  int32_T c2_j_loop_ub;
  int32_T c2_i44;
  real_T c2_A_data[4];
  real_T c2_b_B;
  real_T c2_g_y;
  real_T c2_h_y;
  real_T c2_i_y;
  int32_T c2_k_loop_ub;
  int32_T c2_i45;
  int32_T c2_l_loop_ub;
  int32_T c2_i46;
  int32_T c2_m_loop_ub;
  int32_T c2_i47;
  int32_T c2_i48;
  int32_T c2_i49;
  real_T c2_d_k;
  real_T c2_e_k;
  real_T c2_i_x;
  real_T c2_j_x;
  int32_T c2_i50;
  boolean_T c2_e_VALVE_OUT[4];
  int32_T c2_n_loop_ub;
  int32_T c2_i51;
  int32_T c2_i52;
  real_T *c2_b_MAX_POWER_ALLOWED;
  real_T *c2_b_HOT_COLD;
  real_T (*c2_f_VALVE_OUT)[4];
  real_T (*c2_b_HIGH_SP)[4];
  real_T (*c2_b_LOW_SP)[4];
  real_T (*c2_b_VALVE_IN)[4];
  real_T (*c2_b_TEMP_IN)[4];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  c2_b_HOT_COLD = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c2_f_VALVE_OUT = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_HIGH_SP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
  c2_b_LOW_SP = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
  c2_b_MAX_POWER_ALLOWED = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_b_VALVE_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_TEMP_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_MAX_POWER_ALLOWED;
  c2_b_hoistedGlobal = *c2_b_HOT_COLD;
  for (c2_i7 = 0; c2_i7 < 4; c2_i7++) {
    c2_TEMP_IN[c2_i7] = (*c2_b_TEMP_IN)[c2_i7];
  }

  for (c2_i8 = 0; c2_i8 < 4; c2_i8++) {
    c2_VALVE_IN[c2_i8] = (*c2_b_VALVE_IN)[c2_i8];
  }

  c2_MAX_POWER_ALLOWED = c2_hoistedGlobal;
  for (c2_i9 = 0; c2_i9 < 4; c2_i9++) {
    c2_LOW_SP[c2_i9] = (*c2_b_LOW_SP)[c2_i9];
  }

  for (c2_i10 = 0; c2_i10 < 4; c2_i10++) {
    c2_HIGH_SP[c2_i10] = (*c2_b_HIGH_SP)[c2_i10];
  }

  c2_HOT_COLD = c2_b_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 21U, 21U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(c2_CriticalStates, 0U,
    c2_c_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_DesiredStates, 1U,
    c2_c_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_basePower, 2U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c2_powerPerAngle, 3U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_MAX_ALLOWED_ANGLES, 4U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_thresh, 5U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_i, 6U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_t, 7U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_k, 8U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_m, 9U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_mag, 10U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_total, 11U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 12U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 13U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_TEMP_IN, 14U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_VALVE_IN, 15U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_MAX_POWER_ALLOWED, 16U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_LOW_SP, 17U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_HIGH_SP, 18U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_HOT_COLD, 19U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_VALVE_OUT, 20U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  for (c2_i11 = 0; c2_i11 < 4; c2_i11++) {
    c2_CriticalStates[c2_i11] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  for (c2_i12 = 0; c2_i12 < 4; c2_i12++) {
    c2_DesiredStates[c2_i12] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_basePower = 4.3;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  c2_powerPerAngle = 0.0186;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_A = c2_MAX_POWER_ALLOWED - 4.3;
  c2_x = c2_A;
  c2_b_x = c2_x;
  c2_c_x = c2_b_x;
  c2_MAX_ALLOWED_ANGLES = c2_c_x / 0.0186;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  for (c2_i13 = 0; c2_i13 < 4; c2_i13++) {
    c2_b[c2_i13] = c2_HIGH_SP[c2_i13] - c2_LOW_SP[c2_i13];
  }

  for (c2_i14 = 0; c2_i14 < 4; c2_i14++) {
    c2_thresh[c2_i14] = 0.1 * c2_b[c2_i14];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  for (c2_i15 = 0; c2_i15 < 4; c2_i15++) {
    c2_VALVE_OUT[c2_i15] = c2_VALVE_IN[c2_i15];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 17);
  if (CV_EML_IF(0, 0, c2_HOT_COLD == 0.0)) {
    c2_i = 1.0;
    c2_b_i = 1.0;
    while (c2_b_i <= 4.0) {
      c2_i = c2_b_i;
      CV_EML_FOR(0, 0, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
      guard2 = FALSE;
      if (CV_EML_COND(0, 0, c2_TEMP_IN[(int32_T)c2_i - 1] <= c2_LOW_SP[(int32_T)
                      c2_i - 1])) {
        if (CV_EML_COND(0, 1, c2_VALVE_IN[(int32_T)c2_i - 1] <= 90.0)) {
          CV_EML_MCDC(0, 0, TRUE);
          CV_EML_IF(0, 1, TRUE);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
          c2_VALVE_OUT[(int32_T)c2_i - 1] = 90.0;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 24);
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
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
      if (CV_EML_IF(0, 2, c2_TEMP_IN[(int32_T)c2_i - 1] >= c2_HIGH_SP[(int32_T)
                    c2_i - 1] - c2_thresh[(int32_T)c2_i - 1])) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 33);
        c2_CriticalStates[(int32_T)c2_i - 1] = 1.0;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
        c2_VALVE_OUT[(int32_T)c2_i - 1] = 0.0;
      }

      c2_c_i++;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 0);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 40);
    if (CV_EML_IF(0, 3, c2_HOT_COLD == 1.0)) {
      c2_i = 1.0;
      c2_d_i = 1.0;
      while (c2_d_i <= 4.0) {
        c2_i = c2_d_i;
        CV_EML_FOR(0, 2, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 45);
        guard1 = FALSE;
        if (CV_EML_COND(0, 2, c2_TEMP_IN[(int32_T)c2_i - 1] >= c2_HIGH_SP
                        [(int32_T)c2_i - 1])) {
          if (CV_EML_COND(0, 3, c2_VALVE_IN[(int32_T)c2_i - 1] <= 90.0)) {
            CV_EML_MCDC(0, 1, TRUE);
            CV_EML_IF(0, 4, TRUE);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 46);
            c2_VALVE_OUT[(int32_T)c2_i - 1] = 90.0;
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
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
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 55);
        if (CV_EML_IF(0, 5, c2_TEMP_IN[(int32_T)c2_i - 1] <= c2_LOW_SP[(int32_T)
                      c2_i - 1] + c2_thresh[(int32_T)c2_i - 1])) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 56);
          c2_CriticalStates[(int32_T)c2_i - 1] = 1.0;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 57);
          c2_VALVE_OUT[(int32_T)c2_i - 1] = 0.0;
        }

        c2_e_i++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }

      CV_EML_FOR(0, 3, 0);
    }
  }

  c2_i = 1.0;
  c2_f_i = 1.0;
  while (c2_f_i <= 4.0) {
    c2_i = c2_f_i;
    CV_EML_FOR(0, 4, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 66);
    if (CV_EML_IF(0, 6, c2_VALVE_IN[(int32_T)c2_i - 1] < 90.0)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 67);
      c2_DesiredStates[(int32_T)c2_i - 1] = 1.0;
    }

    c2_f_i++;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 4, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 70);
  for (c2_i16 = 0; c2_i16 < 4; c2_i16++) {
    c2_b_CriticalStates[c2_i16] = (c2_CriticalStates[c2_i16] == 1.0);
  }

  c2_eml_li_find(chartInstance, c2_b_CriticalStates, c2_tmp_data, c2_tmp_sizes);
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i17 = 0; c2_i17 <= c2_loop_ub; c2_i17++) {
    c2_DesiredStates[c2_tmp_data[c2_i17] - 1] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 72);
  for (c2_i18 = 0; c2_i18 < 4; c2_i18++) {
    c2_b_VALVE_OUT[c2_i18] = c2_VALVE_OUT[c2_i18];
  }

  c2_t = 360.0 - c2_sum(chartInstance, c2_b_VALVE_OUT);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 73);
  for (c2_i19 = 0; c2_i19 < 4; c2_i19++) {
    c2_c_CriticalStates[c2_i19] = c2_CriticalStates[c2_i19];
  }

  c2_k = c2_b_sum(chartInstance, c2_c_CriticalStates);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 74);
  for (c2_i20 = 0; c2_i20 < 4; c2_i20++) {
    c2_b_DesiredStates[c2_i20] = c2_DesiredStates[c2_i20];
  }

  c2_m = c2_b_sum(chartInstance, c2_b_DesiredStates);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 79);
  c2_a = c2_k;
  c2_y = c2_a * 90.0;
  if (CV_EML_IF(0, 7, c2_y > c2_MAX_ALLOWED_ANGLES)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 80);
    c2_b_a = c2_k;
    c2_b_y = c2_b_a * 50.0;
    if (CV_EML_IF(0, 8, c2_b_y > c2_MAX_ALLOWED_ANGLES)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 81);
      for (c2_i21 = 0; c2_i21 < 4; c2_i21++) {
        c2_d_CriticalStates[c2_i21] = (c2_CriticalStates[c2_i21] == 1.0);
      }

      c2_eml_li_find(chartInstance, c2_d_CriticalStates, c2_tmp_data,
                     c2_tmp_sizes);
      c2_b_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
      for (c2_i22 = 0; c2_i22 <= c2_b_loop_ub; c2_i22++) {
        c2_VALVE_OUT[c2_tmp_data[c2_i22] - 1] = 40.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 82);
      for (c2_i23 = 0; c2_i23 < 4; c2_i23++) {
        c2_e_CriticalStates[c2_i23] = (c2_CriticalStates[c2_i23] != 1.0);
      }

      c2_eml_li_find(chartInstance, c2_e_CriticalStates, c2_tmp_data,
                     c2_tmp_sizes);
      c2_c_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
      for (c2_i24 = 0; c2_i24 <= c2_c_loop_ub; c2_i24++) {
        c2_VALVE_OUT[c2_tmp_data[c2_i24] - 1] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 83);
      c2_b_floor(chartInstance, c2_VALVE_OUT);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 84);
      for (c2_i25 = 0; c2_i25 < 4; c2_i25++) {
        c2_c_VALVE_OUT[c2_i25] = (c2_VALVE_OUT[c2_i25] > 90.0);
      }

      c2_b_eml_li_find(chartInstance, c2_c_VALVE_OUT, c2_b_tmp_data,
                       &c2_b_tmp_sizes);
      c2_d_loop_ub = c2_b_tmp_sizes - 1;
      for (c2_i26 = 0; c2_i26 <= c2_d_loop_ub; c2_i26++) {
        c2_VALVE_OUT[c2_b_tmp_data[c2_i26] - 1] = 90.0;
      }
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 87);
      for (c2_i27 = 0; c2_i27 < 4; c2_i27++) {
        c2_f_CriticalStates[c2_i27] = (c2_CriticalStates[c2_i27] == 1.0);
      }

      c2_eml_li_find(chartInstance, c2_f_CriticalStates, c2_tmp_data,
                     c2_tmp_sizes);
      c2_b_A = c2_MAX_ALLOWED_ANGLES;
      c2_B = c2_k;
      c2_d_x = c2_b_A;
      c2_c_y = c2_B;
      c2_e_x = c2_d_x;
      c2_d_y = c2_c_y;
      c2_f_x = c2_e_x;
      c2_e_y = c2_d_y;
      c2_f_y = c2_f_x / c2_e_y;
      c2_e_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
      for (c2_i28 = 0; c2_i28 <= c2_e_loop_ub; c2_i28++) {
        c2_VALVE_OUT[c2_tmp_data[c2_i28] - 1] = 90.0 - c2_f_y;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 88);
      for (c2_i29 = 0; c2_i29 < 4; c2_i29++) {
        c2_g_CriticalStates[c2_i29] = (c2_CriticalStates[c2_i29] != 1.0);
      }

      c2_eml_li_find(chartInstance, c2_g_CriticalStates, c2_tmp_data,
                     c2_tmp_sizes);
      c2_f_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
      for (c2_i30 = 0; c2_i30 <= c2_f_loop_ub; c2_i30++) {
        c2_VALVE_OUT[c2_tmp_data[c2_i30] - 1] = 90.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 89);
      for (c2_i31 = 0; c2_i31 < 4; c2_i31++) {
        c2_b[c2_i31] = c2_VALVE_OUT[c2_i31];
      }

      for (c2_i32 = 0; c2_i32 < 4; c2_i32++) {
        c2_VALVE_OUT[c2_i32] = c2_b[c2_i32];
      }

      for (c2_b_k = 1.0; c2_b_k <= 4.0; c2_b_k++) {
        c2_c_k = c2_b_k;
        c2_g_x = c2_VALVE_OUT[(int32_T)c2_c_k - 1];
        c2_h_x = c2_g_x;
        c2_h_x = muDoubleScalarFloor(c2_h_x);
        c2_VALVE_OUT[(int32_T)c2_c_k - 1] = c2_h_x;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 90);
      for (c2_i33 = 0; c2_i33 < 4; c2_i33++) {
        c2_d_VALVE_OUT[c2_i33] = (c2_VALVE_OUT[c2_i33] > 90.0);
      }

      c2_b_eml_li_find(chartInstance, c2_d_VALVE_OUT, c2_b_tmp_data,
                       &c2_b_tmp_sizes);
      c2_g_loop_ub = c2_b_tmp_sizes - 1;
      for (c2_i34 = 0; c2_i34 <= c2_g_loop_ub; c2_i34++) {
        c2_VALVE_OUT[c2_b_tmp_data[c2_i34] - 1] = 90.0;
      }
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 94);
    for (c2_i35 = 0; c2_i35 < 4; c2_i35++) {
      c2_h_CriticalStates[c2_i35] = (c2_CriticalStates[c2_i35] == 1.0);
    }

    c2_eml_li_find(chartInstance, c2_h_CriticalStates, c2_tmp_data, c2_tmp_sizes);
    c2_h_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
    for (c2_i36 = 0; c2_i36 <= c2_h_loop_ub; c2_i36++) {
      c2_VALVE_OUT[c2_tmp_data[c2_i36] - 1] = 0.0;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 100);
    for (c2_i37 = 0; c2_i37 < 4; c2_i37++) {
      c2_i_CriticalStates[c2_i37] = (c2_CriticalStates[c2_i37] == 1.0);
    }

    c2_eml_li_find(chartInstance, c2_i_CriticalStates, c2_tmp_data, c2_tmp_sizes);
    c2_VALVE_OUT_sizes = c2_tmp_sizes[1];
    c2_i_loop_ub = c2_tmp_sizes[1] - 1;
    for (c2_i38 = 0; c2_i38 <= c2_i_loop_ub; c2_i38++) {
      c2_VALVE_OUT_data[c2_i38] = c2_VALVE_OUT[c2_tmp_data[c2_i38] - 1];
    }

    c2_MAX_ALLOWED_ANGLES -= c2_c_sum(chartInstance, c2_VALVE_OUT_data,
      *(int32_T (*)[1])&c2_VALVE_OUT_sizes);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 102);
    if (CV_EML_IF(0, 9, c2_HOT_COLD == 0.0)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 103);
      for (c2_i39 = 0; c2_i39 < 4; c2_i39++) {
        c2_mag[c2_i39] = c2_DesiredStates[c2_i39] * (c2_TEMP_IN[c2_i39] -
          c2_LOW_SP[c2_i39]);
      }
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 106);
      for (c2_i40 = 0; c2_i40 < 4; c2_i40++) {
        c2_mag[c2_i40] = c2_DesiredStates[c2_i40] * (c2_HIGH_SP[c2_i40] -
          c2_TEMP_IN[c2_i40]);
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 108);
    for (c2_i41 = 0; c2_i41 < 4; c2_i41++) {
      c2_b_mag[c2_i41] = c2_mag[c2_i41];
    }

    c2_total = c2_sum(chartInstance, c2_b_mag);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 109);
    for (c2_i42 = 0; c2_i42 < 4; c2_i42++) {
      c2_c_DesiredStates[c2_i42] = (c2_DesiredStates[c2_i42] == 1.0);
    }

    c2_eml_li_find(chartInstance, c2_c_DesiredStates, c2_tmp_data, c2_tmp_sizes);
    for (c2_i43 = 0; c2_i43 < 4; c2_i43++) {
      c2_d_DesiredStates[c2_i43] = (c2_DesiredStates[c2_i43] == 1.0);
    }

    c2_eml_li_find(chartInstance, c2_d_DesiredStates, c2_c_tmp_data,
                   c2_c_tmp_sizes);
    c2_A_sizes = c2_c_tmp_sizes[1];
    c2_j_loop_ub = c2_c_tmp_sizes[1] - 1;
    for (c2_i44 = 0; c2_i44 <= c2_j_loop_ub; c2_i44++) {
      c2_A_data[c2_i44] = c2_mag[c2_c_tmp_data[c2_i44] - 1];
    }

    c2_b_B = c2_total;
    c2_g_y = c2_b_B;
    c2_h_y = c2_g_y;
    c2_i_y = c2_h_y;
    c2_A_sizes;
    c2_k_loop_ub = c2_A_sizes - 1;
    for (c2_i45 = 0; c2_i45 <= c2_k_loop_ub; c2_i45++) {
      c2_A_data[c2_i45] /= c2_i_y;
    }

    c2_A_sizes;
    c2_l_loop_ub = c2_A_sizes - 1;
    for (c2_i46 = 0; c2_i46 <= c2_l_loop_ub; c2_i46++) {
      c2_A_data[c2_i46] *= c2_MAX_ALLOWED_ANGLES;
    }

    sf_debug_size_eq_check_1d(c2_tmp_sizes[1], c2_A_sizes);
    c2_m_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
    for (c2_i47 = 0; c2_i47 <= c2_m_loop_ub; c2_i47++) {
      c2_VALVE_OUT[c2_tmp_data[c2_i47] - 1] = c2_A_data[c2_i47];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 111);
    for (c2_i48 = 0; c2_i48 < 4; c2_i48++) {
      c2_b[c2_i48] = c2_VALVE_OUT[c2_i48];
    }

    for (c2_i49 = 0; c2_i49 < 4; c2_i49++) {
      c2_VALVE_OUT[c2_i49] = c2_b[c2_i49];
    }

    for (c2_d_k = 1.0; c2_d_k <= 4.0; c2_d_k++) {
      c2_e_k = c2_d_k;
      c2_i_x = c2_VALVE_OUT[(int32_T)c2_e_k - 1];
      c2_j_x = c2_i_x;
      c2_j_x = muDoubleScalarFloor(c2_j_x);
      c2_VALVE_OUT[(int32_T)c2_e_k - 1] = c2_j_x;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 112);
    for (c2_i50 = 0; c2_i50 < 4; c2_i50++) {
      c2_e_VALVE_OUT[c2_i50] = (c2_VALVE_OUT[c2_i50] > 90.0);
    }

    c2_b_eml_li_find(chartInstance, c2_e_VALVE_OUT, c2_b_tmp_data,
                     &c2_b_tmp_sizes);
    c2_n_loop_ub = c2_b_tmp_sizes - 1;
    for (c2_i51 = 0; c2_i51 <= c2_n_loop_ub; c2_i51++) {
      c2_VALVE_OUT[c2_b_tmp_data[c2_i51] - 1] = 90.0;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -112);
  sf_debug_symbol_scope_pop();
  for (c2_i52 = 0; c2_i52 < 4; c2_i52++) {
    (*c2_f_VALVE_OUT)[c2_i52] = c2_VALVE_OUT[c2_i52];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_K_LAZY(SFc2_K_LAZYInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i53;
  real_T c2_b_inData[4];
  int32_T c2_i54;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_K_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_K_LAZYInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i53 = 0; c2_i53 < 4; c2_i53++) {
    c2_b_inData[c2_i53] = (*(real_T (*)[4])c2_inData)[c2_i53];
  }

  for (c2_i54 = 0; c2_i54 < 4; c2_i54++) {
    c2_u[c2_i54] = c2_b_inData[c2_i54];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance, const
  mxArray *c2_VALVE_OUT, const char_T *c2_identifier, real_T c2_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_VALVE_OUT), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_VALVE_OUT);
}

static void c2_b_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4])
{
  real_T c2_dv1[4];
  int32_T c2_i55;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv1, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i55 = 0; c2_i55 < 4; c2_i55++) {
    c2_y[c2_i55] = c2_dv1[c2_i55];
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
  int32_T c2_i56;
  SFc2_K_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_K_LAZYInstanceStruct *)chartInstanceVoid;
  c2_VALVE_OUT = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_VALVE_OUT), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_VALVE_OUT);
  for (c2_i56 = 0; c2_i56 < 4; c2_i56++) {
    (*(real_T (*)[4])c2_outData)[c2_i56] = c2_y[c2_i56];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_K_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_K_LAZYInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
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
  SFc2_K_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_K_LAZYInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i57;
  real_T c2_b_inData[4];
  int32_T c2_i58;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_K_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_K_LAZYInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i57 = 0; c2_i57 < 4; c2_i57++) {
    c2_b_inData[c2_i57] = (*(real_T (*)[4])c2_inData)[c2_i57];
  }

  for (c2_i58 = 0; c2_i58 < 4; c2_i58++) {
    c2_u[c2_i58] = c2_b_inData[c2_i58];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 4));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static void c2_d_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4])
{
  real_T c2_dv2[4];
  int32_T c2_i59;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv2, 1, 0, 0U, 1, 0U, 2, 1, 4);
  for (c2_i59 = 0; c2_i59 < 4; c2_i59++) {
    c2_y[c2_i59] = c2_dv2[c2_i59];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_DesiredStates;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i60;
  SFc2_K_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_K_LAZYInstanceStruct *)chartInstanceVoid;
  c2_DesiredStates = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_DesiredStates), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_DesiredStates);
  for (c2_i60 = 0; c2_i60 < 4; c2_i60++) {
    (*(real_T (*)[4])c2_outData)[c2_i60] = c2_y[c2_i60];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_K_LAZY_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[14];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i61;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 14));
  for (c2_i61 = 0; c2_i61 < 14; c2_i61++) {
    c2_r0 = &c2_info[c2_i61];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i61);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i61);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i61);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i61);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i61);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i61);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i61);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i61);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[14])
{
  c2_info[0].context = "";
  c2_info[0].name = "mrdivide";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[0].fileTimeLo = 1296686254U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 1289541292U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[1].name = "rdivide";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[1].fileTimeLo = 1286840444U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 0U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[2].name = "eml_div";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[2].fileTimeLo = 1286840298U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context = "";
  c2_info[3].name = "mtimes";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[3].fileTimeLo = 1289541292U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context = "";
  c2_info[4].name = "sum";
  c2_info[4].dominantType = "double";
  c2_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[4].fileTimeLo = 1286840300U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[5].name = "isequal";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[5].fileTimeLo = 1286840358U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[6].name = "eml_isequal_core";
  c2_info[6].dominantType = "double";
  c2_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c2_info[6].fileTimeLo = 1286840386U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 0U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[7].name = "eml_const_nonsingleton_dim";
  c2_info[7].dominantType = "double";
  c2_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c2_info[7].fileTimeLo = 1286840296U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[8].name = "eml_scalar_eg";
  c2_info[8].dominantType = "double";
  c2_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[8].fileTimeLo = 1286840396U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  c2_info[9].name = "eml_index_class";
  c2_info[9].dominantType = "";
  c2_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[9].fileTimeLo = 1286840378U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context = "";
  c2_info[10].name = "eml_li_find";
  c2_info[10].dominantType = "";
  c2_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m";
  c2_info[10].fileTimeLo = 1286840386U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m!compute_nones";
  c2_info[11].name = "eml_index_plus";
  c2_info[11].dominantType = "int32";
  c2_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[11].fileTimeLo = 1286840378U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context = "";
  c2_info[12].name = "floor";
  c2_info[12].dominantType = "double";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[12].fileTimeLo = 1286840342U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[13].name = "eml_scalar_floor";
  c2_info[13].dominantType = "double";
  c2_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c2_info[13].fileTimeLo = 1286840326U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
}

static real_T c2_sum(SFc2_K_LAZYInstanceStruct *chartInstance, real_T c2_x[4])
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

static real_T c2_b_sum(SFc2_K_LAZYInstanceStruct *chartInstance, real_T c2_x[4])
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

static void c2_eml_li_find(SFc2_K_LAZYInstanceStruct *chartInstance, boolean_T
  c2_x[4], int32_T c2_y_data[4], int32_T c2_y_sizes[2])
{
  int32_T c2_k;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_a;
  const mxArray *c2_y = NULL;
  int32_T c2_tmp_sizes[2];
  int32_T c2_iv0[2];
  int32_T c2_i62;
  int32_T c2_i63;
  int32_T c2_loop_ub;
  int32_T c2_i64;
  int32_T c2_tmp_data[4];
  int32_T c2_i65;
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
  c2_i62 = c2_tmp_sizes[0];
  c2_i63 = c2_tmp_sizes[1];
  c2_loop_ub = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c2_k) - 1;
  for (c2_i64 = 0; c2_i64 <= c2_loop_ub; c2_i64++) {
    c2_tmp_data[c2_i64] = 0;
  }

  for (c2_i65 = 0; c2_i65 < 2; c2_i65++) {
    c2_y_sizes[c2_i65] = c2_tmp_sizes[c2_i65];
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

static void c2_floor(SFc2_K_LAZYInstanceStruct *chartInstance, real_T c2_x[4],
                     real_T c2_b_x[4])
{
  int32_T c2_i66;
  for (c2_i66 = 0; c2_i66 < 4; c2_i66++) {
    c2_b_x[c2_i66] = c2_x[c2_i66];
  }

  c2_b_floor(chartInstance, c2_b_x);
}

static void c2_b_eml_li_find(SFc2_K_LAZYInstanceStruct *chartInstance, boolean_T
  c2_x[4], int32_T c2_y_data[4], int32_T c2_y_sizes[1])
{
  int32_T c2_k;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_a;
  const mxArray *c2_y = NULL;
  int32_T c2_tmp_sizes;
  int32_T c2_loop_ub;
  int32_T c2_i67;
  int32_T c2_tmp_data[4];
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

  c2_tmp_sizes = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c2_k);
  c2_loop_ub = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c2_k) - 1;
  for (c2_i67 = 0; c2_i67 <= c2_loop_ub; c2_i67++) {
    c2_tmp_data[c2_i67] = 0;
  }

  c2_y_sizes[0] = c2_tmp_sizes;
  c2_j = 1;
  for (c2_c_i = 1; c2_c_i < 5; c2_c_i++) {
    c2_d_i = c2_c_i;
    if (c2_x[c2_d_i - 1]) {
      c2_y_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c2_j, 1, c2_y_sizes[0], 1, 0) -
        1] = c2_d_i;
      c2_b_a = c2_j + 1;
      c2_j = c2_b_a;
    }
  }
}

static real_T c2_c_sum(SFc2_K_LAZYInstanceStruct *chartInstance, real_T
  c2_x_data[4], int32_T c2_x_sizes[1])
{
  real_T c2_y;
  boolean_T c2_p;
  boolean_T c2_b_p;
  real_T c2_k;
  real_T c2_b_k;
  real_T c2_d1;
  real_T c2_d2;
  boolean_T c2_b0;
  boolean_T c2_c_p;
  boolean_T c2_b1;
  int32_T c2_i68;
  static char_T c2_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 's', 'u', 'm', '_', 's', 'p', 'e', 'c', 'i', 'a', 'l',
    'E', 'm', 'p', 't', 'y' };

  char_T c2_u[30];
  const mxArray *c2_b_y = NULL;
  boolean_T c2_b2;
  int32_T c2_i69;
  static char_T c2_cv1[36] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'a', 'u', 't', 'o', 'D', 'i', 'm', 'I', 'n', 'c', 'o',
    'm', 'p', 'a', 't', 'i', 'b', 'i', 'l', 'i', 't', 'y' };

  char_T c2_b_u[36];
  const mxArray *c2_c_y = NULL;
  real_T c2_d3;
  real_T c2_d4;
  real_T c2_d5;
  int32_T c2_i70;
  int32_T c2_vlen;
  int32_T c2_c_k;
  int32_T c2_d_k;
  boolean_T guard1 = FALSE;
  int32_T exitg1;
  c2_p = FALSE;
  c2_b_p = FALSE;
  c2_k = 1.0;
  do {
    exitg1 = 0U;
    if (c2_k <= 2.0) {
      c2_b_k = c2_k;
      c2_d1 = c2_b_k;
      if (c2_d1 <= 1.0) {
        c2_d2 = (real_T)c2_x_sizes[0];
      } else {
        c2_d2 = 1.0;
      }

      if (c2_d2 != 0.0) {
        exitg1 = 1U;
      } else {
        c2_k++;
      }
    } else {
      c2_b_p = TRUE;
      exitg1 = 1U;
    }
  } while (exitg1 == 0U);

  if (c2_b_p) {
    c2_b0 = TRUE;
  } else {
    c2_b0 = FALSE;
  }

  c2_c_p = c2_b0;
  if (!c2_c_p) {
  } else {
    c2_p = TRUE;
  }

  if (!c2_p) {
    c2_b1 = TRUE;
  } else {
    c2_b1 = FALSE;
  }

  if (c2_b1) {
  } else {
    for (c2_i68 = 0; c2_i68 < 30; c2_i68++) {
      c2_u[c2_i68] = c2_cv0[c2_i68];
    }

    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 30));
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
      14, c2_b_y));
  }

  guard1 = FALSE;
  if (c2_x_sizes[0] == 1) {
    guard1 = TRUE;
  } else if ((real_T)c2_x_sizes[0] != 1.0) {
    guard1 = TRUE;
  } else {
    c2_b2 = FALSE;
  }

  if (guard1 == TRUE) {
    c2_b2 = TRUE;
  }

  if (c2_b2) {
  } else {
    for (c2_i69 = 0; c2_i69 < 36; c2_i69++) {
      c2_b_u[c2_i69] = c2_cv1[c2_i69];
    }

    c2_c_y = NULL;
    sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 36));
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
      14, c2_c_y));
  }

  if (c2_x_sizes[0] == 0) {
    c2_y = 0.0;
  } else {
    c2_d3 = (real_T)c2_x_sizes[0];
    c2_d4 = c2_d3;
    c2_d4 = c2_d4 < 0.0 ? muDoubleScalarCeil(c2_d4 - 0.5) : muDoubleScalarFloor
      (c2_d4 + 0.5);
    c2_d5 = c2_d4;
    if (c2_d5 < 2.147483648E+9) {
      if (c2_d5 >= -2.147483648E+9) {
        c2_i70 = (int32_T)c2_d5;
      } else {
        c2_i70 = MIN_int32_T;
      }
    } else if (c2_d5 >= 2.147483648E+9) {
      c2_i70 = MAX_int32_T;
    } else {
      c2_i70 = 0;
    }

    c2_vlen = c2_i70;
    c2_y = c2_x_data[0];
    for (c2_c_k = 2; c2_c_k <= c2_vlen; c2_c_k++) {
      c2_d_k = c2_c_k;
      c2_y += c2_x_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c2_d_k, 1, c2_x_sizes[0],
        1, 0) - 1];
    }
  }

  return c2_y;
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_K_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_K_LAZYInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static int32_T c2_e_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i71;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i71, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i71;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_K_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_K_LAZYInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_K_LAZY, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_K_LAZY), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_K_LAZY);
  return c2_y;
}

static uint8_T c2_g_emlrt_marshallIn(SFc2_K_LAZYInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_floor(SFc2_K_LAZYInstanceStruct *chartInstance, real_T c2_x[4])
{
  real_T c2_k;
  real_T c2_b_k;
  real_T c2_b_x;
  real_T c2_c_x;
  for (c2_k = 1.0; c2_k <= 4.0; c2_k++) {
    c2_b_k = c2_k;
    c2_b_x = c2_x[(int32_T)c2_b_k - 1];
    c2_c_x = c2_b_x;
    c2_c_x = muDoubleScalarFloor(c2_c_x);
    c2_x[(int32_T)c2_b_k - 1] = c2_c_x;
  }
}

static void init_dsm_address_info(SFc2_K_LAZYInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_K_LAZY_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4174712377U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(926145501U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3233745027U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3000061265U);
}

mxArray *sf_c2_K_LAZY_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(2399871404U);
    pr[1] = (double)(76943411U);
    pr[2] = (double)(3420751489U);
    pr[3] = (double)(969292246U);
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

static const mxArray *sf_get_sim_state_info_c2_K_LAZY(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[10],T\"VALVE_OUT\",},{M[8],M[0],T\"is_active_c2_K_LAZY\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_K_LAZY_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_K_LAZYInstanceStruct *chartInstance;
    chartInstance = (SFc2_K_LAZYInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_K_LAZYMachineNumber_,
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
          init_script_number_translation(_K_LAZYMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_K_LAZYMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_K_LAZYMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"TEMP_IN");
          _SFD_SET_DATA_PROPS(1,1,1,0,"VALVE_IN");
          _SFD_SET_DATA_PROPS(2,1,1,0,"MAX_POWER_ALLOWED");
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
        _SFD_CV_INIT_EML(0,1,10,0,0,5,0,4,2);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,5135);
        _SFD_CV_INIT_EML_IF(0,0,714,730,1215,1235);
        _SFD_CV_INIT_EML_IF(0,1,814,861,-1,978);
        _SFD_CV_INIT_EML_IF(0,2,1070,1111,-1,1188);
        _SFD_CV_INIT_EML_IF(0,3,1215,1235,-1,1235);
        _SFD_CV_INIT_EML_IF(0,4,1320,1368,-1,1485);
        _SFD_CV_INIT_EML_IF(0,5,1577,1619,-1,1696);
        _SFD_CV_INIT_EML_IF(0,6,1761,1780,-1,1818);
        _SFD_CV_INIT_EML_IF(0,7,2225,2253,3015,3180);
        _SFD_CV_INIT_EML_IF(0,8,2361,2389,2678,3013);
        _SFD_CV_INIT_EML_IF(0,9,3341,3357,3418,3477);
        _SFD_CV_INIT_EML_FOR(0,0,794,806,987);
        _SFD_CV_INIT_EML_FOR(0,1,1050,1062,1200);
        _SFD_CV_INIT_EML_FOR(0,2,1300,1312,1494);
        _SFD_CV_INIT_EML_FOR(0,3,1557,1569,1708);
        _SFD_CV_INIT_EML_FOR(0,4,1745,1757,1826);

        {
          static int condStart[] = { 817, 844 };

          static int condEnd[] = { 840, 861 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,0,817,861,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        {
          static int condStart[] = { 1323, 1351 };

          static int condEnd[] = { 1347, 1368 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,1323,1368,2,2,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
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
          real_T *c2_MAX_POWER_ALLOWED;
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
          c2_MAX_POWER_ALLOWED = (real_T *)ssGetInputPortSignal(chartInstance->S,
            2);
          c2_VALVE_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
          c2_TEMP_IN = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_TEMP_IN);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_VALVE_IN);
          _SFD_SET_DATA_VALUE_PTR(2U, c2_MAX_POWER_ALLOWED);
          _SFD_SET_DATA_VALUE_PTR(3U, *c2_LOW_SP);
          _SFD_SET_DATA_VALUE_PTR(4U, *c2_HIGH_SP);
          _SFD_SET_DATA_VALUE_PTR(5U, *c2_VALVE_OUT);
          _SFD_SET_DATA_VALUE_PTR(6U, c2_HOT_COLD);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_K_LAZYMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c2_K_LAZY(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_K_LAZYInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c2_K_LAZY((SFc2_K_LAZYInstanceStruct*) chartInstanceVar);
  initialize_c2_K_LAZY((SFc2_K_LAZYInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_K_LAZY(void *chartInstanceVar)
{
  enable_c2_K_LAZY((SFc2_K_LAZYInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_K_LAZY(void *chartInstanceVar)
{
  disable_c2_K_LAZY((SFc2_K_LAZYInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_K_LAZY(void *chartInstanceVar)
{
  sf_c2_K_LAZY((SFc2_K_LAZYInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_K_LAZY(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_K_LAZY((SFc2_K_LAZYInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_K_LAZY();/* state var info */
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

extern void sf_internal_set_sim_state_c2_K_LAZY(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_K_LAZY();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_K_LAZY((SFc2_K_LAZYInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_K_LAZY(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_K_LAZY(S);
}

static void sf_opaque_set_sim_state_c2_K_LAZY(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c2_K_LAZY(S, st);
}

static void sf_opaque_terminate_c2_K_LAZY(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_K_LAZYInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_K_LAZY((SFc2_K_LAZYInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_K_LAZY((SFc2_K_LAZYInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_K_LAZY(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_K_LAZY((SFc2_K_LAZYInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_K_LAZY(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"K_LAZY","K_LAZY",2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"K_LAZY","K_LAZY",2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"K_LAZY","K_LAZY",2,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"K_LAZY","K_LAZY",2,6);
      sf_mark_chart_reusable_outputs(S,"K_LAZY","K_LAZY",2,1);
    }

    sf_set_rtw_dwork_info(S,"K_LAZY","K_LAZY",2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(328121694U));
  ssSetChecksum1(S,(2338339288U));
  ssSetChecksum2(S,(1614401851U));
  ssSetChecksum3(S,(854386344U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_K_LAZY(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "K_LAZY", "K_LAZY",2);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_K_LAZY(SimStruct *S)
{
  SFc2_K_LAZYInstanceStruct *chartInstance;
  chartInstance = (SFc2_K_LAZYInstanceStruct *)malloc(sizeof
    (SFc2_K_LAZYInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_K_LAZYInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_K_LAZY;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_K_LAZY;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_K_LAZY;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_K_LAZY;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_K_LAZY;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_K_LAZY;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_K_LAZY;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_K_LAZY;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_K_LAZY;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_K_LAZY;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_K_LAZY;
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

void c2_K_LAZY_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_K_LAZY(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_K_LAZY(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_K_LAZY(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_K_LAZY_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
