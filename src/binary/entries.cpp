#include <binary/entries.hpp>
#include <binary/binary.hpp>

using namespace std;

map<size_t, vector<size_t>> Entries::get_term_infos(uint32_t entry_offset) {
    BinaryReader reader(data_);
    map<size_t, vector<size_t>> term_infos;
    reader.move(entry_offset);
    uint32_t doc_count = 0;
    reader.read(&doc_count, sizeof(doc_count));
    for (size_t i = 0; i < doc_count; ++i) {
        uint32_t doc_offset = 0;
        reader.read(&doc_offset, sizeof(doc_offset));
        uint32_t pos_count = 0;
        reader.read(&pos_count, sizeof(pos_count));
        vector<size_t> positions;
        for (size_t j = 0; j < pos_count; ++j) {
            uint32_t pos = 0;
            reader.read(&pos, sizeof(pos));
            positions.push_back(pos);
        }
        term_infos[doc_offset] = positions;
    }
    return term_infos;
}