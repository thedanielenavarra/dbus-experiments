#!/usr/bin/env python3

from pydbus import SessionBus

class MyDBusService:
    def __init__(self):
        self._bus = SessionBus()
        introspection_data = open("service.xml", "r").read()
        self._bus.publish("com.example.MyService", introspection_data, self)

    def say_hello(self):
        return "Hello, D-Bus!"

if __name__ == "__main__":
    service = MyDBusService()
    try:
        from gi.repository import GLib
        GLib.MainLoop().run()
    except ImportError:
        import time
        while True:
            time.sleep(1)
