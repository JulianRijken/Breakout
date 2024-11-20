#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <any>
#include <functional>
#include <queue>
#include <utility>

namespace bin
{
    struct Message final
    {
        int id;
        std::vector<std::any> args;
    };

    class MessageQueue final
    {
        using Listener = std::pair<void*, std::function<void(const Message&)>>;

    public:
        static void Broadcast(const Message& message);

        template<typename MessageName>
        static void Broadcast(MessageName messageType, std::vector<std::any>&& args = {})
        {
            g_Messages.push({ static_cast<int>(messageType), std::move(args) });
        }

        template<typename ObjectType, typename MessageName>
        static void AddListener(MessageName eventType, ObjectType* object,
                                void (ObjectType::*memberFunction)(const Message&))
        {
            g_MessageListeners.insert({
                static_cast<int>(eventType),
                {object, [=](const Message& message) { (object->*memberFunction)(message); }}
            });
        }

        template<typename ObjectType>
        static void RemoveListenerInstance(ObjectType* object)
        {
            std::erase_if(g_MessageListeners, [object](const auto& other) { return other.second.first == object; });
        }

        static void Dispatch();

        static inline std::unordered_multimap<int, Listener> g_MessageListeners{};
        static inline std::queue<Message> g_Messages{};
    };

}  // namespace bin
#endif // MESSAGEQUEUE_H
