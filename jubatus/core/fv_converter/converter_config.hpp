// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2011 Preferred Infrastructure and Nippon Telegraph and Telephone Corporation.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License version 2.1 as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef JUBATUS_CORE_FV_CONVERTER_CONVERTER_CONFIG_HPP_
#define JUBATUS_CORE_FV_CONVERTER_CONVERTER_CONFIG_HPP_

#include <map>
#include <string>
#include <vector>
#include "jubatus/util/data/serialization.h"
#include "jubatus/util/data/optional.h"
#include "jubatus/util/lang/shared_ptr.h"
#include "jubatus/util/text/json.h"
#include "type.hpp"

namespace jubatus {
namespace core {
namespace fv_converter {

class datum_to_fv_converter;

struct string_rule {
  std::string key;
  jubatus::util::data::optional<std::string> except;
  std::string type;
  std::string sample_weight;
  std::string global_weight;

  friend class jubatus::util::data::serialization::access;
  template<class Archive>
  void serialize(Archive& ar) {
    ar
        & JUBA_MEMBER(key)
        & JUBA_MEMBER(except)
        & JUBA_MEMBER(type)
        & JUBA_MEMBER(sample_weight)
        & JUBA_MEMBER(global_weight);
  }
};

struct filter_rule {
  std::string key;
  jubatus::util::data::optional<std::string> except;
  std::string type;
  std::string suffix;

  friend class jubatus::util::data::serialization::access;
  template<class Archive>
  void serialize(Archive& ar) {
    ar
        & JUBA_MEMBER(key)
        & JUBA_MEMBER(except)
        & JUBA_MEMBER(type)
        & JUBA_MEMBER(suffix);
  }
};

struct num_rule {
  std::string key;
  jubatus::util::data::optional<std::string> except;
  std::string type;

  friend class jubatus::util::data::serialization::access;
  template<class Archive>
  void serialize(Archive& ar) {
    ar & JUBA_MEMBER(key) & JUBA_MEMBER(except) & JUBA_MEMBER(type);
  }
};

struct binary_rule {
  std::string key;
  jubatus::util::data::optional<std::string> except;
  std::string type;

  friend class jubatus::util::data::serialization::access;
  template<class Archive>
  void serialize(Archive& ar) {
    ar & JUBA_MEMBER(key) & JUBA_MEMBER(type);
  }
};

struct converter_config {
  jubatus::util::data::optional<std::map<std::string, param_t> >
    string_filter_types;
  jubatus::util::data::optional<std::vector<filter_rule> > string_filter_rules;

  jubatus::util::data::optional<std::map<std::string, param_t> >
    num_filter_types;
  jubatus::util::data::optional<std::vector<filter_rule> > num_filter_rules;

  jubatus::util::data::optional<std::map<std::string, param_t> > string_types;
  jubatus::util::data::optional<std::vector<string_rule> > string_rules;

  jubatus::util::data::optional<std::map<std::string, param_t> > num_types;
  jubatus::util::data::optional<std::vector<num_rule> > num_rules;

  jubatus::util::data::optional<std::map<std::string, param_t> > binary_types;
  jubatus::util::data::optional<std::vector<binary_rule> > binary_rules;

  jubatus::util::data::optional<int64_t> hash_max_size;

  friend class jubatus::util::data::serialization::access;
  template<class Archive>
  void serialize(Archive& ar) {
    ar
        & JUBA_MEMBER(string_filter_types)
        & JUBA_MEMBER(string_filter_rules)
        & JUBA_MEMBER(num_filter_types)
        & JUBA_MEMBER(num_filter_rules)
        & JUBA_MEMBER(string_types)
        & JUBA_MEMBER(string_rules)
        & JUBA_MEMBER(num_types)
        & JUBA_MEMBER(num_rules)
        & JUBA_MEMBER(binary_types)
        & JUBA_MEMBER(binary_rules)
        & JUBA_MEMBER(hash_max_size);
  }
};


class factory_extender;

void initialize_converter(
    const converter_config& config,
    datum_to_fv_converter& converter,
    const factory_extender* = NULL);

jubatus::util::lang::shared_ptr<datum_to_fv_converter> make_fv_converter(
    const converter_config& config,
    const factory_extender* = NULL);

}  // namespace fv_converter
}  // namespace core
}  // namespace jubatus

#endif  // JUBATUS_CORE_FV_CONVERTER_CONVERTER_CONFIG_HPP_
