#!/usr/bin/env python3
import matplotlib
matplotlib.use('Agg')  # Non-interactive backend
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
    
    time_data = []
    x_data = []
    y_data = []
    z_data = []
    yaw_data = []
    att_time = []
    
    start_time = None
    
    while reader.has_next():
        topic, data, timestamp = reader.read_next()
        
        if start_time is None:
            start_time = timestamp
        
        time_sec = (timestamp - start_time) / 1e9
        
        msg_type = get_message(type_map[topic])
        msg = deserialize_message(data, msg_type)
        
        if topic == '/fmu/out/vehicle_local_position_v1':
            time_data.append(time_sec)
            x_data.append(msg.x)
            y_data.append(msg.y)
            z_data.append(-msg.z)
            
        elif topic == '/fmu/out/vehicle_attitude':
            att_time.append(time_sec)
            q = msg.q
            yaw = np.arctan2(2.0*(q[0]*q[3] + q[1]*q[2]), 1.0 - 2.0*(q[2]**2 + q[3]**2))
            yaw_data.append(np.degrees(yaw))
    
    return time_data, x_data, y_data, z_data, att_time, yaw_data

def plot_trajectory(bag_path):
    print(f"Reading bag file: {bag_path}")
    
    time_data, x_data, y_data, z_data, att_time, yaw_data = read_bag(bag_path)
    
    fig, axes = plt.subplots(2, 2, figsize=(14, 10))
    
    # Plot 1: XY view (top-down)
    axes[0, 0].plot(x_data, y_data, 'b-', linewidth=1)
    axes[0, 0].scatter(x_data[0], y_data[0], c='g', s=100, marker='o', label='Start')
    axes[0, 0].scatter(x_data[-1], y_data[-1], c='r', s=100, marker='x', label='End')
    axes[0, 0].set_xlabel('X (m)')
    axes[0, 0].set_ylabel('Y (m)')
    axes[0, 0].set_title('Top View (XY Plane)')
    axes[0, 0].legend()
    axes[0, 0].grid(True)
    axes[0, 0].axis('equal')
    
    # Plot 2: XZ view (side)
    axes[0, 1].plot(x_data, z_data, 'b-', linewidth=1)
    axes[0, 1].scatter(x_data[0], z_data[0], c='g', s=100, marker='o', label='Start')
    axes[0, 1].scatter(x_data[-1], z_data[-1], c='r', s=100, marker='x', label='End')
    axes[0, 1].set_xlabel('X (m)')
    axes[0, 1].set_ylabel('Z (m) - ENU')
    axes[0, 1].set_title('Side View (XZ Plane)')
    axes[0, 1].legend()
    axes[0, 1].grid(True)
    
    # Plot 3: Altitude over time
    axes[1, 0].plot(time_data, z_data, 'b-', linewidth=1)
    axes[1, 0].set_xlabel('Time (s)')
    axes[1, 0].set_ylabel('Altitude (m) - ENU')
    axes[1, 0].set_title('Altitude vs Time')
    axes[1, 0].grid(True)
    
    # Plot 4: Yaw over time
    axes[1, 1].plot(att_time, yaw_data, 'r-', linewidth=1)
    axes[1, 1].set_xlabel('Time (s)')
    axes[1, 1].set_ylabel('Yaw (degrees)')
    axes[1, 1].set_title('Yaw vs Time')
    axes[1, 1].grid(True)
    
    plt.tight_layout()
    plt.savefig('trajectory_plots.png', dpi=150)
    print("Saved: trajectory_plots.png")

if __name__ == '__main__':
    import sys
    bag_path = sys.argv[1] if len(sys.argv) > 1 else 'test_trajectory'
    plot_trajectory(bag_path)
