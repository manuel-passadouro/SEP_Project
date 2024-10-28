import tkinter as tk
from tkinter import messagebox
import csv

# Function to save data to CSV
def save_data_to_csv():
    data = entry.get()  # Get the data from the entry box
    if data:
        try:
            with open('uart_data_log.csv', mode='a', newline='') as file:  # Append mode
                writer = csv.writer(file)
                writer.writerow([data])  # Write the data as a new row
            messagebox.showinfo("Success", "Data saved to CSV successfully!")
            entry.delete(0, tk.END)  # Clear the entry box
        except Exception as e:
            messagebox.showerror("Error", f"Error saving to CSV: {e}")
    else:
        messagebox.showwarning("Warning", "Please enter some data before saving.")

# Set up the main application window
root = tk.Tk()
root.title("Simple CSV Logger")
root.geometry("400x200")

# Create a label
label = tk.Label(root, text="Enter data to save to CSV:")
label.pack(pady=10)

# Create an entry box
entry = tk.Entry(root, width=40)
entry.pack(pady=10)

# Create a button to save data
save_button = tk.Button(root, text="Save to CSV", command=save_data_to_csv)
save_button.pack(pady=20)

# Start the Tkinter event loop
root.mainloop()
