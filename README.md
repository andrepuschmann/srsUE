srsUE
========

srsUE is a software radio LTE UE developed by SRS (www.softwareradiosystems.com). It is written in C++ and builds upon the srsLTE library (https://github.com/srslte/srslte). Running on an Intel Core i7-4790, srsUE achieves up to 60Mbps DL with a 20Mhz bandwidth SISO configuration.
srsUE is released under the AGPLv3 license and uses software from the OpenLTE project (http://sourceforge.net/projects/openlte) for some security functions and for RRC/NAS message parsing.

*News*: We have just released srsUE 1.2 containing important bugfixes and improvements in the synchronization procedure. Checkout the [CHANGELOG](CHANGELOG).  

Features
--------

### PHY Layer
 
 * LTE Release 8 compliant
 * FDD configuration
 * Tested bandwidths: 1.4, 3, 5, 10, 15 and 20 MHz
 * Transmission mode 1 (single antenna) and 2 (transmit diversity) 
 * Cell search and synchronization procedure for the UE
 * Frequency-based ZF and MMSE equalizer
 * Highly optimized turbo decoder available in Intel SSE4.1/AVX (+100 Mbps) and standard C (+25 Mbps)

### Upper Layers

 * LTE Release 8 compliant
 * MAC, RLC, PDCP, RRC, NAS and GW layers
 * Soft USIM supporting Milenage and XOR authentication

### User Interfaces

 * Detailed log system with per-layer log levels and hex dumps
 * MAC layer wireshark packet capture
 * Command-line trace metrics
 * Detailed input configuration file

### Network Interfaces

 * Virtual network interface *tun_srsue* created upon network attach

Hardware
--------

The library currently supports the Ettus Universal Hardware Driver (UHD) and the bladeRF driver. Thus, any hardware supported by UHD or bladeRF can be used. There is no sampling rate conversion, therefore the hardware should support 30.72 MHz clock in order to work correctly with LTE sampling frequencies and decode signals from live LTE base stations. 

We have tested the following hardware: 
 * USRP B210
 * USRP X300
 * bladeRF

Download & Install Instructions
-------------------------------

* Mandatory dependencies: 
  * srsLTE:        https://github.com/srslte/srslte
  * UHD:           https://github.com/EttusResearch/uhd
  * Boost:         ```sudo apt-get install libboost-all-dev```
  * Polarssl.......```sudo apt-get install libpolarssl-dev```

Download and build srsUE: 
```
git clone https://github.com/srsLTE/srsUE.git
cd srsUE
mkdir build
cd build
cmake ../
make 
```

The ue application can be found in build/ue/src

Running srsUE
-------------

 * Copy and rename the provided configuration file ue.conf.example
 * Check and set configuration parameters
 * ```sudo ./ue ue.conf```

Disclaimer
----------

srsUE is provided with NO WARRANTY OF ANY KIND. Users of this software are expected to comply with all applicable local, national and international telecom and radio spectrum regulations.

Support
-------

Mailing list: http://www.softwareradiosystems.com/mailman/listinfo/srslte-users
