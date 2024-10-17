import pandas as pd
import matplotlib.pyplot as plt

# Load the data
data = pd.read_csv('simulation_results.csv')

# Separate the queue size data
queue_size = data['Queue Size'].tolist()

# Plotting queue size over time
plt.figure(figsize=(10, 5))
plt.plot(queue_size, label='Queue Size Over Time', marker='o')
plt.title('Queue Size Over Time')
plt.xlabel('Clock Cycle')
plt.ylabel('Queue Size')
plt.grid()
plt.legend()
plt.savefig('queue_size_over_time.png')  # Save the plot as a file
plt.show()  # Display the plot

# Plotting requests handled by each server
requests_handled = data.iloc[data[data['Server'].notnull()].index[0]:]['Requests Handled'].tolist()
server_names = data.iloc[data[data['Server'].notnull()].index[0]:]['Server'].tolist()

plt.figure(figsize=(10, 5))
plt.bar(server_names, requests_handled, color='skyblue')
plt.title('Requests Handled by Each Server')
plt.xlabel('Server')
plt.ylabel('Requests Handled')
plt.xticks(rotation=45)
plt.grid(axis='y')
plt.tight_layout()  # Adjust layout
plt.savefig('requests_handled.png')  # Save the plot as a file
plt.show()  # Display the plot
