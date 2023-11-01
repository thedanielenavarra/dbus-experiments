#include <stdio.h>
#include <dbus/dbus.h>

static DBusHandlerResult my_service_handler(DBusConnection *connection, DBusMessage *message, void *user_data) {
    printf("Message received\n");
    if (dbus_message_is_method_call(message, "com.example.MyService", "SayHello")) {
        printf("SayHello called\n");
        DBusMessage *reply;
        const char *response = "Hello, D-Bus!";
        reply = dbus_message_new_method_return(message);
        dbus_message_append_args(reply, DBUS_TYPE_STRING, &response, DBUS_TYPE_INVALID);
        dbus_connection_send(connection, reply, NULL);
        dbus_message_unref(reply);
        return DBUS_HANDLER_RESULT_HANDLED;
    }
    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

int main() {
    DBusConnection *connection;
    DBusError error;

    dbus_error_init(&error);
    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);

    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "D-Bus connection error: %s\n", error.message);
        dbus_error_free(&error);
        return 1;
    }

    dbus_bus_request_name(connection, "com.example.MyService", 0, &error);

    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "Name request error: %s\n", error.message);
        dbus_error_free(&error);
        return 1;
    }

    dbus_connection_add_filter(connection, my_service_handler, NULL, NULL);
    dbus_bus_add_match(connection, "type='method_call',interface='com.example.MyService'", &error);

    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "Match rule error: %s\n", error.message);
        dbus_error_free(&error);
        return 1;
    }

    int ret = dbus_bus_request_name(connection, "com.example.MyService", DBUS_NAME_FLAG_REPLACE_EXISTING , &error);


    printf("Listening for method calls...\n");

    while (dbus_connection_read_write_dispatch(connection, -1)) {
    // This will handle one message and then return
}

    printf("Listening for method calls 2...\n");

    while (1) {
        dbus_connection_read_write(connection, -1);
        dbus_connection_flush(connection);
    }

    return 0;
}
