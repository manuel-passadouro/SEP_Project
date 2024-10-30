import tkinter as tk
from tkinter import scrolledtext, ttk, messagebox
from PIL import Image, ImageTk
import serial
import serial.tools.list_ports
import threading
import time
import csv
from datetime import datetime

# Variables for UART and message count
uart = None
connected = False
message_count = 0
log_file = "uart_data_log.csv"

#Constants for Temperature data conversion
VREF_MV = 3200          # Reference voltage in millivolts (3500 mV)
ADC_MAX_VALUE = 1023    # Max ADC value for a 10-bit ADC

# Initial RGB color for the square (customizable)
#global rgb_color
rgb_color = (255, 111, 55)  # Red color

def open_log_file():
    global csv_file, writer
    try:
        csv_file = open(log_file, mode='w', newline='')     # Open the CSV file for appending
        writer = csv.writer(csv_file)
        writer.writerow(["Timestamp", "Data"])              # Write header only once
    except Exception as e:
        print(f"Error opening log file: {e}")

# Function to connect to UART with selected settings
def connect_uart():
    global uart, connected
    com_port = com_port_var.get()
    baud_rate = baud_rate_var.get()
    
    if not com_port or not baud_rate:
        messagebox.showwarning("Warning", "Please select both COM port and baud rate.")
        return
    
    try:
        uart = serial.Serial(port=com_port, baudrate=int(baud_rate), timeout=1)
        connected = True
        messagebox.showinfo("Success", f"Connected to {com_port} at {baud_rate} baud.")
        threading.Thread(target=read_uart, daemon=True).start()
    except Exception as e:
        messagebox.showerror("Connection Error", f"Failed to connect: {e}")

def read_uart():
    global connected, message_count, rgb_color
    
    while connected:
        try:
            if uart.in_waiting > 0:
                data = uart.read(10) #Read 10 bytes from UART buffer
                print("Size of data:", len(data))

                if data[0:1].decode('utf-8') == 'A':
                    
                    # Read the next two bytes separately
                    temp_low = data[1]
                    temp_high = data[2]
                    temp_value = (temp_high << 8) | temp_low  # Combine high and low bytes

                    temp_k = (temp_value/ADC_MAX_VALUE) * VREF_MV
                    temp_c = temp_k - 273.15

                    # Cap temp_c to 1 decimal place
                    temp_c = round(temp_c, 1)
                                      
                    # Display the high and low bytes separately
                    text_area.insert(tk.END, f"Ambient Temp [C]: {temp_high}, {temp_low}, {temp_c}\n")
                    text_area.see(tk.END)

                    # Log the temperature bytes
                    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    writer.writerow([timestamp, f"Ambient Temp [C]: {temp_c}"])
                    csv_file.flush()
                    print(f"Logged: {timestamp}, Ambient Temp [C]: {temp_c}")

                elif data[0:1].decode('utf-8') == 'B':
                    # Check if at least 2 more bytes are available
                    
                    # Read the next two bytes separately
                    prox_low = data[1]
                    prox_high = data[2]
                    prox_value = (prox_high << 8) | prox_low  # Combine high and low bytes
    
                    # Display the 16-bit proximity value
                    text_area.insert(tk.END, f"Prox: {prox_value}\n")
                    text_area.see(tk.END)

                    # Log the 16-bit proximity value
                    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    writer.writerow([timestamp, f"Prox: {prox_value}"])
                    csv_file.flush()
                    print(f"Logged: {timestamp}, Prox: {prox_value}")

                elif data[0:1].decode('utf-8') == 'C':
                    # Check if at least 2 more bytes are available
                   
                    # Read the next two bytes separately
                    light_low = data[1]
                    light_high = data[2]
                    light_value = (light_high << 8) | light_low  # Combine high and low bytes
    
                    # Display the 16-bit light value
                    text_area.insert(tk.END, f"Light: {light_value}\n")
                    text_area.see(tk.END)

                    # Log the 16-bit light value
                    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    writer.writerow([timestamp, f"Light: {light_value}"])
                    csv_file.flush()
                    print(f"Logged: {timestamp}, Light: {light_value}")

                elif data[0:1].decode('utf-8') == 'D':
                    # Check if at least 2 more bytes are available
                   
                    # Read the next two bytes separately
                    red_low = data[1]
                    red_high = data[2]
                    green_low = data[3]
                    green_high = data[4]
                    blue_low = data[5]
                    blue_high = data[6]

                    # Calculate the 16-bit values from high and low bytes
                    red_16bit = (red_high << 8) | red_low
                    green_16bit = (green_high << 8) | green_low
                    blue_16bit = (blue_high << 8) | blue_low

                    # Scale down 16 bit values to prevent overflow
                    red_8bit = red_16bit >> 4 
                    green_8bit = green_16bit >> 4
                    blue_8bit = blue_16bit >> 4

                    # Ensure values are within the 0-255 range
                    red_8bit = min(max(red_8bit, 0), 255)
                    green_8bit = min(max(green_8bit, 0), 255)
                    blue_8bit = min(max(blue_8bit, 0), 255)

                    
                    # Display the high and low bytes separately
                    rgb_color = (red_8bit, green_8bit, blue_8bit)
                    update_square_color()
                    
                    text_area.insert(tk.END, f"RGB: {red_8bit}, {green_8bit}, {blue_8bit}\n")

                    text_area.see(tk.END)

                    # Log the temperature bytes
                    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    writer.writerow([timestamp, f"RGB: {red_high}, {red_low}, {green_high}, {green_low},"
                                     f" {blue_high}, {blue_low}"])
                    csv_file.flush()
                    print(f"Logged: {timestamp}, RGB: {red_high}, {red_low}, {green_high}, {green_low},"
                                     f" {blue_high}, {blue_low}")
                    
                else:
                    # Handle undifined cases
                    
                    text_area.insert(tk.END, f"CMD error\n")
                    text_area.see(tk.END)

                    # Log the error bytes
                    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    writer.writerow([timestamp, f"CMD error"])
                    csv_file.flush()
                    print(f"CMD error")
                    #print(f"Invalid Message Received")

                last_data_time_var.set("Last Data Received: " + timestamp)
                message_count += 1
                message_count_var.set(f"Messages Received: {message_count}")
        except Exception as e:
            print(f"Error reading from UART: {e}")
        time.sleep(0.1)




def send_command(command):
    if uart and connected:
        uart.write((command + '\n').encode('utf-8'))
        last_command_time_var.set("Last Command Sent: " + datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
    else:
        messagebox.showwarning("Warning", "Please connect to a UART port first.")

def update_time():
    current_time_var.set("Current Time: " + datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
    root.after(1000, update_time)

# Function to update the color of the square based on the rgb_color variable
def update_square_color():
    print(f"Color Update")
    hex_color = "#{:02x}{:02x}{:02x}".format(*rgb_color)
    color_square.config(bg=hex_color)

# GUI setup
root = tk.Tk()
root.title("UART Communication")
root.geometry("800x600")

# Load and display the image
image = Image.open("ist.png")
image = image.resize((60, 70), Image.LANCZOS)
photo = ImageTk.PhotoImage(image)
image_label = tk.Label(root, image=photo)
image_label.image = photo
image_label.place(x=10, y=10)

# Project info
project_info = "SEP Project\nGroup 1:\nManuel Passadouro, 80840\nMiguel Simões, 99162"
project_label = tk.Label(root, text=project_info, font=("Arial", 10), anchor="w", justify="left")
project_label.place(x=80, y=10)

# Frame for COM port and baud rate selection
settings_frame = tk.Frame(root)
settings_frame.pack(pady=10)

# COM Port Selection
tk.Label(settings_frame, text="COM Port:").grid(row=0, column=0, padx=5, pady=5)
com_port_var = tk.StringVar()
com_ports = [port.device for port in serial.tools.list_ports.comports()]
com_port_combo = ttk.Combobox(settings_frame, textvariable=com_port_var, values=com_ports, width=10)
com_port_combo.grid(row=0, column=1, padx=5, pady=5)

# Baud Rate Selection
tk.Label(settings_frame, text="Baud Rate:").grid(row=1, column=0, padx=5, pady=5)
baud_rate_var = tk.StringVar()
baud_rates = ["9600", "19200", "38400", "57600", "115200"]
baud_rate_combo = ttk.Combobox(settings_frame, textvariable=baud_rate_var, values=baud_rates, width=10)
baud_rate_combo.grid(row=1, column=1, padx=5, pady=5)

# Connect Button
connect_button = tk.Button(settings_frame, text="Connect", command=connect_uart)
connect_button.grid(row=2, column=0, columnspan=2, pady=10)

# Main frame for ScrolledText and color square
main_frame = tk.Frame(root)
main_frame.pack(pady=10, fill=tk.X)

# ScrolledText widget for UART data
text_area = scrolledtext.ScrolledText(main_frame, wrap=tk.WORD, width=40, height=10)
text_area.pack(side="left", padx=60, pady=5)

# Frame for the color square and its label
color_square_frame = tk.Frame(main_frame)
color_square_frame.pack(side="left", padx=20)

# Label for the color square, positioned above the RGB box
color_square_label = tk.Label(color_square_frame, text="Detected Object Color", font=("Arial", 10))
color_square_label.grid(row=0, column=0, pady=(0, 5))  # Padding below the label for spacing

# RGB color square placed directly below the label
color_square = tk.Label(color_square_frame, width=25, height=12)  # Adjust dimensions for a larger box
color_square.grid(row=1, column=0)
update_square_color()

# Frame for command buttons and labels
button_frame = tk.Frame(root)
button_frame.pack(pady=10)

# Example command buttons
btn1 = tk.Button(button_frame, text="TEMP", command=lambda: send_command("A"))
btn1.grid(row=0, column=0, padx=5)

btn2 = tk.Button(button_frame, text="PROX", command=lambda: send_command("B"))
btn2.grid(row=0, column=1, padx=5)

btn3 = tk.Button(button_frame, text="LIGHT", command=lambda: send_command("C"))
btn3.grid(row=0, column=2, padx=5)

btn4 = tk.Button(button_frame, text="RGB", command=lambda: send_command("D"))
btn4.grid(row=0, column=3, padx=5)

# Labels for time, command, data, and message count
current_time_var = tk.StringVar()
last_command_time_var = tk.StringVar(value="Last Command Sent: N/A")
last_data_time_var = tk.StringVar(value="Last Data Received: N/A")
message_count_var = tk.StringVar(value="Messages Received: 0")

current_time_label = tk.Label(root, textvariable=current_time_var, font=("Arial", 12))
current_time_label.pack(pady=5)

last_command_time_label = tk.Label(root, textvariable=last_command_time_var, font=("Arial", 12))
last_command_time_label.pack(pady=5)

last_data_time_label = tk.Label(root, textvariable=last_data_time_var, font=("Arial", 12))
last_data_time_label.pack(pady=5)

message_count_label = tk.Label(root, textvariable=message_count_var, font=("Arial", 12))
message_count_label.pack(pady=5)

# Start the current time updater
update_time()

# Open the log file when the application starts
open_log_file()

# Start the GUI event loop
root.mainloop()
