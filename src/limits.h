//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#pragma once

#define N_MODULES 3
#define CELLS_PER_MODULE 12

struct limits {

    constexpr static float cell_v_min = 3.4;
    constexpr static float cell_v_max = 3.75;

    constexpr static float v_hv_min = 122.4;
    constexpr static float v_hv_max = 135.0;

};
