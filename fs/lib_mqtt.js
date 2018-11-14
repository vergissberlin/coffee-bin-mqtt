load('api_config.js');
load('api_mqtt.js');

let mqttUser = Cfg.get('mqtt.user');

/**
 * Send MQTT messages
 * 
 * @param {*} feed MQTT feed
 * @param {*} msg Payload
 * @param {*} qos Quality of service level
 */
function send(feed, msg, qos) {
	let topic = mqttUser + '/feeds/' + feed;
	let msg = JSON.stringify(msg);
	let ok = MQTT.pub(topic, msg, qos || 1);
	if (ok) print('Sent mqtt "' + msg + '" for ' + feed)
	else print('Failed mqtt "' + msg + '" for ' + feed);
	MQTT.setEventHandler(function () { }, null);
  }
