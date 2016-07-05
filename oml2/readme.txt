README: Basic procedure to get the OML2-instrumented version of srsUE built
===========================================================================

Build instructions (based on [2]);

$ sudo sh -c "echo 'deb http://download.opensuse.org/repositories/devel:/tools:/mytestbed:/stable/xUbuntu_14.04/ /' >> /etc/apt/sources.list.d/oml2.list"
$ sudo apt-get update
$ sudo apt-get install oml2 liboml2-dev oml2-server

$ git clone https://github.com/srsLTE/srsUE
$ cd srsUE
$ git checkout oml2_client
$ mkdir build
$ cmake ..
$ make

To run the test application and let the output go to the stdout
$ ue/test/metrics_oml2_test --oml-id ue --oml-domain ue --oml-collect file:-

.. or to the oml2-server running on the localhost

$ ue/test/metrics_oml2_test --oml-id ue --oml-domain ue --oml-collect localhost

To check the log of the oml2-server run:

$ cat /var/log/oml2-server.log

And to actually view the database content, run:

$ sqlite3 /var/lib/oml2/ue.sq3 .dump

To graphically display the results, use the provided plotting tool. For example,
to plot the downlink maximum achievable bitrate (random values), run;

$ ../oml2/plot_oml.py --db /var/lib/oml2/ue.sq3 -y dl_mabr

or

$ ../oml2/plot_oml.py --db /var/lib/oml2/ue.sq3 -t srsue_mac -y ul_buffer


To run the UE in the FLEX testbed with OAI configured in noS1 mode, run:

$ ./ue/src/ue ../ue.conf --expert.skip_mme_attach true --expert.pdn_ip_addr 10.0.2.9 \
        --oml-id srsue --oml-domain srsue --oml-collect tcp:nitlab3.inf.uth.gr:3003


Notes;
At the moment, the test is not integrated into the srsUE CMake test suite .

oml2-scaffold is used to create the code used to talk to the OML2 server.
OML2-scaffold is called from CMake but can also be called manually to 
generate srsue_oml2.h.

$ oml2-scaffold --oml srsue.rb.in


[1] https://oml.mytestbed.net/projects/oml/wiki/Quick_Start_Tutorial
[2] https://mytestbed.net/projects/oml/wiki/Installation
