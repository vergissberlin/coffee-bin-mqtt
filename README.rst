===============
coffee-bin-mqtt
===============

.. image:: https://readthedocs.org/projects/coffee-bin-mqtt/badge/?version=latest
    :target: https://coffee-bin-mqtt.readthedocs.io/en/latest/?badge=latest
    :alt: Documentation Status

MQTT sensor project for `CoffeeBin <https://github.com/vergissberlin/coffee-bin>`_. 

Features
========

- It uses deep sleep ,ode to save energy.
- It messures the volatage on bootup an send the result as MQTT message to the broker.
- It has an external status LED
- It has an switch to broadcast an MQTT message, that the coffe machine is in maintenance mode.


Wiring
======

|CoffeeBin wiring| \
`Download PDF [ 196kb ] <https://github.com/vergissberlin/coffee-bin-mqtt/raw/master/docs/img/coffeebin-mqtt.pdf>`_ \
| `Download PNG [ 121kb ] <https://github.com/vergissberlin/coffee-bin-mqtt/raw/master/docs/img/coffeebin-mqtt.png>`_ \
| `Download SVG [622kb ] <https://github.com/vergissberlin/coffee-bin-mqtt/raw/master/docs/img/coffeebin-mqtt.svg>`_

.. |CoffeeBin wiring| image:: docs/img/coffeebin-mqtt.png
  :width: 800
  :alt: How to wire everthing together


Build
=====

You need to install Docker to build it locally.
.. code:: bash

    git clone https://github.com/vergissberlin/coffee-bin-mqtt
    cd coffee-bin-mqtt
    mos build --platform ESP8266 --local --verbose
    mos flash --port /dev/cu.SLAB_USBtoUART --esp-erase-chip --esp-baud-rate 115200 --esp-flash-params "dio,4m,40m"
    mos console --port /dev/cu.SLAB_USBtoUART

