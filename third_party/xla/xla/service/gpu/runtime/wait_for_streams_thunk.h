/* Copyright 2024 The OpenXLA Authors.

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

#ifndef XLA_SERVICE_GPU_RUNTIME_WAIT_FOR_STREAMS_THUNK_H_
#define XLA_SERVICE_GPU_RUNTIME_WAIT_FOR_STREAMS_THUNK_H_

#include <string>

#include "absl/status/status.h"
#include "xla/service/gpu/thunk.h"

namespace xla::gpu {

// This thunk
class WaitForStreamsThunk : public Thunk {
 public:
  WaitForStreamsThunk(ThunkInfo thunk_info, ExecutionStreamId stream_id,
                      std::vector<ExecutionStreamId> wait_for_stream_ids)
      : Thunk(Kind::kWaitForStreams, thunk_info),
        stream_id_(stream_id),
        wait_for_stream_ids_(wait_for_stream_ids){};

  WaitForStreamsThunk(const WaitForStreamsThunk&) = delete;
  WaitForStreamsThunk& operator=(const WaitForStreamsThunk&) = delete;

  const ExecutionStreamId& stream_id() const { return stream_id_; }

  const std::vector<ExecutionStreamId>& wait_for_stream_ids() const {
    return wait_for_stream_ids_;
  }

  absl::Status ExecuteOnStream(const ExecuteParams& params) override;

 private:
  ExecutionStreamId stream_id_;
  std::vector<ExecutionStreamId> wait_for_stream_ids_;
};

}  // namespace xla::gpu

#endif  // XLA_SERVICE_GPU_RUNTIME_WAIT_FOR_STREAMS_THUNK_H_
