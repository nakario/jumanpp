//
// Created by Arseny Tolmachev on 2017/02/23.
//

#ifndef JUMANPP_SPEC_TYPES_H
#define JUMANPP_SPEC_TYPES_H

#include <vector>
#include "util/string_piece.h"
#include "util/types.hpp"

namespace jumanpp {
namespace core {
namespace spec {

enum class ColumnType { String, Int, StringList, Error };

std::ostream& operator<<(std::ostream& o, ColumnType ct);

struct FieldDescriptor {
  i32 index = -1;
  i32 position;
  std::string name;
  bool isTrieKey = false;
  ColumnType columnType = ColumnType::Error;
  StringPiece emptyString = StringPiece{""};
};

enum class PrimitiveFeatureKind {
  Invalid,
  Copy,
  MatchDic,
  MatchAnyDic,
  Provided,
  Length
};

struct PrimitiveFeatureDescriptor {
  i32 index;
  std::string name;
  PrimitiveFeatureKind kind;
  std::vector<i32> references;
  std::vector<std::string> matchData;
};

struct MatchReference {
  i32 featureIdx;
  i32 dicFieldIdx;
};

struct ComputationFeatureDescriptor {
  i32 index;
  std::string name;
  std::vector<MatchReference> matchReference;
  std::vector<std::string> matchData;
  std::vector<i32> trueBranch;
  std::vector<i32> falseBranch;
};

struct PatternFeatureDescriptor {
  i32 index;
  std::vector<i32> references;
};

struct FinalFeatureDescriptor {
  i32 index;
  std::vector<i32> references;
};

struct FeaturesSpec {
  std::vector<PrimitiveFeatureDescriptor> primitive;
  std::vector<ComputationFeatureDescriptor> computation;
  std::vector<PatternFeatureDescriptor> pattern;
  std::vector<FinalFeatureDescriptor> final;
  i32 totalPrimitives = -1;
};

struct AnalysisSpec {
  std::vector<FieldDescriptor> columns;
  i32 indexColumn = -1;
  FeaturesSpec features;
};

}  // spec
}  // core
}  // jumanpp

#endif  // JUMANPP_SPEC_TYPES_H