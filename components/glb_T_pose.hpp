#pragma once

#include <iostream>
#include "DSPatch.h"
#include "pipelines.hpp"

namespace DSPatch {

class glb_T_pose final : public Component {

public:
    glb_T_pose(AvatarBuild::cmd_options* options)
        : Component()
        , options(options)
    {
        SetInputCount_(3);
        SetOutputCount_(3);
    }

    virtual ~glb_T_pose()
    {
    }

protected:
    virtual void Process_(SignalBus const& inputs, SignalBus& outputs) override
    {
        // just return immediately when there's critical error in previous component
        const auto discarded = inputs.GetValue<bool>(0);
        if (discarded && *discarded) {
            Reset();
            return;
        }

        AVATAR_COMPONENT_LOG("[INFO] glb_T_pose");

        const auto data_ptr = inputs.GetValue<cgltf_data*>(1);
        const auto bones_ptr = inputs.GetValue<AvatarBuild::bone_mappings*>(2);

        if (data_ptr && bones_ptr) {
            cgltf_data* data = *data_ptr;
            AvatarBuild::bone_mappings* mappings = *bones_ptr;
            if (gltf_apply_pose("T", mappings)) {
                gltf_skinning(data);            
                gltf_update_inverse_bind_matrices(data);
            }
            outputs.SetValue(0, false); // discarded
            outputs.SetValue(1, data);  // data
            outputs.SetValue(2, *bones_ptr);  // bone_mappings
        } else {
            AVATAR_COMPONENT_LOG("[ERROR] glb_T_pose: input.1 not found");
            outputs.SetValue(0, true);    // discarded
        }
    }

    AvatarBuild::cmd_options* options;
};

} // namespace DSPatch