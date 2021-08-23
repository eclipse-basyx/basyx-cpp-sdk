#pragma once

namespace basyx {

class serializable_base;

namespace serialization {

    class Serializer {
    public:
        virtual void serialize(const serializable_base&) {};
    };
};

};
