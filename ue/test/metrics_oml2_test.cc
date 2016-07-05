/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2015 Software Radio Systems Limited
 *
 * \section LICENSE
 *
 * This file is part of the srsUE library.
 *
 * srsUE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsUE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include <iostream>
#include "ue.h"
#include "metrics_oml2.h"

using namespace srsue;

double get_random(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

// dummy UE to obtain metrics from
class fake_ue : public ue_metrics_interface
{
public:
    bool get_metrics(ue_metrics_t &m)
    {
        memset((void *)&m, 0, sizeof(ue_metrics_t));
        m.rf.rf_error = false;

        m.phy.dl.sinr = -11.0; // SINR is always constant
        m.phy.dl.mabr_mbps = get_random(0.0, 100.0); // Maximum achievable bitrate is random
        m.phy.ul.mabr_mbps = get_random(0.0, 75.0);
        m.phy.dl.mcs = get_random(0.0, 28.0);
        m.phy.ul.mcs = get_random(0.0, 28.0);
        m.phy.dl.rsrp = rand() % 100;

        m.gw.dl_tput_mbps = get_random(0.0, 100.0);
        m.gw.ul_tput_mbps = get_random(0.0, 75.0);

        m.mac.ul_buffer = rand() % 100;

        m.rlc.dl_tput_mbps = get_random(0.0, 100.0);
        m.rlc.ul_tput_mbps = get_random(0.0, 75.0);

        return true;
    }
};


int main(int argc, char **argv)
{
    // create dummy UE object
    fake_ue *ue;
    ue = new(fake_ue);

    // create a metric object that uses OML2 and let the UE use it
    metrics_oml2 metrics;
    metrics.init(ue, 0.5,  argc, argv);
    metrics.toggle_print(true);

    // let the UE run for a while
    sleep(5);

    // cleanup everything
    metrics.stop();
    delete(ue);
}

