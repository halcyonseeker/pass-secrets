
/*
 * This file was automatically generated by sdbus-c++-xml2cpp; DO NOT EDIT!
 */

#ifndef __sdbuscpp__secretsadapter_h__adaptor__H__
#define __sdbuscpp__secretsadapter_h__adaptor__H__

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>

namespace org {
namespace freedesktop {
namespace Secret {

class Service_adaptor
{
public:
    static constexpr const char* INTERFACE_NAME = "org.freedesktop.Secret.Service";

protected:
    Service_adaptor(sdbus::IObject& object)
        : object_(object)
    {
        object_.registerMethod("OpenSession").onInterface(INTERFACE_NAME).withInputParamNames("algorithm", "input").withOutputParamNames("output", "result").implementedAs([this](const std::string& algorithm, const sdbus::Variant& input){ return this->OpenSession(algorithm, input); });
        object_.registerMethod("CreateCollection").onInterface(INTERFACE_NAME).withInputParamNames("properties", "alias").withOutputParamNames("collection", "prompt").implementedAs([this](const std::map<std::string, sdbus::Variant>& properties, const std::string& alias){ return this->CreateCollection(properties, alias); });
        object_.registerMethod("SearchItems").onInterface(INTERFACE_NAME).withInputParamNames("attributes").withOutputParamNames("unlocked", "locked").implementedAs([this](const std::map<std::string, std::string>& attributes){ return this->SearchItems(attributes); });
        object_.registerMethod("Unlock").onInterface(INTERFACE_NAME).withInputParamNames("objects").withOutputParamNames("unlocked", "prompt").implementedAs([this](const std::vector<sdbus::ObjectPath>& objects){ return this->Unlock(objects); });
        object_.registerMethod("Lock").onInterface(INTERFACE_NAME).withInputParamNames("objects").withOutputParamNames("locked", "Prompt").implementedAs([this](const std::vector<sdbus::ObjectPath>& objects){ return this->Lock(objects); });
        object_.registerMethod("LockService").onInterface(INTERFACE_NAME).implementedAs([this](){ return this->LockService(); });
        object_.registerMethod("ChangeLock").onInterface(INTERFACE_NAME).withInputParamNames("collection").withOutputParamNames("prompt").implementedAs([this](const sdbus::ObjectPath& collection){ return this->ChangeLock(collection); });
        object_.registerMethod("GetSecrets").onInterface(INTERFACE_NAME).withInputParamNames("items", "session").withOutputParamNames("secrets").implementedAs([this](const std::vector<sdbus::ObjectPath>& items, const sdbus::ObjectPath& session){ return this->GetSecrets(items, session); });
        object_.registerMethod("ReadAlias").onInterface(INTERFACE_NAME).withInputParamNames("name").withOutputParamNames("collection").implementedAs([this](const std::string& name){ return this->ReadAlias(name); });
        object_.registerMethod("SetAlias").onInterface(INTERFACE_NAME).withInputParamNames("name", "collection").implementedAs([this](const std::string& name, const sdbus::ObjectPath& collection){ return this->SetAlias(name, collection); });
        object_.registerSignal("CollectionCreated").onInterface(INTERFACE_NAME).withParameters<sdbus::ObjectPath>("collection");
        object_.registerSignal("CollectionDeleted").onInterface(INTERFACE_NAME).withParameters<sdbus::ObjectPath>("collection");
        object_.registerSignal("CollectionChanged").onInterface(INTERFACE_NAME).withParameters<sdbus::ObjectPath>("collection");
        object_.registerProperty("Collections").onInterface(INTERFACE_NAME).withGetter([this](){ return this->Collections(); });
    }

    ~Service_adaptor() = default;

public:
    void emitCollectionCreated(const sdbus::ObjectPath& collection)
    {
        object_.emitSignal("CollectionCreated").onInterface(INTERFACE_NAME).withArguments(collection);
    }

    void emitCollectionDeleted(const sdbus::ObjectPath& collection)
    {
        object_.emitSignal("CollectionDeleted").onInterface(INTERFACE_NAME).withArguments(collection);
    }

    void emitCollectionChanged(const sdbus::ObjectPath& collection)
    {
        object_.emitSignal("CollectionChanged").onInterface(INTERFACE_NAME).withArguments(collection);
    }

private:
    virtual std::tuple<sdbus::Variant, sdbus::ObjectPath> OpenSession(const std::string& algorithm, const sdbus::Variant& input) = 0;
    virtual std::tuple<sdbus::ObjectPath, sdbus::ObjectPath> CreateCollection(const std::map<std::string, sdbus::Variant>& properties, const std::string& alias) = 0;
    virtual std::tuple<std::vector<sdbus::ObjectPath>, std::vector<sdbus::ObjectPath>> SearchItems(const std::map<std::string, std::string>& attributes) = 0;
    virtual std::tuple<std::vector<sdbus::ObjectPath>, sdbus::ObjectPath> Unlock(const std::vector<sdbus::ObjectPath>& objects) = 0;
    virtual std::tuple<std::vector<sdbus::ObjectPath>, sdbus::ObjectPath> Lock(const std::vector<sdbus::ObjectPath>& objects) = 0;
    virtual void LockService() = 0;
    virtual sdbus::ObjectPath ChangeLock(const sdbus::ObjectPath& collection) = 0;
    virtual std::map<sdbus::ObjectPath, sdbus::Struct<sdbus::ObjectPath, std::vector<uint8_t>, std::vector<uint8_t>, std::string>> GetSecrets(const std::vector<sdbus::ObjectPath>& items, const sdbus::ObjectPath& session) = 0;
    virtual sdbus::ObjectPath ReadAlias(const std::string& name) = 0;
    virtual void SetAlias(const std::string& name, const sdbus::ObjectPath& collection) = 0;

private:
    virtual std::vector<sdbus::ObjectPath> Collections() = 0;

private:
    sdbus::IObject& object_;
};

}}} // namespaces

#endif
