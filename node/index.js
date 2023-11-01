const dbus = require('dbus-native');
const service = dbus.sessionBus().getService('org.example.MyService');
const objectPath = '/org/example/MyObject';
const interfaceName = 'org.example.MyInterface';

service.createObject(objectPath, interfaceName, {
  'Hello': async (cb) => {
    cb('Hello, D-Bus from Node.js!');
  },
});

// Listen for incoming messages on D-Bus
dbus.sessionBus().on('message', (message) => {
  console.log('Received message:', message);
});

// Keep the service running
setInterval(() => {
  // Do some work to keep the script running
}, 1000);
