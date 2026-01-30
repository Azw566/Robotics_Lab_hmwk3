/****************************************************************************
 *
 *   Copyright (C) 2013-2022 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/


// auto-generated file

#pragma once

#include <ucdr/microcdr.h>
#include <string.h>
#include <uORB/topics/vtx.h>


static inline constexpr int ucdr_topic_size_vtx()
{
	return 34;
}

static inline bool ucdr_serialize_vtx(const void* data, ucdrBuffer& buf, int64_t time_offset = 0)
{
	const vtx_s& topic = *static_cast<const vtx_s*>(data);
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	const uint64_t timestamp_adjusted = topic.timestamp + time_offset;
	memcpy(buf.iterator, &timestamp_adjusted, sizeof(topic.timestamp));
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.protocol) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.protocol, sizeof(topic.protocol));
	buf.iterator += sizeof(topic.protocol);
	buf.offset += sizeof(topic.protocol);
	static_assert(sizeof(topic.device) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.device, sizeof(topic.device));
	buf.iterator += sizeof(topic.device);
	buf.offset += sizeof(topic.device);
	static_assert(sizeof(topic.mode) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.mode, sizeof(topic.mode));
	buf.iterator += sizeof(topic.mode);
	buf.offset += sizeof(topic.mode);
	static_assert(sizeof(topic.band) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.band, sizeof(topic.band));
	buf.iterator += sizeof(topic.band);
	buf.offset += sizeof(topic.band);
	static_assert(sizeof(topic.channel) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.channel, sizeof(topic.channel));
	buf.iterator += sizeof(topic.channel);
	buf.offset += sizeof(topic.channel);
	buf.iterator += 1; // padding
	buf.offset += 1; // padding
	static_assert(sizeof(topic.frequency) == 2, "size mismatch");
	memcpy(buf.iterator, &topic.frequency, sizeof(topic.frequency));
	buf.iterator += sizeof(topic.frequency);
	buf.offset += sizeof(topic.frequency);
	static_assert(sizeof(topic.band_letter) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.band_letter, sizeof(topic.band_letter));
	buf.iterator += sizeof(topic.band_letter);
	buf.offset += sizeof(topic.band_letter);
	static_assert(sizeof(topic.band_name) == 12, "size mismatch");
	memcpy(buf.iterator, &topic.band_name, sizeof(topic.band_name));
	buf.iterator += sizeof(topic.band_name);
	buf.offset += sizeof(topic.band_name);
	static_assert(sizeof(topic.power_level) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.power_level, sizeof(topic.power_level));
	buf.iterator += sizeof(topic.power_level);
	buf.offset += sizeof(topic.power_level);
	static_assert(sizeof(topic.power_label) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.power_label, sizeof(topic.power_label));
	buf.iterator += sizeof(topic.power_label);
	buf.offset += sizeof(topic.power_label);
	return true;
}

static inline bool ucdr_deserialize_vtx(ucdrBuffer& buf, vtx_s& topic, int64_t time_offset = 0)
{
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	memcpy(&topic.timestamp, buf.iterator, sizeof(topic.timestamp));
	if (topic.timestamp == 0) topic.timestamp = hrt_absolute_time();
	else topic.timestamp = math::min(topic.timestamp - time_offset, hrt_absolute_time());
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.protocol) == 1, "size mismatch");
	memcpy(&topic.protocol, buf.iterator, sizeof(topic.protocol));
	buf.iterator += sizeof(topic.protocol);
	buf.offset += sizeof(topic.protocol);
	static_assert(sizeof(topic.device) == 1, "size mismatch");
	memcpy(&topic.device, buf.iterator, sizeof(topic.device));
	buf.iterator += sizeof(topic.device);
	buf.offset += sizeof(topic.device);
	static_assert(sizeof(topic.mode) == 1, "size mismatch");
	memcpy(&topic.mode, buf.iterator, sizeof(topic.mode));
	buf.iterator += sizeof(topic.mode);
	buf.offset += sizeof(topic.mode);
	static_assert(sizeof(topic.band) == 1, "size mismatch");
	memcpy(&topic.band, buf.iterator, sizeof(topic.band));
	buf.iterator += sizeof(topic.band);
	buf.offset += sizeof(topic.band);
	static_assert(sizeof(topic.channel) == 1, "size mismatch");
	memcpy(&topic.channel, buf.iterator, sizeof(topic.channel));
	buf.iterator += sizeof(topic.channel);
	buf.offset += sizeof(topic.channel);
	buf.iterator += 1; // padding
	buf.offset += 1; // padding
	static_assert(sizeof(topic.frequency) == 2, "size mismatch");
	memcpy(&topic.frequency, buf.iterator, sizeof(topic.frequency));
	buf.iterator += sizeof(topic.frequency);
	buf.offset += sizeof(topic.frequency);
	static_assert(sizeof(topic.band_letter) == 1, "size mismatch");
	memcpy(&topic.band_letter, buf.iterator, sizeof(topic.band_letter));
	buf.iterator += sizeof(topic.band_letter);
	buf.offset += sizeof(topic.band_letter);
	static_assert(sizeof(topic.band_name) == 12, "size mismatch");
	memcpy(&topic.band_name, buf.iterator, sizeof(topic.band_name));
	buf.iterator += sizeof(topic.band_name);
	buf.offset += sizeof(topic.band_name);
	static_assert(sizeof(topic.power_level) == 1, "size mismatch");
	memcpy(&topic.power_level, buf.iterator, sizeof(topic.power_level));
	buf.iterator += sizeof(topic.power_level);
	buf.offset += sizeof(topic.power_level);
	static_assert(sizeof(topic.power_label) == 4, "size mismatch");
	memcpy(&topic.power_label, buf.iterator, sizeof(topic.power_label));
	buf.iterator += sizeof(topic.power_label);
	buf.offset += sizeof(topic.power_label);
	return true;
}
