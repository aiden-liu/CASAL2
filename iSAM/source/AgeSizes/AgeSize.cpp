/*
 * AgeSize.cpp
 *
 *  Created on: 24/07/2013
 *      Author: Admin
 */

#include "AgeSize.h"

namespace isam {

/**
 *
 */
AgeSize::AgeSize() {
  parameters_.RegisterAllowed(PARAM_LABEL, ParameterType::String, "Label");
  parameters_.RegisterAllowed(PARAM_TYPE, ParameterType::String, "Type");

}

/**
 *
 */
void AgeSize::Validate() {
  CheckForRequiredParameter(PARAM_LABEL);
  CheckForRequiredParameter(PARAM_TYPE);

  label_ = parameters_.Get(PARAM_LABEL).GetValue<string>();

  DoValidate();
}

} /* namespace isam */
