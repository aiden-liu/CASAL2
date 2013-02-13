/**
 * @file Partition.h
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @version 1.0
 * @date 13/02/2013
 * @section LICENSE
 *
 * Copyright NIWA Science �2013 - www.niwa.co.nz
 *
 * @section DESCRIPTION
 *
 * This report will print the partition for the target
 * time step and year
 *
 * $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
 */
#ifndef REPORTS_PARTITION_H_
#define REPORTS_PARTITION_H_

// Headers
#include "Reports/Report.h"

// Namespaces
namespace isam {
namespace reports {

/**
 *
 */
class Partition : public isam::Report {
public:
  Partition();
  virtual                     ~Partition() = default;
  void                        Execute() override final;
};

} /* namespace reports */
} /* namespace isam */
#endif /* REPORTS_PARTITION_H_ */
