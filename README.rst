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

.. image:: ./docs/img/coffeebin-mqtt.png

CoffeeBin wiring: \
`Download PDF [ 196kb ] <docs/img/coffeebin-mqtt.pdf>`_ \
| `Download PNG [ 121kb ] <docs/img/coffeebin-mqtt.png>`_ \
| `Download SVG [622kb ] <docs/img/coffeebin-mqtt.svg>`_
