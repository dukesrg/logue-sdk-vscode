#include "fxwrapper.h"

FX_INIT
{

}

FX_PROCESS
{

}

FX_PARAM
{
  float valf = q31_to_f32(value);
  switch (index) {
  case FX_PARAM_TIME:

    break;
  case FX_PARAM_DEPTH:

    break;
#ifndef FX_MODFX
  case FX_PARAM_SHIFT_DEPTH:

    break;
#endif
  default:
    break;
  }
}
