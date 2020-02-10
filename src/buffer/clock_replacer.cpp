//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// clock_replacer.cpp
//
// Identification: src/buffer/clock_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/clock_replacer.h"

namespace bustub {

ClockReplacer::ClockReplacer(size_t num_pages)
    : frames{}, clock_hand{frames.begin()} {

}

ClockReplacer::~ClockReplacer() = default;

// 根据size来判断clock_hand最多可以走多远, 如果走完全程都没有发现可以
// victim的, 就return false;
bool ClockReplacer::Victim(frame_id_t *frame_id) { 
    for (size_t i = 0; i < frames.size(); i++) {
        frame_id_t f_id {clock_hand->first};
        bool& ref_flag {*clock_hand.second};
        if (ref_flag) {
            ref_flag = false;
            clock_hand++;
        } else {
            frame_id_t tmp{f_id};
            frame_id = &tmp;
            clock_hand++;
            return true;
        }

        // clock_hand循环
        if (clock_hand == frames.end()) {
            clock_hand = frames.begin();
        }
    }
    return false; 
}

void ClockReplacer::Pin(frame_id_t frame_id) {
    frames.erase(frame_id);
}

void ClockReplacer::Unpin(frame_id_t frame_id) {
    frames.insert({frame_id, false});
}

size_t ClockReplacer::Size() { return frames.size(); }
}  // namespace bustub
