/**
 * @file CParameterList.cpp
 * @author  Scott Rasmussen (scott.rasmussen@zaita.com)
 * @version 1.0
 * @date 20/02/2012
 * @section LICENSE
 *
 * Copyright NIWA Science �2011 - www.niwa.co.nz
 *
 * $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
 */

// Headers
#include "ParameterList.h"

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "Translations/Translations.h"
#include "Utilities/Logging/Logging.h"
#include "Utilities/To.h"

// Using
namespace util = isam::utilities;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

namespace isam {

/**
 * Add a single value to our parameter list
 *
 * @param label The label for the parameter
 * @param value The value of the parameter
 * @param file_name The file where the parameter was specified
 * @param line_number The line number where the parameter was specified
 * @return true on success, false on failure
 */
bool ParameterList::Add(const string& label, const vector<string>& values, const string& file_name, const unsigned& line_number) {
  if (parameters_.find(label) == parameters_.end())
    return false;

  ParameterPtr parameter = parameters_[label];
  parameter->set_values(values);
  parameter->set_file_name(file_name);
  parameter->set_line_number(line_number);

  return true;
}

/**
 * Add a single value to our parameter list
 *
 * @param label The label for the parameter
 * @param value The value of the parameter
 * @param file_name The file where the parameter was specified
 * @param line_number The line number where the parameter was specified
 * @return true on success, false on failure
 */
bool ParameterList::Add(const string& label, const string& value, const string& file_name, const unsigned& line_number) {
  vector<string> new_values;
  new_values.push_back(value);

  return this->Add(label, new_values, file_name, line_number);
}

/**
 * Add a new table to our parameter list
 *
 * @param label The label for the table
 * @param columns A vector containing the columns
 * @param data A double vector containing the data
 * @param file_name Name of file where table definition finished
 * @param line_number Line number where table definition finished
 * @return true on success, false on failure
 */
bool ParameterList::AddTable(const string& label, const vector<string>& columns, const vector<vector<string> >& data, const string& file_name, const unsigned& line_number) {
  TablePtr table = TablePtr(new isam::parameterlist::Table(label));
  table->AddColumns(columns);
  for (vector<string> row : data)
    table->AddRow(row);

  ParameterTable parameter_table;
  parameter_table.file_name_    = file_name;
  parameter_table.line_number_  = line_number;
  parameter_table.table_        = table;
  return true;
}

/**
 * Return a constant reference to one of our parameter objects.
 *
 * NOTE: This method MUST be called with a valid label otherwise
 * a reference to an empty parameter will be returned.
 *
 * @param label The parameter to return
 * @return The parameter reference
 */
const ParameterPtr ParameterList::Get(const string& label) {
  map<string, ParameterPtr>::iterator iter = parameters_.find(label);
  return iter->second;
}

/**
 * This method will copy all of the parameters from
 * the source parameter list into this parameter list.
 *
 * NOTE: The TablesPtr are not recreated.
 *
 * @param source The source parameter list
 */
void ParameterList::CopyFrom(const ParameterList& source) {
//  map<string, ParameterPtr>::const_iterator iter;
//  for (iter = source.parameters_.begin(); iter != source.parameters_.end(); ++iter)
//    parameters_.insert(std::pair<const string, Parameter>(iter->first, iter->second));
//
//  map<string, ParameterTable>::const_iterator iter2;
//  for (iter2 = source.tables_.begin(); iter2 != source.tables_.end(); ++iter2)
//    tables_[iter2->first] = iter2->second;
}

/**
 * Find the location string for one of our parameters.
 *
 * @param label The label for the parameter
 * @return The location string for an error message
 */
string ParameterList::location(const string& label) {
  map<string, ParameterPtr>::iterator iter = parameters_.find(label);
  if (iter == parameters_.end()) {
    LOG_CODE_ERROR("parameters_ object is missing the parameter: " << label);
  }

  return iter->second->location() + ": " + label;
}

} /* namespace isam */
