#pragma once

#include "DSPatch.h"
#include <string>
#include <iostream>
#include <vector>

#include "pipelines.hpp"
#include "gltf_bone_mappings.inl"

namespace AvatarBuild {

class gltf_pipeline final : public pipeline_processor {

public:
    gltf_pipeline(std::string name, cmd_options* options)
        : pipeline_processor(name, options)
        , data(nullptr)
        , gltf_options{}
    {

    }

    virtual ~gltf_pipeline()
    {

    }

protected:
    virtual void Process_(DSPatch::SignalBus const&, DSPatch::SignalBus&) override
    {
        AVATAR_PIPELINE_LOG("[INFO] gltf_pipeline start");

        if (data != nullptr) {
            AVATAR_PIPELINE_LOG("[WARN] cgltf_data leak detected. Make sure it's freed before pipeline exits.");
            cgltf_free(data);
        }

        const std::string input = state.options->input;

        cgltf_result result = cgltf_parse_file(&gltf_options, input.c_str(), &data);

        if (result != cgltf_result_success) {
            AVATAR_PIPELINE_LOG("[ERROR] failed to parse file " << input);
            return;
        }

        result = cgltf_load_buffers(&gltf_options, data, input.c_str());

        if (result != cgltf_result_success) {
            AVATAR_PIPELINE_LOG("[ERROR] failed to load buffers from " << input);
            return;
        }

        state.data = data;

        gltf_setup_bone_mappings(data, state.options);

        circuit->Tick(DSPatch::Component::TickMode::Series);
       
        if (!state.discarded) {
            result = cgltf_validate(data);

            if (result == cgltf_result_success) {
                state.discarded = !gltf_write_file(data, state.options->output);
                if (state.discarded) {
                    AVATAR_PIPELINE_LOG("[ERROR] faild to write output " << state.options->output);                
                }
            } else {
                state.discarded = true;
                AVATAR_PIPELINE_LOG("[WARN] Invalid glTF data: " << result);
            }
        }

        cgltf_free(data);
        data = nullptr;

        if (!state.discarded) {
            AVATAR_PIPELINE_LOG("[INFO] gltf_pipeline finished without errors");
        }
    }

    cgltf_data* data;
    cgltf_options gltf_options;

};

} // namespace Avatar