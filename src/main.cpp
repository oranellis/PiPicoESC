//  ____  _ ____  _           _____ ____   ____
// |  _ \(_)  _ \(_) ___ ___ | ____/ ___| / ___|
// | |_) | | |_) | |/ __/ _ \|  _| \___ \| |
// |  __/| |  __/| | (_| (_) | |___ ___) | |___
// |_|   |_|_|   |_|\___\___/|_____|____/ \____|
//
// The program entrypoint
//
// Authors: Oran Ellis, Karl Hartmann
// Licence: GPLv3

#include "loops.h"

#include "pico/time.h"

int main() {

	int errorcode = 0;
	unsigned long long loop_start_us = 0;
	unsigned long loop_period_us = 0;

	while (!errorcode) {

		if (!errorcode) {

			DriveLoop(&errorcode);

		}

	}

	return errorcode;

}
