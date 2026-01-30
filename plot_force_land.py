#!/usr/bin/env python3
import matplotlib.pyplot as plt
from rclpy.serialization import deserialize_message
from rosidl_runtime_py.utilities import get_message
import rosbag2_py
import numpy as np

def read_bag(bag_path):
    """Read messages from a ROS2 bag file."""
    storage_options = rosbag2_py.StorageOptions(uri=bag_path, storage_id='sqlite3')
    converter_options = rosbag2_py.ConverterOptions(
        input_serialization_format='cdr',
        output_serialization_format='cdr'
    )
    
    reader = rosbag2_py.SequentialReader()
    reader.open(storage_options, converter_options)
    
    topic_types = reader.get_all_topics_and_types()
    type_map = {topic.name: topic.type for topic in topic_types}
    
    # Data storage
    altitude_time = []
    altitude_data = []
    throttle_time = []
    throttle_data = []
    land_detected_time = []
    land_detected_data = []
    
    start_time = None
    
    while reader.has_next():
        topic, data, timestamp = reader.read_next()
        
        if start_time is None:
            start_time = timestamp
        
        time_sec = (timestamp - start_time) / 1e9  # Convert to seconds
        
        msg_type = get_message(type_map[topic])
        msg = deserialize_message(data, msg_type)
        
        if topic == '/fmu/out/vehicle_local_position_v1':
            altitude_time.append(time_sec)
            altitude_data.append(-msg.z)  # Convert NED to ENU (z up)
            
        elif topic == '/fmu/out/manual_control_setpoint':
            throttle_time.append(time_sec)
            throttle_data.append(msg.throttle)
            
        elif topic == '/fmu/out/vehicle_land_detected':
            land_detected_time.append(time_sec)
            land_detected_data.append(1 if msg.landed else 0)
    
    return (altitude_time, altitude_data, 
            throttle_time, throttle_data,
            land_detected_time, land_detected_data)

def plot_data(bag_path):
    """Generate plots from bag data."""
    print(f"Reading bag file: {bag_path}")
    
    (alt_time, alt_data, 
     throttle_time, throttle_data,
     land_time, land_data) = read_bag(bag_path)
    
    # Create figure with subplots
    fig, axes = plt.subplots(3, 1, figsize=(12, 10), sharex=True)
    
    # Plot 1: Altitude
    axes[0].plot(alt_time, alt_data, 'b-', linewidth=1, label='Altitude')
    axes[0].axhline(y=20, color='r', linestyle='--', linewidth=2, label='Threshold (20m)')
    axes[0].set_ylabel('Altitude (m) - ENU')
    axes[0].set_title('Drone Altitude During Force Land Test')
    axes[0].legend(loc='upper right')
    axes[0].grid(True)
    
    # Plot 2: Throttle (Manual Control Setpoint)
    axes[1].plot(throttle_time, throttle_data, 'g-', linewidth=1, label='Throttle')
    axes[1].set_ylabel('Throttle')
    axes[1].set_title('Manual Control Setpoint (Throttle)')
    axes[1].legend(loc='upper right')
    axes[1].grid(True)
    
    # Plot 3: Land Detected
    axes[2].plot(land_time, land_data, 'r-', linewidth=2, label='Landed')
    axes[2].set_ylabel('Landed (0/1)')
    axes[2].set_xlabel('Time (s)')
    axes[2].set_title('Vehicle Land Detected')
    axes[2].legend(loc='upper right')
    axes[2].grid(True)
    axes[2].set_ylim(-0.1, 1.1)
    
    plt.tight_layout()
    plt.savefig('force_land_plots.png', dpi=150)
    print("Saved: force_land_plots.png")
    plt.show()

if __name__ == '__main__':
    import sys
    bag_path = sys.argv[1] if len(sys.argv) > 1 else 'test_force_land'
    plot_data(bag_path)
