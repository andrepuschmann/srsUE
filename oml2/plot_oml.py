#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# Copyright 2016 The srsUE Developers. See the
# COPYRIGHT file at the top-level directory of this distribution.
#
# This file is part of the srsUE library.
# srsUE is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of
# the License, or (at your option) any later version.
#
# srsUE is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# A copy of the GNU Affero General Public License can be found in
# the LICENSE file in the top-level directory of this distribution
# and at http://www.gnu.org/licenses/.
# 

import sqlite3 as lite
import sys
from optparse import OptionParser
import matplotlib.pyplot as plt

def main():
    usage = "usage: %prog [options] arg"
    parser = OptionParser(usage)
    parser.add_option('--db', '-d', action='store', dest='db_path', type='string',
                    help='path to an OML sqlite database')
    parser.add_option('-t', action='store', dest='tables', default='srsue_phy',
                    help='Table name, e.g., srsue_phy, srsue_mac, srsue_gw')
    parser.add_option("-x", dest="x", default='oml_tuple_id', type='string',
                      help="Which values to use for x axis, e.g., oml_tuple_id, oml_ts_client")                     
    parser.add_option("-y", dest="y", default='dl_mabr', type='string',
                      help="Which values to use for y axis, e.g., dl_sinr, dl_mabr")
    parser.add_option('--xtitle', action='append', dest='x_title', default='ID',
                    help='add a title to the X-axis')
    parser.add_option('--ytitle', action='store', dest='y_title', default='Downlink MABR',
                    help='add a title to the Y-axis')  
    parser.add_option("-o", "--output", dest="outfile",
                      help="Write output to file", metavar="FILE")
    parser.add_option("-c", "--console", help="Plot results to console",
                      action="store_true", dest="console", default=False)


    # turn command line parameters into local variables
    (options, args) = parser.parse_args()
    
    if (not options.db_path):
        parser.error("Please specify database path.")
    
    con = None

    try:
        # initialize values
        x_values=[]
        y_values=[]
        
        # setup database connection
        con = lite.connect(options.db_path)
        cur = con.cursor()
        sql = 'SELECT {x}, {y} FROM {table}'.format(x=options.x, y=options.y, table=options.tables)
        print sql
        cur.execute(sql)

        # fetch results
        results = cur.fetchall()
        for record in results:
            x_values.append(record[0])
            y_values.append(record[1])
        
        # print raw data to console
        if options.console:
            for i in range(len(x_values)):
                print "%2.0f\t%2.0f" % (x_values[i], y_values[i])        
        
        # plot using matplotlib
        plt.plot(x_values, y_values)
        plt.xlabel(options.x_title, fontsize=12)
        plt.ylabel(options.y_title, fontsize=12)
        if options.outfile:
            plt.savefig(options.outfile)
        plt.show()
        
    except lite.Error, e:
        print "Error %s:" % e.args[0]
        sys.exit(1)
        
    finally:
        if con:
            con.close()

if __name__ == "__main__":
    main()
