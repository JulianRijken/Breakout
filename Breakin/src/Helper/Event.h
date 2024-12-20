#ifndef EVENT_H
#define EVENT_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <unordered_set>

// Event based on Observer from game programming patterns
// https://gameprogrammingpatterns.com/observer.html

// Originally implemented in Julgen
// https://github.com/JulianRijken/Julgen

namespace bin
{
    class IEventListener;

    class BaseEvent
    {
    public:
        BaseEvent() = default;
        virtual ~BaseEvent() = default;

        BaseEvent(BaseEvent&&) = delete;
        BaseEvent(const BaseEvent&) = delete;
        BaseEvent& operator=(BaseEvent&&) = delete;
        BaseEvent& operator=(const BaseEvent&) = delete;

        virtual void RemoveListener(IEventListener* listener) = 0;
    };

    class IEventListener
    {
        template<typename... EventArgs>
        friend class Event;

    public:
        virtual ~IEventListener()
        {
            for(auto* event : m_BindedEvents)
                event->RemoveListener(this);
        }

        IEventListener(IEventListener&&) = delete;
        IEventListener(const IEventListener&) = delete;
        IEventListener& operator=(IEventListener&&) = delete;
        IEventListener& operator=(const IEventListener&) = delete;

    protected:
        IEventListener() = default;

    private:
        void AddEvent(BaseEvent* event) { m_BindedEvents.insert(event); }

        void RemoveEvent(BaseEvent* event) { m_BindedEvents.erase(event); }

        std::unordered_set<BaseEvent*> m_BindedEvents;
    };

    template<typename... EventArgs>
    class Event final : public BaseEvent
    {
        using FunctionBind = std::pair<void*, std::function<void(EventArgs...)>>;

    public:
        Event() = default;

        ~Event() override
        {
            for(auto* eventListener : m_EventListeners)
                eventListener->RemoveEvent(this);
        }

        Event(Event&&) = delete;
        Event(const Event&) = delete;
        Event& operator=(Event&&) = delete;
        Event& operator=(const Event&) = delete;

        template<typename Function>
        void AddListener(Function function)
        {
            assert(not m_Invoking && "Can't Add Listener While Invoking");
            m_FunctionBinds.emplace_back(nullptr, [function](EventArgs... args) { function(args...); });
        }

        template<typename ObjectType>
            requires std::derived_from<ObjectType, IEventListener>
        void AddListener(ObjectType* object, void (ObjectType::*memberFunction)(EventArgs...))
        {
            assert(not m_Invoking && "Can't Add Listener While Invoking");
            auto* listener = static_cast<IEventListener*>(object);
            listener->AddEvent(this);
            m_EventListeners.insert(listener);

            m_FunctionBinds.emplace_back(
                listener, [object, memberFunction](EventArgs... args) { (object->*memberFunction)(args...); });
        }

        template<typename... Args>
        void Invoke(Args&&... args)
        {
            m_Invoking = true;
            for(const auto& listenerFunction : m_FunctionBinds)
                listenerFunction.second(args...);
            m_Invoking = false;
        }

        void RemoveListener(IEventListener* listener) override
        {
            assert(not m_Invoking && "Can't Remove Listener While Invoking");
            m_EventListeners.erase(listener);

            m_FunctionBinds.erase(std::remove_if(m_FunctionBinds.begin(),
                                                 m_FunctionBinds.end(),
                                                 [listener](const FunctionBind& bind)
                                                 { return bind.first == static_cast<void*>(listener); }),
                                  m_FunctionBinds.end());
        }

    private:
        bool m_Invoking{ false };
        std::vector<FunctionBind> m_FunctionBinds{};
        std::unordered_set<IEventListener*> m_EventListeners{};
    };
}  // namespace bin
#endif // EVENT_H
