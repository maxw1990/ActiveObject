#pragma once
// Nachrichtenklasse
class Message {
public:
    virtual bool execute() = 0;

    virtual ~Message() {}

    // Optional override for messages that use promises
    virtual void fulfillPromise() {}

    // For cleanup and flexibility
    virtual bool hasPromise() const { return false; }
};
