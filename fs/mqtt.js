
/**
 * Send MQTT messages
 * 
 * @param {*} feed MQTT feed
 * @param {*} msg Payload
 * @param {*} qos Quality of service level
 */
function send(feed, msg, qos) {
	let topic = Cfg.get('mqtt.user') + '/feeds/' + feed;
	let ok = MQTT.pub(topic, JSON.stringify(msg || 1), qos || 1);
	if (ok) print('sent mqtt for ' + feed)
	else print('Failed mqtt for ' + feed);
	MQTT.setEventHandler(function () { }, null);
  }
  