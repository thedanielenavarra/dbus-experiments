#!/usr/bin/env python3
"""
from pydbus import SessionBus
bus = SessionBus()
remote_object = bus.get_object(
    "com.example.MyService", "/com/example/MyService" # Bus name
)

remote_object.SayHello()
#inspect = remote_object.Introspect()
print("Introspection data for the remote object:")
print(inspect)
print(remote_object.SayHello())"""

import dbus

bus = dbus.SessionBus()
service = bus.get_object('com.example.MyService', '/com/example/MyService')
method = service.get_dbus_method('SayHello', 'com.example.MyService')
response = method()
print(response)