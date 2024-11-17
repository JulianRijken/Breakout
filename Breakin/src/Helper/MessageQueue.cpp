#include "MessageQueue.h"

void bin::MessageQueue::Broadcast(const Message& message) { g_Messages.push(message); }

void bin::MessageQueue::Dispatch()
{
    while(not g_Messages.empty())
    {
        const Message message = g_Messages.front();
        g_Messages.pop();

        auto listenersIterator = g_MessageListeners.equal_range(message.id);
        for(auto it = listenersIterator.first; it != listenersIterator.second; ++it)
            it->second.second(message);
    }
}
