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
#include <uORB/topics/device_information.h>


static inline constexpr int ucdr_topic_size_device_information()
{
	return 161;
}

static inline bool ucdr_serialize_device_information(const void* data, ucdrBuffer& buf, int64_t time_offset = 0)
{
	const device_information_s& topic = *static_cast<const device_information_s*>(data);
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	const uint64_t timestamp_adjusted = topic.timestamp + time_offset;
	memcpy(buf.iterator, &timestamp_adjusted, sizeof(topic.timestamp));
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.device_type) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.device_type, sizeof(topic.device_type));
	buf.iterator += sizeof(topic.device_type);
	buf.offset += sizeof(topic.device_type);
	static_assert(sizeof(topic.vendor_name) == 32, "size mismatch");
	memcpy(buf.iterator, &topic.vendor_name, sizeof(topic.vendor_name));
	buf.iterator += sizeof(topic.vendor_name);
	buf.offset += sizeof(topic.vendor_name);
	static_assert(sizeof(topic.model_name) == 32, "size mismatch");
	memcpy(buf.iterator, &topic.model_name, sizeof(topic.model_name));
	buf.iterator += sizeof(topic.model_name);
	buf.offset += sizeof(topic.model_name);
	buf.iterator += 3; // padding
	buf.offset += 3; // padding
	static_assert(sizeof(topic.device_id) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.device_id, sizeof(topic.device_id));
	buf.iterator += sizeof(topic.device_id);
	buf.offset += sizeof(topic.device_id);
	static_assert(sizeof(topic.firmware_version) == 24, "size mismatch");
	memcpy(buf.iterator, &topic.firmware_version, sizeof(topic.firmware_version));
	buf.iterator += sizeof(topic.firmware_version);
	buf.offset += sizeof(topic.firmware_version);
	static_assert(sizeof(topic.hardware_version) == 24, "size mismatch");
	memcpy(buf.iterator, &topic.hardware_version, sizeof(topic.hardware_version));
	buf.iterator += sizeof(topic.hardware_version);
	buf.offset += sizeof(topic.hardware_version);
	static_assert(sizeof(topic.serial_number) == 33, "size mismatch");
	memcpy(buf.iterator, &topic.serial_number, sizeof(topic.serial_number));
	buf.iterator += sizeof(topic.serial_number);
	buf.offset += sizeof(topic.serial_number);
	return true;
}

static inline bool ucdr_deserialize_device_information(ucdrBuffer& buf, device_information_s& topic, int64_t time_offset = 0)
{
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	memcpy(&topic.timestamp, buf.iterator, sizeof(topic.timestamp));
	if (topic.timestamp == 0) topic.timestamp = hrt_absolute_time();
	else topic.timestamp = math::min(topic.timestamp - time_offset, hrt_absolute_time());
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.device_type) == 1, "size mismatch");
	memcpy(&topic.device_type, buf.iterator, sizeof(topic.device_type));
	buf.iterator += sizeof(topic.device_type);
	buf.offset += sizeof(topic.device_type);
	static_assert(sizeof(topic.vendor_name) == 32, "size mismatch");
	memcpy(&topic.vendor_name, buf.iterator, sizeof(topic.vendor_name));
	buf.iterator += sizeof(topic.vendor_name);
	buf.offset += sizeof(topic.vendor_name);
	static_assert(sizeof(topic.model_name) == 32, "size mismatch");
	memcpy(&topic.model_name, buf.iterator, sizeof(topic.model_name));
	buf.iterator += sizeof(topic.model_name);
	buf.offset += sizeof(topic.model_name);
	buf.iterator += 3; // padding
	buf.offset += 3; // padding
	static_assert(sizeof(topic.device_id) == 4, "size mismatch");
	memcpy(&topic.device_id, buf.iterator, sizeof(topic.device_id));
	buf.iterator += sizeof(topic.device_id);
	buf.offset += sizeof(topic.device_id);
	static_assert(sizeof(topic.firmware_version) == 24, "size mismatch");
	memcpy(&topic.firmware_version, buf.iterator, sizeof(topic.firmware_version));
	buf.iterator += sizeof(topic.firmware_version);
	buf.offset += sizeof(topic.firmware_version);
	static_assert(sizeof(topic.hardware_version) == 24, "size mismatch");
	memcpy(&topic.hardware_version, buf.iterator, sizeof(topic.hardware_version));
	buf.iterator += sizeof(topic.hardware_version);
	buf.offset += sizeof(topic.hardware_version);
	static_assert(sizeof(topic.serial_number) == 33, "size mismatch");
	memcpy(&topic.serial_number, buf.iterator, sizeof(topic.serial_number));
	buf.iterator += sizeof(topic.serial_number);
	buf.offset += sizeof(topic.serial_number);
	return true;
}
