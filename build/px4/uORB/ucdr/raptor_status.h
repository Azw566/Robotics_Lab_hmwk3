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
#include <uORB/topics/raptor_status.h>


static inline constexpr int ucdr_topic_size_raptor_status()
{
	return 88;
}

static inline bool ucdr_serialize_raptor_status(const void* data, ucdrBuffer& buf, int64_t time_offset = 0)
{
	const raptor_status_s& topic = *static_cast<const raptor_status_s*>(data);
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	const uint64_t timestamp_adjusted = topic.timestamp + time_offset;
	memcpy(buf.iterator, &timestamp_adjusted, sizeof(topic.timestamp));
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.timestamp_sample) == 8, "size mismatch");
	const uint64_t timestamp_sample_adjusted = topic.timestamp_sample + time_offset;
	memcpy(buf.iterator, &timestamp_sample_adjusted, sizeof(topic.timestamp_sample));
	buf.iterator += sizeof(topic.timestamp_sample);
	buf.offset += sizeof(topic.timestamp_sample);
	static_assert(sizeof(topic.subscription_update_angular_velocity) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.subscription_update_angular_velocity, sizeof(topic.subscription_update_angular_velocity));
	buf.iterator += sizeof(topic.subscription_update_angular_velocity);
	buf.offset += sizeof(topic.subscription_update_angular_velocity);
	static_assert(sizeof(topic.subscription_update_local_position) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.subscription_update_local_position, sizeof(topic.subscription_update_local_position));
	buf.iterator += sizeof(topic.subscription_update_local_position);
	buf.offset += sizeof(topic.subscription_update_local_position);
	static_assert(sizeof(topic.subscription_update_attitude) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.subscription_update_attitude, sizeof(topic.subscription_update_attitude));
	buf.iterator += sizeof(topic.subscription_update_attitude);
	buf.offset += sizeof(topic.subscription_update_attitude);
	static_assert(sizeof(topic.subscription_update_trajectory_setpoint) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.subscription_update_trajectory_setpoint, sizeof(topic.subscription_update_trajectory_setpoint));
	buf.iterator += sizeof(topic.subscription_update_trajectory_setpoint);
	buf.offset += sizeof(topic.subscription_update_trajectory_setpoint);
	static_assert(sizeof(topic.subscription_update_vehicle_status) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.subscription_update_vehicle_status, sizeof(topic.subscription_update_vehicle_status));
	buf.iterator += sizeof(topic.subscription_update_vehicle_status);
	buf.offset += sizeof(topic.subscription_update_vehicle_status);
	static_assert(sizeof(topic.exit_reason) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.exit_reason, sizeof(topic.exit_reason));
	buf.iterator += sizeof(topic.exit_reason);
	buf.offset += sizeof(topic.exit_reason);
	buf.iterator += 2; // padding
	buf.offset += 2; // padding
	static_assert(sizeof(topic.timestamp_last_vehicle_angular_velocity) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.timestamp_last_vehicle_angular_velocity, sizeof(topic.timestamp_last_vehicle_angular_velocity));
	buf.iterator += sizeof(topic.timestamp_last_vehicle_angular_velocity);
	buf.offset += sizeof(topic.timestamp_last_vehicle_angular_velocity);
	static_assert(sizeof(topic.timestamp_last_vehicle_local_position) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.timestamp_last_vehicle_local_position, sizeof(topic.timestamp_last_vehicle_local_position));
	buf.iterator += sizeof(topic.timestamp_last_vehicle_local_position);
	buf.offset += sizeof(topic.timestamp_last_vehicle_local_position);
	static_assert(sizeof(topic.timestamp_last_vehicle_attitude) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.timestamp_last_vehicle_attitude, sizeof(topic.timestamp_last_vehicle_attitude));
	buf.iterator += sizeof(topic.timestamp_last_vehicle_attitude);
	buf.offset += sizeof(topic.timestamp_last_vehicle_attitude);
	static_assert(sizeof(topic.timestamp_last_trajectory_setpoint) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.timestamp_last_trajectory_setpoint, sizeof(topic.timestamp_last_trajectory_setpoint));
	buf.iterator += sizeof(topic.timestamp_last_trajectory_setpoint);
	buf.offset += sizeof(topic.timestamp_last_trajectory_setpoint);
	static_assert(sizeof(topic.vehicle_angular_velocity_stale) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.vehicle_angular_velocity_stale, sizeof(topic.vehicle_angular_velocity_stale));
	buf.iterator += sizeof(topic.vehicle_angular_velocity_stale);
	buf.offset += sizeof(topic.vehicle_angular_velocity_stale);
	static_assert(sizeof(topic.vehicle_local_position_stale) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.vehicle_local_position_stale, sizeof(topic.vehicle_local_position_stale));
	buf.iterator += sizeof(topic.vehicle_local_position_stale);
	buf.offset += sizeof(topic.vehicle_local_position_stale);
	static_assert(sizeof(topic.vehicle_attitude_stale) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.vehicle_attitude_stale, sizeof(topic.vehicle_attitude_stale));
	buf.iterator += sizeof(topic.vehicle_attitude_stale);
	buf.offset += sizeof(topic.vehicle_attitude_stale);
	static_assert(sizeof(topic.trajectory_setpoint_stale) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.trajectory_setpoint_stale, sizeof(topic.trajectory_setpoint_stale));
	buf.iterator += sizeof(topic.trajectory_setpoint_stale);
	buf.offset += sizeof(topic.trajectory_setpoint_stale);
	static_assert(sizeof(topic.active) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.active, sizeof(topic.active));
	buf.iterator += sizeof(topic.active);
	buf.offset += sizeof(topic.active);
	static_assert(sizeof(topic.substep) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.substep, sizeof(topic.substep));
	buf.iterator += sizeof(topic.substep);
	buf.offset += sizeof(topic.substep);
	buf.iterator += 2; // padding
	buf.offset += 2; // padding
	static_assert(sizeof(topic.control_interval) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.control_interval, sizeof(topic.control_interval));
	buf.iterator += sizeof(topic.control_interval);
	buf.offset += sizeof(topic.control_interval);
	static_assert(sizeof(topic.trajectory_setpoint_dt_mean) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.trajectory_setpoint_dt_mean, sizeof(topic.trajectory_setpoint_dt_mean));
	buf.iterator += sizeof(topic.trajectory_setpoint_dt_mean);
	buf.offset += sizeof(topic.trajectory_setpoint_dt_mean);
	static_assert(sizeof(topic.trajectory_setpoint_dt_max) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.trajectory_setpoint_dt_max, sizeof(topic.trajectory_setpoint_dt_max));
	buf.iterator += sizeof(topic.trajectory_setpoint_dt_max);
	buf.offset += sizeof(topic.trajectory_setpoint_dt_max);
	static_assert(sizeof(topic.trajectory_setpoint_dt_max_since_activation) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.trajectory_setpoint_dt_max_since_activation, sizeof(topic.trajectory_setpoint_dt_max_since_activation));
	buf.iterator += sizeof(topic.trajectory_setpoint_dt_max_since_activation);
	buf.offset += sizeof(topic.trajectory_setpoint_dt_max_since_activation);
	static_assert(sizeof(topic.internal_reference_position) == 12, "size mismatch");
	memcpy(buf.iterator, &topic.internal_reference_position, sizeof(topic.internal_reference_position));
	buf.iterator += sizeof(topic.internal_reference_position);
	buf.offset += sizeof(topic.internal_reference_position);
	static_assert(sizeof(topic.internal_reference_linear_velocity) == 12, "size mismatch");
	memcpy(buf.iterator, &topic.internal_reference_linear_velocity, sizeof(topic.internal_reference_linear_velocity));
	buf.iterator += sizeof(topic.internal_reference_linear_velocity);
	buf.offset += sizeof(topic.internal_reference_linear_velocity);
	return true;
}

static inline bool ucdr_deserialize_raptor_status(ucdrBuffer& buf, raptor_status_s& topic, int64_t time_offset = 0)
{
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	memcpy(&topic.timestamp, buf.iterator, sizeof(topic.timestamp));
	if (topic.timestamp == 0) topic.timestamp = hrt_absolute_time();
	else topic.timestamp = math::min(topic.timestamp - time_offset, hrt_absolute_time());
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.timestamp_sample) == 8, "size mismatch");
	memcpy(&topic.timestamp_sample, buf.iterator, sizeof(topic.timestamp_sample));
	if (topic.timestamp_sample == 0) topic.timestamp_sample = hrt_absolute_time();
	else topic.timestamp_sample = math::min(topic.timestamp_sample - time_offset, hrt_absolute_time());
	buf.iterator += sizeof(topic.timestamp_sample);
	buf.offset += sizeof(topic.timestamp_sample);
	static_assert(sizeof(topic.subscription_update_angular_velocity) == 1, "size mismatch");
	memcpy(&topic.subscription_update_angular_velocity, buf.iterator, sizeof(topic.subscription_update_angular_velocity));
	buf.iterator += sizeof(topic.subscription_update_angular_velocity);
	buf.offset += sizeof(topic.subscription_update_angular_velocity);
	static_assert(sizeof(topic.subscription_update_local_position) == 1, "size mismatch");
	memcpy(&topic.subscription_update_local_position, buf.iterator, sizeof(topic.subscription_update_local_position));
	buf.iterator += sizeof(topic.subscription_update_local_position);
	buf.offset += sizeof(topic.subscription_update_local_position);
	static_assert(sizeof(topic.subscription_update_attitude) == 1, "size mismatch");
	memcpy(&topic.subscription_update_attitude, buf.iterator, sizeof(topic.subscription_update_attitude));
	buf.iterator += sizeof(topic.subscription_update_attitude);
	buf.offset += sizeof(topic.subscription_update_attitude);
	static_assert(sizeof(topic.subscription_update_trajectory_setpoint) == 1, "size mismatch");
	memcpy(&topic.subscription_update_trajectory_setpoint, buf.iterator, sizeof(topic.subscription_update_trajectory_setpoint));
	buf.iterator += sizeof(topic.subscription_update_trajectory_setpoint);
	buf.offset += sizeof(topic.subscription_update_trajectory_setpoint);
	static_assert(sizeof(topic.subscription_update_vehicle_status) == 1, "size mismatch");
	memcpy(&topic.subscription_update_vehicle_status, buf.iterator, sizeof(topic.subscription_update_vehicle_status));
	buf.iterator += sizeof(topic.subscription_update_vehicle_status);
	buf.offset += sizeof(topic.subscription_update_vehicle_status);
	static_assert(sizeof(topic.exit_reason) == 1, "size mismatch");
	memcpy(&topic.exit_reason, buf.iterator, sizeof(topic.exit_reason));
	buf.iterator += sizeof(topic.exit_reason);
	buf.offset += sizeof(topic.exit_reason);
	buf.iterator += 2; // padding
	buf.offset += 2; // padding
	static_assert(sizeof(topic.timestamp_last_vehicle_angular_velocity) == 4, "size mismatch");
	memcpy(&topic.timestamp_last_vehicle_angular_velocity, buf.iterator, sizeof(topic.timestamp_last_vehicle_angular_velocity));
	buf.iterator += sizeof(topic.timestamp_last_vehicle_angular_velocity);
	buf.offset += sizeof(topic.timestamp_last_vehicle_angular_velocity);
	static_assert(sizeof(topic.timestamp_last_vehicle_local_position) == 4, "size mismatch");
	memcpy(&topic.timestamp_last_vehicle_local_position, buf.iterator, sizeof(topic.timestamp_last_vehicle_local_position));
	buf.iterator += sizeof(topic.timestamp_last_vehicle_local_position);
	buf.offset += sizeof(topic.timestamp_last_vehicle_local_position);
	static_assert(sizeof(topic.timestamp_last_vehicle_attitude) == 4, "size mismatch");
	memcpy(&topic.timestamp_last_vehicle_attitude, buf.iterator, sizeof(topic.timestamp_last_vehicle_attitude));
	buf.iterator += sizeof(topic.timestamp_last_vehicle_attitude);
	buf.offset += sizeof(topic.timestamp_last_vehicle_attitude);
	static_assert(sizeof(topic.timestamp_last_trajectory_setpoint) == 4, "size mismatch");
	memcpy(&topic.timestamp_last_trajectory_setpoint, buf.iterator, sizeof(topic.timestamp_last_trajectory_setpoint));
	buf.iterator += sizeof(topic.timestamp_last_trajectory_setpoint);
	buf.offset += sizeof(topic.timestamp_last_trajectory_setpoint);
	static_assert(sizeof(topic.vehicle_angular_velocity_stale) == 1, "size mismatch");
	memcpy(&topic.vehicle_angular_velocity_stale, buf.iterator, sizeof(topic.vehicle_angular_velocity_stale));
	buf.iterator += sizeof(topic.vehicle_angular_velocity_stale);
	buf.offset += sizeof(topic.vehicle_angular_velocity_stale);
	static_assert(sizeof(topic.vehicle_local_position_stale) == 1, "size mismatch");
	memcpy(&topic.vehicle_local_position_stale, buf.iterator, sizeof(topic.vehicle_local_position_stale));
	buf.iterator += sizeof(topic.vehicle_local_position_stale);
	buf.offset += sizeof(topic.vehicle_local_position_stale);
	static_assert(sizeof(topic.vehicle_attitude_stale) == 1, "size mismatch");
	memcpy(&topic.vehicle_attitude_stale, buf.iterator, sizeof(topic.vehicle_attitude_stale));
	buf.iterator += sizeof(topic.vehicle_attitude_stale);
	buf.offset += sizeof(topic.vehicle_attitude_stale);
	static_assert(sizeof(topic.trajectory_setpoint_stale) == 1, "size mismatch");
	memcpy(&topic.trajectory_setpoint_stale, buf.iterator, sizeof(topic.trajectory_setpoint_stale));
	buf.iterator += sizeof(topic.trajectory_setpoint_stale);
	buf.offset += sizeof(topic.trajectory_setpoint_stale);
	static_assert(sizeof(topic.active) == 1, "size mismatch");
	memcpy(&topic.active, buf.iterator, sizeof(topic.active));
	buf.iterator += sizeof(topic.active);
	buf.offset += sizeof(topic.active);
	static_assert(sizeof(topic.substep) == 1, "size mismatch");
	memcpy(&topic.substep, buf.iterator, sizeof(topic.substep));
	buf.iterator += sizeof(topic.substep);
	buf.offset += sizeof(topic.substep);
	buf.iterator += 2; // padding
	buf.offset += 2; // padding
	static_assert(sizeof(topic.control_interval) == 4, "size mismatch");
	memcpy(&topic.control_interval, buf.iterator, sizeof(topic.control_interval));
	buf.iterator += sizeof(topic.control_interval);
	buf.offset += sizeof(topic.control_interval);
	static_assert(sizeof(topic.trajectory_setpoint_dt_mean) == 4, "size mismatch");
	memcpy(&topic.trajectory_setpoint_dt_mean, buf.iterator, sizeof(topic.trajectory_setpoint_dt_mean));
	buf.iterator += sizeof(topic.trajectory_setpoint_dt_mean);
	buf.offset += sizeof(topic.trajectory_setpoint_dt_mean);
	static_assert(sizeof(topic.trajectory_setpoint_dt_max) == 4, "size mismatch");
	memcpy(&topic.trajectory_setpoint_dt_max, buf.iterator, sizeof(topic.trajectory_setpoint_dt_max));
	buf.iterator += sizeof(topic.trajectory_setpoint_dt_max);
	buf.offset += sizeof(topic.trajectory_setpoint_dt_max);
	static_assert(sizeof(topic.trajectory_setpoint_dt_max_since_activation) == 4, "size mismatch");
	memcpy(&topic.trajectory_setpoint_dt_max_since_activation, buf.iterator, sizeof(topic.trajectory_setpoint_dt_max_since_activation));
	buf.iterator += sizeof(topic.trajectory_setpoint_dt_max_since_activation);
	buf.offset += sizeof(topic.trajectory_setpoint_dt_max_since_activation);
	static_assert(sizeof(topic.internal_reference_position) == 12, "size mismatch");
	memcpy(&topic.internal_reference_position, buf.iterator, sizeof(topic.internal_reference_position));
	buf.iterator += sizeof(topic.internal_reference_position);
	buf.offset += sizeof(topic.internal_reference_position);
	static_assert(sizeof(topic.internal_reference_linear_velocity) == 12, "size mismatch");
	memcpy(&topic.internal_reference_linear_velocity, buf.iterator, sizeof(topic.internal_reference_linear_velocity));
	buf.iterator += sizeof(topic.internal_reference_linear_velocity);
	buf.offset += sizeof(topic.internal_reference_linear_velocity);
	return true;
}
