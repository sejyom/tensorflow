/* Copyright 2020 The OpenXLA Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef XLA_SERVICE_COMPARISON_EXPANDER_H_
#define XLA_SERVICE_COMPARISON_EXPANDER_H_

#include <utility>
#include <vector>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "xla/hlo/ir/hlo_instruction.h"
#include "xla/primitive_util.h"
#include "xla/service/op_expander_pass.h"
#include "xla/statusor.h"
#include "xla/xla_data.pb.h"

namespace xla {

// A pass which performs expansion of the comparison operator to support total
// order comparison of floating point numbers.
class ComparisonExpander : public OpExpanderPass {
 public:
  explicit ComparisonExpander(
      absl::Span<const std::pair<PrimitiveType, PrimitiveType>>
          expand_via_upcast = {})
      : expand_via_upcast_(expand_via_upcast.begin(), expand_via_upcast.end()) {
  }
  ~ComparisonExpander() override = default;
  absl::string_view name() const override { return "comparison-expander"; }

 private:
  // Returns `true` if `instruction` should be expanded by this pass.
  bool InstructionMatchesPattern(HloInstruction* instruction) override;
  // Returns a replacement for `instruction`, or nullptr if no replacement is
  // needed (e.g. only the to_apply subcomputation of the instruction was
  // modified).
  StatusOr<HloInstruction*> ExpandInstruction(
      HloInstruction* instruction) override;

  std::vector<std::pair<PrimitiveType, PrimitiveType>> expand_via_upcast_;
};

}  // namespace xla

#endif  // XLA_SERVICE_COMPARISON_EXPANDER_H_
