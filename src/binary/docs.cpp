#include <binary/docs.hpp>
#include <binary/binary.hpp>

using namespace std;

string Documents::get_document_by_id(size_t identifier) const {
    BinaryReader reader(data_);
    reader.move(identifier);
    uint8_t length = 0;
    reader.read(&length, sizeof(length));
    string document(length - 1, ' ');
    reader.read(document.data(), document.length());
    return document;
}

size_t Documents::get_document_count() const {
    BinaryReader reader(data_);
    uint32_t titles_count = 0;
    reader.read(&titles_count, sizeof(titles_count));
    return titles_count;
}