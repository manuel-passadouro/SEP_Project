import csv
from datetime import datetime
import time

def test_csv_write():
    log_file = "test_uart_data_log.csv"  # Test log file name

    # Open the CSV file once for writing
    try:
        with open(log_file, mode='w', newline='') as file:  # Overwrite if exists
            writer = csv.writer(file)

            # Write header
            writer.writerow(["Timestamp", "Data"])

            # Simulate writing data for a few iterations
            for i in range(10):  # Simulate 10 data entries
                timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")  # Generate timestamp
                data = f"Test Data {i}"  # Simulated data
                writer.writerow([timestamp, data])  # Write timestamp and simulated data
                print(f"Logged: {timestamp}, {data}")  # Print log message
                time.sleep(10)  # Wait for 1 second before next entry

    except Exception as e:
        print(f"Error opening/writing to CSV: {e}")

if __name__ == "__main__":
    test_csv_write()
