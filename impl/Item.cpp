//
// Created by nullobsi on 2021/03/22.
//

#include "Item.h"

#include <utility>
#include <cstring>
#include "Collection.h"

bool
Item::Locked() {
	return !backend->isUnlocked();
}

std::map<std::string, std::string>
Item::Attributes() {
	return backend->getAttrib();
}

void
Item::Attributes(const std::map<std::string, std::string> &value) {
	backend->setAttrib(value);
	backend->updateMetadata();
	parent.lock()->ItemChanged(getPath());
}

std::string
Item::Label() {
	return backend->getLabel();
}

void
Item::Label(const std::string &value) {
	backend->setLabel(value);
	backend->updateMetadata();
	parent.lock()->ItemChanged(getPath());
}

std::string
Item::Type() {
	return backend->getType();
}

void
Item::Type(const std::string &value) {
	backend->setType(value);
	backend->updateMetadata();
	parent.lock()->ItemChanged(getPath());
}

uint64_t
Item::Created() {
	return backend->getCreated();
}

uint64_t
Item::Modified() {
	return 0;
}

sdbus::ObjectPath
Item::Delete() {
	backend->Delete();
	parent.lock()->DiscardItem(this->backend->getId());
	return sdbus::ObjectPath("/");
}

Item::Item(std::shared_ptr<PassItem> backend_,
           sdbus::IConnection &conn,
           std::string path,
           std::weak_ptr<Collection> parent_) : backend(std::move(backend_)),
                                                sdbus::AdaptorInterfaces<org::freedesktop::Secret::Item_adaptor>(conn,
                                                                                                                 std::move(
		                                                                                                                 path)),
                                                parent(std::move(parent_)) {
	registerAdaptor();
}

Item::~Item() {
	unregisterAdaptor();
}

sdbus::Struct<sdbus::ObjectPath, std::vector<uint8_t>, std::vector<uint8_t>, std::string>
Item::GetSecret(const sdbus::ObjectPath &session) {
	if (!backend->isUnlocked()) {
		throw sdbus::Error("org.freedesktop.Secret.Error.IsLocked",
		                   "The object must be unlocked before this action can be carried out.");
	}
	auto cArr = backend->getSecret();
	std::vector<uint8_t> secret(cArr, cArr + backend->getSecretLength());

	// TODO: how to check item type?
	return sdbus::Struct<sdbus::ObjectPath, std::vector<uint8_t>, std::vector<uint8_t>, std::string>(
			std::tuple<sdbus::ObjectPath, std::vector<uint8_t>, std::vector<uint8_t>, std::string>(session,
			                                                                                       std::vector<uint8_t>(),
			                                                                                       secret,
			                                                                                       "text/plain; charset=utf8"));
}

sdbus::ObjectPath
Item::getPath() {
	return sdbus::ObjectPath(getObject().getObjectPath());
}

void
Item::SetSecret(const sdbus::Struct<sdbus::ObjectPath, std::vector<uint8_t>, std::vector<uint8_t>, std::string> &secret) {
	auto data = secret.get<2>();
	auto nData = (uint8_t *)malloc(sizeof(uint8_t) * data.size());
	memcpy(nData, data.data(), sizeof(uint8_t) * data.size());
	backend->setSecret(nData, data.size());

	parent.lock()->ItemChanged(getPath());
}

std::shared_ptr<PassItem>
Item::getBackend() {
	return backend;
}
