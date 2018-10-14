Configuration
=============



.. tip::

    You can enable RPC to configure and controll your divice over WiFi.



config9.json
------------

.. code-block:: json

    {
    "device": {
        "id": "esp8266_XXXXX"
    },
    "mqtt": {
        "enable": false,
        "server": "io.adafruit.com:1883",
        "user": "USERNAME",
        "pass": "PASSWORD"
    },
    "aws": {
        "thing_name": "esp8266_XXXXX"
    },
    "wifi": {
        "ap": {
            "enable": false
        },
        "sta": {
            "enable": true,
            "ssid": "WIFI_SSID",
            "pass": "WIFI_PASSWORD"
            }
        }
    }


