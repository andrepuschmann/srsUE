/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2016 Software Radio Systems Limited
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

/******************************************************************************
 * File:        metrics.h
 * Description: Base metrics class.
 *****************************************************************************/

#ifndef METRICS_H
#define METRICS_H

#include <pthread.h>
#include <stdint.h>
#include <string>

#include "ue_metrics_interface.h"

namespace srsue {

class metrics
{
  friend class metrics_stdout;

public:
  metrics(int report_period_secs=1);
  virtual ~metrics() {}

  bool init(ue_metrics_interface *u, float report_period_secs);
  void stop();
  void toggle_active(bool b);
  static void* metrics_thread_start(void *m);
  virtual void metrics_thread_run() = 0;

private:
  void        print_metrics();
  void        print_disconnect();
  std::string float_to_string(float f, int digits);
  std::string float_to_eng_string(float f, int digits);
  std::string int_to_eng_string(int f, int digits);

  ue_metrics_interface *ue_;

  bool          started;
  bool          is_active;
  pthread_t     metrics_thread;
  ue_metrics_t  metrics_container;
  float         metrics_report_period; // seconds
  uint8_t       n_reports;
};

} // namespace srsue

#endif // METRICS_H
