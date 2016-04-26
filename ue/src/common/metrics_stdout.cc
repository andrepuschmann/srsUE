/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2015 The srsUE Developers. See the
 * COPYRIGHT file at the top-level directory of this distribution.
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

#include "common/metrics_stdout.h"

#include <unistd.h>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <iomanip>
#include <iostream>

using namespace std;

namespace srsue{

char const * const prefixes[2][9] =
{
  {   "",   "m",   "u",   "n",    "p",    "f",    "a",    "z",    "y", },
  {   "",   "k",   "M",   "G",    "T",    "P",    "E",    "Z",    "Y", },
};

void metrics_stdout::metrics_thread_run()
{
  while(started)
  {
    usleep(metrics_report_period*1e6);
    if(ue_->get_metrics(metrics_container)) {
      print_metrics();
    } else {
      print_disconnect();
    }
  }
}

void metrics_stdout::print_metrics()
{
  if(!is_active)
    return;

  if(++n_reports > 10)
  {
    n_reports = 0;
    cout << endl;
    cout << "--Signal--------------DL------------------------------UL----------------------" << endl;
    cout << "  rsrp    pl    cfo   mcs   snr turbo  brate   bler   mcs   buff  brate   bler" << endl;
  }
  cout << float_to_string(metrics_container.phy.dl.rsrp, 2);
  cout << float_to_string(metrics_container.phy.dl.pathloss, 2);
  cout << float_to_eng_string(metrics_container.phy.sync.cfo, 2);
  cout << float_to_string(metrics_container.phy.dl.mcs, 2);
  cout << float_to_string(metrics_container.phy.dl.sinr, 2);
  cout << float_to_string(metrics_container.phy.dl.turbo_iters, 2);
  cout << float_to_eng_string((float) metrics_container.mac.rx_brate/metrics_report_period, 2);
  if (metrics_container.mac.rx_pkts > 0) {
    cout << float_to_string((float) 100*metrics_container.mac.rx_errors/metrics_container.mac.rx_pkts, 1) << "%";
  } else {
    cout << float_to_string(0, 2) << "%";
  }
  cout << float_to_string(metrics_container.phy.ul.mcs, 2);
  cout << float_to_eng_string((float) metrics_container.mac.ul_buffer, 2);
  cout << float_to_eng_string((float) metrics_container.mac.tx_brate/metrics_report_period, 2);
  if (metrics_container.mac.tx_pkts > 0) {
    cout << float_to_string((float) 100*metrics_container.mac.tx_errors/metrics_container.mac.tx_pkts, 1) << "%";
  } else {
    cout << float_to_string(0, 2) << "%";
  }
  cout << endl;

  if(metrics_container.rf.rf_error) {
    cout << "RF status:"
         << "  O=" << metrics_container.rf.rf_o
         << ", U=" << metrics_container.rf.rf_u
         << ", L=" << metrics_container.rf.rf_l << endl;
  }
  
}

void metrics_stdout::print_disconnect()
{
  if(is_active) {
    cout << "--- disconnected ---" << endl;
  }
}

} // namespace srsue
