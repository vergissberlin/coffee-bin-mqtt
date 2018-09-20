// Send MQTT messages
function send(feed, msg, qos) {
	let topic = Cfg.get('mqtt.user') + '/feeds/' + feed;
	let ok = MQTT.pub(topic, JSON.stringify(msg||1), qos||1);
	if(ok) print('sent mqtt for ' + feed)
	else print('failed mqtt for' + feed);
	MQTT.setEventHandler(function(){}, null);
}
