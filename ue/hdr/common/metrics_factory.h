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
 * File:        metrics_factory.h
 * Description: Basic factory class to create metrics objects.
 *****************************************************************************/

#ifndef METRICS_FACTORY_H
#define METRICS_FACTORY_H

#include "metrics_stdout.h"

namespace srsue {

  typedef enum{
    METRICS_STDOUT = 0,
    METRICS_N_ITEMS,
  } metrics_t;

  class metrics_factory
  {
  public:
    static metrics* make_metrics(const metrics_t choice)
    {
      switch (choice) {
        case METRICS_STDOUT:
          return new metrics_stdout();
        default:
          return NULL;
        }
    }
  };

} // namespace srsue

#endif // METRICS_FACTORY_H
