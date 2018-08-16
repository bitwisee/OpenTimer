#ifndef OT_LIBERTY_LIBERTY_HPP_
#define OT_LIBERTY_LIBERTY_HPP_

#include <ot/liberty/cell.hpp>
#include <ot/unit/unit.hpp>

namespace ot {

// Enum: DelayModel
enum class DelayModel {
  GENERIC_CMOS,
  TABLE_LOOKUP,
  CMOS2,
  PIECEWISE_CMOS,
  DCM,
  POLYNOMIAL
};

inline const std::unordered_map<std::string_view, DelayModel> delay_models {
  {"generic_cmos",   DelayModel::GENERIC_CMOS},
  {"table_lookup",   DelayModel::TABLE_LOOKUP},
  {"cmos2",          DelayModel::CMOS2},
  {"piecewise_cmos", DelayModel::PIECEWISE_CMOS},
  {"dcm",            DelayModel::DCM},
  {"polynomial",     DelayModel::POLYNOMIAL}
};

// Function: to_string
std::string to_string(DelayModel);

// Class: Celllib
struct Celllib {
  
  using token_iterator = std::vector<std::string_view>::iterator;

  std::string name {"OpenTimer"};

  std::optional<DelayModel> delay_model;

  std::optional<float> default_cell_leakage_power;
  std::optional<float> default_inout_pin_cap;
  std::optional<float> default_input_pin_cap;
  std::optional<float> default_output_pin_cap;
  std::optional<float> default_fanout_load;
  std::optional<float> default_max_fanout;
  std::optional<float> default_max_transition;

  std::unordered_map<std::string, LutTemplate> lut_templates;
  std::unordered_map<std::string, Cell> cells;

  void read(const std::filesystem::path&);

  const LutTemplate* lut_template(const std::string&) const;
  const Cell* cell(const std::string&) const;
  
  LutTemplate* lut_template(const std::string&);
  Cell* cell(const std::string&);

  private:

    LutTemplate _extract_lut_template(token_iterator&, const token_iterator);
    Lut         _extract_lut         (token_iterator&, const token_iterator);
    Cell        _extract_cell        (token_iterator&, const token_iterator);
    Cellpin     _extract_cellpin     (token_iterator&, const token_iterator);
    Timing      _extract_timing      (token_iterator&, const token_iterator);

    void _apply_default_values();
    void _uncomment(std::vector<char>&);
    void _tokenize(const std::vector<char>&, std::vector<std::string_view>&);
};

// Operator <<
std::ostream& operator << (std::ostream&, const Celllib&);


};  // end of namespace ot. -----------------------------------------------------------------------


#endif










