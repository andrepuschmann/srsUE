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
#include "common/metrics_factory.h"

using namespace srsue;

double get_random(double min, double max)
{
  double f = (double)rand() / RAND_MAX;
  return min + f * (max - min);
}

// dummy UE to obtain metrics from
class dummy_ue : public ue_metrics_interface
{
public:
  bool get_metrics(ue_metrics_t &m)
  {
    rf_metrics_t rf;
    rf.rf_error = false;
    m.rf = rf;

    phy_metrics_t phy;
    phy.dl.mabr_mbps = get_random(0.0, 100.0);
    phy.ul.mabr_mbps = get_random(0.0, 75.0);
    phy.dl.rsrp = rand() % 100;
    m.phy = phy;

    gw_metrics_t gw;
    gw.dl_tput_mbps = get_random(0.0, 100.0);
    gw.ul_tput_mbps = get_random(0.0, 75.0);
    m.gw = gw;

    mac_metrics_t mac;
    mac.ul_buffer = rand() % 100;
    m.mac = mac;

    rlc_metrics_t rlc;
    rlc.dl_tput_mbps = get_random(0.0, 100.0);
    rlc.ul_tput_mbps = get_random(0.0, 75.0);
    m.rlc = rlc;

    return true;
  }
};

int main(int argc, char **argv)
{
  // create dummy UE object
  dummy_ue *ue;
  ue = new(dummy_ue);
  if (ue != NULL) {
     // create a metric object that uses OML2 and let the UE use it
      float interval = 1.0;
      metrics* metrics = metrics_factory::make_metrics(METRICS_STDOUT);
      metrics->init(ue, interval);
      metrics->toggle_active(true);

      // let the UE run for a while
      sleep(5);

      // cleanup everything
      metrics->stop();
      delete(ue);
      delete(metrics);
  }
}
