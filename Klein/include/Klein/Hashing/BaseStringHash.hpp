#pragma once

#include <cstddef>
#include <memory>
#include <utility>

namespace Klein::Hashing {
	template <typename TString, typename THash>
	class BaseStringHash {
	public:

		constexpr BaseStringHash() : hash(THash()(TString())) {
			// ...
		}

		constexpr BaseStringHash(const BaseStringHash<TString, THash>& stringHash) : string(stringHash.string), hash(stringHash.hash) {
			// ...
		}

		constexpr BaseStringHash(BaseStringHash<TString, THash>&& stringHash) noexcept : string(std::move(stringHash.string)), hash(std::move(stringHash.hash)) {
			// ...
		}

		constexpr BaseStringHash(const TString& string) : string(std::make_shared<TString>(string)), hash(THash()(string)) {
			// ...
		}

		constexpr BaseStringHash(TString&& string) : string(std::make_shared<TString>(string)), hash(THash()(*(this->string))) {
			// ...
		}

		const TString& GetString() const noexcept {
			return *string;
		}

		constexpr TString& GetString(TString& result) const {
			return result = *string;
		}

		constexpr std::size_t GetHash() const noexcept {
			return hash;
		}

		constexpr BaseStringHash<TString, THash>& operator =(const BaseStringHash<TString, THash>& stringHash) {
			string = stringHash.string;
			hash = stringHash.hash;
			return *this;
		}
		
		constexpr BaseStringHash<TString, THash>& operator =(BaseStringHash<TString, THash>&& stringHash) noexcept {
			string = std::move(stringHash.string);
			hash = std::move(stringHash.hash);
			return *this;
		}
		
		constexpr BaseStringHash<TString, THash>& operator =(const TString& string) {
			this->string = make_shared<TString>(string);
			hash = THash()(string);
			return *this;
		}
		
		constexpr BaseStringHash<TString, THash>& operator =(TString&& string) noexcept {
			this->string = std::make_shared<TString>(string);
			hash = THash()(*(this->string));
			return *this;
		}

		constexpr bool operator ==(const BaseStringHash<TString, THash>& stringHash) const noexcept {
			return hash == stringHash.GetHash();
		}

	private:

		std::shared_ptr<TString> string;
		std::size_t hash;

		constexpr BaseStringHash(std::shared_ptr<TString>&& string, std::size_t hash) noexcept : string(string), hash(hash) {
			// ...
		}
	};
}
