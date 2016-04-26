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

/******************************************************************************
 * File:        metrics_stdout.h
 * Description: Metrics class printing to stdout.
 *****************************************************************************/

#ifndef METRICS_STDOUT_H
#define METRICS_STDOUT_H

#include <pthread.h>
#include <stdint.h>
#include <string>

#include "common/metrics.h"
#include "ue_metrics_interface.h"

namespace srsue {

class metrics_stdout : public metrics
{
public:
  metrics_stdout() {}
  ~metrics_stdout() {}

  bool init(ue_metrics_interface *u, float report_period_secs=1.0) {}
  void stop() {}
  void toggle_print(bool b);
  static void* metrics_thread_start(void *m);
  void metrics_thread_run();

private:
  void        print_metrics();
  void        print_disconnect();
};

} // namespace srsue

#endif // METRICS_STDOUT_H
