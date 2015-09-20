/**
 * @file MortalityInstantaneous.h
 * @author Scott Rasmussen (scott.rasmussen@zaita.com)
 * @github https://github.com/Zaita
 * @date 28/07/2015
 * @section LICENSE
 *
 * Copyright NIWA Science �2015 - www.niwa.co.nz
 *
 * @section DESCRIPTION
 *
 * This mortality process is a combination of the
 * constant and event mortality processes.
 */
#ifndef SOURCE_PROCESSES_CHILDREN_MORTALITYINSTANTANEOUS_H_
#define SOURCE_PROCESSES_CHILDREN_MORTALITYINSTANTANEOUS_H_

// headers
#include "Model/Model.h"
#include "Partition/Accessors/Categories.h"
#include "Penalties/Children/Process.h"
#include "Processes/Process.h"
#include "Selectivities/Selectivity.h"
#include "Utilities/Map.h"

// namespaces
namespace niwa {
namespace processes {

namespace accessor = niwa::partition::accessors;
using utilities::map3D;
using utilities::map2D;

// classes
class MortalityInstantaneous : public Process {
 /**
 * FisheryData holds all the information related to a fishery
 */
  struct FisheryData {
    string          label_;
    string          time_step_label_;
    unsigned        time_step_index_;
    Double          u_max_;
    string          penalty_label_;
    PenaltyPtr      penalty_;
    map<unsigned, Double>  catches_;
  };
  /**
   * FisheryCategoryData is used to store 1 Fishery x Category x Selectivity
   */
  struct FisheryCategoryData {
    FisheryCategoryData(FisheryData& x) : fishery_(x) { };
    string          fishery_label_;
    string          category_label_;
    string          selectivity_label_;
    SelectivityPtr  selectivity_;
    FisheryData&    fishery_;
  };
public:
  // methods
  MortalityInstantaneous();
  virtual                     ~MortalityInstantaneous() = default;
  void                        DoValidate() override final;
  void                        DoBuild() override final;
  void                        DoReset() override final { };
  void                        DoExecute() override final;
  Double                      GetMBySelectivity(const string& category_label, unsigned age);
  Double                      GetFisheryExploitationFraction(const string& fishery_label, const string& category_label, unsigned age);
  bool                        IsFisheryValid(const string& fishery_label);

  // accessors
  Double                      time_step_ratio();

private:
  // members
  vector<string>              category_labels_;
  vector<FisheryCategoryData> fishery_categories_;
  map<string, FisheryData>    fisheries_;
  parameters::TablePtr        catches_table_;
  parameters::TablePtr        fisheries_table_;
  accessor::Categories        partition_;
  Double                      current_m_ = 0.0;
  map<string, Double>         fishery_exploitation;
  // members from mortality event
  Double                      u_max_;
  string                      penalty_label_ = "";
  penalties::ProcessPtr       penalty_;
  // members from natural mortality
  vector<Double>              m_;
  vector<Double>              time_step_ratios_temp_;
  map<unsigned, Double>       time_step_ratios_;
  vector<string>              selectivity_labels_;
  vector<SelectivityPtr>      selectivities_;
};

} /* namespace processes */
} /* namespace niwa */

#endif /* SOURCE_PROCESSES_CHILDREN_MORTALITYINSTANTANEOUS_H_ */
