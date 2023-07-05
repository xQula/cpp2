#include <map>
#include <string>
#include <iostream>

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept {
        return "Very Big Data String: " + key;
    }
};

class CacheProxyDB : VeryHeavyDatabase {
public:
    explicit CacheProxyDB (VeryHeavyDatabase* real_object) : real_db_(real_object) {}
    std::string GetData(const std::string& key) noexcept {
        if (cache_.find(key) == cache_.end()) {
            std::cout << "Get from real object\n";
            cache_[key] = real_db_->GetData(key);
        } else {
            std::cout << "Get from cache\n";
        }
        return cache_.at(key);
    }

private:
    std::map<std::string, std::string> cache_;
    VeryHeavyDatabase* real_db_;
};

class TestDB : VeryHeavyDatabase {
public:
    explicit TestDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {}
    std::string GetData(const std::string& key) noexcept {
        return "test_data\n";
    }
private:
    VeryHeavyDatabase* real_db_;
};

class OneShotDB : VeryHeavyDatabase {
private:
    VeryHeavyDatabase * real_db_;
    size_t size_requests;
public:
    explicit OneShotDB(VeryHeavyDatabase * real_object, size_t shots = 1)
        : real_db_(real_object), size_requests(shots){}
        std::string GetData(const std::string& key){
            if(size_requests == 0)
                return "error";
            --size_requests;
            return real_db_->GetData(key);
        }
};

int main() {
    auto real_db = VeryHeavyDatabase();
    OneShotDB three_requests_db(std::addressof(real_db), 3);
    std::cout << three_requests_db.GetData("one") << std::endl <<
        three_requests_db.GetData("two") << std::endl <<
        three_requests_db.GetData("three") << std::endl <<
        three_requests_db.GetData("four") << std::endl <<
        three_requests_db.GetData("five");
    return 0;
}