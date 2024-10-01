#include <iostream>
#include <string>
#include <unordered_map>

class VeryHeavyDatabase {
public:
    virtual std::string GetData(const std::string& key) {
        if (key == "key") {
            return "value";
        }
        return "unknown key";
    }

    virtual ~VeryHeavyDatabase() = default;
};

class OneShotDB : public VeryHeavyDatabase {
private:
    VeryHeavyDatabase* real_object;
    size_t shots;
    size_t current_shots;

public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1)
        : real_object(real_object), shots(shots), current_shots(0) {}

    std::string GetData(const std::string& key) override {
        if (current_shots < shots) {
            ++current_shots;
            return real_object->GetData(key);
        }
        else {
            return "error";
        }
    }
};

int main() {
    VeryHeavyDatabase real_db;
    OneShotDB limit_db(&real_db, 2);

    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;

    return 0;
}
