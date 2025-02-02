#ifndef LOCATOR_H
#define LOCATOR_H

#include <memory>
#include <typeindex>
#include <unordered_map>

// Generic Service based on Service Locator from game programming patterns
// https://gameprogrammingpatterns.com/service-locator.html

// Originally implemented in Julgen
// https://github.com/JulianRijken/Julgen

namespace bin
{
    class Service
    {
    public:
        explicit Service() = default;
        virtual ~Service() = default;

        Service(const Service&) = delete;
        Service(Service&&) noexcept = delete;
        Service& operator=(const Service&) = delete;
        Service& operator=(Service&&) noexcept = delete;
    };

    class Locator final
    {
    public:
        // When using an existing service
        template<typename ServiceType, typename ImplementationType>
        static void Provide(std::unique_ptr<ImplementationType> implementationUPtr)
        {
            g_Services.emplace(typeid(ServiceType), std::move(implementationUPtr));
        }

        // When creating a new service
        template<typename ServiceType, typename ImplementationType, typename... Args>
        static void Provide(Args&&... args)
        {
            g_Services.emplace(typeid(ServiceType), std::make_unique<ImplementationType>(std::forward<Args>(args)...));
        }

        // When creating a new service with no specific implementation
        template<typename ServiceType, typename... Args>
        static void Provide(Args&&... args)
        {
            Provide<ServiceType, ServiceType>(std::forward<Args>(args)...);
        }

        // TODO: Implement null service or error handling
        template<typename ServiceType>
        [[nodiscard]] static ServiceType& Get()
        {
            const auto service{ g_Services.find(typeid(ServiceType)) };
            return *dynamic_cast<ServiceType*>(service->second.get());
        }

        template<typename ServiceType, typename ImplementationType>
        static std::unique_ptr<ImplementationType> Release()
        {
            const auto node{ g_Services.extract(typeid(ServiceType)) };

            auto* releasedPtr = dynamic_cast<ImplementationType*>(node.mapped().release());

            return std::unique_ptr<ImplementationType>(releasedPtr);
        }

        template<typename ServiceType>
        static std::unique_ptr<ServiceType> Release()
        {
            return Release<ServiceType, ServiceType>();
        }

    private:
        static inline std::unordered_map<std::type_index, std::unique_ptr<Service>> g_Services{};
    };

}  // namespace bin
#endif // LOCATOR_H
