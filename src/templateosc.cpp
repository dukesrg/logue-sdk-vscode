#include "userosc.h"

void OSC_INIT(__attribute__((unused)) uint32_t platform, __attribute__((unused)) uint32_t api)
{

}

void OSC_CYCLE(const user_osc_param_t * const params, int32_t *yn, const uint32_t frames)
{

}

void OSC_NOTEON(const user_osc_param_t * const params)
{

}

void OSC_NOTEOFF(__attribute__((unused)) const user_osc_param_t * const params)
{

}

void OSC_PARAM(uint16_t index, uint16_t value)
{
  switch (index) {
    case k_user_osc_param_shape:

      break;
    case k_user_osc_param_shiftshape:

      break;
    case k_user_osc_param_id1:

      break;
    case k_user_osc_param_id2:

      break;
    case k_user_osc_param_id3:

      break;
    case k_user_osc_param_id4:

      break;
    case k_user_osc_param_id5:

      break;
    case k_user_osc_param_id6:

      break;
    default:
      break;
  }
}
