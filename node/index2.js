const dbus = require('dbus-native');

const sessionBus = dbus.sessionBus();
const serviceName = 'com.example.MyService';
const objectPath = '/com/example/MyService';
const interfaceName = 'com.example.MyService.Interface';

const ifaceDesc = {
    name: interfaceName,
    methods: {
        Hello: ['', 's', [], ['response']],
    },
    signals: {
        HelloEmitted: ['s', ['message']],
    },
    properties: {}
};

const myService = {
    Hello: function() {
        return 'Hello, D-Bus from Node.js!';
    }
};

sessionBus.exportInterface(myService, objectPath, ifaceDesc);

sessionBus.requestName(serviceName, 0);