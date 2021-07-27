#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "GameObject.h"
#include <map>
#include <functional>

class ObjectFactory
{
    public:
        GameObject* CreateObject(std::string type, Properties* props);
        void RegisterType(std::string className, std::function<GameObject*(Properties*props)> type);
        
        static ObjectFactory* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectFactory();
        }

    private:
        ObjectFactory() {}
        static ObjectFactory* s_Instance;
        std::map<std::string, std::function<GameObject*(Properties*props)>> m_TypeRegistry;
};

template<class Type>
class Register
{
    public:
        Register(std::string className)
        {
            ObjectFactory::GetInstance()->RegisterType(className, [](Properties* props)->GameObject* {
                return new Type(props);
            });
        }
};

#endif